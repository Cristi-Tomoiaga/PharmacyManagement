#include <cassert>
#include <fstream>
#include <algorithm>
#include <random>
#include "Prescription.h"

void Prescription::addMedicament(const Medicament& med) {
	this->medicaments.push_back(med);

	this->notify();
}

void Prescription::clear() noexcept {
	this->medicaments.clear();

	this->notify();
}

void Prescription::generateRandom(std::vector<Medicament> medicamentList, int count) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::shuffle(medicamentList.begin(), medicamentList.end(), mt);

	this->clear();
	while (count > 0 && medicamentList.size() > 0) {
		this->medicaments.push_back(medicamentList.back());
		medicamentList.pop_back();
		count--;
	}

	this->notify();
}

void Prescription::exportCSV(const std::string& filename) const {
	std::ofstream fout(filename);

	for (const Medicament& med : this->medicaments) {
		fout << med.getName() << "," << med.getPrice() << "," << med.getManufacturer() << "," << med.getActiveSubstance() << std::endl;
	}

	fout.close();
}

const std::vector<Medicament>& Prescription::getMedicaments() const noexcept {
	return this->medicaments;
}

void testAddClearGetPrescription() {
	Medicament med1{ "nume1", 100, "prod1", "subst1" };
	Medicament med2{ "nume2", 150, "prod2", "subst2" };
	Medicament med3{ "nume3", 400, "prod3", "subst3" };
	Prescription p;

	assert(p.getMedicaments().size() == 0);
	p.addMedicament(med1);
	assert(p.getMedicaments().size() == 1);
	p.addMedicament(med2);
	assert(p.getMedicaments().size() == 2);
	p.addMedicament(med3);
	assert(p.getMedicaments().size() == 3);

	std::vector<Medicament> v = p.getMedicaments();
	assert(v.size() == 3);
	assert(v.at(0).getName() == med1.getName());
	assert(v.at(1).getName() == med2.getName());
	assert(v.at(2).getName() == med3.getName());

	p.clear();
	assert(p.getMedicaments().size() == 0);
	p.clear();
	assert(p.getMedicaments().size() == 0);
}

void testGeneratePrescription() {
	Medicament med1{ "nume1", 100, "prod1", "subst1" };
	Medicament med2{ "nume2", 150, "prod2", "subst2" };
	Medicament med3{ "nume3", 400, "prod3", "subst3" };
	std::vector<Medicament> meds;
	meds.push_back(med1);
	meds.push_back(med2);
	meds.push_back(med3);
	Prescription p;

	assert(p.getMedicaments().size() == 0);
	p.generateRandom(meds, 0);
	assert(p.getMedicaments().size() == 0);
	p.generateRandom(meds, 1);
	assert(p.getMedicaments().size() == 1);
	p.generateRandom(meds, 10);
	assert(p.getMedicaments().size() == 3);
}

void testExportCSVPrescription() {
	Medicament med1{ "nume1", 100, "prod1", "subst1" };
	Medicament med2{ "nume2", 150, "prod2", "subst2" };
	Medicament med3{ "nume3", 400, "prod3", "subst3" };
	Prescription p;

	assert(p.getMedicaments().size() == 0);
	p.exportCSV("test.csv");
	std::ifstream fin("test.csv");
	assert(fin.is_open());
	std::string line;
	getline(fin, line);
	assert(line == "");
	assert(fin.eof());
	fin.close();

	p.addMedicament(med1);
	assert(p.getMedicaments().size() == 1);
	p.exportCSV("test.csv");
	fin.open("test.csv");
	getline(fin, line);
	assert(line == "nume1,100,prod1,subst1");
	getline(fin, line);
	assert(line == "");
	assert(fin.eof());
	fin.close();

	p.addMedicament(med2);
	p.addMedicament(med3);

	assert(p.getMedicaments().size() == 3);
	p.exportCSV("test.csv");
	fin.open("test.csv");
	getline(fin, line);
	assert(line == "nume1,100,prod1,subst1");
	getline(fin, line);
	assert(line == "nume2,150,prod2,subst2");
	getline(fin, line);
	assert(line == "nume3,400,prod3,subst3");
	getline(fin, line);
	assert(line == "");
	assert(fin.eof());
	fin.close();
}
