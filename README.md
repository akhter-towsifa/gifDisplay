# gifDisplay

original package:
https://github.com/mhl0116/gifDisplay


put this package under CMSSW_X_Y_Z/src

then cmsenv and compile 
CSCEventDisplay.py includes CSC unpacker + CSC local trigger emulation + event display
cmsRun CSCEventDisplay.py to produce event displays

1, in CSCEventDisplay.py provide input using "process.source"
  input rootfiles must have RAW data to be unpacked, using edmDumpEventContent one should 
  see event has "FEDRawDataCollection" type
 
2, save event and chamber id for which you want make eventdisplay for in eventList.txt 
   FORMAT: eventNumber endcapID stationID ringID chamberID (note: use ringID=1 for both ME11a and ME11b)


email hualin.mei@cern.ch if you have any suggestions or questions
