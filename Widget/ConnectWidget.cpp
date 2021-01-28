
/*
 * @author WardenAllen
 * @date   2020/10/22 20:36:58
 * @brief  
 */

#include "ConnectWidget.h"

ConnectWidget::ConnectWidget()
{
	QHBoxLayout* pLayout = new QHBoxLayout;

	_hint_label.setFixedSize(23, 23);
	_hint_label.SetState(HS_0);

	_address_label.setText("Address: ");
	_port_label.setText("Port: ");

	_connect_button.setText("Connect");
	_close_button.setText("Close");

	pLayout->addWidget(&_address_label);
	pLayout->addWidget(&_address_edit);
	pLayout->addWidget(&_port_label);
	pLayout->addWidget(&_port_edit);
	pLayout->addWidget(&_connect_button);
	pLayout->addWidget(&_close_button);
	pLayout->addWidget(&_hint_label);

	this->setLayout(pLayout);

	// °ó¶¨ÐÅºÅ
	connect(&_connect_button, &QPushButton::clicked, this, &ConnectWidget::OnConnectBtnClicked);
	connect(&_close_button, &QPushButton::clicked, this, &ConnectWidget::OnCloseBtnClicked);

	connect(&_tcp, &WATcp::TcpConnected, this, &ConnectWidget::OnTcpConnected);
	connect(&_tcp, &WATcp::TcpClosed, this, &ConnectWidget::OnTcpClosed);
}

void ConnectWidget::Init(QString& address_, QString& port_, int type_)
{
	this->_address = address_;
	this->_port = port_;
	this->_type = type_;
	_address_edit.setText(address_);
	_port_edit.setText(port_);
}

void ConnectWidget::SetConnected()
{
	_hint_label.SetState(HS_1);
}

void ConnectWidget::SetClosed()
{
	_hint_label.SetState(HS_0);
}

void ConnectWidget::OnConnectBtnClicked()
{
	//_tcp.Connect(_address_edit.text(), static_cast<quint16>(_port_edit.text().toInt()));

	std::vector<WATcp *> vec;

	for (int i = 0; i < 2; i++)
		vec.push_back(new WATcp);

	for (int i = 0; i < (int)vec.size(); i++)
	{
		vec[i]->Connect(_address_edit.text(), static_cast<quint16>(_port_edit.text().toInt()));
	}
}

void ConnectWidget::OnCloseBtnClicked()
{
	_tcp.Close();
}

void ConnectWidget::OnTcpConnected()
{
	SetConnected();
}

void ConnectWidget::OnTcpClosed()
{
	SetClosed();
}