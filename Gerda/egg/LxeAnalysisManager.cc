/*
 * LxeAnalysisManager.cc
 *
 *  Created on: Jul 24, 2010
 *      Author: saturnman
 */
#include <G4SDManager.hh>
#include <G4Run.hh>
#include <G4Event.hh>
#include <G4HCofThisEvent.hh>

#include <numeric>

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TParameter.h>

#include "LxeDetectorConstruction.hh"
#include "LxeLiquidXenonHit.hh"
#include "LxePrimaryGeneratorAction.hh"
#include "LxeEventData.hh"

#include "LxeAnalysisManager.hh"

LxeAnalysisManager::LxeAnalysisManager(LxePrimaryGeneratorAction* pPrimaryGeneratorAction)
{
	this->m_iLxeHitsCollectionID = -1;
	this->m_pPrimaryGeneratorAction = pPrimaryGeneratorAction;
	this->m_hOutputDataFileName = "events.root";
	m_pEventData = new LxeEventData();
}
LxeAnalysisManager::~LxeAnalysisManager()
{
	delete m_pEventData;
}
void LxeAnalysisManager::BeginOfRun(const G4Run* pRun)
{
	this->m_pTreeFile = new TFile(this->m_hOutputDataFileName.c_str(),"RECREATE","File containing event data for Lxe");
	this->m_pTree = new TTree("t1","Tree containing event data for Lxe");
	gROOT->ProcessLine("#include <vector>");

	m_pTree->Branch("eventid", &m_pEventData->m_iEventID, "eventid/I");
	m_pTree->Branch("etot", &m_pEventData->m_fTotalEnergyDeposited, "etot/F");
	m_pTree->Branch("nsteps", &m_pEventData->m_iNbSteps, "nsteps/I");

 	m_pTree->Branch("trackid", "vector<int>", &m_pEventData->m_pTrackId);
	m_pTree->Branch("type", "vector<string>", &m_pEventData->m_pParticleType);
	m_pTree->Branch("parentid", "vector<int>", &m_pEventData->m_pParentId);
	m_pTree->Branch("parenttype", "vector<string>", &m_pEventData->m_pParentType);
	m_pTree->Branch("creaproc", "vector<string>", &m_pEventData->m_pCreatorProcess);
	m_pTree->Branch("edproc", "vector<string>", &m_pEventData->m_pDepositingProcess);
	m_pTree->Branch("xp", "vector<float>", &m_pEventData->m_pX);
	m_pTree->Branch("yp", "vector<float>", &m_pEventData->m_pY);
	m_pTree->Branch("zp", "vector<float>", &m_pEventData->m_pZ);
	m_pTree->Branch("ke", "vector<float>", &m_pEventData->m_fKineticEnergy);
	m_pTree->Branch("time", "vector<float>", &m_pEventData->m_pTime);

	m_pTree->Branch("type_pri", "vector<string>", &m_pEventData->m_pPrimaryParticleType);
	m_pTree->Branch("xp_pri", &m_pEventData->m_fPrimaryX, "xp_pri/F");
	m_pTree->Branch("yp_pri", &m_pEventData->m_fPrimaryY, "yp_pri/F");
	m_pTree->Branch("zp_pri", &m_pEventData->m_fPrimaryZ, "zp_pri/F");
	m_pTree->SetMaxTreeSize(G4int(10e9));
	m_pTree->AutoSave();
	m_pNbEventsToSimulatePamameter = new TParameter<int>("nbevents",this->m_iNbEventsToSimulate);
	m_pNbEventsToSimulatePamameter->Write();
}
void LxeAnalysisManager::BeginOfEvent(const G4Event* pEvent)
{
	if(m_iLxeHitsCollectionID == -1)
	{
		G4SDManager* pSDManager = G4SDManager::GetSDMpointer();
		m_iLxeHitsCollectionID = pSDManager->GetCollectionID("LxeLiquidXenonHitsCollection");
	}
}
void LxeAnalysisManager::EndOfEvent(const G4Event* pEvent)
{
	G4HCofThisEvent* pHCofThisEvent = pEvent->GetHCofThisEvent();
	LxeLiquidXenonHitsCollection* pLxeLiquidXenonHitsCollection = NULL;
	G4int iNbLxeHits = 0;
	if(pHCofThisEvent != NULL)
	{
		if(m_iLxeHitsCollectionID != -1)
		{
			pLxeLiquidXenonHitsCollection = (LxeLiquidXenonHitsCollection*)(pHCofThisEvent->GetHC(m_iLxeHitsCollectionID));
			if(pLxeLiquidXenonHitsCollection != NULL)
			{
				iNbLxeHits = pLxeLiquidXenonHitsCollection->entries();
			}
		}
	}
	if(iNbLxeHits != 0)
	{
		m_pEventData->m_iEventID = pEvent->GetEventID();
		m_pEventData->m_pPrimaryParticleType->push_back(this->m_pPrimaryGeneratorAction->GetParticleTypeOfPrimary());
		m_pEventData->m_fPrimaryX = m_pPrimaryGeneratorAction->GetPositionOfPrimary().x();
		m_pEventData->m_fPrimaryY = m_pPrimaryGeneratorAction->GetPositionOfPrimary().y();
		m_pEventData->m_fPrimaryZ = m_pPrimaryGeneratorAction->GetPositionOfPrimary().z();
		G4int iNbSteps = 0;
		G4float fTotalEnergyDeposited = 0;

		//process hits
		for(int i=0;i<iNbLxeHits;++i)
		{
			LxeLiquidXenonHit* pHit = (*pLxeLiquidXenonHitsCollection)[i];
			if(pHit->GetParticleType() != "opticalphoton")
			{
				m_pEventData->m_pTrackId->push_back(pHit->GetTrackId());
				m_pEventData->m_pParentId->push_back(pHit->GetParentId());
				m_pEventData->m_pParticleType->push_back(pHit->GetParticleType());
				m_pEventData->m_pParentType->push_back(pHit->GetParentType());
				m_pEventData->m_pCreatorProcess->push_back(pHit->GetCreatorProcess());
				m_pEventData->m_pDepositingProcess->push_back(pHit->GetDepositingProcess());
				m_pEventData->m_pX->push_back(pHit->GetPosition().x()/mm);
				m_pEventData->m_pY->push_back(pHit->GetPosition().y()/mm);
				m_pEventData->m_pZ->push_back(pHit->GetPosition().z()/mm);

				fTotalEnergyDeposited += pHit->GetEnergyDeposited()/keV;
				m_pEventData->m_fDepositEnergy->push_back(pHit->GetEnergyDeposited()/keV);

				m_pEventData->m_fKineticEnergy->push_back(pHit->GetKineticEnergy()/keV);
				m_pEventData->m_pTime->push_back(pHit->GetTime()/second);

				++iNbSteps;
			}
		}
		m_pEventData->m_iNbSteps = iNbSteps;
		m_pEventData->m_fTotalEnergyDeposited = fTotalEnergyDeposited;
		if(fTotalEnergyDeposited > 0.0)
		{
			m_pTree->Fill();
		}
		m_pEventData->Clear();
	}

}
void LxeAnalysisManager::Step(const G4Step* pStep)
{
}
void LxeAnalysisManager::EndOfRun(const G4Run* pRun)
{
	this->m_pTreeFile->Write();
	this->m_pTreeFile->Close();
}
