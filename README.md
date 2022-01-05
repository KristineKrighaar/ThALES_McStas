# ThALES_McStas
 
 Authors: Kristine M. L. Krighaar (kristine.krighaar@nbi.ku.dk) and Kim Lefmann (lefmann@nbi.ku.dk)
 
 This simulation is meant to determine the energy resolution for the ThALES instrument using two different methods.
 1. res_sample and res_monitor to calculate the energy FWHM of the resolution ellipsoide. (SAMPLE=0)
 2. Simulation an energy vanadiumscan and determining the FWHM for the gaussian profile of the signal. (SAMPLE = 1)
 
 
 The Files:
 - Calculate_resolution.ipynb: jupyter notebook for data treatment of both sample types.
 
 - cov.py: Calculates and extracts information about the resolution ellipsoide from the res_sample and res_monitor
 
 - tas.py: Calls the cov.py script. Has to be included to to program structure.
 
 - Source_gen_silent.comp: Source component from the previous version of the instrument.
 
 - ThALES_resolution_v2.instr , .c, .out: Instrument files for the McStas simulation.
 
 - V_sample.comp: Vanadium sample component, used for SAMPLE=1
 
 - Eternal_Functions (folder): Python script for generalized chi**2 fitting 
