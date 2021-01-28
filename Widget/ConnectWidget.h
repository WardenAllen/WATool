
/*
 * @author WardenAllen
 * @date   2020/10/22 20:36:49
 * @brief  
 */

#pragma once

#include "Header.h"
#include "Label/HintLabel.h"
#include "Net/Tcp.h"

class ConnectWidget : public QWidget
{
	Q_OBJECT
public:
	ConnectWidget();

public:
	void Init(QString& address_, QString& port_, int type_);
	void SetConnected();
	void SetClosed();

private:
	HintLabel _hint_label;
	QLabel _address_label;
	QLabel _port_label;
	QLineEdit _address_edit;
	QLineEdit _port_edit;
	QPushButton _connect_button;
	QPushButton _close_button;

public:
	inline WATcp& GetTcp() { return _tcp; }

private slots:
	void OnConnectBtnClicked();
	void OnCloseBtnClicked();

private slots:
	void OnTcpConnected();
	void OnTcpClosed();

private:
	QString _address;
	QString _port;
	int _type;
	WATcp _tcp;

};
