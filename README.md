# Ray Tracing Simulator (SDL3, C++)

A simple 2D ray tracing simulation built using SDL3. This project visualizes rays emitted from a light source interacting with an obstacle (circle).

## Features

* Interactive light source (controlled via mouse)
* Multiple rays emitted from a single point
* Ray-circle intersection (basic obstruction)
* Real-time rendering using SDL3
* Clean modular structure (Ray, Circle, rendering functions)

## Preview

### Demo

```md
![Demo](assets/demo.mp4)
```

---

### Screenshots

| Ray Simulation                 |
| -----------------------------  |
| ![Output](assets/output.jpg)   |
---

The simulation displays:

* A light source emitting rays in multiple directions
* A circular obstacle blocking the rays
* Rays stop when they intersect with the obstacle

## Tech Stack

* Language: C++
* Graphics Library: SDL3

## Project Structure

```
Ray-Tracing-Simulator/
│
├── main.cpp
├── src/
│   ├── include/        # SDL headers
│   └── lib/            # SDL libraries
│
├── assets/
│   ├── demo.mp4        #  demo recording
│   └── output2.jpg     # screenshot
│
├── README.md
└── SDL3.dll            #Linker
```

### Code Structure

* `Ray` class → Represents individual rays
* `Circle` class → Represents objects (light source + obstacle)
* `setlines()` → Initializes rays with endpoints
* `drawlines()` → Handles ray rendering and collision logic
* `drawcircle1()` → Renders light source
* `drawcircle2()` → Renders obstacle
* `main()` → Entry point and event loop

## How It Works

* Rays originate from a source (first circle)
* Each ray is extended toward a random endpoint on screen edges
* If a ray intersects the obstacle (second circle), it stops at the intersection point
* Otherwise, it continues to its endpoint

## Current Implementation

* Rays are generated using multiple random endpoints
* No strict angular distribution yet

## Future Improvements

* Uniform angular distribution of rays (true radial emission)
* Ray reflection / bouncing
* Multiple obstacles
* Better collision precision
* Performance optimizations (spatial partitioning, etc.)

## Installation & Setup

### Requirements

* C++ compiler (G++)
* SDL3 installed (include + lib folders)

### Compilation (Windows)

```bash
g++ main.cpp -o main.exe -I src/include -L src/lib -lsdl3
```

### Run

```bash
./main.exe
```

## SDL3 Cross-Platform Note

SDL (Simple DirectMedia Layer) is a **cross-platform library**. It supports:

* Windows
* Linux
* macOS


## Controls

* Mouse movement → Moves the light source

## Learning Value

This project demonstrates:

* Basic ray casting principles
* Geometry (line-circle intersection)
* Real-time rendering
* SDL event handling

## Why This Project Matters

Even though ray tracing is often associated with game engines, this project is valuable for:

* Understanding graphics fundamentals
* Building problem-solving skills in geometry
* Strengthening low-level rendering knowledge

## Author

* Aditya Chauhan

---

Feel free to fork, modify, and extend this project 🚀
