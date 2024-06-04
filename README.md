# space_invaders

CS467 final project

## How to Run:

### Download the Latest Release

Navigate to the releases page and download the .zip archive for your platform and extract to a folder. To be able to run
space invaders with this program, a ROM of the original game is required. This is not provided by the project and must
be obtained through other sources. Once you have a Space Invaders ROM, ensure that the file is named "invaders_combined"
and place it in the "include" directory.

### Linux

To run Space Invaders on a Linux machine, the SDL2 and SDL2_mixer library dependencies need to be installed. These can
be installed through the package manager for your distribution. Consult the package manager for the exact package names,
as these can differ between distributions. Before installing any new packages on a linux machine, it is recommended to
update the system. Consult your distribution’s documentation for how to do this, as this can differ between
distributions. On Debian based systems, the following command will update the package repository and install any pending
system updates.

`sudo apt update && sudo apt upgrade -y`

Once the system is up-to-date, the dependencies can be installed. The following command will install the necessary
packages on most debian based distributions

`sudo apt install libsdl2-2.0-0 libsdl2-mixer-2.0-0`

Once the necessary dependencies are installed the game can be launched. Navigate to the executable folder and run
space_invaders_8080. If this does not run by clicking on the program file, check that the permissions allow executing
the file as a program. If this is still not working, try launching the program by navigating to the folder in a terminal
and running

`./space_invaders_8080`