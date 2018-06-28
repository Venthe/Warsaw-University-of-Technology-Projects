#pragma once

#include <QAbstractTableModel>

class ControlPointModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	ControlPointModel(QObject *parent);
	~ControlPointModel();

	int rowCount();
	int columnCount();
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole);
	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole);
	void setData();
};
