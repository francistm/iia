#include <QApplication>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "main_window.h"

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	int argc = 0;
	char *argv = { nullptr };

	QApplication app(argc, &argv);
	MainWindow mainWindow;

	mainWindow.show();

	return app.exec();
}
#else
int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	MainWindow mainWindow;

	mainWindow.show();

	return app.exec();
}
#endif