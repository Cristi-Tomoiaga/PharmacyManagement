#pragma once
#include <QWidget>
#include "Service.h"
#include "ObserverPattern.h"

class PrescriptionReadOnlyGUI: public QWidget, public Observer {
private:
	Service& srv;

protected:
	void paintEvent(QPaintEvent* event) override;

public:
	/*
	* Constructor for PrescriptionReadOnlyGUI
	* @param srv: Service
	*/
	PrescriptionReadOnlyGUI(Service& srv) : srv{ srv } {
		setWindowTitle("Reteta ReadOnly");
		setAttribute(Qt::WA_DeleteOnClose);

		srv.getPrescription().addObserver(this);
		srand(time(NULL));
	}

	/*
	* Called when the observable object changes its state
	*/
	void update() override {
		repaint();
	}

	/*
	* Destructor for PrescriptionReadOnlyGUI
	*/
	~PrescriptionReadOnlyGUI() {
		srv.getPrescription().removeObserver(this);
	}
};

