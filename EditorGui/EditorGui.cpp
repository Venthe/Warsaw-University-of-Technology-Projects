#include "stdafx.h"
#include "EditorGui.h"

#include "DrawingArea.h"
#include "Io.h"

#include "AddDialog.h"

EditorGui::EditorGui(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.centralWidget->setLayout(ui.mainGrid);

	connect(ui.exportPointsButton, SIGNAL(clicked()), this, SLOT(exportToFile()));
	connect(ui.importPointsButton, SIGNAL(clicked()), this, SLOT(importFromFile()));
	connect(ui.drawingArea, SIGNAL(mousePositionChanged(QString)), this, SLOT(mousePositionUpdated(QString)));
	connect(ui.drawingArea, SIGNAL(controlPointListChanged(std::vector<ControlPoint>)), this, SLOT(controlPointChanged(std::vector<ControlPoint>)));

	connect(this, SIGNAL(controlPointListUpdated(std::vector<ControlPoint>)), ui.drawingArea, SLOT(controlPointListUpdated(std::vector<ControlPoint>)));

	connect(ui.addPointButton, SIGNAL(clicked()), this, SLOT(addPointClicked()));

	emit controlPointListUpdated(controlPointList);
}

void EditorGui::addPointClicked() {
	qDebug() << "Point clicked";
	//esl::ControlPoint newControlPoint = esl::controlPointFrom(ui.newPointText->toPlainText().toStdString());
	//controlPointList.push_back(newControlPoint);

	//qDebug() << "Point clicked" << newControlPoint.to_string().c_str() << ui.newPointText->toPlainText();
	controlPointChanged(controlPointList);
}

void EditorGui::mousePositionUpdated(QString text) {
	statusBar()->showMessage(text);
}

void EditorGui::controlPointChanged(std::vector<esl::ControlPoint> points) {
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
	header.push_back(QString("X"));
	header.push_back(QString("Y"));
	header.push_back(QString("Weight"));
	ui.pointsList->setHorizontalHeaderLabels(header);


	for (int i = 0; i < controlPointList.size(); i++) {
		ui.pointsList->setItem(i, 0, new QTableWidgetItem(QString(std::to_string(controlPointList.at(i).get_x()).c_str())));
		ui.pointsList->setItem(i, 1, new QTableWidgetItem(QString(std::to_string(controlPointList.at(i).get_y()).c_str())));
		ui.pointsList->setItem(i, 2, new QTableWidgetItem(QString(std::to_string(controlPointList.at(i).get_weight()).c_str())));
	}
}

void EditorGui::exportToFile() {
	qDebug() << "Export to file";
	esl::io::write_to_file("./points.pli", EditorGui::controlPointList);
}

void EditorGui::importFromFile() {
	qDebug() << "import from file";
	EditorGui::controlPointList = esl::io::read_from_file("./points.pli");
	controlPointChanged(controlPointList);
}