; ModuleID = '../SDL/app.c'
source_filename = "../SDL/app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: nounwind sspstrong uwtable
define dso_local void @init_game(ptr nocapture noundef writeonly %0, ptr nocapture noundef readnone %1) local_unnamed_addr #0 {
  br label %3

3:                                                ; preds = %2, %6
  %4 = phi i64 [ 0, %2 ], [ %7, %6 ]
  br label %9

5:                                                ; preds = %6
  ret void

6:                                                ; preds = %9
  %7 = add nuw nsw i64 %4, 1
  %8 = icmp eq i64 %7, 256
  br i1 %8, label %5, label %3, !llvm.loop !5

9:                                                ; preds = %3, %9
  %10 = phi i64 [ 0, %3 ], [ %14, %9 ]
  %11 = tail call i32 (...) @simRand() #6
  %12 = srem i32 %11, 2
  %13 = getelementptr inbounds [512 x i32], ptr %0, i64 %4, i64 %10
  store i32 %12, ptr %13, align 4, !tbaa !7
  %14 = add nuw nsw i64 %10, 1
  %15 = icmp eq i64 %14, 512
  br i1 %15, label %6, label %9, !llvm.loop !11
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

declare i32 @simRand(...) local_unnamed_addr #2

; Function Attrs: nounwind sspstrong uwtable
define dso_local void @draw(ptr nocapture noundef readonly %0, ptr nocapture noundef readnone %1) local_unnamed_addr #0 {
  br label %3

3:                                                ; preds = %2, %7
  %4 = phi i64 [ 0, %2 ], [ %8, %7 ]
  %5 = trunc i64 %4 to i32
  br label %10

6:                                                ; preds = %7
  tail call void (...) @simFlush() #6
  ret void

7:                                                ; preds = %10
  %8 = add nuw nsw i64 %4, 1
  %9 = icmp eq i64 %8, 256
  br i1 %9, label %6, label %3, !llvm.loop !12

10:                                               ; preds = %3, %10
  %11 = phi i64 [ 0, %3 ], [ %17, %10 ]
  %12 = getelementptr inbounds [512 x i32], ptr %0, i64 %4, i64 %11
  %13 = load i32, ptr %12, align 4, !tbaa !7
  %14 = icmp eq i32 %13, 0
  %15 = select i1 %14, i32 -16777216, i32 -16711936
  %16 = trunc i64 %11 to i32
  tail call void @simPutPixel(i32 noundef %16, i32 noundef %5, i32 noundef %15) #6
  %17 = add nuw nsw i64 %11, 1
  %18 = icmp eq i64 %17, 512
  br i1 %18, label %7, label %10, !llvm.loop !13
}

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #2

declare void @simFlush(...) local_unnamed_addr #2

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(argmem: read) uwtable
define dso_local i32 @get_state(i32 noundef %0, i32 noundef %1, ptr nocapture noundef readonly %2, ptr nocapture noundef readnone %3) local_unnamed_addr #3 {
  %5 = or i32 %1, %0
  %6 = icmp sgt i32 %5, -1
  %7 = icmp slt i32 %0, 512
  %8 = and i1 %7, %6
  %9 = icmp slt i32 %1, 256
  %10 = and i1 %9, %8
  br i1 %10, label %11, label %16

11:                                               ; preds = %4
  %12 = zext nneg i32 %1 to i64
  %13 = zext nneg i32 %0 to i64
  %14 = getelementptr inbounds [512 x i32], ptr %2, i64 %12, i64 %13
  %15 = load i32, ptr %14, align 4, !tbaa !7
  br label %16

16:                                               ; preds = %4, %11
  %17 = phi i32 [ %15, %11 ], [ 0, %4 ]
  ret i32 %17
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(argmem: read) uwtable
define dso_local i32 @get_count_neib(i32 noundef %0, i32 noundef %1, ptr nocapture noundef readonly %2, ptr nocapture noundef readnone %3) local_unnamed_addr #3 {
  %5 = add nsw i32 %1, -1
  %6 = or i32 %5, %0
  %7 = icmp sgt i32 %6, -1
  %8 = icmp slt i32 %0, 512
  %9 = icmp slt i32 %1, 257
  %10 = and i1 %9, %7
  %11 = and i1 %8, %10
  br i1 %11, label %12, label %17

