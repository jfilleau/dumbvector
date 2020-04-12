#ifndef DUMBESET_VECTOR_H
#define DUMBEST_VECTOR_H

/* dumbestvector

For when dumb::vector isn't dumb enough.
 */


class dumbestvector
{
private:
    // using something different than int? Change it here!
    typedef int value_type;

    value_type* data_;
    unsigned int size_;

public:
    /* ONLY ONE CONSTRUCTOR IS AVAILABLE */

    // This one lets you make a vector of a certain size.
    // All elements are default constructed, but then assigned value
    // dumb::vector v(10, 1000); // 10 ints all set to value 1000
    dumbestvector(unsigned int count, const value_type& value)
    {
        data_ = new value_type[count];
        size_ = count;
        for (unsigned int i = 0; i < size_; ++i)
        {
            data_[i] = value;
        }
    }

    /* YOU MUST KEEP THE FOLLOWING THREE FUNCTIONS OR RULE OF 3 IS VIOLATED */
    // copy constructor. Type MUST BE const reference
    dumbestvector(const dumbestvector& other)
    {
        data_ = new value_type[other.size_];
        size_ = other.size_;
        for (unsigned int i = 0; i < size_; ++i)
        {
            data_[i] = other.data_[i];
        }
    }

    // assignment operator. Other doesn't need to be const reference but it is good practice
    dumbestvector& operator=(const dumbestvector& other)
    {
        delete[] data_;

        data_ = new value_type[other.size_];
        size_ = other.size_;
        for (unsigned int i = 0; i < size_; ++i)
        {
            data_[i] = other.data_[i];
        }

        return *this;
    }

    // destructor
    ~dumbestvector()
    {
        delete[] data_;
    }

    /* THE FOLLOWING FUNCTIONS ARE OPTIONAL BUT RECOMMENDED DEPENDING ON YOUR NEEDS */
    value_type& operator[](unsigned int pos)
    {
        return data_[pos];
    }

    unsigned int size()
    {
        return size_;
    }

    // returns a raw pointer to the data. Really useful for
    // functions that take a value_type[] as a parameter
    value_type* data()
    {
        return data_;
    }
};

#endif // DUMBEST_VECTOR_H