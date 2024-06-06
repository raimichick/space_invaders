# space_invaders

CS467 final project

## How to Run:

### Download the Latest Release

Navigate to the releases page and download the .zip archive for your platform and extract to a folder. To be able to run
space invaders with this program, a ROM of the original game is required. This is not provided by the project and must
be obtained through other sources. The ROM can be found online as invaders.e, .f, .g, and .h. These should be cat'd 
together, labeled "invaders_combined" and put in the "include" directory. 

### Windows

From Release: Navigate to the executable directory and run space_invaders_8080.exe

Build from source: 
1. Clone or download a zip of the Github repo.
2. Ensure the ‘main’ branch is checked out.
3. Copy the game ROM into the ./include folder. Label it “invaders_combined”.
4. Load the CMakeLists.txt file in the root directory.
5. Run.

### Apple

From Release: Navigate to the executable directory and run space_invaders_8080

Build from source:
1. Clone or download a zip of the Github repo.
2. Ensure the ‘main’ branch is checked out.
3. Copy the game ROM into the ./include folder. Label it “invaders_combined”.
4. Install the following through homebrew:
   - SDL2: `brew install sdl2`
   - SDL2_mixer: `brew install sdl2_mixer`
   - SDL2_image: `brew install sdl2_image`
5. Load the CMakeLists.txt file in the root directory.
6. Run.

### Linux

To run Space Invaders on a Linux machine, the SDL2, SDL2-image, and SDL2_mixer library dependencies need to be installed. These can
be installed through the package manager for your distribution. Consult the package manager for the exact package names,
as these can differ between distributions. Before installing any new packages on a linux machine, it is recommended to
update the system. Consult your distribution’s documentation for how to do this, as this can differ between
distributions. On Debian based systems, the following command will update the package repository and install any pending
system updates.

`sudo apt update && sudo apt upgrade -y`

Once the system is up-to-date, the dependencies can be installed. The following command will install the necessary
packages on most debian based distributions

`sudo apt install libsdl2-2.0-0 libsdl2-mixer-2.0-0 libsdl2-image-2.0-0`

Once the necessary dependencies are installed the game can be launched. Navigate to the executable folder and run
space_invaders_8080. If this does not run by clicking on the program file, check that the permissions allow executing
the file as a program. If this is still not working, try launching the program by navigating to the folder in a terminal
and running

`./space_invaders_8080`


## Controls
Shoot the aliens, avoid getting shot, don’t let the aliens reach the bottom of the screen.

| Key                         | Action          | Description                                      |
|-----------------------------|-----------------| ------------------------------------------------ |
| ‘C’\*                       | Insert coin\*   | Inserts a coin to start the game.\*              |
| ‘1’                         | Player 1 start  | Starts the game for player 1.                    |
| ‘2’                         | Player 2 start  | Starts the game for 2 players. Player 1 begins.  |
| ‘Space’, 'Up Arrow', or 'F' | Shoot           | Fires the player’s weapon.                       |
| ‘Left Arrow’ or 'W'         | Move left       | Moves the player’s ship to the left.             |
| ‘Right Arrow’ or 'D'        | Move right      | Moves the player’s ship to the right.            |
| ‘L’                         | Number of lives | Increment the bonus life (base 3, up to 6).      |
| ‘T’                         | Tilt            | Activates the tilt button.                       |
| ‘B’                         | Bonus life      | Toggle bonus life point target between 1000/1500 |
| ‘I’                         | Coin info       | Toggles coin information.                        |
| ‘Q’                         | Quit            | Exits the game.                                  |
*Note that the first time you hit ‘C’ it doesn’t register.

## Settings

See the settings.h file to adjust window size and background options. 