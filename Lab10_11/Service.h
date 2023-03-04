#pragma once
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <memory>
#include "Repository.h"
#include "Validator.h"
#include "Medicament.h"
#include "Prescription.h"
#include "UndoActions.h"

/*
* Exception used in the undo method of Service
*/
class UndoException {
private:
	std::string msg;
public:
	/*
	* Constructor for UndoException
	* @param message: string
	*/
	UndoException(const std::string message) : msg{ message } {};

	/*
	* Getter for the message stored in the exception
	* @returns the message - string
	*/
	std::string getMessage() const;
};

/*
* GRASP controller for actions on Medicament objects
*/
class Service {
private:
	Repository& repo;
	MedicamentValidator& medVal;
	Prescription currentPrescription;
	std::vector<std::unique_ptr<UndoAction>> undoList;
public:
	/*
	* Constructor for Service
	* @param repo: Repository
	* @param medVal: MedicamentValidator
	*/
	Service(Repository& repo, MedicamentValidator& medVal) noexcept: repo{ repo }, medVal{ medVal } {}

	/*
	* No copy constructor
	*/
	Service(const Service&) = delete;

	/*
	* Gets all the Medicament objects stored in the underlying repository
	* @returns: the vector of Medicament objects
	*/
	const std::vector<Medicament> getAllMedicaments() const;

	/*
	* Adds a new Medicament object based on the given data
	* @param name: string
	* @param price: double
	* @param manufacturer: string
	* @param activeSubstance: string
	* @throws RepoException if there is already a Medicament with the given name
	*		  ValidationException if the given data is invalid
	*/
	void addMedicament(const std::string& name, const double price, const std::string& manufacturer, const std::string& activeSubstance);

	/*
	* Modifies an existing Medicament object based on the given data (price, manufacturer, activeSubstance)
	* @param name: string
	* @param price: double
	* @param manufacturer: string
	* @param activeSubstance: string
	* @throws RepoException if there isn't a Medicament with the given name
	*		  ValidationException if the given data is invalid
	*/
	void modifyMedicament(const std::string& name, const double price, const std::string& manufacturer, const std::string& activeSubstance);

	/*
	* Removes the Medicament with the given name
	* @param name: string
	* @throws RepoException if there isn't a Medicament with the given name
	*/
	void removeMedicament(const std::string& name);

	/*
	* Finds the Medicament with the given name
	* @param name: string
	* @throws RepoException if there isn't a Medicament with the given name
	*/
	const Medicament& findMedicament(const std::string& name);

	/*
	* Generates test data in the service
	*/
	void generateMedicaments();

	/*
	* Filters the Medicaments by a maximum given price
	* @param price: double
	* @returns: the filtered list of Medicaments
	*/
	std::vector<Medicament> filterByPrice(double price) const;

	/*
	* Filters the Medicaments by a active substance
	* @param activeSubstance: string
	* @returns: the filtered list of Medicaments
	*/
	std::vector<Medicament> filterByActiveSubstance(const std::string& activeSubstance) const;

	/*
	* Sorts the Medicaments by name in ascending order
	* @returns: the sorted list of Medicaments
	*/
	std::vector<Medicament> sortByName() const;

	/*
	* Sorts the Medicaments by a manufacturer in ascending order
	* @returns: the sorted list of Medicaments
	*/
	std::vector<Medicament> sortByManufacturer() const;

	/*
	* Sorts the Medicaments by active substance and price in ascending order
	* @returns: the sorted list of Medicaments
	*/
	std::vector<Medicament> sortByActiveSubstancePrice() const;

	/*
	* Adds the Medicament identified by the given name to the current Prescription
	* @param name: string
	* @throws RepoException if there isn't a Medicament with the given name
	*/
	void addMedicamentToPrescription(const std::string& name);

	/*
	* Clears the current Prescription
	*/
	void clearPrescription() noexcept;

	/*
	* Generates a random Prescription using count Medicaments from the service
	* @param count: int
	*/
	void generateRandomPrescription(int count);

	/*
	* Exports the current Prescription to a CSV file named filename
	* @param filename: string
	*/
	void exportPrescriptionToCSV(const std::string& filename) const;

	/*
	* Gets all the Medicaments stored in the current Prescription
	* @returns: the list of Medicaments
	*/
	const std::vector<Medicament>& getAllMedicamentsFromPrescription() const noexcept;

	/*
	* Generates a report on active substances 
	* @returns: a map of (active substance, count) pairs
	*/
	std::map<std::string, int> generateReportOnActiveSubstance() const;

	/*
	* Undoes the last operation
	* @throws UndoException if there are no operations left to undo
	*/
	void undo();

	/*
	* Getter for the associated Prescription
	* @returns Prescription
	*/
	Prescription& getPrescription();
};

/*
* Tests for Service
*/
void testAddGetService();
void testModifyService();
void testRemoveService();
void testFindService();
void testGenerateService();
void testFilterService();
void testSortService();
void testPrescription();
void testReportService();
void testUndoService();