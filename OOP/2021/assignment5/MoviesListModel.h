#pragma once
#include <QAbstractListModel>
#include "../Service/AdminService.h"

class MoviesTableModel: public QAbstractListModel {
private:
    AdminService& as;

public:
    MoviesTableModel(AdminService& as, QObject *parent = nullptr);
    virtual ~MoviesTableModel();

	// number of rows
	int rowCount(const QModelIndex &parent = QModelIndex{}) const override;
    // Value at a given position
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

