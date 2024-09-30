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
	QHBoxLayout *actionButtonsLayout = new QHBoxLayout();
	QHBoxLayout *filterLayout = new QHBoxLayout();

	QPushButton *viewBackBtn = new QPushButton("<");
	QPushButton *setAsRootBtn = new QPushButton("R");

	viewBackBtn->setEnabled(false);
	viewBackBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	setAsRootBtn->setEnabled(false);
	setAsRootBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	actionButtonsLayout->addWidget(viewBackBtn);
	actionButtonsLayout->addWidget(setAsRootBtn);
	actionButtonsLayout->setAlignment(Qt::AlignLeft);

	// QTableView model & filter
	QStandardItemModel *model = new QStandardItemModel();

	model->setColumnCount(2);

	QLineEdit *propFilter = new QLineEdit();
	QLineEdit *valueFilter = new QLineEdit();

	propFilter->setPlaceholderText("Search field name");
	valueFilter->setPlaceholderText("Search field value");

	filterLayout->addWidget(propFilter);
	filterLayout->addWidget(valueFilter);

	QSortFilterProxyModel *propFilterModel = new QSortFilterProxyModel();
	propFilterModel->setSourceModel(model);
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

	widgetLayout->addLayout(actionButtonsLayout);
	widgetLayout->addLayout(filterLayout);
	widgetLayout->addWidget(tableView);

	widgetLayout->setContentsMargins(QMargins(0, 0, 0, 0));
	setLayout(widgetLayout);
}

DataTable::~DataTable()
{
}