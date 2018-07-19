#include "stdafx.h"
#include "EditorGui.h"

#include "DrawingArea.h"
#include "Io.h"

EditorGui::EditorGui(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);
	ui.drawingArea->setControlPointList(&controlPointsList);
	ui.drawingArea->setControlPointWeight(&controlPointWeight);
	ui.centralWidget->setLayout(ui.mainGrid);

	connectDrawingArea();
	connectPointList();

	controlPointsChanged();
}

void EditorGui::connectDrawingArea() {
	connect(ui.drawingArea, SIGNAL(mousePositionChanged(QPoint)), this, SLOT(mousePositionChanged(QPoint)));
	connect(ui.drawingArea, SIGNAL(controlPointListChanged()), this, SLOT(controlPointsChanged()));

	connect(this, SIGNAL(updatePoints()), ui.drawingArea, SLOT(controlPointListUpdated()));
}

void EditorGui::connectPointList() {
	connect(ui.exportPointsButton, SIGNAL(clicked()), this, SLOT(exportPoints()));
	connect(ui.importPointsButton, SIGNAL(clicked()), this, SLOT(importPoints()));
}

// TODO:: Split into signal/slot pair on main gui
void EditorGui::controlPointsChanged() {
	updatePointListTable();

	emit updatePoints();
}

void EditorGui::mousePositionChanged(QPoint mousePosition) {
	// TODO: To function
	statusBar()->showMessage(QString((std::to_string(mousePosition.x()) + " " + std::to_string(mousePosition.y()) + " " + std::to_string(controlPointWeight)).c_str()));
}

void EditorGui::updatePointListTable() {
	ui.pointsList->setColumnCount(3);
	ui.pointsList->setRowCount(controlPointsList.size());

	QStringList header;
	header.push_back(QString("X"));
	header.push_back(QString("Y"));
	header.push_back(QString("Weight"));
	ui.pointsList->setHorizontalHeaderLabels(header);

	for (int i = 0; i < controlPointsList.size(); i++) {
		ui.pointsList->setItem(
			i, 0,
			new QTableWidgetItem(
				QString(std::to_string(controlPointsList.at(i).getX()).c_str())));
		ui.pointsList->setItem(
			i, 1,
			new QTableWidgetItem(
				QString(std::to_string(controlPointsList.at(i).getY()).c_str())));
		ui.pointsList->setItem(
			i, 2,
			new QTableWidgetItem(QString(
				std::to_string(controlPointsList.at(i).getWeight()).c_str())));
	}
}

void EditorGui::exportPoints() {
	// TODO: Make file name changeable
	esl::io::writeToFile("./points.pli", EditorGui::controlPointsList);
}

void EditorGui::importPoints() {
	// TODO: Make file name changeable
	EditorGui::controlPointsList = esl::io::readFromFile("./points.pli");
	controlPointsChanged();
}

// TODO: Restore Add Point functionality, maybe as modal?
// TODO: Add weight change via scroll/buttons?
// TODO: Edit list table inline