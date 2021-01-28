
/*
 * @author WardenAllen
 * @date   2020/10/22 20:36:24
 * @brief  
 */

#include "WATool.h"

#include <QtWidgets>

WATool::WATool(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	QVBoxLayout* v_layout = new QVBoxLayout;

	QString address = "192.168.1.66";
	QString port = "9999";
	_connect_widget.Init(address, port, 1);
	v_layout->addWidget(&_connect_widget);

	centralWidget()->setLayout(v_layout);
}
