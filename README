Make sure the files run.sh, genCSV1.py and plotgraph.py are in the same folder as sim_run file.
Add your reputation algorithm in tsys_lib folder, and execute the following commands
  make delete
  make all
This will add your algorithms to the tool.
Add your algo name in the array in run.sh script 

Requirements
  pip install matplotlib
  pip install pandas
  pip install numpy

The default number of users(Total_users) is 100. However it can be modified in run.sh file.
The parameteres to run run.sh are
  ./run.sh user_behaviour step_size pre_trust_users

  ./run.sh -usr:disguise 10 5
The above command sets no. of pre trust users as 5 and run for disguise users 10,20,30,..... for the algorithms given in the array in run.sh  script.
  ./run.sh -usr:disguise 20 5 will run for disguise users 20,40,....
After running the command , all the intermediate files are stored in a folder(name given in the terminal). The folder contains a consolidated csv file, graph and other files. 



The tool supports the following behaviours of users
./run.sh -usr:purely 20 5
./run.sh -usr:disguise 20 5
./run.sh -usr:sybil 20 5
./run.sh -usr:provider 20 5
./run.sh -usr:feedback 20 5

To know about the Reputation tool see the link at 


