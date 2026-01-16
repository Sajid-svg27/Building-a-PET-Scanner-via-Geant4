# Geant4 PET Detector Simulation

A high-fidelity Geant4 simulation of a Positron Emission Tomography (PET) detector ring. This project simulates the interaction of 511 keV gamma rays with Lutetium Oxyorthosilicate (LSO) crystals, featuring 3D visualization and energy spectrum analysis to verify detector physics.

![Detector Visualization] https://github.com/Sajid-svg27/Building-a-PET-Scanner-via-Geant4/blob/main/Detector_Geometry.png?raw=true


## 🚀 Key Features
* **Custom Geometry:** Detailed simulation of a PET scanner ring composed of LSO crystals ($Z=71$, density 7.4 g/cm³).
* **Physics Validation:** Verified 511 keV Photoelectric peak confirming material density and absorption properties.
* **3D Visualization:** Full rendering of the detector geometry, water phantom, and particle trajectories.
* **Data Analysis:** Automated Python scripts to extract and plot energy deposition spectra from Geant4 CSV output.
* **Phantom Integration:** Includes a water phantom to simulate scattering events (Compton continuum).

## 🛠️ Prerequisites
* **Geant4** (v10.0 or later)
* **CMake** (v3.0 or later)
* **Visual Studio** (C++ Compiler)
* **Python 3.x** (with `matplotlib` and `pandas` for plotting)

## 📦 Installation & Build

    
2.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```
3.  **Run CMake:**
    ```bash
    cmake ..
    ```
4.  **Build the Project:**
    Open the generated `.sln` file in Visual Studio and click **Rebuild Solution**, or run:
    ```bash
    cmake --build . --config Release
    ```

## 🖥️ Usage

### 1. Visual Mode (3D Visualization)
To view the detector geometry and particle tracks in 3D:
1.  Run the executable `exampleB1.exe`.
2.  Execute the visualization macro:
    ```bash
    /control/execute my_run.mac
    ```
*This will render the LSO ring, the phantom, and the gamma ray trajectories in the Geant4 viewer.*

### 2. Scientific Mode (Spectrum Analysis)
To generate the Physics Validation Graph (511 keV peak):
1.  Execute the physics macro (high-speed, no graphics):
    ```bash
    /control/execute spectrum.mac
    ```
    *This simulates 10,000 events where 511 keV gammas are shot directly at the crystals.*
2.  This generates an output file named `Output_h1_0.csv`.
3.  Run the Python script to plot the data:
    ```bash
    python plot_fixed.py
    ```

## 📊 Results & Validation

### Energy Spectrum Analysis
The simulation successfully reconstructs the energy deposition spectrum for LSO.
* **Photoelectric Peak:** Clearly visible at **0.511 MeV**, confirming total energy absorption in the crystals.
* **Compton Continuum:** Low-energy scattering events caused by interactions with the water phantom and partial energy deposition.

![Energy Spectrum]https://github.com/Sajid-svg27/Building-a-PET-Scanner-via-Geant4/blob/main/PET_Energy_Spectrum.png?raw=true


## 📂 Project Structure
* **`DetectorConstruction.cc`**: Defines the LSO material and Ring Geometry.
* **`RunAction.cc`**: Handles data initialization and CSV file creation.
* **`EventAction.cc`**: Records energy deposition per event.
* **`my_run.mac`**: Macro for 3D visualization and geometry checks.
* **`spectrum.mac`**: Macro for high-statistics physics runs (aims gun at crystal).
* **`plot_fixed.py`**: Python analysis tool for generating the energy spectrum plot.

## 🤝 Contributing
Contributions are welcome! Please fork the repository and submit a pull request for any improvements to the physics list or geometry.

## 📜 License
This project is open-source and available under the MIT License.
