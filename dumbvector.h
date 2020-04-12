#ifndef DUMB_VECTOR_H
#define DUMB_VECTOR_H

/* dumb::vector

"I'm not allowed to use std::vector!" the student lamented on stackoverflow.

The commenters rolled their collective eyes.
 */

#include <initializer_list>

namespace dumb {

    class vector
    {
    private:
        // using something different than int? Change it here!
        typedef int value_type;

        value_type* data_;
        unsigned int size_;
        unsigned int capacity_;

    public:
        /* YOU MUST KEEP AT LEAST ONE OF THE FOLLOWING FOUR CONSTRUCTORS */
        // This one lets you make an empty vector:
        // dumb::vector v;
        vector()
        {
            data_ = nullptr;
            size_ = 0;
            capacity_ = 0;
        }

        // This one lets you make a vector of a certain size.
        // All elements are default constructed:
        // dumb::vector v(10);
        vector(unsigned int count)
        {
            data_ = new value_type[count];
            size_ = count;
            capacity_ = count;
        }

        // This one lets you make a vector of a certain size.
        // All elements are default constructed, but then assigned value
        // dumb::vector v(10, 1000); // 10 ints all set to value 1000
        vector(unsigned int count, const value_type& value)
        {
            data_ = new value_type[count];
            size_ = count;
            capacity_ = count;
            for (unsigned int i = 0; i < size_; ++i)
            {
                data_[i] = value;
            }
        }

        // This one lets you use an initializer_list for creation.
        // I know this might be confusing. If you don't want to use this one,
        // remove #include <initializer_list> from the top of this file.
        // dumb::vector v = {1, 1, 2, 3, 5, 8, 13};
        vector(const std::initializer_list<value_type>& init_list)
        {
            size_ = init_list.size();
            capacity_ = init_list.size();
            data_ = new value_type[size_];
            auto it = init_list.begin();
            for (unsigned int i = 0; i < size_; ++i)
            {
                data_[i] = *it;
                ++it;
            }
        }

        /* YOU MUST KEEP THE FOLLOWING THREE FUNCTIONS OR RULE OF 3 IS VIOLATED */
        // copy constructor. Type MUST BE const reference
        vector(const vector& other)
        {
            data_ = new value_type[other.size_];
            size_ = other.size_;
            capacity_ = other.size_;
            for (unsigned int i = 0; i < size_; ++i)
            {
                data_[i] = other.data_[i];
            }
        }

        // assignment operator. Other doesn't need to be const reference but it is good practice
        vector& operator=(const vector& other)
        {
            delete[] data_;

            data_ = new value_type[other.size_];
            size_ = other.size_;
            capacity_ = other.size_;
            for (unsigned int i = 0; i < size_; ++i)
            {
                data_[i] = other.data_[i];
            }

            return *this;
        }

        // destructor
        ~vector()
        {
            delete[] data_;
        }

        /* THE FOLLOWING FUNCTIONS ARE OPTIONAL BUT RECOMMENDED DEPENDING ON YOUR NEEDS */

        // allows index operations
        // dumb::vector v(10, 5); // vector of size 10, all set to 5
        // v[0] = 20; // set the first element to 20 instead
        value_type& operator[](unsigned int pos)
        {
            return data_[pos];
        }

        unsigned int size()
        {
            return size_;
        }

        /* THE FOLLOWING FUNCTIONS ARE OPTIONAL DEPENDING ON YOUR NEEDS */
        
        bool empty()
        {
            return size_ == 0;
        }

        // increase capacity if required, and copy the element to the end
        void push_back(const value_type& value)
        {
            if (size_ == capacity_)
            {
                reserve(size_ + 1);
            }

            data_[size_] = value;
            ++size_;
        }

        // removes the last element from the vector. Does not return it.
        void pop_back()
        {
            --size_;
            // this overwrites what used to be the last element
            // with a default constructed object of your type
            // essentially deleting what used to be there
            data_[size_] = value_type{};
        }

        // increases capacity if required, inserts a copy of the element at the chosen index
        value_type* insert(unsigned int pos, const value_type& value)
        {
            if (size_ == capacity_)
            {
                reserve(size_ + 1);
            }

            for (unsigned int i = size_; i > pos; --i)
            {
                data_[i] = data_[i - 1];
            }

            data_[pos] = value;
            ++size_;

            return data_ + pos;
        }

        // copies every element above pos down a slot
        value_type* erase(unsigned int pos)
        {
            --size_;
            unsigned int i;
            for (i = pos; i < size_; ++i)
            {
                data_[i] = data_[i + 1];
            }
            // this overwrites what used to be the last element
            // with a default constructed object of your type
            // essentially deleting what used to be there
            data_[i] = value_type{};

            return data_ + pos;
        }

        // Copies all the elements in the vector to a larger data allocation.
        // Accessing that extra space is undefined behavior.
        // dumb::vector v;
        // v.reserve(10); // increases capacity to 10
        // for (unsigned int i = 0; i < 10; i++)
        //     v.push_back(i); // doesn't keep copying the entire vector on every push_back()
        void reserve(unsigned int new_cap)
        {
            if (new_cap <= capacity_)
                return;

            value_type* new_data = new value_type[new_cap];
            for (unsigned int i = 0; i < size_; ++i)
            {
                new_data[i] = data_[i];
            }

            delete[] data_;
            data_ = new_data;
            capacity_ = new_cap;
        }

        // returns a raw pointer to the data. Really useful for
        // functions that take a value_type[] as a parameter
        value_type* data()
        {
            return data_;
        }

        // acts as an iterator so you can use iterator loops
        // and range-based for loops
        // for (auto i = v.begin(); i != v.end(); i++)
        //     func(*i);
        // for (auto i : v)
        //     func(i);
        value_type* begin()
        {
            return data_;
        }

        // same as above
        value_type* end()
        {
            return data_ + size_;
        }
    };

}

#endif // DUMB_VECTOR_H
