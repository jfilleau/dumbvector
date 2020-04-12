#include <iostream>
#include "dumbvector.h"
#include "dumbestvector.h"

void print_vec_it(dumb::vector vec);
void print_vec_loop(dumb::vector vec);
void print_dumbest(dumbestvector vec);
void insertion_sort(dumb::vector& vec);
void insertion_sort(dumbestvector& vec);

int main(int argc, char** argv)
{
    // create an empty dumb::vector and push_back elements into it
    dumb::vector v1;
    v1.push_back(0);
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);

    // we can either use iterators or loops to access the contents
    std::cout << "Testing iterator printing:\n";
    print_vec_it(v1);
    std::cout << "Testing loop printing:\n";
    print_vec_loop(v1);

    // pop pop!
    v1.pop_back();
    std::cout << "Testing pop_back(). Should be one fewer item then before:\n";
    print_vec_it(v1);

    // testing that insert works
    v1.insert(0, 10);
    std::cout << "Testing insert(0, 10). First element should be 10:\n";
    print_vec_it(v1);

    v1.insert(2, 20);
    std::cout << "Testing insert(2, 20). Third element should be 20:\n";
    print_vec_it(v1);

    // testing that operator[] works
    v1[0] = 6;
    v1[4] = 12;
    std::cout << "Testing operator[]. v[0] = 6; v[4] = 12;\n";
    print_vec_it(v1);

    // testing that copy construction works
    dumb::vector v2 = v1;
    std::cout << "Testing copy construction. Should be same as above:\n";
    print_vec_it(v2);

    // testing that erase works
    std::cout << "Testing erase. Fourth element should be erased:\n";
    v2.erase(3);
    print_vec_it(v2);

    // testing that assignment operator works
    v1 = v2;
    std::cout << "Testing operator=. Should be same as above:\n";
    print_vec_it(v1);

    // testing that initializer lists work
    dumb::vector v3{ 1, 1, 2, 3, 5, 8, 13 };
    dumb::vector v4 = { 21, 34, 55, 89 };

    std::cout << "Testing initializer_list construction. Should be { 1, 1, 2, 3, 5, 8, 13 }:\n";
    print_vec_it(v3);
    std::cout << "Testing initializer_list construction. Should be { 21, 34, 55, 89 }:\n";
    print_vec_it(v4);

    dumb::vector v5 = { 7, 0, -8, 100, 12345, 2, 22 };
    std::cout << "Testing a common use case, insertion sort. Unsorted dumb::vector:\n";
    print_vec_it(v5);
    insertion_sort(v5);
    std::cout << "After sorting:\n";
    print_vec_it(v5);

    // test dumbest vector
    dumbestvector v6(10, 100);
    std::cout << "Testing dumbest vector. Should be 10 elements of value 100:\n";
    print_dumbest(v6);

    v6[5] = 0;
    std::cout << "Testing operator[]. v[5] = 0:\n";
    print_dumbest(v6);

    for (unsigned int i = 0; i < v6.size(); i++)
    {
        v6[i] = i * -10;
    }
    std::cout << "Testing dumbestvector insertion sort. Unsorted:\n";
    print_dumbest(v6);
    insertion_sort(v6);
    std::cout << "After sorting:\n";
    print_dumbest(v6);
}

void print_vec_it(dumb::vector vec)
{
    std::cout << "[ ";
    for (const auto& i : vec)
    {
        std::cout << i << " ";
    }
    std::cout << "]\n";
}

void print_vec_loop(dumb::vector vec)
{
    std::cout << "[ ";
    for (unsigned int i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << "]\n";
}

void print_dumbest(dumbestvector vec)
{
    std::cout << "[ ";
    for (unsigned int i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << "]\n";
}

void insertion_sort(dumb::vector& vec)
{
    unsigned int i = 1;
    while (i < vec.size())
    {
        unsigned int j = i;
        while (j > 0 && vec[j - 1] > vec[j])
        {
            std::swap(vec[j], vec[j - 1]);
            j -= 1;
        }
        i += 1;
    }
}

void insertion_sort(dumbestvector& vec)
{
    unsigned int i = 1;
    while (i < vec.size())
    {
        unsigned int j = i;
        while (j > 0 && vec[j - 1] > vec[j])
        {
            std::swap(vec[j], vec[j - 1]);
            j -= 1;
        }
        i += 1;
    }
}