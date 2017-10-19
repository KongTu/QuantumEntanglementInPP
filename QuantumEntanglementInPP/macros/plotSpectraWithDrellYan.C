#include "RiceStyle.h"

using namespace std;

void plotSpectraWithDrellYan(){

	gStyle->SetErrorX(0);

	TFile* file = new TFile("../rootfiles/test.root");

	TH2D* MassVsPt = (TH2D*) file->Get("ana/MassVsPt");

	double massbin[] = {0,1,3,5,10,20,50,70,100};

	TH1D* spectra_1D[10];
	for(int i = 0; i < 8; i++){

		spectra_1D[i] = (TH1D*) MassVsPt->ProjectionY(Form("pt_%d",i+1), massbin[i],massbin[i+1]);
	}

	TCanvas* c1 = new TCanvas("c1","c1",700,700);
    gPad->SetTicks();
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.13);
	gPad->SetLogy();
	gStyle->SetPadBorderMode(0.1);
	gStyle->SetOptTitle(0);

	TH1D* base1 = makeHist("base1", "Pb-going", "p_{T} (GeV)", "dN/dp_{T}", 100,0,100,kBlack);
	base1->GetYaxis()->SetRangeUser(0.00001, 10000000);
	base1->GetXaxis()->SetTitleColor(kBlack);
	
	fixedFontHist1D(base1,1.1,1.25);

	base1->GetYaxis()->SetTitleOffset(1.3);
	base1->GetYaxis()->SetTitleSize(base1->GetYaxis()->GetTitleSize()*1.6);
	base1->GetXaxis()->SetTitleSize(base1->GetXaxis()->GetTitleSize()*1.6);
	base1->GetYaxis()->SetLabelSize(base1->GetYaxis()->GetLabelSize()*1.6);
	base1->GetXaxis()->SetLabelSize(base1->GetXaxis()->GetLabelSize()*1.6);
	base1->GetXaxis()->SetNdivisions(4,6,0);
	base1->GetYaxis()->SetNdivisions(4,6,0);

	base1->Draw();	


	for(int i = 0; i < 8; i++){

		spectra_1D[i]->Rebin(10);
		spectra_1D[i]->SetMarkerStyle(20+i);
		spectra_1D[i]->SetMarkerColor(i+3);
		spectra_1D[i]->SetLineColor(i+1);
		spectra_1D[i]->Draw("Psame");

	}















}