#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QListView>
#include <QLabel>
#include "Service.h"
#include "ObserverPattern.h"
#include "MedicamentListModel.h"

/*
* The window for Prescription
*/
class PrescriptionGUI : public QWidget, public Observer {
private:
	Service& srv;

	QListView* listPrescription = new QListView;
	MedicamentListModel* listModel = new MedicamentListModel;
	QLineEdit* edtName = new QLineEdit;
	QLabel* lblPrescriptionSize = new QLabel;

	QPushButton* btnAdd = new QPushButton("Adauga");
	QPushButton* btnClear = new QPushButton("Goleste");
	QPushButton* btnGenerate = new QPushButton("Genereaza");
	QPushButton* btnExport = new QPushButton("Exporta");
	QPushButton* btnClose = new QPushButton("Inchide");

	/*
	* Initializes the GUI components and layouts of the window
	*/
	void initGuiComponents();

	/*
	* Connects the signals of the components to the slots
	*/
	void connectSignalsSlots();

	/*
	* Reloads the data stored in the service for the Prescription
	*/
	void reloadData();

	/*
	* Adds a Medicament to the Prescription
	*/
	void addMedicament();

	/*
	* Clears the Prescription
	*/
	void clearPrescription();

	/*
	* Generates a random Prescription
	*/
	void generatePrescription();

	/*
	* Exports the Prescription
	*/
	void exportPrescription();
public:
	/*
	* Constructor for PrescriptionGUI
	* @param srv: Service
	*/
	PrescriptionGUI(Service& srv) : srv{ srv } {
		initGuiComponents();
		listPrescription->setModel(listModel);
		connectSignalsSlots();
		reloadData();

		srv.getPrescription().addObserver(this);
	}

	/*
	* Called when the observable object changes its state
	*/
	void update() override {
		reloadData();
	}

	/*
	* Destructor for PrescriptionGUI
	*/
	~PrescriptionGUI() {
		srv.getPrescription().removeObserver(this);
	}
};
