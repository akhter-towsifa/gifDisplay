#include "gifDisplay/GifDisplay/interface/display.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include <vector>
#include <list>
#include <iterator>
#include <boost/lexical_cast.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Rtypes.h"

#include "TF1.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TPaletteAxis.h"
#include "TMath.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#define PI 3.14159265

void GEMPadDisplay(TString address, GEMDetID id, vector<GEMSIMHIT> &simhit, vector<GEMPAD> &gempads, vector<GEMCLUSTER> &gemclusters,
        vector<GEMDetID> &usedChamber, int Run, int Event, int doDebug){

    gStyle->SetPalette(55);
    const int NPad = 192;
    const int NRoll = 8;
    const int NLayer = 2;

    //if (std::find(usedChamber.begin(), usedChamber.end(), id) == usedChamber.end()) return;

    bool doSimHit = simhit.size() > 0;
    vector<GEMDetID> allids_sh;
    for (const auto& id_simhit : simhit){
        allids_sh.push_back(id_simhit.first);
    }
    vector<GEMDetID> allids_pads;
    for (const auto& id_pad : gempads){
        allids_pads.push_back(id_pad.first);
    }

    srand (time(NULL));
    TString name = "";
    TString legendName = "";

    SetSaveNameLegendNameGEM(name, legendName, address, id, Run, Event);

    TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 600, 800);

    int npad_canvas = doSimHit ? 3 : 2;
    if(doDebug>2)  cout <<"start to display GEM, total in canvas " << npad_canvas << endl;
    
    c1->Divide(1, npad_canvas);

    c1->SetRightMargin(0.15);
    c1->SetBottomMargin(0.25);
    c1->SetTopMargin(0.25);

//GEM Pad display
    int ipad = 1;
    int nybins = NRoll*(NLayer+1)-1;
    c1->cd(ipad)->SetGridy(); ipad++;
    gPad->SetTopMargin(0.1);
    gPad->SetBottomMargin(0.15);
    TH2F* padDis = new TH2F("padDis", "", NPad, 0, NPad,  nybins, 0, nybins);
    TPaveText *pt1 = new TPaveText(0.4,.92,0.6,0.96, "NDC");

    PadDigiDisplay(id, allids_pads, gempads, padDis, doDebug);
    SetTitle(pt1, "GEM Pads");

    padDis->SetMarkerSize(1.0);
    padDis->Draw("COLZ text");
    pt1->Draw();

    TH2F* simhitDis = new TH2F("padDis", "", NPad, 0, NPad*2, nybins, 0, nybins);
    TPaveText *pt2 = new TPaveText(0.4,.92,0.6,0.96, "NDC");
    if (doSimHit){
        if (doDebug>2) cout <<"dipslay GEM simHits at ipad canvas "<< ipad << endl;
        c1->cd(ipad)->SetGridy(); ipad++;
        gPad->SetTopMargin(0.1);
        gPad->SetBottomMargin(0.15);

        GEMSimHitDisplay(id, allids_sh, simhit, simhitDis, doDebug);
        SetTitle(pt2, "SimHits and PDGID");
        simhitDis->SetMarkerSize(1.0);
        simhitDis->Draw("COLZtext");
        pt2->Draw();
    }


    //show GEMClusters
    if (doDebug>2) cout <<"dipslay GEM Cluster at ipad canvas "<< ipad << " superchamber "<< id << endl;
    c1->cd(ipad)->SetGridy(); ipad++;
    gPad->SetTopMargin(0.0);
    gPad->SetBottomMargin(0.0);
    //chamber, run, event
    stringstream ss;
    ss <<"GEM SuperChamber "<< (id.Endcap == 1 ? "+":"-") << id.Station <<"/"<< id.Ring <<"/"<< id.Chamber <<" ";
    ss <<" run: "<<  Run <<"  event #"<< Event <<" nominalBX=8(<-0)";
    TPaveText * tex1 = new TPaveText(0.1, 0.0, 0.9, 1.0, "NDC");
    //tex1->SetTextFont(42);
    tex1->AddText(ss.str().c_str());
    stringstream ss_clusters[100];
    int iclst = 0;
    for (int l=1; l <=NLayer; l++){
        for (int ieta=1; ieta <= NRoll; ieta++){
          
            GEMDetID thisid;
            thisid.Endcap  = id.Endcap;
            thisid.Station = id.Station;
            thisid.Ring    = id.Ring;
            thisid.Chamber = id.Chamber;
            thisid.Layer = l;
            thisid.Roll = ieta;
            vector<GEMPadCluster> clts = findClustersInChamber(thisid, gemclusters);
            for (unsigned int i = 0; i < clts.size(); i++){
                ss_clusters[iclst] <<"Cluster #"<< iclst <<" Layer "<< l <<" Roll "<< ieta <<" first Pad "<< clts[i].firstPad << " size " << clts[i].size <<" BX "<< clts[i].BX+8;
                tex1->AddText(ss_clusters[iclst].str().c_str());
                iclst++;
            }
        }
    }
    tex1->Draw();

    

    c1->Update();
    c1->SaveAs(name + ".png");
    c1->SaveAs(name + ".pdf");

    delete c1;
    delete padDis;
    delete simhitDis;
    delete tex1;
}





