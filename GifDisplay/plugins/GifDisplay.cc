//# -*- C++ -*-
// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"



#include <Geometry/CSCGeometry/interface/CSCGeometry.h> 
#include <Geometry/Records/interface/MuonGeometryRecord.h> 
#include <RecoMuon/Records/interface/MuonRecoGeometryRecord.h> 
#include "DataFormats/CSCRecHit/interface/CSCRecHit2D.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "CondFormats/AlignmentRecord/interface/GlobalPositionRcd.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include <DataFormats/GeometrySurface/interface/LocalError.h> 
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include <DataFormats/Provenance/interface/EventID.h> 


#include "DataFormats/CSCDigi/interface/CSCWireDigi.h"
 #include "DataFormats/CSCDigi/interface/CSCWireDigiCollection.h"
 #include "DataFormats/CSCDigi/interface/CSCStripDigi.h"
 #include "DataFormats/CSCDigi/interface/CSCStripDigiCollection.h"
 #include "DataFormats/CSCDigi/interface/CSCComparatorDigi.h"
 #include "DataFormats/CSCDigi/interface/CSCComparatorDigiCollection.h"
 #include "DataFormats/CSCDigi/interface/CSCALCTDigi.h"
 #include "DataFormats/CSCDigi/interface/CSCALCTDigiCollection.h"
 #include "DataFormats/CSCDigi/interface/CSCCLCTDigi.h"
 #include "DataFormats/CSCDigi/interface/CSCCLCTDigiCollection.h"
 #include "DataFormats/CSCDigi/interface/CSCCorrelatedLCTDigi.h"
 #include "DataFormats/CSCDigi/interface/CSCCorrelatedLCTDigiCollection.h"

 
#include "DataFormats/MuonDetId/interface/CSCDetId.h"
#include <DataFormats/CSCRecHit/interface/CSCRecHit2D.h>
#include <DataFormats/CSCRecHit/interface/CSCSegmentCollection.h>
#include "DataFormats/MuonDetId/interface/RPCDetId.h"

#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutRecord.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutCollection.h"

#include "Geometry/CSCGeometry/interface/CSCGeometry.h"
#include "Geometry/CSCGeometry/interface/CSCChamber.h"
#include "Geometry/CSCGeometry/interface/CSCLayer.h"
#include "Geometry/CSCGeometry/interface/CSCLayerGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"
#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"

#include "DataFormats/CSCRecHit/interface/CSCRecHit2DCollection.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/GeometryVector/interface/LocalVector.h"
#include "DataFormats/CLHEP/interface/AlgebraicObjects.h"
#include "DataFormats/MuonDetId/interface/CSCIndexer.h"

#include "CondFormats/CSCObjects/interface/CSCDBGains.h"
#include "CondFormats/DataRecord/interface/CSCDBGainsRcd.h"
#include "CondFormats/CSCObjects/interface/CSCDBNoiseMatrix.h"
#include "CondFormats/DataRecord/interface/CSCDBNoiseMatrixRcd.h"
#include "CondFormats/CSCObjects/interface/CSCDBCrosstalk.h"
#include "CondFormats/DataRecord/interface/CSCDBCrosstalkRcd.h"
#include "CondFormats/CSCObjects/interface/CSCDBPedestals.h"
#include "CondFormats/DataRecord/interface/CSCDBPedestalsRcd.h"
#include "CondFormats/Alignment/interface/Alignments.h"

#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"

#include <TGClient.h>
#include <TRootEmbeddedCanvas.h>
#include "TCanvas.h"
#include "TPad.h"
#include "TStyle.h"

#include "TF1.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH1I.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TGraph.h"
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>

//#include "Gif.h"
#include "gifDisplay/GifDisplay/interface/display.h"
//##include "../interface/display.h"
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class GifDisplay : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit GifDisplay(const edm::ParameterSet&);
      ~GifDisplay();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      void fillALCT(edm::Handle<CSCALCTDigiCollection> digicollection, vector<CSCIDLCTs>& alct_container);
      void fillCLCT(edm::Handle<CSCCLCTDigiCollection> digicollection, vector<CSCIDLCTs>& clct_container);
      void fillCorrLCT(edm::Handle<CSCCorrelatedLCTDigiCollection> digicollection, vector<CSCIDLCTs>& lct_container);
