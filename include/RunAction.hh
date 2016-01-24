#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4CsvAnalysisManager.hh"

class G4Run;

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
   ~RunAction();

  public:   
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
                                  
  private:
};

#endif

