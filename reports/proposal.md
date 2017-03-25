#Proposal
**Bombasstic Bamboo**

Daniel Bishop, Shane Kelly, Hieu Nguyen, Rachel Yang

## Project Goal
The primary goal of this project is to write a C implementation of the game Tetris. We will be developing the core game in C and handling rendering using ASCII art in a terminal. The minimum viable product that we are aiming for is a stripped down version of Tetris in which a player can move and rotate blocks according to the game rules, and see the game state via a graphical display in the terminal. Further goals include an OpenGL renderer and a scoring and scaling difficulty system. The possibility of developing multiplayer functionality is a far stretch goal.


## Design choices
*Demonstrate that you have acquired the knowledge you need to get started.  We will know that you have this knowledge if the text of the proposal uses domain language effectively to convey ideas clearly and concisely.*

- Terminal Tetris
  - Our MVP is a version of Tetris that runs in the terminal, controlled by a C codebase. We will be careful to separate out controller logic from the view logic, such that we can later on replace ascii art with OpenGL for a more immersive experience. The program will take in a flag `-g` to run with the graphics package.

- Decision on using OpenGL
  - OpenGL abstracts away the lowest level graphics operations, providing wrapper functions which manage geometric primitives (points, lines, and polygons). Manipulating the geometric primitives directly would probably be reasonable for our application. OpenGL’s documentation is suitable for our purposes.
 
- Model-View-Controller Architecture
  - Our codebase will be in both C and C++. We will use C for controlling the game state, and C++ for graphics. The two components will communicate as follows: the view will send user input (e.g. keypresses) to the controller, and the controller will send game state diffs (square colors) back. We send diffs to optimize re-rendering: we simply do not care about cells that did not change color.

## Annotated Bibliography
*Demonstrate that you have assembled the resources you need to get started.  One good way to do that is to include an annotated bibliography with a pointer to each resource and a few sentences that describe the content.*

[OpenGL Matrices] (http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/)This tutorial, part of a series of tutorials for OpenGL, explains the cumulation of basic matrix translations and transformations, and provides a structure for Model, View, and Projection matrices to separate out the transformations in a clean and effective manner.

[Tetris game algorithm] (http://gaming.stackexchange.com/questions/13057/tetris-difficulty) This source contains details about how Tetris handles difficulty levels and block spawning.

[`fflush` documentation] (http://man7.org/linux/man-pages/man3/fflush.3.html) This website contains documentation for the `fflush` method that we will need to clear the current display every time the game state updates and a rerender is called.

## Product Backlog
[Our Trello board.] (https://trello.com/b/98M6BDsY/softsysbombassticbamboo)
       
## Potential Roadblocks
We have a decent sense of direction for this stage of the project, but we will let you know if any show-stopping questions arise.

