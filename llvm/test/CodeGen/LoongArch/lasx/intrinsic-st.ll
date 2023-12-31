; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc --mtriple=loongarch64 --mattr=+lasx < %s | FileCheck %s

declare void @llvm.loongarch.lasx.xvst(<32 x i8>, i8*, i32)

define void @lasx_xvst(<32 x i8> %va, i8* %p) nounwind {
; CHECK-LABEL: lasx_xvst:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    xvst $xr0, $a0, 1
; CHECK-NEXT:    ret
entry:
  call void @llvm.loongarch.lasx.xvst(<32 x i8> %va, i8* %p, i32 1)
  ret void
}

declare void @llvm.loongarch.lasx.xvstx(<32 x i8>, i8*, i64)

define void @lasx_xvstx(<32 x i8> %va, i8* %p) nounwind {
; CHECK-LABEL: lasx_xvstx:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    ori $a1, $zero, 1
; CHECK-NEXT:    xvstx $xr0, $a0, $a1
; CHECK-NEXT:    ret
entry:
  call void @llvm.loongarch.lasx.xvstx(<32 x i8> %va, i8* %p, i64 1)
  ret void
}
