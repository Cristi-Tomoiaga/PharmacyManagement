#pragma once
#include <string>
#include "Medicament.h"

/*
* Exception used in validation
*/
class ValidationException {
private:
	std::string msg;
public:
	/*
	* Constructor for ValidationException
	* @param message: string
	*/
	ValidationException(const std::string message) : msg{ message } {};

	/*
	* Getter for the message stored in the exception
	* @returns the message - string
	*/
	std::string getMessage() const;
};

/*
* A class for validating a Medicament
*/
class MedicamentValidator {
public:	
	/*
	* Default constructor
	*/
	MedicamentValidator() = default;

	/*
	* No copy constructor
	*/
	MedicamentValidator(const MedicamentValidator&) = delete;

	/*
	* Validates a Medicament
	* @param med: Medicament object
	* @throws ValidationException if
	*		name is empty
	*		price is less than or equal to 0
	*		manufacturer is empty
	*		activeSubstance is empty
	*/
	void validate(const Medicament& med) const;
};

/*
* Tests for Validator
*/
void testCreateGetValidExcp();
void testValidateMedicament();