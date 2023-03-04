#pragma once
#include <QWidget>
#include <QListView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include "Service.h"
#include "ObserverPattern.h"
#include "MedicamentListModel.h"

class PrescriptionCRUDGUI: public QWidget, public Observer {
private:
	Service& srv;

	QListView* listPrescription = new QListView;
	MedicamentListModel* listModel = new MedicamentListModel;

	QPushButton* btnClear = new QPushButton("Goleste");
	QPushButton* btnGenerate = new QPushButton("Genereaza");

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
	* Clears the Prescription
	*/
	void clearPrescription();

	/*
	* Generates a random Prescription
	*/
	void generatePrescription();
public:
	/*
	* Constructor for PrescriptionCRUDGUI
	* @param srv: Service
	*/
	PrescriptionCRUDGUI(Service& srv) : srv{ srv } {
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
	* Destructor for PrescriptionCRUDGUI
	*/
	~PrescriptionCRUDGUI() {
		srv.getPrescription().removeObserver(this);
	}
};

