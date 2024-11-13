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

void translateALLOC(Function* func) {
  ArrayType* arrayType = ArrayType::get(builder.getInt32Ty(), 256 * 512);
  module->getOrInsertGlobal("array1", arrayType);
  module->getOrInsertGlobal("array2", arrayType);
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

void countNeighbors(Function* func) {
  BasicBlock* countNeighborsBB = BasicBlock::Create(context, "count_neighbors", func);
  builder.SetInsertPoint(countNeighborsBB);
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
  FunctionType* voidFuncType = FunctionType::get(builder.getVoidTy(), false);
  Function* mainFunc = Function::Create(voidFuncType, Function::ExternalLinkage, "main", module);
  translateALLOC(mainFunc);
  Function* initGameFunc = Function::Create(voidFuncType, Function::ExternalLinkage, "init_game", module);
  initGame(initGameFunc);
  Function* drawFunc = Function::Create(voidFuncType, Function::ExternalLinkage, "draw", module);
  draw(drawFunc);
  Function* countNeighborsFunc = Function::Create(voidFuncType, Function::ExternalLinkage, "count_neighbors", module);
  countNeighbors(countNeighborsFunc);
  Function* updateFunc = Function::Create(voidFuncType, Function::ExternalLinkage, "update", module);
  update(updateFunc);
  BasicBlock* mainBB = BasicBlock::Create(context, "entry", mainFunc);
  builder.SetInsertPoint(mainBB);
  builder.CreateCall(initGameFunc);
  builder.CreateCall(drawFunc);
  builder.CreateCall(updateFunc);
  BasicBlock* loopBB = BasicBlock::Create(context, "app_loop", mainFunc);
  builder.CreateBr(loopBB);
  builder.SetInsertPoint(loopBB);
  builder.CreateCall(drawFunc);
  builder.CreateCall(updateFunc);
  builder.CreateBr(loopBB);
  builder.SetInsertPoint(mainBB);
  builder.CreateRetVoid();
  outs() << "\n#[LLVM IR]:\n";
  module->print(outs(), nullptr);
  bool verif = verifyFunction(*mainFunc, &outs());
  outs() << "[VERIFICATION] " << (!verif ? "OK\n\n" : "FAIL\n\n");
  outs() << "\n#[Running code]\n";
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  ExecutionEngine* ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->addGlobalMapping(module->getNamedGlobal("array1"), (void*)REG_FILE);
  ee->finalizeObject();
  ArrayRef<GenericValue> noargs;
  ee->runFunction(mainFunc, noargs);
  outs() << "#[Code was run]\n";
  simExit();
  return 0;
}
