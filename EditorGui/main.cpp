#include "stdafx.h"

#include <QtWidgets/QApplication>  // NOLINT
#include "EditorGui.h"

int main(int argc, char* argv[]) {
  QApplication application(argc, argv);
  EditorGui mainWindow;
  mainWindow.show();
  return application.exec();
}
