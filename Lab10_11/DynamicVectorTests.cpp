#include <stdexcept>
#include <cassert>
#include "DynamicVectorTests.h"
#include "DynamicVector.h"

void testDynamicVector() {
	DynamicVector<int> v;
	assert(v.size() == 0);

	v.push_back(5);
	assert(v.size() == 1);
	v.clear();
	assert(v.size() == 0);

	v.push_back(5);
	assert(v.size() == 1);
	v.push_back(3);
	assert(v.size() == 2);
	v.push_back(-5);
	assert(v.size() == 3);
	v.push_back(10);
	assert(v.size() == 4);

	assert(v.at(0) == 5);
	assert(v.at(1) == 3);
	assert(v.at(2) == -5);
	assert(v.at(3) == 10);

	try {
		v.at(-1); assert(false);
	}
	catch (std::out_of_range&) {
		assert(true);
		assert(v.size() == 4);
	}

	try {
		v.at(20); assert(false);
	}
	catch (std::out_of_range&) {
		assert(true);
		assert(v.size() == 4);
	}

	v.set(0, 20);
	assert(v.at(0) == 20);
	assert(v.size() == 4);

	try {
		v.set(20, 2); assert(false);
	}
	catch (std::out_of_range&) {
		assert(true);
		assert(v.size() == 4);
	}

	v.erase(0);
	assert(v.size() == 3);
	assert(v.at(0) == 3);

	v.push_back(30);
	assert(v.size() == 4);
	v.erase(3);
	assert(v.size() == 3);
	assert(v.at(2) == 10);

	v.erase(100);
	assert(v.size() == 3);

	v.clear();
	v.push_back(1);
	v.push_back(2);
	v.push_back(-3);
	v.push_back(5);
	assert(v.size() == 4);

	DynamicVector<int> v2{ v };
	assert(v2.size() == 4);
	for (int i = 0; i < v.size(); i++)
		assert(v2.at(i) == v.at(i));

	v2.push_back(100);
	assert(v2.size() == 5);
	assert(v.size() == 4);

	v2.set(0, -1);
	assert(v2.at(0) == -1);
	assert(v.at(0) == 1);

	v2 = v;
	assert(v2.size() == 4);
	for (int i = 0; i < v.size(); i++)
		assert(v2.at(i) == v.at(i));

	v = v;
	assert(v.size() == 4);
}

void testDynamicVectorIterator() {
	DynamicVector<int> v;
	DynamicVector<int> v2;
	for (int i = 1; i <= 10; i++)
		v.push_back(i);
	assert(v.size() == 10);
	
	DynamicVectorIterator<int> it{ v };
	assert(it.isValid());
	assert(it.element() == 1);
	assert(it == v.begin());
	assert(it != v.end());

	++it;
	assert(it.isValid());
	assert(*it == 2);

	const DynamicVectorIterator<int> it2{ v, 2 };
	assert(it != it2);
	const DynamicVectorIterator<int> it3{ v, 1 };
	assert(it == it3);
	const DynamicVectorIterator<int> it4{ v2, 1 };
	assert(it != it4);

	for (int i = 3; i <= 10; i++) {
		it.next();
		assert(it.isValid());
		assert(it.element() == i);
	}
	it.next();
	assert(!it.isValid());
	assert(it == v.end());
	assert(it != v.begin());

	DynamicVectorIterator<int> iter = v.begin();
	int i = 0;
	while (iter != v.end()) {
		assert(*iter == v.at(i));
		++iter;
		i++;
	}
	
	i = 0;
	for (const auto& val : v) {
		assert(val == v.at(i));
		i++;
	}
}
