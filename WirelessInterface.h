//
// The model that implements the UDG model to check
// connectivity to other nodes in the neighbourhood
//
// @author : Asanga Udugama (adu@comnets.uni-bremen.de)
// @date   : 02-may-2017
//
//

#ifndef __MOBILITYMODELCHECK_WIRELESSINTERFACE_H_
#define __MOBILITYMODELCHECK_WIRELESSINTERFACE_H_

#include "inet/mobility/contract/IMobility.h"

#include <omnetpp.h>

using namespace omnetpp;
using namespace std;

#include <fstream>

//int numContacts = 0;
//double sumContactDurations = 0.0;
//int sumNeighbourhoodSize = 0;
//int totNeighbourhoodReportingTimes = 0;

bool pathFileOpen = false;
ofstream pathFile;

class WirelessInterface : public cSimpleModule
{
  protected:
    virtual void initialize(int stage);
    virtual int numInitStages() const;
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

  private:
    typedef struct nodeinfo {
        string nodeName;
        inet::IMobility *nodeMobilityModule;
        bool contactStarted;
        double contactStartTime;
    } NodeInfo;

    double wirelessRange;
    double neighbourhoodCheckingInterval;
    double statReportingInterval;
    bool nodePathRecorded;
    string nodePathFileName;
    string ownName;

    cMessage *checkNeighboursEvent;
    cMessage *statReportingEvent;

    inet::IMobility *ownMobilityModule;
    list<NodeInfo*> allNodeInfoList;
    list<NodeInfo*> currentNeighbourNodeInfoList;
    list<NodeInfo*> newNeighbourNodeInfoList;

    simsignal_t contactMadeSignalID;
    simsignal_t contactDurationSignalID;
    simsignal_t neighbourhoodSizeSignalID;

    simsignal_t periodicCountOfContactsMadeID;
    simsignal_t periodicAvgOfContactDurationID;
    simsignal_t periodicAvgOfNeighbourhoodSizesID;

    long totContactsSinceLast;
    double totContactDurationsSinceLast;
    long totNeighbourhoodSizeReportsSinceLast;
    long totNeighbourhoodSizesSinceLast;

};

#endif
