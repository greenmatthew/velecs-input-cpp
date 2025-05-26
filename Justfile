# Set shell for Windows
set windows-shell := ["powershell.exe", "-NoLogo", "-Command"]

# Generator used for project
generator := "Visual Studio 17 2022"
# Where the project gets generated at
build := "build"
# Where the executable gets compiled to
bin := "bin"
# Where the library gets compiled to
libs := "libs"

# Default target to show available commands
default: help

# Show available commands
help:
    just --list

# Build the library in debug mode
build:
    @echo "Building velecs-math library (debug)..."
    if (!(Test-Path {{build}})) { New-Item -ItemType Directory -Path {{build}} -Force }
    cmake -S . -B {{build}} -DVELECS_MATH_BUILD_TESTS=OFF -G "{{generator}}"
    cmake --build {{build}} --config Debug

# Build the library in release mode
build-release:
    @echo "Building velecs-math library (release)..."
    if (!(Test-Path {{build}})) { New-Item -ItemType Directory -Path {{build}} -Force }
    cmake -S . -B {{build}} -DVELECS_MATH_BUILD_TESTS=OFF -G "{{generator}}"
    cmake --build {{build}} --config Release

# Build the library and test executable in debug mode
build-exec:
    @echo "Building velecs-math library and test executable (debug)..."
    if (!(Test-Path {{build}})) { New-Item -ItemType Directory -Path {{build}} -Force }
    cmake -S . -B {{build}} -DVELECS_MATH_BUILD_TESTS=ON -G "{{generator}}"
    cmake --build {{build}} --config Debug

# Build the library and test executable in release mode
build-exec-release:
    @echo "Building velecs-math library and test executable (release)..."
    if (!(Test-Path {{build}})) { New-Item -ItemType Directory -Path {{build}} -Force }
    cmake -S . -B {{build}} -DVELECS_MATH_BUILD_TESTS=ON -G "{{generator}}"
    cmake --build {{build}} --config Release

# Run the test executable (debug)
run: build-exec
    @echo "Running velecs-math test executable (debug)..."
    & "{{build}}/Debug/velecs-math-test.exe"

# Run the test executable (release)
run-release: build-exec-release
    @echo "Running velecs-math test executable (release)..."
    & "{{build}}/Release/velecs-math-test.exe"

# Create just the VS solution without building
solution:
    @echo "Creating Visual Studio solution..."
    if (!(Test-Path {{build}})) { New-Item -ItemType Directory -Path {{build}} -Force }
    cmake -S . -B {{build}} -G "{{generator}}"

# Open the solution in Visual Studio
open-solution: solution
    @echo "Opening solution in Visual Studio..."
    Start-Process "{{build}}/velecs-math.sln"

# Clean build directories
clean:
    @echo "Cleaning build directories..."
    if (Test-Path {{build}}) { Remove-Item -Recurse -Force {{build}} }

# Clean everything
clean-all: clean
    @echo "Cleaning everything..."
    if (Test-Path {{bin}}) { Remove-Item -Recurse -Force {{bin}} }
    if (Test-Path {{libs}}) { Remove-Item -Recurse -Force {{libs}} }