// ----------member data ---------------------------
//edm::InputTag stripDigiTag;
//edm::InputTag wireDigiTag;
//edm::InputTag comparatorDigiTag;
  edm::EDGetTokenT<CSCWireDigiCollection> wireDigiTagSrc;
  edm::EDGetTokenT<CSCStripDigiCollection> stripDigiTagSrc;
  edm::EDGetTokenT<CSCComparatorDigiCollection> compDigiTagSrc;
  edm::EDGetTokenT<CSCALCTDigiCollection> alctDigiTagSrc;
  edm::EDGetTokenT<CSCCLCTDigiCollection> clctDigiTagSrc;
  edm::EDGetTokenT<CSCCorrelatedLCTDigiCollection> corrlctDigiTagSrc;

  edm::EDGetTokenT<CSCALCTDigiCollection> alctDigiTagSrc_emul;
  edm::EDGetTokenT<CSCCLCTDigiCollection> clctDigiTagSrc_emul;
  edm::EDGetTokenT<CSCCorrelatedLCTDigiCollection> corrlctDigiTagSrc_emul;
  edm::ESGetToken<CSCGeometry, MuonGeometryRecord> cscToken_;

//edm::InputTag compDigiTag;
//edm::InputTag cscRecHitTag;
//edm::InputTag cscSegTag;
//edm::InputTag saMuonTag;
//edm::InputTag l1aTag;
//edm::InputTag alctDigiTag;
//edm::InputTag clctDigiTag;
//edm::InputTag corrlctDigiTag;
//edm::InputTag hltTag;

//std::string theRootFileName,pdf;
std::string eventDisplayDir;
std::vector<double> eventList;
std::vector<int> runList;
std::vector<int> endcapList;
std::vector<int> stationList;
std::vector<int> ringList;
std::vector<int> chamberList;
std::string eventlistFile;


std::string chamberType;

bool doDebug;
bool addEmulation ;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
GifDisplay::GifDisplay(const edm::ParameterSet& iConfig)

{
   
//now do what ever initialization is needed
//theRootFileName= iConfig.getUntrackedParameter<std::string>("rootFileName");
/*std::cout<<theRootFileName.c_str()<<"\n";
pdf=theRootFileName+".pdf";
fout=new TFile(theRootFileName.c_str(),"RECREATE");
fout->cd();
*/
//cscRecHitTag  = iConfig.getParameter<edm::InputTag>("cscRecHitTag");
//stripDigiTag  = iConfig.getParameter<edm::InputTag>("stripDigiTag");
//wireDigiTag  = iConfig.getParameter<edm::InputTag>("wireDigiTag");
//comparatorDigiTag = iConfig.getParameter<edm::InputTag>("comparatorDigiTag");
  wireDigiTagSrc=consumes<CSCWireDigiCollection>(iConfig.getUntrackedParameter<edm::InputTag>("wireDigiTagSrc")),
  stripDigiTagSrc=consumes<CSCStripDigiCollection>(iConfig.getUntrackedParameter<edm::InputTag>("stripDigiTagSrc")),
  compDigiTagSrc=consumes<CSCComparatorDigiCollection>(iConfig.getUntrackedParameter<edm::InputTag>("compDigiTagSrc")),
//alctDigiTag = iConfig.getParameter<edm::InputTag>("alctDigiTag");
  alctDigiTagSrc = consumes<CSCALCTDigiCollection>(iConfig.getUntrackedParameter<edm::InputTag>("alctDigiTagSrc"));
  clctDigiTagSrc = consumes<CSCCLCTDigiCollection>(iConfig.getUntrackedParameter<edm::InputTag>("clctDigiTagSrc"));
  corrlctDigiTagSrc = consumes<CSCCorrelatedLCTDigiCollection>(iConfig.getUntrackedParameter<edm::InputTag>("corrlctDigiTagSrc"));

  alctDigiTagSrc_emul = consumes<CSCALCTDigiCollection>(iConfig.getUntrackedParameter<edm::InputTag>("alctDigiTagSrc_Emul"));
  clctDigiTagSrc_emul = consumes<CSCCLCTDigiCollection>(iConfig.getUntrackedParameter<edm::InputTag>("clctDigiTagSrc_Emul"));
  corrlctDigiTagSrc_emul = consumes<CSCCorrelatedLCTDigiCollection>(iConfig.getUntrackedParameter<edm::InputTag>("corrlctDigiTagSrc_Emul"));



  eventDisplayDir = iConfig.getUntrackedParameter<std::string>("eventDisplayDir","/home/mhl/public_html/2017/20171025_cscSeg/eventdisplay/");
  eventlistFile = "eventList.txt";
  chamberType = iConfig.getUntrackedParameter<std::string>("chamberType", "11");
  doDebug = iConfig.getUntrackedParameter<bool>("debug", false);
  addEmulation = iConfig.getUntrackedParameter<bool>("addEmulation", false);

  cscToken_ = consumesCollector().esConsumes<CSCGeometry, MuonGeometryRecord>();
}