12:                                               ; preds = %4
  %13 = zext nneg i32 %5 to i64
  %14 = zext nneg i32 %0 to i64
  %15 = getelementptr inbounds [512 x i32], ptr %2, i64 %13, i64 %14
  %16 = load i32, ptr %15, align 4, !tbaa !7
  br label %17

17:                                               ; preds = %4, %12
  %18 = phi i32 [ %16, %12 ], [ 0, %4 ]
  %19 = add nsw i32 %0, -1
  %20 = or i32 %19, %1
  %21 = icmp sgt i32 %20, -1
  %22 = icmp slt i32 %0, 513
  %23 = and i1 %22, %21
  %24 = icmp slt i32 %1, 256
  %25 = and i1 %24, %23
  br i1 %25, label %26, label %31

26:                                               ; preds = %17
  %27 = zext nneg i32 %1 to i64
  %28 = zext nneg i32 %19 to i64
  %29 = getelementptr inbounds [512 x i32], ptr %2, i64 %27, i64 %28
  %30 = load i32, ptr %29, align 4, !tbaa !7
  br label %31

31:                                               ; preds = %17, %26
  %32 = phi i32 [ %30, %26 ], [ 0, %17 ]
  %33 = add nsw i32 %1, 1
  %34 = or i32 %33, %0
  %35 = icmp sgt i32 %34, -1
  %36 = icmp slt i32 %1, 255
  %37 = and i1 %36, %35
  %38 = and i1 %8, %37
  br i1 %38, label %39, label %44

39:                                               ; preds = %31
  %40 = zext nneg i32 %33 to i64
  %41 = zext nneg i32 %0 to i64
  %42 = getelementptr inbounds [512 x i32], ptr %2, i64 %40, i64 %41
  %43 = load i32, ptr %42, align 4, !tbaa !7
  br label %44

44:                                               ; preds = %31, %39
  %45 = phi i32 [ %43, %39 ], [ 0, %31 ]
  %46 = add nsw i32 %0, 1
  %47 = or i32 %46, %1
  %48 = icmp sgt i32 %47, -1
  %49 = icmp slt i32 %0, 511
  %50 = and i1 %49, %48
  %51 = and i1 %24, %50
  br i1 %51, label %52, label %57

52:                                               ; preds = %44
  %53 = zext nneg i32 %1 to i64
  %54 = zext nneg i32 %46 to i64
  %55 = getelementptr inbounds [512 x i32], ptr %2, i64 %53, i64 %54
  %56 = load i32, ptr %55, align 4, !tbaa !7
  br label %57

57:                                               ; preds = %44, %52
  %58 = phi i32 [ %56, %52 ], [ 0, %44 ]
  %59 = add nsw i32 %32, %18
  %60 = add nsw i32 %59, %45
  %61 = add nsw i32 %60, %58
  ret i32 %61
}

; Function Attrs: nofree norecurse nosync nounwind sspstrong memory(argmem: readwrite) uwtable
define dso_local void @update(ptr nocapture noundef %0, ptr nocapture noundef %1) local_unnamed_addr #4 {
  %3 = ptrtoint ptr %1 to i64
  %4 = ptrtoint ptr %0 to i64
  br label %5

5:                                                ; preds = %2, %40
  %6 = phi i64 [ 0, %2 ], [ %10, %40 ]
  %7 = icmp eq i64 %6, 0
  %8 = icmp eq i64 %6, 255
  %9 = add nsw i64 %6, -1
  %10 = add nuw nsw i64 %6, 1
  br i1 %7, label %14, label %11

11:                                               ; preds = %5
  %12 = getelementptr inbounds [512 x i32], ptr %0, i64 %9, i64 0
  %13 = load i32, ptr %12, align 4, !tbaa !7
  br i1 %8, label %18, label %14

14:                                               ; preds = %5, %11
  %15 = phi i32 [ %13, %11 ], [ 0, %5 ]
  %16 = getelementptr inbounds [512 x i32], ptr %0, i64 %10, i64 0
  %17 = load i32, ptr %16, align 4, !tbaa !7
  br label %18

