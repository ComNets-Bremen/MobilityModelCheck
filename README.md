# MobilityModelCheck

A simple set of OMNeT++ models to evaluate INET based mobility models. They are used to configure and run existing or new mobility models in the INET framework to determine the performance of those mobility models in terms of contacts made, contact durations, etc. The models use unit disc graph (UDG) mechanism to determine the contacts between nodes (i.e., wireless range).


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

8. Use the generated statistics and log (in `results` folder) to compute statistics - a separater parser maybe required to parse the log file to extract required stats (such as number of contacts, contact durations, etc.)



## Statistics Generated

The models generate the following statistics using OMNeT++ statistics mechanism.

1. Contacts Made - The number of contacts made  by every node.

2. Contact Durations - The duration of a contact after the contact ends, of every node.  

3. Neighbourhood Sizes - The number of neighbours in wireless range of every node, every second.



## Log Entries

If the simulations are run in the `Cmdenv` mode (not the `Qtenv` mode), a log is generated. The generated log contains the following information. These can be parsed to obtain statistics.

1. Start of a contact - `xxxx says: Contact with yyyy started at nnnn seconds`
   - xxxx - node name
   - yyyy - contacted node name
   - nnnn - seconds

2. End of a contact - `xxxx says: Contact with yyyy ended at nnnn seconds - Contact duration was dddd seconds`
   - xxxx - node name
   - yyyy - contacted node name
   - nnnn - seconds
   - dddd - seconds

3. The tags ANS (accumulated neighbourhood size) and TNRT (total neighbourhood reporting times) - `ssss xxxx ANS pppp TNRT rrrr`
   - ssss - simulation time
   - xxxx - node name
   - pppp - accumulated neighbourhood size
   - rrrr - total neighbourhood reporting times

4. The tags ACD (accumulated contact durations) and TNC (total number of contacts up to now) - `ssss xxxx ACD bbbb TNC cccc`
   - ssss - simulation time
   - xxxx - node name
   - bbbb - accumulated contact durations
   - cccc - total number of contacts up to now



## Questions or Comments

If you have any comments or suggestions, we will be very glad to hear them. Please write to us using any of the e-mail adresses below.

  - Asanga Udugama (adu@comnets.uni-bremen.de)
  - Anna Förster (anna.foerster@comnets.uni-bremen.de)
  - Vishnupriya Parimalam (vp@fb1.uni-bremen.de)
  - Jens Dede (jd@comnets.uni-bremen.de)

