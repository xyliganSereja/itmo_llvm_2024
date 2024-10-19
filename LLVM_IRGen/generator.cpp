#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "../SDL/sim.h"
#include <array>
#include <string>

using namespace llvm;

constexpr std::string RUN = "run";
constexpr std::string PRINT = "print";

int main(int argc, char* argv[]) {
  if (argc != 2 || argv[1] != PRINT && argv[1] != RUN) {
    outs() << "either \"print\" or \"run\" expected\n";
    return 1;
  }
  
  LLVMContext context;
  Module *module = new Module("app.c", context);
  IRBuilder<> builder(context);
  Function *funcinit_game = Function::Create(FunctionType::get(Type::getVoidTy(context), { PointerType::get(context, 0), PointerType::get(context, 0) }, false), Function::ExternalLinkage, "init_game", module);
  Function *funcsimRand = Function::Create(FunctionType::get(Type::getInt32Ty(context), {  }, false), Function::ExternalLinkage, "simRand", module);
  Function *funcdraw = Function::Create(FunctionType::get(Type::getVoidTy(context), { PointerType::get(context, 0), PointerType::get(context, 0) }, false), Function::ExternalLinkage, "draw", module);
  Function *funcsimFlush = Function::Create(FunctionType::get(Type::getVoidTy(context), {  }, false), Function::ExternalLinkage, "simFlush", module);
  Function *funcsimPutPixel = Function::Create(FunctionType::get(Type::getVoidTy(context), { Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "simPutPixel", module);
  Function *funcget_state = Function::Create(FunctionType::get(Type::getInt32Ty(context), { Type::getInt32Ty(context), Type::getInt32Ty(context), PointerType::get(context, 0), PointerType::get(context, 0) }, false), Function::ExternalLinkage, "get_state", module);
  Function *funcget_count_neib = Function::Create(FunctionType::get(Type::getInt32Ty(context), { Type::getInt32Ty(context), Type::getInt32Ty(context), PointerType::get(context, 0), PointerType::get(context, 0) }, false), Function::ExternalLinkage, "get_count_neib", module);
  Function *funcupdate = Function::Create(FunctionType::get(Type::getVoidTy(context), { PointerType::get(context, 0), PointerType::get(context, 0) }, false), Function::ExternalLinkage, "update", module);
  Function *funcapp = Function::Create(FunctionType::get(Type::getVoidTy(context), {  }, false), Function::ExternalLinkage, "app", module);
  Function *funcllvm_lifetime_start_p0 = Function::Create(FunctionType::get(Type::getVoidTy(context), { Type::getInt64Ty(context), PointerType::get(context, 0) }, false), Function::ExternalLinkage, "llvm.lifetime.start.p0", module);
  {
    Function *func = funcinit_game;
    BasicBlock *val2 = BasicBlock::Create(context, "", func);
    BasicBlock *val3 = BasicBlock::Create(context, "", func);
    BasicBlock *val5 = BasicBlock::Create(context, "", func);
    BasicBlock *val6 = BasicBlock::Create(context, "", func);
    BasicBlock *val9 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    builder.SetInsertPoint(val2);
    //   br label %3
    builder.CreateBr(val3);
    builder.SetInsertPoint(val3);
    //   %4 = phi i64 [ 0, %2 ], [ %7, %6 ]
    PHINode *val4 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   br label %9
    builder.CreateBr(val9);
    builder.SetInsertPoint(val5);
    //   ret void
    builder.CreateRetVoid();
    builder.SetInsertPoint(val6);
    //   %7 = add nuw nsw i64 %4, 1
    Value *val7 = builder.CreateAdd(val4, builder.getInt64(1ll), "", true, true);
    //   %8 = icmp eq i64 %7, 256
    Value *val8 = builder.CreateICmpEQ(val7, builder.getInt64(256ll), "");
    //   br i1 %8, label %5, label %3, !llvm.loop !5
    builder.CreateCondBr(val8, val5, val3);
    builder.SetInsertPoint(val9);
    //   %10 = phi i64 [ 0, %3 ], [ %14, %9 ]
    PHINode *val10 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %11 = tail call i32 (...) @simRand() #6
    Value *val11 = builder.CreateCall(funcsimRand, {});
    //   %12 = srem i32 %11, 2
    Value *val12 = wtf;
    //   %13 = getelementptr inbounds [512 x i32], ptr %0, i64 %4, i64 %10
    Value *val13 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val0, {val4, val10});
    builder.Insert(val13);
    //   store i32 %12, ptr %13, align 4, !tbaa !7
    builder.CreateAlignedStore(val12, val13, MaybeAlign(4));
    //   %14 = add nuw nsw i64 %10, 1
    Value *val14 = builder.CreateAdd(val10, builder.getInt64(1ll), "", true, true);
    //   %15 = icmp eq i64 %14, 512
    Value *val15 = builder.CreateICmpEQ(val14, builder.getInt64(512ll), "");
    //   br i1 %15, label %6, label %9, !llvm.loop !11
    builder.CreateCondBr(val15, val6, val9);
    val4->addIncoming(builder.getInt64(0ll), val2);
    val4->addIncoming(val7, val6);
    val10->addIncoming(builder.getInt64(0ll), val3);
    val10->addIncoming(val14, val9);
  }
  {
    Function *func = funcdraw;
    BasicBlock *val2 = BasicBlock::Create(context, "", func);
    BasicBlock *val3 = BasicBlock::Create(context, "", func);
    BasicBlock *val6 = BasicBlock::Create(context, "", func);
    BasicBlock *val7 = BasicBlock::Create(context, "", func);
    BasicBlock *val10 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    builder.SetInsertPoint(val2);
    //   br label %3
    builder.CreateBr(val3);
    builder.SetInsertPoint(val3);
    //   %4 = phi i64 [ 0, %2 ], [ %8, %7 ]
    PHINode *val4 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %5 = trunc i64 %4 to i32
    Value *val5 = builder.CreateTrunc(val4, Type::getInt32Ty(context));
    //   br label %10
    builder.CreateBr(val10);
    builder.SetInsertPoint(val6);
    //   tail call void (...) @simFlush() #6
    builder.CreateCall(funcsimFlush, {});
    //   ret void
    builder.CreateRetVoid();
    builder.SetInsertPoint(val7);
    //   %8 = add nuw nsw i64 %4, 1
    Value *val8 = builder.CreateAdd(val4, builder.getInt64(1ll), "", true, true);
    //   %9 = icmp eq i64 %8, 256
    Value *val9 = builder.CreateICmpEQ(val8, builder.getInt64(256ll), "");
    //   br i1 %9, label %6, label %3, !llvm.loop !5
    builder.CreateCondBr(val9, val6, val3);
    builder.SetInsertPoint(val10);
    //   %11 = phi i64 [ 0, %3 ], [ %17, %10 ]
    PHINode *val11 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %12 = getelementptr inbounds [512 x i32], ptr %0, i64 %4, i64 %11
    Value *val12 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val0, {val4, val11});
    builder.Insert(val12);
    //   %13 = load i32, ptr %12, align 4, !tbaa !7
    Value *val13 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val12, MaybeAlign(4));
    //   %14 = icmp eq i32 %13, 0
    Value *val14 = builder.CreateICmpEQ(val13, builder.getInt32(0), "");
    //   %15 = select i1 %14, i32 -16777216, i32 -16711936
    Value *val15 = builder.CreateSelect(val14, builder.getInt32(-16777216), builder.getInt32(-16711936));
    //   %16 = trunc i64 %11 to i32
    Value *val16 = builder.CreateTrunc(val11, Type::getInt32Ty(context));
    //   tail call void @simPutPixel(i32 noundef %16, i32 noundef %5, i32 noundef %15) #6
    builder.CreateCall(funcsimPutPixel, {val16, val5, val15});
    //   %17 = add nuw nsw i64 %11, 1
    Value *val17 = builder.CreateAdd(val11, builder.getInt64(1ll), "", true, true);
    //   %18 = icmp eq i64 %17, 512
    Value *val18 = builder.CreateICmpEQ(val17, builder.getInt64(512ll), "");
    //   br i1 %18, label %7, label %10, !llvm.loop !11
    builder.CreateCondBr(val18, val7, val10);
    val4->addIncoming(builder.getInt64(0ll), val2);
    val4->addIncoming(val8, val7);
    val11->addIncoming(builder.getInt64(0ll), val3);
    val11->addIncoming(val17, val10);
  }
  {
    Function *func = funcget_state;
    BasicBlock *val4 = BasicBlock::Create(context, "", func);
    BasicBlock *val11 = BasicBlock::Create(context, "", func);
    BasicBlock *val16 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    Value *val2 = func->getArg(2);
    Value *val3 = func->getArg(3);
    builder.SetInsertPoint(val4);
    //   %5 = or i32 %1, %0
    Value *val5 = builder.CreateOr(val1, val0, "");
    //   %6 = icmp sgt i32 %5, -1
    Value *val6 = builder.CreateICmpSGT(val5, builder.getInt32(-1), "");
    //   %7 = icmp slt i32 %0, 512
    Value *val7 = builder.CreateICmpSLT(val0, builder.getInt32(512), "");
    //   %8 = and i1 %7, %6
    Value *val8 = builder.CreateAnd(val7, val6, "");
    //   %9 = icmp slt i32 %1, 256
    Value *val9 = builder.CreateICmpSLT(val1, builder.getInt32(256), "");
    //   %10 = and i1 %9, %8
    Value *val10 = builder.CreateAnd(val9, val8, "");
    //   br i1 %10, label %11, label %16
    builder.CreateCondBr(val10, val11, val16);
    builder.SetInsertPoint(val11);
    //   %12 = zext nneg i32 %1 to i64
    Value *val12 = builder.CreateZExt(val1, Type::getInt64Ty(context));
    //   %13 = zext nneg i32 %0 to i64
    Value *val13 = builder.CreateZExt(val0, Type::getInt64Ty(context));
    //   %14 = getelementptr inbounds [512 x i32], ptr %2, i64 %12, i64 %13
    Value *val14 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val2, {val12, val13});
    builder.Insert(val14);
    //   %15 = load i32, ptr %14, align 4, !tbaa !5
    Value *val15 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val14, MaybeAlign(4));
    //   br label %16
    builder.CreateBr(val16);
    builder.SetInsertPoint(val16);
    //   %17 = phi i32 [ %15, %11 ], [ 0, %4 ]
    PHINode *val17 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   ret i32 %17
    builder.CreateRet(val17);
    val17->addIncoming(val15, val11);
    val17->addIncoming(builder.getInt32(0), val4);
  }
  {
    Function *func = funcget_count_neib;
    BasicBlock *val4 = BasicBlock::Create(context, "", func);
    BasicBlock *val12 = BasicBlock::Create(context, "", func);
    BasicBlock *val17 = BasicBlock::Create(context, "", func);
    BasicBlock *val26 = BasicBlock::Create(context, "", func);
    BasicBlock *val31 = BasicBlock::Create(context, "", func);
    BasicBlock *val39 = BasicBlock::Create(context, "", func);
    BasicBlock *val44 = BasicBlock::Create(context, "", func);
    BasicBlock *val52 = BasicBlock::Create(context, "", func);
    BasicBlock *val57 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    Value *val2 = func->getArg(2);
    Value *val3 = func->getArg(3);
    builder.SetInsertPoint(val4);
    //   %5 = add nsw i32 %1, -1
    Value *val5 = builder.CreateAdd(val1, builder.getInt32(-1), "", false, true);
    //   %6 = or i32 %5, %0
    Value *val6 = builder.CreateOr(val5, val0, "");
    //   %7 = icmp sgt i32 %6, -1
    Value *val7 = builder.CreateICmpSGT(val6, builder.getInt32(-1), "");
    //   %8 = icmp slt i32 %0, 512
    Value *val8 = builder.CreateICmpSLT(val0, builder.getInt32(512), "");
    //   %9 = icmp slt i32 %1, 257
    Value *val9 = builder.CreateICmpSLT(val1, builder.getInt32(257), "");
    //   %10 = and i1 %9, %7
    Value *val10 = builder.CreateAnd(val9, val7, "");
    //   %11 = and i1 %8, %10
    Value *val11 = builder.CreateAnd(val8, val10, "");
    //   br i1 %11, label %12, label %17
    builder.CreateCondBr(val11, val12, val17);
    builder.SetInsertPoint(val12);
    //   %13 = zext nneg i32 %5 to i64
    Value *val13 = builder.CreateZExt(val5, Type::getInt64Ty(context));
    //   %14 = zext nneg i32 %0 to i64
    Value *val14 = builder.CreateZExt(val0, Type::getInt64Ty(context));
    //   %15 = getelementptr inbounds [512 x i32], ptr %2, i64 %13, i64 %14
    Value *val15 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val2, {val13, val14});
    builder.Insert(val15);
    //   %16 = load i32, ptr %15, align 4, !tbaa !5
    Value *val16 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val15, MaybeAlign(4));
    //   br label %17
    builder.CreateBr(val17);
    builder.SetInsertPoint(val17);
    //   %18 = phi i32 [ %16, %12 ], [ 0, %4 ]
    PHINode *val18 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %19 = add nsw i32 %0, -1
    Value *val19 = builder.CreateAdd(val0, builder.getInt32(-1), "", false, true);
    //   %20 = or i32 %19, %1
    Value *val20 = builder.CreateOr(val19, val1, "");
    //   %21 = icmp sgt i32 %20, -1
    Value *val21 = builder.CreateICmpSGT(val20, builder.getInt32(-1), "");
    //   %22 = icmp slt i32 %0, 513
    Value *val22 = builder.CreateICmpSLT(val0, builder.getInt32(513), "");
    //   %23 = and i1 %22, %21
    Value *val23 = builder.CreateAnd(val22, val21, "");
    //   %24 = icmp slt i32 %1, 256
    Value *val24 = builder.CreateICmpSLT(val1, builder.getInt32(256), "");
    //   %25 = and i1 %24, %23
    Value *val25 = builder.CreateAnd(val24, val23, "");
    //   br i1 %25, label %26, label %31
    builder.CreateCondBr(val25, val26, val31);
    builder.SetInsertPoint(val26);
    //   %27 = zext nneg i32 %1 to i64
    Value *val27 = builder.CreateZExt(val1, Type::getInt64Ty(context));
    //   %28 = zext nneg i32 %19 to i64
    Value *val28 = builder.CreateZExt(val19, Type::getInt64Ty(context));
    //   %29 = getelementptr inbounds [512 x i32], ptr %2, i64 %27, i64 %28
    Value *val29 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val2, {val27, val28});
    builder.Insert(val29);
    //   %30 = load i32, ptr %29, align 4, !tbaa !5
    Value *val30 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val29, MaybeAlign(4));
    //   br label %31
    builder.CreateBr(val31);
    builder.SetInsertPoint(val31);
    //   %32 = phi i32 [ %30, %26 ], [ 0, %17 ]
    PHINode *val32 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %33 = add nsw i32 %1, 1
    Value *val33 = builder.CreateAdd(val1, builder.getInt32(1), "", false, true);
    //   %34 = or i32 %33, %0
    Value *val34 = builder.CreateOr(val33, val0, "");
    //   %35 = icmp sgt i32 %34, -1
    Value *val35 = builder.CreateICmpSGT(val34, builder.getInt32(-1), "");
    //   %36 = icmp slt i32 %1, 255
    Value *val36 = builder.CreateICmpSLT(val1, builder.getInt32(255), "");
    //   %37 = and i1 %36, %35
    Value *val37 = builder.CreateAnd(val36, val35, "");
    //   %38 = and i1 %8, %37
    Value *val38 = builder.CreateAnd(val8, val37, "");
    //   br i1 %38, label %39, label %44
    builder.CreateCondBr(val38, val39, val44);
    builder.SetInsertPoint(val39);
    //   %40 = zext nneg i32 %33 to i64
    Value *val40 = builder.CreateZExt(val33, Type::getInt64Ty(context));
    //   %41 = zext nneg i32 %0 to i64
    Value *val41 = builder.CreateZExt(val0, Type::getInt64Ty(context));
    //   %42 = getelementptr inbounds [512 x i32], ptr %2, i64 %40, i64 %41
    Value *val42 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val2, {val40, val41});
    builder.Insert(val42);
    //   %43 = load i32, ptr %42, align 4, !tbaa !5
    Value *val43 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val42, MaybeAlign(4));
    //   br label %44
    builder.CreateBr(val44);
    builder.SetInsertPoint(val44);
    //   %45 = phi i32 [ %43, %39 ], [ 0, %31 ]
    PHINode *val45 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %46 = add nsw i32 %0, 1
    Value *val46 = builder.CreateAdd(val0, builder.getInt32(1), "", false, true);
    //   %47 = or i32 %46, %1
    Value *val47 = builder.CreateOr(val46, val1, "");
    //   %48 = icmp sgt i32 %47, -1
    Value *val48 = builder.CreateICmpSGT(val47, builder.getInt32(-1), "");
    //   %49 = icmp slt i32 %0, 511
    Value *val49 = builder.CreateICmpSLT(val0, builder.getInt32(511), "");
    //   %50 = and i1 %49, %48
    Value *val50 = builder.CreateAnd(val49, val48, "");
    //   %51 = and i1 %24, %50
    Value *val51 = builder.CreateAnd(val24, val50, "");
    //   br i1 %51, label %52, label %57
    builder.CreateCondBr(val51, val52, val57);
    builder.SetInsertPoint(val52);
    //   %53 = zext nneg i32 %1 to i64
    Value *val53 = builder.CreateZExt(val1, Type::getInt64Ty(context));
    //   %54 = zext nneg i32 %46 to i64
    Value *val54 = builder.CreateZExt(val46, Type::getInt64Ty(context));
    //   %55 = getelementptr inbounds [512 x i32], ptr %2, i64 %53, i64 %54
    Value *val55 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val2, {val53, val54});
    builder.Insert(val55);
    //   %56 = load i32, ptr %55, align 4, !tbaa !5
    Value *val56 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val55, MaybeAlign(4));
    //   br label %57
    builder.CreateBr(val57);
    builder.SetInsertPoint(val57);
    //   %58 = phi i32 [ %56, %52 ], [ 0, %44 ]
    PHINode *val58 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %59 = add nsw i32 %32, %18
    Value *val59 = builder.CreateAdd(val32, val18, "", false, true);
    //   %60 = add nsw i32 %59, %45
    Value *val60 = builder.CreateAdd(val59, val45, "", false, true);
    //   %61 = add nsw i32 %60, %58
    Value *val61 = builder.CreateAdd(val60, val58, "", false, true);
    //   ret i32 %61
    builder.CreateRet(val61);
    val18->addIncoming(val16, val12);
    val18->addIncoming(builder.getInt32(0), val4);
    val32->addIncoming(val30, val26);
    val32->addIncoming(builder.getInt32(0), val17);
    val45->addIncoming(val43, val39);
    val45->addIncoming(builder.getInt32(0), val31);
    val58->addIncoming(val56, val52);
    val58->addIncoming(builder.getInt32(0), val44);
  }
  {
    Function *func = funcupdate;
    BasicBlock *val2 = BasicBlock::Create(context, "", func);
    BasicBlock *val4 = BasicBlock::Create(context, "", func);
    BasicBlock *val10 = BasicBlock::Create(context, "", func);
    BasicBlock *val13 = BasicBlock::Create(context, "", func);
    BasicBlock *val17 = BasicBlock::Create(context, "", func);
    BasicBlock *val27 = BasicBlock::Create(context, "", func);
    BasicBlock *val30 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader10 = BasicBlock::Create(context, "", func);
    BasicBlock *val31 = BasicBlock::Create(context, "", func);
    BasicBlock *val32 = BasicBlock::Create(context, "", func);
    BasicBlock *val36 = BasicBlock::Create(context, "", func);
    BasicBlock *val37 = BasicBlock::Create(context, "", func);
    BasicBlock *val38 = BasicBlock::Create(context, "", func);
    BasicBlock *val40 = BasicBlock::Create(context, "", func);
    BasicBlock *val44 = BasicBlock::Create(context, "", func);
    BasicBlock *val46 = BasicBlock::Create(context, "", func);
    BasicBlock *val50 = BasicBlock::Create(context, "", func);
    BasicBlock *val56 = BasicBlock::Create(context, "", func);
    BasicBlock *val61 = BasicBlock::Create(context, "", func);
    BasicBlock *val67 = BasicBlock::Create(context, "", func);
    BasicBlock *val70 = BasicBlock::Create(context, "", func);
    BasicBlock *val78 = BasicBlock::Create(context, "", func);
    BasicBlock *val82 = BasicBlock::Create(context, "", func);
    BasicBlock *val83 = BasicBlock::Create(context, "", func);
    BasicBlock *val84 = BasicBlock::Create(context, "", func);
    BasicBlock *val87 = BasicBlock::Create(context, "", func);
    BasicBlock *val88 = BasicBlock::Create(context, "", func);
    BasicBlock *val89 = BasicBlock::Create(context, "", func);
    BasicBlock *val91 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader4 = BasicBlock::Create(context, "", func);
    BasicBlock *val109 = BasicBlock::Create(context, "", func);
    BasicBlock *val_loopexit = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    builder.SetInsertPoint(val2);
    //   %3 = ptrtoint ptr %1 to i64
    Value *val3 = wtf;
    //   br label %4
    builder.CreateBr(val4);
    builder.SetInsertPoint(val4);
    //   %5 = phi i64 [ 0, %2 ], [ %9, %38 ]
    PHINode *val5 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %6 = icmp eq i64 %5, 0
    Value *val6 = builder.CreateICmpEQ(val5, builder.getInt64(0ll), "");
    //   %7 = icmp eq i64 %5, 255
    Value *val7 = builder.CreateICmpEQ(val5, builder.getInt64(255ll), "");
    //   %8 = add nsw i64 %5, -1
    Value *val8 = builder.CreateAdd(val5, builder.getInt64(-1ll), "", false, true);
    //   %9 = add nuw nsw i64 %5, 1
    Value *val9 = builder.CreateAdd(val5, builder.getInt64(1ll), "", true, true);
    //   br i1 %6, label %13, label %10
    builder.CreateCondBr(val6, val13, val10);
    builder.SetInsertPoint(val10);
    //   %11 = getelementptr inbounds [512 x i32], ptr %0, i64 %8, i64 0
    Value *val11 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val0, {val8, builder.getInt64(0ll)});
    builder.Insert(val11);
    //   %12 = load i32, ptr %11, align 4, !tbaa !5
    Value *val12 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val11, MaybeAlign(4));
    //   br i1 %7, label %17, label %13
    builder.CreateCondBr(val7, val17, val13);
    builder.SetInsertPoint(val13);
    //   %14 = phi i32 [ %12, %10 ], [ 0, %4 ]
    PHINode *val14 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %15 = getelementptr inbounds [512 x i32], ptr %0, i64 %9, i64 0
    Value *val15 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val0, {val9, builder.getInt64(0ll)});
    builder.Insert(val15);
    //   %16 = load i32, ptr %15, align 4, !tbaa !5
    Value *val16 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val15, MaybeAlign(4));
    //   br label %17
    builder.CreateBr(val17);
    builder.SetInsertPoint(val17);
    //   %18 = phi i32 [ %14, %13 ], [ %12, %10 ]
    PHINode *val18 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %19 = phi i32 [ %16, %13 ], [ 0, %10 ]
    PHINode *val19 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %20 = getelementptr inbounds [512 x i32], ptr %0, i64 %5, i64 1
    Value *val20 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val0, {val5, builder.getInt64(1ll)});
    builder.Insert(val20);
    //   %21 = load i32, ptr %20, align 4, !tbaa !5
    Value *val21 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val20, MaybeAlign(4));
    //   %22 = add nsw i32 %19, %18
    Value *val22 = builder.CreateAdd(val19, val18, "", false, true);
    //   %23 = add nsw i32 %22, %21
    Value *val23 = builder.CreateAdd(val22, val21, "", false, true);
    //   %24 = getelementptr inbounds [512 x i32], ptr %0, i64 %5, i64 0
    Value *val24 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val0, {val5, builder.getInt64(0ll)});
    builder.Insert(val24);
    //   %25 = load i32, ptr %24, align 4, !tbaa !5
    Value *val25 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val24, MaybeAlign(4));
    //   %26 = icmp eq i32 %25, 1
    Value *val26 = builder.CreateICmpEQ(val25, builder.getInt32(1), "");
    //   br i1 %26, label %32, label %27
    builder.CreateCondBr(val26, val32, val27);
    builder.SetInsertPoint(val27);
    //   %28 = icmp eq i32 %23, 3
    Value *val28 = builder.CreateICmpEQ(val23, builder.getInt32(3), "");
    //   %29 = getelementptr inbounds [512 x i32], ptr %1, i64 %5, i64 0
    Value *val29 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val1, {val5, builder.getInt64(0ll)});
    builder.Insert(val29);
    //   br i1 %28, label %31, label %30
    builder.CreateCondBr(val28, val31, val30);
    builder.SetInsertPoint(val30);
    //   store i32 0, ptr %29, align 4, !tbaa !5
    builder.CreateAlignedStore(builder.getInt32(0), val29, MaybeAlign(4));
    //   br label %.preheader10
    builder.CreateBr(val_preheader10);
    builder.SetInsertPoint(val_preheader10);
    //   br label %44
    builder.CreateBr(val44);
    builder.SetInsertPoint(val31);
    //   store i32 1, ptr %29, align 4, !tbaa !5
    builder.CreateAlignedStore(builder.getInt32(1), val29, MaybeAlign(4));
    //   br label %.preheader10
    builder.CreateBr(val_preheader10);
    builder.SetInsertPoint(val32);
    //   %33 = and i32 %23, -2
    Value *val33 = builder.CreateAnd(val23, builder.getInt32(-2), "");
    //   %34 = icmp eq i32 %33, 2
    Value *val34 = builder.CreateICmpEQ(val33, builder.getInt32(2), "");
    //   %35 = getelementptr inbounds [512 x i32], ptr %1, i64 %5, i64 0
    Value *val35 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val1, {val5, builder.getInt64(0ll)});
    builder.Insert(val35);
    //   br i1 %34, label %37, label %36
    builder.CreateCondBr(val34, val37, val36);
    builder.SetInsertPoint(val36);
    //   store i32 0, ptr %35, align 4, !tbaa !5
    builder.CreateAlignedStore(builder.getInt32(0), val35, MaybeAlign(4));
    //   br label %.preheader10
    builder.CreateBr(val_preheader10);
    builder.SetInsertPoint(val37);
    //   store i32 1, ptr %35, align 4, !tbaa !5
    builder.CreateAlignedStore(builder.getInt32(1), val35, MaybeAlign(4));
    //   br label %.preheader10
    builder.CreateBr(val_preheader10);
    builder.SetInsertPoint(val38);
    //   %39 = icmp eq i64 %9, 256
    Value *val39 = builder.CreateICmpEQ(val9, builder.getInt64(256ll), "");
    //   br i1 %39, label %40, label %4, !llvm.loop !9
    builder.CreateCondBr(val39, val40, val4);
    builder.SetInsertPoint(val40);
    //   %41 = ptrtoint ptr %0 to i64
    Value *val41 = wtf;
    //   %42 = sub i64 %41, %3
    Value *val42 = builder.CreateSub(val41, val3, "", false, false);
    //   %43 = icmp ult i64 %42, 32
    Value *val43 = builder.CreateICmpULT(val42, builder.getInt64(32ll), "");
    //   br label %91
    builder.CreateBr(val91);
    builder.SetInsertPoint(val44);
    //   %45 = phi i64 [ %65, %89 ], [ 1, %.preheader10 ]
    PHINode *val45 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   br i1 %6, label %46, label %50
    builder.CreateCondBr(val6, val46, val50);
    builder.SetInsertPoint(val46);
    //   %47 = add nsw i64 %45, -1
    Value *val47 = builder.CreateAdd(val45, builder.getInt64(-1ll), "", false, true);
    //   %48 = getelementptr inbounds [512 x i32], ptr %0, i64 0, i64 %47
    Value *val48 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val0, {builder.getInt64(0ll), val47});
    builder.Insert(val48);
    //   %49 = load i32, ptr %48, align 4, !tbaa !5
    Value *val49 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val48, MaybeAlign(4));
    //   br label %56
    builder.CreateBr(val56);
    builder.SetInsertPoint(val50);
    //   %51 = getelementptr inbounds [512 x i32], ptr %0, i64 %8, i64 %45
    Value *val51 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val0, {val8, val45});
    builder.Insert(val51);
    //   %52 = load i32, ptr %51, align 4, !tbaa !5
    Value *val52 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val51, MaybeAlign(4));
    //   %53 = add nsw i64 %45, -1
    Value *val53 = builder.CreateAdd(val45, builder.getInt64(-1ll), "", false, true);
    //   %54 = getelementptr inbounds [512 x i32], ptr %0, i64 %5, i64 %53
    Value *val54 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val0, {val5, val53});
    builder.Insert(val54);
    //   %55 = load i32, ptr %54, align 4, !tbaa !5
    Value *val55 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val54, MaybeAlign(4));
    //   br i1 %7, label %61, label %56
    builder.CreateCondBr(val7, val61, val56);
    builder.SetInsertPoint(val56);
    //   %57 = phi i32 [ %49, %46 ], [ %55, %50 ]
    PHINode *val57 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %58 = phi i32 [ 0, %46 ], [ %52, %50 ]
    PHINode *val58 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %59 = getelementptr inbounds [512 x i32], ptr %0, i64 %9, i64 %45
    Value *val59 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val0, {val9, val45});
    builder.Insert(val59);
    //   %60 = load i32, ptr %59, align 4, !tbaa !5
    Value *val60 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val59, MaybeAlign(4));
    //   br label %61
    builder.CreateBr(val61);
    builder.SetInsertPoint(val61);
    //   %62 = phi i32 [ %57, %56 ], [ %55, %50 ]
    PHINode *val62 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %63 = phi i32 [ %58, %56 ], [ %52, %50 ]
    PHINode *val63 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %64 = phi i32 [ %60, %56 ], [ 0, %50 ]
    PHINode *val64 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %65 = add nuw nsw i64 %45, 1
    Value *val65 = builder.CreateAdd(val45, builder.getInt64(1ll), "", true, true);
    //   %66 = icmp eq i64 %45, 511
    Value *val66 = builder.CreateICmpEQ(val45, builder.getInt64(511ll), "");
    //   br i1 %66, label %70, label %67
    builder.CreateCondBr(val66, val70, val67);
    builder.SetInsertPoint(val67);
    //   %68 = getelementptr inbounds [512 x i32], ptr %0, i64 %5, i64 %65
    Value *val68 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val0, {val5, val65});
    builder.Insert(val68);
    //   %69 = load i32, ptr %68, align 4, !tbaa !5
    Value *val69 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val68, MaybeAlign(4));
    //   br label %70
    builder.CreateBr(val70);
    builder.SetInsertPoint(val70);
    //   %71 = phi i32 [ %69, %67 ], [ 0, %61 ]
    PHINode *val71 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %72 = add nsw i32 %63, %62
    Value *val72 = builder.CreateAdd(val63, val62, "", false, true);
    //   %73 = add nsw i32 %72, %64
    Value *val73 = builder.CreateAdd(val72, val64, "", false, true);
    //   %74 = add nsw i32 %73, %71
    Value *val74 = builder.CreateAdd(val73, val71, "", false, true);
    //   %75 = getelementptr inbounds [512 x i32], ptr %0, i64 %5, i64 %45
    Value *val75 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val0, {val5, val45});
    builder.Insert(val75);
    //   %76 = load i32, ptr %75, align 4, !tbaa !5
    Value *val76 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val75, MaybeAlign(4));
    //   %77 = icmp eq i32 %76, 1
    Value *val77 = builder.CreateICmpEQ(val76, builder.getInt32(1), "");
    //   br i1 %77, label %78, label %84
    builder.CreateCondBr(val77, val78, val84);
    builder.SetInsertPoint(val78);
    //   %79 = and i32 %74, -2
    Value *val79 = builder.CreateAnd(val74, builder.getInt32(-2), "");
    //   %80 = icmp eq i32 %79, 2
    Value *val80 = builder.CreateICmpEQ(val79, builder.getInt32(2), "");
    //   %81 = getelementptr inbounds [512 x i32], ptr %1, i64 %5, i64 %45
    Value *val81 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val1, {val5, val45});
    builder.Insert(val81);
    //   br i1 %80, label %82, label %83
    builder.CreateCondBr(val80, val82, val83);
    builder.SetInsertPoint(val82);
    //   store i32 1, ptr %81, align 4, !tbaa !5
    builder.CreateAlignedStore(builder.getInt32(1), val81, MaybeAlign(4));
    //   br label %89
    builder.CreateBr(val89);
    builder.SetInsertPoint(val83);
    //   store i32 0, ptr %81, align 4, !tbaa !5
    builder.CreateAlignedStore(builder.getInt32(0), val81, MaybeAlign(4));
    //   br label %89
    builder.CreateBr(val89);
    builder.SetInsertPoint(val84);
    //   %85 = icmp eq i32 %74, 3
    Value *val85 = builder.CreateICmpEQ(val74, builder.getInt32(3), "");
    //   %86 = getelementptr inbounds [512 x i32], ptr %1, i64 %5, i64 %45
    Value *val86 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val1, {val5, val45});
    builder.Insert(val86);
    //   br i1 %85, label %87, label %88
    builder.CreateCondBr(val85, val87, val88);
    builder.SetInsertPoint(val87);
    //   store i32 1, ptr %86, align 4, !tbaa !5
    builder.CreateAlignedStore(builder.getInt32(1), val86, MaybeAlign(4));
    //   br label %89
    builder.CreateBr(val89);
    builder.SetInsertPoint(val88);
    //   store i32 0, ptr %86, align 4, !tbaa !5
    builder.CreateAlignedStore(builder.getInt32(0), val86, MaybeAlign(4));
    //   br label %89
    builder.CreateBr(val89);
    builder.SetInsertPoint(val89);
    //   %90 = icmp eq i64 %65, 512
    Value *val90 = builder.CreateICmpEQ(val65, builder.getInt64(512ll), "");
    //   br i1 %90, label %38, label %44, !llvm.loop !11
    builder.CreateCondBr(val90, val38, val44);
    builder.SetInsertPoint(val91);
    //   %92 = phi i64 [ %110, %.loopexit ], [ 0, %40 ]
    PHINode *val92 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   br i1 %43, label %.preheader, label %.preheader4
    builder.CreateCondBr(val43, val_preheader, val_preheader4);
    builder.SetInsertPoint(val_preheader4);
    //   %93 = phi i64 [ %107, %.preheader4 ], [ 0, %91 ]
    PHINode *val93 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %94 = getelementptr inbounds [512 x i32], ptr %1, i64 %92, i64 %93
    Value *val94 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val1, {val92, val93});
    builder.Insert(val94);
    //   %95 = getelementptr inbounds i32, ptr %94, i64 4
    Value *val95 = GetElementPtrInst::Create(Type::getInt32Ty(context), val94, {builder.getInt64(4ll)});
    builder.Insert(val95);
    //   %96 = load <4 x i32>, ptr %94, align 4, !tbaa !5
    Value *val96 = builder.CreateAlignedLoad(, val94, MaybeAlign(4));
    //   %97 = load <4 x i32>, ptr %95, align 4, !tbaa !5
    Value *val97 = builder.CreateAlignedLoad(, val95, MaybeAlign(4));
    //   %98 = getelementptr inbounds [512 x i32], ptr %0, i64 %92, i64 %93
    Value *val98 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val0, {val92, val93});
    builder.Insert(val98);
    //   %99 = getelementptr inbounds i32, ptr %98, i64 4
    Value *val99 = GetElementPtrInst::Create(Type::getInt32Ty(context), val98, {builder.getInt64(4ll)});
    builder.Insert(val99);
    //   store <4 x i32> %96, ptr %98, align 4, !tbaa !5
    builder.CreateAlignedStore(val96, val98, MaybeAlign(4));
    //   store <4 x i32> %97, ptr %99, align 4, !tbaa !5
    builder.CreateAlignedStore(val97, val99, MaybeAlign(4));
    //   %100 = or disjoint i64 %93, 8
    Value *val100 = builder.CreateOr(val93, builder.getInt64(8ll), "");
    //   %101 = getelementptr inbounds [512 x i32], ptr %1, i64 %92, i64 %100
    Value *val101 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val1, {val92, val100});
    builder.Insert(val101);
    //   %102 = getelementptr inbounds i32, ptr %101, i64 4
    Value *val102 = GetElementPtrInst::Create(Type::getInt32Ty(context), val101, {builder.getInt64(4ll)});
    builder.Insert(val102);
    //   %103 = load <4 x i32>, ptr %101, align 4, !tbaa !5
    Value *val103 = builder.CreateAlignedLoad(, val101, MaybeAlign(4));
    //   %104 = load <4 x i32>, ptr %102, align 4, !tbaa !5
    Value *val104 = builder.CreateAlignedLoad(, val102, MaybeAlign(4));
    //   %105 = getelementptr inbounds [512 x i32], ptr %0, i64 %92, i64 %100
    Value *val105 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val0, {val92, val100});
    builder.Insert(val105);
    //   %106 = getelementptr inbounds i32, ptr %105, i64 4
    Value *val106 = GetElementPtrInst::Create(Type::getInt32Ty(context), val105, {builder.getInt64(4ll)});
    builder.Insert(val106);
    //   store <4 x i32> %103, ptr %105, align 4, !tbaa !5
    builder.CreateAlignedStore(val103, val105, MaybeAlign(4));
    //   store <4 x i32> %104, ptr %106, align 4, !tbaa !5
    builder.CreateAlignedStore(val104, val106, MaybeAlign(4));
    //   %107 = add nuw nsw i64 %93, 16
    Value *val107 = builder.CreateAdd(val93, builder.getInt64(16ll), "", true, true);
    //   %108 = icmp eq i64 %107, 512
    Value *val108 = builder.CreateICmpEQ(val107, builder.getInt64(512ll), "");
    //   br i1 %108, label %.loopexit, label %.preheader4, !llvm.loop !13
    builder.CreateCondBr(val108, val_loopexit, val_preheader4);
    builder.SetInsertPoint(val109);
    //   ret void
    builder.CreateRetVoid();
    builder.SetInsertPoint(val_loopexit);
    //   %110 = add nuw nsw i64 %92, 1
    Value *val110 = builder.CreateAdd(val92, builder.getInt64(1ll), "", true, true);
    //   %111 = icmp eq i64 %110, 256
    Value *val111 = builder.CreateICmpEQ(val110, builder.getInt64(256ll), "");
    //   br i1 %111, label %109, label %91, !llvm.loop !16
    builder.CreateCondBr(val111, val109, val91);
    builder.SetInsertPoint(val_preheader);
    //   %112 = phi i64 [ %128, %.preheader ], [ 0, %91 ]
    PHINode *val112 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %113 = getelementptr inbounds [512 x i32], ptr %1, i64 %92, i64 %112
    Value *val113 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val1, {val92, val112});
    builder.Insert(val113);
    //   %114 = load i32, ptr %113, align 4, !tbaa !5
    Value *val114 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val113, MaybeAlign(4));
    //   %115 = getelementptr inbounds [512 x i32], ptr %0, i64 %92, i64 %112
    Value *val115 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val0, {val92, val112});
    builder.Insert(val115);
    //   store i32 %114, ptr %115, align 4, !tbaa !5
    builder.CreateAlignedStore(val114, val115, MaybeAlign(4));
    //   %116 = or disjoint i64 %112, 1
    Value *val116 = builder.CreateOr(val112, builder.getInt64(1ll), "");
    //   %117 = getelementptr inbounds [512 x i32], ptr %1, i64 %92, i64 %116
    Value *val117 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val1, {val92, val116});
    builder.Insert(val117);
    //   %118 = load i32, ptr %117, align 4, !tbaa !5
    Value *val118 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val117, MaybeAlign(4));
    //   %119 = getelementptr inbounds [512 x i32], ptr %0, i64 %92, i64 %116
    Value *val119 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val0, {val92, val116});
    builder.Insert(val119);
    //   store i32 %118, ptr %119, align 4, !tbaa !5
    builder.CreateAlignedStore(val118, val119, MaybeAlign(4));
    //   %120 = or disjoint i64 %112, 2
    Value *val120 = builder.CreateOr(val112, builder.getInt64(2ll), "");
    //   %121 = getelementptr inbounds [512 x i32], ptr %1, i64 %92, i64 %120
    Value *val121 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val1, {val92, val120});
    builder.Insert(val121);
    //   %122 = load i32, ptr %121, align 4, !tbaa !5
    Value *val122 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val121, MaybeAlign(4));
    //   %123 = getelementptr inbounds [512 x i32], ptr %0, i64 %92, i64 %120
    Value *val123 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val0, {val92, val120});
    builder.Insert(val123);
    //   store i32 %122, ptr %123, align 4, !tbaa !5
    builder.CreateAlignedStore(val122, val123, MaybeAlign(4));
    //   %124 = or disjoint i64 %112, 3
    Value *val124 = builder.CreateOr(val112, builder.getInt64(3ll), "");
    //   %125 = getelementptr inbounds [512 x i32], ptr %1, i64 %92, i64 %124
    Value *val125 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val1, {val92, val124});
    builder.Insert(val125);
    //   %126 = load i32, ptr %125, align 4, !tbaa !5
    Value *val126 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val125, MaybeAlign(4));
    //   %127 = getelementptr inbounds [512 x i32], ptr %0, i64 %92, i64 %124
    Value *val127 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val0, {val92, val124});
    builder.Insert(val127);
    //   store i32 %126, ptr %127, align 4, !tbaa !5
    builder.CreateAlignedStore(val126, val127, MaybeAlign(4));
    //   %128 = add nuw nsw i64 %112, 4
    Value *val128 = builder.CreateAdd(val112, builder.getInt64(4ll), "", true, true);
    //   %129 = icmp eq i64 %128, 512
    Value *val129 = builder.CreateICmpEQ(val128, builder.getInt64(512ll), "");
    //   br i1 %129, label %.loopexit, label %.preheader, !llvm.loop !17
    builder.CreateCondBr(val129, val_loopexit, val_preheader);
    val5->addIncoming(builder.getInt64(0ll), val2);
    val5->addIncoming(val9, val38);
    val14->addIncoming(val12, val10);
    val14->addIncoming(builder.getInt32(0), val4);
    val18->addIncoming(val14, val13);
    val18->addIncoming(val12, val10);
    val19->addIncoming(val16, val13);
    val19->addIncoming(builder.getInt32(0), val10);
    val45->addIncoming(val65, val89);
    val45->addIncoming(builder.getInt64(1ll), val_preheader10);
    val57->addIncoming(val49, val46);
    val57->addIncoming(val55, val50);
    val58->addIncoming(builder.getInt32(0), val46);
    val58->addIncoming(val52, val50);
    val62->addIncoming(val57, val56);
    val62->addIncoming(val55, val50);
    val63->addIncoming(val58, val56);
    val63->addIncoming(val52, val50);
    val64->addIncoming(val60, val56);
    val64->addIncoming(builder.getInt32(0), val50);
    val71->addIncoming(val69, val67);
    val71->addIncoming(builder.getInt32(0), val61);
    val92->addIncoming(val110, val_loopexit);
    val92->addIncoming(builder.getInt64(0ll), val40);
    val93->addIncoming(val107, val_preheader4);
    val93->addIncoming(builder.getInt64(0ll), val91);
    val112->addIncoming(val128, val_preheader);
    val112->addIncoming(builder.getInt64(0ll), val91);
  }
  {
    Function *func = funcapp;
    BasicBlock *val0 = BasicBlock::Create(context, "", func);
    BasicBlock *val3 = BasicBlock::Create(context, "", func);
    BasicBlock *val5 = BasicBlock::Create(context, "", func);
    BasicBlock *val8 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader = BasicBlock::Create(context, "", func);
    BasicBlock *val17 = BasicBlock::Create(context, "", func);
    BasicBlock *val20 = BasicBlock::Create(context, "", func);
    BasicBlock *val29 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_backedge = BasicBlock::Create(context, "", func);
    builder.SetInsertPoint(val0);
    //   %1 = alloca [256 x [512 x i32]], align 16
    Value *val1 = builder.CreateAlloca(ArrayType::get(ArrayType::get(Type::getInt32Ty(context), 512), 256));
    //   %2 = alloca [256 x [512 x i32]], align 16
    Value *val2 = builder.CreateAlloca(ArrayType::get(ArrayType::get(Type::getInt32Ty(context), 512), 256));
    //   call void @llvm.lifetime.start.p0(i64 524288, ptr nonnull %1) #6
    builder.CreateCall(funcllvm_lifetime_start_p0, {builder.getInt64(524288ll), val1});
    //   call void @llvm.lifetime.start.p0(i64 524288, ptr nonnull %2) #6
    builder.CreateCall(funcllvm_lifetime_start_p0, {builder.getInt64(524288ll), val2});
    //   br label %3
    builder.CreateBr(val3);
    builder.SetInsertPoint(val3);
    //   %4 = phi i64 [ 0, %0 ], [ %6, %5 ]
    PHINode *val4 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   br label %8
    builder.CreateBr(val8);
    builder.SetInsertPoint(val5);
    //   %6 = add nuw nsw i64 %4, 1
    Value *val6 = builder.CreateAdd(val4, builder.getInt64(1ll), "", true, true);
    //   %7 = icmp eq i64 %6, 256
    Value *val7 = builder.CreateICmpEQ(val6, builder.getInt64(256ll), "");
    //   br i1 %7, label %.preheader, label %3, !llvm.loop !5
    builder.CreateCondBr(val7, val_preheader, val3);
    builder.SetInsertPoint(val8);
    //   %9 = phi i64 [ 0, %3 ], [ %13, %8 ]
    PHINode *val9 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %10 = tail call i32 (...) @simRand() #6
    Value *val10 = builder.CreateCall(funcsimRand, {});
    //   %11 = srem i32 %10, 2
    Value *val11 = wtf;
    //   %12 = getelementptr inbounds [512 x i32], ptr %1, i64 %4, i64 %9
    Value *val12 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val1, {val4, val9});
    builder.Insert(val12);
    //   store i32 %11, ptr %12, align 4, !tbaa !7
    builder.CreateAlignedStore(val11, val12, MaybeAlign(4));
    //   %13 = add nuw nsw i64 %9, 1
    Value *val13 = builder.CreateAdd(val9, builder.getInt64(1ll), "", true, true);
    //   %14 = icmp eq i64 %13, 512
    Value *val14 = builder.CreateICmpEQ(val13, builder.getInt64(512ll), "");
    //   br i1 %14, label %5, label %8, !llvm.loop !11
    builder.CreateCondBr(val14, val5, val8);
    builder.SetInsertPoint(val_preheader);
    //   %15 = phi i64 [ %.be, %.preheader.backedge ], [ 0, %5 ]
    PHINode *val15 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %16 = trunc i64 %15 to i32
    Value *val16 = builder.CreateTrunc(val15, Type::getInt32Ty(context));
    //   br label %20
    builder.CreateBr(val20);
    builder.SetInsertPoint(val17);
    //   %18 = add nuw nsw i64 %15, 1
    Value *val18 = builder.CreateAdd(val15, builder.getInt64(1ll), "", true, true);
    //   %19 = icmp eq i64 %18, 256
    Value *val19 = builder.CreateICmpEQ(val18, builder.getInt64(256ll), "");
    //   br i1 %19, label %29, label %.preheader.backedge
    builder.CreateCondBr(val19, val29, val_preheader_backedge);
    builder.SetInsertPoint(val20);
    //   %21 = phi i64 [ 0, %.preheader ], [ %27, %20 ]
    PHINode *val21 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %22 = getelementptr inbounds [512 x i32], ptr %1, i64 %15, i64 %21
    Value *val22 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 512), val1, {val15, val21});
    builder.Insert(val22);
    //   %23 = load i32, ptr %22, align 4, !tbaa !7
    Value *val23 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val22, MaybeAlign(4));
    //   %24 = icmp eq i32 %23, 0
    Value *val24 = builder.CreateICmpEQ(val23, builder.getInt32(0), "");
    //   %25 = select i1 %24, i32 -16777216, i32 -16711936
    Value *val25 = builder.CreateSelect(val24, builder.getInt32(-16777216), builder.getInt32(-16711936));
    //   %26 = trunc i64 %21 to i32
    Value *val26 = builder.CreateTrunc(val21, Type::getInt32Ty(context));
    //   tail call void @simPutPixel(i32 noundef %26, i32 noundef %16, i32 noundef %25) #6
    builder.CreateCall(funcsimPutPixel, {val26, val16, val25});
    //   %27 = add nuw nsw i64 %21, 1
    Value *val27 = builder.CreateAdd(val21, builder.getInt64(1ll), "", true, true);
    //   %28 = icmp eq i64 %27, 512
    Value *val28 = builder.CreateICmpEQ(val27, builder.getInt64(512ll), "");
    //   br i1 %28, label %17, label %20, !llvm.loop !12
    builder.CreateCondBr(val28, val17, val20);
    builder.SetInsertPoint(val29);
    //   tail call void (...) @simFlush() #6
    builder.CreateCall(funcsimFlush, {});
    //   call void @update(ptr noundef nonnull %1, ptr noundef nonnull %2)
    builder.CreateCall(funcupdate, {val1, val2});
    //   br label %.preheader.backedge
    builder.CreateBr(val_preheader_backedge);
    builder.SetInsertPoint(val_preheader_backedge);
    //   %.be = phi i64 [ %18, %17 ], [ 0, %29 ]
    PHINode *val_be = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   br label %.preheader, !llvm.loop !13
    builder.CreateBr(val_preheader);
    val4->addIncoming(builder.getInt64(0ll), val0);
    val4->addIncoming(val6, val5);
    val9->addIncoming(builder.getInt64(0ll), val3);
    val9->addIncoming(val13, val8);
    val15->addIncoming(val_be, val_preheader_backedge);
    val15->addIncoming(builder.getInt64(0ll), val5);
    val21->addIncoming(builder.getInt64(0ll), val_preheader);
    val21->addIncoming(val27, val20);
    val_be->addIncoming(val18, val17);
    val_be->addIncoming(builder.getInt64(0ll), val29);
  }
  
  LLVMInitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();
  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([=](const std::string &fnName) -> void * {
    if (fnName == "simPutPixel") {
      return reinterpret_cast<void *>(simPutPixel);
    }
    if (fnName == "simFlush") {
      return reinterpret_cast<void *>(simFlush);
    }
    return nullptr;
  });
  ee->finalizeObject();
  simInit();
  ee->runFunction(funcapp, {});
  simExit();
  return 0;
}
