// RUN: %clang_cc1 -verify -fopenmp -DOMP51 %s -Wuninitialized

// RUN: %clang_cc1 -verify -fopenmp-simd -DOMP51 %s -Wuninitialized

// RUN: %clang_cc1 -verify -fopenmp-version=50 -fopenmp %s -Wuninitialized

// RUN: %clang_cc1 -verify -fopenmp-version=50 -fopenmp-simd %s -Wuninitialized

void foo();

namespace {
static int y = 0;
}
static int x = 0;

int main(int argc, char **argv) {
  #pragma omp target
  #pragma omp teams distribute parallel for default // expected-error {{expected '(' after 'default'}}
  for (int i=0; i<200; i++) foo();
  #pragma omp target
#pragma omp teams distribute parallel for default( // expected-error {{expected 'none', 'shared', 'private' or 'firstprivate' in OpenMP clause 'default'}} expected-error {{expected ')'}} expected-note {{to match this '('}}
  for (int i=0; i<200; i++) foo();
  #pragma omp target
#pragma omp teams distribute parallel for default() // expected-error {{expected 'none', 'shared', 'private' or 'firstprivate' in OpenMP clause 'default'}}
  for (int i=0; i<200; i++) foo();
  #pragma omp target
  #pragma omp teams distribute parallel for default (none // expected-error {{expected ')'}} expected-note {{to match this '('}}
  for (int i=0; i<200; i++) foo();
  #pragma omp target
  #pragma omp teams distribute parallel for default (shared), default(shared) // expected-error {{directive '#pragma omp teams distribute parallel for' cannot contain more than one 'default' clause}}
  for (int i=0; i<200; i++) foo();
  #pragma omp target
#pragma omp teams distribute parallel for default(x) // expected-error {{expected 'none', 'shared', 'private' or 'firstprivate' in OpenMP clause 'default'}}
  for (int i=0; i<200; i++) foo();

  #pragma omp target
  #pragma omp teams distribute parallel for default(none) // expected-note {{explicit data sharing attribute requested here}}
  for (int i=0; i<200; i++) ++argc; // expected-error {{variable 'argc' must have explicitly specified data sharing attributes}}

#ifdef OMP51
#pragma omp target
#pragma omp teams distribute parallel for default(firstprivate) // expected-note 2 {{explicit data sharing attribute requested here}}
  for (int i = 0; i < 200; i++) {
    ++x; // expected-error {{variable 'x' must have explicitly specified data sharing attributes}}
    ++y; // expected-error {{variable 'y' must have explicitly specified data sharing attributes}}
  }
#pragma omp target
#pragma omp teams distribute parallel for default(private) // expected-note 2 {{explicit data sharing attribute requested here}}
  for (int i = 0; i < 200; i++) {
    ++x; // expected-error {{variable 'x' must have explicitly specified data sharing attributes}}
    ++y; // expected-error {{variable 'y' must have explicitly specified data sharing attributes}}
  }
#endif

  return 0;
}