18:                                               ; preds = %14, %11
  %19 = phi i32 [ %15, %14 ], [ %13, %11 ]
  %20 = phi i32 [ %17, %14 ], [ 0, %11 ]
  %21 = getelementptr inbounds [512 x i32], ptr %0, i64 %6, i64 1
  %22 = load i32, ptr %21, align 4, !tbaa !7
  %23 = add nsw i32 %19, %20
  %24 = add nsw i32 %23, %22
  %25 = getelementptr inbounds [512 x i32], ptr %0, i64 %6, i64 0
  %26 = load i32, ptr %25, align 4, !tbaa !7
  %27 = icmp eq i32 %26, 1
  br i1 %27, label %33, label %28

28:                                               ; preds = %18
  %29 = icmp eq i32 %24, 3
  %30 = getelementptr inbounds [512 x i32], ptr %1, i64 %6, i64 0
  br i1 %29, label %32, label %31

31:                                               ; preds = %28
  store i32 0, ptr %30, align 4, !tbaa !7
  br label %39

32:                                               ; preds = %28
  store i32 1, ptr %30, align 4, !tbaa !7
  br label %39

33:                                               ; preds = %18
  %34 = and i32 %24, -2
  %35 = icmp eq i32 %34, 2
  %36 = getelementptr inbounds [512 x i32], ptr %1, i64 %6, i64 0
  br i1 %35, label %38, label %37

37:                                               ; preds = %33
  store i32 0, ptr %36, align 4, !tbaa !7
  br label %39

38:                                               ; preds = %33
  store i32 1, ptr %36, align 4, !tbaa !7
  br label %39

39:                                               ; preds = %31, %32, %37, %38
  br label %45

40:                                               ; preds = %90
  %41 = icmp eq i64 %10, 256
  br i1 %41, label %42, label %5, !llvm.loop !14

42:                                               ; preds = %40
  %43 = sub i64 %4, %3
  %44 = icmp ult i64 %43, 32
  br label %92

45:                                               ; preds = %39, %90
  %46 = phi i64 [ %66, %90 ], [ 1, %39 ]
  br i1 %7, label %47, label %51

47:                                               ; preds = %45
  %48 = add nsw i64 %46, -1
  %49 = getelementptr inbounds [512 x i32], ptr %0, i64 %6, i64 %48
  %50 = load i32, ptr %49, align 4, !tbaa !7
  br label %57

51:                                               ; preds = %45
  %52 = getelementptr inbounds [512 x i32], ptr %0, i64 %9, i64 %46
  %53 = load i32, ptr %52, align 4, !tbaa !7
  %54 = add nsw i64 %46, -1
  %55 = getelementptr inbounds [512 x i32], ptr %0, i64 %6, i64 %54
  %56 = load i32, ptr %55, align 4, !tbaa !7
  br i1 %8, label %62, label %57

57:                                               ; preds = %47, %51
  %58 = phi i32 [ %50, %47 ], [ %56, %51 ]
  %59 = phi i32 [ 0, %47 ], [ %53, %51 ]
  %60 = getelementptr inbounds [512 x i32], ptr %0, i64 %10, i64 %46
  %61 = load i32, ptr %60, align 4, !tbaa !7
  br label %62

62:                                               ; preds = %57, %51
  %63 = phi i32 [ %58, %57 ], [ %56, %51 ]
  %64 = phi i32 [ %59, %57 ], [ %53, %51 ]
  %65 = phi i32 [ %61, %57 ], [ 0, %51 ]
  %66 = add nuw nsw i64 %46, 1
  %67 = icmp eq i64 %46, 511
  br i1 %67, label %71, label %68

68:                                               ; preds = %62
  %69 = getelementptr inbounds [512 x i32], ptr %0, i64 %6, i64 %66
  %70 = load i32, ptr %69, align 4, !tbaa !7
  br label %71

71:                                               ; preds = %62, %68
  %72 = phi i32 [ %70, %68 ], [ 0, %62 ]
  %73 = add nsw i32 %63, %64
  %74 = add nsw i32 %73, %65
  %75 = add nsw i32 %74, %72
  %76 = getelementptr inbounds [512 x i32], ptr %0, i64 %6, i64 %46
  %77 = load i32, ptr %76, align 4, !tbaa !7
  %78 = icmp eq i32 %77, 1
  br i1 %78, label %79, label %85

