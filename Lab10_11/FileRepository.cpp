#include "FileRepository.h"
#include <fstream>
#include <sstream>
#include <cassert>

void FileRepository::loadFromFile() {
	std::ifstream fin{ this->fileName };

	if (!fin.is_open()) {
		throw RepoException{ "Eroare la deschiderea fisierului\n" };
	}

	std::string line;
	while (std::getline(fin, line)) {
		// skip empty lines
		if (line == "")
			continue;

		std::stringstream lineStream{ line };
		std::string name, manufacturer, activeSubstance, priceStr;
		double price;
		std::getline(lineStream, name, ',');
		std::getline(lineStream, priceStr, ',');
		std::getline(lineStream, manufacturer, ',');
		std::getline(lineStream, activeSubstance, ',');
		price = std::stod(priceStr);

		Medicament med{ name, price, manufacturer, activeSubstance };
		Repository::add(med);
	}

	fin.close();
}

void FileRepository::saveToFile() {
	std::ofstream fout{ this->fileName };

	if (!fout.is_open()) throw RepoException{ "Eroare la deschiderea fisierului\n" };

	for (const auto& med : this->getAll()) {
		fout << med.getName() << ",";
		fout << med.getPrice() << ",";
		fout << med.getManufacturer() << ",";
		fout << med.getActiveSubstance() << "\n";
	}

	fout.close();
}

void FileRepository::add(const Medicament& med) {
	Repository::add(med);
	this->saveToFile();
}

void FileRepository::remove(const Medicament& med) {
	Repository::remove(med);
	this->saveToFile();
}

void FileRepository::modify(const Medicament& med) {
	Repository::modify(med);
	this->saveToFile();
}

void FileRepository::clear() {
	Repository::clear();
	this->saveToFile();
}

void testOperationsFileRepo() {
	try {
		FileRepository fileRepo1{ "testInexistent.txt" }; assert(false); }
	catch (const RepoException& re) {
		assert(true);
		assert(re.getMessage() == "Eroare la deschiderea fisierului\n");
	}

	FileRepository fileRepo2{ "testOne.txt" };
	assert(fileRepo2.getSize() == 1);
	Medicament med = fileRepo2.find("Paracetamol Sinus");
	assert(med.getName() == "Paracetamol Sinus");
	assert(med.getManufacturer() == "ABC");
	assert(med.getPrice() == 50);
	assert(med.getActiveSubstance() == "Acetaminofen");

	FileRepository fileRepo3{ "testFull.txt" };
	assert(fileRepo3.getSize() == 6);

	// Create a new empty file
	std::ofstream out{ "testFile.txt", std::ios::out | std::ios::trunc };
	out.close();

	FileRepository fileRepo4{ "testFile.txt" };
	assert(fileRepo4.getSize() == 0);

	fileRepo4.add(Medicament{ "test", 200, "testProd", "testSubst" });
	assert(fileRepo4.getSize() == 1);
	fileRepo4.add(Medicament{ "test2", 100, "testProd2", "testSubst2" });
	assert(fileRepo4.getSize() == 2);
	fileRepo4.add(Medicament{ "test3", 150, "testProd3", "testSubst3" });
	assert(fileRepo4.getSize() == 3);
	fileRepo4.remove(Medicament{ "test2", 100, "testProd2", "testSubst2" });
	assert(fileRepo4.getSize() == 2);
	fileRepo4.modify(Medicament{ "test3", 300, "testProd3", "testSubst3" });
	assert(fileRepo4.getSize() == 2);

	std::ifstream fin{ "testFile.txt" };
	std::string line;
	std::getline(fin, line);
	assert(line == "test,200,testProd,testSubst");
	std::getline(fin, line);
	assert(line == "test3,300,testProd3,testSubst3");
	std::getline(fin, line);
	assert(line == "");
	assert(fin.eof());
	fin.close();

	fileRepo4.clear();
	assert(fileRepo4.getSize() == 0);
	fin.open("testFile.txt");
	std::getline(fin, line);
	assert(line == "");
	assert(fin.eof());
	fin.close();
}
