#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "sim.h"

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>

using namespace llvm;

const int REG_FILE_SIZE = 8;
uint32_t REG_FILE[REG_FILE_SIZE];
LLVMContext context;
Module* module = new Module("top", context);
IRBuilder<> builder(context);
std::unordered_map<std::string, Value*> registers;

Value* getRegister(const std::string& reg) {
    if (registers.find(reg) == registers.end()) {
        registers[reg] = builder.CreateAlloca(builder.getInt32Ty());
    }
    return builder.CreateLoad(registers[reg]);
}

void setRegister(const std::string& reg, Value* value) {
    if (registers.find(reg) == registers.end()) {
        registers[reg] = builder.CreateAlloca(builder.getInt32Ty());
    }
    builder.CreateStore(value, registers[reg]);
}

void translateALLOC(const std::string& reg, int size) {
    ArrayType* arrayType = ArrayType::get(builder.getInt32Ty(), size);
    module->getOrInsertGlobal(reg, arrayType);
}

void translateCALL(const std::string& funcName, const std::vector<Value*>& args) {
    FunctionCallee func = module->getOrInsertFunction(funcName, FunctionType::get(builder.getVoidTy(), args, false));
    builder.CreateCall(func, args);
}

void translateCMP(const std::string& regDest, const std::string& regSrc, int value) {
    Value* regVal = getRegister(regSrc);
    Value* cmpVal = builder.getInt32(value);
    Value* cmpResult = builder.CreateICmpEQ(regVal, cmpVal);
    setRegister(regDest, cmpResult);
}

void translateJMP(const std::string& label) {
    BasicBlock* targetBB = BasicBlock::Create(context, label, builder.GetInsertBlock()->getParent());
    builder.CreateBr(targetBB);
    builder.SetInsertPoint(targetBB);
}

void parseAssembly(const std::string& filename, Function* mainFunc) {
    std::ifstream infile(filename);
    std::string line;
    
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string instr;
        iss >> instr;
        
        if (instr == "ALLOC") {
            std::string reg;
            int size;
            iss >> reg >> size;
            translateALLOC(reg, size);
        } else if (instr == "CALL") {
            std::string funcName;
            std::vector<Value*> args;
            iss >> funcName;
            
            std::string arg;
            while (iss >> arg) {
                args.push_back(getRegister(arg));
            }
            translateCALL(funcName, args);
        } else if (instr == "MOV") {
            std::string dest, src;
            iss >> dest >> src;
            Value* srcVal = getRegister(src);
            setRegister(dest, srcVal);
        } else if (instr == "CMP") {
            std::string regDest, regSrc;
            int value;
            iss >> regDest >> regSrc >> value;
            translateCMP(regDest, regSrc, value);
        } else if (instr == "JMP") {
            std::string label;
            iss >> label;
            translateJMP(label);
        }
    }
}

void initGame(Function* func) {
    BasicBlock* initBB = BasicBlock::Create(context, "init_game", func);
    builder.SetInsertPoint(initBB);
    builder.CreateCall(module->getFunction("SIM_RAND"));
    builder.CreateRetVoid();
}

void draw(Function* func) {
    BasicBlock* drawBB = BasicBlock::Create(context, "draw", func);
    builder.SetInsertPoint(drawBB);
    FunctionCallee simPutPixelFunc = module->getOrInsertFunction(
        "SIM_PUTPIXEL", FunctionType::get(builder.getVoidTy(), 
                                          {builder.getInt32Ty(), builder.getInt32Ty(), builder.getInt32Ty()}, false));
    Value* x = builder.getInt32(0);
    Value* y = builder.getInt32(0);
    Value* color = builder.getInt32(-16777216);
    builder.CreateCall(simPutPixelFunc, {x, y, color});
    builder.CreateRetVoid();
}

void update(Function* func) {
    BasicBlock* updateBB = BasicBlock::Create(context, "update", func);
    builder.SetInsertPoint(updateBB);
    FunctionCallee countNeighborsFunc =
        module->getOrInsertFunction("count_neighbors", FunctionType::get(builder.getVoidTy(), false));
    builder.CreateCall(countNeighborsFunc);
    builder.CreateRetVoid();
}

int main() {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    
    FunctionType* voidFuncType = FunctionType::get(builder.getVoidTy(), false);
    Function* mainFunc = Function::Create(voidFuncType, Function::ExternalLinkage, "main", module);
    BasicBlock* mainBB = BasicBlock::Create(context, "entry", mainFunc);
    builder.SetInsertPoint(mainBB);

    Function* initGameFunc = Function::Create(voidFuncType, Function::ExternalLinkage, "init_game", module);
    initGame(initGameFunc);
    Function* drawFunc = Function::Create(voidFuncType, Function::ExternalLinkage, "draw", module);
    draw(drawFunc);
    Function* updateFunc = Function::Create(voidFuncType, Function::ExternalLinkage, "update", module);
    update(updateFunc);
    
    parseAssembly("app.s", mainFunc);

    builder.CreateRetVoid();
    
    outs() << "\n#[LLVM IR]:\n";
    module->print(outs(), nullptr);
    bool verif = verifyFunction(*mainFunc, &outs());
    outs() << "[VERIFICATION] " << (!verif ? "OK\n\n" : "FAIL\n\n");

    ExecutionEngine* ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
    ee->addGlobalMapping(module->getNamedGlobal("array1"), (void*)REG_FILE);
    ee->finalizeObject();
    ArrayRef<GenericValue> noargs;
    ee->runFunction(mainFunc, noargs);

    outs() << "#[Code was run]\n";
    simExit();
    return 0;
}