79:                                               ; preds = %71
  %80 = and i32 %75, -2
  %81 = icmp eq i32 %80, 2
  %82 = getelementptr inbounds [512 x i32], ptr %1, i64 %6, i64 %46
  br i1 %81, label %83, label %84

83:                                               ; preds = %79
  store i32 1, ptr %82, align 4, !tbaa !7
  br label %90

84:                                               ; preds = %79
  store i32 0, ptr %82, align 4, !tbaa !7
  br label %90

85:                                               ; preds = %71
  %86 = icmp eq i32 %75, 3
  %87 = getelementptr inbounds [512 x i32], ptr %1, i64 %6, i64 %46
  br i1 %86, label %88, label %89

88:                                               ; preds = %85
  store i32 1, ptr %87, align 4, !tbaa !7
  br label %90

89:                                               ; preds = %85
  store i32 0, ptr %87, align 4, !tbaa !7
  br label %90

90:                                               ; preds = %88, %89, %83, %84
  %91 = icmp eq i64 %66, 512
  br i1 %91, label %40, label %45, !llvm.loop !15

92:                                               ; preds = %112, %42
  %93 = phi i64 [ %113, %112 ], [ 0, %42 ]
  br i1 %44, label %115, label %94

94:                                               ; preds = %92, %94
  %95 = phi i64 [ %109, %94 ], [ 0, %92 ]
  %96 = getelementptr inbounds [512 x i32], ptr %1, i64 %93, i64 %95
  %97 = getelementptr inbounds i32, ptr %96, i64 4
  %98 = load <4 x i32>, ptr %96, align 4, !tbaa !7
  %99 = load <4 x i32>, ptr %97, align 4, !tbaa !7
  %100 = getelementptr inbounds [512 x i32], ptr %0, i64 %93, i64 %95
  %101 = getelementptr inbounds i32, ptr %100, i64 4
  store <4 x i32> %98, ptr %100, align 4, !tbaa !7
  store <4 x i32> %99, ptr %101, align 4, !tbaa !7
  %102 = or disjoint i64 %95, 8
  %103 = getelementptr inbounds [512 x i32], ptr %1, i64 %93, i64 %102
  %104 = getelementptr inbounds i32, ptr %103, i64 4
  %105 = load <4 x i32>, ptr %103, align 4, !tbaa !7
  %106 = load <4 x i32>, ptr %104, align 4, !tbaa !7
  %107 = getelementptr inbounds [512 x i32], ptr %0, i64 %93, i64 %102
  %108 = getelementptr inbounds i32, ptr %107, i64 4
  store <4 x i32> %105, ptr %107, align 4, !tbaa !7
  store <4 x i32> %106, ptr %108, align 4, !tbaa !7
  %109 = add nuw nsw i64 %95, 16
  %110 = icmp eq i64 %109, 512
  br i1 %110, label %112, label %94, !llvm.loop !17

111:                                              ; preds = %112
  ret void

112:                                              ; preds = %94, %115
  %113 = add nuw nsw i64 %93, 1
  %114 = icmp eq i64 %113, 256
  br i1 %114, label %111, label %92, !llvm.loop !20

115:                                              ; preds = %92, %115
  %116 = phi i64 [ %132, %115 ], [ 0, %92 ]
  %117 = getelementptr inbounds [512 x i32], ptr %1, i64 %93, i64 %116
  %118 = load i32, ptr %117, align 4, !tbaa !7
  %119 = getelementptr inbounds [512 x i32], ptr %0, i64 %93, i64 %116
  store i32 %118, ptr %119, align 4, !tbaa !7
  %120 = or disjoint i64 %116, 1
  %121 = getelementptr inbounds [512 x i32], ptr %1, i64 %93, i64 %120
  %122 = load i32, ptr %121, align 4, !tbaa !7
  %123 = getelementptr inbounds [512 x i32], ptr %0, i64 %93, i64 %120
  store i32 %122, ptr %123, align 4, !tbaa !7
  %124 = or disjoint i64 %116, 2
  %125 = getelementptr inbounds [512 x i32], ptr %1, i64 %93, i64 %124
  %126 = load i32, ptr %125, align 4, !tbaa !7
  %127 = getelementptr inbounds [512 x i32], ptr %0, i64 %93, i64 %124
  store i32 %126, ptr %127, align 4, !tbaa !7
  %128 = or disjoint i64 %116, 3
  %129 = getelementptr inbounds [512 x i32], ptr %1, i64 %93, i64 %128
  %130 = load i32, ptr %129, align 4, !tbaa !7
  %131 = getelementptr inbounds [512 x i32], ptr %0, i64 %93, i64 %128
  store i32 %130, ptr %131, align 4, !tbaa !7
  %132 = add nuw nsw i64 %116, 4
  %133 = icmp eq i64 %132, 512
  br i1 %133, label %112, label %115, !llvm.loop !21
}

