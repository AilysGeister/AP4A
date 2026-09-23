# Simulator

## Quick Start

```bash
# 1. Configure
cmake -B build -S .

# 2. Build
cmake --build build

# 3. Run
./bin/simulator
```

## Build Commands

| Action | Command |
| :--- | :--- |
| **Standard Build** | `cmake --build build` |
| **Clean Build Directory** | `cmake --build build --target clean` |
| **Clean & Rebuild** | `cmake --build build --target cleanbuild` |
| **Force Rebuild All** | `cmake --build build --target forcebuild` |