{
gROOT->SetBatch(kTRUE); 
FILE *htmlpage;
htmlpage=fopen("myindex.html","w");
fprintf(htmlpage,"<html>\n");
fprintf(htmlpage,"<h1><center>Juerg Eugster Plotpage</h1><hr>");
char thumbsize[100]="200x200";
char buffer[500]="";
char histname[500]="";
char picturetype[10]="gif";
//TFile *f1=new TFile("file:/home/xv/PFSamples/TauAnalyzer/sumw2/test/AnalyzedFullSim10000TauPt0_200.root");
TFile *f1=new TFile("/home/xv/PFSamples/TauAnalyzer/sumw2/fastjet10/AnalyzedFastSim10000TauPt0_200.root");
//TFile *f1=new TFile("AnalyzedFullSim10000TauPt0_200.root");

// 1 Delta Et

TH1F *hist11;
TH1F *hist12;
TH1F *hist01;
c1 = new TCanvas("c1","",100,200,1280,1024);
c1->SetFrameFillColor(0);
f1->GetObject("h_deltaETvisible_MCHEPMC_EHT_;1",hist11);
f1->GetObject("h_deltaETvisible_MCHEPMC_PF_;1",hist12);
hist01= new TH1F("hist01" , "" ,150,-150,150);//#Delta E_{T}    -    red: EHT, blue: PF//
hist01->SetBinContent(1,2000);
hist01->SetBin Content(2,0);
hist01->GetXaxis()->SetTitle("#Delta E_{T}");
hist01->SetMarkerColor(0);
hist01->Draw("E4");
hist11->SetFillColor(42);
hist11->SetLineWidth(2);
hist11->SetLineColor(2);

hist12->SetLineColor(4);
hist12->SetLineWidth(2);
hist12->GetXaxis()->SetTitle("#Delta E_{T}");
hist12->SetTitle("");
hist12->Draw("sames");
hist11->Draw("sames");
c1->SetFillColor(0);
c1->SetBorderMode(0);
c1->SetBorderSize(0);
c1->Update();
TPaveStats *shist11=(TPaveStats*)hist11->GetListOfFunctions()->FindObject("stats");
TPaveStats *shist12=(TPaveStats*)hist12->GetListOfFunctions()->FindObject("stats");

//shist11->SetFillStyle(0);
shist11->SetFillColor(0);
shist11->SetLineColor(2);
shist11->SetY1NDC(0.65);
shist11->SetY2NDC(0.8);
shist12->SetLineColor(4);
//shist12->SetFillStyle(0);
shist12->SetFillColor(0);

c1->Modified();
histname="01FullSim10000TauPt0_200DeltaEt";
sprintf(buffer,"%s.%s",histname,picturetype);
c1->Print(buffer);
sprintf(buffer,"convert %s.%s -resize %s %s_small.%s",histname,picturetype,thumbsize,histname,picturetype);
system(buffer);
fprintf(htmlpage,"<a href=%s.%s><img src=%s.%s></a>\n",histname,picturetype,histname,picturetype);
//c1->Print("/home/xv/PFSamples/TauAnalyzer/sumw2/test/01FullSim10000TauPt0_200DeltaEt.gif");

// 2 delta Et vs Pt

c2 = new TCanvas("c2","",100,200,1280,1024);
c2->SetFillColor(0);
TH1F *hist21;
TH1F *hist22;
TH1F *hist02;
hist02= new TH1F("hist02" , "#Delta E_{T} vs p_{T}    -    red: EHT, blue: PF" ,50,0,200);
hist02->SetBinContent(1,50);
hist02->SetBin Content(2,-15);
hist02->GetXaxis()->SetTitle("p_{T}");
hist02->GetYaxis()->SetTitle("#Delta E_{T}");

TPaveStats *ptstats = new TPaveStats(0.854885,0.916284,0.948276,0.970183,"brNDC");
ptstats->SetName("stats");
ptstats->SetBorderSize(2);
ptstats->SetFillStyle(0);
ptstats->SetLineColor(0);
ptstats->SetTextAlign(12);
ptstats->SetTextColor(0);

TText *text = ptstats->AddText("hist02");
text->SetTextSize(0.0123968);
text = ptstats->AddText("Entries = 2      ");
text = ptstats->AddText("Mean  =  43.54");
text = ptstats->AddText("RMS   =  36.42");
ptstats->SetOptStat(1111);
ptstats->SetOptFit(0);
ptstats->Draw();
hist02->GetListOfFunctions()->Add(ptstats);
ptstats->SetParent(hist02->GetListOfFunctions());
hist02->SetMarkerColor(0);
hist02->Draw("E4");

f1->GetObject("h_deltaEtvsEt_MCHEPMC_EHT_;1",hist21);
f1->GetObject("h_deltaEtvsEt_MCHEPMC_PF_;1",hist22);

hist21->SetMarkerStyle(20);
hist21->SetMarkerColor(2);
hist21->Draw("E1 same");
hist22->SetMarkerStyle(20);
hist22->SetMarkerColor(4);
hist22->Draw("E1 same");

TPaveText *pt2 = new TPaveText(0.01,0.94161,0.5,0.995,"blNDC");
pt2->SetName("title");
pt2->SetBorderSize(2);
pt2->SetFillColor(0);
text = pt2->AddText("");
pt2->Draw();

c2->Modified();
histname="02FullSim10000TauPt0_200DeltaEtvsPt";
sprintf(buffer,"%s.%s",histname,picturetype);
c2->Print(buffer);
sprintf(buffer,"convert %s.%s -resize %s %s_small.%s",histname,picturetype,thumbsize,histname,picturetype);
system(buffer);
fprintf(htmlpage,"<a href=%s.%s><img src=%s.%s></a>\n",histname,picturetype,histname,picturetype);
//c2->Print("/home/xv/PFSamples/TauAnalyzer/sumw2/test/02FullSim10000TauPt0_200DeltaEtvsPt.gif");



// 3 delta ET vs Eta

c3 = new TCanvas("c2","",100,200,1280,1024);
c3->SetFillColor(0);
TH1F *hist31;
TH1F *hist32;
TH1F *hist03;
hist03= new TH1F("hist03" , "#Delta E_{T}  vs #eta     -     red: EHT, blue: PF" ,80,-3,3);
hist03->SetBinContent(1,50);
hist03->SetBin Content(2,-20);
hist03->GetXaxis()->SetTitle("#eta");
hist03->GetYaxis()->SetTitle("#Delta E_{T}");

TPaveStats *ptstats = new TPaveStats(0.854885,0.916284,0.948276,0.970183,"brNDC");
ptstats->SetName("stats");
ptstats->SetBorderSize(2);
ptstats->SetFillStyle(0);
ptstats->SetLineColor(0);
ptstats->SetTextAlign(12);
ptstats->SetTextColor(0);

TText *text = ptstats->AddText("hist03");
text->SetTextSize(0.0123968);
text = ptstats->AddText("Entries = 2      ");
text = ptstats->AddText("Mean  =  43.54");
text = ptstats->AddText("RMS   =  36.42");
ptstats->SetOptStat(1111);
ptstats->SetOptFit(0);
ptstats->Draw();
hist03->GetListOfFunctions()->Add(ptstats);
ptstats->SetParent(hist03->GetListOfFunctions());
hist03->SetMarkerColor(0);
hist03->Draw("E4");

f1->GetObject("h_deltaEtvsEta_MCHEPMC_EHT_;1",hist31);
f1->GetObject("h_deltaEtvsEta_MCHEPMC_PF_;1",hist32);

hist31->SetMarkerStyle(20);
hist31->SetMarkerColor(2);
hist31->Draw("E1 same");
hist32->SetMarkerStyle(20);
hist32->SetMarkerColor(4);
hist32->Draw("E1 same");

TPaveText *pt3 = new TPaveText(0.01,0.94161,0.5,0.995,"blNDC");
pt3->SetName("title");
pt3->SetBorderSize(2);
pt3->SetFillColor(0);
text = pt3->AddText("");
pt3->Draw();

c3->Modified();
histname="03FullSim10000TauPt0_200DeltaEtvsEta";
sprintf(buffer,"%s.%s",histname,picturetype);
c3->Print(buffer);
sprintf(buffer,"convert %s.%s -resize %s %s_small.%s",histname,picturetype,thumbsize,histname,picturetype);
system(buffer);
fprintf(htmlpage,"<a href=%s.%s><img src=%s.%s></a>\n",histname,picturetype,histname,picturetype);
//c3->Print("/home/xv/PFSamples/TauAnalyzer/sumw2/test/03FullSim10000TauPt0_200DeltaEtvsEta.gif");


// 4 delta Et / Et(true) vs pt

c4 = new TCanvas("c4","",100,200,1280,1024);
c4->SetFillColor(0);
TH1F *hist41;
TH1F *hist42;
TH1F *hist04;
hist04= new TH1F("hist04" , "#Delta E_{T} / E_{T true} vs p_{T}    -    red: EHT, blue: PF" ,50,0,200);
hist04->SetBinContent(1,.5);
hist04->SetBin Content(2,-1); //-10 - 10?
hist04->GetXaxis()->SetTitle("p_{T}");
hist04->GetYaxis()->SetTitle("#Delta E_{T} / E_{T true}");

TPaveStats *ptstats = new TPaveStats(0.854885,0.916284,0.948276,0.970183,"brNDC");
ptstats->SetName("stats");
ptstats->SetBorderSize(2);
ptstats->SetFillStyle(0);
ptstats->SetLineColor(0);
ptstats->SetTextAlign(12);
ptstats->SetTextColor(0);

TText *text = ptstats->AddText("hist04");
text->SetTextSize(0.0123968);
text = ptstats->AddText("Entries = 2      ");
text = ptstats->AddText("Mean  =  43.54");
text = ptstats->AddText("RMS   =  36.42");
ptstats->SetOptStat(1111);
ptstats->SetOptFit(0);
ptstats->Draw();
hist04->GetListOfFunctions()->Add(ptstats);
ptstats->SetParent(hist04->GetListOfFunctions());
hist04->SetMarkerColor(0);
hist04->Draw("E4");

f1->GetObject("h_deltaEtDivEtvsEt_MCHEPMC_EHT_;1",hist41);
f1->GetObject("h_deltaEtDivEtvsEt_MCHEPMC_PF_;1",hist42);

hist41->SetMarkerStyle(20);
hist41->SetMarkerColor(2);
hist41->Draw("E1 same");
hist42->SetMarkerStyle(20);
hist42->SetMarkerColor(4);
hist42->Draw("E1 same");

TPaveText *pt4 = new TPaveText(0.01,0.94161,0.5,0.995,"blNDC");
pt4->SetName("title");
pt4->SetBorderSize(2);
pt4->SetFillColor(0);
text = pt4->AddText("");
pt4->Draw();

c4->Modified();
histname="04FullSim10000TauPt0_200DeltaEtDivEttruevsPt";
sprintf(buffer,"%s.%s",histname,picturetype);
c4->Print(buffer);
sprintf(buffer,"convert %s.%s -resize %s %s_small.%s",histname,picturetype,thumbsize,histname,picturetype);
system(buffer);
fprintf(htmlpage,"<a href=%s.%s><img src=%s.%s></a>\n",histname,picturetype,histname,picturetype);
//c4->Print("/home/xv/PFSamples/TauAnalyzer/sumw2/test/04FullSim10000TauPt0_200DeltaEtDivEttruevsPt.gif");

// 5 delta Et / Et(rec) vs pt

c5 = new TCanvas("c2","",100,200,1280,1024);
c5->SetFillColor(0);
TH1F *hist51;
TH1F *hist52;
TH1F *hist05;
hist05= new TH1F("hist05" , "#Delta E_{T} / E_{T rec}  vs p_{T}    -    red: EHT, blue: PF" ,150,0,200);
hist05->SetBinContent(1,0.2);
hist05->SetBin Content(2,-1);
hist05->GetXaxis()->SetTitle("p_{T}");
hist05->GetYaxis()->SetTitle("#Delta E_{T} / E_{T rec}");

TPaveStats *ptstats = new TPaveStats(0.854885,0.916284,0.948276,0.970183,"brNDC");
ptstats->SetName("stats");
ptstats->SetBorderSize(2);
ptstats->SetFillStyle(0);
ptstats->SetLineColor(0);
ptstats->SetTextAlign(12);
ptstats->SetTextColor(0);

TText *text = ptstats->AddText("hist05");
text->SetTextSize(0.0123968);
text = ptstats->AddText("Entries = 2      ");
text = ptstats->AddText("Mean  =  43.54");
text = ptstats->AddText("RMS   =  36.42");
ptstats->SetOptStat(1111);
ptstats->SetOptFit(0);
ptstats->Draw();
hist05->GetListOfFunctions()->Add(ptstats);
ptstats->SetParent(hist05->GetListOfFunctions());
hist05->SetMarkerColor(0);
hist05->Draw("E4");

f1->GetObject("h_deltaEtDivEtrecvsEt_MCHEPMC_EHT_;1",hist51);
f1->GetObject("h_deltaEtDivEtrecvsEt_MCHEPMC_PF_;1",hist52);

hist51->SetMarkerStyle(20);
hist51->SetMarkerColor(2);
hist51->Draw("E1 same");
hist52->SetMarkerStyle(20);
hist52->SetMarkerColor(4);
hist52->Draw("E1 same");

TPaveText *pt5 = new TPaveText(0.01,0.94161,0.5,0.995,"blNDC");
pt5->SetName("title");
pt5->SetBorderSize(2);
pt5->SetFillColor(0);
text = pt5->AddText("");
pt5->Draw();

c5->Modified();
histname="05FullSim10000TauPt0_200DeltaEtrecvsPt";
sprintf(buffer,"%s.%s",histname,picturetype);
c5->Print(buffer);
sprintf(buffer,"convert %s.%s -resize %s %s_small.%s",histname,picturetype,thumbsize,histname,picturetype);
system(buffer);
fprintf(htmlpage,"<a href=%s.%s><img src=%s.%s></a>\n",histname,picturetype,histname,picturetype);
//c5->Print("/home/xv/PFSamples/TauAnalyzer/sumw2/test/05FullSim10000TauPt0_200DeltaEtrecvsPt.gif");

// 6 delta Et / Et(true) vs eta

c6 = new TCanvas("c6","",100,200,1280,1024);
c6->SetFillColor(0);
TH1F *hist61;
TH1F *hist62;
TH1F *hist06;
hist06= new TH1F("hist06" , "#Delta E_{T} / E_{T true}  vs #eta    -    red: EHT, blue: PF" ,80,-3,3);
hist06->SetBinContent(1,0.5);
hist06->SetBin Content(2,-0.5);
hist06->GetXaxis()->SetTitle("#eta");
hist06->GetYaxis()->SetTitle("#Delta E_{T} / E_{T true}");

TPaveStats *ptstats = new TPaveStats(0.854885,0.916284,0.948276,0.970183,"brNDC");
ptstats->SetName("stats");
ptstats->SetBorderSize(2);
ptstats->SetFillStyle(0);
ptstats->SetLineColor(0);
ptstats->SetTextAlign(12);
ptstats->SetTextColor(0);

TText *text = ptstats->AddText("hist03");
text->SetTextSize(0.0123968);
text = ptstats->AddText("Entries = 2      ");
text = ptstats->AddText("Mean  =  43.54");
text = ptstats->AddText("RMS   =  36.42");
ptstats->SetOptStat(1111);
ptstats->SetOptFit(0);
ptstats->Draw();
hist06->GetListOfFunctions()->Add(ptstats);
ptstats->SetParent(hist06->GetListOfFunctions());
hist06->SetMarkerColor(0);
hist06->Draw("E4");

f1->GetObject("h_deltaEtDivEtvsEta_MCHEPMC_EHT_;1",hist61);
f1->GetObject("h_deltaEtDivEtvsEta_MCHEPMC_PF_;1",hist62);

hist61->SetMarkerStyle(20);
hist61->SetMarkerColor(2);
hist61->Draw("E1 same");
hist62->SetMarkerStyle(20);
hist62->SetMarkerColor(4);
hist62->Draw("E1 same");

TPaveText *pt6 = new TPaveText(0.01,0.94161,0.5,0.995,"blNDC");
pt6->SetName("title");
pt6->SetBorderSize(2);
pt6->SetFillColor(0);
text = pt6->AddText("");
pt6->Draw();

c6->Modified();
histname="06FullSim10000TauPt0_200DeltaEtDivEttruevsEta";
sprintf(buffer,"%s.%s",histname,picturetype);
c6->Print(buffer);
sprintf(buffer,"convert %s.%s -resize %s %s_small.%s",histname,picturetype,thumbsize,histname,picturetype);
system(buffer);
fprintf(htmlpage,"<a href=%s.%s><img src=%s.%s></a>\n",histname,picturetype,histname,picturetype);


//c6->Print("/home/xv/PFSamples/TauAnalyzer/sumw2/test/06FullSim10000TauPt0_200DeltaEtDivEttruevsEta.gif");

// 7 delta Et / Et(rec) vs eta

c7 = new TCanvas("c7","",100,200,1280,1024);
c7->SetFillColor(0);
TH1F *hist71;
TH1F *hist72;
TH1F *hist07;
hist07= new TH1F("hist07" , "#Delta E_{T} / E_{T rec}  vs #eta    -    red: EHT, blue: PF" ,80,-3,3);
hist07->SetBinContent(1,0.2);
hist07->SetBin Content(2,-0.5);
hist07->GetXaxis()->SetTitle("#eta");
hist07->GetYaxis()->SetTitle("#Delta E_{T} / E_{T rec}");

TPaveStats *ptstats = new TPaveStats(0.854885,0.916284,0.948276,0.970183,"brNDC");
ptstats->SetName("stats");
ptstats->SetBorderSize(2);
ptstats->SetFillStyle(0);
ptstats->SetLineColor(0);
ptstats->SetTextAlign(12);
ptstats->SetTextColor(0);

TText *text = ptstats->AddText("hist07");
text->SetTextSize(0.0123968);
text = ptstats->AddText("Entries = 2      ");
text = ptstats->AddText("Mean  =  43.54");
text = ptstats->AddText("RMS   =  36.42");
ptstats->SetOptStat(1111);
ptstats->SetOptFit(0);
ptstats->Draw();
hist07->GetListOfFunctions()->Add(ptstats);
ptstats->SetParent(hist07->GetListOfFunctions());
hist07->SetMarkerColor(0);
hist07->Draw("E4");

f1->GetObject("h_deltaEtDivEtrecvsEta_MCHEPMC_EHT_;1",hist71);
f1->GetObject("h_deltaEtDivEtrecvsEta_MCHEPMC_PF_;1",hist72);

hist71->SetMarkerStyle(20);
hist71->SetMarkerColor(2);
hist71->Draw("E1 same");
hist72->SetMarkerStyle(20);
hist72->SetMarkerColor(4);
hist72->Draw("E1 same");

TPaveText *pt7 = new TPaveText(0.01,0.94161,0.5,0.995,"blNDC");
pt7->SetName("title");
pt7->SetBorderSize(2);
pt7->SetFillColor(0);
text = pt7->AddText("");
pt7->Draw();

c7->Modified();
histname="07FullSim10000TauPt0_200DeltaEtDivEtrecvsEta";
sprintf(buffer,"%s.%s",histname,picturetype);
c7->Print(buffer);
sprintf(buffer,"convert %s.%s -resize %s %s_small.%s",histname,picturetype,thumbsize,histname,picturetype);
system(buffer);
fprintf(htmlpage,"<a href=%s.%s><img src=%s.%s></a>\n",histname,picturetype,histname,picturetype);


//c7->Print("/home/xv/PFSamples/TauAnalyzer/sumw2/test/07FullSim10000TauPt0_200DeltaEtDivEtrecvsEta.gif");

// 8 delta eta

c8 = new TCanvas("c8","",100,200,1280,1024);
c8->SetFillColor(0);
TH1F *hist81;
TH1F *hist82;
f1->GetObject("h_deltaEta_MCHEPMC_EHT_;1",hist82);
f1->GetObject("h_deltaEta_MCHEPMC_PF_;1",hist81);
//
TH1F *hist08;
hist08= new TH1F("hist01" , "#Delta #eta    -    red: EHT, blue: PF" ,250,-0.2,0.2);
hist08->SetBinContent(1,800);
hist08->SetBin Content(2,0);
hist08->GetXaxis()->SetTitle("#Delta #eta");
hist08->SetMarkerColor(0);

TText *text = ptstats->AddText("hist08");
text->SetTextSize(0.0123968);
text = ptstats->AddText("Entries = 2      ");
text = ptstats->AddText("Mean  =  43.54");
text = ptstats->AddText("RMS   =  36.42");
ptstats->SetOptStat(1111);
ptstats->SetOptFit(0);
ptstats->Draw();
hist08->GetListOfFunctions()->Add(ptstats);
ptstats->SetParent(hist08->GetListOfFunctions());
hist08->SetMarkerColor(0);
//hist08->SetTitle("#Delta #eta    -    red: EHT, blue: PF");
//hist08->Draw("E4");
TPaveStats *ptstats81 = new TPaveStats(0.78,0.65,0.98,0.79,"brNDC");
ptstats81->SetBorderSize(2);
ptstats81->SetFillColor(0);
ptstats81->SetLineColor(4);
ptstats81->SetTextAlign(12);
ptstats81->Draw("sames");
hist81->GetListOfFunctions()->Add(ptstats81);
//hist81->SetTitle("#Delta #eta    -    red: EHT, blue: PF");//
hist08->Draw("E4");//
hist81->SetLineWidth(2);
hist81->SetLineColor(4);
hist81->Draw("sames");
TPaveStats *ptstats82 = new TPaveStats(0.78,0.81,0.98,0.95,"brNDC");
ptstats82->SetBorderSize(2);
ptstats82->SetFillColor(0);
ptstats82->SetLineColor(2);
ptstats82->SetTextAlign(12);
ptstats82->Draw("sames");
hist82->GetListOfFunctions()->Add(ptstats82);

hist82->SetLineWidth(2);
hist82->SetLineColor(2);
hist82->Draw("sames");
TPaveText *pt8 = new TPaveText(0.01,0.94161,0.5,0.995,"blNDC");//0.01,0.94161,0.167931,0.995
pt8->SetName("title");
pt8->SetBorderSize(2);
pt8->SetFillColor(0);
text = pt8->AddText("dfgsd");
pt8->Draw("sames");

c8->Modified();
histname="08FullSim10000TauPt0_200DeltaEta";
sprintf(buffer,"%s.%s",histname,picturetype);
c8->Print(buffer);
sprintf(buffer,"convert %s.%s -resize %s %s_small.%s",histname,picturetype,thumbsize,histname,picturetype);
system(buffer);
fprintf(htmlpage,"<a href=%s.%s><img src=%s.%s></a>\n",histname,picturetype,histname,picturetype);
//c8->Print("/home/xv/PFSamples/TauAnalyzer/sumw2/test/08FullSim10000TauPt0_200DeltaEta.gif");




// 9 deltaEta vs pt 

c9 = new TCanvas("c9","",100,200,1280,1024);
c9->SetFillColor(0);
TH1F *hist91;
TH1F *hist92;
f1->GetObject("h_deltaEtavsPt_MCHEPMC_EHT_;1",hist92);
f1->GetObject("h_deltaEtavsPt_MCHEPMC_PF_;1",hist91);
//
TH1F *hist09;
hist09= new TH1F("hist09" , "#Delta #eta vs p_{T}   -    red: EHT, blue: PF" ,50,0,200);
hist09->SetBinContent(1,0.5);
hist09->SetBin Content(2,-0.5);
hist09->GetXaxis()->SetTitle("p_{T}");
hist09->GetYaxis()->SetTitle("#Delta #eta");
hist09->SetMarkerColor(0);

TText *text = ptstats->AddText("hist09");
text->SetTextSize(0.0123968);
text = ptstats->AddText("Entries = 2      ");
text = ptstats->AddText("Mean  =  43.54");
text = ptstats->AddText("RMS   =  36.42");
ptstats->SetOptStat(1111);
ptstats->SetOptFit(0);
ptstats->Draw();
hist09->GetListOfFunctions()->Add(ptstats);
ptstats->SetParent(hist09->GetListOfFunctions());
//hist09->SetMarkerColor(0);
hist09->Draw("E4");
//
TPaveStats *ptstats91 = new TPaveStats(0.78,0.65,0.98,0.79,"brNDC");
ptstats91->SetBorderSize(2);
ptstats91->SetFillColor(0);
ptstats91->SetLineColor(4);
ptstats91->SetTextAlign(12);
ptstats91->Draw();
hist91->GetListOfFunctions()->Add(ptstats91);
hist91->SetTitle("#Delta #eta vs p_{T}    -    red: EHT, blue: PF");
hist91->SetMarkerStyle(20);
hist91->SetMarkerColor(4);
hist91->Draw("E1 sames");//
TPaveStats *ptstats92 = new TPaveStats(0.78,0.81,0.98,0.95,"brNDC");
ptstats92->SetBorderSize(2);
ptstats92->SetFillColor(0);
ptstats92->SetLineColor(2);
ptstats92->SetTextAlign(12);
ptstats92->Draw();
hist92->GetListOfFunctions()->Add(ptstats92);
hist92->SetMarkerStyle(20);
hist92->SetMarkerColor(2);
hist92->Draw("E1 sames");
TPaveText *pt9 = new TPaveText(0.01,0.94161,0.5,0.995,"blNDC");//0.01,0.94161,0.167931,0.995
pt9->SetName("title");
pt9->SetBorderSize(2);
pt9->SetFillColor(0);
text9 = pt9->AddText("");
pt9->Draw();

c9->Modified();
histname="09FullSim10000TauPt0_200DeltaEtavsPt";
sprintf(buffer,"%s.%s",histname,picturetype);
c9->Print(buffer);
sprintf(buffer,"convert %s.%s -resize %s %s_small.%s",histname,picturetype,thumbsize,histname,picturetype);
system(buffer);
fprintf(htmlpage,"<a href=%s.%s><img src=%s.%s></a>\n",histname,picturetype,histname,picturetype);
//c9->Print("/home/xv/PFSamples/TauAnalyzer/sumw2/test/09FullSim10000TauPt0_200DeltaEtavsPt.gif");

// 10 delta eta vs eta

c10 = new TCanvas("c10","",100,200,1280,1024);
c10->SetFillColor(0);
TH1F *hist101;
TH1F *hist102;
f1->GetObject("h_deltaEtavsEta_MCHEPMC_EHT_;1",hist102);
f1->GetObject("h_deltaEtavsEta_MCHEPMC_PF_;1",hist101);
//
TH1F *hist010;
hist010= new TH1F("hist010" , "#Delta #eta vs #eta   -    red: EHT, blue: PF" ,80,-3,3);
hist010->SetBinContent(1,3);
hist010->SetBin Content(2,-2);
hist010->GetXaxis()->SetTitle("#Delta #eta");
hist010->SetMarkerColor(0);

TText *text = ptstats->AddText("hist010");
text->SetTextSize(0.0123968);
text = ptstats->AddText("Entries = 2      ");
text = ptstats->AddText("Mean  =  43.54");
text = ptstats->AddText("RMS   =  36.42");
ptstats->SetOptStat(1111);
ptstats->SetOptFit(0);
ptstats->Draw();
hist010->GetListOfFunctions()->Add(ptstats);
ptstats->SetParent(hist09->GetListOfFunctions());
hist010->SetMarkerColor(0);
hist010->Draw("E4 sames");
//
TPaveStats *ptstats101 = new TPaveStats(0.78,0.65,0.98,0.79,"brNDC");
ptstats101->SetBorderSize(2);
ptstats101->SetFillColor(0);
ptstats101->SetLineColor(4);
ptstats101->SetTextAlign(12);
ptstats101->Draw();
hist101->GetListOfFunctions()->Add(ptstats101);
hist101->SetTitle("#Delta #eta vs #eta    -    red: EHT, blue: PF");
hist101->SetMarkerStyle(20);
hist101->SetMarkerColor(4);
hist101->Draw("E1 ");
TPaveStats *ptstats102 = new TPaveStats(0.78,0.81,0.98,0.95,"brNDC");
ptstats102->SetBorderSize(2);
ptstats102->SetFillColor(0);
ptstats102->SetLineColor(2);
ptstats102->SetTextAlign(12);
ptstats102->Draw();
hist102->GetListOfFunctions()->Add(ptstats102);
hist102->SetMarkerStyle(20);
hist102->SetMarkerColor(2);
hist102->Draw("E1 sames");
TPaveText *pt10 = new TPaveText(0.01,0.94161,0.5,0.995,"blNDC");//0.01,0.94161,0.167931,0.995
pt10->SetName("title");
pt10->SetBorderSize(2);
pt10->SetFillColor(0);
text10 = pt10->AddText("");
pt10->Draw();

c10->Modified();
histname="10FullSim10000TauPt0_200DeltaEtavsEta";
sprintf(buffer,"%s.%s",histname,picturetype);
c10->Print(buffer);
sprintf(buffer,"convert %s.%s -resize %s %s_small.%s",histname,picturetype,thumbsize,histname,picturetype);
system(buffer);
fprintf(htmlpage,"<a href=%s.%s><img src=%s.%s></a>\n",histname,picturetype,histname,picturetype);
//c10->Print("/home/xv/PFSamples/TauAnalyzer/sumw2/test/10FullSim10000TauPt0_200DeltaEtavsEta.gif");



// 11 delta phi

c11 = new TCanvas("c10","",100,200,1280,1024);
c11->SetFillColor(0);
TH1F *hist111;
TH1F *hist112;
f1->GetObject("h_deltaPhi_MCHEPMC_EHT_;1",hist112);
f1->GetObject("h_deltaPhi_MCHEPMC_PF_;1",hist111);
//
TH1F *hist011;
hist011= new TH1F("hist011" , "#Delta #phi   -    red: EHT, blue: PF" ,250,-0.2,0.2);
hist011->SetBinContent(1,700);
hist011->SetBin Content(2,0);
hist011->GetXaxis()->SetTitle("#Delta #phi");
hist011->SetMarkerColor(0);

TText *text = ptstats->AddText("hist011");
text->SetTextSize(0.0123968);
text = ptstats->AddText("Entries = 2      ");
text = ptstats->AddText("Mean  =  43.54");
text = ptstats->AddText("RMS   =  36.42");
ptstats->SetOptStat(1111);
ptstats->SetOptFit(0);
ptstats->Draw();
hist011->GetListOfFunctions()->Add(ptstats);
ptstats->SetParent(hist011->GetListOfFunctions());
//hist09->SetMarkerColor(0);
hist011->Draw("E4");
//
TPaveStats *ptstats111 = new TPaveStats(0.78,0.65,0.98,0.79,"brNDC");
ptstats111->SetBorderSize(2);
ptstats111->SetFillColor(0);
ptstats111->SetLineColor(4);
ptstats111->SetTextAlign(12);
ptstats111->Draw();
hist111->GetListOfFunctions()->Add(ptstats111);
hist111->SetTitle("#Delta #phi    -    red: EHT, blue: PF");
hist111->SetLineWidth(2);
hist111->SetLineColor(4);
hist111->Draw("sames");
TPaveStats *ptstats112 = new TPaveStats(0.78,0.81,0.98,0.95,"brNDC");
ptstats112->SetBorderSize(2);
ptstats112->SetFillColor(0);
ptstats112->SetLineColor(2);
ptstats112->SetTextAlign(12);
ptstats112->Draw();
hist112->GetListOfFunctions()->Add(ptstats112);
hist112->SetLineWidth(2);
hist112->SetLineColor(2);
hist112->Draw("sames");
TPaveText *pt11 = new TPaveText(0.01,0.94161,0.5,0.995,"blNDC");//0.01,0.94161,0.167931,0.995
pt11->SetName("title");
pt11->SetBorderSize(2);
pt11->SetFillColor(0);
text11 = pt11->AddText("");
pt11->Draw();

c11->Modified();
histname="11FullSim10000TauPt0_200DeltaPhi";
sprintf(buffer,"%s.%s",histname,picturetype);
c11->Print(buffer);
sprintf(buffer,"convert %s.%s -resize %s %s_small.%s",histname,picturetype,thumbsize,histname,picturetype);
system(buffer);
fprintf(htmlpage,"<a href=%s.%s><img src=%s.%s></a>\n",histname,picturetype,histname,picturetype);
//c10->Print("/home/xv/PFSamples/TauAnalyzer/sumw2/test/10FullSim10000TauPt0_200DeltaEtavsEta.gif");
//c11->Print("/home/xv/PFSamples/TauAnalyzer/sumw2/test/11FullSim10000TauPt0_200DeltaPhi.gif");


//12 delta phi vs pt

c12 = new TCanvas("c12","",100,200,1280,1024);
c12->SetFillColor(0);
TH1F *hist121;
TH1F *hist122;
f1->GetObject("h_deltaPhivsPt_MCHEPMC_EHT_;1",hist122);
f1->GetObject("h_deltaPhivsPt_MCHEPMC_PF_;1",hist121);
//
TH1F *hist012;
hist012= new TH1F("hist012" , "#Delta #phi vs p_{T}   -    red: EHT, blue: PF" ,50,0,200);
hist012->SetBinContent(1,0.5);
hist012->SetBin Content(2,-0.5);
hist012->SetMarkerColor(0);
hist012->GetXaxis()->SetTitle("p_{T}");
hist012->GetYaxis()->SetTitle("#Delta #phi");

TText *text = ptstats->AddText("hist012");
text->SetTextSize(0.0123968);
text = ptstats->AddText("Entries = 2      ");
text = ptstats->AddText("Mean  =  43.54");
text = ptstats->AddText("RMS   =  36.42");
ptstats->SetOptStat(1111);
ptstats->SetOptFit(0);
ptstats->Draw();
hist012->GetListOfFunctions()->Add(ptstats);
ptstats->SetParent(hist012->GetListOfFunctions());
//hist09->SetMarkerColor(0);
hist012->Draw("E4");
//
TPaveStats *ptstats121 = new TPaveStats(0.78,0.65,0.98,0.79,"brNDC");
ptstats121->SetBorderSize(2);
ptstats121->SetFillColor(0);
ptstats121->SetLineColor(4);
ptstats121->SetTextAlign(12);
ptstats121->Draw();
hist121->GetListOfFunctions()->Add(ptstats121);
hist121->SetTitle("#Delta #phi vs p_{T}    -    red: EHT, blue: PF");
hist121->SetMarkerStyle(20);
hist121->SetMarkerColor(4);
hist121->Draw("E1 sames");
TPaveStats *ptstats122 = new TPaveStats(0.78,0.81,0.98,0.95,"brNDC");
ptstats122->SetBorderSize(2);
ptstats122->SetFillColor(0);
ptstats122->SetLineColor(2);
ptstats122->SetTextAlign(12);
ptstats122->Draw();
hist122->GetListOfFunctions()->Add(ptstats122);
hist122->SetMarkerStyle(20);
hist122->SetMarkerColor(2);
hist122->Draw("E1 sames");
TPaveText *pt12 = new TPaveText(0.01,0.94161,0.5,0.995,"blNDC");//0.01,0.94161,0.167931,0.995
pt12->SetName("title");
pt12->SetBorderSize(2);
pt12->SetFillColor(0);
text12 = pt12->AddText("");
pt12->Draw();

c12->Modified();
histname="12FullSim10000TauPt0_200DeltaPhivsPt";
sprintf(buffer,"%s.%s",histname,picturetype);
c12->Print(buffer);
sprintf(buffer,"convert %s.%s -resize %s %s_small.%s",histname,picturetype,thumbsize,histname,picturetype);
system(buffer);
fprintf(htmlpage,"<a href=%s.%s><img src=%s.%s></a>\n",histname,picturetype,histname,picturetype);
//c12->Print("/home/xv/PFSamples/TauAnalyzer/sumw2/test/12FullSim10000TauPt0_200DeltaPhivsPt.gif");

//13 delta phi  vs  eta

c13 = new TCanvas("c13","",100,200,1280,1024);
c13->SetFillColor(0);
TH1F *hist131;
TH1F *hist132;
f1->GetObject("h_deltaPhivsEta_MCHEPMC_EHT_;1",hist132);
f1->GetObject("h_deltaPhivsEta_MCHEPMC_PF_;1",hist131);
//
TH1F *hist013;
hist013= new TH1F("hist013" , "#Delta #phi vs #eta   -    red: EHT, blue: PF" ,80,-3,3);//-0.5,0.5
hist013->SetBinContent(1,0.5);
hist013->SetBin Content(2,-0.5);
//hist012->GetXaxis()->SetTitle("#Delta #phi");
hist013->SetMarkerColor(0);
hist013->GetXaxis()->SetTitle("#eta");
hist013->GetYaxis()->SetTitle("#Delta #phi");

TText *text = ptstats->AddText("hist013");
text->SetTextSize(0.0123968);
text = ptstats->AddText("Entries = 2      ");
text = ptstats->AddText("Mean  =  43.54");
text = ptstats->AddText("RMS   =  36.42");
ptstats->SetOptStat(1111);
ptstats->SetOptFit(0);
ptstats->Draw();
hist013->GetListOfFunctions()->Add(ptstats);
ptstats->SetParent(hist013->GetListOfFunctions());
//hist09->SetMarkerColor(0);
hist013->Draw("E4");
//
TPaveStats *ptstats131 = new TPaveStats(0.78,0.65,0.98,0.79,"brNDC");
ptstats131->SetBorderSize(2);
ptstats131->SetFillColor(0);
ptstats131->SetLineColor(4);
ptstats131->SetTextAlign(12);
ptstats131->Draw();
hist131->GetListOfFunctions()->Add(ptstats131);
hist131->SetTitle("#Delta #phi vs #eta    -    red: EHT, blue: PF");
hist131->SetMarkerStyle(20);
hist131->SetMarkerColor(4);
hist131->Draw("E1 sames");
TPaveStats *ptstats132 = new TPaveStats(0.78,0.81,0.98,0.95,"brNDC");
ptstats132->SetBorderSize(2);
ptstats132->SetFillColor(0);
ptstats132->SetLineColor(2);
ptstats132->SetTextAlign(12);
ptstats132->Draw();
hist132->GetListOfFunctions()->Add(ptstats132);
hist132->SetMarkerStyle(20);
hist132->SetMarkerColor(2);
hist132->Draw("E1 sames");
TPaveText *pt13 = new TPaveText(0.01,0.94161,0.5,0.995,"blNDC");//0.01,0.94161,0.167931,0.995
pt13->SetName("title");
pt13->SetBorderSize(2);
pt13->SetFillColor(0);
text13 = pt13->AddText("");
pt13->Draw();

c13->Modified();
histname="13FullSim10000TauPt0_200DeltaPhivsEta";
sprintf(buffer,"%s.%s",histname,picturetype);
c13->Print(buffer);
sprintf(buffer,"convert %s.%s -resize %s %s_small.%s",histname,picturetype,thumbsize,histname,picturetype);
system(buffer);
fprintf(htmlpage,"<a href=%s.%s><img src=%s.%s></a>\n",histname,picturetype,histname,picturetype);
//c13->Print("/home/xv/PFSamples/TauAnalyzer/sumw2/test/13FullSim10000TauPt0_200DeltaPhivsEta.gif");

// 14 Erec/Etrue vs Pt

c14 = new TCanvas("c14","",100,200,1280,1024);
c14->SetFillColor(0);
TH1F *hist141;
TH1F *hist142;
TH1F *hist014;
hist014= new TH1F("hist014" , "E_{T rec} / E_{T true} vs p_{T}    -    red: EHT, blue: PF" ,20,0,200);
hist014->SetBinContent(1,1);
hist014->SetBin Content(2,0);
hist014->GetXaxis()->SetTitle("p_{T}");
hist014->GetYaxis()->SetTitle("E_{T rec} / E_{T true}");

TPaveStats *ptstats = new TPaveStats(0.854885,0.916284,0.948276,0.970183,"brNDC");
ptstats->SetName("stats");
ptstats->SetBorderSize(2);
ptstats->SetFillStyle(0);
ptstats->SetLineColor(0);
ptstats->SetTextAlign(12);
ptstats->SetTextColor(0);

TText *text = ptstats->AddText("hist014");
text->SetTextSize(0.0123968);
text = ptstats->AddText("Entries = 2      ");
text = ptstats->AddText("Mean  =  43.54");
text = ptstats->AddText("RMS   =  36.42");
ptstats->SetOptStat(1111);
ptstats->SetOptFit(0);
ptstats->Draw();
hist014->GetListOfFunctions()->Add(ptstats);
ptstats->SetParent(hist014->GetListOfFunctions());
hist014->SetMarkerColor(0);
hist014->Draw("E4");

f1->GetObject("h_ErecDivEtrue_MCHEPMC_EHT_;1",hist141);
f1->GetObject("h_ErecDivEtrue_MCHEPMC_PF_;1",hist142);

hist141->SetMarkerStyle(20);
hist141->SetMarkerColor(2);
hist141->Draw("E1 same");
hist142->SetMarkerStyle(20);
hist142->SetMarkerColor(4);
hist142->Draw("E1 same");

TPaveText *pt14 = new TPaveText(0.01,0.94161,0.5,0.995,"blNDC");
pt14->SetName("title");
pt14->SetBorderSize(2);
pt14->SetFillColor(0);
text = pt14->AddText("");
pt14->Draw();

c14->Modified();
c14->Print("14FullSim10000TauPt0_200ErecDivEtrue.gif");
histname="14FullSim10000TauPt0_200ErecDivEtrue";
sprintf(buffer,"%s.%s",histname,picturetype);
c14->Print(buffer);
sprintf(buffer,"convert %s.%s -resize %s %s_small.%s",histname,picturetype,thumbsize,histname,picturetype);
system(buffer);
fprintf(htmlpage,"<a href=%s.%s><img src=%s.%s></a>\n",histname,picturetype,histname,picturetype);
//c14->Print("/home/xv/PFSamples/TauAnalyzer/sumw2/test/14FullSim10000TauPt0_200DeltaEtvsPt.gif");

fprintf(htmlpage,"</html>");
fclose(htmlpage);
exit();
}
