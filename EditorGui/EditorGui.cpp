#include "stdafx.h"
#include "EditorGui.h"

#include "DrawingArea.h"
#include "ControlPointList.h"
#include "Io.h"

EditorGui::EditorGui(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.exportPointsButton, SIGNAL(clicked()), this, SLOT(exportToFile()));
	connect(ui.importPointsButton, SIGNAL(clicked()), this, SLOT(importFromFile()));
	connect(ui.drawingArea, SIGNAL(mousePositionChanged(QString)), this, SLOT(mousePositionUpdated(QString)));
	connect(ui.drawingArea, SIGNAL(controlPointListChanged(std::vector<ControlPoint>)), this, SLOT(controlPointChanged(std::vector<ControlPoint>)));
	connect(this, SIGNAL(controlPointListUpdated(std::vector<ControlPoint>)), ui.drawingArea, SLOT(controlPointListUpdated(std::vector<ControlPoint>)));

	emit controlPointListUpdated(controlPointList);
}


void EditorGui::mousePositionUpdated(QString text) {
	statusBar()->showMessage(text);
}

void EditorGui::controlPointChanged(std::vector<ControlPoint> points) {
	qDebug() << "Control point changed";
	controlPointList = points;
	emit controlPointListUpdated(controlPointList);

	updateTable();
}

void EditorGui::updateTable()
{
	ui.pointsList->setColumnCount(3);
	ui.pointsList->setRowCount(controlPointList.size());

	QStringList header;
	ui.pointsList->setHorizontalHeaderLabels(header);

	header.push_back(QString("X"));
	header.push_back(QString("Y"));
	header.push_back(QString("Weight"));


	for (int i = 0; i < controlPointList.size(); i++) {
		ui.pointsList->setItem(i, 0, new QTableWidgetItem(QString(std::to_string(controlPointList.at(i).getX()).c_str())));
		ui.pointsList->setItem(i, 1, new QTableWidgetItem(QString(std::to_string(controlPointList.at(i).getY()).c_str())));
		ui.pointsList->setItem(i, 2, new QTableWidgetItem(QString(std::to_string(controlPointList.at(i).getWeight()).c_str())));
	}
}

void EditorGui::exportToFile() {
	qDebug() << "Export to file";
	writeToFile("./points.pli", EditorGui::controlPointList);
}

void EditorGui::importFromFile() {
	qDebug() << "import from file";
	EditorGui::controlPointList = readFromFile("./points.pli");
	emit  controlPointListUpdated(controlPointList);
	controlPointChanged(controlPointList);
}