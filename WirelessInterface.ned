//
// The model that 
//
// @author : Asanga Udugama (adu@comnets.uni-bremen.de)
// @date   : 02-may-2017
//
//

simple WirelessInterface
{
    parameters:
		double wirelessRange @unit(m) = default(30m);
		
		@signal[contactMade](type=long);
        @statistic[contactMade](source=contactMade;record=count,vector,histogram);
		@signal[contactDuration](type=double);
        @statistic[contactDuration](source=contactDuration;record=timeavg,stats,vector,histogram);
		@signal[neighbourhoodSize](type=unsigned long);
        @statistic[neighbourhoodSize](source=neighbourhoodSize;record=timeavg,stats,vector,histogram);
		
}
