#pragma once
#include <string>
#include <iostream>

/*
* Models a Medicament from the domain
* name - string
* price - double
* manufacturer - string
* active substance - string
*/
class Medicament {
private:
	std::string name;
	double price;
	std::string manufacturer;
	std::string activeSubstance;
public:
	/*
	* Default constructor
	*/
	Medicament() = default;

	/*
	* Copy constructor
	* @param ot: Medicament
	*/
	//Medicament(const Medicament& ot) : name{ ot.name }, price{ ot.price }, manufacturer{ ot.manufacturer }, activeSubstance{ ot.activeSubstance } {
	//	std::cout << "COPIERE\n";
	//}

	/*
	* Constructor for Medicament
	* @param name: string
	* @param price: double
	* @param manufacturer: string
	* @param activeSubstance: string
	*/
	Medicament(std::string name, double price, std::string manufacturer, std::string activeSubstance) 
		: name{ name }, price{ price }, manufacturer{ manufacturer }, activeSubstance{ activeSubstance } {};

	/*
	* Getter for name
	* @returns the name - string
	*/
	std::string getName() const;

	/*
	* Getter for price
	* @returns the price - double
	*/
	double getPrice() const noexcept;

	/*
	* Getter for manufacturer
	* @returns the manufacturer - string
	*/
	std::string getManufacturer() const;

	/*
	* Getter for active substance
	* @returns the active substance - string
	*/
	std::string getActiveSubstance() const;
};

/*
* Tests for Medicament
*/
void testCreateGetMedicament();