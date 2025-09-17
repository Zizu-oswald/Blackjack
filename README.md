# Blackjack

A simple C++ project using [Raylib](https://www.raylib.com/) for graphics.
Build and dependencies are managed through [vcpkg](https://github.com/microsoft/vcpkg) and CMake.

---

## Requirements

* Ubuntu 20.04+ (or any modern Linux version)
* C++ compiler (g++ >= 10)
* CMake >= 3.13
* Git
* vcpkg

---

## Installation and Build

### 1. Clone the project

```bash
git clone https://github.com/USERNAME/Blackjack.git
cd Blackjack
```

### 2. Install vcpkg (if not already installed)

```bash
git clone --branch 2025.08.27 --single-branch https://github.com/microsoft/vcpkg.git
# or you can clone another stable version
cd ~/vcpkg
./bootstrap-vcpkg.sh
```

---

### 3. Install dependencies

In the project root:

```bash
~/vcpkg/vcpkg install raylib
```

---

### 4. Build the project

```bash
mkdir build
cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

All dependencies will be automatically pulled via vcpkg.

---

### 5. Run the game

While in the `build/` folder:

```bash
./Blackjack
```

The game should launch and correctly load all assets.

---
### 6. Playing the game

At the beginning of the game, enter your bank and bet.

Tap `R` to restart distribution

---


