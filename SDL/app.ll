; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: nounwind optsize sspstrong uwtable
define dso_local void @init_game(ptr nocapture noundef writeonly %0) local_unnamed_addr #0 {
  br label %2

2:                                                ; preds = %1, %5
  %3 = phi i64 [ 0, %1 ], [ %6, %5 ]
  br label %8

4:                                                ; preds = %5
  ret void

5:                                                ; preds = %8
  %6 = add nuw nsw i64 %3, 1
  %7 = icmp eq i64 %6, 256
  br i1 %7, label %4, label %2, !llvm.loop !5

8:                                                ; preds = %2, %8
  %9 = phi i64 [ 0, %2 ], [ %13, %8 ]
  %10 = tail call i32 (...) @simRand() #6
  %11 = srem i32 %10, 2
  %12 = getelementptr inbounds [512 x i32], ptr %0, i64 %3, i64 %9
  store i32 %11, ptr %12, align 4, !tbaa !7
  %13 = add nuw nsw i64 %9, 1
  %14 = icmp eq i64 %13, 512
  br i1 %14, label %5, label %8, !llvm.loop !11
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: optsize
declare i32 @simRand(...) local_unnamed_addr #2

; Function Attrs: nounwind optsize sspstrong uwtable
define dso_local void @draw(ptr nocapture noundef readonly %0) local_unnamed_addr #0 {
  br label %2

2:                                                ; preds = %1, %6
  %3 = phi i64 [ 0, %1 ], [ %7, %6 ]
  %4 = trunc i64 %3 to i32
  br label %9

5:                                                ; preds = %6
  tail call void (...) @simFlush() #6
  ret void

6:                                                ; preds = %9
  %7 = add nuw nsw i64 %3, 1
  %8 = icmp eq i64 %7, 256
  br i1 %8, label %5, label %2, !llvm.loop !12

9:                                                ; preds = %2, %9
  %10 = phi i64 [ 0, %2 ], [ %16, %9 ]
  %11 = getelementptr inbounds [512 x i32], ptr %0, i64 %3, i64 %10
  %12 = load i32, ptr %11, align 4, !tbaa !7
  %13 = icmp eq i32 %12, 0
  %14 = select i1 %13, i32 -16777216, i32 -16711936
  %15 = trunc i64 %10 to i32
  tail call void @simPutPixel(i32 noundef %15, i32 noundef %4, i32 noundef %14) #6
  %16 = add nuw nsw i64 %10, 1
  %17 = icmp eq i64 %16, 512
  br i1 %17, label %6, label %9, !llvm.loop !13
}

; Function Attrs: optsize
declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #2

; Function Attrs: optsize
declare void @simFlush(...) local_unnamed_addr #2

; Function Attrs: nofree norecurse nosync nounwind optsize sspstrong memory(argmem: read) uwtable
define dso_local i32 @count_neighbors(i32 noundef %0, i32 noundef %1, ptr nocapture noundef readonly %2) local_unnamed_addr #3 {
  br label %4

4:                                                ; preds = %3, %12
  %5 = phi i32 [ 0, %3 ], [ %31, %12 ]
  %6 = phi i32 [ -1, %3 ], [ %13, %12 ]
  %7 = add nsw i32 %6, %1
  %8 = icmp sgt i32 %7, -1
  %9 = icmp slt i32 %7, 256
  %10 = zext nneg i32 %7 to i64
  br label %15

11:                                               ; preds = %12
  ret i32 %31

12:                                               ; preds = %30
  %13 = add nsw i32 %6, 1
  %14 = icmp eq i32 %13, 2
  br i1 %14, label %11, label %4, !llvm.loop !14

15:                                               ; preds = %4, %30
  %16 = phi i32 [ %5, %4 ], [ %31, %30 ]
  %17 = phi i32 [ -1, %4 ], [ %32, %30 ]
  %18 = or i32 %17, %6
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %30, label %20

20:                                               ; preds = %15
  %21 = add nsw i32 %17, %0
  %22 = icmp ult i32 %21, 512
  %23 = select i1 %22, i1 %8, i1 false
  %24 = select i1 %23, i1 %9, i1 false
  br i1 %24, label %25, label %30

25:                                               ; preds = %20
  %26 = zext nneg i32 %21 to i64
  %27 = getelementptr inbounds [512 x i32], ptr %2, i64 %10, i64 %26
  %28 = load i32, ptr %27, align 4, !tbaa !7
  %29 = add nsw i32 %28, %16
  br label %30

