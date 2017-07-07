#include <TSystem.h>
#include <TH2.h>
#include <TF1.h>
#include <TGraph.h>
#include <TNtuple.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TPaveText.h>
#include <TText.h>
#include <iostream>
#include <fstream>
#include <TLatex.h>
#include <string.h>
#include <TString.h>
#include <TLegend.h>
#include <THStack.h>
#include <TRandom3.h>
#include <TPad.h>
#include <TMath.h>
#include <TColor.h>

using namespace std;

Color_t kColorBK = kRed-4;
Color_t kColorUlmer = kCyan+1;
Color_t kColorSpline = kGreen+1;
Color_t kColorLinear = kBlack;

Int_t kLineBK = 1;
Int_t kLineUlmer = 9;
Int_t kLineLinear = 7;
Int_t kLineSpline = 10;

void makePlots() {
   TCanvas *c = new TCanvas("c", "Parameterization accuracy", 1200, 900);

   // Parameterization (l = 1st quartile, m = median, h = 3rd quartile)
   Double_t paraNPoints[100] = {};
   Double_t paraBKl[100] = {};
   Double_t paraBKm[100] = {};
   Double_t paraBKh[100] = {};
   Double_t paraBKInvl[100] = {};
   Double_t paraBKInvm[100] = {};
   Double_t paraBKInvh[100] = {};
   Double_t paraUlmerl[100] = {};
   Double_t paraUlmerm[100] = {};
   Double_t paraUlmerh[100] = {};
   Double_t paraUlmerInvl[100] = {};
   Double_t paraUlmerInvm[100] = {};
   Double_t paraUlmerInvh[100] = {};
   Double_t paraSplinel[100] = {};
   Double_t paraSplinem[100] = {};
   Double_t paraSplineh[100] = {};
   Double_t paraSplineInvl[100] = {};
   Double_t paraSplineInvm[100] = {};
   Double_t paraSplineInvh[100] = {};
   Double_t paraLinearl[100] = {};
   Double_t paraLinearm[100] = {};
   Double_t paraLinearh[100] = {};
   Double_t paraLinearInvl[100] = {};
   Double_t paraLinearInvm[100] = {};
   Double_t paraLinearInvh[100] = {};

   gStyle->SetOptStat(0);

   ifstream in;
   Double_t pN;
   Int_t    pi = 0;
   Double_t pBKl, pBKm, pBKh, pBKIl, pBKIm, pBKIh;
   Double_t pUlmerl, pUlmerm, pUlmerh, pUlmerIl, pUlmerIm, pUlmerIh;
   Double_t pLinearl, pLinearm, pLinearh, pLinearIl, pLinearIm, pLinearIh;
   Double_t pSplinel, pSplinem, pSplineh, pSplineIl, pSplineIm, pSplineIh;

   in.open("MedianValuesForParameterization_merged.csv");
   while (1) {
      in >> pN >> pBKl >> pBKm >> pBKh >> pBKIl >> pBKIm >> pBKIh >> pUlmerl >> pUlmerm >> pUlmerh >> pUlmerIl >> pUlmerIm >> pUlmerIh >> pSplinel >> pSplinem >> pSplineh >> pSplineIl >> pSplineIm >> pSplineIh >> pLinearl >> pLinearm >> pLinearh >> pLinearIl >> pLinearIm >> pLinearIh;

      if (!in.good()) break;

      paraNPoints[pi] = pN;
      paraBKm[pi] = pBKm;
      paraBKl[pi] = pBKm - pBKl;
      paraBKh[pi] = pBKh - pBKm;
      paraBKInvm[pi] = pBKIm;
      paraBKInvl[pi] = pBKIm - pBKIl;
      paraBKInvh[pi] = pBKIh - pBKIm;
      paraUlmerm[pi] = pUlmerm;
      paraUlmerl[pi] = pUlmerm - pUlmerl;
      paraUlmerh[pi] = pUlmerh - pUlmerm;
      paraUlmerInvm[pi] = pUlmerIm;
      paraUlmerInvl[pi] = pUlmerIm - pUlmerIl;
      paraUlmerInvh[pi] = pUlmerIh - pUlmerIm;
      paraSplinem[pi] = pSplinem;
      paraSplinel[pi] = pSplinem - pSplinel;
      paraSplineh[pi] = pSplineh - pSplinem;
      paraSplineInvm[pi] = pSplineIm;
      paraSplineInvl[pi] = pSplineIm - pSplineIl;
      paraSplineInvh[pi] = pSplineIh - pSplineIm;
      paraLinearm[pi] = pLinearm;
      paraLinearl[pi] = pLinearm - pLinearl;
      paraLinearh[pi] = pLinearh - pLinearm;
      paraLinearInvm[pi] = pLinearIm;
      paraLinearInvl[pi] = pLinearIm - pLinearIl;
      paraLinearInvh[pi] = pLinearIh - pLinearIm;

      pi++;
   }
   
   printf("pi = %d\n", pi);

   Double_t dummy[21] = {};
   
   gPad->SetLogy();
   gPad->SetLogx();

   TGraph *tgaBK     = new TGraph(pi, paraNPoints, paraBKh);
   TGraph *tgaUlmer  = new TGraph(pi, paraNPoints, paraUlmerh);
   TGraph *tgaSpline = new TGraph(pi, paraNPoints, paraSplineh);
   TGraph *tgaLinear = new TGraph(pi, paraNPoints, paraLinearh);

   tgaBK->SetTitle(";Number of data points in training group; 75% percentile of errors in range calculation [%]");

   tgaBK->SetLineColor(kColorBK);
   tgaBK->SetLineWidth(3);
   tgaBK->SetLineStyle(kLineBK);
   tgaUlmer->SetLineColor(kColorUlmer);
   tgaUlmer->SetLineStyle(kLineUlmer);
   tgaUlmer->SetLineWidth(3);
   tgaSpline->SetLineColor(kColorSpline);
   tgaSpline->SetLineStyle(kLineSpline);
   tgaSpline->SetLineWidth(3);
   tgaLinear->SetLineColor(kColorLinear);
   tgaLinear->SetLineStyle(kLineLinear);
   tgaLinear->SetLineWidth(3);

   tgaBK->GetXaxis()->SetTitleFont(22);
   tgaBK->GetXaxis()->SetLabelFont(22);
   tgaBK->GetYaxis()->SetTitleFont(22);
   tgaBK->GetYaxis()->SetLabelFont(22);

   tgaBK->Draw("AL");
   tgaUlmer->Draw("same, L");
   tgaSpline->Draw("same, L");
   tgaLinear->Draw("same, L");
   
   
   tgaBK->GetYaxis()->SetRangeUser(0.0005, 200);
   tgaBK->GetYaxis()->SetNoExponent();
   tgaBK->GetXaxis()->SetNoExponent();
   tgaBK->GetYaxis()->SetTitleOffset(1.2);

   TLegend *leg = new TLegend(0.72, 0.7, 0.94, 0.93);
   leg->SetTextSize(0.035);
   leg->SetTextFont(22);
   leg->AddEntry(tgaBK, "Bragg-Kleeman", "L");
   leg->AddEntry(tgaUlmer, "Sum of exponentials", "L");
   leg->AddEntry(tgaLinear, "Linear interpolation", "L");
   leg->AddEntry(tgaSpline, "Spline interpolation", "L");
   leg->Draw();
}
