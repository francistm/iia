#include <qwidget.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include "main_window.h"
#include "data_table.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	setWindowTitle("IIA");

	QWidget *centralWidget = new QWidget(this);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	QHBoxLayout *topButtonLayout = new QHBoxLayout();

	QPushButton *loadFromClipboardBtn = new QPushButton("Clipboard");
	QPushButton *loadFromFileBtn = new QPushButton("File");

	loadFromClipboardBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	loadFromFileBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	topButtonLayout->addWidget(loadFromClipboardBtn);
	topButtonLayout->addWidget(loadFromFileBtn);
	topButtonLayout->setAlignment(Qt::AlignLeft);

	DataTable *dataTable = new DataTable();

	mainLayout->addLayout(topButtonLayout);
	mainLayout->addWidget(dataTable);

	centralWidget->setLayout(mainLayout);

	setCentralWidget(centralWidget);
	resize(800, 600);
}

MainWindow::~MainWindow()
{
}