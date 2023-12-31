// RUN: llvm-mc -triple=amdgcn -mcpu=tonga -show-encoding %s | FileCheck %s --check-prefix=VI9
// RUN: llvm-mc -triple=amdgcn -mcpu=gfx900 -show-encoding %s | FileCheck %s --check-prefix=VI9

zero = 0
two = 2
one = 1

v_mov_b32 v0, v0 quad_perm:[0+zero,zero-2+two*two,1/one,1]
// VI9: v_mov_b32_dpp v0, v0 quad_perm:[0,2,1,1] row_mask:0xf bank_mask:0xf ; encoding: [0xfa,0x02,0x00,0x7e,0x00,0x58,0x00,0xff]

v_mov_b32 v0, v0 row_shl:two-1
// VI9: v_mov_b32_dpp v0, v0 row_shl:1 row_mask:0xf bank_mask:0xf ; encoding: [0xfa,0x02,0x00,0x7e,0x00,0x01,0x01,0xff]

v_mov_b32 v0, v0 row_shr:0xe+one
// VI9: v_mov_b32_dpp v0, v0 row_shr:15 row_mask:0xf bank_mask:0xf ; encoding: [0xfa,0x02,0x00,0x7e,0x00,0x1f,0x01,0xff]

v_mov_b32 v0, v0 row_ror:0x6*two
// VI9: v_mov_b32_dpp v0, v0 row_ror:12 row_mask:0xf bank_mask:0xf ; encoding: [0xfa,0x02,0x00,0x7e,0x00,0x2c,0x01,0xff]

v_mov_b32 v0, v0 wave_shl:two/2
// VI9: v_mov_b32_dpp v0, v0 wave_shl:1 row_mask:0xf bank_mask:0xf ; encoding: [0xfa,0x02,0x00,0x7e,0x00,0x30,0x01,0xff]

v_mov_b32 v0, v0 wave_rol:two-one
// VI9: v_mov_b32_dpp v0, v0 wave_rol:1 row_mask:0xf bank_mask:0xf ; encoding: [0xfa,0x02,0x00,0x7e,0x00,0x34,0x01,0xff]

v_mov_b32 v0, v0 wave_shr:1+zero
// VI9: v_mov_b32_dpp v0, v0 wave_shr:1 row_mask:0xf bank_mask:0xf ; encoding: [0xfa,0x02,0x00,0x7e,0x00,0x38,0x01,0xff]

v_mov_b32 v0, v0 wave_ror:two*2-3
// VI9: v_mov_b32_dpp v0, v0 wave_ror:1 row_mask:0xf bank_mask:0xf ; encoding: [0xfa,0x02,0x00,0x7e,0x00,0x3c,0x01,0xff]

v_mov_b32 v0, v0 row_bcast:150/(two*2+zero/one+two*3)
// VI9: v_mov_b32_dpp v0, v0 row_bcast:15 row_mask:0xf bank_mask:0xf ; encoding: [0xfa,0x02,0x00,0x7e,0x00,0x42,0x01,0xff]

v_mov_b32 v0, v0 quad_perm:[one,two+one,zero,2-one] row_mask:2*5 bank_mask:0x2-one bound_ctrl:1-1
// VI9: v_mov_b32_dpp v0, v0 quad_perm:[1,3,0,1] row_mask:0xa bank_mask:0x1 bound_ctrl:1 ; encoding: [0xfa,0x02,0x00,0x7e,0x00,0x4d,0x08,0xa1]
