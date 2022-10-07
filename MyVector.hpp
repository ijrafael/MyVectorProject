#include <assert.h>
#include <iostream>
#include <string>
#include <algorithm>


//Questions
//
template <typename T>
class MyVector
{
	public:

		/*******************
		 * Static constants
		 ******************/

		/// Default capacity
		static constexpr size_t DEFAULT_CAPACITY = 64;

		/// Minimum capacity
		static constexpr size_t MINIMUM_CAPACITY = 8;

		/*****************************
		 * Constructors / Destructors
		 ****************************/

		/// Normal constructor
		MyVector(size_t capacity = MyVector::DEFAULT_CAPACITY) {

			capacity_ = capacity;			//setting private capacity_ to the new capacity
			elements_ = new T[capacity]; 	// array of elements
		}

		/// Copy constructor
		MyVector(const MyVector& other) {
			size_ = other.size_;  //set members to that of other class
			capacity_ = other.capacity_;
			elements_ = new T[other.capacity_];

			//create loop to set each elmenet inside array to copy of another class
			// stop once i = end of loop, or less then other class's size
			for(size_t i = 0; i < other.size_; i++)
				{
					elements_[i] = other.elements_[i];
				}
		}

		/**
		 * Destructor
		 * Should call clear() so each element gets its destructor called.
		 * Then, deallocate the internal array and make it a nullptr, if its not already a nullptr.
		 */
		~MyVector() {
		}

		/************
		 * Operators
		 ************/

		///	Assignment operator
		MyVector& operator=(const MyVector& rhs) {
		// TODO: Your code here
		if( this != &rhs )	{
    	std::copy( rhs.elements_, rhs.elements_ + rhs.size_, elements_ );
    	size_ = rhs.size_;
  			}
			return *this;
		}

		/// Operator overload to at()
		T& operator[](size_t index) const {

			// TODO: Your code here
			/*if ( index > size_ || index < 0) {
				throw std::range_error ("Out of bounds");
			}*/
  			return at(index);
		}

		/************
		 * Accessors
		 ************/

		/// Return the number of valid elements in our data
		size_t size() const {
			return size_;
		}

		/// Return the capacity of our internal array
		size_t capacity() const {

			return capacity_;
		}

		/**
		 * Check whether our vector is empty
		 * Return true if we have zero elements in our array (regardless of capacity)
		 * Otherwise, return false
		 */
		bool empty() const {

			if ( size() == 0) {
				return true;
			}
			else {
				return false;
			}
		}

		/// Return a reference to the element at an index
		T& at(size_t index) const {

			//might still have some errors
			//the index is bigger than size_ however it is still pulls an element, and does not throw std::range_error
			if ( index < 0  || index > size_) {
				throw std::range_error ("Index out of bounds");
			}
			return elements_[index];
		}

		/***********
		 * Mutators
		 ***********/

		/**
		 * Reserve capacity in advance, if our capacity isn't currently large enough.
		 * Useful if we know we're about to add a large number of elements, and we'd like to avoid the overhead of many internal changes to capacity.
		 */
		void reserve(size_t capacity) {
			if(capacity > capacity_){
                capacity_ = capacity;
            }
			// TODO: Your code here
		}

		/**
		 * Set an element at an index.
		 * Throws range error if outside the size boundary.
		 * Returns a reference to the newly set element (not the original)
		 */
		T& set(size_t index, const T& element) {
			if(index > size_){
				throw std::range_error("Out of range");
			}
			if(index < 0){
				throw std::range_error("Out of range");
			}
			return at(index);

		}

		/**
		 * Add an element onto the end of our vector, increasing the size by 1
		 * Should rely on the insert() function to avoid repeating code.
		 * Returns a reference to the newly inserted element
		 */
		T& push_back(const T& element) {
			return insert( size_ , element);
		}

		/**
		 * Remove the last element in our vector, decreasing the size by 1
		 * Should rely on the erase() function to avoid repeating code.
		 * Returns the new size.
		 */
		size_t pop_back() {
			// TODO: Your code here
			erase(size_ - 1);
			--size_;
			return size_;
		}

