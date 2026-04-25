# Snake Game (C++ & Raylib)

This project is a classic Snake Game developed using C++ and the Raylib framework.

## Project Setup and Execution

This project utilizes the Raylib C++ Starter Template for Visual Studio Code on Windows.

1. Double-click the `main.code-workspace` file to open the template in Visual Studio Code.
2. From the Explorer Window in VS Code, navigate to the `src` directory and open the `main.cpp` file.
3. Press `F5` to compile and run the application.

### Video Setup Tutorial

For additional guidance on configuring Raylib with Visual Studio Code, refer to the following tutorial by Programming With Nick:
- [Video Tutorial on YouTube](https://www.youtube.com/watch?v=PaAcVk5jUd8)

---

## Current Progress and Features

### 1. Core Game Architecture
The project features a clean, class-based architecture utilizing Raylib. The codebase is organized into three primary classes to ensure a clear separation of concerns:

| Class | Responsibility |
|-------|----------------|
| `Snake` | Manages body state, movement direction, segment growth, and rendering. |
| `Food` | Handles texture loading, random position generation, and rendering. |
| `Game` | Orchestrates the interaction between the snake and food, including collision detection. |

### 2. Snake Class Implementation
- Utilizes `std::deque<Vector2>` for the snake's body, allowing efficient `push_front` (head addition) and `pop_back` (tail removal) operations for movement.
- The initial body is spawned at grid positions `{6,9}`, `{5,9}`, and `{4,9}`, comprising 3 segments facing right.
- **Growth Mechanic:** Implements an `addSegment` flag. When set to `true`, the tail is retained during an update cycle, effectively increasing the snake's length by one segment.
- **Rendering:** Each segment is drawn as a rounded rectangle (`DrawRectangleRounded`) using a bright neon green color.

### 3. Food Class Implementation
- Loads a custom food texture from `graphics/food.png`, resized to 20x20 pixels.
- **Collision-Aware Spawning:** The `GenerateRandomPos()` method iterates until it identifies a grid cell that is not occupied by the snake's body.

### 4. Game Class Implementation
- Manages instances of both the `Snake` and `Food` classes.
- Detects collisions between the snake's head and the food's position. Upon collision, it regenerates the food's position and triggers the snake's growth mechanic.

### 5. Main Game Loop
- **Window Specifications:** 600x600 pixels (20 cells, each 30x30 pixels).
- **Target Frame Rate:** 60 FPS.
- **Input Handling:** Arrow key navigation includes reverse-direction prevention to stop the snake from moving directly into itself.
- **Background:** Set to a dark forest green (`{20, 60, 20, 255}`).
- **Rendering Order:** Food is rendered before the Snake, ensuring the food appears underneath the snake when overlapped.
- **Update Mechanism:** Employs time-based updates decoupled from the frame rate, ensuring smooth and consistent movement regardless of system performance.
