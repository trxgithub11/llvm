// RUN: %clang_cc1 -fxray-instrument -fxray-instrumentation-bundle=none -x c++ \
// RUN:     -std=c++11 -triple x86_64-unknown-unknown -emit-llvm -o - %s \
// RUN:     | FileCheck --check-prefixes CHECK,NOFUNCTION,NOCUSTOM,NOTYPED %s
// RUN: %clang_cc1 -fxray-instrument -fxray-instrumentation-bundle=function -x c++ \
// RUN:     -std=c++11 -triple x86_64-unknown-unknown -emit-llvm -o - %s \
// RUN:     | FileCheck --check-prefixes CHECK,FUNCTION,NOCUSTOM,NOTYPED %s
// RUN: %clang_cc1 -fxray-instrument \
// RUN:     -fxray-instrumentation-bundle=custom -x c++ \
// RUN:     -std=c++11 -triple x86_64-unknown-unknown -emit-llvm -o - %s \
// RUN:     | FileCheck --check-prefixes CHECK,NOFUNCTION,CUSTOM,NOTYPED %s
// RUN: %clang_cc1 -fxray-instrument \
// RUN:     -fxray-instrumentation-bundle=typed -x c++ \
// RUN:     -std=c++11 -triple x86_64-unknown-unknown -emit-llvm -o - %s \
// RUN:     | FileCheck --check-prefixes CHECK,NOFUNCTION,NOCUSTOM,TYPED %s
// RUN: %clang_cc1 -fxray-instrument \
// RUN:     -fxray-instrumentation-bundle=custom,typed -x c++ \
// RUN:     -std=c++11 -triple x86_64-unknown-unknown -emit-llvm -o - %s \
// RUN:     | FileCheck --check-prefixes CHECK,NOFUNCTION,CUSTOM,TYPED %s
// RUN: %clang_cc1 -fxray-instrument \
// RUN:     -fxray-instrumentation-bundle=function,custom -x c++ \
// RUN:     -std=c++11 -triple x86_64-unknown-unknown -emit-llvm -o - %s \
// RUN:     | FileCheck --check-prefixes CHECK,FUNCTION,CUSTOM,NOTYPED %s
// RUN: %clang_cc1 -fxray-instrument \
// RUN:     -fxray-instrumentation-bundle=function,typed -x c++ \
// RUN:     -std=c++11 -triple x86_64-unknown-unknown -emit-llvm -o - %s \
// RUN:     | FileCheck --check-prefixes CHECK,FUNCTION,NOCUSTOM,TYPED %s
// RUN: %clang_cc1 -fxray-instrument \
// RUN:     -fxray-instrumentation-bundle=function,custom,typed -x c++ \
// RUN:     -std=c++11 -triple x86_64-unknown-unknown -emit-llvm -o - %s \
// RUN:     | FileCheck --check-prefixes CHECK,FUNCTION,CUSTOM,TYPED %s
// RUN: %clang_cc1 -fxray-instrument \
// RUN:     -fxray-instrumentation-bundle=function \
// RUN:     -fxray-instrumentation-bundle=custom \
// RUN:     -fxray-instrumentation-bundle=typed -x c++ \
// RUN:     -std=c++11 -triple x86_64-unknown-unknown -emit-llvm -o - %s \
// RUN:     | FileCheck --check-prefixes CHECK,FUNCTION,CUSTOM,TYPED %s
// RUN: %clang_cc1 -fxray-instrument \
// RUN:     -fxray-instrumentation-bundle=function-entry -x c++ \
// RUN:     -std=c++11 -triple x86_64-unknown-unknown -emit-llvm -o - %s \
// RUN:     | FileCheck --check-prefixes CHECK,NOCUSTOM,NOTYPED,SKIPEXIT %s
// RUN: %clang_cc1 -fxray-instrument \
// RUN:     -fxray-instrumentation-bundle=function-exit -x c++ \
// RUN:     -std=c++11 -triple x86_64-unknown-unknown -emit-llvm -o - %s \
// RUN:     | FileCheck --check-prefixes CHECK,NOCUSTOM,NOTYPED,SKIPENTRY %s
// RUN: %clang_cc1 -fxray-instrument \
// RUN:     -fxray-instrumentation-bundle=function-entry,function-exit -x c++ \
// RUN:     -std=c++11 -triple x86_64-unknown-unknown -emit-llvm -o - %s \
// RUN:     | FileCheck --check-prefixes CHECK,FUNCTION,NOCUSTOM,NOTYPED %s

// CHECK: define{{.*}} void @_Z16alwaysInstrumentv() #[[ALWAYSATTR:[0-9]+]] {
[[clang::xray_always_instrument]] void alwaysInstrument() {
  static constexpr char kPhase[] = "always";
  __xray_customevent(kPhase, 6);
  __xray_typedevent(1, kPhase, 6);
  // CUSTOM: call void @llvm.xray.customevent(ptr {{.*}}, i64 6)
  // NOCUSTOM-NOT: call void @llvm.xray.customevent(
  // TYPED: call void @llvm.xray.typedevent(i64 {{.*}}, ptr{{.*}}, i64 6)
  // NOTYPED-NOT: call void @llvm.xray.typedevent(
}

// FUNCTION: attributes #[[ALWAYSATTR]] = {{.*}} "function-instrument"="xray-always" {{.*}}
// NOFUNCTION-NOT: attributes #[[ALWAYSATTR]] = {{.*}} "function-instrument"="xray-always" {{.*}}

// SKIPENTRY: attributes #[[ALWAYSATTR]] = {{.*}} "function-instrument"="xray-always" {{.*}} "xray-skip-entry" {{.*}}
// SKIPEXIT: attributes #[[ALWAYSATTR]] = {{.*}} "function-instrument"="xray-always" {{.*}} "xray-skip-exit" {{.*}}
