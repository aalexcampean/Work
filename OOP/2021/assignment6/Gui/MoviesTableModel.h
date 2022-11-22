#pragma once
#include "../Service/AdminService.h"
#include <QAbstractListModel>
#include <qpixmap.h>

class MoviesTableModel: public QAbstractTableModel {
private:
    std::vector<Movie> inputVector;

public:
    MoviesTableModel(std::vector<Movie>&, QObject *parent = nullptr);
    virtual ~MoviesTableModel();

	// number of rows
	int rowCount(const QModelIndex &parent = QModelIndex{}) const override;
    // number of columns
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    // Value at a given position
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

