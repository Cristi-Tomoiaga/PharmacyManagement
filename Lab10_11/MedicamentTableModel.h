#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "Medicament.h"

class MedicamentTableModel: public QAbstractTableModel {
private:
	std::vector<Medicament> medicaments;
public:
	/*
	* Constructor for MedicamentTableModel
	*/
	MedicamentTableModel(QObject* parent = nullptr) : QAbstractTableModel{ parent } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return static_cast<int>(medicaments.size());
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			int row = index.row();
			Medicament med = this->medicaments[row];

			int col = index.column();
			if (col == 0) {
				return QString::fromStdString(med.getName());
			}
			else if (col == 1) {
				return QString::number(med.getPrice());
			}
			else if (col == 2) {
				return QString::fromStdString(med.getManufacturer());
			}
			else if (col == 3) {
				return QString::fromStdString(med.getActiveSubstance());
			}
		}

		return QVariant{};
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
		if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
			if (section == 0) {
				return QString{ "Nume" };
			}
			else if (section == 1) {
				return QString{ "Pret" };
			}
			else if (section == 2) {
				return QString{ "Producator" };
			}
			else if (section == 3) {
				return QString{ "Substanta activa" };
			}
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
		QModelIndex bottomRight = createIndex(rowCount() - 1, columnCount() - 1);
		emit layoutChanged();
		emit dataChanged(topLeft, bottomRight);
	}
};