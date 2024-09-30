#include <Windows.h>
#include <qapplication.h>
#include <qpushbutton.h>
#include "main_window.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	int argc = 0;
	char *argv = { nullptr };

	QApplication app(argc, &argv);
	MainWindow mainWindow;

	mainWindow.show();

	return app.exec();
}