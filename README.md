# HW5 - Dijkstra's Shortest Path Algorithm

This C++ project implements a directed graph, a better priority queue, and Dijkstra's shortest-path algorithm.

## Compile

Open a terminal in the folder containing the `.cpp` and `.h` files and the `Makefile`.

Run:

```bash
make
```

This creates three executables:

- `graph-tests` — tests the Graph class
- `bpq-tests` — tests the BetterPriorityQueue class
- `dijkstra` — tests Dijkstra's algorithm

## Run the Tests

Run each program separately:

```bash
./graph-tests
./bpq-tests
./dijkstra
```

Or run all three using:

```bash
make run
```

## Clean

To remove the compiled executables, run:

```bash
make clean
```

## Requirements

- A C++ compiler (`g++`)
- `make`

No external C++ libraries are required.
