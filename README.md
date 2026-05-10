# GraphFlow-Lite

GraphFlow-Lite is a lightweight, header-only C++ library for modeling weighted graphs and running shortest-path analysis with Dijkstra's algorithm.

It is designed for quick integration into small and medium projects without requiring a build system dependency or external packages.

## Features

- Header-only design (`include/GraphFlow.hpp`)
- Directed and undirected weighted edge support
- Dijkstra shortest-path calculation with path reconstruction
- Simple API focused on readability and practical usage

## Project Structure

```text
GraphFlow-Lite/
├── include/
│   └── GraphFlow.hpp
├── examples/
│   └── main.cpp
└── README.md
```

## Quick Start

Compile and run the example from the project root:

```bash
g++ -std=c++17 -O2 examples/main.cpp -o example
./example
```

## Example Scenario

The example models a simple road network between:

- Erbil
- Duhok
- Zakho

Then it computes the shortest route from **Erbil** to **Zakho** using Dijkstra.

## API Overview

Main class:

- `graphflow::Graph`

Key methods:

- `addNode(node)`
- `addEdge(from, to, weight)`
- `addUndirectedEdge(a, b, weight)`
- `dijkstra(source, target)` which returns:
  - total distance
  - ordered path of nodes

## Requirements

- C++17 or newer
- Standard C++ library only (no third-party dependencies)

## License

You can add your preferred license file (for example MIT) based on your project needs.
