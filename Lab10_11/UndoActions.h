#pragma once
#include "Repository.h"
/*
* Abstract class that models an UndoAction
*/
class UndoAction {
public:
	/*
	* Undoes the represented operation (virtual method)
	*/
	virtual void doUndo() = 0;

	/*
	* Default constructor
	*/
	virtual ~UndoAction() = default;
};

/*
* UndoAction for add
*/
class UndoAdd : public UndoAction {
private:
	Repository& repo;
	Medicament med;
public:
	/*
	* Constructor for UndoAdd
	* @param repo: the repository
	* @param med: the added Medicament
	*/
	UndoAdd(Repository& repo, const Medicament& med) : repo{ repo }, med{ med } {}

	/*
	* Undoes the add operation
	*/
	void doUndo() override {
		repo.remove(med);
	}
};

/*
* UndoAction for modify
*/
class UndoModify : public UndoAction {
private:
	Repository& repo;
	Medicament med;
public:
	/*
	* Constructor for UndoModify
	* @param repo: the repository
	* @param med: the initial unmodified Medicament
	*/
	UndoModify(Repository& repo, const Medicament& med) : repo{ repo }, med{ med } {}

	/*
	* Undoes the add operation
	*/
	void doUndo() override {
		repo.modify(med);
	}
};

/*
* UndoAction for remove
*/
class UndoRemove : public UndoAction {
private:
	Repository& repo;
	Medicament med;
public:
	/*
	* Constructor for UndoRemove
	* @param repo: the repository
	* @param med: the removed Medicament
	*/
	UndoRemove(Repository& repo, const Medicament& med) : repo{ repo }, med{ med } {}

	/*
	* Undoes the remove operation
	*/
	void doUndo() override {
		repo.add(med);
	}
};
