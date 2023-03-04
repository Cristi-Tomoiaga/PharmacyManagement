#include "MedicamentGUI.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QInputDialog>
#include <QCloseEvent>
#include <QCoreApplication>
#include "PrescriptionCRUDGUI.h"
#include "PrescriptionReadOnlyGUI.h"

void MedicamentGUI::initGuiComponents() {
	setWindowTitle("Farmacie");
	// Main layout
	QHBoxLayout* layMain = new QHBoxLayout;
	this->setLayout(layMain);

	// Side TableWidget
	QWidget* left = new QWidget;
	QVBoxLayout* layLeft = new QVBoxLayout;
	left->setLayout(layLeft);

	// Search form
	QWidget* search = new QWidget;
	QHBoxLayout* laySearch = new QHBoxLayout;
	search->setLayout(laySearch);
	edtSearch->setPlaceholderText("Nume");
	laySearch->addWidget(edtSearch);
	laySearch->addWidget(btnSearch);
	layLeft->addWidget(search);

	// Table
	tableMedicaments->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	tableMedicaments->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableMedicaments->setSelectionMode(QAbstractItemView::SingleSelection);
	layLeft->addWidget(tableMedicaments);

	// Action buttons
	QWidget* tableActions = new QWidget;
	QVBoxLayout* layTableActions = new QVBoxLayout;
	tableActions->setLayout(layTableActions);

	QWidget* firstRowTableActions = new QWidget;
	QHBoxLayout* layFirstRowActions = new QHBoxLayout;
	firstRowTableActions->setLayout(layFirstRowActions);
	layFirstRowActions->addWidget(btnGenerate);
	layFirstRowActions->addWidget(btnReload);
	layTableActions->addWidget(firstRowTableActions);

	QGroupBox* secondRowTableActions = new QGroupBox("Filtrare");
	QHBoxLayout* laySecondRowActions = new QHBoxLayout;
	secondRowTableActions->setLayout(laySecondRowActions);
	laySecondRowActions->addWidget(btnFilterPrice);
	laySecondRowActions->addWidget(btnFilterActiveSubst);
	layTableActions->addWidget(secondRowTableActions);

	layLeft->addWidget(tableActions);
	layMain->addWidget(left);

	// Main form for CRUD operations
	QWidget* right = new QWidget;
	QVBoxLayout* layRight = new QVBoxLayout;
	right->setLayout(layRight);

	// Form
	QWidget* medForm = new QWidget;
	QFormLayout* layMedForm = new QFormLayout;
	medForm->setLayout(layMedForm);
	
	QLabel* lblName = new QLabel("Nume");
	layMedForm->addRow(lblName, edtName);
	QLabel* lblPrice = new QLabel("Pret");
	layMedForm->addRow(lblPrice, edtPrice);
	QLabel* lblManufacturer = new QLabel("Producator");
	layMedForm->addRow(lblManufacturer, edtManufacturer);
	QLabel* lblActiveSubst = new QLabel("Substanta activa");
	layMedForm->addRow(lblActiveSubst, edtActiveSubst);

	layRight->addWidget(medForm);

	// Action buttons
	QWidget* btnMedForm = new QWidget;
	QHBoxLayout* layBtnMedForm = new QHBoxLayout;
	btnMedForm->setLayout(layBtnMedForm);
	layBtnMedForm->addWidget(btnAdd);
	layBtnMedForm->addWidget(btnModify);
	layBtnMedForm->addWidget(btnRemove);
	layBtnMedForm->addWidget(btnUndo);
	layRight->addWidget(btnMedForm);

	QGroupBox* grpBoxSort = new QGroupBox("Sortare");
	QVBoxLayout* layGrpBoxSort = new QVBoxLayout;
	grpBoxSort->setLayout(layGrpBoxSort);
	radioBtnName->setChecked(true);
	layGrpBoxSort->addWidget(radioBtnName);
	layGrpBoxSort->addWidget(radioBtnManufacturer);
	layGrpBoxSort->addWidget(radioBtnActiveSubstPrice);
	layGrpBoxSort->addWidget(btnSort);
	layRight->addWidget(grpBoxSort);

	QWidget* prescription = new QWidget;
	QHBoxLayout* layPrescription = new QHBoxLayout;
	prescription->setLayout(layPrescription);
	layPrescription->addWidget(btnPrescription);
	layRight->addWidget(prescription);

	layRight->addStretch();
	layMain->addWidget(right);

	// Prescription menu
	QWidget* presc = new QWidget;
	QVBoxLayout* layPresc = new QVBoxLayout;
	presc->setLayout(layPresc);

	QGroupBox* grpPresc = new QGroupBox;
	grpPresc->setTitle("Reteta");
	QVBoxLayout* layGrpPresc = new QVBoxLayout;
	grpPresc->setLayout(layGrpPresc);

	layGrpPresc->addWidget(btnPrescAdd);
	layGrpPresc->addWidget(btnPrescClear);
	layGrpPresc->addWidget(btnPrescGenerate);
	layGrpPresc->addSpacing(10);
	layGrpPresc->addWidget(btnPrescCRUD);
	layGrpPresc->addWidget(btnPrescReadOnly);

	layPresc->addWidget(grpPresc);
	layPresc->addStretch();
	layMain->addWidget(presc);

	// Dynamic buttons for report
	QWidget* btnsReport = new QWidget;
	btnsReport->setLayout(layBtnsReport);

	layMain->addWidget(btnsReport);
}

