//This script draw vb_t or rb_t graph for all index=//
//In the tree=======================================//
//Need .L drawgraph.C first=========================//

{
  //variables=========================================//
  string rootname;
  string treename;
  string logname;
  string graphdir;
  char inflagc='y';
  bool inflag=1;

  ifstream configf(".drawgraph-vbrb.conf");
  if (!configf.is_open())
    cout<<"No config file"<<endl;
  else
  {
    configf>>rootname;
    configf>>treename;
    configf>>logname;
    configf>>graphdir;
  }

  //input=============================================//
  cout<<"root name("<<rootname<<")('y'/n):";
  cin>>inflagc;
  if (inflagc=='n')
  {
    cout<<"Input root name:";
    cin>>rootname;
  }
  cout<<"Tree name("<<treename<<")('y'/n):";
  cin>>inflagc;
  if (inflagc=='n')
  {
    cout<<"Tree name:";
    cin>>treename;
  }
  cout<<"Index log name("<<logname<<")('y'/n):";
  cin>>inflagc;
  if (inflagc=='n')
  {
    cout<<"Input index log name:";
    cin>>logname;
  }
  cout<<"Graph save directory ("<<logname<<")('y'/n):";
  cin>>inflagc;
  if (inflagc=='n')
  {
    cout<<"Graph save directory (add / at last)";
    cin>>graphdir;
  }
  
  ofstream outconf(".drawgraph-vbrb.conf");
  outconf<<rootname<<endl;
  outconf<<treename<<endl;
  outconf<<logname<<endl;
  outconf<<graphdir<<endl;
  outconf.close();

  //Analysis==========================================//
  ifstream orgdata(logname.c_str());
  if (!orgdata.is_open())
  {
    cout<<"No log file"<<endl;
    exit();
  }
  else
  {
    TFile *fn=new TFile(rootname.c_str(),"update");
    TTree *stree=(TTree*)(gDirectory->Get(treename.c_str()));
    TCanvas *c1= new TCanvas("c1","graph",200,10,600,400);
    //  stree->Draw(">>indexlist","time_cur==0","entrylist");
    //  stree->SetBranchAddress("index",&indexi);
    //  Int_t indexnum=indexlist->GetN();
    while (!orgdata.eof())
    {
      stringstream sstr;
      string cutstr;
      Int_t sindex;
      Int_t tmpindex=sindex;
      orgdata>>sindex;
      if (tmpindex==sindex)
      {
        //          cout<<"index dup!"<<endl;
        continue;
      }
      sstr.str("");
      sstr.clear();
      sstr<<sindex;
      sstr>>cutstr;
      //      cout<<"total "<<indexnum<<endl;
      //  for (int i=0;i<indexnum;i++)
      //      {
      //    cout<<"Loop "<<i<<endl;
      //    Int_t entryi=indexlist->GetEntry(i);
      //    cout<<"step "<<entryi<<endl;
      //    stree->GetEntry(entryi);
      //    cout<<"now "<<indexi<<endl;
      //    sstr<<indexi;
      //    sstr>>cutstr;
      //    sstr.str("");
      //    sstr.clear();
      TCut cutv=("index=="+cutstr).c_str();
      TCut cutr=("index=="+cutstr+"&&rb<10").c_str();
      drawgraph(treename,cutr,"time_cur","rb",(graphdir+"rb-t-"+cutstr).c_str(),"AC",c1);
      drawgraph(treename,cutv,"time_cur","vb",(graphdir+"vb-t-"+cutstr).c_str(),"AC*",c1);
    }
  }
}
