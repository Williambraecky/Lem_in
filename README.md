# Lem_in

This is a pathfinding project in C.

The goal of this project is to move a certain amount of ants from point ##start to point ##end using the smallest steps possible.

# Rules

- An ant may move only once per line
- A point may only contain one ant at a time except for point ##start and ##end

# How did we do?

Since point coordinates have no significant value, some pathfinding algorithms aren't useful (a* for example).

We used a modified dijkstra algorithm (which is effectively a bfs-algorithm since there is also no movement cost) to handle negative links which is used to handle multiple path at the same time.

Everything has been thought to have the best performance possible as well as low memory usage (feel free to pr suggestions), as for all pathfinding algorithms it doesn't always find THE shortest(s) paths but it will be very close.

# Usage

- Compile the project using the make command (has only been tested on macos)
- Execute the executable by piping (or redirecting) a valid lem_in file inside of it
- Options are (all optional):
  - [-a number]: Defines the maximum length for a path
  - [-n number]: Defines the maximum number of path to be used
  - [-m file]: Defines a map file without piping
  - [-s]: Shows multiple information at the end of the pathfinding
  - [-h]: Do not show ant movement
  - [-r]: Reverse the algorithm; Instead of finding paths from the start point, start from the end point (useful for randomly generated maps)
  - [-d file]: Defines a "dictionary" for the ants name, by default they will be named 1, 2, 3, ... (one name per line)
