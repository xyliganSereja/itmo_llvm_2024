#include "sim.h"

#include <array>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class CPU {
public:
  CPU(size_t mem_size = 4096) : memory(std::make_unique<int32_t[]>(mem_size)), stack_size(mem_size) {
    stack_pointer = memory.get() + stack_size;
    registers.fill(0);
    srand(static_cast<unsigned>(time(0)));
  }

  void loadProgram(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
      std::cerr << "Error: Could not open file " << filename << std::endl;
      return;
    }

    std::string line;
    while (std::getline(file, line)) {
      program.push_back(line);
    }
    file.close();
  }

  void run() {
    int pc = 0;
    while (pc < program.size()) {
      const std::string& instruction = program[pc];
      if (instruction.find("ALLOC") != std::string::npos) {
        alloc(instruction);
      } else if (instruction.find("CALL SIM_RAND") != std::string::npos) {
        simRand();
      } else if (instruction.find("MOV") != std::string::npos) {
        mov(instruction);
      } else if (instruction.find("ADD") != std::string::npos) {
        add(instruction);
      } else if (instruction.find("CMP") != std::string::npos) {
        cmp(instruction);
      } else if (instruction.find("CALL SIM_FLUSH") != std::string::npos) {
        simFlush();
      } else if (instruction.find("SIM_PUTPIXEL") != std::string::npos) {
        simPutPixel(instruction);
      } else if (instruction.find("JMP") != std::string::npos) {
        pc = jmp(instruction) - 1;
      } else {
        std::cout << "Unknown instruction: " << instruction << std::endl;
      }
      pc++;
    }
  }

private:
  std::unique_ptr<int32_t[]> memory;
  std::array<int32_t, 16> registers;
  int32_t* stack_pointer;
  size_t stack_size;
  std::vector<std::string> program;

  void alloc(const std::string& instruction) {
    std::cout << "Allocating memory (dummy function): " << instruction << std::endl;
  }

  void mov(const std::string& instruction) {
    auto reg_value = parseInstruction(instruction);
    registers[reg_value.first] = reg_value.second;
    std::cout << "MOV " << "R" << reg_value.first << " = " << reg_value.second << std::endl;
  }

  void add(const std::string& instruction) {
    auto reg_value = parseInstruction(instruction);
    registers[reg_value.first] += reg_value.second;
    std::cout << "ADD " << "R" << reg_value.first << " += " << reg_value.second << std::endl;
  }

  void cmp(const std::string& instruction) {
    auto reg_value = parseInstruction(instruction);
    registers[reg_value.first] = (registers[reg_value.first] == reg_value.second) ? 1 : 0;
    std::cout << "CMP " << "R" << reg_value.first << " == " << reg_value.second << std::endl;
  }

  void simRand() {
    registers[5] = SIM_RAND();
    std::cout << "Random value for R5 = " << registers[5] << std::endl;
  }

  void simFlush() {
    SIM_FLUSH();
    std::cout << "Screen flushed" << std::endl;
  }

  void simPutPixel(const std::string& instruction) {
    int x = registers[3];
    int y = registers[3];
    int color = -16777216;
    SIM_PUTPIXEL(x, y, color);
    std::cout << "Drawing pixel at (" << x << ", " << y << ") with color " << color << std::endl;
  }

  int jmp(const std::string& instruction) {
    if (instruction.find("app_loop") != std::string::npos) {
      return 0;
    }

    return -1;
  }

  std::pair<int, int> parseInstruction(const std::string& instruction) {
    int reg = instruction[4] - '0';
    int value = std::stoi(instruction.substr(instruction.find_last_of(' ') + 1));
    return {reg, value};
  }
};

int main() {
  CPU cpu;
  cpu.loadProgram("app.s");
  cpu.run();

  return 0;
}
