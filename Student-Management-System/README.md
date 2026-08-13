# Student Management System (C++17)

## Project objective

This is a beginner-friendly, console-based Student Management System for a small, single-user dataset. It manages student records in memory with `std::vector` and stores them in a local text file. It is an academic/training project, not a production institutional information system.

## Features

- Add a student after validating every field and enforcing unique positive Student IDs.
- Display all records, including ID, name, course, semester, email, and marks.
- Search by Student ID or by name (case-insensitive name text match).
- Update a student's non-ID fields only after all replacement values are valid.
- Delete a student only after a `Y/N` confirmation.
- Sort records by Student ID, name, or marks using `std::sort`.
- Save records to a local pipe-delimited text file and load them at startup.
- Recover from invalid menu, numeric, field, and confirmation input without terminating unexpectedly.
- Ignore malformed or duplicate-ID records found in the data file and report their count.
- Save automatically during a normal exit; if saving fails, let the operator cancel the exit or explicitly exit without saving current changes.

## Technologies used

- C++17
- Standard C++ Library
- `std::vector`, `std::string`, `std::sort`, `std::find_if`
- File handling with `ifstream` and `ofstream`
- Classes, constructors, encapsulation, functions, exception handling for numeric conversion, and modular source files

## Requirements

- A C++17-capable compiler, such as GCC, Clang, or MSVC
- CMake 3.16+ (recommended build method), or a compiler command that supports C++17

## Project structure

```text
Student-Management-System/
├── include/
│   ├── Student.h          # Encapsulated Student data model
│   ├── Validator.h        # Parsing and field validation
│   └── FileManager.h      # Local text-file persistence interface
├── src/
│   ├── Student.cpp
│   ├── Validator.cpp
│   ├── FileManager.cpp
│   └── main.cpp           # Console UI and application logic
├── data/
│   └── students.txt       # Sample local data file
├── docs/
│   └── TESTING.md         # Manual functional, boundary, and integration tests
├── CMakeLists.txt
└── README.md
```

## Architecture

```text
Console user interface (main.cpp)
            |
Application / business operations (StudentManagementSystem)
            |
Student model (Student)  <---->  File persistence (FileManager)
            |
Input and record validation (Validator)
```

`Student` owns one record and exposes getters/setters. `Validator` centralizes string trimming, numeric parsing, field rules, and range checks. `FileManager` serializes and validates local records. `main.cpp` contains a small application class that runs the menu and coordinates the other modules; `main()` itself only starts the application.

## Compilation

From the project root, use CMake:

```bash
cmake -S . -B build
cmake --build build
```

Or compile directly with GCC or Clang:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Iinclude \
  src/main.cpp src/Student.cpp src/Validator.cpp src/FileManager.cpp \
  -o student_management_system
```

## Execution

Run the executable **from the project root** so that the relative `data/students.txt` path is used:

```bash
./build/student_management_system
```

For the direct compiler command:

```bash
./student_management_system
```

The startup loader reports whether it restored data, found no file, or ignored malformed records. Every completed menu operation returns to the main menu unless the operator exits.

## File storage

Records are stored locally in `data/students.txt`, one record per line, using this exact field order:

```text
Student ID|Name|Course|Semester|Email|Marks
```

For example:

```text
1001|Aarav Sharma|B.Tech CSE|3|aarav@example.com|84.5
```

The vertical bar (`|`) is reserved as the file delimiter and is therefore not accepted in text fields. The application does not use a database, network service, cloud storage, or external library.

## Sample data

The included `data/students.txt` starts with these two valid sample records:

```text
1001|Aarav Sharma|B.Tech CSE|3|aarav@example.com|84.5
1002|Meera Kapoor|B.Tech CSE|3|meera@example.com|91.0
```

## Testing

The complete functional, boundary, malformed-file, and restart workflow test plan is in [docs/TESTING.md](docs/TESTING.md). It covers TC-01 through TC-12 plus the required semester/marks boundaries and an end-to-end persistence workflow.

## Known limitations

- Console-only interface; no GUI, web, or mobile client.
- Single-user operation with a small in-memory `std::vector` dataset.
- Local, plain text persistence only; there is no database, index, synchronization, or concurrent access control.
- Search is linear and intended for small datasets.
- Basic input validation is not full security. The text file is not encrypted or access-controlled and must not be used as secure institutional storage for real sensitive student data.
- The system is an academic training project and is not production-ready.

## Future enhancements — not implemented

1. Further refactor the application into additional C++ files if the project grows beyond the current required module split.
2. Database integration.
3. Authentication and role management.
4. Graphical user interface.
5. Reporting and analytics.
6. Automated testing framework.
7. Web/API layer.
8. Cloud deployment.

None of these future items are part of this baseline implementation.
