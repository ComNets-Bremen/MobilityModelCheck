//
// The model that implements the UDG model to check
// connectivity to other nodes in the neighbourhood
//
// @author : Asanga Udugama (adu@comnets.uni-bremen.de)
// @date   : 02-may-2017
//
//

simple WirelessInterface
{
    parameters:
        
        // wireless interface parameters
        double wirelessRange @unit(m) = default(30m);

		// neighbourhood checking interval
		double neighbourhoodCheckingInterval @unit(s) = default(1s);

        // statistic reporting interval for periodic statistics
        double statReportingInterval @unit(s) = default(100s);
        
        // node path coordinates collection params
        bool nodePathRecorded = default(false);
        string nodePathFileName = default("node-paths.csv");

        // icon
        @display("i=device/card");

        // signals for statistics
        @signal[contactMade](type=long);
        @signal[contactDuration](type=double);
        @signal[neighbourhoodSize](type=long);

        @signal[periodicCountOfContactsMade](type=long);
        @signal[periodicAvgOfContactDuration](type=double);
        @signal[periodicAvgOfNeighbourhoodSizes](type=double);

}

