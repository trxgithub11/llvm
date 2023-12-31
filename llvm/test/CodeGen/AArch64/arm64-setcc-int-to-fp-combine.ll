; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=arm64-apple-ios | FileCheck %s

define <4 x float> @foo(<4 x float> %val, <4 x float> %test) nounwind {
; CHECK-LABEL: foo:
; CHECK:       ; %bb.0:
; CHECK-NEXT:    fmov.4s v2, #1.00000000
; CHECK-NEXT:    fcmeq.4s v0, v0, v1
; CHECK-NEXT:    and.16b v0, v0, v2
; CHECK-NEXT:    ret
  %cmp = fcmp oeq <4 x float> %val, %test
  %ext = zext <4 x i1> %cmp to <4 x i32>
  %result = sitofp <4 x i32> %ext to <4 x float>
  ret <4 x float> %result
}
; Make sure the operation doesn't try to get folded when the sizes don't match,
; as that ends up crashing later when trying to form a bitcast operation for
; the folded nodes.
define void @foo1(<4 x float> %val, <4 x float> %test, ptr %p) nounwind {
; CHECK-LABEL: foo1:
; CHECK:       ; %bb.0:
; CHECK-NEXT:    movi.4s v2, #1
; CHECK-NEXT:    fcmeq.4s v0, v0, v1
; CHECK-NEXT:    and.16b v0, v0, v2
; CHECK-NEXT:    ushll2.2d v1, v0, #0
; CHECK-NEXT:    ushll.2d v0, v0, #0
; CHECK-NEXT:    scvtf.2d v1, v1
; CHECK-NEXT:    scvtf.2d v0, v0
; CHECK-NEXT:    stp q0, q1, [x0]
; CHECK-NEXT:    ret
  %cmp = fcmp oeq <4 x float> %val, %test
  %ext = zext <4 x i1> %cmp to <4 x i32>
  %result = sitofp <4 x i32> %ext to <4 x double>
  store <4 x double> %result, ptr %p
  ret void
}

; Fold explicit AND operations when the constant isn't a splat of a single
; scalar value like what the zext creates.
define <4 x float> @foo2(<4 x float> %val, <4 x float> %test) nounwind {
; CHECK-LABEL: foo2:
; CHECK:       ; %bb.0:
; CHECK-NEXT:    fcmeq.4s v0, v0, v1
; CHECK-NEXT:  Lloh0:
; CHECK-NEXT:    adrp x8, lCPI2_0@PAGE
; CHECK-NEXT:  Lloh1:
; CHECK-NEXT:    ldr q1, [x8, lCPI2_0@PAGEOFF]
; CHECK-NEXT:    and.16b v0, v0, v1
; CHECK-NEXT:    ret
; CHECK-NEXT:    .loh AdrpLdr Lloh0, Lloh1
  %cmp = fcmp oeq <4 x float> %val, %test
  %ext = zext <4 x i1> %cmp to <4 x i32>
  %and = and <4 x i32> %ext, <i32 255, i32 256, i32 257, i32 258>
  %result = sitofp <4 x i32> %and to <4 x float>
  ret <4 x float> %result
}
