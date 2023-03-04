#pragma once
#include <vector>
#include <algorithm>

/*
* Abstract class that every Concrete Observer must inherit from
*/
class Observer {
public:
	/*
	* Called when the observable object changes its state
	* The Concrete Observer must implement this method
	*/
	virtual void update() = 0;
};

/*
* Every Concrete Subject must inherit from this class 
* and notify interested observers about state changes
*/
class Observable {
private:
	std::vector<Observer*> observers;

protected:
	/*
	* Notifies the registered observers about a state change
	*/
	void notify() {
		for (auto observer : this->observers) {
			observer->update();
		}
	}

public:
	/*
	* Registers a new Observer to the list
	* @param obs: Observer*
	*/
	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}

	/*
	* Unregisters an already existing Observer from the list
	* @param obs: Observer*
	*/
	void removeObserver(Observer* obs) {
		observers.erase(std::find(observers.begin(), observers.end(), obs));
	}
};