This code repository is useful to reproduce the results given in the paper titled **"Decentralized Device Authentication Model using the Trust Score and Blockchain Technology for Dynamic Networks"**.

We used the [QTM: P2P Trust Simulator](https://rtg.cis.upenn.edu/qtm/p2psim.php3) tool for simulating the trust.The simulated reputation algorithms in the paper are stored in tsys_lib folder.The file [tsys_smart.c](tsys_lib/tsys_smart.c) represents our algorithm, [tsys_zheyang.c](tsys_lib/tsys_zheyang.c) for zheyang and [tsys_none.c](tsys_lib/tsys_none.c) for no reputation.To compare other trust algorithms like eigen, tnasl in the results, add eigen and tnasl to the array **alglist** in the script [run.sh](run.sh).   

Make sure the files run.sh, genCSV.py and plotgraph.py are in the same folder as sim_run file.The default number of users(Total_users) is 100. However it can be modified in run.sh file.  

Execute the following commands in the root folder  
```
  pip install matplotlib pandas numpy
  make delete  
  make all  
  chmod +x run.sh
  ./run.sh -usr:purely 10 5         #./run.sh user_behaviour step_size pre_trust_users  
  ./run.sh -usr:disguise 10 5          
  ./run.sh -usr:sybil 10 5  
```
Above commands will give the results. All the intermediate files and the results are automatically stored in the test folder.
The results include  
1. a graph  
2. csv file for each trust algorithm given  
3. csv file consolidated for all the given trust algorithms  
 
 
 
 ## Additional
 You can also try  the following   
 ```
./run.sh -usr:provider 20 5         # With pretrust users=5 and users of type -usr:provider=20,40,60,...,100         
./run.sh -usr:feedback 30 10        # With pretrust users=10 and users of type -usr:provider=30,60,90,...,100         
 ```
To know about the parameters used in the script see [P2P-SIM README ](https://rtg.cis.upenn.edu/qtm/doc/p2p_readme.txt)  
 
