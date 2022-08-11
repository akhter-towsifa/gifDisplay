# gifDisplay



This packge is used to display CSC hits and CSC local track for CMS events from simulation or data

## Setup
```
cmsrel CMSSW_12_5_0_pre2
cd CMSSW_12_5_0_pre2/src
cmsenv
git clone https://github.com/tahuang1991/gifDisplay.git
scram b -j 9
```
## How to use CSC event display package 


 1. in CSCEventDisplay.py uses "process.source" to get input files.
  By default input rootfiles must have RAW data to be unpacked, using edmDumpEventContent one should 
  see event has "FEDRawDataCollection" type. Configure the process you need.
 
 1. CSCEventDisplay.py needs to read in the run range and event range for each display case.
 
 1. save event and chamber id for which you want make eventdisplay for in eventList.txt 
   FORMAT: runNumber eventNumber endcapID stationID ringID chamberID (note: use ringID=1 for both ME11a and ME11b)
## Examples to run CSC display

>```
>runDisplay.sh
>```
Make sure that sample path and plot directory are replaced with yours
## Reference
original package:
https://github.com/mhl0116/gifDisplay

email hualin.mei@cern.ch if you have any suggestions or questions
