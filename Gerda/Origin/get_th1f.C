TH1F* get_th1f(char* hisname)
{
   return (TH1F*) gDirectory->Get(hisname);
}
