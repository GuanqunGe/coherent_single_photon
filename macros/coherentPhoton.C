#include <cmath>
#include<stdio.h>
#include <iostream>
#include <string>


void coherentPhoton(const char* filename) {
	
	FILE *fp = NULL;
	remove("coherentPhoton1000Events.txt");
	fp = fopen("coherentPhoton1000Events.txt", "a");	

	TFile* fin = new TFile(filename, "read");
	
	TTree* tin = (TTree*)fin->Get("gst");

	TRandom3 *rand= new TRandom3();
	std::string coherent_photon_cut = "nfem==1 && pdgf[0]==22";
	
	double Ef[5];
	double pxf[5];
	double pyf[5];
	double pzf[5];
	int nfem;
	double pdgf[5];
	int neu;
	double Q2;
	double Ev;
	
	tin->SetBranchAddress("neu", &neu);
	tin->SetBranchAddress("Q2", &Q2);
	tin->SetBranchAddress("Ev", &Ev);
	tin->SetBranchAddress("nfem", &nfem);
	tin->SetBranchAddress("pdgf", &pdgf);
	tin->SetBranchAddress("Ef", &Ef);
	tin->SetBranchAddress("pxf", &pxf);
	tin->SetBranchAddress("pyf", &pyf);
	tin->SetBranchAddress("pzf", &pzf);

//	TH2D* h_xy_dist = new TH2D("xydistribution", "X vs Y coordinates; x coordinate (cm); y coordinate (cm)", 50,-1.55, 254.8, 50, -115.53, 117.47);
//	TH2D* h_xz_dist = new TH2D("xzdistribution", "X vs Z coordinates; x coordinate (cm); z coordinate (cm)", 50, -1.55, 254.8, 50, 0.1, 1036.8);
//	TH2D* h_yz_dist = new TH2D("yzdistribution", "Y vs Z coordinates; y coordinate (cm); z coordinate (cm)", 50, -115.3, 117.47, 50, 0.1, 1036.8); 
//	TH1D* h_x_coords = new TH1D("xdistribution", "Distribution of x Coordinates; x coordinate (cm); Entries", 50, -1.55, 254.8);
//	TH1D* h_y_coords = new TH1D("ydistribution", "Distribution of y Coordinates; y coordinate (cm); Entries", 50, -115.3, 117.47);
//	TH1D* h_z_coords = new TH1D("zdistribution", "Distribution of z Coordinates; z coordinate (cm); Entries", 50, 0.1, 1036.8);	

	for (int i = 0; i < 1000; ++i) {
		tin->GetEntry(i);
		int neu_pdg_code = neu;
		double mom_transfer = Q2;
		double neu_energy = Ev;
		int event_num = i;
		int num_particles = 2;
		int status_code = 1;
		int pdg_code = 22;
		int first_mother = 0;
		int second_mother = 0;
		int first_daughter = 0;
		int second_daughter = 0;
		double momentum_x = pxf[0];
		double momentum_y = pyf[0];
		double momentum_z = pzf[0];
		double energy = Ef[0];
		double mass = 0.0;
		double pos_x = rand->Uniform(-1.55, 254.8);
		double pos_y = rand->Uniform(-115.53, 117.47);
		double pos_z = rand->Uniform(0.1, 1036.8);
//		double pos_x = std::fmod(((double) rand()), (256.35 + 1.)) - 1.55;   //in cm
//		double pos_y = std::fmod(((double) rand()), (116.5 + 116.5 + 1.)) + (-116.5 + 0.97);  //in cm
//		double pos_z = std::fmod(((double) rand()), (1036.8 - 0.1 + 1.)) + 0.1;  //in cm
		double time = rand->Uniform(3125, 4725); //in ns
		fprintf(fp, "%d %d\n", event_num, num_particles);
		fprintf(fp, "%d %d %d %d %d %d %f %f %f %f %f %f %f %f %f\n", status_code, pdg_code, first_mother, second_mother, first_daughter, second_daughter, momentum_x, momentum_y, momentum_z, energy, mass, pos_x, pos_y, pos_z, time);
		
		fprintf(fp, "0 %d 0 0 0 0 0 0 0 %f %f 0 0 0 0\n", neu_pdg_code, neu_energy, mom_transfer);
//		h_xy_dist->Fill(pos_x, pos_y);
//		h_xz_dist->Fill(pos_x, pos_z);
//		h_yz_dist->Fill(pos_y, pos_z);
//		h_x_coords->Fill(pos_x);
//		h_y_coords->Fill(pos_y);
//		h_z_coords->Fill(pos_z);
}


//TCanvas* c = new TCanvas();
//c->Divide(2,2);
//c->cd(1);
//h_xy_dist->Draw("colz");
//h_xy_dist->SetStats(0);

//c->cd(2);
//h_xz_dist->Draw("colz");
//h_xz_dist->SetStats(0);

//c->cd(3);
//h_yz_dist->Draw("colz");
//h_yz_dist->SetStats(0);

//c->SaveAs("coord_distributions.pdf", "pdf");

//TCanvas* d = new TCanvas();
//d->Divide(2,2);
//d->cd(1);
//h_x_coords->Draw("histEX0");

//d->cd(2);
//h_y_coords->Draw("histEX0");

//d->cd(3);
//h_z_coords->Draw("histEX0");

//d->SaveAs("positions.pdf", "pdf");

fclose(fp);
}