GifDisplay::~GifDisplay()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
GifDisplay::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;

int testE = 2;
int testS = 1;
int testR = 1;
int testC = 21;

edm::ESHandle<CSCGeometry> cscGeom;
cscGeom = &iSetup.getData(cscToken_);
//iSetup.get<MuonGeometryRecord>().get(cscGeom);
//edm::EventId evId=iEvent.id();
//unsigned int time=iEvent.time().unixTime();

double Run,Event;
Run = iEvent.id().run();
Event = iEvent.id().event();

//vector<CSCDetID> chamberList;
//chamberList.clear();
endcapList.clear();
stationList.clear();
ringList.clear();
chamberList.clear();
eventList.clear();
runList.clear();

vector<WIRE>   wire_container;
vector<STRIP>  strip_container;
vector<COMPARATOR> com_container;
//vector<CSCALCTDigi> alct_container;
//vector<CSCCLCTDigi> clct_container;
vector<CSCIDLCTs> alct_container;
vector<CSCIDLCTs> alct_emul_container;
vector<CSCIDLCTs> clct_container;
vector<CSCIDLCTs> clct_emul_container;
vector<CSCIDLCTs> lct_container;
vector<CSCIDLCTs> lct_emul_container;

//==========================Get event list for display================
ifstream file(eventlistFile);
while (file)
 {
     string line;
     getline(file, line);
     istringstream is(line);
     while (is) {

           int run;
           is >> run;

           double event;
           is >> event;
           eventList.push_back(event);

           int endcap; is >> endcap;
           endcapList.push_back(endcap);

           int station; is >> station;
           stationList.push_back(station);

           int ring; is >> ring;
           ringList.push_back(ring);

           int chamber; is >> chamber;
           chamberList.push_back(chamber);

           }

  }


if (find (runList.begin(), runList.end(), Run) == runList.end()) return;
if (find (eventList.begin(), eventList.end(), Event) == eventList.end()) return;

/*
CSCDetID chamberID;

if (chamberType == "11"){

   chamberID.Endcap = 1;
   chamberID.Station = 1;
   chamberID.Ring = 1;
   chamberID.Chamber = 1;

   }else if(chamberType == "21"){

           chamberID.Endcap = 1;
           chamberID.Station = 2;
           chamberID.Ring = 1;
           chamberID.Chamber = 2;

           }
*/

//========================== WIRES ========================
//edm::EDGetTokenT<CSCWireDigiCollection> w_token = consumes<CSCWireDigiCollection>(wireDigiTag);
edm::Handle<CSCWireDigiCollection> wires;
//iEvent.getByLabel(wireDigiTag,wires);
iEvent.getByToken(wireDigiTagSrc, wires);


for (CSCWireDigiCollection::DigiRangeIterator wi=wires->begin(); wi!=wires->end(); wi++) {
    CSCDetId id = (CSCDetId)(*wi).first;
    std::vector<CSCWireDigi>::const_iterator wireIt = (*wi).second.first;
    std::vector<CSCWireDigi>::const_iterator lastWire = (*wi).second.second;

    CSCDetID tmpID;
    WIRE tmpWIRE;

if (doDebug) {
   if (!(id.endcap() == testE && id.station() == testS && id.ring() == testR && id.chamber() == testC ) ) continue;
   }

    tmpID.Endcap = id.endcap();
    tmpID.Ring = id.ring();//==4 ? 1 : id.ring();
    tmpID.Station = id.station();
    tmpID.Chamber = id.chamber();
    tmpID.Layer = id.layer();


    for( ; wireIt != lastWire; ++wireIt){

       Wire tmpWG;

       tmpWG.WireGroup = wireIt->getWireGroup();
       tmpWG.TimeBin = wireIt->getTimeBin();
       tmpWG.NumberTimeBin = int((wireIt->getTimeBinsOn()).size());

       tmpWIRE.second.push_back(tmpWG);
//if (doDebug) cout << id << endl;
//if (doDebug) cout << "wg: " << tmpWG.WireGroup << ", time: " << tmpWG.TimeBin << endl;

       }// all wires
  
    tmpWIRE.first = tmpID;
    wire_container.push_back(tmpWIRE); 
}	//all layers for wires		



