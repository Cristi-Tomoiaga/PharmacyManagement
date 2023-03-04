#include <cassert>
#include <algorithm>
#include <fstream>
#include "Service.h"

std::string UndoException::getMessage() const {
	return this->msg;
}

const std::vector<Medicament> Service::getAllMedicaments() const {
	return this->repo.getAll();
}

void Service::addMedicament(const std::string& name, const double price, const std::string& manufacturer, const std::string& activeSubstance) {
	Medicament med{ name, price, manufacturer, activeSubstance };

	this->medVal.validate(med);
	this->repo.add(med);

	this->undoList.push_back(std::make_unique<UndoAdd>(this->repo, med));
}

void Service::modifyMedicament(const std::string& name, const double price, const std::string& manufacturer, const std::string& activeSubstance) {
	Medicament med{ name, price, manufacturer, activeSubstance };
	const Medicament originalMed = this->findMedicament(name);

	this->medVal.validate(med);
	this->repo.modify(med);

	this->undoList.push_back(std::make_unique<UndoModify>(this->repo, originalMed));
}

void Service::removeMedicament(const std::string& name) {
	const Medicament med = this->repo.find(name);

	this->repo.remove(med);

	this->undoList.push_back(std::make_unique<UndoRemove>(this->repo, med));
}

const Medicament& Service::findMedicament(const std::string& name) {
	return this->repo.find(name);
}

void Service::generateMedicaments() {
	this->repo.clear();
	addMedicament("Paracetamol Sinus", 50, "ABC", "Acetaminofen");
	addMedicament("Nurofen", 70, "Pharm", "Ibuprofen");
	addMedicament("Nurofen raceala si gripa", 80, "Pharm", "Ibuprofen");
	addMedicament("Imodium", 30, "ABC", "Loperamida");
	addMedicament("No-spa", 80, "Pharm", "Drotaverina");
	addMedicament("Paracetamol 1000", 95, "HPharm", "Acetaminofen");
}

std::vector<Medicament> Service::filterByPrice(double price) const {
	const std::vector<Medicament> allMeds{ this->getAllMedicaments() };
	std::vector<Medicament> filteredMeds;

	std::copy_if(allMeds.begin(), allMeds.end(), std::back_inserter(filteredMeds), 
		[price](Medicament med) noexcept { return med.getPrice() <= price; });

	return filteredMeds;
}

std::vector<Medicament> Service::filterByActiveSubstance(const std::string& activeSubstance) const {
	const std::vector<Medicament> allMeds{ this->getAllMedicaments() };
	std::vector<Medicament> filteredMeds;

	std::copy_if(allMeds.begin(), allMeds.end(), std::back_inserter(filteredMeds),
		[activeSubstance](Medicament med) { return med.getActiveSubstance() == activeSubstance; });

	return filteredMeds;
}

std::vector<Medicament> Service::sortByName() const {
	std::vector<Medicament> sortedMeds{ this->getAllMedicaments() };

	std::sort(sortedMeds.begin(), sortedMeds.end(), 
		[](const Medicament& med1, const Medicament& med2) { return med1.getName() < med2.getName(); });

	return sortedMeds;
}

std::vector<Medicament> Service::sortByManufacturer() const {
	std::vector<Medicament> sortedMeds{ this->getAllMedicaments() };

	std::sort(sortedMeds.begin(), sortedMeds.end(),
		[](const Medicament& med1, const Medicament& med2) { return med1.getManufacturer() < med2.getManufacturer(); });

	return sortedMeds;
}

std::vector<Medicament> Service::sortByActiveSubstancePrice() const {
	std::vector<Medicament> sortedMeds{ this->getAllMedicaments() };

	std::sort(sortedMeds.begin(), sortedMeds.end(),
		[](const Medicament& med1, const Medicament& med2) {
			if (med1.getActiveSubstance() != med2.getActiveSubstance())
				return med1.getActiveSubstance() < med2.getActiveSubstance();

			return med1.getPrice() < med2.getPrice();
		});

	return sortedMeds;
}

void Service::addMedicamentToPrescription(const std::string& name) {
	Medicament med = this->findMedicament(name);
	this->currentPrescription.addMedicament(med);
}

void Service::clearPrescription() noexcept {
	this->currentPrescription.clear();
}

