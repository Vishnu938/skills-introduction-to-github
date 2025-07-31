# Docker Report C++ Utility

A comprehensive C++ utility for generating Docker system reports. This educational project demonstrates various C++ programming concepts while providing useful Docker container and image reporting functionality.

## Features

- **Container Analysis**: Lists all Docker containers with their status, names, images, and port mappings
- **Image Inventory**: Reports on all Docker images including repository, tags, IDs, and sizes
- **System Summary**: Provides statistics on running/stopped containers and total images
- **Report Generation**: Creates detailed text reports for record-keeping
- **Error Handling**: Robust error handling and user-friendly messages
- **Cross-platform**: Works on Linux, macOS, and Windows (with appropriate C++ compiler)

## Educational Value

This project demonstrates several important C++ concepts:

- **Object-Oriented Programming**: Uses classes and encapsulation
- **STL Containers**: Vector, string, map usage
- **File I/O**: Reading from and writing to files
- **System Integration**: Executing system commands from C++
- **Memory Management**: Smart pointers and RAII principles
- **Error Handling**: Exception handling and graceful error recovery
- **String Processing**: Parsing and manipulating text data

## Prerequisites

- C++ compiler with C++11 support (g++, clang++, etc.)
- Docker installed and accessible via command line
- Make utility (optional, for using the Makefile)

## Building

### Using Make (Recommended)
```bash
# Build the utility
make

# Build and run
make run

# Show help
make help

# Clean build artifacts
make clean
```

### Manual Compilation
```bash
# Compile with g++
g++ -std=c++11 -Wall -Wextra -O2 -o docker_report docker_report.cpp

# Or with clang++
clang++ -std=c++11 -Wall -Wextra -O2 -o docker_report docker_report.cpp
```

## Usage

```bash
# Generate a full Docker report
./docker_report

# Show help information
./docker_report --help

# Show version information
./docker_report --version
```

## Sample Output

```
=================================================
           DOCKER SYSTEM REPORT
=================================================

✅ Docker is available on this system.

📦 CONTAINER REPORT
-------------------------------------------------
ID           NAME                 IMAGE                STATUS          PORTS
--------------------------------------------------------------------------------
a1b2c3d4e5f6 web-server          nginx:latest         Up 2 hours      80:8080/tcp
g7h8i9j0k1l2 database            postgres:13          Up 3 hours      5432/tcp

🖼️  IMAGE REPORT
-------------------------------------------------
REPOSITORY               TAG             IMAGE ID     SIZE
----------------------------------------------------------------------
nginx                   latest          d1a364dc548d  133MB
postgres                13              b97bae343e06  314MB

📊 SYSTEM SUMMARY
-------------------------------------------------
Total Containers: 2
  - Running: 2
  - Stopped: 0
Total Images: 2

Docker Version: Docker version 20.10.12, build e91ed57

📄 Detailed report saved to: docker_report.txt

Report generation completed successfully! ✅
```

## Generated Files

The utility creates a detailed text report file (`docker_report.txt`) containing:
- Complete container information
- Complete image information  
- Timestamps and system details
- Formatted for easy reading and sharing

## Error Handling

The utility gracefully handles various scenarios:
- Docker not installed or not running
- No containers or images present
- Permission issues
- File system errors

## Installation

### System-wide Installation
```bash
# Install to /usr/local/bin (requires sudo)
make install

# Now you can run from anywhere
docker_report
```

### Uninstallation
```bash
# Remove from system
make uninstall
```

## Contributing

This is an educational project created for the GitHub Skills tutorial. Feel free to:
- Add new features
- Improve error handling
- Enhance the reporting format
- Add unit tests
- Optimize performance

## Code Structure

```
docker_report.cpp
├── DockerReporter class
│   ├── ContainerInfo struct - Container data structure
│   ├── ImageInfo struct - Image data structure  
│   ├── executeCommand() - System command execution
│   ├── parseContainers() - Parse container data
│   ├── parseImages() - Parse image data
│   ├── displayContainerReport() - Container output formatting
│   ├── displayImageReport() - Image output formatting
│   ├── displaySystemSummary() - Statistics display
│   └── generateReportFile() - File report generation
└── main() - Command line handling and program entry
```

## Technical Notes

- Uses `popen()` for system command execution
- Implements RAII with smart pointers for resource management
- Employs STL containers for data management
- Uses iostream for formatted output
- Includes comprehensive error handling with exceptions

## License

This educational project is part of the GitHub Skills tutorial and is provided for learning purposes.

## Learning Objectives

By studying and modifying this code, you will learn:
1. How to structure a C++ application with classes
2. How to interact with system commands from C++
3. How to parse and process text data
4. How to handle errors gracefully
5. How to create user-friendly command-line interfaces
6. How to generate formatted reports
7. How to work with STL containers and algorithms