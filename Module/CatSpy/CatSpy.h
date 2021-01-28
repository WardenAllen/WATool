#pragma once

#include "catspy_global.h"

/*
 * 必须使用extern "C"链接标记，否则C++编译器会产生一个修饰过的函数名，
 * 这样导出函数的名字将不再是helloworld，而是一个形 如
 * " ?helloWorld@TestDll@@UAEXXZ”的名字。为什么名字不是
 * helloworld呢？这是因为C++为了支持函数的重载，会在编译时将函数的
 * 参数类型信息以及返回值类型信息加入到函数名中，这样代码中名字一样的
 * 重载函数，在经过编译后就互相区分开了，调用时函数名也经过同样的处理，
 * 就能找到对应的函数了。
 */
extern "C" CATSPY_EXPORT void DLLTest(const char* Msg);
