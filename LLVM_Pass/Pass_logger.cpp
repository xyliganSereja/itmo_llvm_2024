#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
using namespace llvm;

struct MyModPass : public PassInfoMixin<MyModPass> {
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {    
      LLVMContext& Ctx = M.getContext();
      IRBuilder<> builder(Ctx);
      ArrayRef<Type*> printType = {Type::getInt8Ty(Ctx)};
      FunctionCallee printF = M.getOrInsertFunction("puts", Type::getInt32Ty(Ctx), PointerType::get(Type::getInt8Ty(Ctx), 0));
      for (auto&& F : M) {
        if (F.isDeclaration() || M.getSourceFileName() != "../SDL/app.c") continue;
        for (auto&& B : F) {
          for (auto&& I : B) {
            if (isa<PHINode>(I)) continue;
            builder.SetInsertPoint(&I);
            for (auto&& O : I.operands()) {
              if (auto *op = dyn_cast<Instruction>(O)) {
                Value* i_ptr = builder.CreateGlobalStringPtr(std::string() + I.getOpcodeName() + " <- " + op->getOpcodeName());
                builder.CreateCall(printF, {i_ptr});
              }
            }
          }
        }
      }

      return PreservedAnalyses::none();
  }
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    PB.registerOptimizerLastEPCallback([&](ModulePassManager &MPM, auto) {
      MPM.addPass(MyModPass{});
      return true;
    });
  };

  return {LLVM_PLUGIN_API_VERSION, "MyPlugin", "0.0.1", callback};
};

extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getPassPluginInfo();
}
