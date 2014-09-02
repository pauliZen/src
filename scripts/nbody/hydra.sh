echo 'Script_Name Number_of_steps nodes ppn threads tcrit'
read subname nsteps nnum ppn threads tlimit
echo "Please add commander in the script file at the end"

echo "# @ shell=/bin/bash
#
# Sample script for LoadLeveler
#
# @ error = job.err.\$(jobid).\$(stepid)
# @ output = job.out.\$(jobid).\$(stepid)
# @ job_type = parallel
# @ requirements = (Feature==\"gpu\")
# @ node_usage= not_shared
#" > $subname

for ((i=1;i<=nsteps;i=i+1))
do
echo "# @ step_name = rs"$i >>$subname
[ $i != 1 ] && echo "# @ dependency = (rs"`expr $i - 1`" >= 0)" >>$subname
echo "# @ node = "$nnum >>$subname
echo "# @ tasks_per_node = "$ppn >>$subname
echo "# @ resources = ConsumableCpus("$threads")" >>$subname
echo "# @ network.MPI = sn_all,not_shared,us"  >>$subname
echo "# @ wall_clock_limit = "$tlimit  >>$subname
echo "# @ notification = complete
# @ notify_user = \$(user)@rzg.mpg.de
# @ queue
#" >>$subname
done

echo "export OMP_NUM_THREADS="$threads >>$subname
echo "export CUDA_PATH=\${CUDA_HOME}
module load cuda" >>$subname

dir=`pwd -P`

echo "cd "$dir >>$subname

echo "mkdir rs\$LOADL_STEP_ID
cp rs fort.1 rs\$LOADL_STEP_ID
ln -sf rs\$LOADL_STEP_ID/fort.2 fort.1
cd rs\$LOADL_STEP_ID

# run the program" >>$subname

echo "poe" >>$subname
