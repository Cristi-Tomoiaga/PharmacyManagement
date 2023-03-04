#pragma once
#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include "Service.h"
#include "PrescriptionGUI.h"
#include "MedicamentTableModel.h"

/*
* The main window of the application
*/
class MedicamentGUI : public QWidget {
private:
	Service& srv;
	PrescriptionGUI wndPrescription{ srv };

	QTableView* tableMedicaments = new QTableView;
	MedicamentTableModel* tableModel = new MedicamentTableModel;
	QVBoxLayout* layBtnsReport = new QVBoxLayout;

	QPushButton* btnGenerate = new QPushButton("Generare medicamente");
	QPushButton* btnReload = new QPushButton("Reincarca medicamente");
	QPushButton* btnAdd = new QPushButton("Adauga");
	QPushButton* btnModify = new QPushButton("Modifica");
	QPushButton* btnRemove = new QPushButton("Sterge");
	QPushButton* btnUndo = new QPushButton("Undo");
	QPushButton* btnSearch = new QPushButton("Search");
	QPushButton* btnSort = new QPushButton("Sorteaza");
	QPushButton* btnFilterPrice = new QPushButton("Dupa pret");
	QPushButton* btnFilterActiveSubst = new QPushButton("Dupa substanta activa");
	QPushButton* btnPrescription = new QPushButton("Reteta");

	QPushButton* btnPrescAdd = new QPushButton("Adauga");
	QPushButton* btnPrescClear = new QPushButton("Goleste");
	QPushButton* btnPrescGenerate = new QPushButton("Genereaza");
	QPushButton* btnPrescCRUD = new QPushButton("Reteta CRUD");
	QPushButton* btnPrescReadOnly = new QPushButton("Reteta ReadOnly");

	QRadioButton* radioBtnName = new QRadioButton("Dupa denumire");
	QRadioButton* radioBtnManufacturer = new QRadioButton("Dupa producator");
	QRadioButton* radioBtnActiveSubstPrice = new QRadioButton("Dupa substanta activa si pret");

	QLineEdit* edtName = new QLineEdit;
	QLineEdit* edtPrice = new QLineEdit;
	QLineEdit* edtManufacturer = new QLineEdit;
	QLineEdit* edtActiveSubst = new QLineEdit;
	QLineEdit* edtSearch = new QLineEdit;

	/*
	* Initializes the GUI components and layouts of the window
	*/
	void initGuiComponents();

	/*
	* Connects the signals of the components to the slots
	*/
	void connectSignalsSlots();

	/*
	* Reloads the table with the data provided in the vector
	* @param meds: a list of Medicament objects
	*/
	void reloadTable(std::vector<Medicament> meds);

	/*
	* Reloads the form with the selection made in the table
	*/
	void reloadForm();

	/*
	* Generates test data for Medicaments
	*/
	void generateMedicaments();

	/*
	* Adds a new Medicament to the application
	*/
	void addMedicament();

	/*
	* Modifies an existing Medicament from the application
	*/
	void modifyMedicament();

	/*
	* Removes an existing Medicament from the application
	*/
	void removeMedicament();

	/*
	* Undoes the last operation
	*/
	void undoOperation();

	/*
	* Adds buttons dynamically based on the report
	*/
	void generateButtonsReport();

	/*
	* Searches an existing Medicament by a given name from the application
	*/
	void searchMedicament();

	/*
	* Sorts the Medicaments in the application
	*/
	void sortMedicaments();

	/*
	* Filters the Medicaments in the application by price
	*/
	void filterByPrice();
	
	/*
	* Filters the Medicaments in the application by active substance
	*/
	void filterByActiveSubst();

	/*
	* Adds a Medicament to the Prescription
	*/
	void addPrescMedicament();

	/*
	* Clears the Prescription
	*/
	void clearPrescription();

	/*
	* Generates a random Prescription
	*/
	void generatePrescription();

protected:
	void closeEvent(QCloseEvent* ev) override;

public:
	/*
	* Constructor for GUI
	* @param srv: Service
	*/
	MedicamentGUI(Service& srv) : srv{ srv } {
		initGuiComponents();
		tableMedicaments->setModel(tableModel);
		connectSignalsSlots();
		reloadTable(srv.getAllMedicaments());
		generateButtonsReport();
	}
};
