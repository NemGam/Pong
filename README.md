# [<ins>Pong</ins>](https://github.com/NemGam/Pong/releases/download/v1.2.0/Pong.zip)
This is the pong game recreated using C++ and SDL2 library. 
It supports sprite and font loading, allowing you to replace files as long as the same file name is kept.
<!--This game is also available in [Game Launcher](https://github.com/NemGam/GameLauncher) -->


![Pong](https://github.com/user-attachments/assets/dc92b710-6a10-4fa6-8fdc-ea464a461de3)


Windows build can be downloaded [here](https://github.com/NemGam/Snake/releases/download/v1.2.0/Pong.zip). Just unpack to any folder and run snake.exe. 
# Getting Started (Linux)
## Dependencies
- CMake (version 3.13 or higher recommended)
- C++ Compiler: Compatible with C++17 standard
- SDL2 (>= 2.0.20)
- SDL2-ttf (>= 2.0.18)
- SDL2-image (>= 2.0.5)

## Downloading
### Clone the repository:
	git clone https://github.com/NemGam/Pong.git
### Navigate to the project directory:
	cd Pong

## Building the Project
From the project root directory, generate the build system:

	cmake -S . -B build

Compile and install the project:

    cmake --build build && cmake --install build

### Running the Application
Execute the compiled application:

	./dist/bin/pong
