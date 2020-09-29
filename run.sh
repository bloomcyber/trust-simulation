set -e
[ -d tests ] || mkdir tests
# algList=('zheyang' 'block' 'none' 'eigen' 'tnasl' )       # or    algList=('eigen' 'none' 'etinc' 'tnasl')
algList=('smart' 'none' 'zheyang' )
usr=100
pt=$3
echo pretrust $3
file=`cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 3 | head -n 1`
folder=`cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 3 | head -n 1`
eu=0 #non-trusted users
if [ "$1" = "-usr:pre_trusted" ];then
	eu=$usr
else
	eu=$((usr-pt))
fi
echo eu is $eu
step=$2
for ((i = 0 ; i <= $eu ; i=$i+$step)); do
		fileout=$file$i".trace"
	./gen_trace -users $usr -output $fileout -usr:pre_trusted $pt $1 $i
	echo $i
	for j in "${algList[@]}"; do
		echo $i
		./sim_run -input $fileout -tm $j -strategy isolated
	done
done
#-band:max_conn -band:period -mode:smartgen -mode:warmup
i=$((i-step))
echo COPYING.....
t=$file*
mkdir tests/$folder
echo tests/$folder folder created 
echo file names start with $file 
mv $t tests/$folder/
cp *.py tests/$folder/
cd tests/$folder
echo RunningPYTHON
name=()
for j in "${algList[@]}"; do
	if [ $j = 'zheyang' ];then
		j='zheya'
	fi
	python3 genCSV.py $j $file $step $i $1
	name+=($j".csv")
done
name+=($1)
python3 plotgraph.py ${name[@]}
echo Raw data stored in tests/$folder folder
