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
#include "DetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Element.hh"
#include "G4Material.hh"

namespace B1
{

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();

  // --- 1. Define Materials (The Bulletproof Way) ---
  G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* water = nist->FindOrBuildMaterial("G4_WATER");
  
  // MANUAL DEFINITION OF LSO (Lutetium Oxyorthosilicate - Lu2SiO5)
  // We define this manually so we don't rely on the NIST database working.
  G4double a, z, density;
  G4String name, symbol;
  G4int ncomponents, natoms;

  // Define Elements
  G4Element* elLu = new G4Element("Lutetium", "Lu", z=71., a=174.97*g/mole);
  G4Element* elSi = new G4Element("Silicon", "Si", z=14., a=28.09*g/mole);
  G4Element* elO  = new G4Element("Oxygen",  "O",  z=8.,  a=16.00*g/mole);

  // Define Material
  G4Material* lso_mat = new G4Material("LSO_Crystal", density=7.4*g/cm3, ncomponents=3);
  lso_mat->AddElement(elLu, natoms=2);
  lso_mat->AddElement(elSi, natoms=1);
  lso_mat->AddElement(elO,  natoms=5);

  // --- 2. World Volume ---
  G4double world_size = 1.0*m;
  auto solidWorld = new G4Box("World", 0.5*world_size, 0.5*world_size, 0.5*world_size);
  auto logicWorld = new G4LogicalVolume(solidWorld, air, "World");
  auto physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0, true);

  // --- 3. The Phantom (Water Cylinder) ---
  auto solidPhantom = new G4Tubs("Phantom", 0, 10*cm, 20*cm, 0, 360*deg);
  auto logicPhantom = new G4LogicalVolume(solidPhantom, water, "Phantom");
  new G4PVPlacement(nullptr, G4ThreeVector(), logicPhantom, "Phantom", logicWorld, false, 0, true);

  // --- 4. The PET Detector Ring ---
  G4int nCrystals = 60;
  G4double ringRadius = 30*cm;
  
  G4double cryst_dX = 1.5*cm; 
  G4double cryst_dY = 3.0*cm; 
  G4double cryst_dZ = 5.0*cm; 

  auto solidCrystal = new G4Box("Crystal", 0.5*cryst_dX, 0.5*cryst_dY, 0.5*cryst_dZ);
  // Use our manually created material 'lso_mat'
  auto logicCrystal = new G4LogicalVolume(solidCrystal, lso_mat, "Crystal");

  // Place 60 copies
  for (G4int i = 0; i < nCrystals; i++) {
      G4double phi = i * (360*deg / nCrystals); 
      
      G4double x = ringRadius * std::sin(phi);
      G4double y = ringRadius * std::cos(phi);
      G4ThreeVector pos(x, y, 0);

      G4RotationMatrix* rot = new G4RotationMatrix();
      rot->rotateZ(-phi); 

      new G4PVPlacement(rot, pos, logicCrystal, "Crystal", logicWorld, false, i, true);
  }

  // --- 5. IMPORTANT: Set Scoring Volume ---
  // (Setting this prevents other parts of the code from getting confused)
  fScoringVolume = logicCrystal;

  return physWorld;
}

}