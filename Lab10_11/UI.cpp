#include "UI.h"
#include <iostream>
#include <stdexcept>
#include <map>

void UI::trim(std::string& str) const {
	const size_t start = str.find_first_not_of(" \n\r\t\f\v");
	const size_t end = str.find_last_not_of(" \n\r\t\f\v");

	if (start == std::string::npos || end == std::string::npos)
		str = "";
	else
		str = str.substr(start, end - start + 1);
}

std::string UI::readCommand() const {
	std::string menu = "Alege o optiune:\na - Adauga un medicament\nm - Modifica un medicament\nd - Sterge un medicament\nl - Cauta un medicament\nf - Filtreaza medicamente\ns - Sorteaza medicamente\nr - Creare reteta\nra - Genereaza raport pe substante active\nu - Undo ultima operatie\ng - Genereaza medicamente\np - Tipareste toate medicamentele\nq - Inchide aplicatia\n";
	std::cout << menu << "> ";

	std::string cmd;
	std::getline(std::cin, cmd);
	trim(cmd);

	return cmd;
}

void UI::addMedicament() {
	std::cout << "Nume: ";
	std::string name;
	std::getline(std::cin, name);
	trim(name);

	std::cout << "Pret: ";
	std::string priceStr;
	double price;
	std::getline(std::cin, priceStr);
	trim(priceStr);
	try {
		price = std::stod(priceStr);
	}
	catch (std::invalid_argument&) {
		std::cout << "Valoare reala invalida\n";
		return;
	}

	std::cout << "Producator: ";
	std::string manufacturer;
	std::getline(std::cin, manufacturer);
	trim(manufacturer);

	std::cout << "Substanta activa: ";
	std::string activeSubstance;
	std::getline(std::cin, activeSubstance);
	trim(activeSubstance);

	srv.addMedicament(name, price, manufacturer, activeSubstance);

	std::cout << "Medicamentul a fost adaugat\n";
}

void UI::modifyMedicament() {
	std::cout << "Nume: ";
	std::string name;
	std::getline(std::cin, name);
	trim(name);

	std::cout << "Pret nou: ";
	std::string priceStr;
	double price;
	std::getline(std::cin, priceStr);
	trim(priceStr);
	try {
		price = std::stod(priceStr);
	}
	catch (std::invalid_argument&) {
		std::cout << "Valoare reala invalida\n";
		return;
	}

	std::cout << "Producator nou: ";
	std::string manufacturer;
	std::getline(std::cin, manufacturer);
	trim(manufacturer);

	std::cout << "Substanta activa noua: ";
	std::string activeSubstance;
	std::getline(std::cin, activeSubstance);
	trim(activeSubstance);

	srv.modifyMedicament(name, price, manufacturer, activeSubstance);

	std::cout << "Medicamentul a fost modificat\n";
}

void UI::removeMedicament() {
	std::cout << "Nume: ";
	std::string name;
	std::getline(std::cin, name);
	trim(name);

	srv.removeMedicament(name);

	std::cout << "Medicamentul a fost sters\n";
}

void UI::findMedicament() {
	std::cout << "Nume: ";
	std::string name;
	std::getline(std::cin, name);
	trim(name);

	const Medicament& med = srv.findMedicament(name);

	std::cout << "Medicamentul gasit:\n";
	std::cout << med.getName() << " " << med.getPrice() << " " << med.getManufacturer() << " " << med.getActiveSubstance() << std::endl;
}

void UI::generateMedicaments() {
	srv.generateMedicaments();
	std::cout << "Medicamentele au fost generate\n";
}

void UI::filterMedicaments() {
	std::cout << "Submeniu filtrare:\np - Dupa pret\ns - Dupa substanta activa\n";
	std::cout << "> ";

	std::string cmd;
	std::getline(std::cin, cmd);
	trim(cmd);

	if (cmd == "p") {
		std::cout << "Pret maxim: ";
		std::string priceStr;
		double price;
		std::getline(std::cin, priceStr);
		trim(priceStr);
		try {
			price = std::stod(priceStr);
		}
		catch (std::invalid_argument&) {
			std::cout << "Valoare reala invalida\n";
			return;
		}

		auto v = srv.filterByPrice(price);
		printMedicamentsVector(v);
	}
	else if (cmd == "s") {
		std::cout << "Substanta activa: ";
		std::string activeSubstance;
		std::getline(std::cin, activeSubstance);
		trim(activeSubstance);

		auto v = srv.filterByActiveSubstance(activeSubstance);
		printMedicamentsVector(v);
	}
	else {
		std::cout << "Optiune invalida\n";
	}
}

