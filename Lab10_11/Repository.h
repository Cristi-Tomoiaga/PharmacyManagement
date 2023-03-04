#pragma once
#include <string>
#include <vector>
#include "Medicament.h"

/*
* Exception used in repository
*/
class RepoException {
private:
	std::string msg;
public:
	/*
	* Constructor for RepoException
	* @param message: string
	*/
	RepoException(const std::string message): msg{message}{};

	/*
	* Getter for the message stored in the exception
	* @returns the message - string
	*/
	std::string getMessage() const;
};

/*
* In-Memory repository for Medicament objects
*/
class Repository {
private:
	std::vector<Medicament> data;
public:
	/*
	* Default constructor
	*/
	Repository() = default;

	/*
	* No copy constructor
	*/
	Repository(const Repository&) = delete;

	/*
	* Default destructor
	*/
	virtual ~Repository() = default;

	/*
	* Gets the size of the repository
	* @returns the size - size_t
	*/
	size_t getSize() const noexcept;

	/*
	* Gets all the Medicament objects in the repository
	* @returns the vector of Medicament objects
	*/
	const std::vector<Medicament> getAll() const;

	/*
	* Verifies if a given Medicament exists in the repository
	* @param med: the Medicament
	* @returns: true if found, false otherwise
	*/
	bool exists(const Medicament& med) const;

	/*
	* Adds a new Medicament to the repository
	* @param med: the Medicament
	* @throws RepoException if the given Medicament already exists in the repository
	*/
	virtual void add(const Medicament& med);

	/*
	* Removes a Medicament with the same name as the given Medicament from the repository
	* @param med: the Medicament
	* @throws RepoException if the given Medicament does not exist in the repository
	*/
	virtual void remove(const Medicament& med);

	/*
	* Modifies a Medicament with the same name as the given Medicament, changing the other fields
	* @param med: the Medicament
	* @throws RepoException if the given Medicament does not exist in the repository
	*/
	virtual void modify(const Medicament& med);

	/*
	* Searches for a Medicament by a given name in the repository
	* @param name: string
	* @returns the found medicament
	* @throws RepoException if there is no Medicament with the given name
	*/
	const Medicament& find(const std::string& name) const;

	/*
	* Removes all the Medicament objects from the repository
	*/
	virtual void clear();
};

/*
* Tests for Repository
*/
void testCreateGetRepoExp();
void testAddSizeGetClearRepo();
void testModifyRepo();
void testRemoveRepo();
void testFindExistsRepo();