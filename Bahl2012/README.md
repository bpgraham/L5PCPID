# Bahl L5 PC model

NEURON code for the simulations presented in:



Graham, Bruce P. and Kay, Jim W. and Phillips, William A. (2025). Context-sensitive processing in a model neocortical pyramidal cell with two sites of input integration. Neural Computation 37:588-634. https://doi.org/10.1162/neco\_a\_01739



Graham, Bruce P. and Kay, Jim W. (under review). Inhibitory and neuromodulatory control of two-pathway signal integration in a model neocortical pyramidal cell. (preprint in bioRxiv at https://doi.org/10.1101/2025.04.21.649759)



These simulations are of the Bahl model of L5 pyramidal cell (Bahl, A., et al (2012). Journal of Neuroscience Methods, 210(1), 22-34. doi:10.1016/j.jneumeth.2012.04.006). Most of the code is from the Bahl repository on ModelDB, but with the addition of mod files for noisy current injection (IOU.mod) and an implementation of an Ih current with added leak (hl.mod; Migliore, M. and Migliore, R. (2012). PloS One 7(5):e36867).



To run, you may need to rebuild NEURON in the channels folder and adjust the link in **reduced\_model.hoc**.



Opening **run\_Bahl\_std.hoc** gives a GUI from which you can run individual simulations covering many of the situations presented in the above two papers by Graham et al. Note that to run simulations with Ih and added leak, you need to uncomment the appropriate link near the top of run\_Bahl\_std.hoc (and possibly the link to the NEURON library in reduced\_model\_hl.hoc).





