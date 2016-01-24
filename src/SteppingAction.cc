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
/// \file electromagnetic/TestEm14/src/SteppingAction.cc
/// \brief Implementation of the SteppingAction class
//
// $Id: SteppingAction.cc 84208 2014-10-10 14:44:50Z gcosmo $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4VProcess.hh"
#include "G4RunManager.hh"
#include "G4CsvAnalysisManager.hh"
#include "G4Track.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction()
    :G4UserSteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
    const G4StepPoint* endPoint = aStep->GetPostStepPoint();
    //  G4String procName = endPoint->GetProcessDefinedStep()->GetProcessName();
    G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();

    const G4StepPoint* iniPoint = aStep->GetPreStepPoint();
    //scattered primary particle
    //
    G4int id = 0;
    if (aStep->GetTrack()->GetTrackStatus() == fAlive) {
        G4double e0 = endPoint->GetKineticEnergy();
        G4String pname = aStep->GetTrack()->GetDefinition()->GetParticleName();
        //    id = 2;
        G4ThreeVector d1 = iniPoint->GetMomentumDirection();
        G4ThreeVector d2 = endPoint->GetMomentumDirection();
        G4double cost1 = d1.x()*d2.x()+d1.y()*d2.y()+d1.z()*d2.z();
//        analysisManager->FillH2(id,e0,cost1);
        analysisManager->FillH1(id,e0);


        //    secondaries

        const std::vector<const G4Track*>* secondary = aStep->GetSecondaryInCurrentStep();
        for (size_t lp=0; lp<(*secondary).size(); lp++) {
            G4ParticleDefinition* p = (*secondary)[lp]->GetDefinition();
            if(p->GetParticleName()=="e-")
            {
                G4double e1 = (*secondary)[lp]->GetKineticEnergy();
                G4ThreeVector d3 = (*secondary)[lp]->GetMomentumDirection();
                G4double cost2 = d1.x()*d3.x()+d1.y()*d3.y()+d1.z()*d3.z();
//                analysisManager->FillH2(id,e1,cost2);
                analysisManager->FillH1(id,e1);
            }
        }
    }
    // kill event after first interaction
    //
    G4RunManager::GetRunManager()->AbortEvent();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


