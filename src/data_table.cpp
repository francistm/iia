#include <QString>
#include <QWidget>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QHeaderView>
#include <QRegularExpression>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "data_table.h"

DataTable::DataTable(QWidget *parent) : QWidget(parent)
{
	QVBoxLayout *widgetLayout = new QVBoxLayout();
	QHBoxLayout *filterLayout = new QHBoxLayout();

	model.setColumnCount(2);
	filterMatchMode = FilterMatchMode::STD;

	propFilter.setPlaceholderText("Search field name");
	valueFilter.setPlaceholderText("Search field value");

	filterLayout->addWidget(&propFilter);
	filterLayout->addWidget(&valueFilter);

	propFilterModel.setSourceModel(&model);
	propFilterModel.setFilterCaseSensitivity(Qt::CaseInsensitive);

	valueFilterModel.setSourceModel(&propFilterModel);
	valueFilterModel.setFilterCaseSensitivity(Qt::CaseInsensitive);

	QObject::connect(&propFilter, &QLineEdit::textChanged, [&](const QString &text) {
		propFilterModel.setFilterKeyColumn(0);

		if (filterMatchMode == FilterMatchMode::STD) {
			propFilterModel.setFilterFixedString(text);
		} else {
			QRegularExpression re(text);
			if (re.isValid()) propFilterModel.setFilterRegularExpression(re);
		}
	});

	QObject::connect(&valueFilter, &QLineEdit::textChanged, [&](const QString &text) {
		valueFilterModel.setFilterKeyColumn(1);

		if (filterMatchMode == FilterMatchMode::STD) {
			valueFilterModel.setFilterFixedString(text);
		} else {
			QRegularExpression re(text);
			if (re.isValid()) valueFilterModel.setFilterRegularExpression(re);
		}
	});

	QTableView *tableView = new QTableView();
	tableView->setModel(&valueFilterModel);
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

void DataTable::setFilterMatchMode(FilterMatchMode mode)
{
	QString field = propFilter.text();
	QString value = valueFilter.text();

	if (mode == FilterMatchMode::STD) {
		propFilterModel.setFilterFixedString(field);
		valueFilterModel.setFilterFixedString(value);
	} else {
		QRegularExpression fieldRe(field);
		QRegularExpression valueRe(value);

		if (fieldRe.isValid()) propFilterModel.setFilterRegularExpression(fieldRe);
		if (valueRe.isValid()) valueFilterModel.setFilterRegularExpression(valueRe);
	}

	filterMatchMode = mode;
}