#pragma once

#include <QWidget>
#include "ui_AddPoint.h"

class AddPoint : public QGridLayout
{
	Q_OBJECT

public:
	AddPoint(QWidget *parent = Q_NULLPTR);
	~AddPoint();

private:
	Ui::AddPoint ui;
};
