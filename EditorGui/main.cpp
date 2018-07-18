#include "stdafx.h"
#include "EditorGui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);
	EditorGui mainWindow;
	mainWindow.show();
	return application.exec();
}
