#include <array>
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QClipboard>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include "main_window.h"
#include "data_table.h"
#include "json_convert.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	setWindowTitle("IIA");

	QWidget *centralWidget = new QWidget(this);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	QHBoxLayout *topButtonLayout = new QHBoxLayout();

	QPushButton *loadFromClipboardBtn = new QPushButton("Clipboard");
	QPushButton *loadFromFileBtn = new QPushButton("File");
	QPushButton *useRegexpBtn = new QPushButton("RE Mode");

	loadFromClipboardBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	loadFromFileBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	useRegexpBtn->setCheckable(true);
	useRegexpBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	topButtonLayout->addWidget(loadFromClipboardBtn);
	topButtonLayout->addWidget(loadFromFileBtn);
	topButtonLayout->addWidget(useRegexpBtn);
	topButtonLayout->setAlignment(Qt::AlignLeft);

	DataTable *dataTable = new DataTable();

	mainLayout->addLayout(topButtonLayout);
	mainLayout->addWidget(dataTable);

	centralWidget->setLayout(mainLayout);

	setCentralWidget(centralWidget);
	resize(800, 600);

	QObject::connect(loadFromClipboardBtn, &QPushButton::pressed, [dataTable]() {
		QClipboard *clipboard;
		std::vector<std::shared_ptr<JsonConvert::KeyValue>> keyValues;

		clipboard = QApplication::clipboard();
		keyValues = JsonConvert::convertStdStringToKeyValues(clipboard->text().toStdString());

		dataTable->reloadData(keyValues);
	});

	QObject::connect(loadFromFileBtn, &QPushButton::pressed, [this, dataTable]() {
		QFile *file;
		QTextStream *readStream;
		QString filePath = QFileDialog::getOpenFileName(this, "Select File", "", "All files (*)");

		QString data;
		std::vector<std::shared_ptr<JsonConvert::KeyValue>> keyValues;

		if (filePath.isEmpty()) return;

		file = new QFile(filePath);

		if (file->open(QIODevice::ReadOnly | QIODevice::Text))
		{
			readStream = new QTextStream(file);
			data = readStream->readAll();
			file->close();
		}

		if (!data.isEmpty())
		{
			keyValues = JsonConvert::convertStdStringToKeyValues(data.toStdString());
			dataTable->reloadData(keyValues);
		}
	});

	QObject::connect(useRegexpBtn, &QPushButton::clicked, [dataTable](bool selected) {
		dataTable->setFilterMatchMode(selected ? FilterMatchMode::RE : FilterMatchMode::STD);
	});
}

MainWindow::~MainWindow()
{
}