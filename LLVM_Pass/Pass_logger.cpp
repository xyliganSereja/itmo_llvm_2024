#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

struct MyModPass : public PassInfoMixin<MyModPass> {

  bool isFuncLogger(StringRef name) {
    return name == "binOptLogger"
        || name == "callLogger" 
        || name == "funcStartLogger" 
        || name == "funcEndLogger";
  }

  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {    
    for (auto &F : M) {
      if (isFuncLogger(F.getName()) || F.isDeclaration()) {
        continue;
      }

      for (auto &B : F) {
        for (auto &I : B) {
          if (isa<PHINode>(&I)) {
            continue;
          }

          outs() << I.getOpcodeName();
          for (auto *U : I.users()) {
            if (Instruction *usedInst = dyn_cast<Instruction>(U)) {
              outs() << " <- " << usedInst->getOpcodeName();
            }
          }

          outs() << "\n";
        }
      }
    }

    outs() << "\n";
    return PreservedAnalyses::none();
  }
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    PB.registerPipelineStartEPCallback([&](ModulePassManager &MPM, auto) {
      MPM.addPass(MyModPass{});
      return true;
    });
  };

  return {LLVM_PLUGIN_API_VERSION, "MyPlugin", "0.0.1", callback};
};

/* When a plugin is loaded by the driver, it will call this entry point to
obtain information about this plugin and about how to register its passes.
*/
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getPassPluginInfo();
}
