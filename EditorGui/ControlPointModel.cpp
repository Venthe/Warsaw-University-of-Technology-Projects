#include "stdafx.h"
#include "ControlPointModel.h"

ControlPointModel::ControlPointModel(QObject *parent)
	: QAbstractTableModel(parent)
{
}

ControlPointModel::~ControlPointModel()
{
}

int ControlPointModel::rowCount()
{
	return 0;
}

int ControlPointModel::columnCount()
{
	return 0;
}

QVariant ControlPointModel::headerData(int section, Qt::Orientation orientation, int role)
{
	return QVariant();
}

QVariant ControlPointModel::data(const QModelIndex & index, int role)
{
	return QVariant();
}

void ControlPointModel::setData()
{
}