		/**
		 * Insert an element at some index in our vector, increasing the size by 1
		 * Returns a reference to the newly added element (not the original).
		 */
		T& insert(size_t index, const T& element) {
			if(index > size_){
				throw std::range_error ("Index is out of bounds");
			}
			increaseSize();
			std::move_backward( elements_+ index, elements_ + size_, elements_ + size_ + 1);
			elements_[ index ] = element;
			return elements_[index];
		}

		/**
		 * Erase one element in our vector at the specified index, decreasing the size by 1
		 * Throws std::range_error if the index is out of bounds.
		 * Calls the erased element's destructor.
		 * Returns the new size.
		 */
		size_t erase(size_t index) {

			// TODO: Your code here
			if( index >= size() ) {
				throw std::range_error( "index is out of bounds" ); 
			}																					// shift elements to the left and decrement the number of elements in the container
 			std::move( elements_ + index + 1, elements_ + size_, elements_ + index );        	
  			--size_;
			return size_;

  return index;
		}

		/**
		 * Calls each element's destructor, then clears our internal
		 * data by setting size to zero and resetting the capacity.
		*/
		void clear() {
			while( size_ != 0 ) elements_[--size_].~T();
			//changeCapacity(DEFAULT_CAPACITY);
			//size_ = 0;
			//capacity_ = DEFAULT_CAPACITY;
		}

	/**
	 * Begin private members and methods.
	 * Private methods can often contain useful helper functions,
	 * or functions to reduce repeated code.
	*/
	private:

		/// Number of valid elements currently in our vector
		size_t size_ = 0;

		/// Capacity of our vector; The actual size of our internal array
		size_t capacity_ = 0;

		/**
		 * Our internal array of elements of type T.
		 * Starts off as a null pointer.
		 */
		T* elements_ = nullptr;

		/**
		 * Increases the size of our vector by 1 element.
		 * If more capacity is needed, it is doubled.
		 */
		void increaseSize() {
			size_ ++;
			if (size_ > capacity_) {
				changeCapacity(capacity_ * 2);
			}
		}

		/**
		 * Decreases the size of our vector by 1 element.
		 * If our size is less than a third of our capacity, cuts our capacity in half.
		 * Capacity should always be at least MyVector::MINIMUM_CAPACITY
		 */
		void decreaseSize() {
			if(size_ < (capacity_ / 3))
				{
					capacity_ = capacity_ /2;
				}
			else if(capacity_ < MINIMUM_CAPACITY)
				{
					reserve(MINIMUM_CAPACITY);
				}
			// TODO: Your code here
			size_--;
		}

		/**
		 * Helper function that is called whenever we need to change the capacity of our vector
		 * Should throw std::range_error when asked to change to a capacity that cannot hold our existing elements.
		 */
		void changeCapacity(size_t c) {

			capacity_ = c;
			T* temp = new T[c];
			for(int i = 0;i < c;i++){
				temp[i] = elements_[i];
			}
			delete [] elements_;
			elements_ = temp;
		}

		/**
		 * Copy another vector's elements into our own, by value.
		 * Does not simply copy the other vector's array's pointer
		 * Does not care about matching the capacity exactly.
		 * This is a helper function relied upon by the copy constuctor and the assignment operator
		 */
		void copyOther(const MyVector& other) {
			MyVector newvector = other;
			// TODO: Your code here

		}

		/**
		 * Receives a pointer to an array of elements, and their size.
		 * Throw an std::range_error if we don't already have enough capacity.
		 * Then, create a new temporary array, and copy each element by value.
		 * Next, delete our internal array if it wasn't a null pointer.
		 * Next, assign the new temporary array pointer to our internal array pointer.
		 * Finally, change our size attribute to match.
		 */
		void copyElements(T* pElements, size_t size) {
			//size_ = size;
			// TODO: Your code here
		}

		//
		void assertCapacity(size_t c) const {
			//capacity_ = c;
			// TODO: Your code here
		}

		//
		void assertBounds(size_t index, std::string message = "") const {

			// TODO: Your code here
		}
};