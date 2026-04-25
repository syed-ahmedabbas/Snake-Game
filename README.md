# 🐍 Snake Game (C++ & Raylib)

This project is a classic Snake Game built using C++ and the Raylib framework.

## 🚀 How to Setup Raylib and Run the Game
This project uses the Raylib C++ Starter Template for Visual Studio Code on Windows.

1. Double click on the `main.code-workspace` file. This will open the template in VS Code.
2. From the Explorer Window of VS Code, navigate to the `src` folder and double click on the `main.cpp` file.
3. Press `F5` on the keyboard to compile and run the program.

### 🎥 Video Tutorial on Setup
If you need help setting up Raylib with VS Code, watch this tutorial by Programming With Nick:
- [Video Tutorial on YouTube](https://www.youtube.com/watch?v=PaAcVk5jUd8)

---

## ✅ Current Progress & Features

### 1. Core Game Architecture Established
Designed and implemented a clean, class-based architecture for the Snake Game using Raylib. The codebase is organized around three main classes with clear separation of concerns:

| Class | Responsibility |
|-------|----------------|
| `Snake` | Body state, movement direction, segment growth, rendering |
| `Food` | Texture loading, random position generation, rendering |
| `Game` | Orchestrates snake + food, collision detection |

### 2. `Snake` Class
- Used `std::deque<Vector2>` for the snake body — allows efficient `push_front` (add head) and `pop_back` (remove tail) for movement.
- Initial body spawned at grid positions `{6,9}`, `{5,9}`, `{4,9}` (3 segments, facing right).
- **Growth mechanic:** `addSegment` flag — when `true`, the tail is NOT popped on update, effectively growing the snake by 1.
- **Rendering:** Each segment drawn as a rounded rectangle (`DrawRectangleRounded`) in bright neon green.

### 3. `Food` Class
- Loads a custom food texture from `graphics/food.png` (resized to 20×20px).
- **Collision-aware spawning:** `GenerateRandomPos()` loops until a cell not occupied by the snake body is found.

### 4. `Game` Class
- Owns both `Snake` and `Food` instances.
- Detects when the snake head lands on the food position → regenerates food position + grows the snake.

### 5. Main Game Loop
- Window: **600×600px** (20 cells × 30px per cell).
- Target FPS: **60**.
- Arrow key input with **reverse-direction prevention** (can't move directly into yourself).
- Background: dark forest green `{20, 60, 20, 255}`.
- Draw order: Food → Snake (food renders underneath).
- Time-based updates (decoupled from FPS) — smooth and frame-rate independent movement.
