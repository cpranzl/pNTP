# pNTP

## Particle based LED-Matrix NTP clock 

#### ```/src``` folder:  
This is the source folder that contains the firmware files. It should *not* be renamed. Anything that is in this folder when you compile pNTP will be compiled into a firmware binary for the Particle device that is targeted.

#### ```.ino``` file:
This file is the firmware run as the primary application on the Particle device. It contains a `setup()` and `loop()` function.

#### ```project.properties``` file:  
This is the file that specifies the name and version number of the libraries that pNTP depends on.

## Compiling pNTP

When you're ready to compile pNTP, make sure you have the correct Particle device target selected and run `particle compile <platform>` in the CLI or click the Compile button in the Desktop IDE.
