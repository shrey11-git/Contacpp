# Contacpp (Contac++)
A C++-based contact manager app with GUI and SQLite integration—built to explore C++ development, databases, and GUI frameworks.

# ※ What Problem Does It Solve?
Managing personal contacts quickly without relying on heavy apps or online services. This simple tool is great for anyone learning C++ or looking to build small, functional desktop tools.

# ※ Key Features
- Add, search, and delete contacts
- Search by name with partial matches
- Sort results by name or phone (ascending & descending)
- Clear all contacts
- GUI built with ImGui + GLFW + OpenGL

# ※ Tech Stack
Language: C++17
Database: SQLite
GUI: ImGui, GLFW, OpenGL
Tools: CMake, Visual Studio 2022

# ※ How to Run
- Clone the repo
git clone https://github.com/shrey11-git/Contacpp.git
cd Contacpp
- Make sure you have g++, CMake, and dependencies (GLFW, ImGui, SQLite)
- Then build and run
g++ gui_main.cpp db.cpp -lglfw -lGL -ldl -lX11 -lpthread -lXrandr -lXi -lXxf86vm -lXcursor -lXinerama -lsqlite3 -o Contacpp
- Run the app
./Contacpp

# ※ Screenshot
<img width="982" height="714" alt="Screenshot 2025-07-11 202353" src="https://github.com/user-attachments/assets/7341a6c8-952c-4ac7-baa4-b42dc392ee7d" />

# ※ What I Learned
Built this to practice C++ fundamentals like file structure, pointers, and class-free modularity. Also got hands-on with SQLite integration and learned the ropes of setting up a lightweight GUI using ImGui with GLFW + OpenGL.

# ※ Author
Shreyash Tiwari
[ GitHub](https://github.com/shrey11-git) • [linkedin](http://www.linkedin.com/in/shreyashtiwari-csbs)

TL;DR Summary
A contact manager built with C++, ImGui, and SQLite to explore modern C++ programming, GUI building, and DB integration.