; Function Attrs: noreturn nounwind sspstrong uwtable
define dso_local void @app() local_unnamed_addr #5 {
  %1 = alloca [256 x [512 x i32]], align 16
  %2 = alloca [256 x [512 x i32]], align 16
  call void @llvm.lifetime.start.p0(i64 524288, ptr nonnull %1) #6
  call void @llvm.lifetime.start.p0(i64 524288, ptr nonnull %2) #6
  br label %3

3:                                                ; preds = %5, %0
  %4 = phi i64 [ 0, %0 ], [ %6, %5 ]
  br label %8

5:                                                ; preds = %8
  %6 = add nuw nsw i64 %4, 1
  %7 = icmp eq i64 %6, 256
  br i1 %7, label %15, label %3, !llvm.loop !5

8:                                                ; preds = %8, %3
  %9 = phi i64 [ 0, %3 ], [ %13, %8 ]
  %10 = tail call i32 (...) @simRand() #6
  %11 = srem i32 %10, 2
  %12 = getelementptr inbounds [512 x i32], ptr %1, i64 %4, i64 %9
  store i32 %11, ptr %12, align 4, !tbaa !7
  %13 = add nuw nsw i64 %9, 1
  %14 = icmp eq i64 %13, 512
  br i1 %14, label %5, label %8, !llvm.loop !11

15:                                               ; preds = %5, %21
  %16 = phi i64 [ %22, %21 ], [ 0, %5 ]
  %17 = trunc i64 %16 to i32
  br label %23

18:                                               ; preds = %23
  %19 = add nuw nsw i64 %16, 1
  %20 = icmp eq i64 %19, 256
  br i1 %20, label %32, label %21

21:                                               ; preds = %18, %32
  %22 = phi i64 [ %19, %18 ], [ 0, %32 ]
  br label %15, !llvm.loop !12

23:                                               ; preds = %23, %15
  %24 = phi i64 [ 0, %15 ], [ %30, %23 ]
  %25 = getelementptr inbounds [512 x i32], ptr %1, i64 %16, i64 %24
  %26 = load i32, ptr %25, align 4, !tbaa !7
  %27 = icmp eq i32 %26, 0
  %28 = select i1 %27, i32 -16777216, i32 -16711936
  %29 = trunc i64 %24 to i32
  tail call void @simPutPixel(i32 noundef %29, i32 noundef %17, i32 noundef %28) #6
  %30 = add nuw nsw i64 %24, 1
  %31 = icmp eq i64 %30, 512
  br i1 %31, label %18, label %23, !llvm.loop !13

32:                                               ; preds = %18
  tail call void (...) @simFlush() #6
  call void @update(ptr noundef nonnull %1, ptr noundef nonnull %2)
  br label %21
}

attributes #0 = { nounwind sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(argmem: read) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nofree norecurse nosync nounwind sspstrong memory(argmem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { noreturn nounwind sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{!"clang version 18.1.8"}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.mustprogress"}
!7 = !{!8, !8, i64 0}
!8 = !{!"int", !9, i64 0}
!9 = !{!"omnipotent char", !10, i64 0}
!10 = !{!"Simple C/C++ TBAA"}
!11 = distinct !{!11, !6}
!12 = distinct !{!12, !6}
!13 = distinct !{!13, !6}
!14 = distinct !{!14, !6}
!15 = distinct !{!15, !6, !16}
!16 = !{!"llvm.loop.peeled.count", i32 1}
!17 = distinct !{!17, !6, !18, !19}
!18 = !{!"llvm.loop.isvectorized", i32 1}
!19 = !{!"llvm.loop.unroll.runtime.disable"}
!20 = distinct !{!20, !6}
!21 = distinct !{!21, !6, !18}
