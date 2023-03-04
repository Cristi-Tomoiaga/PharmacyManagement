#include <cassert>
#include <cmath>
#include "Medicament.h"

std::string Medicament::getName() const {
	return this->name;
}

double Medicament::getPrice() const noexcept {
	return this->price;
}

std::string Medicament::getManufacturer() const {
	return this->manufacturer;
}

std::string Medicament::getActiveSubstance() const {
	return this->activeSubstance;
}

void testCreateGetMedicament() {
	Medicament m{ "Paracetamol Sinus", 100.5, "ABC", "Paracetamol" };
	assert(m.getName() == "Paracetamol Sinus");
	assert(fabs(m.getPrice() - 100.5) < 1e-5);
	assert(m.getManufacturer() == "ABC");
	assert(m.getActiveSubstance() == "Paracetamol");
}
