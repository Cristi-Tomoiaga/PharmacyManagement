#include <cassert>
#include <cmath>
#include <algorithm>
#include "Repository.h"

std::string RepoException::getMessage() const {
	return this->msg;
}

void testCreateGetRepoExp() {
	RepoException re{ "test" };
	assert(re.getMessage() == "test");
}

size_t Repository::getSize() const noexcept {
	return this->data.size();
}

const std::vector<Medicament> Repository::getAll() const {
	return this->data;
}

bool Repository::exists(const Medicament& med) const {
	try {
		find(med.getName());
		return true;
	}
	catch (RepoException&) {
		return false; }
}

void Repository::add(const Medicament& med) {
	if (exists(med))
		throw RepoException("Medicamentul exista deja\n");

	this->data.push_back(med);
}

void Repository::remove(const Medicament& med) {
	if (!exists(med))
		throw RepoException("Medicament inexistent\n");

	auto it = std::find_if(this->data.begin(), this->data.end(), [=](Medicament m) { return m.getName() == med.getName(); });
	this->data.erase(it);
}

void Repository::modify(const Medicament& med) {
	if (!exists(med))
		throw RepoException("Medicament inexistent\n");

	auto it = std::find_if(this->data.begin(), this->data.end(), [=](Medicament m) { return m.getName() == med.getName(); });
	*it = med;
}

const Medicament& Repository::find(const std::string& name) const {
	auto it = std::find_if(this->data.begin(), this->data.end(), [=](Medicament m) { return m.getName() == name; });

	if(it == this->data.end())
		throw RepoException("Medicament inexistent\n");

	return *it;
}

void Repository::clear() {
	this->data.clear();
}

void testAddSizeGetClearRepo() {
	Repository repo;
	assert(repo.getSize() == 0);
	repo.add(Medicament{ "Nume1", 100, "Prod1", "Subst1" });
	assert(repo.getSize() == 1);
	repo.add(Medicament{ "Nume2", 150, "Prod2", "Subst2" });
	assert(repo.getSize() == 2);

	const std::vector<Medicament> v = repo.getAll();
	assert(v.at(0).getName() == "Nume1");
	assert(fabs(v.at(0).getPrice() - 100) < 1e-5);
	assert(v.at(0).getManufacturer() == "Prod1");
	assert(v.at(0).getActiveSubstance() == "Subst1");

	assert(v.at(1).getName() == "Nume2");
	assert(fabs(v.at(1).getPrice() - 150) < 1e-5);
	assert(v.at(1).getManufacturer() == "Prod2");
	assert(v.at(1).getActiveSubstance() == "Subst2");

	try {
		repo.add(Medicament{ "Nume2", 150, "Prod2", "Subst2" }); assert(false);
	}
	catch (const RepoException& re) {
		assert(true);
		assert(repo.getSize() == 2);
		assert(re.getMessage() == "Medicamentul exista deja\n");
	}

	assert(repo.getSize() == 2);
	repo.clear();
	assert(repo.getSize() == 0);
}

void testModifyRepo() {
	Repository repo;
	assert(repo.getSize() == 0);
	repo.add(Medicament{ "Nume1", 100, "Prod1", "Subst1" });
	assert(repo.getSize() == 1);
	repo.add(Medicament{ "Nume2", 150, "Prod2", "Subst2" });
	assert(repo.getSize() == 2);

	repo.modify(Medicament{ "Nume1", 200, "ABC", "Paracetamol" });
	const Medicament& med = repo.find("Nume1");
	assert(med.getName() == "Nume1");
	assert(fabs(med.getPrice() - 200) < 1e-5);
	assert(med.getManufacturer() == "ABC");
	assert(med.getActiveSubstance() == "Paracetamol");

	try {
		repo.modify(Medicament{ "Nume10", 10, "CDE", "Subst" }); assert(false);
	}
	catch (const RepoException& re) {
		assert(true);
		assert(repo.getSize() == 2);
		assert(re.getMessage() == "Medicament inexistent\n");
	}
}

void testRemoveRepo() {
	Repository repo;
	assert(repo.getSize() == 0);
	repo.add(Medicament{ "Nume1", 100, "Prod1", "Subst1" });
	assert(repo.getSize() == 1);
	repo.add(Medicament{ "Nume2", 150, "Prod2", "Subst2" });
	assert(repo.getSize() == 2);

	repo.remove(Medicament{ "Nume2", 150, "Prod2", "Subst2" });
	assert(repo.getSize() == 1);

	try {
		repo.remove(Medicament{ "Ceva2", 150, "Prod2", "Subst2" }); assert(false);
	}
	catch (const RepoException& re) {
		assert(true);
		assert(repo.getSize() == 1);
		assert(re.getMessage() == "Medicament inexistent\n");
	}

	repo.remove(Medicament{ "Nume1", 100, "Prod1", "Subst1" });
	assert(repo.getSize() == 0);

	try {
		repo.remove(Medicament{ "Ceva2", 150, "Prod2", "Subst2" }); assert(false);
	}
	catch (const RepoException& re) {
		assert(true);
		assert(repo.getSize() == 0);
		assert(re.getMessage() == "Medicament inexistent\n");
	}
}

void testFindExistsRepo() {
	Repository repo;
	assert(repo.getSize() == 0);
	repo.add(Medicament{ "Nume1", 100, "Prod1", "Subst1" });
	assert(repo.getSize() == 1);
	repo.add(Medicament{ "Nume2", 150, "Prod2", "Subst2" });
	assert(repo.getSize() == 2);

	Medicament med1{ "Nume1", 100, "Prod1", "Subst1" };
	Medicament med2{ "alabala", 200, "ceva", "gresit" };
	assert(repo.exists(med1));
	assert(!repo.exists(med2));

	const Medicament& med3 = repo.find("Nume1");
	assert(med3.getName() == "Nume1");
	assert(fabs(med3.getPrice() - 100) < 1e-5);
	assert(med3.getManufacturer() == "Prod1");
	assert(med3.getActiveSubstance() == "Subst1");

	try {
		repo.find("Altceva"); assert(false);
	} catch (const RepoException& re) {
		assert(true);
		assert(re.getMessage() == "Medicament inexistent\n");
	}
}
