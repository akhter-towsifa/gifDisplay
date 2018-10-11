import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

import sys, os
### cmsRun CSCEventDisplay.py plotdir="/afs/cern.ch/work/t/tahuang/CSCEmulation/CMSSW_10_2_1/src/displayplots/"
options = VarParsing ('analysis')
options.register('plotdir', '', mytype=VarParsing.varType.string)
options.parseArguments()
from Configuration.StandardSequences.Eras import eras
process = cms.Process("GifDisplay", eras.Run2_2018)

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
#process.load("Configuration/Geometry/GeometryIdeal2015Reco_cff")
#process.load("Configuration/Geometry/IdealGeometry_cff")
#process.load("Configuration/StandardSequences/Geometry_cff")
process.load("Configuration/StandardSequences/MagneticField_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration/StandardSequences/RawToDigi_Data_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("RecoMuon.MuonSeedGenerator.standAloneMuonSeeds_cff")
#process.load("RecoMuon.GlobalMuonProducer.globalMuons_cff")

#process.GlobalTag.globaltag = '74X_dataRun2_Prompt_v0'
#process.GlobalTag.globaltag = '92X_dataRun2_Prompt_v11'
process.GlobalTag.globaltag = '102X_dataRun2_Prompt_v1'

process.options = cms.untracked.PSet(
	SkipEvent = cms.untracked.vstring('LogicError','ProductNotFound')
)


process.source = cms.Source("PoolSource",
#  fileNames = cms.untracked.vstring('file:me11_test27_oct23.root')
#  fileNames = cms.untracked.vstring('file:../../../CMSSW_9_2_13/src/../../inputRoot/0026F566-83BB-E711-B677-7845C4FC3683.root')
  eventsToProcess = cms.untracked.VEventRange(),
  fileNames = cms.untracked.vstring('file:../../../inputRoot/Zmu_rawreco_2016H.root')
#  eventsToProcess = cms.untracked.VEventRange(pickEvent + '-' + pickEvent)

)

process.maxEvents = cms.untracked.PSet(
     input = cms.untracked.int32(-1)
)




## helper for files on dCache/EOS (LPC)
def useInputDir(process, inputDir, onEOS = True):
    theInputFiles = []
    for d in range(len(inputDir)):
        my_dir = inputDir[d]
        if not os.path.isdir(my_dir):
            print "ERROR: This is not a valid directory: ", my_dir
            if d==len(inputDir)-1:
                print "ERROR: No input files were selected"
                exit()
            continue
        print "Proceed to next directory"
        ls = os.listdir(my_dir)
        if onEOS:
            theInputFiles.extend(['file:' + my_dir[:] + x for x in ls if x.endswith('root')])
        else:
            ## this works only if you pass the location on pnfs - FIXME for files staring with store/user/...                                                            
            theInputFiles.extend([my_dir[16:] + x for x in ls if x.endswith('root')])

    process.source.fileNames = cms.untracked.vstring(*theInputFiles)
    return process


inputdirs = ["/eos/cms/store/data/Run2018D/SingleMuon/RAW/v1/000/323/524/00000/"]
useInputDir(process, inputdirs)

#print "==============================================="
#print "input files: "
#print process.source.fileNames
#print "==============================================="


file_event_to_process = "/afs/cern.ch/work/t/tahuang/CSCEmulation/CMSSW_10_2_1/src/ToInvestigate2.txt"
eventlist_display = "eventList.txt"
eventlist_w = open(eventlist_display, 'w')

totEvents = 0
with open(file_event_to_process) as fevents:
   for line in fevents:
       runnumber = int(line.split()[0])
       eventnumber = int(line.split()[1])
       process.source.eventsToProcess.append('%d:%d-%d:%d'%(runnumber, eventnumber, runnumber, eventnumber))
       totEvents = totEvents+1
       eventlist_w.write("%d 1 1 1 9\n"%eventnumber)
       
       #print "run ",runnumber, "eventnumber ",eventnumber

eventlist_w.close()
process.maxEvents.input = totEvents



#process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
##scram b -j8 USER_CXXFLAGS="-DEDM_ML_DEBUG"
process.MessageLogger = cms.Service("MessageLogger",
    destinations = cms.untracked.vstring("displaydebug"),
    displaydebug = cms.untracked.PSet(
        extension = cms.untracked.string(".txt"),
        threshold = cms.untracked.string("DEBUG"),
        lineLength = cms.untracked.int32(132),
        noLineBreaks = cms.untracked.bool(True)
    ),
    # debugModules = cms.untracked.vstring("*")
    debugModules = cms.untracked.vstring("cscTriggerPrimitiveDigis")
)



# CSC Trigger Primitives emulator
# ===============================
process.load("L1Trigger.CSCTriggerPrimitives.cscTriggerPrimitiveDigis_cfi")
process.cscTriggerPrimitiveDigis.alctParam07.verbosity = 0
process.cscTriggerPrimitiveDigis.clctParam07.verbosity = 2
process.cscTriggerPrimitiveDigis.tmbParam.verbosity = 2
process.cscTriggerPrimitiveDigis.CSCComparatorDigiProducer = "muonCSCDigis:MuonCSCComparatorDigi"
process.cscTriggerPrimitiveDigis.CSCWireDigiProducer = "muonCSCDigis:MuonCSCWireDigi"
process.cscTriggerPrimitiveDigis.commonParam.isSLHC = cms.bool(True)
process.cscTriggerPrimitiveDigis.commonParam.smartME1aME1b = cms.bool(False)
process.cscTriggerPrimitiveDigis.alctSLHC.verbosity = 0
process.cscTriggerPrimitiveDigis.clctSLHC.verbosity = 2
process.cscTriggerPrimitiveDigis.clctSLHC.clctPidThreshPretrig = 2
process.cscTriggerPrimitiveDigis.clctSLHC.clctPretriggerTriggerZone = 224
process.cscTriggerPrimitiveDigis.clctSLHC.clctStateMachineZone = 4
process.cscTriggerPrimitiveDigis.clctSLHC.useDynamicStateMachineZone = False
process.cscTriggerPrimitiveDigis.tmbSLHC.verbosity = 2
process.cscTriggerPrimitiveDigis.tmbSLHC.matchTrigWindowSize = 7
print process.cscTriggerPrimitiveDigis.commonParam

# CSC Trigger Primitives reader


process.GifDisplay = cms.EDAnalyzer('GifDisplay',
#rootFileName = cms.untracked.string("output_me11_test27_oct30.root"),
rootFileName = cms.untracked.string("output.root"),

stripDigiTagSrc = cms.untracked.InputTag("muonCSCDigis","MuonCSCStripDigi"),
wireDigiTagSrc = cms.untracked.InputTag("muonCSCDigis","MuonCSCWireDigi"),
compDigiTagSrc = cms.untracked.InputTag("muonCSCDigis", "MuonCSCComparatorDigi"),
#cscRecHitTag = cms.InputTag("csc2DRecHits",""),
#alctDigiTag = cms.InputTag('muonCSCDigis', 'MuonCSCALCTDigi'),
alctDigiTagSrc = cms.untracked.InputTag('muonCSCDigis', 'MuonCSCALCTDigi'),
alctDigiTagSrc_Emul = cms.untracked.InputTag('cscTriggerPrimitiveDigis'),
clctDigiTagSrc = cms.untracked.InputTag('muonCSCDigis', 'MuonCSCCLCTDigi'),
clctDigiTagSrc_Emul = cms.untracked.InputTag('cscTriggerPrimitiveDigis'),
#corrlctDigiTag = cms.InputTag('muonCSCDigis', 'MuonCSCCorrelatedLCTDigi'),
corrlctDigiTagSrc = cms.untracked.InputTag('muonCSCDigis', 'MuonCSCCorrelatedLCTDigi'),
corrlctDigiTagSrc_Emul = cms.untracked.InputTag('cscTriggerPrimitiveDigis'),

addEmulation = cms.untracked.bool(True),
debug = cms.untracked.bool(False),
#directory for eventdisplay
eventDisplayDir = cms.untracked.string(options.plotdir),
#eventDisplayDir = cms.untracked.string("/home/mhl/public_html/2017/20171201_cscSeg/"),
#chamber type: ME1/1-11, ME2/1-21
chamberType = cms.untracked.string('11')
)


process.p = cms.Path(process.muonCSCDigis * process.cscTriggerPrimitiveDigis * process.GifDisplay)