//========================== STRIPS ========================

//edm::Handle<CSCStripDigiCollection> strips;
//iEvent.getByLabel(stripDigiTag,strips);
//edm::EDGetTokenT<CSCStripDigiCollection> s_token = consumes<CSCStripDigiCollection>(stripDigiTag);
edm::Handle<CSCStripDigiCollection> strips;
//iEvent.getByLabel(wireDigiTag,wires);
iEvent.getByToken(stripDigiTagSrc, strips);

for (CSCStripDigiCollection::DigiRangeIterator si=strips->begin(); si!=strips->end(); si++) {
    CSCDetId id = (CSCDetId)(*si).first;
    std::vector<CSCStripDigi>::const_iterator stripIt = (*si).second.first;
    std::vector<CSCStripDigi>::const_iterator lastStrip = (*si).second.second;

    CSCDetID tmpID;
    STRIP tmpSTRIP;

    tmpID.Endcap = id.endcap();
    tmpID.Ring = id.ring();//==4 ? 1 : id.ring();//if me11a, set its ring=1
    tmpID.Station = id.station();
    tmpID.Chamber = id.chamber();
    tmpID.Layer = id.layer();

if (doDebug) {
   if (!(id.endcap() == testE && id.station() == testS && id.ring() == testR && id.chamber() == testC ) ) continue;
   }

    for( ; stripIt != lastStrip; ++stripIt) {

       Strips tmpSP;

       tmpSP.Strip = stripIt->getStrip();
       if (id.ring() == 4) tmpSP.Strip+=64;//for now ME11A only shift 2cfeb, BECAUSE GIF ME11A ONLY HAS dcfeb 1,5,7

       std::vector<int> myADCVals = stripIt->getADCCounts();
       int adcTotal, maxADC, adcMaxTime;
       double ped = 0.5*(myADCVals[0]+myADCVals[1]);   

       adcTotal = 0; maxADC = 0; adcMaxTime = 0;

//cout << tmpID.Layer << ", strip: " << tmpSP.Strip << endl;     
//cout << myADCVals[0] << " " << myADCVals[1] << endl;

       for (int i = 2; i < int(myADCVals.size()); i++){

           double tmpADC = myADCVals[i]-ped;
           adcTotal+=tmpADC;

//cout << myADCVals[i] - ped << " " ;
           if (tmpADC > maxADC && tmpADC > 13.3){

              maxADC = tmpADC;
              adcMaxTime = i;
 
              }

           }//loop over all 6 time bins for each strip, from 2 to 7
//cout << endl;

//if (doDebug) cout << id << endl;
//if (doDebug&&maxADC>0) cout << "strip: " << tmpSP.Strip << ", adc: " << maxADC << endl;

       tmpSP.ADCTotal = adcTotal;
       tmpSP.MaxADC = maxADC;
       tmpSP.ADCMaxTime = adcMaxTime;

       tmpSTRIP.second.push_back(tmpSP);
    }   

    tmpSTRIP.first = tmpID;
    strip_container.push_back(tmpSTRIP);

}//strip collection

//==========COMPARATOR=========================


//edm::Handle<CSCComparatorDigiCollection> comparators;
//iEvent.getByLabel(comparatorDigiTag,comparators);
//edm::EDGetTokenT<CSCComparatorDigiCollection> c_token = consumes<CSCComparatorDigiCollection>(comparatorDigiTag);
edm::Handle<CSCComparatorDigiCollection> comparators;
//iEvent.getByLabel(wireDigiTag,wires);
iEvent.getByToken(compDigiTagSrc, comparators);


