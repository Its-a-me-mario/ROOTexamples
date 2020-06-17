// A simple example program
// Opens a file containing a TTree via TTreeReader
// Makes basic kinematics histograms based on this
//
#include "TFile.h"
#include "TFile.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include <stdio.h>
#include <algorithm>
#include <cstdlib>

void NTUPreader() {
	// Create a histogram to store the values of l_pt
	TH1F *hist_max_pt = new TH1F("h1","Max pT of leptons",100,0,250);
	TH1F *hist_min_pt = new TH1F("h2","pT of second lepton (if present)",100,0,250);
	TH1F *hist_delta_phi = new TH1F("h3","#Delta #phi between leptons",100,0,6.29);

	// Open the file containing the TTree
	TFile *file = TFile::Open("user.wmccorma.21183331._000001.NTUP10.root");
	if (!file || file->IsZombie()) { printf("File could not be opened properly.\n"); return; }

	// Create a TTreeReader for the TTree
	TTreeReader reader("anatree_nominal",file);
	TTreeReaderValue<std::vector<float>> lpt(reader, "l_pt");
	TTreeReaderValue<std::vector<float>> l_phi(reader, "l_phi");
	
	int i=0;
	while (reader.Next()) 
	{	
		i++;
		if (!(*lpt).empty()) 
		{ 
			// Print the l_pt values. There are usually either 0 or 2 of them.
			//for (std::vector<float>::iterator it = (*lpt).begin(); it != (*lpt).end(); ++it) {
				//std::cout << *it << ' '; 
			//}
			//cout << endl;
			// Now print only the maximum value
			//cout << *std::max_element( (*lpt).begin(), (*lpt).end() ) << endl;
			if (i%1000==0) {
				cout << abs ( (*l_phi).at(0) - (*l_phi).at(1) ) << endl;
			}	
			// Put the max l_pt into the histogram
			hist_max_pt->Fill( *std::max_element( (*lpt).begin(), (*lpt).end() ) );
			if ((*lpt).size()==2) {
			hist_min_pt->Fill( *std::min_element( (*lpt).begin(), (*lpt).end() ) );
			hist_delta_phi->Fill( abs( (*l_phi).at(0) - (*l_phi).at(1) ) ); 
			} 
		} 
	}
	// Draw histograms
	//hist_max_pt->Draw();
	//hist_min_pt->Draw();
	hist_delta_phi->Draw();	
}
 
