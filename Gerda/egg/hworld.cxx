// @(#)root/test:$Id: hworld.cxx 20882 2007-11-19 11:31:26Z rdm $
// Author: Fons Rademakers   04/04/97

// This small demo shows the traditional "Hello World". Its main use is
// to show how to use ROOT graphics and how to enter the eventloop to
// be able to interact with the graphics.

#include "TApplication.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TPaveLabel.h"
#include "TH1F.h"
int main(int argc, char **argv)
{
  TApplication theApp("App", &argc, argv);

   TCanvas *c = new TCanvas("c", "The Hello Canvas", 400, 400);
   //TPad *c = new TPad("p","The pad",0,0,400,400);
    c->Connect("Closed()", "TApplication", &theApp, "Terminate()");
   TH1F *f1 = new TH1F("f1","Demo function",100,-3,3);
   f1->FillRandom("gaus",10000000);
   f1->Draw();
   //TPaveLabel *hello = new TPaveLabel(0.2,0.4,0.8,0.6,"Hello World");
   //hello->Draw();
   //TPaveLabel *quit = new TPaveLabel(0.2,0.2,0.8,0.3,"Close via menu File/Quit");
   //quit->Draw();
   c->Update();
   c->SaveAs("res.pdf");
   theApp.Run();
   c->Close();
   
   c->Delete();
   f1->Delete();
   //delete hello;
   //delete quit;
   return 0;
}
