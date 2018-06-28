#pragma once

#include <QTableWidget>

class ControlPointWidget : public QTableWidget
{
	Q_OBJECT

public:
	ControlPointWidget(QObject *parent);
	~ControlPointWidget();
};
