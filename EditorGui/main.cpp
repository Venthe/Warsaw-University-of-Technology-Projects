#include "stdafx.h"
#include "EditorGui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	EditorGui w;
	w.show();
	return a.exec();
}
