
/*
 * @author WardenAllen
 * @date   2020/10/22 20:36:12
 * @brief  
 */

#include "WATool.h"

#include <iostream>

#include <QtWidgets>
#include <QtWidgets/QApplication>
#include <QLibrary> 

#include "Header.h"
#include "Net/Tcp.h"

using namespace std;

typedef void (*Fun)(const char*); //���庯��ָ��,int add(int a,int b);    

int main(int argc, char *argv[])
{

	/*WATcp tcp(QString::fromStdString("192.168.1.24"), 58601);
	tcp.Connect();*/

	/*PlutoConnectReq req;
	req.set_serverid(123);
	string s = req.SerializeAsString();
	qDebug() << QString::fromStdString(s);*/

	QLibrary mylib("CatSpy.dll");   //�������õ���dll�ļ�  
	int result;
	//�ж��Ƿ���ȷ����  
	if (!mylib.load())
	{
		std::cout << "DLL load failed!" << std::endl;
	}
	else
	{
		std::cout << "DLL load success!" << std::endl;
		//�����ⲿ���� add()  
		Fun test = (Fun)mylib.resolve("DLLTest");
		//�Ƿ�ɹ������� add() ����  
		if (test)
		{
			std::cout << "Link to DLLTest Function success!" << std::endl;
			test("Hello dll!");
		}
		else
			std::cout << "Link to DLLTest Function failed!!" << std::endl;
	}

    QApplication a(argc, argv);
	QFont f("Microsoft JhengHei", 10);
	a.setFont(f);
    WATool w;
    w.show();
    return a.exec();
}
