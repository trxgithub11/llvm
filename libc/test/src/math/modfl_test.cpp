//===-- Unittests for modfl -----------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ModfTest.h"

#include "src/math/modfl.h"

LIST_MODF_TESTS(long double, LIBC_NAMESPACE::modfl)
