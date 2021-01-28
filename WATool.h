
/*
 * @author WardenAllen
 * @date   2020/10/22 20:36:35
 * @brief  
 */

#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_WATool.h"
#include "Widget/ConnectWidget.h"

class WATool : public QMainWindow
{
    Q_OBJECT

public:
    WATool(QWidget *parent = Q_NULLPTR);

private:
    Ui::WAToolClass ui;
    ConnectWidget _connect_widget;
};
