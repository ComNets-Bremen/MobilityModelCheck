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

    submodules:

         // wifi adhoc interface
        wirelessIfc: WirelessInterface;

        // mobility
        mobility: <mobilityType> like IMobility;
}