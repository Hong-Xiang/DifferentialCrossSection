//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file electromagnetic/TestEm1/src/RunAction.cc
/// \brief Implementation of the RunAction class
//
// $Id: RunAction.cc 84208 2014-10-10 14:44:50Z gcosmo $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4EmCalculator.hh"

#include "Randomize.hh"
#include <iomanip>
#include "G4SystemOfUnits.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
:G4UserRunAction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
}



void RunAction::BeginOfRunAction(const G4Run*)
{      
    G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();    
    analysisManager->SetActivation(true);
        analysisManager->SetFileName("Result.csv");
        analysisManager->OpenFile();
//        analysisManager->CreateH2("elctScatAna","scattering", 5000,9*MeV,18*MeV,1000,-1,1);
        analysisManager->CreateH1("elctScatAna","scattering", 5000,9*MeV,18*MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run*)
{
  // compute and print statistic 
  //if (isMaster) fRun->EndOfRun();
             
  //save histograms      
  G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();
  if ( analysisManager->IsActive() ) {
    analysisManager->Write();
    analysisManager->CloseFile();
  }    
  
  // show Rndm status
  if (isMaster)  G4Random::showEngineStatus(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
