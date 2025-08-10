# Zombie Arena (Learning Project) 💪🧠

This is a **learning project** based on the book *Beginning C++ Game Programming* by John Horton (Packt Publishing).  
The goal is to practice C++, SFML, and basic game architecture — **not** to create a polished final product.  
Currently, the game is running in **32-bit Debug** mode.

## Technologies
- **C++17** (or newer)
- **SFML 2.5.x** (32-bit)
- Visual Studio (Windows) / CMake + g++ (optional)

## How to Run (32-bit Debug)
1. Open the solution in Visual Studio.
2. Select **x86** and **Debug** configuration.
3. Run with **Local Windows Debugger** (F5).
4. If SFML `.dll` files are missing, place them in the output directory (e.g. `...\Debug\`).

> **Note:** Assets (textures, sounds, fonts) must be in the expected folders (`fonts/`, `sound/`, `graphics/`, `gamedata/`).

## Controls
- **W A S D** – Move
- **Mouse** – Aim
- **Left Click** – Shoot
- **R** – Reload
- **Esc** – Pause / Main Menu
- **Goal:** Survive waves of zombies, collect pickups, increase score.  
- **Hi score** is stored in `gamedata/score.txt` (read at start, written on GAME_OVER).

## Current Status
- Working: Game loop, shooting, zombie AI, HUD, sounds.
  
## Project Structure (short)
- `Player`, `Zombie`, `Bullet`, `Pickup` – main game classes
- `TextureHolder` – texture caching
- `ZombieArena.*` – arena & horde generation
- `gamedata/score.txt` – hi score read/write

## TODO
- Balance ammo and reload time
- Add settings (sound, mouse sensitivity)
- Fix edge collision checks & rare double-hit bug
- Switch to **Release** build & optimize

## Credits
- Game design and logic inspired by *Beginning C++ Game Programming* by John Horton.  
- Code adapted for personal learning purposes.