void UI::sortMedicaments() {
	std::cout << "Submeniu sortare:\nn - Dupa denumire\np - Dupa producator\nsp - Dupa substanta activa si pret\n";
	std::cout << "> ";

	std::string cmd;
	std::getline(std::cin, cmd);
	trim(cmd);

	if (cmd == "n") {
		auto v = srv.sortByName();
		printMedicamentsVector(v);
	}
	else if (cmd == "p") {
		auto v = srv.sortByManufacturer();
		printMedicamentsVector(v);
	}
	else if (cmd == "sp") {
		auto v = srv.sortByActiveSubstancePrice();
		printMedicamentsVector(v);
	}
	else {
		std::cout << "Optiune invalida\n";
	}
}

void UI::prescriptionSubmenu(){
	while (true) {
		std::cout << "Submeniu reteta:\na - Adauga medicament pe reteta\nc - Goleste reteta\ng - Genereaza reteta\ne - Exporta reteta\np - Afiseaza continutul retetei\nb - Inchide submeniu\n";
		std::cout << "Numar total de medicamente din reteta: " << srv.getAllMedicamentsFromPrescription().size() << "\n";
		std::cout << "> ";

		std::string cmd;
		std::getline(std::cin, cmd);
		trim(cmd);

		if (cmd == "a") {
			std::cout << "Nume: ";
			std::string name;
			std::getline(std::cin, name);
			try {
				srv.addMedicamentToPrescription(name);
			}
			catch (const RepoException& re) {
				std::cout << re.getMessage();
				continue;
			}
			std::cout << "Medicamentul a fost adaugat\n";
		}
		else if (cmd == "c") {
			srv.clearPrescription();
			std::cout << "Reteta a fost golita\n";
		}
		else if (cmd == "g") {
			std::cout << "Numar medicamente: ";
			int count;
			std::string countString;
			std::getline(std::cin, countString);

			try {
				count = std::stoi(countString);
			}
			catch (std::invalid_argument&) {
				std::cout << "Valoare intreaga invalida\n";
				continue;
			}

			srv.generateRandomPrescription(count);
			std::cout << "Reteta a fost generata\n";
		}
		else if (cmd == "e") {
			std::cout << "Nume fisier: ";
			std::string filename;
			getline(std::cin, filename);

			srv.exportPrescriptionToCSV(filename);
			std::cout << "Export-ul s-a realizat cu succes\n";
		}
		else if (cmd == "p") {
			printMedicamentsVector(srv.getAllMedicamentsFromPrescription());
		}
		else if (cmd == "b") {
			break;
		}
		else {
			std::cout << "Comanda invalida\n";
		}
	}
}

void UI::generateReport() {
	std::map<std::string, int> report = srv.generateReportOnActiveSubstance();

	if (report.size() == 0) {
		std::cout << "Raport vid\n";
		return;
	}

	for (const auto& pair : report) {
		std::cout << pair.first << ": " << pair.second << std::endl;
	}
}

void UI::printAllMedicaments() const {
	auto& v = srv.getAllMedicaments();

	printMedicamentsVector(v);
}

void UI::printMedicamentsVector(const std::vector<Medicament>& meds) const {
	if (meds.size() == 0) {
		std::cout << "Lista de medicamente vida\n";
		return;
	}

	std::cout << "Lista de medicamente: " << std::endl;
	for (const auto& med : meds) {
		std::cout << med.getName() << " " << med.getPrice() << " " << med.getManufacturer() << " " << med.getActiveSubstance() << std::endl;
	}
	std::cout << std::endl;
}

void UI::undoOperation() {
	try {
		srv.undo();
		std::cout << "Undo-ul s-a realizat cu succes\n";
	}
	catch (const UndoException& ue) {
		std::cout << ue.getMessage();
	}
}

void UI::run() {
	while (true) {
		std::string cmd = readCommand();

		try {
			if (cmd == "a") {
				addMedicament();
			}
			else if (cmd == "m") {
				modifyMedicament();
			}
			else if (cmd == "d") {
				removeMedicament();
			}
			else if (cmd == "l") {
				findMedicament();
			}
			else if (cmd == "f") {
				filterMedicaments();
			}
			else if (cmd == "s") {
				sortMedicaments();
			}
			else if (cmd == "r") {
				prescriptionSubmenu();
			}
			else if (cmd == "ra") {
				generateReport();
			}
			else if (cmd == "u") {
				undoOperation();
			}
			else if (cmd == "g") {
				generateMedicaments();
			}
			else if (cmd == "p") {
				printAllMedicaments();
			}
			else if (cmd == "q") {
				break;
			}
			else {
				std::cout << "Comanda invalida\n";
			}
		}
		catch (const RepoException& re) {
			std::cout << re.getMessage();
		}
		catch (const ValidationException& ve) {
			std::cout << ve.getMessage();
		}
	}
}
