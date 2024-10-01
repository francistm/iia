#include <array>
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QClipboard>
#include <QApplication>
#include "main_window.h"
#include "data_table.h"
#include "json_converter.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	setWindowTitle("IIA");

	JsonConverter *converter = new JsonConverter();

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

	// connect signals
	QObject::connect(loadFromClipboardBtn, &QPushButton::pressed, [converter]() {
		QClipboard *clipboard = QApplication::clipboard();
		QString value = clipboard->text();

		converter->loadStdString(value.toStdString());
	});

	QObject::connect(converter, &JsonConverter::loaded, [dataTable](std::vector<KeyValue *> data) {
		dataTable->reloadData(data);
	});

	setCentralWidget(centralWidget);
	resize(800, 600);
}

MainWindow::~MainWindow()
{
}