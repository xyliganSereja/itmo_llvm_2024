# Instruction Set Architecture (ISA) Documentation

This ISA is designed to manage and update a 2D grid with specific rules and conditions, supporting functionalities such as memory allocation, pixel manipulation, and counting neighboring cells.

## Instructions

### Memory Allocation and Initialization
- **ALLOC R1, SIZE**  
  Allocates a memory block of `SIZE` units and assigns its address to register `R1`.

- **CALL FUNC, R1, ...**  
  Calls a subroutine `FUNC`, passing registers (e.g., `R1`) as arguments.

- **RET**  
  Returns from a subroutine to the caller.

### Basic Arithmetic and Data Movement
- **MOV Rx, VALUE**  
  Moves a literal `VALUE` into register `Rx`.

- **ADD Rx, Ry, Rz**  
  Adds the contents of `Ry` and `Rz` and stores the result in `Rx`.

- **MOD Rx, Ry, VALUE**  
  Computes `Ry % VALUE` and stores the result in `Rx`.

### Comparison and Conditional Jumps
- **CMP Rx, Ry, VALUE**  
  Compares the contents of `Ry` with `VALUE` and sets `Rx` to `1` if they are equal, otherwise `0`.

- **CMPG Rx, Ry, VALUE**  
  Sets `Rx` to `1` if `Ry` is greater than or equal to `VALUE`.

- **CMPL Rx, Ry, VALUE**  
  Sets `Rx` to `1` if `Ry` is less than `VALUE`.

- **CMPN Rx, Ry, VALUE**  
  Sets `Rx` to `1` if `Ry` is not equal to `VALUE`.

- **JMPEQ Rx, VALUE, LABEL**  
  Jumps to `LABEL` if `Rx` is equal to `VALUE`.

- **JMP LABEL**  
  Unconditionally jumps to `LABEL`.

### Logic and Bitwise Operations
- **AND Rx, Ry, Rz**  
  Performs a bitwise AND operation between `Ry` and `Rz`, storing the result in `Rx`.

- **SELECT Rx, CONDITION, TRUE_VALUE, FALSE_VALUE**  
  Sets `Rx` to `TRUE_VALUE` if `CONDITION` is true, otherwise sets `Rx` to `FALSE_VALUE`.

### Memory Access
- **STORE Rx, [MEM_ADDR]**  
  Stores the value in `Rx` at memory address `MEM_ADDR`.

- **LOAD Rx, [MEM_ADDR]**  
  Loads the value from memory address `MEM_ADDR` into `Rx`.

### Grid Management (Specific to Display or Simulation)
- **CALL SIM_RAND**  
  Calls the `SIM_RAND` function to generate a random number, typically stored in a register for further calculations.

- **CALL SIM_FLUSH**  
  Calls the `SIM_FLUSH` function to refresh the display or grid state.

- **CALL SIM_PUTPIXEL Rx, Ry, COLOR**  
  Calls `SIM_PUTPIXEL`, placing a pixel at coordinates `(Rx, Ry)` with the specified `COLOR`.

## Subroutines

### `init_game`
Initializes the grid cells with random values, storing `0` or `1` in each cell.

### `draw`
Draws each pixel on the grid. The color of each pixel is chosen based on its value (e.g., -16777216 for black and -16711936 for green).

### `count_neighbors`
Counts active neighboring cells around a specific grid cell. This is used to determine the cell's future state based on the sum of its neighbors.

### `update`
Updates the grid based on cell neighbor counts. Each cell's state changes according to the neighboring values, implementing custom rules to simulate a grid-based update.

## Example Program Workflow

1. **Initialization**: `init_game` initializes two grids with random values.
2. **Draw Loop**: `draw` displays the grid based on the cell values.
3. **Update Loop**: `update` modifies the grid values based on neighbor conditions, and the program repeats.

This ISA enables grid management through conditional logic, memory handling, and pixel manipulation, supporting custom grid-based applications such as cellular automata or simple simulations.
