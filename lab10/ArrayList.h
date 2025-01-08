#ifndef ARRAYLIST_H
#define ARRAYLIST_H
/*
 * A generic array list/sequence/dynamic array/vector
 *
 * This code uses the C++11 function to_string() to convert
 * integers to strings.  MUST be compiled with C++11.
 *
 * Mark A. Sheldon, Tufts University
 * Spring 2015
 *
 * Change Log
 *      2016-03-19 [MAS] Used to_string() to throw an exception to
 *                       throw exception with helpful message
 *      2016-11-04 [MAS] Adapted for template lab:
 *                       Renamed class to ArrayList
 *                       Removed separate destroy()
 *                       Moved ensure_in_range() into class
 *                       Used STL max() algorithm
 *
 */

template<typename ElemType>
class ArrayList {
public:
        ArrayList(int initialCapacity);
        ArrayList();
        ~ArrayList();
        ArrayList(const ArrayList &old);
        ArrayList(ArrayList &&old);
        ArrayList &operator=(const ArrayList &rhs);
        ArrayList &operator=(ArrayList &&rhs);

        void         addAtBack(ElemType new_val);
        ElemType     get(int index);
        void         set(int index, ElemType new_val);
        ElemType    &operator[] (const int index);
        void         removeFromBack();
        int          size();

private:
        int       current_capacity, current_size;
        ElemType *data;

        void ensure_capacity(int desired_capacity);
        void ensure_in_range(int i, int lo, int hi);
        void copy_array(ElemType from[], ElemType to[], int length);
};

#include <stdexcept>
#include <string>
#include <algorithm>

/*
 * Initialize an empty sequence of given initial capacity.
 */
template<typename ElemType>
ArrayList<ElemType>::ArrayList(int initialCapacity)
{
    initialCapacity = 0;
    current_capacity = 0;
    current_size = 0;
    data = NULL;

        // TODO:  Student fills this in (and deletes this comment)
}

/*
 * Initialize an empty sequence of 0 capacity.
 */
template<typename ElemType>
ArrayList<ElemType>::ArrayList()
{
        current_capacity = 0;
        current_size     = 0;
        data             = NULL;
}

/*
 * Sets size and capacity to -1 to identify deleted sequences
 * when debugging.
 */
template<typename ElemType>
ArrayList<ElemType>::~ArrayList()
{
        current_size = current_capacity = -1;
        delete [] data;
        data = NULL;
}

/*
 * Copy constructor
 */
template<typename ElemType>
ArrayList<ElemType>::ArrayList(const ArrayList &old)
{
        current_capacity = old.current_capacity;
        current_size     = old.current_size;
        data             = new ElemType[current_capacity];

        copy_array(old.data, data, current_size);
}

/*
 * Copy move constructor
 */
template<typename ElemType>
ArrayList<ElemType>::ArrayList(ArrayList &&old)
{
        current_capacity = old.current_capacity;
        current_size     = old.current_capacity;
        data             = old.data;

        old.current_capacity = old.current_size = 0;
        old.data = NULL;
}

/*
 * Assignment operator
 */
template<typename ElemType>
ArrayList<ElemType> &ArrayList<ElemType>::operator=(const ArrayList &rhs)
{
        if (this == &rhs)
                return *this;          /* Ignore self assignment */

        current_capacity = rhs.current_capacity;
        current_size     = rhs.current_size;

        delete [] data;
        data = new ElemType[current_capacity];
        copy_array(rhs.data, data, current_size);

        return *this;
}

/*
 * Assignment move operator
 */
template<typename ElemType>
ArrayList<ElemType> &ArrayList<ElemType>::operator=(ArrayList &&rhs)
{
        if (this == &rhs)
                return *this;          /* Ignore self assignment */

        delete [] data;

        current_capacity = rhs.current_capacity;
        current_size     = rhs.current_size;
        data             = rhs.data;

        rhs.current_capacity = rhs.current_size = 0;
        rhs.data = NULL;

        return *this;
}


template<typename ElemType>
int ArrayList<ElemType>::size()
{
        return current_size;
}

/*
 * Subscript operator overload.
 * Returns reference to index-th slot in sequenceso client can
 * update entry.
 *
 * Note:
 *      Client should not save pointer or reference, because it will
 *      become stale when array changes capacity.
 */
template<typename ElemType>
ElemType &ArrayList<ElemType>::operator[] (const int index)
{
        ensure_in_range(index, 0, current_size);
        return data[index];
}

/*
 * Returns the index-th value in the vector.
 */
template<typename ElemType>
ElemType ArrayList<ElemType>::get(int index)
{
    return data[index];
}

/*
 * Sets the index-th position of the vector to contain the new value.
 * Precondition:  There must be an index-th position.
 *
 * Notes:       * The sequence will not be grown to accommodate out of
 *                bounds indices.
 *              * If ElemType is a struct or class, it must have an
 *                assignment operator.
 */
template<typename ElemType>
void ArrayList<ElemType>::set(int index, ElemType new_val)
{
        (*this)[index] = new_val;
}

/*
 * Add the new value as the last element of the sequence.
 * The vector's size increases by one.
 */
template<typename ElemType>
void ArrayList<ElemType>::addAtBack(ElemType new_val)
{
    if (current_size == current_capacity) {
        if (current_capacity == 0) {
          current_capacity += 1;
        } else {
          current_capacity *= 2;
        }
        ElemType *new_data = new ElemType[current_capacity];
    	for (int i = 0; i < current_size; i++) {
    		new_data[i] = data[i];
    	}
    	delete [] data;
    	data = new_data;
    	new_data = NULL;
  	}
  	data[current_size] = new_val;
  	current_size++;
}

/*
 * Remove the last element of the sequence.
 */
template<typename ElemType>
void ArrayList<ElemType>::removeFromBack()
{
    current_size--;
    if (current_size == (current_capacity/2)) {
        current_capacity = current_capacity/2;
        ElemType *new_data = new ElemType[current_size];
    	for (int i = 0; i < current_size; i++) {
    		new_data[i] = data[i];
    	}
    	delete [] data;
    	data = new_data;
    	new_data = NULL;
	}
}

/*
 * Guarantees there are at least desired_capacity slots in the sequence
 */
template<typename ElemType>
void ArrayList<ElemType>::ensure_capacity(int desired_capacity)
{

    ElemType *new_data = new ElemType[desired_capacity];
	for(int i = 0; i < current_size; i++) {
		new_data[i] = data[i];
	}
	delete [] data;
	data = new_data;
	new_data = NULL;
	current_capacity = desired_capacity;
        // TODO:  Student fills this in (and deletes this comment)
        // Note:  copy_array() function below might be handy
}

template<typename ElemType>
void ArrayList<ElemType>::copy_array(ElemType from[], ElemType to[], int length)
{
        for (int i = 0; i < length; ++i)
                to[i] = from[i];
}

/*
 * Guarantees that i is in [0, ..., hi)
 * Throws range_error exceiption if i is out of range
 */
template<typename ElemType>
void ArrayList<ElemType>::ensure_in_range(int i, int lo, int hi)
{
        if ((i < lo) || (i >= hi)) {
                throw std::range_error(std::to_string(i) + " not in ["
                                       + std::to_string(lo) + ", "
                                       + std::to_string(hi) + ")");
        }
}

#endif
