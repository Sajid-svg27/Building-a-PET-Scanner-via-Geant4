import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# --- SETTINGS MATCHING YOUR C++ CODE ---
MIN_ENERGY = 0.0   # MeV
MAX_ENERGY = 0.6   # MeV
NBINS = 100        # Number of bins
BIN_WIDTH = (MAX_ENERGY - MIN_ENERGY) / NBINS

filename = "Output_h1_0.csv"

try:
    # 1. Read the CSV, skipping the comment lines (#)
    #    The file has a header row: "entries, Sw, Sw2..."
    df = pd.read_csv(filename, comment='#')

    # 2. Extract the 'entries' column (This is your Y-axis: Counts)
    #    We strip any whitespace from column names just in case
    df.columns = df.columns.str.strip()
    counts = df['entries']

    
    #    We create an array of energy values corresponding to each row
    #    We use the center of the bin for plotting
    energies = np.linspace(MIN_ENERGY + BIN_WIDTH/2, MAX_ENERGY - BIN_WIDTH/2, len(counts))

    # 4. PLOT
    plt.figure(figsize=(10, 6))
    
    # Plot bars
    plt.bar(energies, counts, width=BIN_WIDTH, color='green', alpha=0.7, edgecolor='black', linewidth=0.5)

    # Add labels and formatting
    plt.title("PET Simulation: Energy Deposition Spectrum")
    plt.xlabel("Energy (MeV)")
    plt.ylabel("Counts")
    plt.grid(True, alpha=0.3)
    
    # Add a marker for where the 511 keV peak SHOULD be
    plt.axvline(x=0.511, color='red', linestyle='--', label='511 keV Limit')
    plt.legend()

    # Save and Show
    output_file = "Final_Spectrum.png"
    plt.savefig(output_file)
    print(f"Success! Plot saved as {output_file}")
    plt.show()

except Exception as e:
    print(f"Error: {e}")
    print("Tip: Make sure the file 'Output_h1_0.csv' is in the same folder.")