void MedicamentGUI::connectSignalsSlots(){
	QObject::connect(tableMedicaments->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MedicamentGUI::reloadForm);
	
	QObject::connect(btnReload, &QPushButton::clicked, [&]() {
		this->reloadTable(this->srv.getAllMedicaments());
	});
	QObject::connect(btnGenerate, &QPushButton::clicked, this, &MedicamentGUI::generateMedicaments);
	QObject::connect(btnAdd, &QPushButton::clicked, this, &MedicamentGUI::addMedicament);
	QObject::connect(btnModify, &QPushButton::clicked, this, &MedicamentGUI::modifyMedicament);
	QObject::connect(btnRemove, &QPushButton::clicked, this, &MedicamentGUI::removeMedicament);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &MedicamentGUI::undoOperation);
	QObject::connect(btnSearch, &QPushButton::clicked, this, &MedicamentGUI::searchMedicament);
	QObject::connect(btnSort, &QPushButton::clicked, this, &MedicamentGUI::sortMedicaments);
	QObject::connect(btnFilterPrice, &QPushButton::clicked, this, &MedicamentGUI::filterByPrice);
	QObject::connect(btnFilterActiveSubst, &QPushButton::clicked, this, &MedicamentGUI::filterByActiveSubst);
	QObject::connect(btnPrescription, &QPushButton::clicked, [&]() {
		this->wndPrescription.show();
	});

	QObject::connect(btnPrescAdd, &QPushButton::clicked, this, &MedicamentGUI::addPrescMedicament);
	QObject::connect(btnPrescGenerate, &QPushButton::clicked, this, &MedicamentGUI::generatePrescription);
	QObject::connect(btnPrescClear, &QPushButton::clicked, this, &MedicamentGUI::clearPrescription);
	QObject::connect(btnPrescCRUD, &QPushButton::clicked, [&]() {
		PrescriptionCRUDGUI* wndCRUD = new PrescriptionCRUDGUI{ srv };
		wndCRUD->show();
	});
	QObject::connect(btnPrescReadOnly, &QPushButton::clicked, [&]() {
		PrescriptionReadOnlyGUI* wndReadOnly = new PrescriptionReadOnlyGUI{ srv };
		wndReadOnly->show();
	});
}

