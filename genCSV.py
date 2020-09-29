from subprocess import check_output
import pandas as pd
import sys
def get_one_line(filepath, line_number):
    return check_output([
		"sed",
		"-n",
		"%sp" % line_number,
		filepath
	])
def getdata(filename,readfor):
    arr=[0,1,2,3]
    if(readfor=='-usr:pre_trusted'):
    	arr[0]=int(get_one_line(filename,10).decode("utf-8")[25:-1])
    elif readfor=='-usr:purely':
    	arr[0]=int(get_one_line(filename,12).decode("utf-8")[25:-1])
    elif readfor=='-usr:feedback':
    	arr[0]=int(get_one_line(filename,13).decode("utf-8")[25:-1])
    elif readfor=='-usr:provider':
    	arr[0]=int(get_one_line(filename,14).decode("utf-8")[25:-1])
    elif readfor=='-usr:disguise':
    	arr[0]=int(get_one_line(filename,15).decode("utf-8")[25:-1])
    elif readfor=='-usr:sybil':
    	arr[0]=int(get_one_line(filename,16).decode("utf-8")[25:-1])
    else:
    	print('invalid first argument to scipt file')
    	exit()
    #arr[0]=ar1
    #print(arr[0])

    arr[1]=int(get_one_line(filename,47).decode("utf-8")[25:-1])
    #arr[1]=ar1
    #print(arr[1])

    arr[2]=int(get_one_line(filename,48).decode("utf-8")[25:-1])
    #arr+=ar1
    #print(arr[2])
    arr[3]=int(get_one_line(filename,49).decode("utf-8")[25:-1])
    #arr+=ar1
    #print(arr[3])
    #print(type(arr[0]))
    return arr
algo = sys.argv[1]   #For naming convenience algo name
file= sys.argv[2]    #file name       
step=int(sys.argv[3])
i=int(sys.argv[4])    #upper limit
readfor=sys.argv[5]

arr={}
for i in range(0,i+1,step):
    s=file+str(i)+"."+algo
    arr[i]=getdata(s,readfor)
    df = pd.DataFrame(arr)
print(df)
t=algo+".csv"
df.to_csv(t, mode='w',index= False, header=False)
print('saved to ',t)