void SetSaveNameLegendNameGEM(TString& name, TString& legendName, TString address, GEMDetID id, int Run, int Event){

    TString  space = "                                   "; 
    if (id.Endcap == 1){
        legendName = "GE+" + NumberToString(id.Station) + "/" + NumberToString(id.Ring) + "/" + NumberToString(id.Chamber) + space+space + "Run #" + NumberToString(Run) + "  " + "Event #" + NumberToString(Event);
        name = address +"/"+ NumberToString(Run) + "_" + NumberToString(Event)+"_GEPlus" + NumberToString(id.Station) + "_" + NumberToString(id.Ring) + "_" + NumberToString(id.Chamber);
        }

    if (id.Endcap == 2){
        legendName = "GE-" + NumberToString(id.Station) + "/" + NumberToString(id.Ring) + "/" + NumberToString(id.Chamber)  + space+space + "Run #" + NumberToString(Run) + "  " + "Event #" + NumberToString(Event);
        name = address +"/" +NumberToString(Run) + "_" + NumberToString(Event)+"_GEMinus" + NumberToString(id.Station) + "_" + NumberToString(id.Ring) + "_" + NumberToString(id.Chamber);

        }


}



void GEMSimHitDisplay(GEMDetID id, vector<GEMDetID>& allIds, vector<GEMSIMHIT>& gemsimHits, TH2F* stripDis, int doDebug){ 

    stripDis->GetXaxis()->SetNdivisions(1010);
    stripDis->GetYaxis()->SetNdivisions(-23);
    stringstream label[24];
    for (int i = 1; i < 3; i++){//in each interesting layer has strip hits
      for (int ieta = 1; ieta <= 8; ieta++){

        GEMDetID tempId;
        tempId.Station = id.Station;
        tempId.Ring    = id.Ring;
        tempId.Layer   = i;
        tempId.Roll    = ieta;
        tempId.Endcap  = id.Endcap;
        tempId.Chamber = id.Chamber;
        int ybin = (8-tempId.Roll)*3+2-tempId.Layer;
        label[ybin] <<"L"<< i <<"Eta"<<ieta;
        stripDis->GetYaxis()->ChangeLabel(ybin+1,-1,-1,-1,-1,-1, label[ybin].str().c_str());
        if (i==1)  
            stripDis->GetYaxis()->ChangeLabel(ybin+2,-1,-1,-1,-1,-1, "--");

        if (doDebug > 2) cout <<"GEMSimhit display id "<< tempId <<" label "<< label[ybin].str()<<" ybin "<< ybin <<endl;
        auto it = find(allIds.begin(), allIds.end(), tempId);
        int index = (it == allIds.end()) ? -1 : distance(allIds.begin (), it);
        if (doDebug > 2)
            cout <<"\t total ids  "<< allIds.size() <<" index in SIMHIT vector " << index << endl;
        if (index < 0) continue;

        vector<SimHit> tempHits = gemsimHits[index].second;
        if (doDebug > 2) cout <<"\t GEM simhits found in chamber, size "<< tempHits.size() << endl;
        MakeOneLayerGEMSimHitDisplay(tempId, tempHits, stripDis);
      }
    }

    SetHistContour(stripDis, 11, 13);

    //stripDis_text->SetMarkerSize(1.5);

    stripDis->GetZaxis()->SetLabelSize(0.1);
    stripDis->GetZaxis()->SetRangeUser(11, 13);
    stripDis->SetStats(0);
    stripDis->GetXaxis()->SetTitle("Strip Number, SimHit");
    stripDis->GetXaxis()->SetLabelSize(0.06);
    stripDis->GetYaxis()->SetLabelSize(0.03);
    stripDis->GetXaxis()->SetTitleSize(0.06);
    stripDis->GetYaxis()->SetTitleSize(0.0);
    stripDis->GetXaxis()->SetTitleOffset(0.81);
    stripDis->GetYaxis()->SetTitleOffset(0.2);
    stripDis->GetYaxis()->CenterLabels();
    stripDis->SetTitle("");
}

