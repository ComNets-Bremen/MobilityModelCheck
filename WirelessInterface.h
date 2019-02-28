
#ifndef __MOBILITYMODELCHECK_WIRELESSINTERFACE_H_
#define __MOBILITYMODELCHECK_WIRELESSINTERFACE_H_

#include "inet/mobility/contract/IMobility.h"

#include <omnetpp.h>

using namespace omnetpp;
using namespace std;

class WirelessInterface : public cSimpleModule
{
  protected:
    virtual void initialize(int stage);
    virtual int numInitStages() const;
    virtual void handleMessage(cMessage *msg);

  private:
    typedef struct nodeinfo {
        string nodeName;
        inet::IMobility *nodeMobilityModule;
        bool contactStarted;
        double contactStartTime;
    } NodeInfo;

    double wirelessRange;
    string ownName;
    inet::IMobility *ownMobilityModule;
    list<NodeInfo*> allNodeInfoList;
    list<NodeInfo*> currentNeighbourNodeInfoList;
    list<NodeInfo*> newNeighbourNodeInfoList;
    simsignal_t contactMadeSignalID;
    simsignal_t contactDurationSignalID;
    simsignal_t neighbourhoodSizeSignalID;
};

#endif
