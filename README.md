# Terminally Tetris
Tetris for your Terminal
Olin College of Engineering - Software Systems Final Project: SoftsysBombassticBamboo

## Seeing is believing
![demo](docs/demo.gif)

## Dev dependencies
**Ncurses**

Ubuntu: `sudo apt-get install libncurses5-dev`

Mac: `brew install homebrew/dupes/ncurses`

## Build from source

- First clone the repo `git clone https://github.com/thecardkid/terminally-tetris`
- Then build the source code `cd terminally-tetris && make`
- Move the executable `mv build/ttetris /usr/local/bin` (I assume here that `/usr/local/bin` is part of your `$PATH`. If not:
  - echo `$PATH`
  - `mv` the executable into any of the `:` delimited directories
- Play with `ttetris`

## Co-Authors

- [Daniel Bishop](https://github.com/Daniel6)
- [Rachel Yang](https://github.com/RachelYang02)
- [Shane Kelly](https://github.com/shanek21)