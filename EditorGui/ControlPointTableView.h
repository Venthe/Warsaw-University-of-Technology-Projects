#pragma once

#include <QTableView>

class ControlPointTableView : public QTableView
{
	Q_OBJECT

public:
	ControlPointTableView(QObject *parent);
	~ControlPointTableView();
};
