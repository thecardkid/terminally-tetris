# Preliminary Report

**Bombasstic Bamboo**

Daniel Bishop, Shane Kelly, Hieu Nguyen, Rachel Yang

## Project Goal
The primary goal of this project is to write a C implementation of the game Tetris. We will be developing the core game in C and handling rendering using ASCII art in a terminal. The minimum viable product that we are aiming for is a basic version of Tetris with the following features:
- A complete set of tetrominos as usable blocks
- Movement and rotation of blocks according to Tetris rules
- Scoring system
- Preview of next block that will appear
- In-game menu and pausing
- Command line rendering using ncurses library
- Ability to disguise game as innocent stdout

Some stretch goals include:
- OpenGL rendering system
- Block "holding" mechanic
- Local multiplayer "battle" mode
- Sound effects

## Completed Work Items
| Work Item | Feature Branch  |
|:------------|:-----------------|
| Block factory | [hn/block-factory](https://github.com/thecardkid/SoftSysBombassticBamboo/tree/hn/block-factory)|
| Collision detection and lateral movement | [db/movements-v2](https://github.com/thecardkid/SoftSysBombassticBamboo/tree/db/movements-v2)
| Block rotations | [ry/block-rotation](https://github.com/thecardkid/SoftSysBombassticBamboo/tree/block-rotation)
| User input | [sk/pause-quit](https://github.com/thecardkid/SoftSysBombassticBamboo/tree/sk/pause-quit)
| Row clearing | [hn/row-clear](https://github.com/thecardkid/SoftSysBombassticBamboo/tree/hn/row-clear)
| Scoring | [hn/scoring](https://github.com/thecardkid/SoftSysBombassticBamboo/tree/hn/scoring)
| Game end state | [db/endgame](https://github.com/thecardkid/SoftSysBombassticBamboo/tree/db/endgame)
| Block preview | [hn/display-next](https://github.com/thecardkid/SoftSysBombassticBamboo/tree/hn/display-next)
| Boss mode | [hn/boss-mode](https://github.com/thecardkid/SoftSysBombassticBamboo/tree/hn/boss-mode)

## Preliminary Results
[releases/preliminary](https://github.com/thecardkid/SoftSysBombassticBamboo/tree/releases/preliminary)
### Quickstart
```
git clone -b releases/preliminary git@github.com:thecardkid/SoftSysBombassticBamboo.git
cd SoftSysBombassticBamboo
make
```

## Project Issue Tracker
[Trello board](https://trello.com/b/98M6BDsY/softsysbombassticbambo)

## Potential Roadblocks
The team is making good progress and has not identified any major roablocks preventing execution of minimum project goals. The identification of blockers in achieving stretch goals has not yet been assessed.

## Annotated Bilbiography
[OpenGL Matrices](http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/)This tutorial, part of a series of tutorials for OpenGL, explains the cumulation of basic matrix translations and transformations, and provides a structure for Model, View, and Projection matrices to separate out the transformations in a clean and effective manner.

[Tetris game algorithm](http://gaming.stackexchange.com/questions/13057/tetris-difficulty) This source contains details about how Tetris handles difficulty levels and block spawning.

[`ncurses` documentation](http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/) This website contains documentation for the `ncurses` method package.

