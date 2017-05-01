# Terminally Tetris
Tetris for your Terminal. Visit our [github page](https://thecardkid.github.io/terminally-tetris/) for more info.

## Installation

### OSX (Homebrew)
```
$ brew tap thecardkid/homebrew-ttetris
$ brew install terminally-tetris
$ ttetris
```

## Seeing is believing
![demo](docs/gameplay.gif)

## Build from source

### Install Dependencies (`ncurses`)

OSX: `$ brew install ncurses`

Ubuntu: `$ sudo apt-get install ncurses5-dev`

### Clone the repo
`$ git clone https://github.com/thecardkid/terminally-tetris`

### Build source code
`$ cd terminally-tetris && make`

### Move the executable to `$PATH`
`$ mv build/ttetris /usr/local/bin`

I assumed that `/usr/local/bin` is part of your `$PATH`. If not:

- `$ echo $PATH` and then
- `mv` the executable into any of the `:` delimited directories

### Play
`$ ttetris`

## Co-Authors

- [Daniel Bishop](https://github.com/Daniel6)
- [Rachel Yang](https://github.com/RachelYang02)
- [Shane Kelly](https://github.com/shanek21)

## License

MIT License

Copyright (c) [2017] [Hieu Nguyen et. all]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
