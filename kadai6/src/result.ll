@.str1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str2 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@n = common global i32 0, align 4
@temp = common global i32 0, align 4

define void @fact(i32) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  %4 = icmp sle i32 %3, 1
  br i1 %4, label %5, label %6

5:
  store i32 1, i32* @temp, align 4
  br label %12

6:
  %7 = load i32, i32* %2, align 4
  %8 = sub nsw i32 %7, 1
  call void @fact(i32 %8)
  %9 = load i32, i32* @temp, align 4
  %10 = load i32, i32* %2, align 4
  %11 = mul nsw i32 %9, %10
  store i32 %11, i32* @temp, align 4
  br label %12

12:
  ret void
}

define i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str1, i32 0, i32 0), i32* @n)
  %3 = load i32, i32* @n, align 4
  call void @fact(i32 %3)
  %4 = load i32, i32* @temp, align 4
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str2, i32 0, i32 0), i32 %4)
  ret i32 0
}
declare dso_local i32 @scanf(i8*, ...)
declare dso_local i32 @printf(i8*, ...)
