#pragma once
#include <string>
#include "Service.h"

/*
* Console-based user interface
*/
class UI {
private:
	Service& srv;

	/*
	* Trims whitespaces from a string
	*/
	void trim(std::string& str) const;

	/*
	* Prints the menu and reads a command from the user
	* @returns the command - string
	*/
	std::string readCommand() const;

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
	* Finds an existing Medicament by a given name from the application
	*/
	void findMedicament();

	/*
	* Generates test data for Medicaments
	*/
	void generateMedicaments();

	/*
	* Filters the Medicaments in the application
	*/
	void filterMedicaments();

	/*
	* Sorts the Medicaments in the application
	*/
	void sortMedicaments();

	/*
	* Handles the prescription feature in the UI
	*/
	void prescriptionSubmenu();

	/*
	* Generates a report for the Medicaments
	*/
	void generateReport();

	/*
	* Prints all the stored Medicament objects from the application
	*/
	void printAllMedicaments() const;

	/*
	* Helper function for printing a Medicament object vector
	* @param meds: the vector
	*/
	void printMedicamentsVector(const std::vector<Medicament>& meds) const;

	/*
	* Undoes the last operation
	*/
	void undoOperation();
public:
	/*
	* Constructor for UI
	* @param srv: Service
	*/
	UI(Service& srv) noexcept: srv{ srv } {}

	/*
	* No copy constructor
	*/
	UI(const UI&) = delete;

	/*
	* Starts the console UI
	*/
	void run();
};

