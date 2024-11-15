# Trajectory Planning Project

This project implements a trajectory planning system using C++ for robots navigating in dynamic environments. The goal is to determine optimal paths from a starting point to a target while avoiding obstacles.

## Project Overview

- **Developers**: Aymen Ben Ammar, Eya Jlassi
- **Supervisor**: Mme. Sonia Alouane
- **Institution**: ENSTA Paris, 2023/2024

This project explores C++ algorithms and data structures to plan optimal paths while taking into account obstacle constraints and environmental changes.

## Features

- **Path Optimization**: Uses Dijkstra's algorithm for shortest path calculations.
- **Obstacle Detection**: Integrates OpenCV to identify obstacle contours.
- **User Interface**: Built with wxWidgets for a GUI, allowing users to upload environment maps and select start and end points.
- **Visualization**: Displays the planned path and obstacles using SFML for graphical rendering.
<p align="center">
  <img src="https://github.com/user-attachments/assets/cc5498e3-8669-4186-a393-d083657f422d" alt="Image 1" width="45%">
  <img src="https://github.com/user-attachments/assets/4102421c-deb7-483f-8968-dfc8f8184a1d" alt="Image 2" width="45%">
</p>

## Project Structure

- `src/`: Contains source code for path planning and GUI.
- `include/`: Header files defining data structures (e.g., Vertex, Segment, Obstacle, Graph).
- `data/`: Sample environment maps and obstacle files.
- `docs/`: Project report detailing design, implementation, and testing.

## Prerequisites

- **C++ Compiler**: Ensure C++11 or later support.
- **wxWidgets**: For the graphical user interface.
- **SFML**: Used for graphical visualization.
- **OpenCV**: (Optional) Required for advanced obstacle detection.

## Installation

1. **Install wxWidgets**:
   ```bash
   sudo apt-get install libwxgtk3.0-dev
   ```

2. **Install SFML**:
   ```bash
   sudo apt-get install libsfml-dev
   ```

3. **Install OpenCV (Optional)**:
   ```bash
   sudo apt-get install libopencv-dev
   ```

4. **Clone Repository**:
   ```bash
   git clone https://github.com/EyaJlassi695/Airborne-TSP-Optimizer.git
   cd Airborne-TSP-Optimizer
   ```

## Usage

1. **Build the Project**:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

2. **Run the Application**:
   ```bash
   ./TrajectoryPlanner
   ```

3. **Using the GUI**:
   - Upload an obstacle map image.
   - Select the start and end points.
   - View the calculated optimal path.

## Project Documentation

Please refer to the full project documentation for detailed information on:

- Functional modeling and system architecture.
- Data input/output management.
- Step-by-step implementation and testing.
- Challenges encountered and solutions implemented.

## Acknowledgments

We extend our gratitude to Mme. Sonia Alouane for her guidance and support, and Mme Hedia Chaker for her encouragement throughout this project.

## License

This project is licensed under the MIT License.
