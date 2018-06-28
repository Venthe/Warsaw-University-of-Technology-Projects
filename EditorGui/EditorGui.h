#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EditorGui.h"

class EditorGui : public QMainWindow
{
	Q_OBJECT

public:
	EditorGui(QWidget *parent = Q_NULLPTR);
	
	QWidget renderArea;

private:
	Ui::EditorGuiClass ui;
};
