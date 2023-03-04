#pragma once
#include "Repository.h"

/*
* File repository for Medicament objects
*/
class FileRepository : public Repository {
private:
	std::string fileName;

	/*
	* Loads the entities from the specified file
	* @throws RepoException if the file could not be opened
	*/
	void loadFromFile();

	/*
	* Saves the entities to the file
	* @throws RepoException if the file could not be opened
	*/
	void saveToFile();
public:
	/*
	* Constructor for FileRepository
	* @param fileName: path to the file containing the Medicaments
	* @throws RepoException if the file could not be opened
	*/
	FileRepository(std::string fileName) : Repository{}, fileName { fileName } {
		this->loadFromFile();
	}

	/*
	* Default destructor
	*/
	~FileRepository() = default;

	/*
	* Adds a new Medicament to the repository
	* @param med: the Medicament
	* @throws RepoException if the given Medicament already exists in the repository
	*/
	void add(const Medicament& med) override;

	/*
	* Removes a Medicament with the same name as the given Medicament from the repository
	* @param med: the Medicament
	* @throws RepoException if the given Medicament does not exist in the repository
	*/
	void remove(const Medicament& med) override;

	/*
	* Modifies a Medicament with the same name as the given Medicament, changing the other fields
	* @param med: the Medicament
	* @throws RepoException if the given Medicament does not exist in the repository
	*/
	void modify(const Medicament& med) override;

	/*
	* Removes all the Medicament objects from the repository
	*/
	void clear() override;
};

void testOperationsFileRepo();

