
#include "WirelessInterface.h"

Define_Module(WirelessInterface);

void WirelessInterface::initialize(int stage)
{
    if (stage == 0) {

        // get params
        wirelessRange = par("wirelessRange");
        neighbourhoodCheckingInterval = par("neighbourhoodCheckingInterval");
        nodePathRecorded = par("nodePathRecorded");
        nodePathFileName = par("nodePathFileName").stringValue();
        statReportingInterval = par("statReportingInterval");

    } else if (stage == 1) {

        // get own model pointers
        ownName = getParentModule()->getFullName();
        for (cModule::SubmoduleIterator it(getParentModule()); !it.end(); ++it) {
            ownMobilityModule = dynamic_cast<inet::IMobility*>(*it);
            if (ownMobilityModule != NULL) {
                break;
            }
        }

    } else if (stage == 2) {

        // get other model pointers
        for (int id = 0; id <= getSimulation()->getLastComponentId(); id++) {
            cModule *unknownModule = getSimulation()->getModule(id);
            if (unknownModule == NULL) {
                continue;
            }
            inet::IMobility *mobilityModule = dynamic_cast<inet::IMobility*>(unknownModule);
            if (mobilityModule == NULL) {
                continue;
            }

            if (strstr(unknownModule->getParentModule()->getFullName(), ownName.c_str()) != NULL) {
                continue;
            }

            NodeInfo *nodeInfo = new NodeInfo();
            nodeInfo->nodeMobilityModule = mobilityModule;
            nodeInfo->nodeName = unknownModule->getParentModule()->getFullName();
            nodeInfo->contactStartTime = 0.0;
            nodeInfo->contactStarted = true;
            allNodeInfoList.push_back(nodeInfo);

        }

        // setup neighbourhood check trigger
        checkNeighboursEvent = new cMessage("Check Neighbours Event");
        checkNeighboursEvent->setKind(100);
        scheduleAt(simTime() + neighbourhoodCheckingInterval, checkNeighboursEvent);

        // init stat signals
        contactMadeSignalID = registerSignal("contactMade");
        contactDurationSignalID = registerSignal("contactDuration");
        neighbourhoodSizeSignalID = registerSignal("neighbourhoodSize");

        periodicCountOfContactsMadeID = registerSignal("periodicCountOfContactsMade");
        periodicAvgOfContactDurationID = registerSignal("periodicAvgOfContactDuration");
        periodicAvgOfNeighbourhoodSizesID = registerSignal("periodicAvgOfNeighbourhoodSizes");

        // setup periodic stat trigger
        statReportingEvent = new cMessage("Stat Reporting Event");
        statReportingEvent->setKind(200);
        scheduleAt(simTime() + statReportingInterval, statReportingEvent);

        // init stat collection variables
        totContactsSinceLast = 0;
        totContactDurationsSinceLast = 0.0;
        totNeighbourhoodSizeReportsSinceLast = 0;
        totNeighbourhoodSizesSinceLast = 0;

        // open path recording file
        if(nodePathRecorded && !pathFileOpen) {
            pathFile.open(nodePathFileName, ios::out | ios::trunc);
            pathFileOpen = true;
        }
    }
}

int WirelessInterface::numInitStages() const
{
    return 3;
}

