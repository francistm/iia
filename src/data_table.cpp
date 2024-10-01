#include <QString>
#include <QWidget>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "data_table.h"

DataTable::DataTable(QWidget *parent) : QWidget(parent)
{
	QVBoxLayout *widgetLayout = new QVBoxLayout();
	QHBoxLayout *filterLayout = new QHBoxLayout();

	// QTableView model & filter
	model.setColumnCount(2);

	QLineEdit *propFilter = new QLineEdit();
	QLineEdit *valueFilter = new QLineEdit();

	propFilter->setPlaceholderText("Search field name");
	valueFilter->setPlaceholderText("Search field value");

	filterLayout->addWidget(propFilter);
	filterLayout->addWidget(valueFilter);

	QSortFilterProxyModel *propFilterModel = new QSortFilterProxyModel();
	propFilterModel->setSourceModel(&model);
	propFilterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

	QSortFilterProxyModel *valueFilterModel = new QSortFilterProxyModel();
	valueFilterModel->setSourceModel(propFilterModel);
	valueFilterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

	QObject::connect(propFilter, &QLineEdit::textChanged, [propFilterModel](const QString &text) {
		propFilterModel->setFilterKeyColumn(0);
		propFilterModel->setFilterFixedString(text);
	});

	QObject::connect(valueFilter, &QLineEdit::textChanged, [valueFilterModel](const QString &text) {
		valueFilterModel->setFilterKeyColumn(1);
		valueFilterModel->setFilterFixedString(text);
	});

	QTableView *tableView = new QTableView();
	tableView->setModel(valueFilterModel);
	tableView->setSortingEnabled(false);
	tableView->verticalHeader()->setVisible(true);
	tableView->horizontalHeader()->setVisible(false);
	tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	widgetLayout->addLayout(filterLayout);
	widgetLayout->addWidget(tableView);

	widgetLayout->setContentsMargins(QMargins(0, 0, 0, 0));
	setLayout(widgetLayout);
}

DataTable::~DataTable()
{
}

void DataTable::reloadData(std::vector<KeyValue *> data)
{
	this->model.clear();

	for (int i = 0; i < data.size(); i++)
	{
		KeyValue *keyValue = data.at(i);
		QString fieldName = QString::fromStdString(keyValue->key);
		QString fieldValue = QString::fromStdString(keyValue->value);

		this->model.appendRow({ new QStandardItem(fieldName), new QStandardItem(fieldValue) });

		delete keyValue;
	}
}