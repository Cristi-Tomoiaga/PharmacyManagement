#pragma once
#include <QAbstractListModel>
#include <vector>
#include "Medicament.h"

class MedicamentListModel: public QAbstractListModel {
private:
	std::vector<Medicament> medicaments;
public:
	/*
	* Constructor for MedicamentListModel
	*/
	MedicamentListModel(QObject* parent = nullptr) : QAbstractListModel{ parent } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return static_cast<int>(medicaments.size());
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			int row = index.row();
			Medicament med = this->medicaments[row];
			QString medString = QString::fromStdString(med.getName()) + ", " + QString::number(med.getPrice(), 'g', 2) + ", " + QString::fromStdString(med.getManufacturer() + ", " + med.getActiveSubstance());

			return medString;
		}

		return QVariant{};
	}

	/*
	* Setter for the underlying vector of Medicaments
	* @param meds: vector of Medicament objects
	*/
	void setMedicaments(const std::vector<Medicament>& meds) {
		this->medicaments = meds;

		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(rowCount() - 1, 0);
		//emit layoutChanged();
		emit dataChanged(topLeft, bottomRight);
	}
};