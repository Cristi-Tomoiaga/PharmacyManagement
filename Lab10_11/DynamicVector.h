#pragma once
#include <stdexcept>

constexpr size_t INITIAL_CAPACITY = 2;

/*
* Forward declaration for the iterator
*/
template<typename ElemT>
class DynamicVectorIterator;

/*
* Generic implementation for a dynamic vector
*/
template<typename ElementT>
class DynamicVector{
private:
	ElementT* elems;
	size_t capacity;
	size_t length;

	/*
	* Resizes the vector 
	*/
	void resize();
public:
	/*
	* Default constructor
	* Creates an empty vector
	*/
	DynamicVector() noexcept;

	/*
	* Copy constructor
	* @param ot: the other vector
	*/
	DynamicVector(const DynamicVector& ot);

	/*
	* Copy assignment operator
	* @param ot: the other vector
	* @returns: a reference to the current object
	*/
	DynamicVector& operator=(const DynamicVector& ot);

	/*
	* Destructor
	*/
	~DynamicVector();

	/*
	* Adds the given element to the end of the vector
	* @param elem: the new element
	*/
	void push_back(const ElementT& elem);

	/*
	* Gets the element at the given position
	* @param pos: the position, 0 <= pos < size()
	* @returns: a reference to the element at the given position
	* @throws std::out_of_range if the position is invalid
	*/
	ElementT& at(int pos) const;

	/*
	* Modifies the element at the given position with elem
	* @param pos: the position, 0 <= pos < size()
	* @param elem: the new element
	* @throws std::out_of_range if the position is invalid
	*/
	void set(int pos, const ElementT& elem);

	/*
	* Removes the element with the given position
	* If the position is invalid, do nothing
	* @param pos: the position, 0 <= pos < size()
	*/
	void erase(int pos) noexcept;

	/*
	* Gets the current length of the vector
	* @returns: the length
	*/
	size_t size() const noexcept;

	/*
	* Removes all elements from the vector
	*/
	void clear() noexcept;


	friend class DynamicVectorIterator<ElementT>;

	/*
	* Constructs an iterator for the first element in the vector
	* @returns: the iterator
	*/
	DynamicVectorIterator<ElementT> begin() const noexcept;

	/*
	* Constructs an iterator for the end of the vector (the first invalid position)
	* @returns: the iterator
	*/
	DynamicVectorIterator<ElementT> end() const noexcept;
};

/*
* Generic implementation for a dynamic vector iterator
*/
template<typename ElemT>
class DynamicVectorIterator {
private:
	const DynamicVector<ElemT>& vector;
	int pos;
public:
	/*
	* Constructor
	* @param vector: reference to the vector
	*/
	DynamicVectorIterator(const DynamicVector<ElemT>& vector) noexcept;

	/*
	* Constructor
	* @param vector: reference to the vector
	* @param pos: initial position for iterator
	*/
	DynamicVectorIterator(const DynamicVector<ElemT>& vector, int pos) noexcept;

	/*
	* Verifies if the iterator is referencing a valid element in the vector
	* @returns true if it is valid, false otherwise
	*/
	bool isValid() const noexcept;

	/*
	* Moves the iterator to the next element
	*/
	void next() noexcept;

	/*
	* Gets the element at the current position, the iterator must be valid
	* @returns: a reference to the element
	*/
	ElemT& element() const noexcept;

	/*
	* Equality operator for two iterators
	* @param ot: the other iterator
	* @returns: true if equal, false otherwise
	*/
	bool operator==(const DynamicVectorIterator& ot) noexcept;

	/*
	* Inequality operator for two iterators
	* @param ot: the other iterator
	* @returns: true if not equal, false otherwise
	*/
	bool operator!=(const DynamicVectorIterator& ot) noexcept;

	/*
	* Dereferencing operator
	* @returns: the element referenced by the iterator
	*/
	ElemT& operator*() noexcept;

	/*
	* Increment operator
	* Moves the iterator to the next element
	* @returns: a reference to the iterator
	*/
	DynamicVectorIterator& operator++() noexcept;
};

template<typename ElementT>
void DynamicVector<ElementT>::resize() {
	const size_t newCapacity = this->capacity * 2;
	ElementT* newElems = new ElementT[newCapacity];

	for (int i = 0; i < this->length; i++)
		newElems[i] = this->elems[i];

	delete[] this->elems;
	this->elems = newElems;
	this->capacity = newCapacity;
}