30:                                               ; preds = %20, %25, %15
  %31 = phi i32 [ %16, %15 ], [ %29, %25 ], [ %16, %20 ]
  %32 = add nsw i32 %17, 1
  %33 = icmp eq i32 %32, 2
  br i1 %33, label %12, label %15, !llvm.loop !15
}

; Function Attrs: nofree norecurse nosync nounwind optsize sspstrong memory(argmem: readwrite) uwtable
define dso_local void @update(ptr nocapture noundef %0, ptr nocapture noundef %1) local_unnamed_addr #4 {
  br label %3

3:                                                ; preds = %2, %6
  %4 = phi i64 [ 0, %2 ], [ %7, %6 ]
  %5 = trunc i64 %4 to i32
  br label %9

6:                                                ; preds = %23
  %7 = add nuw nsw i64 %4, 1
  %8 = icmp eq i64 %7, 256
  br i1 %8, label %29, label %3, !llvm.loop !16

9:                                                ; preds = %3, %23
  %10 = phi i64 [ 0, %3 ], [ %27, %23 ]
  %11 = trunc i64 %10 to i32
  %12 = tail call i32 @count_neighbors(i32 noundef %11, i32 noundef %5, ptr noundef %0) #7
  %13 = getelementptr inbounds [512 x i32], ptr %0, i64 %4, i64 %10
  %14 = load i32, ptr %13, align 4, !tbaa !7
  %15 = icmp ne i32 %14, 0
  %16 = and i32 %12, -2
  %17 = icmp eq i32 %16, 2
  %18 = select i1 %15, i1 %17, i1 false
  br i1 %18, label %23, label %19

19:                                               ; preds = %9
  %20 = icmp eq i32 %14, 0
  %21 = icmp eq i32 %12, 3
  %22 = select i1 %20, i1 %21, i1 false
  br label %23

23:                                               ; preds = %9, %19
  %24 = phi i1 [ %22, %19 ], [ true, %9 ]
  %25 = zext i1 %24 to i32
  %26 = getelementptr inbounds [512 x i32], ptr %1, i64 %4, i64 %10
  store i32 %25, ptr %26, align 4, !tbaa !7
  %27 = add nuw nsw i64 %10, 1
  %28 = icmp eq i64 %27, 512
  br i1 %28, label %6, label %9, !llvm.loop !17

29:                                               ; preds = %6, %32
  %30 = phi i64 [ %33, %32 ], [ 0, %6 ]
  br label %35

31:                                               ; preds = %32
  ret void

32:                                               ; preds = %35
  %33 = add nuw nsw i64 %30, 1
  %34 = icmp eq i64 %33, 256
  br i1 %34, label %31, label %29, !llvm.loop !18

35:                                               ; preds = %29, %35
  %36 = phi i64 [ 0, %29 ], [ %40, %35 ]
  %37 = getelementptr inbounds [512 x i32], ptr %1, i64 %30, i64 %36
  %38 = load i32, ptr %37, align 4, !tbaa !7
  %39 = getelementptr inbounds [512 x i32], ptr %0, i64 %30, i64 %36
  store i32 %38, ptr %39, align 4, !tbaa !7
  %40 = add nuw nsw i64 %36, 1
  %41 = icmp eq i64 %40, 512
  br i1 %41, label %32, label %35, !llvm.loop !19
}

; Function Attrs: noreturn nounwind optsize sspstrong uwtable
define dso_local void @app() local_unnamed_addr #5 {
  %1 = alloca [256 x [512 x i32]], align 16
  %2 = alloca [256 x [512 x i32]], align 16
  call void @llvm.lifetime.start.p0(i64 524288, ptr nonnull %1) #8
  call void @llvm.lifetime.start.p0(i64 524288, ptr nonnull %2) #8
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

15:                                               ; preds = %5, %15
  call void @draw(ptr noundef nonnull %1) #7
  call void @update(ptr noundef nonnull %1, ptr noundef nonnull %2) #7
  br label %15
}

attributes #0 = { nounwind optsize sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { optsize "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nofree norecurse nosync nounwind optsize sspstrong memory(argmem: read) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nofree norecurse nosync nounwind optsize sspstrong memory(argmem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { noreturn nounwind optsize sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { nounwind optsize }
attributes #7 = { optsize }
attributes #8 = { nounwind }

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
!15 = distinct !{!15, !6}
!16 = distinct !{!16, !6}
!17 = distinct !{!17, !6}
!18 = distinct !{!18, !6}
!19 = distinct !{!19, !6}
