# Rubik’s cube in C
## Software Systems Spring 2017
### [Hieu Nguyen](https://github.com/thecardkid) [David Papp](https://github.com/davpapp) [Philip Seger](https://github.com/segerphilip) [Sarah Walters](https://github.com/sarahwalters)
This project uses depth first search, threading, and OpenGL to solve and display a Rubik’s cube in C/C++.

## Rubik’s cube algorithms
Unsurprisingly, depth first search is not the most efficient algorithm for solving a Rubik’s cube. Many individuals have done work to solve a cube in [52 moves](https://www.jaapsch.net/puzzles/thistle.htm) or near-perfect with only [20 moves](http://kociemba.org/cube.htm). With both of these approaches, searching is used to try theoretical moves and find the optimal solution from large lookup-tables. With our depth-first search implementation, we follow a similar idea. We create nine threads (one for each face move), and run depth-first search from the new individual cube state. If a solution is found within a max depth, the solution is returned and timed. This means that the number of moves and the time each took are shown so the user can choose their own solve method.

## Implementation
The project consists of four major components: an object-oriented Rubik’s cube API written in C++, graphics written in OpenGL with C++, a multi-threaded depth-first search solver written in C, and a connector library written in C++ which allows the multi-threaded solver to “try” Rubik’s cube moves using the object-oriented API.

### _Cube API_
We wanted to write the cube API in C++ to simplify rotation -- the cube API is a wrapper around an array, and manipulating the array directly to rotate the cube is a little complicated. With object orientation, we were able to tuck all of the rotation complexity away into a RubiksCube class with a single rotate method.

### _Graphics_
We chose to use [OpenGL](http://www.glprogramming.com/red/chapter01.html), a library which provides useful abstractions on top of low-level graphics programming, to render the cube. In theory it would’ve been possible to render the cube directly in C; however, it’s easier to model, display, and manipulate multi-part three-dimensional objects like Rubik’s cubes with the aid of OpenGL’s abstractions. For instance, OpenGL provides a “camera” which is useful for switching perspective, used in our program to rotate the user’s “eye” relative to the cube. It also handles double-buffering for smooth animation.

The graphical implementation models the Rubik’s cube as a collection of twenty-seven individual cubelets. The geometry of each cubelet is defined by its eight corner vertices. Graphics hardware is designed to render triangles, so each cubelet is drawn using twelve triangles -- two for each of the six square faces.

### _Solving algorithms vs. DFS_
We strayed away from solving cubes algorithmically, the way one would in real life. This approach would have consisted of tediously hard-coding simple patterns. Furthermore, this approach could not have been used to generalize to larger cubes.  Computationally, an algorithmic approach would be orders of magnitude faster than DFS, but might not find the optimal solution (meaning the fewest number of moves).
Since some scrambled cubes might take as many as 20 moves to solve, there are over 43 quintillion solutions and thus DFS will not always find a solution in a reasonable amount of time. However, DFS allowed us to learn and implement threading. Threading and DFS also required us to be careful with memory management, which we realized after various segmentation faults and erratic behavior between threads.

### _Multi-threading_
We also wanted to investigate threading and implement our algorithm in such a way that threading would be possible. We started our implementation using [pthread](https://computing.llnl.gov/tutorials/pthreads/) to create a new thread for an individual face move, such that thread 0 would start with the current cube state except for one face rotated, thread 1 would start with the current cube state except the second face would be rotated, and so on. Before and after a thread is started, we take the value of [clock](http://www.gnu.org/software/libc/manual/html_node/CPU-Time.html) and use the difference between the two values and the clock speed of the computer hardware to compute how much CPU time was used for a thread to complete.

### _Connector library_
We chose to write the cube API in C++ and the solver in C. To give the solver the ability to “try” moves, we wrote a shared library which exposes a C-compatible wrapper around the Rubik’s cube rotation function. The shared rotate function transforms takes as arguments an underlying state array to transform and a move to perform. It initializes a Rubik’s cube with the underlying state, performs the rotation (thereby modifying the underlying state), and throws away the Rubik’s cube.

## Results
![rubik.gif](reports/resources/cube_solving.gif)

Running our program ([found here](https://github.com/thecardkid/SoftSysAsocialAardvark)), a user is able to manipulate the cube, scramble it, and solve it. The solution (with both the moves and the time the thread took to complete) is printed to console. As an example, thread #5 on our test ran for 0.000628s and solved the cube in 6 moves (a more complex scramble would take longer).  If we had more time for this project, our stretch goals included extending our implementation to support cubes of larger size (theoretically to nxnxn) and using different solve algorithms with threading to show performance differences (in terms of moves and CPU time).
