# MobilityModelCheck

A simple set of OMNeT++ models to evaluate INET based mobility models. They are used to configure and run existing or new mobility models in the INET framework to determine the performance of those mobility models in terms of contacts made, contact durations, etc. The models use unit disc graphs (UDG) to determine the contacts between nodes assuming that they are connected using a peer-to-peer wireless communication technology such as WiFi Direct, Wireless Adhoc or Bluetooth. The parameter `wirelessRange` determines the range of the wireless communication technology.


## Procedure
The list given below provides the procedure on how to install, compile and run INET mobility models using MobilityModelCheck.


1. Install and build OMNeT++ (version 5.4.1)

2. Run the OMNet++ IDE and create a new workspace

3. Install and build INET (version 4.0.0) in the newly created workspace using option - `Help -> Install Simulation Models...` or another means (e.g., at workspace creation, using a downloaded archive, etc.)

4. Install the Github repository [MobilityModelCheck](https://github.com/ComNets-Bremen/MobilityModelCheck.git) using `File -> Import... -> Git -> Project from Git ->  Clone URI` and giving the repository path

5. Tick INET as a referenced project in the properties of the MobilityModelCheck project (`Properties -> Project References`)

5. Build the MobilityModelCheck project using - `Project -> Build Project` (should not have any errors or warnings after building)

6. Modify the `omnetpp.ini` to suit your requirements (e.g., mobility model, number of nodes, etc.)

7. Select the MobilityModelCheck folder (the top most folder of the OPSLite project) and run using - `Run -> Run As -> OMNeT++ Simulation`

8. Check the generated statistics and the node paths file



## Statistics Generated

The models generate the following statistics using OMNeT++ statistics mechanism at node-level and network-level.

1. Contacts Made - The number of contacts made  by every node.

2. Contact Durations - The duration of a contact after the contact ends, of every node.  

3. Neighbourhood Sizes - The number of neighbours in wireless range of every node, every second.

There are 2 categories of the above 2 statistics. Immediate statistics and Periodic statistics

- Immediate statistics are the statistics that are generated on every change of the monitored variable
- Periodic statistics are the statistics that are generated periodically where the interval is configured using `statReportingInterval` parameter

An important point to remember is that, though the 2 categories present the same variables, the statistic values of each category vary due to the way the statistics are computed. 



## Node Paths

If `nodePathRecorded` and `nodePathFileName` are configured, the silumation will log the x and y coordinates of each node to a text file in a CSV format.



## Questions or Comments

If you have any comments or suggestions, we will be very glad to hear them. Please write to us using the e-mail adresses ops@comnets.uni-bremen.de.