void WirelessInterface::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() && msg->getKind() == 100) {

        // init the new list
        while (newNeighbourNodeInfoList.size() > 0) {
            list<NodeInfo*>::iterator iteratorNeighbourNodeInfo = newNeighbourNodeInfoList.begin();
            NodeInfo *nodeInfo = *iteratorNeighbourNodeInfo;
            newNeighbourNodeInfoList.remove(nodeInfo);
        }

        // get current position of self
        inet::Coord ownCoord = ownMobilityModule->getCurrentPosition();

        // write to path recording file
        if(nodePathRecorded) {
            pathFile << ownName << "," << ownCoord.x << "," << ownCoord.y << "\n";
        }


        // make the new neighbour list
        list<NodeInfo*>::iterator iteratorNeighbourNodeInfo = allNodeInfoList.begin();
        while (iteratorNeighbourNodeInfo != allNodeInfoList.end()) {
            NodeInfo *nodeInfo = *iteratorNeighbourNodeInfo;
            inet::Coord neighCoord = nodeInfo->nodeMobilityModule->getCurrentPosition();

            double l = ((neighCoord.x - ownCoord.x) * (neighCoord.x - ownCoord.x))
                + ((neighCoord.y - ownCoord.y) * (neighCoord.y - ownCoord.y));
            double r = wirelessRange * wirelessRange;
            if (l <= r) {
                newNeighbourNodeInfoList.push_back(nodeInfo);
//                 EV_INFO << " " << simTime() << " " << ownName << " neighbour " << (newNeighbourNodeInfoList.size() - 1) << " " << nodeInfo->nodeName << "\n";
            }
            iteratorNeighbourNodeInfo++;
        }

//        if (newNeighbourNodeInfoList.size() > 0) {
//            sumNeighbourhoodSize += newNeighbourNodeInfoList.size();
//            totNeighbourhoodReportingTimes++;
//            // ANS = accumilated neighbourhood size
//            // TNRT = total neighbourhood reporting times
//            EV_INFO << " " << simTime() << " " << ownName << " ANS " << sumNeighbourhoodSize << " TNRT " << totNeighbourhoodReportingTimes << "\n";
//        }

        emit(neighbourhoodSizeSignalID, newNeighbourNodeInfoList.size());

        totNeighbourhoodSizesSinceLast += newNeighbourNodeInfoList.size();
        totNeighbourhoodSizeReportsSinceLast++;

        // check and update left neighbours
        list<NodeInfo*>::iterator iteratorOldNeighbourNodeInfo = currentNeighbourNodeInfoList.begin();
        while (iteratorOldNeighbourNodeInfo != currentNeighbourNodeInfoList.end()) {
            NodeInfo *oldNodeInfo = *iteratorOldNeighbourNodeInfo;

            bool found = false;
            list<NodeInfo*>::iterator iteratorNewNeighbourNodeInfo = newNeighbourNodeInfoList.begin();
            while (iteratorNewNeighbourNodeInfo != newNeighbourNodeInfoList.end()) {
                NodeInfo *newNodeInfo = *iteratorNewNeighbourNodeInfo;

                if (strstr(oldNodeInfo->nodeName.c_str(), newNodeInfo->nodeName.c_str()) != NULL) {
                    found = true;
                    break;
                }
                iteratorNewNeighbourNodeInfo++;
            }

            if (!found) {
                double contactDuration = simTime().dbl() - oldNodeInfo->contactStartTime;

//                EV_INFO << " " << simTime() << " " << ownName << " says: Contact with " << oldNodeInfo->nodeName << " ended at " << simTime().dbl() << " seconds - Contact duration was " << contactDuration << " seconds \n";

                oldNodeInfo->contactStarted = false;
                oldNodeInfo->contactStartTime = 0.0;

                currentNeighbourNodeInfoList.remove(oldNodeInfo);
                emit(contactMadeSignalID, 1);
                emit(contactDurationSignalID, contactDuration);

//                if (contactDuration > 0.0) {
//                    sumContactDurations += contactDuration;
//                    numContacts++;
//                    // ACD = accumilated contact durations
//                    // TNC = total number of contacts upto now
//                    EV_INFO << " " << simTime() << " " << ownName << " ACD " << sumContactDurations << " TNC " << numContacts << "\n";
//                }

                totContactDurationsSinceLast += contactDuration;
                totContactsSinceLast++;
            }

            if (!found) {
                iteratorOldNeighbourNodeInfo = currentNeighbourNodeInfoList.begin();
            } else {
                iteratorOldNeighbourNodeInfo++;
            }
        }

        // check and update new neighbours
        list<NodeInfo*>::iterator iteratorNewNeighbourNodeInfo = newNeighbourNodeInfoList.begin();
        while (iteratorNewNeighbourNodeInfo != newNeighbourNodeInfoList.end()) {
            NodeInfo *newNodeInfo = *iteratorNewNeighbourNodeInfo;

            bool found = false;
            list<NodeInfo*>::iterator iteratorOldNeighbourNodeInfo = currentNeighbourNodeInfoList.begin();
            while (iteratorOldNeighbourNodeInfo != currentNeighbourNodeInfoList.end()) {
                NodeInfo *oldNodeInfo = *iteratorOldNeighbourNodeInfo;

                if (strstr(newNodeInfo->nodeName.c_str(), oldNodeInfo->nodeName.c_str()) != NULL) {
                    found = true;
                    break;
                }
                iteratorOldNeighbourNodeInfo++;
            }

            if (!found) {
//                EV_INFO << " " << simTime() << " " << ownName << " says: Contact with " << newNodeInfo->nodeName << " started at " << simTime().dbl() << " seconds \n";
                newNodeInfo->contactStarted = true;
                newNodeInfo->contactStartTime = simTime().dbl();
                currentNeighbourNodeInfoList.push_back(newNodeInfo);
            }
            iteratorNewNeighbourNodeInfo++;
        }

        scheduleAt(simTime() + neighbourhoodCheckingInterval, msg);

    } else if (msg->isSelfMessage() && msg->getKind() == 200) {

        // create and emit periodic stats
        emit(periodicCountOfContactsMadeID, totContactsSinceLast);
        double avgContactDurationsSinceLast = 0.0;
        if (totContactsSinceLast > 0) {
            avgContactDurationsSinceLast = totContactDurationsSinceLast / totContactsSinceLast;
        }
        emit(periodicAvgOfContactDurationID, avgContactDurationsSinceLast);
        double avgNeighbourhoodSizeSinceLast = 0.0;
        if (totNeighbourhoodSizesSinceLast > 0) {
            avgNeighbourhoodSizeSinceLast = totNeighbourhoodSizesSinceLast / totNeighbourhoodSizeReportsSinceLast;
        }
        emit(periodicAvgOfNeighbourhoodSizesID, avgNeighbourhoodSizeSinceLast);

        // init stat collection variables for next round
        totContactsSinceLast = 0;
        totContactDurationsSinceLast = 0.0;
        totNeighbourhoodSizeReportsSinceLast = 0;
        totNeighbourhoodSizesSinceLast = 0;

        // setup periodic stat trigger again
        scheduleAt(simTime() + statReportingInterval, msg);
    }
}


void WirelessInterface::finish()
{
    // close path recording file
    if(nodePathRecorded && pathFileOpen) {
        pathFile.close();
        pathFileOpen = false;
    }

}
