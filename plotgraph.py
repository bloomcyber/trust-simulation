#Reads multiple csv files(with same no. of columns) given as arguments
#And computes effectiveness metric then plots the graph
#eg: python plotgraph.py (pre_5)eigen.csv (pre_5)none.csv (pre_5)etinc.csv (pre_5)tnasl.csv

import matplotlib.pyplot as plt
import pandas as pd
#import numpy as np
import sys

# first_arg = sys.argv[1]
# second_arg = sys.argv[2]

d={}
j=1
k={}
a=[]
b=len(sys.argv)-1
s='no. of '+str(sys.argv[b])
for i in range(1,b):
    d[i]= pd.read_csv(str(sys.argv[i]),header=None)
    if(j==1):
    	k[s]=d[i].loc[0]
    	print(k[s])
    	j=j+1	
    a=d[i].loc[2]/d[i].loc[1]
    plt.plot(d[i].loc[0],a,label=str(sys.argv[i]))
    k[str(sys.argv[i])]=a
    #write to csv file consolidated
df1=pd.DataFrame(k)
df1_tr=df1.transpose()
df1_tr.to_csv(sys.argv[i+1]+'.csv')
plt.xlabel(sys.argv[i+1])
plt.ylabel('Evaluation Metrics')
plt.legend()
plt.savefig(sys.argv[i+1]+'.png')
plt.show()
print('graphData stored in '+sys.argv[i+1]+'.csv')