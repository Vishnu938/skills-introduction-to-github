# Makefile for Docker Report C++ utility
# This demonstrates basic C++ compilation for educational purposes

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = docker_report
SOURCE = docker_report.cpp

# Default target
all: $(TARGET)

# Build the main executable
$(TARGET): $(SOURCE)
	@echo "Compiling Docker Report utility..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)
	@echo "Build complete! Run with: ./$(TARGET)"

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -f $(TARGET) docker_report.txt
	@echo "Clean complete!"

# Install (copy to /usr/local/bin - requires sudo)
install: $(TARGET)
	@echo "Installing Docker Report utility..."
	sudo cp $(TARGET) /usr/local/bin/
	@echo "Installation complete! You can now run 'docker_report' from anywhere."

# Uninstall
uninstall:
	@echo "Uninstalling Docker Report utility..."
	sudo rm -f /usr/local/bin/$(TARGET)
	@echo "Uninstall complete!"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Run with help option
help: $(TARGET)
	./$(TARGET) --help

# Show version
version: $(TARGET)
	./$(TARGET) --version

# Display available targets
.PHONY: all clean install uninstall run help version show-targets

show-targets:
	@echo "Available targets:"
	@echo "  all       - Build the Docker Report utility (default)"
	@echo "  clean     - Remove build artifacts"
	@echo "  run       - Build and run the program"
	@echo "  help      - Build and show help message"
	@echo "  version   - Build and show version"
	@echo "  install   - Install to /usr/local/bin (requires sudo)"
	@echo "  uninstall - Remove from /usr/local/bin (requires sudo)"