template<typename ElementT>
DynamicVector<ElementT>::DynamicVector() noexcept {
	this->capacity = INITIAL_CAPACITY;
	this->length = 0;
	this->elems = new ElementT[this->capacity];
}

template<typename ElementT>
DynamicVector<ElementT>::DynamicVector(const DynamicVector& ot) {
	this->capacity = ot.capacity;
	this->length = ot.length;
	this->elems = new ElementT[this->capacity];

	for (int i = 0; i < this->length; i++)
		this->elems[i] = ot.elems[i];
}

template<typename ElementT>
DynamicVector<ElementT>& DynamicVector<ElementT>::operator=(const DynamicVector& ot) {
	if (this == &ot) {
		return *this; // guard against self-assignment
	}

	this->capacity = ot.capacity;
	this->length = ot.length;
	delete[] this->elems;
	this->elems = new ElementT[this->capacity];

	for (int i = 0; i < this->length; i++)
		this->elems[i] = ot.elems[i];

	return *this;
}

template<typename ElementT>
DynamicVector<ElementT>::~DynamicVector() {
	delete[] this->elems;
}

template<typename ElementT>
void DynamicVector<ElementT>::push_back(const ElementT& elem) {
	if (this->length == this->capacity)
		resize();

	this->elems[this->length++] = elem;
}

template<typename ElementT>
ElementT& DynamicVector<ElementT>::at(int pos) const {
	if (pos < 0 || pos >= this->length)
		throw std::out_of_range("invalid position");

	return this->elems[pos];
}

template<typename ElementT>
void DynamicVector<ElementT>::set(int pos, const ElementT& elem) {
	if (pos < 0 || pos >= this->length)
		throw std::out_of_range("invalid position");

	this->elems[pos] = elem;
}

template<typename ElementT>
void DynamicVector<ElementT>::erase(int pos) noexcept {
	if (pos < 0 || pos >= this->length)
		return;

	for (int i = pos; i < this->length - 1; i++)
		this->elems[i] = this->elems[i + 1];
	this->length--;
}

template<typename ElementT>
size_t DynamicVector<ElementT>::size() const noexcept {
	return this->length;
}

template<typename ElementT>
void DynamicVector<ElementT>::clear() noexcept {
	this->length = 0; // logically delete the elements
}

template<typename ElementT>
DynamicVectorIterator<ElementT> DynamicVector<ElementT>::begin() const noexcept {
	return DynamicVectorIterator<ElementT>(*this);
}

template<typename ElementT>
DynamicVectorIterator<ElementT> DynamicVector<ElementT>::end() const noexcept {
	return DynamicVectorIterator<ElementT>(*this, static_cast<int>(this->length));
}


template<typename ElemT>
DynamicVectorIterator<ElemT>::DynamicVectorIterator(const DynamicVector<ElemT>& vector) noexcept: vector{ vector } {
	this->pos = 0;
}

template<typename ElemT>
DynamicVectorIterator<ElemT>::DynamicVectorIterator(const DynamicVector<ElemT>& vector, int pos) noexcept: vector{ vector } {
	this->pos = pos;
}

template<typename ElemT>
bool DynamicVectorIterator<ElemT>::isValid() const noexcept {
	return this->pos < this->vector.length;
}

template<typename ElemT>
void DynamicVectorIterator<ElemT>::next() noexcept {
	this->pos++;
}

template<typename ElemT>
ElemT& DynamicVectorIterator<ElemT>::element() const noexcept {
	return this->vector.elems[this->pos];
}

template<typename ElemT>
bool DynamicVectorIterator<ElemT>::operator==(const DynamicVectorIterator& ot) noexcept {
	return &this->vector == &ot.vector && this->pos == ot.pos;
}

template<typename ElemT>
bool DynamicVectorIterator<ElemT>::operator!=(const DynamicVectorIterator& ot) noexcept {
	return !(*this == ot);
}

template<typename ElemT>
ElemT& DynamicVectorIterator<ElemT>::operator*() noexcept {
	return this->element();
}

template<typename ElemT>
DynamicVectorIterator<ElemT>& DynamicVectorIterator<ElemT>::operator++() noexcept{
	this->next();
	return *this;
}