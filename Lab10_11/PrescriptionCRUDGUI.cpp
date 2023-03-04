#include "PrescriptionCRUDGUI.h"
#include "Medicament.h"

void PrescriptionCRUDGUI::initGuiComponents() {
	setWindowTitle("Reteta CRUD");
	setAttribute(Qt::WA_DeleteOnClose);

	// Main Layout
	QHBoxLayout* layMain = new QHBoxLayout;
	setLayout(layMain);

	// List Widget
	listPrescription->setSelectionMode(QAbstractItemView::NoSelection);
	listPrescription->setUniformItemSizes(true);
	layMain->addWidget(listPrescription);

	// Action buttons
	QWidget* actions = new QWidget;
	QVBoxLayout* layActions = new QVBoxLayout;
	actions->setLayout(layActions);

	layActions->addWidget(btnClear);
	layActions->addWidget(btnGenerate);
	layActions->addStretch();

	layMain->addWidget(actions);
}

void PrescriptionCRUDGUI::connectSignalsSlots() {
	QObject::connect(btnClear, &QPushButton::clicked, this, &PrescriptionCRUDGUI::clearPrescription);
	QObject::connect(btnGenerate, &QPushButton::clicked, this, &PrescriptionCRUDGUI::generatePrescription);
}

void PrescriptionCRUDGUI::reloadData() {
	listModel->setMedicaments(srv.getAllMedicamentsFromPrescription());
}

void PrescriptionCRUDGUI::clearPrescription() {
	srv.clearPrescription();
	reloadData();
	QMessageBox::information(this, "Info", "Reteta a fost golita!");
}

void PrescriptionCRUDGUI::generatePrescription() {
	bool ok = false;
	int count = QInputDialog::getInt(this, "Generare", "Numar medicamente", 0, 0, INT_MAX, 1, &ok);

	if (ok) {
		srv.generateRandomPrescription(count);
		reloadData();
		QMessageBox::information(this, "Info", "Reteta a fost generata!");
	}
}