for (CSCComparatorDigiCollection::DigiRangeIterator com=comparators->begin(); com!=comparators->end(); com++) {

    CSCDetId id = (CSCDetId)(*com).first;

if (doDebug) {
   if (!(id.endcap() == testE && id.station() == testS && id.ring() == testR && id.chamber() == testC ) ) continue;
   }

    std::vector<CSCComparatorDigi>::const_iterator comparatorIt = (*com).second.first;
    std::vector<CSCComparatorDigi>::const_iterator lastComparator = (*com).second.second;
   
    CSCDetID tmpID;
    
    COMPARATOR tmpCOMPARATOR;

    tmpID.Endcap = id.endcap();
    tmpID.Ring = id.ring();// ? 1 : id.ring();
    tmpID.Station = id.station();
    tmpID.Chamber = id.chamber();
    tmpID.Layer = id.layer();

    for( ; comparatorIt != lastComparator; ++comparatorIt) {

       Comparator tmpCOM;   

       tmpCOM.Strip = comparatorIt->getStrip();
       if (id.ring() == 4) tmpCOM.Strip+=64; //gif for now, same reason as strip
       tmpCOM.TimeBin = comparatorIt->getTimeBin();
       tmpCOM.ComparatorNumber = comparatorIt->getComparator();
       if (id.ring() == 4) tmpCOM.ComparatorNumber+=128;
//if (doDebug) cout << id << endl;
//if (doDebug) cout << "strip: " << tmpCOM.Strip << ", comparator: " << tmpCOM.ComparatorNumber << endl;
       tmpCOMPARATOR.second.push_back(tmpCOM);

       }


    tmpCOMPARATOR.first = tmpID;
    com_container.push_back(tmpCOMPARATOR);

}//comparator collection

//ALCT
edm::Handle<CSCALCTDigiCollection> alcts;
iEvent.getByToken(alctDigiTagSrc, alcts);
fillALCT(alcts, alct_container);

// CLCT
edm::Handle<CSCCLCTDigiCollection> clcts;
iEvent.getByToken(clctDigiTagSrc, clcts);
fillCLCT(clcts, clct_container);


// LCT
edm::Handle<CSCCorrelatedLCTDigiCollection> lcts;
iEvent.getByToken(corrlctDigiTagSrc, lcts);
fillCorrLCT(lcts, lct_container);

//ALCT
edm::Handle<CSCALCTDigiCollection> alcts_emul;
// CLCT
edm::Handle<CSCCLCTDigiCollection> clcts_emul;
// LCT
edm::Handle<CSCCorrelatedLCTDigiCollection> lcts_emul;
if (addEmulation){
   try{
	  iEvent.getByToken(alctDigiTagSrc_emul, alcts_emul);
	  fillALCT(alcts_emul, alct_emul_container);

	  iEvent.getByToken(clctDigiTagSrc_emul, clcts_emul);
	  fillCLCT(clcts_emul, clct_emul_container);

	  iEvent.getByToken(corrlctDigiTagSrc_emul, lcts_emul);
	  fillCorrLCT(lcts_emul, lct_emul_container);
   } catch (cms::Exception){
     std::cout <<" failed to emulated trigger primitives, ignore "<< std::endl;
     addEmulation = false;
  }
}

//make event display
vector<CSCDetID> usedChamber;

//if (Event < 500){//find(eventList.begin(), eventList.end(), Event) != eventList.end()){
//if (find(eventList.begin(), eventList.end(), Event) != eventList.end()){

for (int i = 0; i < int(eventList.size()); i++) {

   if (i >= 1000) continue;

   double eventL = eventList[i];
   int endcapL = endcapList[i];
   int stationL = stationList[i];
   int ringL = ringList[i];
   int chamberL = chamberList[i];

   if (Event != eventL) continue;

   CSCDetID tmpId;
   tmpId.Endcap = endcapL;
   tmpId.Station =  stationL;
   tmpId.Ring = ringL;
   tmpId.Chamber = chamberL;

   WireStripDisplay(eventDisplayDir, tmpId, wire_container, strip_container, com_container, alct_container, alct_emul_container, clct_container, clct_emul_container, lct_container, lct_emul_container, usedChamber, Run, Event, addEmulation);
}
//   }






#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}



void GifDisplay::fillALCT(edm::Handle<CSCALCTDigiCollection> digicoll, vector<CSCIDLCTs>& alct_container){

 for (CSCALCTDigiCollection::DigiRangeIterator j=digicoll->begin(); j!=digicoll->end(); j++) {
    const CSCALCTDigiCollection::Range& range =(*j).second;
    const CSCDetId& idLCT = (*j).first;

   CSCIDLCTs tmpidlcts;
   CSCDetID tmpID;
   

   tmpID.Endcap = idLCT.endcap();
   tmpID.Ring = idLCT.ring();// ? 1 : id.ring();
   tmpID.Station = idLCT.station();
   tmpID.Chamber = idLCT.chamber();
   tmpID.Layer = idLCT.layer();

   tmpidlcts.first = tmpID ;

    for (CSCALCTDigiCollection::const_iterator digiIt = range.first; digiIt!=range.second; ++digiIt){
	if (!digiIt->isValid()) continue;
	CorrelatedLCT tmplct;
	tmplct.keyWG = digiIt->getKeyWG();
	tmplct.quality =  digiIt->getQuality();
	tmplct.pattern = digiIt->getCollisionB();
	tmplct.BX = digiIt->getBX();
	tmpidlcts.second.push_back(tmplct);

	  if (doDebug) cout << idLCT << endl;
	  if (doDebug) {
	  cout << "ALCT strip: " << tmplct.keyStrip;
	  cout << " keyWG: " << tmplct.keyWG;
	  cout << " pattern: " << tmplct.pattern;
	  cout << " quality: " << tmplct.quality << endl;

	  }


        }
   alct_container.push_back(tmpidlcts);

  }
}