void PadDigiDisplay(GEMDetID id, vector<GEMDetID>& allIds, vector<GEMPAD>& gempads, TH2F*padDis, int doDebug){ 
//Roll structure, eta increasing from top to bottom
// top: roll=1, bottom roll=8
//
    padDis->GetXaxis()->SetNdivisions(1010);
    padDis->GetYaxis()->SetNdivisions(-23);
    stringstream label[24];
    for (int i = 1; i < 3; i++){//in each interesting layer has strip hits
      for (int ieta = 1; ieta <= 8; ieta++){

        GEMDetID tempId;
        tempId.Station = id.Station;
        tempId.Ring    = id.Ring;
        tempId.Layer   = i;
        tempId.Roll    = ieta;
        tempId.Endcap  = id.Endcap;
        tempId.Chamber = id.Chamber;
        int ybin = (8-tempId.Roll)*3+2-tempId.Layer;
        label[ybin] <<"L"<< i <<"Eta"<<ieta;
        padDis->GetYaxis()->ChangeLabel(ybin+1,-1,-1,-1,-1,-1, label[ybin].str().c_str());
        if (i==1)  
            padDis->GetYaxis()->ChangeLabel(ybin+2,-1,-1,-1,-1,-1, "--");

        if (doDebug > 2) cout <<"GEMPad display id "<< tempId << " label "<< label[ybin].str() <<" ybin "<< ybin <<endl;
        auto it = find(allIds.begin(), allIds.end(), tempId);
        int index = (it == allIds.end()) ? -1 : distance(allIds.begin (), it);
        if (doDebug > 2)
           cout <<"\t GEPads display, total ids "<< allIds.size() <<" index in GEMPads vector " << index << endl;
        if (index < 0) continue;

        vector<GEMPad> tempPads = gempads[index].second;
        if (doDebug > 2) cout <<"\t GEMpads found in the detector, size " << tempPads.size() << endl;
        MakeOneLayerGEMPadDisplay(tempId, tempPads, padDis);

      }
    }

    SetHistContour(padDis, 0, 16);

    padDis->GetZaxis()->SetLabelSize(0.1);
    padDis->GetZaxis()->SetRangeUser(0,16);
    padDis->SetStats(0);
    padDis->GetXaxis()->SetTitle("GEM Pad Number");
    padDis->GetYaxis()->SetTitle("");
    padDis->GetXaxis()->SetLabelSize(0.06);
    padDis->GetYaxis()->SetLabelSize(0.03);
    padDis->GetXaxis()->SetTitleSize(0.06);
    padDis->GetYaxis()->SetTitleSize(0.0);
    padDis->GetXaxis()->SetTitleOffset(0.81);
    padDis->GetYaxis()->SetTitleOffset(0.2);
    padDis->GetYaxis()->CenterLabels();
    padDis->SetTitle("");
}



void MakeOneLayerGEMPadDisplay(GEMDetID tempId, vector<GEMPad> &pads, TH2F* padDisplay){

    for (int i = 0; i < int(pads.size()); i++){

        double time = pads[i].TimeBin+8;
        if (time==0){time+=0.1;}

        int pad = pads[i].Pad;
        int x1 = padDisplay->GetXaxis()->FindBin(pad);
        int ybin = (8-tempId.Roll)*3+2-tempId.Layer+1;
        padDisplay->SetBinContent(x1, ybin, time);

    }

}

void MakeOneLayerGEMSimHitDisplay(GEMDetID tempId, vector<SimHit> &shs, TH2F* stripDisplay){
    for (int i = 0; i < int(shs.size()); i++){

        double pdgid = shs[i].PdgId;
        int strip = shs[i].Strip;
        int x1 = stripDisplay->GetXaxis()->FindBin(strip);
        int ybin = (8-tempId.Roll)*3+2-tempId.Layer+1;
        //cout<<"Do one GEM layer display strip " << strip <<" ybin "<< ybin <<" pdgId " << pdgid <<endl;
        stripDisplay->SetBinContent(x1, ybin, pdgid);

    }
}

vector<GEMPadCluster> findClustersInChamber(GEMDetID id, vector<GEMCLUSTER>& allclusters){
   vector<GEMPadCluster> clusters;
   for (auto idclusters : allclusters){
      // cout <<"findCluster in "<< id <<" from allclusters "<< idclusters.first <<" num of cluster "<< idclusters.second.size() << endl;
       if (idclusters.first == id){
	   clusters = idclusters.second;
	   break;
       }
   }
  
 return clusters;
}