void Service::generateRandomPrescription(int count) {
	this->currentPrescription.generateRandom(this->getAllMedicaments(), count);
}

void Service::exportPrescriptionToCSV(const std::string& filename) const {
	this->currentPrescription.exportCSV(filename);
}

const std::vector<Medicament>& Service::getAllMedicamentsFromPrescription() const noexcept {
	return this->currentPrescription.getMedicaments();
}

std::map<std::string, int> Service::generateReportOnActiveSubstance() const {
	std::map<std::string, int> report;

	for (const auto& med : getAllMedicaments()) {
		if (report.find(med.getActiveSubstance()) == report.end()) {
			// cheia nu a fost gasita, deci e prima oara cand o accesam
			report[med.getActiveSubstance()] = 0;
		}
		report[med.getActiveSubstance()]++;
	}

	return report;
}

void Service::undo() {
	if (this->undoList.empty()) {
		throw UndoException("Nu mai exista operatii pentru undo\n");
	}

	this->undoList.back()->doUndo();
	this->undoList.pop_back();
}

Prescription& Service::getPrescription() {
	return this->currentPrescription;
}

void testAddGetService() {
	MedicamentValidator medVal;
	Repository repo;
	repo.add(Medicament{ "Nume1", 100, "Prod1", "Subst1" });
	repo.add(Medicament{ "Nume2", 100, "Prod2", "Subst2" });
	Service srv{ repo, medVal };

	const auto& v = srv.getAllMedicaments();
	assert(v.size() == 2);

	srv.addMedicament("Nume3", 200, "Prod3", "Subst3");
	assert(repo.getSize() == 3);
	srv.addMedicament("Nume4", 230, "Prod4", "Subst4");
	assert(repo.getSize() == 4);

	try {
		srv.addMedicament("Nume1", 200, "Prod3", "Subst3"); assert(false);
	}
	catch (RepoException&) {
		assert(repo.getSize() == 4);
		assert(true);
	}

	try {
		srv.addMedicament("", -200, "Prod3", ""); assert(false);
	}
	catch (ValidationException&) {
		assert(true);
		assert(repo.getSize() == 4);
	}
}

void testModifyService() {
	MedicamentValidator medVal;
	Repository repo;
	Service srv{ repo, medVal };
	srv.addMedicament("Nume1", 100, "Prod1", "Subst1");
	srv.addMedicament("Nume2", 200, "Prod2", "Subst2");
	assert(repo.getSize() == 2);

	srv.modifyMedicament("Nume1", 300, "Prod5", "Subst10");
	assert(repo.getSize() == 2);

	try {
		srv.modifyMedicament("Nume4", 300, "Prod5", "Subst10"); assert(false);
	}
	catch (RepoException&) {
		assert(true);
		assert(repo.getSize() == 2);
	}

	try {
		srv.modifyMedicament("Nume1", -300, "", "Subst10"); assert(false);
	}
	catch (ValidationException&) {
		assert(true);
		assert(repo.getSize() == 2);
	}
}

void testRemoveService() {
	MedicamentValidator medVal;
	Repository repo;
	Service srv{ repo, medVal };
	srv.addMedicament("Nume1", 100, "Prod1", "Subst1");
	srv.addMedicament("Nume2", 200, "Prod2", "Subst2");
	assert(repo.getSize() == 2);

	srv.removeMedicament("Nume1");
	assert(repo.getSize() == 1);

	try {
		srv.removeMedicament("NumeCeva"); assert(false);
	}
	catch (RepoException&) {
		assert(true);
		assert(repo.getSize() == 1);
	}

	srv.removeMedicament("Nume2");
	assert(repo.getSize() == 0);

	try {
		srv.removeMedicament("NumeCeva2"); assert(false);
	}
	catch (RepoException&) {
		assert(true);
		assert(repo.getSize() == 0);
	}
}

