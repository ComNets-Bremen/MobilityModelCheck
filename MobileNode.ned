//
// Node model to check mobility
//
// @author : Asanga Udugama (adu@comnets.uni-bremen.de)
// @date   : 28-feb-2019
//

import inet.mobility.contract.IMobility;

module MobileNode
{
    parameters:
        @networkNode();

        // unique node identifier
        int nodeID;

        // mobility model used
        string mobilityType = default("StationaryMobility");

        // icon
        @display("i=device/palm2;bgb=250,340");

        // statistics
        @statistic[contactMadeMovingAvg](source=mean(contactMade);record=count,stats,vector);
        @statistic[contactDurationMovingAvg](source=mean(contactDuration);record=count,stats,vector);
        @statistic[neighbourhoodSizeMovingAvg](source=mean(neighbourhoodSize);record=count,stats,vector);

        @statistic[periodicCountOfContactsMade](source=periodicCountOfContactsMade;record=stats,vector);
        @statistic[periodicAvgOfContactDuration](source=periodicAvgOfContactDuration;record=stats,vector);
        @statistic[periodicAvgOfNeighbourhoodSizes](source=periodicAvgOfNeighbourhoodSizes;record=stats,vector);

    submodules:

         // wifi adhoc interface
        wirelessIfc: WirelessInterface;

        // mobility
        mobility: <mobilityType> like IMobility;
}

