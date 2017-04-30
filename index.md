# Terminally Tetris
## Software Systems Spring 2017
### [Hieu Nguyen](https://github.com/thecardkid) [Daniel Bishop](https://github.com/Daniel6) [Shane Kelly](https://github.com/shanek21) [Rachel Yang](https://github.com/RachelYang02)
Play Tetris in your terminal and disguise it as actual work!

## What is Terminally Tetris?
Terminally Tetris is a basic implementation of the popular game, Tetris, with a little extra. Terminally Tetris ships with the ability to pause and replace the game's visuals with the output of a package being installed. We call this "boss mode" as it serves as a quick way to diguise your tomfoolery from curious eyes. Terminally Tetris is designed to be lightweight, capable of starting and exiting at a moment's notice in order to avoid detection.

## Implementation
Terminally Tetris is written entirely in the C language.

### _Tetromino Movement_
Tetrominos can move at variable speeds that are directly tied to the framerate of the game. By default, the game renders at 60fps, and a Tetromino will move towards the bottom of the stage every 48 frames. As the difficulty of the game increases, this number decreases to a minimum of 1 (Tetrominos move at every frame). Although the game can be modified to run at higher frequencies, this would only affect inpout handling which occurs on each render frame.

Valid Tetromino movements are all lateral directions, and counter/counter clockwise rotations. Not all of these movements are used in the game, but support for them exists.

A special movement exists for dropping Tetrominos which instantly moves the Tetromino as far down as it can go. This lets the player quickly finalize the position of the Tetromino without having to make repeated downwards inputs or wait for the Tetromino to fall on its own.

Internally, Tetromino movements are represented by a movement structure, which contains information on the net movement of a Tetromino. During normal gameplay, movement should not exceed 1 unit in any direction and 1 rotation, although programmatically there is no limit. Exceeding these limits will yield jittery movement, but will not interfere with collision detection.

### _Tetromino Collision_
Any time a movement is applied to a Tetromino, the new position of the Tetromino is checked to make sure that the Tetromino remains within the game boundaries and is not moving into a space that is occupied by another Tetromino. Since a movement can be a combination of lateral and rotational movements, each sub-move of a movement is applied separately to the Tetromino and checked for validity. Once all possible sub-moves have been applied, the new position is finalized and rendered. The hierarchy in which sub-moves are applied is:
1. Vertical
2. Horizontal
3. Rotational

If a Tetromino is unable to move down, it will still attempt to move horizontally or rotate. This allows for techniques such as [t-spins](http://tetris.wikia.com/wiki/T-Spin).

When a playable Tetromino attempts to move vertically as part of its movement but cannot execute the vertical movement, it becomes a non-playable Tetromino and triggers a score calculation plus a block spawning event. 

### _User Input_
User input is aggregated over a timespan after which a movement structure is generated and applied to the playable Tetromino. By default the aggregation period is 1 frame, but can be extended to accept inputs over a longer span. The purpose of aggregation is to combine multiple user inputs into 1 movement, cancelling out conflicting inputs such as move left and move right. The aggregation period should be a few frames in order to catch keys being pressed at almost the same time.

When user inputs generate a movement structure, the movement is applied to the playable Tetromino immediately, unlike the standard downwards progression of the piece. If the user movement includes a downwards portion, the Tetromino will reset its timer and wait another 48 frames (or however many the difficulty calsl for) before moving downwards again.

### _Tetromino Spawning_
When a new is spawned, it is chosen from the pool of [Tetromino types](http://tetris.wikia.com/wiki/Tetromino#The_Basic_Tetrominoes) with a bias against choosing the same type as the previous Tetromino. This new Tetromino is spawned above the top of the visible game area in a buffer zone, and is then moved down into the playable area by user input or the natural game progression.

The Tetromino to be spawned after the current one is also calcuated in the spawning process, and is displayed to the player to help them plan their moves in advance.

### _Tetromino Holding_
The player has the ability to remove a playable Tetromino and "hold" hold in reserve. Only one Tetromino may be held at a time, and there is a cooldown period after holding a Tetromino in which the hold function is disabled. When a hold action is made, the currently playable Tetromino is immediately removed from the field, and the Tetromino which was previously held is spawned. If no Tetromino was being held before, the Tetromino that would normally spawn next is spawned.

### _Scoring_
When a Tetromino comes to a rest, the rows which it is present in are checked for completion. If any of the rows are filled completely, they are cleared and points are added. More points are rewarded for clearing multiple rows at once. If clearing the rows results in an empty stage, an additional point reward is added.

Score bonuses are multiplied by a difficulty multiplier that increases as the game progresses. This is directly tied to the rate at which Tetrominos move downards without user input.

### _Ghosting_
Ghosting is a feature that displays the final position of the playable Tetromino if no further user inputs were made. This display aids in the horizontal positioning of the Tetromino.

### _Graphics_
Terminally Tetris uses the [ncurses](https://en.wikipedia.org/wiki/Ncurses) library to render itself as ASCII art in the terminal. Upon entering Boss Mode, it renders some sample output from package installation processes in its place.

## Results
![rubik.gif](reports/resources/cube_solving.gif)

Running our program ([found here](https://github.com/thecardkid/SoftSysAsocialAardvark)), a user is able to manipulate the cube, scramble it, and solve it. The solution (with both the moves and the time the thread took to complete) is printed to console. As an example, thread #5 on our test ran for 0.000628s and solved the cube in 6 moves (a more complex scramble would take longer).  If we had more time for this project, our stretch goals included extending our implementation to support cubes of larger size (theoretically to nxnxn) and using different solve algorithms with threading to show performance differences (in terms of moves and CPU time).
