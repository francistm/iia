#pragma once

#include <vector>
#include <QWidget>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "json_convert.h"

using namespace std;

enum FilterMatchMode
{
	RE,
	STD,
};

class DataTable : public QWidget
{
	Q_OBJECT

private:
	QStandardItemModel model;
	QLineEdit propFilter;
	QLineEdit valueFilter;
	FilterMatchMode filterMatchMode;
	QSortFilterProxyModel propFilterModel;
	QSortFilterProxyModel valueFilterModel;

public:
	explicit DataTable(QWidget *parent = 0);
	~DataTable();

	void reloadData(vector<shared_ptr<JsonConvert::KeyValue>> data);
	void setFilterMatchMode(FilterMatchMode mode);
};