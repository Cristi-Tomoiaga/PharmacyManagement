#include <QHboxLayout>
#include <QVboxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <vector>
#include <string>
#include "PrescriptionGUI.h"

void PrescriptionGUI::initGuiComponents() {
	setWindowTitle("Reteta");

	// Main Layout
	QHBoxLayout* layMain = new QHBoxLayout;
	setLayout(layMain);

	// List Widget
	QWidget* wdgList = new QWidget;
	QVBoxLayout* layWdgList = new QVBoxLayout;
	wdgList->setLayout(layWdgList);
	listPrescription->setSelectionMode(QAbstractItemView::NoSelection);
	listPrescription->setUniformItemSizes(true);
	layWdgList->addWidget(listPrescription);
	layWdgList->addWidget(lblPrescriptionSize);
	layMain->addWidget(wdgList);

	// Form and action buttons
	QWidget* formActions = new QWidget;
	QVBoxLayout* layFormActions = new QVBoxLayout;
	formActions->setLayout(layFormActions);

	// Form
	QWidget* form = new QWidget;
	QFormLayout* layForm = new QFormLayout;
	form->setLayout(layForm);
	QLabel* lblName = new QLabel("Nume");
	layForm->addRow(lblName, edtName);
	layFormActions->addWidget(form);

	// Actions
	QWidget* actions = new QWidget;
	QVBoxLayout* layActions = new QVBoxLayout;
	actions->setLayout(layActions);
	layActions->addWidget(btnAdd);
	layActions->addWidget(btnClear);
	layActions->addWidget(btnGenerate);
	layActions->addWidget(btnExport);
	layActions->addWidget(btnClose);
	layActions->addStretch();
	layFormActions->addWidget(actions);

	layMain->addWidget(formActions);
}

void PrescriptionGUI::connectSignalsSlots(){
	QObject::connect(btnClose, &QPushButton::clicked, this, &PrescriptionGUI::close);

	QObject::connect(btnAdd, &QPushButton::clicked, this, &PrescriptionGUI::addMedicament);
	QObject::connect(btnClear, &QPushButton::clicked, this, &PrescriptionGUI::clearPrescription);
	QObject::connect(btnGenerate, &QPushButton::clicked, this, &PrescriptionGUI::generatePrescription);
	QObject::connect(btnExport, &QPushButton::clicked, this, &PrescriptionGUI::exportPrescription);
}

void PrescriptionGUI::reloadData(){
	const std::vector<Medicament>& presc = srv.getAllMedicamentsFromPrescription();
	listModel->setMedicaments(presc);

	QString sizePrescription = "Numar de medicamente: " + QString::number(presc.size());
	lblPrescriptionSize->setText(sizePrescription);
}

void PrescriptionGUI::addMedicament(){
	std::string name = edtName->text().trimmed().toStdString();
	edtName->clear();

	try {
		srv.addMedicamentToPrescription(name);
		reloadData();
		QMessageBox::information(this, "Info", "Medicamentul a fost adaugat cu succes!");
	}
	catch (const RepoException& re) {
		QMessageBox::warning(this, "Eroare", QString::fromStdString(re.getMessage()));
	}
}

void PrescriptionGUI::clearPrescription() {
	srv.clearPrescription();
	reloadData();
	QMessageBox::information(this, "Info", "Reteta a fost golita!");
}

void PrescriptionGUI::generatePrescription(){
	bool ok = false;
	int count = QInputDialog::getInt(this, "Generare", "Numar medicamente", 0, 0, INT_MAX, 1, &ok);

	if (ok) {
		srv.generateRandomPrescription(count);
		reloadData();
		QMessageBox::information(this, "Info", "Reteta a fost generata!");
	}
}

void PrescriptionGUI::exportPrescription(){
	bool ok = false;
	std::string fileName = QInputDialog::getText(this, "Export", "Nume fisier", QLineEdit::Normal, "", &ok).toStdString();

	if (ok && !fileName.empty()) {
		srv.exportPrescriptionToCSV(fileName);
		QMessageBox::information(this, "Info", "Export-ul s-a realizat cu succes!");
	}
}
