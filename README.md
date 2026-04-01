# 🔴 Martian

A C++ program that reads coordinate data from a CSV file, processes it through a multi-class pipeline, and outputs a decoded text post.

## Pipeline

```
CSV file
    ↓
File_text   →  reads file, splits into lines, stores in vector
    ↓
Coords      →  tokenizes lines into coordinates, converts to hex → ASCII
    ↓
Operator    →  stores vectors of degrees and errors, builds output string
    ↓
Text file   ←  final decoded string written to output
```
## Classes
| Class | Responsibility |
|-------|---------------|
| `File_text` | Reads CSV, breaks into lines, stores in `std::vector` |
| `Coords` | Tokenizes coordinate data; converts to hex code → ASCII |
| `Operator` | Works with `Coords` to store degree/error vectors; builds final string |

## Key Concepts
- CSV parsing and line tokenization
- Hexadecimal and ASCII encoding
- `std::vector` for dynamic data storage
- Multi-class data transformation pipeline
- File I/O (read CSV, write text output)

## Build
```
bash
g++ -std=c++11 -o martian *.cpp
./martian <input.csv>
```
> The included `.txt` file in the repo is the result of a successful binary-to-string conversion.

