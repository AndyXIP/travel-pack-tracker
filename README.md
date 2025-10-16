# Travel Pack Tracker

![Status](https://img.shields.io/badge/Status-Complete-success)
![C++](https://img.shields.io/badge/C%2B%2B-23-00599C?logo=cplusplus&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-macOS%20%7C%20Linux-lightgrey)
![License](https://img.shields.io/badge/License-MIT-yellow)

A lightweight C++ CLI tool for tracking and managing items across multiple locations. Perfect for managing belongings between homes, suitcases, offices, or any other locations during travel or daily life.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Tech Stack](#tech-stack)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Building](#building)
- [Usage](#usage)
  - [Command Reference](#command-reference)
  - [Examples](#examples)
- [How It Works](#how-it-works)
- [Data Format](#data-format)
- [Development](#development)
- [Future Enhancements](#future-enhancements)
- [License](#license)

---

## Overview

Travel Pack Tracker is a command‑line application designed to help you keep track of physical items distributed across different locations. Whether you're packing for a trip, managing items between multiple homes, or organizing office supplies, this tool provides a simple and efficient way to know exactly where everything is.

Key capabilities include adding items with quantities, moving items between locations, smart item merging, and automatic data persistence through JSON storage.

---

## Features

- **Item Management** – Add, remove, and track items with quantities
- **Location Tracking** – Know exactly where each item is located
- **Smart Movement** – Move all or partial quantities between locations
- **Location Filtering** – List items by specific location or view all at once
- **Quick Search** – Find items instantly by name
- **Automatic Persistence** – All changes save to JSON automatically
- **Intelligent Merging** – Duplicate items at the same location are combined
- **Error Handling** – Graceful handling of invalid input and edge cases

---

## Tech Stack

- **Language:** C++23
- **Build System:** Make
- **JSON Library:** [nlohmann/json](https://github.com/nlohmann/json) 3.x
- **Data Storage:** JSON file‑based persistence
- **Standard Library:** STL (vectors, optional, algorithms, file I/O)

---

## Project Structure

```
travel-pack-tracker/
├── include/                 # Header files
│   ├── item.h
│   ├── inventory.h
│   └── commands.h
├── src/                     # Implementation files
│   ├── item.cpp
│   ├── inventory.cpp        # Inventory operations + JSON I/O
│   ├── commands.cpp         # Command parsing and execution
│   └── main.cpp             # Application entry point
├── Makefile
├── .gitignore
├── LICENSE
└── README.md
```

---

## Getting Started

### Prerequisites

- **C++ Compiler:** g++ or clang with C++23 support
- **Build Tool:** Make
- **Dependencies:** nlohmann/json library

### Installation

#### macOS (Homebrew)

```bash
# Install nlohmann-json library
brew install nlohmann-json

# Clone the repository
git clone https://github.com/AndyXIP/travel-pack-tracker.git
cd travel-pack-tracker
```

#### Linux (Ubuntu/Debian)

```bash
# Install dependencies
sudo apt-get update
sudo apt-get install nlohmann-json3-dev build-essential

# Clone the repository
git clone https://github.com/AndyXIP/travel-pack-tracker.git
cd travel-pack-tracker
```

### Building

```bash
# Build the project
make

# The binary will be created at bin/main
```

---

## Usage

### Command Reference

All commands follow the pattern: `./bin/main <command> [arguments]`

| Command | Syntax | Description |
|---------|--------|-------------|
| `help` | `./bin/main help` | Display usage information |
| `add` | `./bin/main add <name> <qty> <location>` | Add item to inventory |
| `remove` | `./bin/main remove <name> [qty]` | Remove item or reduce quantity |
| `move` | `./bin/main move <name> <qty\|all> <from> <to>` | Move items between locations |
| `list` | `./bin/main list [location]` | List all items or filter by location |
| `find` | `./bin/main find <name>` | Search for a specific item |

### Examples

#### Adding Items

```bash
# Add items to different locations
./bin/main add laptop 1 home
./bin/main add charger 2 home
./bin/main add socks 5 home
./bin/main add toothbrush 1 travel-bag
```

#### Listing Items

```bash
# View all items
./bin/main list

# Output:
# All Items:
# ----------------------------------------
# - laptop (Qty: 1, Location: home)
# - charger (Qty: 2, Location: home)
# - socks (Qty: 5, Location: home)
# - toothbrush (Qty: 1, Location: travel-bag)
# ----------------------------------------

# View items at specific location
./bin/main list home
```

#### Moving Items

```bash
# Pack for a trip - move some socks to suitcase
./bin/main move socks 3 home suitcase

# Move laptop completely
./bin/main move laptop all home suitcase

# Check what's packed
./bin/main list suitcase
```

#### Finding Items

```bash
./bin/main find charger

# Output:
# ✓ Found: charger
#   Quantity: 2
#   Location: home
```

#### Removing Items

```bash
# Remove 1 charger
./bin/main remove charger 1

# Remove all socks
./bin/main remove socks
```

---

## How It Works

The application follows a simple three‑step process on each execution:

1. **Load** – Reads existing inventory from `inventory.json` (if it exists)
2. **Execute** – Processes your command (add, remove, move, list, find)
3. **Save** – Automatically persists all changes back to `inventory.json`

The JSON file is created automatically on first use if it doesn't exist, making the application ready to use immediately after installation.

### Smart Item Merging

When adding items, the inventory automatically detects duplicates at the same location and combines quantities. For example:

```bash
./bin/main add socks 2 home
./bin/main add socks 3 home  # Combines to 5 socks at home
```

### Partial Quantity Moves

The move command supports moving partial quantities, automatically splitting items:

```bash
./bin/main move socks 2 home suitcase  # Leaves 3 at home, adds 2 to suitcase
```

---

## Data Format

Items are stored in `inventory.json` with the following structure:

```json
[
    {
        "name": "laptop",
        "quantity": 1,
        "location": "suitcase"
    },
    {
        "name": "socks",
        "quantity": 3,
        "location": "home"
    },
    {
        "name": "socks",
        "quantity": 2,
        "location": "suitcase"
    }
]
```

The file uses pretty‑printed JSON with 4‑space indentation for readability.

---

## Development

### Build Commands

```bash
# Clean and rebuild
make clean && make

# Build only
make

# Clean build artifacts
make clean
```

### Code Documentation

All header files include professional Doxygen‑style documentation. Implementation files contain inline comments explaining complex logic.

### Adding New Features

The modular architecture makes extending functionality straightforward:

- **New commands:** Add methods to `CommandHandler` class in `commands.h/cpp`
- **Item properties:** Extend the `Item` class in `item.h/cpp`
- **Inventory operations:** Add methods to `Inventory` class in `inventory.h/cpp`

---

## Future Enhancements

Potential improvements for future development:

- **Categories/Tags** – Group items by type (clothing, electronics, toiletries)
- **Export Functionality** – Generate reports in CSV or Markdown format
- **History Tracking** – Log of all item movements with timestamps
- **Multi‑User Support** – Separate inventories for different users
- **Undo/Redo** – Revert recent operations
- **Advanced Search** – Filter by multiple criteria (location + quantity range)
- **Cloud Sync** – Backup and sync across devices
- **Unit Tests** – Comprehensive test suite using Google Test or Catch2
- **CI/CD** – Automated builds and testing via GitHub Actions

---

## License

This project is licensed under the MIT License – see [LICENSE](LICENSE) for details.

---

## Acknowledgments

- [nlohmann/json](https://github.com/nlohmann/json) for the excellent modern C++ JSON library
- Inspired by the need for simple, effective item tracking during frequent travel
