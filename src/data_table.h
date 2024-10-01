#pragma once

#include <array>
#include <QWidget>
#include <QStandardItemModel>
#include "json_converter.h"

class DataTable : public QWidget
{
	Q_OBJECT

private:
	QStandardItemModel model;

public:
	explicit DataTable(QWidget *parent = 0);
	~DataTable();

	void reloadData(std::vector<KeyValue *> data);
};