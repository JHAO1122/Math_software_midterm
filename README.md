# This is the README file for the project "Conway's Game of Life" 
## The purpose of the program
Implement the project "Conway's Game of Life" by C language and visualize it.
## The functions of the program
1. Implement Random Initialization of the World for Conway's Game of Life
2. Implement Initialization of the World Using an Input RLE File for Conway's Game of Life
3. Implement Dynamic Update Process of Conway's Game World
4. Implement Exit Functionality for Conway's Game of Life
5. Implement Saving Current Game State as a BMP File for Conway's Game of Life
6. Implement Doxygen Comment Documentation HTML File for Conway's Game of Life and Directly Display It
7. Implement Visualization of Conway's Game of Life
8. Implement a Makefile for Compiling, Running, Generating Documentation, and Cleaning Up Files for Conway's Game of Life
## The methods of use
1. Compilation: In the terminal, navigate to the project directory ass02 and run the make command to compile the program.
Running the Program:
2. To initialize the world with a specific size, run the command ./conway number1 number2, where number1 and number2 represent the dimensions of the world.
To initialize the world using an RLE file, run the command ./conway number1 number2 filename, where filename is the name of the RLE file.
3. Saving the Current State: Press the s key to save the current game state as world.bmp.
4. Exiting the Game: Press the q key to exit the game.
5. Generating Documentation: Run the command make doc to generate Doxygen comment documentation.
6. Cleaning Intermediate Files: Run the command make clean to remove intermediate files.
7. Cleaning All Files: Run the command make clean-all to remove all intermediate files and generated documentation.
## The dependent relationships of the program
1. C Compiler: gcc
2. Make Tool: make
3. Doxygen Tool: doxygen
4. ncurses Library: ncurses
5. Live Server Plugin: live server plugin
6. xdg-utils Package: xdg-utils
