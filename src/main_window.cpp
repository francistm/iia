#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QClipboard>
#include <QApplication>
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
	QPushButton *viewBackBtn = new QPushButton("<");
	QPushButton *setAsRootBtn = new QPushButton("R");

	loadFromClipboardBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	loadFromFileBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	viewBackBtn->setEnabled(false);
	viewBackBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	setAsRootBtn->setEnabled(false);
	setAsRootBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	topButtonLayout->addWidget(loadFromClipboardBtn);
	topButtonLayout->addWidget(loadFromFileBtn);
	topButtonLayout->addWidget(viewBackBtn);
	topButtonLayout->addWidget(setAsRootBtn);
	topButtonLayout->setAlignment(Qt::AlignLeft);

	DataTable *dataTable = new DataTable();

	mainLayout->addLayout(topButtonLayout);
	mainLayout->addWidget(dataTable);

	centralWidget->setLayout(mainLayout);

	// connect signals
	QObject::connect(loadFromClipboardBtn, &QPushButton::pressed, []() {
		QClipboard *clipboard = QApplication::clipboard();
		QString value = clipboard->text();
	});

	setCentralWidget(centralWidget);
	resize(800, 600);
}

MainWindow::~MainWindow()
{
}