void MedicamentGUI::reloadTable(std::vector<Medicament> meds) {
	tableModel->setMedicaments(meds);
	generateButtonsReport();
}

void MedicamentGUI::reloadForm() {
	if (tableMedicaments->selectionModel()->selectedIndexes().isEmpty()) {
		edtName->clear();
		edtPrice->clear();
		edtManufacturer->clear();
		edtActiveSubst->clear();
		
		return;
	}

	int row = tableMedicaments->selectionModel()->selectedIndexes().at(0).row();

	QModelIndex ind = tableMedicaments->model()->index(row, 0);
	edtName->setText(tableMedicaments->model()->data(ind, Qt::DisplayRole).toString());
	ind = tableMedicaments->model()->index(row, 1);
	edtPrice->setText(tableMedicaments->model()->data(ind, Qt::DisplayRole).toString());
	ind = tableMedicaments->model()->index(row, 2);
	edtManufacturer->setText(tableMedicaments->model()->data(ind, Qt::DisplayRole).toString());
	ind = tableMedicaments->model()->index(row, 3);
	edtActiveSubst->setText(tableMedicaments->model()->data(ind, Qt::DisplayRole).toString());
}

void MedicamentGUI::generateMedicaments() {
	srv.generateMedicaments();

	reloadTable(srv.getAllMedicaments());
	QMessageBox::information(this, "Info", "Medicamentele au fost generate cu succes!");
}

void MedicamentGUI::addMedicament(){
	std::string name = edtName->text().trimmed().toStdString();
	bool ok;
	double price = edtPrice->text().trimmed().toDouble(&ok);
	if (!ok) {
		QMessageBox::warning(this, "Eroare", "Valoare reala invalida");
		return;
	}

	std::string manufacturer = edtManufacturer->text().trimmed().toStdString();
	std::string activeSubst = edtActiveSubst->text().trimmed().toStdString();

	edtName->clear();
	edtPrice->clear();
	edtManufacturer->clear();
	edtActiveSubst->clear();

	try {
		srv.addMedicament(name, price, manufacturer, activeSubst);

		reloadTable(srv.getAllMedicaments());
		QMessageBox::information(this, "Info", "Medicamentul a fost adaugat cu succes!");
	}
	catch (const RepoException& re) {
		QMessageBox::warning(this, "Eroare", QString::fromStdString(re.getMessage()));
	}
	catch (const ValidationException& ve) {
		QMessageBox::warning(this, "Eroare", QString::fromStdString(ve.getMessage()));
	}
}

void MedicamentGUI::modifyMedicament() {
	std::string name = edtName->text().trimmed().toStdString();
	bool ok;
	double price = edtPrice->text().trimmed().toDouble(&ok);
	if (!ok) {
		QMessageBox::warning(this, "Eroare", "Valoare reala invalida");
		return;
	}

	std::string manufacturer = edtManufacturer->text().trimmed().toStdString();
	std::string activeSubst = edtActiveSubst->text().trimmed().toStdString();

	edtName->clear();
	edtPrice->clear();
	edtManufacturer->clear();
	edtActiveSubst->clear();

	try {
		srv.modifyMedicament(name, price, manufacturer, activeSubst);

		reloadTable(srv.getAllMedicaments());
		QMessageBox::information(this, "Info", "Medicamentul a fost modificat cu succes!");
	}
	catch (const RepoException& re) {
		QMessageBox::warning(this, "Eroare", QString::fromStdString(re.getMessage()));
	}
	catch (const ValidationException& ve) {
		QMessageBox::warning(this, "Eroare", QString::fromStdString(ve.getMessage()));
	}
}

void MedicamentGUI::removeMedicament() {
	std::string name = edtName->text().trimmed().toStdString();

	edtName->clear();
	edtPrice->clear();
	edtManufacturer->clear();
	edtActiveSubst->clear();

	try {
		srv.removeMedicament(name);

		reloadTable(srv.getAllMedicaments());
		QMessageBox::information(this, "Info", "Medicamentul a fost sters cu succes!");
	}
	catch (const RepoException& re) {
		QMessageBox::warning(this, "Eroare", QString::fromStdString(re.getMessage()));
	}
}

