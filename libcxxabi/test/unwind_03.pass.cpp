//===------------------------- unwind_03.cpp ------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: libcxxabi-no-exceptions
// REQUIRES: c++98 || c++03 || c++11 || c++14

#include <exception>
#include <stdlib.h>
#include <assert.h>

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunreachable-code"
#endif

struct A
{
    static int count;
    int id_;
    A() : id_(++count) {}
    ~A() {assert(id_ == count--);}

private:
    A(const A&);
    A& operator=(const A&);
};

int A::count = 0;

struct B
{
    static int count;
    int id_;
    B() : id_(++count) {}
    ~B() {assert(id_ == count--);}

private:
    B(const B&);
    B& operator=(const B&);
};

int B::count = 0;

struct C
{
    static int count;
    int id_;
    C() : id_(++count) {}
    ~C() {assert(id_ == count--);}

private:
    C(const C&);
    C& operator=(const C&);
};

int C::count = 0;

void f2()
{
    C c;
    A a;
    throw 55;
    B b;
}

void f1() throw (long, char, double)
{
    A a;
    B b;
    f2();
    C c;
}

void u_handler()
{
    exit(0);
}

int main()
{
    std::set_unexpected(u_handler);
    try
    {
        f1();
        assert(false);
    }
    catch (int* i)
    {
        assert(false);
    }
    catch (long i)
    {
        assert(false);
    }
    catch (int i)
    {
        assert(i == 55);
    }
    catch (...)
    {
        assert(false);
    }
    assert(false);
}
