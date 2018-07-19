#pragma once

#include <QtWidgets/QMainWindow> // NOLINT
#include "ui_EditorGui.h"

class EditorGui : public QMainWindow
{
	Q_OBJECT

public:
	EditorGui(QWidget *parent = Q_NULLPTR);

	QWidget drawing_area;
signals:
	void updatePoints();
public slots:
	void mousePositionChanged(QPoint mousePosition);
	void controlPointsChanged();

	void exportPoints();
	void importPoints();
private:
	Ui::EditorGuiClass ui;
	// TODO: Extend control point to include control point type - ignoring weight?
	std::vector<esl::ControlPoint> controlPointsList;
	double controlPointWeight = 0.0;

	void updatePointListTable();

	void connectDrawingArea();
	void connectPointList();
};