void MedicamentGUI::undoOperation() {
	try {
		srv.undo();

		reloadTable(srv.getAllMedicaments());
		QMessageBox::information(this, "Info", "Undo-ul s-a realizat cu succes!");
	}
	catch (const UndoException& ue) {
		QMessageBox::warning(this, "Eroare", QString::fromStdString(ue.getMessage()));
	}
}

void MedicamentGUI::generateButtonsReport(){
	std::map<std::string, int> report = srv.generateReportOnActiveSubstance();

	// clear layout
	QLayoutItem* child;
	while (child = layBtnsReport->takeAt(0)) {
		delete child->widget();
		delete child;
	}

	for (const auto& item : report) {
		QPushButton* btn = new QPushButton{QString::fromStdString(item.first)};
		layBtnsReport->addWidget(btn);

		QObject::connect(btn, &QPushButton::clicked, [item]() {
			QMessageBox::information(nullptr, "Info", QString::number(item.second));
		});
	}
}

void MedicamentGUI::searchMedicament(){
	try {
		std::string name = edtSearch->text().trimmed().toStdString();
		edtSearch->clear();
		Medicament med = srv.findMedicament(name);

		std::vector<Medicament> meds;
		meds.push_back(med);
		reloadTable(meds);
	}
	catch (const RepoException& re) {
		reloadTable(srv.getAllMedicaments());
		QMessageBox::warning(this, "Eroare", QString::fromStdString(re.getMessage()));
	}
}

void MedicamentGUI::sortMedicaments(){
	if (radioBtnName->isChecked()) {
		reloadTable(srv.sortByName());
	}
	else if (radioBtnManufacturer->isChecked()) {
		reloadTable(srv.sortByManufacturer());
	}
	else if (radioBtnActiveSubstPrice->isChecked()) {
		reloadTable(srv.sortByActiveSubstancePrice());
	}
}

void MedicamentGUI::filterByPrice(){
	bool ok = false;
	double price = QInputDialog::getDouble(this, "Filtrare", "Pret maxim", 0.0, -1000, 1000, 2, &ok, Qt::WindowFlags(), 0.5);

	if (ok) {
		reloadTable(srv.filterByPrice(price));
	}
}

void MedicamentGUI::filterByActiveSubst(){
	bool ok = false;
	std::string activeSubst = QInputDialog::getText(this, "Filtrare", "Substanta activa", QLineEdit::Normal, "", &ok).toStdString();

	if (ok) {
		reloadTable(srv.filterByActiveSubstance(activeSubst));
	}
}

void MedicamentGUI::addPrescMedicament() {
	std::string name = edtName->text().trimmed().toStdString();
	edtName->clear();

	try {
		srv.addMedicamentToPrescription(name);
		QMessageBox::information(this, "Info", "Medicamentul a fost adaugat cu succes!");
	}
	catch (const RepoException& re) {
		QMessageBox::warning(this, "Eroare", QString::fromStdString(re.getMessage()));
	}
}

void MedicamentGUI::clearPrescription() {
	srv.clearPrescription();
	QMessageBox::information(this, "Info", "Reteta a fost golita!");
}

void MedicamentGUI::generatePrescription() {
	bool ok = false;
	int count = QInputDialog::getInt(this, "Generare", "Numar medicamente", 0, 0, INT_MAX, 1, &ok);

	if (ok) {
		srv.generateRandomPrescription(count);
		QMessageBox::information(this, "Info", "Reteta a fost generata!");
	}
}

void MedicamentGUI::closeEvent(QCloseEvent* ev){
	//wndPrescription.close();
	QCoreApplication::quit();
}
