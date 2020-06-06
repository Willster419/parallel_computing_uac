#!/bin/bash

#http://talby.rcs.manchester.ac.uk/~rcs/_linux_and_hpc_lib/sge_intro.html
#https://www.hoffman2.idre.ucla.edu/computing/sge-commands/
#man qsub

#
# -- SGE options :
#

# Run the script using the BASH shell
#$ -S /bin/bash

# Run the job in the same directory as you submitted
#$ -cwd

# The name of the job. The name should follow the "name" definition in sge_types(1).  Invalid job names will be denied at submit time.
#$ -N reduce

# The path used for the standard output stream of the job.
#$ -o reduce.out.$JOB_ID

# Defines or redefines the path used for the standard error stream of the job.
#$ -e reduce.err.$JOB_ID

# Parallel programming environment (PE) to instantiate.
#$ -pe orte 8

#
# -- the commands to be executed (programs to be run) :
#

mpirun -np 8 ./reduce
