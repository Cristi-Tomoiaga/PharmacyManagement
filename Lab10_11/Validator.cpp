#include <cassert>
#include "Validator.h"

std::string ValidationException::getMessage() const {
	return this->msg;
}

void MedicamentValidator::validate(const Medicament& med) const {
	std::string msg;
	if (med.getName() == "")
		msg += "Nume invalid\n";
	if (med.getPrice() <= 0)
		msg += "Pret invalid\n";
	if (med.getManufacturer() == "")
		msg += "Producator invalid\n";
	if (med.getActiveSubstance() == "")
		msg += "Substanta activa invalida\n";

	if (msg.length() > 0)
		throw ValidationException(msg);
}

void testCreateGetValidExcp() {
	ValidationException ve{"test"};
	assert(ve.getMessage() == "test");
}

void testValidateMedicament() {
	Medicament medValid{ "Paracetamol Sinus", 49.99, "ABC", "Paracetamol" };
	Medicament medName{ "", 49.99, "ABC", "Paracetamol" };
	Medicament medPrice{ "Paracetamol Sinus", -20, "ABC", "Paracetamol" };
	Medicament medManuf{ "Paracetamol Sinus", 49.99, "", "Paracetamol" };
	Medicament medActiveSub{ "Paracetamol Sinus", 49.99, "ABC", "" };
	Medicament medAll{ "", 0, "", "" };
	MedicamentValidator mv;

	mv.validate(medValid);
	assert(true);

	try {
		mv.validate(medName); assert(false);
	}
	catch (const ValidationException& ve) {
		assert(true);
		assert(ve.getMessage() == "Nume invalid\n");
	}

	try {
		mv.validate(medPrice); assert(false);
	}
	catch (const ValidationException& ve) {
		assert(true);
		assert(ve.getMessage() == "Pret invalid\n");
	}

	try {
		mv.validate(medManuf); assert(false);
	}
	catch (const ValidationException& ve) {
		assert(true);
		assert(ve.getMessage() == "Producator invalid\n");
	}

	try {
		mv.validate(medActiveSub); assert(false);
	}
	catch (const ValidationException& ve) {
		assert(true);
		assert(ve.getMessage() == "Substanta activa invalida\n");
	}

	try {
		mv.validate(medAll); assert(false);
	}
	catch (const ValidationException& ve) {
		assert(true);
		assert(ve.getMessage() == "Nume invalid\nPret invalid\nProducator invalid\nSubstanta activa invalida\n");
	}
}
