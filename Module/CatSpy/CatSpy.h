#pragma once

#include "catspy_global.h"

/*
 * ����ʹ��extern "C"���ӱ�ǣ�����C++�����������һ�����ι��ĺ�������
 * �����������������ֽ�������helloworld������һ���� ��
 * " ?helloWorld@TestDll@@UAEXXZ�������֡�Ϊʲô���ֲ���
 * helloworld�أ�������ΪC++Ϊ��֧�ֺ��������أ����ڱ���ʱ��������
 * ����������Ϣ�Լ�����ֵ������Ϣ���뵽�������У���������������һ����
 * ���غ������ھ��������ͻ������ֿ��ˣ�����ʱ������Ҳ����ͬ���Ĵ�����
 * �����ҵ���Ӧ�ĺ����ˡ�
 */
extern "C" CATSPY_EXPORT void DLLTest(const char* Msg);