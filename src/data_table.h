#pragma once

#include <qwidget.h>

class DataTable : public QWidget
{
	Q_OBJECT

public:
	explicit DataTable(QWidget *parent = 0);
	~DataTable();
};