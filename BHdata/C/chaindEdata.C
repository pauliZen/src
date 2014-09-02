// Chain the DdE... data
Int_t chaindEdata(TChain *dEtree,string rootname="run-020-020-1mil-result-dEt-up1m-",Int_t filenumber=7 )
{
   stringstream sstr;
   for (int i=0;i<filenumber;i++)
   {
     string index;
     sstr.str("");
     sstr.clear();
     sstr<<i;
     sstr>>index;
     dEtree->AddFile((rootname+index+".root").c_str());
   }
   return dEtree->GetEntries();
}

