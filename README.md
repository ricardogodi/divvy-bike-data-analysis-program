# Divvy Bike Data Analysis Program

## Project Overview
This C++ application analyzes Divvy Bike ride data, providing insights through a variety of computational analyses. It reads ride data from external sources, calculates distances, and displays various statistics about the rides.

## Features
- Load and clean data from external CSV files available via Dropbox.
- Calculate and display the total and average trip distances.
- Compare member versus casual riders.
- Analyze and display ride data for weekdays versus weekends.
- Extra credit: Locate the nearest bike station.

## Getting Started

### Prerequisites
Ensure you have a C++ compiler installed that supports C++11, such as GCC or Clang.

### Data Files
The data files `weekdayweekend.csv` and `all_divvy_rides_september.csv` can be downloaded from the following Dropbox link:
[Download Data Files](https://www.dropbox.com/scl/fo/xlouexx0bneuv7ucsi1fz/AE_VPbka_OQSq112syqrEGA?rlkey=0rmvlt1nxioqfpw3wb1znvvvm&st=qq3fc2rw&dl=0)

### Compiling the Program
1. Open a terminal in the project directory.
2. Run the following command to compile the program:
   ```bash
   make
3. This will compile the source file main.cpp into an executable named divvy_analysis.


## Running the Program

After compiling the program, you can run it using:

   ```bash
   ./divvy_analysis
   ```

## Cleaning Build Files

To clean up build files and executables, use:
   ```bash
   make clean
   ```


## Using the Program

- After running the program, you will be prompted with a menu to select different options for data analysis.
- Follow the on-screen prompts to select data files and view analysis results.