void testFindService() {
	MedicamentValidator medVal;
	Repository repo;
	Service srv{ repo, medVal };
	srv.addMedicament("Nume1", 100, "Prod1", "Subst1");
	srv.addMedicament("Nume2", 200, "Prod2", "Subst2");
	assert(repo.getSize() == 2);

	const Medicament& med = srv.findMedicament("Nume1");
	assert(med.getName() == "Nume1");
	assert(fabs(med.getPrice() - 100) < 1e-5);
	assert(med.getManufacturer() == "Prod1");
	assert(med.getActiveSubstance() == "Subst1");

	try {
		srv.findMedicament("ceva"); assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
}

void testGenerateService(){
	MedicamentValidator medVal;
	Repository repo;
	Service srv{ repo, medVal };
	assert(repo.getSize() == 0);
	srv.generateMedicaments();
	assert(repo.getSize() == 6);
	srv.generateMedicaments();
	assert(repo.getSize() == 6);
}

void testFilterService() {
	MedicamentValidator medVal;
	Repository repo;
	Service srv{ repo, medVal };
	srv.addMedicament("Nume1", 120, "Prod1", "Subst3");
	srv.addMedicament("Nume2", 40, "Prod3", "Subst1");
	srv.addMedicament("Nume3", 70, "Prod2", "Subst2");
	srv.addMedicament("Nume4", 75, "Prod5", "Subst2");
	assert(repo.getSize() == 4);

	std::vector<Medicament> v = srv.filterByPrice(120);
	assert(v.size() == 4);

	v = srv.filterByPrice(300);
	assert(v.size() == 4);

	v = srv.filterByPrice(10);
	assert(v.size() == 0);

	v = srv.filterByPrice(50);
	assert(v.size() == 1);

	v = srv.filterByActiveSubstance("Subst1");
	assert(v.size() == 1);

	v = srv.filterByActiveSubstance("Subst");
	assert(v.size() == 0);

	v = srv.filterByActiveSubstance("Subst2");
	assert(v.size() == 2);
}

void testSortService() {
	MedicamentValidator medVal;
	Repository repo;
	Service srv{ repo, medVal };
	srv.addMedicament("Nume1", 120, "Prod1", "Subst3");
	srv.addMedicament("Nume2", 40, "Prod3", "Subst1");
	srv.addMedicament("Nume3", 70, "Prod2", "Subst2");
	srv.addMedicament("Nume4", 75, "Prod5", "Subst2");
	assert(repo.getSize() == 4);

	std::vector<Medicament> v = srv.sortByName();
	assert(v.size() == 4);
	assert(v.at(0).getName() == "Nume1");
	assert(v.at(1).getName() == "Nume2");
	assert(v.at(2).getName() == "Nume3");
	assert(v.at(3).getName() == "Nume4");

	v = srv.sortByManufacturer();
	assert(v.size() == 4);
	assert(v.at(0).getName() == "Nume1");
	assert(v.at(1).getName() == "Nume3");
	assert(v.at(2).getName() == "Nume2");
	assert(v.at(3).getName() == "Nume4");

	v = srv.sortByActiveSubstancePrice();
	assert(v.size() == 4);
	assert(v.at(0).getName() == "Nume2");
	assert(v.at(1).getName() == "Nume3");
	assert(v.at(2).getName() == "Nume4");
	assert(v.at(3).getName() == "Nume1");
}

void testPrescription() {
	MedicamentValidator medVal;
	Repository repo;
	Service srv{ repo, medVal };
	srv.addMedicament("Nume1", 120, "Prod1", "Subst3");
	srv.addMedicament("Nume2", 40, "Prod3", "Subst1");
	srv.addMedicament("Nume3", 70, "Prod2", "Subst2");

	assert(srv.getAllMedicamentsFromPrescription().size() == 0);
	srv.addMedicamentToPrescription("Nume1");
	assert(srv.getAllMedicamentsFromPrescription().size() == 1);
	srv.addMedicamentToPrescription("Nume2");
	assert(srv.getAllMedicamentsFromPrescription().size() == 2);
	srv.addMedicamentToPrescription("Nume3");
	assert(srv.getAllMedicamentsFromPrescription().size() == 3);

	Prescription& presc = srv.getPrescription();
	assert(presc.getMedicaments().size() == 3);

	try {
		srv.addMedicamentToPrescription("Nume5"); assert(false);
	}
	catch (RepoException&) {
		assert(true);
		assert(srv.getAllMedicamentsFromPrescription().size() == 3);
	}

	srv.clearPrescription();
	assert(srv.getAllMedicamentsFromPrescription().size() == 0);
	srv.clearPrescription();
	assert(srv.getAllMedicamentsFromPrescription().size() == 0);

	srv.generateRandomPrescription(0);
	assert(srv.getAllMedicamentsFromPrescription().size() == 0);
	srv.generateRandomPrescription(1);
	assert(srv.getAllMedicamentsFromPrescription().size() == 1);
	srv.generateRandomPrescription(3);
	assert(srv.getAllMedicamentsFromPrescription().size() == 3);
	srv.generateRandomPrescription(15);
	assert(srv.getAllMedicamentsFromPrescription().size() == 3);

	srv.clearPrescription();
	assert(srv.getAllMedicamentsFromPrescription().size() == 0);

	srv.exportPrescriptionToCSV("test2.csv");
	std::ifstream fin("test2.csv");
	std::string line;
	assert(fin.is_open());
	getline(fin, line);
	assert(fin.eof());
	fin.close();

	srv.addMedicamentToPrescription("Nume1");
	srv.addMedicamentToPrescription("Nume2");
	assert(srv.getAllMedicamentsFromPrescription().size() == 2);

	srv.exportPrescriptionToCSV("test2.csv");
	fin.open("test2.csv");
	assert(fin.is_open());
	getline(fin, line);
	assert(!fin.eof());
	getline(fin, line);
	assert(!fin.eof());
	getline(fin, line);
	assert(fin.eof());
	fin.close();
}

void testReportService() {
	MedicamentValidator medVal;
	Repository repo;
	Service srv{ repo, medVal };
	
	assert(srv.getAllMedicaments().size() == 0);
	std::map<std::string, int> report = srv.generateReportOnActiveSubstance();
	assert(report.size() == 0);

	srv.addMedicament("Nume1", 120, "Prod1", "Subst3");
	assert(srv.getAllMedicaments().size() == 1);
	report = srv.generateReportOnActiveSubstance();
	assert(report.size() == 1);
	assert(report["Subst3"] == 1);

	srv.addMedicament("Nume2", 40, "Prod3", "Subst1");
	srv.addMedicament("Nume3", 70, "Prod2", "Subst1");
	srv.addMedicament("Nume4", 80, "Prod2", "Subst3");
	srv.addMedicament("Nume5", 280, "Prod2", "Subst2");
	assert(srv.getAllMedicaments().size() == 5);
	report = srv.generateReportOnActiveSubstance();
	assert(report.size() == 3);
	assert(report["Subst1"] == 2);
	assert(report["Subst2"] == 1);
	assert(report["Subst3"] == 2);

	srv.addMedicament("NumeNou", 180, "Prod2", "Subst3");
	srv.addMedicament("NumeNou2", 183, "Prod2", "Subst5");
	assert(srv.getAllMedicaments().size() == 7);

	report = srv.generateReportOnActiveSubstance();
	assert(report.size() == 4);
	assert(report["Subst1"] == 2);
	assert(report["Subst2"] == 1);
	assert(report["Subst3"] == 3);
	assert(report["Subst5"] == 1);
}

void testUndoService() {
	MedicamentValidator medVal;
	Repository repo;
	Service srv{ repo, medVal };
	srv.addMedicament("Nume1", 100, "Prod1", "Subst1");
	srv.addMedicament("Nume2", 200, "Prod2", "Subst2");
	assert(repo.getSize() == 2);

	srv.addMedicament("Nume3", 210, "Prod3", "Subst3");
	assert(repo.getSize() == 3);
	srv.undo();
	assert(repo.getSize() == 2);

	srv.removeMedicament("Nume2");
	assert(repo.getSize() == 1);
	srv.undo();
	assert(repo.getSize() == 2);

	srv.modifyMedicament("Nume1", 200, "Prod1", "Subst1");
	assert(repo.getSize() == 2);
	Medicament med = srv.findMedicament("Nume1");
	assert(med.getPrice() == 200);
	srv.undo();
	assert(repo.getSize() == 2);
	med = srv.findMedicament("Nume1");
	assert(med.getPrice() == 100);

	srv.undo();
	srv.undo();
	try {
		srv.undo(); assert(false); }
	catch (const UndoException& ue) {
		assert(true);
		assert(ue.getMessage() == "Nu mai exista operatii pentru undo\n");
	}
	try {
		srv.undo(); assert(false); }
	catch (const UndoException& ue) {
		assert(true);
		assert(ue.getMessage() == "Nu mai exista operatii pentru undo\n");
	}
}