void GifDisplay::fillCLCT(edm::Handle<CSCCLCTDigiCollection> digicoll, vector<CSCIDLCTs>& clct_container){

 for (CSCCLCTDigiCollection::DigiRangeIterator j=digicoll->begin(); j!=digicoll->end(); j++) {
    const CSCCLCTDigiCollection::Range& range =(*j).second;
    const CSCDetId& idLCT = (*j).first;

   CSCIDLCTs tmpidlcts;
   CSCDetID tmpID;
   

   tmpID.Endcap = idLCT.endcap();
   tmpID.Ring = idLCT.ring();// ? 1 : id.ring();
   tmpID.Station = idLCT.station();
   tmpID.Chamber = idLCT.chamber();
   tmpID.Layer = idLCT.layer();

   tmpidlcts.first = tmpID ;

    for (CSCCLCTDigiCollection::const_iterator digiIt = range.first; digiIt!=range.second; ++digiIt){
	if (!digiIt->isValid()) continue;
	CorrelatedLCT tmplct;
	tmplct.keyStrip = digiIt->getKeyStrip() ;
	tmplct.quality =  digiIt->getQuality();
	tmplct.pattern = digiIt->getPattern();
	tmplct.BX = digiIt->getBX();
	tmpidlcts.second.push_back(tmplct);

	  if (doDebug) cout << idLCT << endl;
	  if (doDebug) {
	  cout << "CLCT strip: " << tmplct.keyStrip;
	  cout << " keyWG: " << tmplct.keyWG;
	  cout << " pattern: " << tmplct.pattern;
	  cout << " quality: " << tmplct.quality << endl;

	  }


        }
   clct_container.push_back(tmpidlcts);

  }
}


void GifDisplay::fillCorrLCT(edm::Handle<CSCCorrelatedLCTDigiCollection> digicoll, vector<CSCIDLCTs>& lct_container){

 for (CSCCorrelatedLCTDigiCollection::DigiRangeIterator j=digicoll->begin(); j!=digicoll->end(); j++) {
    const CSCCorrelatedLCTDigiCollection::Range& range =(*j).second;
    const CSCDetId& idLCT = (*j).first;

   CSCIDLCTs tmpidlcts;
   CSCDetID tmpID;
   

   tmpID.Endcap = idLCT.endcap();
   tmpID.Ring = idLCT.ring();// ? 1 : id.ring();
   tmpID.Station = idLCT.station();
   tmpID.Chamber = idLCT.chamber();
   tmpID.Layer = idLCT.layer();

   tmpidlcts.first = tmpID ;

    for (CSCCorrelatedLCTDigiCollection::const_iterator digiIt = range.first; digiIt!=range.second; ++digiIt){
	if (!digiIt->isValid()) continue;
	CorrelatedLCT tmplct;
	tmplct.keyWG = digiIt->getKeyWG();
	tmplct.keyStrip = digiIt->getStrip() ;
	tmplct.quality =  digiIt->getQuality();
	tmplct.pattern = digiIt->getPattern();
	tmplct.BX = digiIt->getBX();
	tmpidlcts.second.push_back(tmplct);

	  if (doDebug) cout << idLCT << endl;
	  if (doDebug) {
	  cout << "CorrelatedLCT strip: " << digiIt->getStrip();
	  cout << " keyWG: " << digiIt->getKeyWG();
	  cout << " pattern: " << digiIt->getPattern();
	  cout << " quality: " << digiIt->getQuality() << endl;

	  }


        }
   lct_container.push_back(tmpidlcts);

  }
}


// ------------ method called once each job just before starting event loop  ------------
void 
GifDisplay::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GifDisplay::endJob() 
{

}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
GifDisplay::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(GifDisplay);
