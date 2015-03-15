## Pep/8 CPU simulator ##

This repository is for the source code of the Pep/8 CPU simulator for use with the textbook _Computer Systems_. The application is written in C++, is GUI-based, and is compiled with the Qt 4 development environment using the Qt Creator IDE available from Nokia at http://www.qtsoftware.com/downloads/ .

The complete rewrite of Pep8CPU is complete, and a release is upcoming! Because we want to provide an executable without external dependencies (for OSX and Windows; Linux users can get Qt libraries (and probably already have them!) from repositories) we will be uploading once we rediscover the voodoo that is statically compiling Qt on Windows.

Please send comments, bug reports, and feature requests to [Stan Warford](http://www.cslab.pepperdine.edu/warford/index.html).

The CPU simulator is an implementation of the data section of the Pep/8 CPU as shown in Figure 12.2 of the textbook.
It features color-coded display paths that trace the data flow depending on control signals to the multiplexers,
a single-cycle mode of operation with GUI inputs for each control signal and instant visual display of the effects of the signal,
and a multi-cycle mode of operation with an integrated text editor for the student to write Mc2 microcode sequences and execute them to implement ISA3 instructions.

  * [Pep8CPU46Win.zip](http://pep8-1.googlecode.com/files/Pep8CPU46Win.zip): Windows executable build for Pep/8 CPU simulator version 46

  * [Pep8CPU46MacPower.zip](http://pep8-1.googlecode.com/files/Pep8CPU46MacPower.zip): PowerPC Mac executable build for Pep/8 CPU simulator version 46

  * [Pep8CPU46MacTel.zip](http://pep8-1.googlecode.com/files/Pep8CPU46MacTel.zip): Intel Mac executable build for Pep/8 CPU simulator version 46

  * [Pep8CPU46.tar.gz](http://pep8-1.googlecode.com/files/Pep8CPU46.tar.gz): Source code for Pep/8 CPU simulator version 46

pep8cpu is one of several software support packages for the textbook
_Computer Systems_, J. Stanley Warford, fourth edition,
Jones & Bartlett, Publishers, 2010.
The program source is maintained at this site, but the downloads are posted with the other support packages at http://code.google.com/p/pep8-1/ .

