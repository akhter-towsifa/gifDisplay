# gifDisplay

original package:
https://github.com/mhl0116/gifDisplay


put this package under CMSSW_12_5_Z/src


 1. in CSCEventDisplay.py uses "process.source" to get input files.
  By default input rootfiles must have RAW data to be unpacked, using edmDumpEventContent one should 
  see event has "FEDRawDataCollection" type. Configure the process you need.
 
 1. CSCEventDisplay.py needs to read in the run range and event range for each display case.
 
 1. save event and chamber id for which you want make eventdisplay for in eventList.txt 
   FORMAT: runNumber eventNumber endcapID stationID ringID chamberID (note: use ringID=1 for both ME11a and ME11b)


email hualin.mei@cern.ch if you have any suggestions or questions
