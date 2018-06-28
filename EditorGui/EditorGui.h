#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EditorGui.h"

class EditorGui : public QMainWindow
{
	Q_OBJECT

public:
	EditorGui(QWidget *parent = Q_NULLPTR);

	QWidget renderArea;
signals:
	void controlPointListUpdated(std::vector<ControlPoint> controlPointList);
public slots:
	void mousePositionUpdated(QString text);
	void controlPointChanged(std::vector<ControlPoint> points);
	void updateTable();
	void exportToFile();
	void importFromFile();
	void addPointClicked();
private:
	Ui::EditorGuiClass ui;
	std::vector<ControlPoint> controlPointList;
};
