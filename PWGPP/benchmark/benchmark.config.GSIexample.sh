#
# Example config file for GSI batch farm
# Last test done at GSI batch farm  master git describe =vAN-20141205-13-g9760344
# To modify example setup for your needs  grep string "TO BE CHANGED"  
# Most probably these will be only changes which you will have to do to run CPASS0/CPASS1/QA benchmark on GSI batch farm
# similar example files should be done for other farms


## default OCDB, if autoOCDB is set put in any 4 digit year starting with 20
## by default the OCDB year set automatically for each chunk
## based on the path
## to disable set autoOCDB=0
#
#autoOCDB=0
# TO BE CHANGED:
#defaultOCDB="local:///cvmfs/alice-ocdb.cern.ch/calibration/data/2010/OCDB/"
defaultOCDB="local:///cvmfs/alice.gsi.de/alice/data/2013/OCDB/"

## force the run number (disables automatic guessing from chunk path)
#runNumber=167123

## makeflow options
#makeflowPath="/hera/alice/aux/cctools/bin"
#makeflowOptions="-T wq -N alice -d all -C ali-copilot.cern.ch:9097"
#makeflowOptions="-T wq -N alice -C ali-copilot.cern.ch:9097"
makeflowOptions="-T condor"

## TO BE CHANGED: batch system options
batchCommand="/usr/bin/qsub"
#batchFlags="-b y -cwd -l h_rt=24:0:0,h_rss=4G -P alice"    # should be working at GSI - central batch farm
batchFlags="-b y -cwd -l h_rt=24:0:0,h_rss=4G "    # should be working at GSI - lxb1001

## TO BE CHANGED: Directory to store output, productionID from command line will be appended
#
baseOutputDirectory="/hera/alice/miranov/alice-tpc-notes/reconstruction/distortionFit/data/benchmark/submit/"
#
#TO BE CHANGED: init aliroot
#must be a script which executed a command in a modified environment
#e.g. alienv aliroot somemacro.C
#
#alirootEnv="/cvmfs/alice.cern.ch/bin/alienv setenv AliRoot/$ALIROOT_VERSION -c"
alirootEnv="/u/miranov/.baliceTPC"

#for running with old releases use a more recent aliroot that contains all the machinery
#if set, will only be used at the MakeSummary stage
#alirootEnvQA="/cvmfs/alice.cern.ch/bin/alienv setenv AliRoot/$ALIROOT_VERSION -c"

#run QA with a known good version of the QA script
#trustedQAtrainMacro='/hera/alice/mkrzewic/gsisvn/Calibration/QAtrain_duo.C'

## if set to 1, run in whatever mktemp -d aasfa provides,
## if set to 2, run in the current dir (as provided by the batch system) or subdir of that
## then copy results to final place
#
reconstructInTemporaryDir=0

## trigger mask sent to the reconstruction
## if you want to send an empty string use "\"\""
## usually, for filtered data use empty, 
## for unfiltered chunks use kCalibBarrel
#
#recoTriggerOptions="?Trigger=kCalibBarrel"
#
recoTriggerOptions="\"\""

## merging is started when this percentage of input files is reconstructed
#  only relevant for batch systems
#
percentProcessedFilesToContinue=100
maxSecondsToWait=$(( 3600*24 ))

## maximal number of events to process (per chunk, -1 means no limit)
#
nEvents=100

## max no of chunks per run(0 means no limit)
#
nMaxChunks=0

## run these command(s) after the runnig dir has been set up, use to e.g.
#
postSetUpActionCPass0=""
postSetUpActionCPass1=""

## detailed setting what to run
## CPass0
#
         runCPass0reco=1
runCPass0MergeMakeOCDB=1
## CPass1
#
         runCPass1reco=1
runCPass1MergeMakeOCDB=1

## filtering
       runESDfiltering=1
filteringFactorHighPt=1e2
filteringFactorV0s=1e1

## who to email upon completion
#
MAILTO=""

## uncomment to just run the logic, dont check for data and dont process it - 
## fake the output files (for debugging)
#
#pretend=1

##dump all output to stdout instead of a log for debugging
#
#dontRedirectStdOutToLog=1

## uncomment this option to force streaming the logs to the final destination instead of the running directory
## this way a log is always available even in case the batch system kills the job
#
logToFinalDestination=1

#set the downscaling factors during the filtering fro expert QA (overrides the previous values)
#AliAnalysisTaskFilteredTree_fLowPtTrackDownscaligF="1e-2"
#AliAnalysisTaskFilteredTree_fLowPtV0DownscaligF="1e-2"

#this forces root to produce a coredump where it normally would just crash (floting point exception)
ALIROOT_FORCE_COREDUMP=1

#run one job per run with valgrind...
#profilingCommand="valgrind --tool=callgrind --num-callers=40 -v --trace-children=yes"
#nEventsProfiling=5

#copy input data to current dir instead of linking
#copyInputData=0
