#pragma once
#include <vector>
#include "Medicament.h"
#include "ObserverPattern.h"

/*
* Models a Prescription from the domain
* medicaments - a list of the medicaments contained
*/
class Prescription: public Observable {
private:
	std::vector<Medicament> medicaments;
public:
	/*
	* Default constrcuctor
	*/
	Prescription() = default;

	/*
	* Adds a Medicament object to the Prescription
	* 
	* @param med: Medicament
	*/
	void addMedicament(const Medicament& med);

	/*
	* Clears the Prescription
	*/
	void clear() noexcept;

	/*
	* Populates the Prescription with count random Medicaments from the given list
	* 
	* @param medicamentList: a list of medicaments
	* @param count: int
	*/
	void generateRandom(std::vector<Medicament> medicamentList, int count);

	/*
	* Exports the Prescription as a CSV file with the given file name
	* 
	* @param filename: string
	*/
	void exportCSV(const std::string& filename) const;

	/*
	* Getter for medicaments
	* 
	* @returns: a list of Medicaments
	*/
	const std::vector<Medicament>& getMedicaments() const noexcept;
};

void testAddClearGetPrescription();
void testGeneratePrescription();
void testExportCSVPrescription();