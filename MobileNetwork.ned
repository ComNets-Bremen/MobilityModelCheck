
network MobileNetwork
{
   parameters:
        int numNodes = default(20);


        // statistics
        @statistic[movingAvgOfContactsMade](source=mean(contactMade);record=count,last,vector);
        @statistic[movingAvfOfContactDurations](source=mean(contactDuration);record=count,last,vector);
        @statistic[movingAvgOfNeighbourhoodSizes](source=mean(neighbourhoodSize);record=count,last,vector);

        @statistic[movingAvgOfPeriodicContactsMade](source=mean(periodicCountOfContactsMade);record=last,vector);
        @statistic[movingAvgOfPeriodicContactDurations](source=mean(periodicAvgOfContactDuration);record=last,vector);
        @statistic[movingAvgOfPeriodicNeighbourhoodSizes](source=mean(periodicAvgOfNeighbourhoodSizes);record=last,vector);


    submodules:

        // nodes of the network
        node[numNodes]: MobileNode {
            nodeID = index;
        }
}
