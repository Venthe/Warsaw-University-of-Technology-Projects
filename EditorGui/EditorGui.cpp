#include "stdafx.h"
#include "EditorGui.h"

#include "DrawingArea.h"

EditorGui::EditorGui(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QLabel *label = new QLabel(ui.drawingArea->mousePosition().c_str());
	statusBar()->addWidget(label);
}
