#!/bin/bash

if [[ $# -ne 5 ]]
then
  echo "Error - parameters missing"
  echo "Syntax: $0 rtems_dir1 simics_workspace1 rtems_dir2 simics_workspace2 results_tag"
  echo "Example: $0 ${HOME}/work/rtems/rtems-sched/rtems ${HOME}/work/simics/gems/gems-2.1.1-gedare/simics ${HOME}/work/rtems/rtems-sched/rtems-hwds ${HOME}/work/simics/gems/gems-2.1.1-hwds/simics baseline"
  exit 1
fi

# Check that $1 is a valid rtems source directory
if [[ ! -d $1/cpukit || ! -d $1/c ]]
then
  echo "$1 is not a valid rtems source-code directory"
  exit 1
fi

# Check that $2 is a prepared simics workspace
if [[ ! -f $2/opal-quicktest.sh ]]
then
  echo "$2 is not a proper simics workspace"
  exit 1
fi

# Check that $3 is a valid rtems source directory
if [[ ! -d $3/cpukit || ! -d $3/c ]]
then
  echo "$3 is not a valid rtems source-code directory"
  exit 1
fi

# Check that $4 is a prepared simics workspace
if [[ ! -f $4/opal-quicktest.sh ]]
then
  echo "$4 is not a proper simics workspace"
  exit 1
fi
PWD=`pwd`
count=0
RTEMS_DIR1=$1
SIMICS_WKSP1=$2
RTEMS_DIR2=$3
SIMICS_WKSP2=$4
RESULTS_TAG=${5}_`date +%Y%m%d%H%M`

## prepare the pre-build (configure) environment.
## this makes for faster re-building later.
${SIMICS_WKSP1}/build-sparc64/build-b-usiiicvs.sh
${SIMICS_WKSP2}/build-sparc64/build-b-usiiicvs.sh
mkdir ${SIMICS_WKSP1}/results
mkdir ${SIMICS_WKSP2}/results
mkdir ${SIMICS_WKSP1}/results/${RESULTS_TAG}
mkdir ${SIMICS_WKSP2}/results/${RESULTS_TAG}

## make this a loop
## get some parameters ...
distribution=1
for tasks in 80 60 40 20
do
  for utilization in 0.8 0.6 0.4 0.2
  do
    ## Generate tests
    for count in {1..50}
      do
      if [ $count -lt 10 ]; then
        spintest=spspin0${count}
      else
        spintest=spspin${count}
      fi
      spindir1=${RTEMS_DIR1}/testsuites/gabtests/${spintest}
      spindir2=${RTEMS_DIR2}/testsuites/gabtests/${spintest}
  
      if [[ ! -d ${spindir1} || ! -d ${spindir2} ]]
      then
        echo "Unable to find directory: ${spindir1} or ${spindir2}"
        exit 1
      fi
  
      python gen-params.py -t ${tasks} -d ${distribution} -u ${utilization}
  
      cp params.h ${spindir1}/params.h
      cp macros.h ${spindir1}/macros.h
      cp params.h ${spindir2}/params.h
      cp macros.h ${spindir2}/macros.h
      ## enforce RM (priority) scheduling first
      sed -i -e 's/#define CONFIGURE_SCHEDULER_EDF/\/\/#define CONFIGURE_SCHEDULER_EDF/' ${spindir1}/system.h
      sed -i -e 's/#define CONFIGURE_SCHEDULER_EDF/\/\/#define CONFIGURE_SCHEDULER_EDF/' ${spindir2}/system.h
    done

    ## build and run tests
    ./runtests.sh ${SIMICS_WKSP1} ${RESULTS_TAG} ${tasks} ${utilization} ${distribution} "RM" ${PWD} &
    ./runtests.sh ${SIMICS_WKSP2} ${RESULTS_TAG} ${tasks} ${utilization} ${distribution} "RM" ${PWD} &
    wait

    ## Now do the EDF scheduler
    for count in {1..50}
      do
      if [ $count -lt 10 ]; then
        spintest=spspin0${count}
      else
        spintest=spspin${count}
      fi
      spindir1=${RTEMS_DIR1}/testsuites/gabtests/${spintest}
      spindir2=${RTEMS_DIR2}/testsuites/gabtests/${spintest}

      sed -i -e 's/\/\/#define CONFIGURE_SCHEDULER_EDF/#define CONFIGURE_SCHEDULER_EDF/' ${spindir1}/system.h
      sed -i -e 's/\/\/#define CONFIGURE_SCHEDULER_EDF/#define CONFIGURE_SCHEDULER_EDF/' ${spindir2}/system.h
    done

    ## build and run tests
    ./runtests.sh ${SIMICS_WKSP1} ${RESULTS_TAG} ${tasks} ${utilization} ${distribution} "EDF" ${PWD} &
    ./runtests.sh ${SIMICS_WKSP2} ${RESULTS_TAG} ${tasks} ${utilization} ${distribution} "EDF" ${PWD} &
    wait
  done
done

