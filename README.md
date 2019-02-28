# MobilityModelCheck

A simple OMNeT++ model to evaluate INET based mobility models. It is used to configure and run existing or new mobility models in the INET framework to determine performance of those models.


## Procedure
The list given below provides the procedure on how to install, compile and run INET mobility models.


1. Install and build OMNeT++ (version 5.4.1)

2. Run the OMNet++ IDE and create a new workspace

3. Install and build INET (version 4.0.0) in the newly created workspace using option - `Help -> Install Simulation Models...` or another means (e.g., at workspace creation, using a downloaded archive, etc.)

4. Install the Github repository [MobilityModelCheck](https://github.com/ComNets-Bremen/MobilityModelCheck.git) using `File -> Import... -> Git -> Project from Git ->  Clone URI` and giving the repository path

5. Tick INET as a referenced project in the properties of the MobilityModelCheck project (`Properties -> Project References`)

5. Build the MobilityModelCheck project using - `Project -> Build Project` (should not have any errors or warnings after building)

6. Modify the `omnetpp.ini` to suit your requirements (e.g., mobility model, number of nodes, etc.)

7. Select the MobilityModelCheck folder (the top most folder of the OPSLite project) and run using - `Run -> Run As -> OMNeT++ Simulation`

8. Use the generated log to compute statistics - a separater parser has to be written to extract whatever statistics required (such as number of contacts, contact durations, etc.)


## Questions or Comments

If you have any comments or suggestions, we will be very glad to hear them. Please write to us using any of the e-mail adresses below.

  - Asanga Udugama (adu@comnets.uni-bremen.de)
  - Anna Förster (anna.foerster@comnets.uni-bremen.de)
  - Vishnupriya Parimalam (vp@fb1.uni-bremen.de)
  - Jens Dede (jd@comnets.uni-bremen.de)

