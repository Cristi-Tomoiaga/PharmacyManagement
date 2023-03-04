#include <QtWidgets/QApplication>
#include "Medicament.h"
#include "Validator.h"
#include "Repository.h"
#include "FileRepository.h"
#include "Prescription.h"
#include "Service.h"
#include "UI.h"
#include "MedicamentGUI.h"

/*
* Runs all tests
*/
void runTests() {
	testCreateGetMedicament();

	testCreateGetValidExcp();
	testValidateMedicament();

	testCreateGetRepoExp();
	testAddSizeGetClearRepo();
	testModifyRepo();
	testRemoveRepo();
	testFindExistsRepo();
	testOperationsFileRepo();

	testAddClearGetPrescription();
	testGeneratePrescription();
	testExportCSVPrescription();

	testAddGetService();
	testModifyService();
	testRemoveService();
	testFindService();
	testGenerateService();
	testFilterService();
	testSortService();
	testPrescription();
	testReportService();
	testUndoService();
}

/*
* Prepares and runs the application
*/
void runApp() {
	MedicamentValidator medVal;
	FileRepository repo{ "medicaments.txt" };
	Service srv{ repo, medVal };
	UI console{ srv };
	console.run();
}

/*
* Prepares and runs the GUI application
* @param argc: argc parameter from main
* @param argv: argv parameter from main
*/
void runGUIApp(int argc, char *argv[]) {
	QApplication a(argc, argv);

	MedicamentValidator medVal;
	FileRepository repo{ "medicaments.txt" };
	Service srv{ repo, medVal };
	MedicamentGUI gui{ srv };
	gui.show();

	a.exec();
}

int main(int argc, char* argv[]) {
	runTests();
	runGUIApp(argc, argv);

	return 0;
}