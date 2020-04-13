# dumb::vector

## Table of contents
1. [Introduction](#intro)
1. [Warning](#warning)
1. [Getting started](#getting_started)
    * [`dumbestvector`](#dumbestvector)
    * [`dumb::vector`](#dumbvector)
1. [Multi-file projects](#multi_file)
1. [`dumb::vector`s of multiple types](#two_dumbvectors)
1. [Why?](#why)
1. [Concessions](#concessions)
1. [Use of `initializer_list`](#initializer_list)
1. [The `dumb::` namespace](#namespace)

<a name="intro" />

`dumb::vector` was made with the design goal of providing a memory management container to students when they are forbidden from using `std::vector` on homework or assignments. It was designed with the subgoal of reducing the cognitive load a new student to C++ would endure while juggling learning a a new language and learning about memory management. That means a lot of places you'd normally see move operations, `noexcept`, `std::size_t`, etc don't have those (if you don't know what those things are you can ignore them).

I'm trying to produce code that your average beginner student can read and understand if they're stuck in a course that believes "C++ is just C with extra stuff".

The expected use case is to use and understand the memory management provided by `dumb::vector`, so you can focus on your assignment and not worry about pointers flying around everywhere.

C-style manual dynamic memory management requires you to track pointers, and decide ownership. Whose job is it to delete memory allocated on the heap? It looks like this:
```
#include <iostream>
#include "do_something.h"

int main(int argc, char** argv)
{
    unsigned int n;
    std::cout << "How many elements do you need: ";
    std::cin >> n;

    int* arr = new int[n];
    std::cout << "Enter the " << n << " numbers:\n"; 
    for (unsigned int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    unsigned int new_size = do_something_arr(arr, n);
    if (new_size > n)
    {
        std::cout << "Enter " << new_size - n << " more numbers:\n";
        
        int* temp = new int[new_size]; // have to get more memory
        for (unsigned int i = 0; i < n; i++)
        {
            temp[i] = arr[i]; // have to copy the old array to the new array
        }
        delete[] arr; // have to deallocate the old memory
        arr = temp;
        
        // now we can get the remaining numbers
        for (unsigned int i = n; i < new_size; i++)
        {
            std::cin >> arr[i];
        }
    }

    delete[] arr; // have to manually delete here as well
}
```

C++ style is to encapsulate resource acquisition (such as a dynamic memory request) into classes. The class worries about managing the resource, and the class cleans up the resource when it goes out of scope. Automatically. The point is to reduce the cognitive load on your brain so you can do the programming you want to do. That looks like this:
```
#include <iostream>
#include "dumbvector.h"
#include "do_something.h"

int main(int argc, char** argv)
{
    unsigned int n;
    std::cout << "How many elements do you need: ";
    std::cin >> n;

    dumb::vector vec(n); // creates a dumb::vector of n elements
    std::cout << "Enter the " << n << " numbers:\n"; 
    for (unsigned int i = 0; i < n; ++i)
    {
        std::cin >> vec[i];
    }

    unsigned int new_size = do_something_vec(vec);
    if (new_size > n)
    {
        std::cout << "Enter " << new_size - n << " more numbers:\n";
        
        // now we can get the remaining numbers
        // dumb::vector::reserve is optional (but recommended if bulk-adding):
        vec.reserve(new_size); // increases capacity to new_size
        for (unsigned int i = vec.size(); i < n * 2; ++i)
        {
            int x;
            std::cin >> x;
            vec.push_back(x); // dumb::vector increases its size/capacity as needed
        }
    }
    // dumb::vector takes care of cleaning up the resource
}
```


<a name="warning" />

## Warning

Before using `dumb::vector` in your homework assignment, consult the academic integrity policy of your university, and ask your professor if using a class to handle memory management is allowed. Like, actually ask them. With an e-mail. Or during their office hours. They are people and their job is to teach you - take advantage of that. Heck, even send them a link to `dumb::vector`.

Read through the code you use. Copy-pasting code from the internet without understand it is never a good idea. If you don't understand any of the code you're using, or don't understand *why* the code you copy-pasted is doing something a certain way, consult your book, your professor, or the internet in that order. Despite the memes online, software development is not just copy-pasting other people's code.

<a name="getting_started" />

## Getting started

<a name="dumbestvector" />

### For the absolute bare-bones, super minimal implementation, use `dumbestvector.h`

For the following steps, I recommend renaming `dumbestvector` to something less dumb.

1. Copy `dumbestvector.h` into the same folder as your `.cpp` file  
2. Add `#include "dumbestvector.h"` among the other `#include`s in your `.cpp` file
> Alternatively: instead of 1. and 2. copy the code from `dumbestvector.h` above all the code in your `.cpp` file that needs to know about `dumbestvector`    
3. Find the line `typedef int value_type;`,and change `int` to the type of variable that you want `dumbestvector` to use (`double`, `char`, `myClass`, etc.)  
> If your `value_type` is a [fundamental type](https://en.cppreference.com/w/cpp/language/types)(`int`, `double`, pointer, `char`, etc), then you're okay  
> If your `value_type` is a class or struct, then it must have a default constructor and it must be copyable and assignable (If your class has no defined constructors, then the compiler automatically made these for you. If your class has one or more constructors that take parameters, then you need to explicitly define a constructor that takes no parameters, like `myClass() {}`)
4. Make any changes you want to make. Want to add a function from `dumb::vector`? Want to add operator overloading? If you know what those are, go for it.
5. Start using `dumbestvector`!
```
// dumbestvector only has one constructor
// you tell it how many elements and what value they should have
// this makes a dumbestvector of size 10 with all elements set to 0
dumbestvector dv(10, 0);

// you can directly access an element of the vector by using []
// this assigns the element at index 5 to be "-1"
dv[5] = -1;

// dumbestvector knows its size, even if you pass it to a function
// this loops through and assigns each element to the square of its index
for (unsigned int i = 0; i < dv.size(); i++)
{
    dv[i] = i * i;
}

// the data in dumbest vector can be sent to a function that
// expects an array or a pointer to your data, if your assignment
// has some function like this that you MUST use
int find_minimum(int arr[], int size); // a function that expects an array (look up pointer decay)
int find_maximum(int* arr, int size);  // a function that expect a pointer to int

int min = find_minimum(dv.data(), dv.size());
int max = find_maximum(dv.data(), dv.size());

// even functions that modify the data
void insertion_sort(int arr[], int size);

insertion_sort(dv.data(), dv.size());
```

A `dumbestvector` **CANNOT** by default add new elements, remove elements, or iterate through elements (using `begin()` and `end()`). If you need this functionality, add it from `dumb::vector` or just use `dumb::vector`.

<a name="dumbvetor" />

### `dumb::vector` For basic one-file projects

For the following steps, I recommend renaming `dumb::vector` to something less dumb. If you want to rename the encapsulating `dumb::` namespace (or remove it entirely) feel free to do so. If you remove it, you'll have to delete the `namespace dumb {` at the top of the file, and the very last `}` at the end of the file.

If you remove the namespace, you'll type `vector` in your code everywhere instead of `dumb::vector`. If you're `using namespace std;` in your code, then the compiler will get confused because it can't tell if `vector` means `std::vector` or the `vector` formerly known as `dumb::vector`. In this case I recommend not `using namespace std;`. If you MUST use it, then rename the `vector` formerly known as `dumb::vetor` to something like `MyVector` so the compiler doesn't get confused.

1. Copy `dumbvector.h` into the same folder as your `.cpp` file  
2. Add `#include "dumbvector.h"` among the other `#include`s in your `.cpp` file
> Alternatively: instead of 1. and 2. copy the code from `dumbvector.h` above all the code in your `.cpp` file that needs to know about `dumb::vector`    
3. Find the line `typedef int value_type;`,and change `int` to the type of variable that you want `dumb::vector` to use (`double`, `char`, `myClass`, etc.)  
> If your `value_type` is a [fundamental type](https://en.cppreference.com/w/cpp/language/types)(`int`, `double`, pointer, `char`, etc), then you're okay  
> If your `value_type` is a class or struct, then it must have a default constructor and it must be copyable and assignable (If your class has no defined constructors, then the compiler automatically made these for you. If your class has one or more constructors that take parameters, then you need to explicitly define a constructor that takes no parameters, like `myClass() {}`)
4. Make any changes you want to make. I recommend removing the functions you're not going to use. At the very least, leave in the functions that `dumbestvector` uses.
5. Start using `dumb::vector`!
```
// several ways to create a dumb::vector
dumb::vector dv1; // default constructor. An empty dumb::vector
dumb::vector dv2(10); // creates a dumb::vector of 10 elements, all default initialized
dumb::vector dv3(10, -1); // creates a dumb::vector of 10 elements, all set to -1
dumb::vector dv4 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // creates a dumb::vector of 10 different elements
dumb::vector dv5 = dv4; // creates a dumb::vector that is a copy of another dumb::vector
dv3 = dv2; // assigns a dumb::vector to be a copy of another dumb::vector

// access elements just like an array or std::vector
dv4[0] = 100;
int a = dv4[9];

// iterate through a dumb::vector by size
for (int i = 0; i < dv4.size(); i++)
{
    std::cout << dv4[i] << " ";
}
std::cout << "\n";

// iterate through a dumb::vector with iterators
for (auto it = dv4.begin(); it != dv.end(); it++)
{
    std::cout << *it << " ";
}
std::cout << "\n";

// or use a range-based for loop
for (auto e : dv4)
{
    std::cout << e << " ";
}
std::cout << "\n";

// pass a pointer to the data to functions that want to operate on arrays
int find_max(int arr[], int size);

int max = find_max(dv4.data(), dv4.size());

// even functions that mutate the data
void insert_sort(int arr[], int size);

insert_sort(dv4.data(), dv4.size());

// (although it's better if you write these functions to take a dumb::vector& parameter)
int find_max(const dumb::vector& dv);
void insert_sort(dumb::vector& dv);

max = find_max(dv4);
insert_sort(dv4);

// you can add elements to the end of a dumb::vector
dv4.push_back(100);
dv4.push_back(1000);

// you can remove elements from the end of a dumb::vector
// this does not return the element, so use it before you pop_back()
dv4.pop_back();
dv4.pop_back();

// you can insert an element at any valid index
dv4.insert(42, 0); // inserts 42 at index 0, everything else is shifted right
dv4.insert(14159, 3); // inserts 14159 at index 3, everything to the right is shifted right

// you can erase an element from a given index (but not a range)
dv4.erase(0); // erase at index 0, everything else is shifted left
dv4.erase(3); // erase at index 3, everything to the right is shifted left

// you can reserve a bunch of space up front if you know you're going
// to add many items to the dumb::vector
dv4.reserve(100); // increases the capacity, does not increase the size
for (int i = 0; i < 50; i++)
{
    // dv[i] = i * i; // invalid, accessing elements out of bounds. Size has not increased
    dv.push_back(i * i); // valid
}

// using reserve does not increase the capacity BY the requested number
// using reserve increases the capacity TO the requested number
```

<a name="multi_file" />

## For multi-file projects

If you include `dumb::vector` in multiple compilation units (`.cpp` files), you're going to have a bad time. Each of the compiled objects will contain the definition for the `dumb::vector` functions, and then the linker won't know which function is the "real" one. Normally this is solved by having separate `.h` and `.cpp` files. I'm not sure about this, but I think my target audience generally makes one-file C++ projects. I wanted to make the single `.h` file for ease of use.

If you want to use `dumb::vector` in multiple compilation units, you'll have to split it into a `.h` and `.cpp` file. I leave that as an exercise to the reader.

<a name="two_dumbvectors" />

## For using two or more `dumb::vector` with different `value_type`s

You want a `dumb::vector` that holds `int`s and a `dumb::vector` that holds `double`s (or `char`s or `MyClass`es)? Well you'll either need to make TWO copies of the `dumb::vector` code, name them something different (`intvector` and `doublevector` for example), and set the `value_type` for each to the desired type. Or use templates. If you know how to use templates, you're probably allowed to use `std::vector`, and should do so.

<a name="why" />

## Why does this exist?

The pont of `dumb::vector` is to provide a container class to students who:

- are first learning C++,
- understand only the basics,
- have an assignment that forbids the use of `std::vector`,
- could reasonably be expected to understand the code of `dumb::vector`,
- don't know what the Rule of 0/3/5 is, and desperately need to learn it (if you don't know what that is, you [desperately](https://stackoverflow.com/q/4172722/2027196) [need to](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-zero) [learn it](https://en.cppreference.com/w/cpp/language/rule_of_three)).

`dumb::vector` is very pro-Rule of 3. Resource management and [RAII](https://en.wikipedia.org/wiki/Resource_acquisition_is_initialization) are key concepts of C++, and should be taught. They are often not.

<a name="concessions" />

## Concessions

`dumb::vector` was made with the design goal of limiting the cognitive load a student would have to endure while learning a new language and figuring out how memory management works. That's a frustrating situation to be in. Because of that, I leave out a lot of keywords I would add to real code. I don't have any move operations. Nothing is `noexcept`. This isn't a `template` class. There's `unsigned int` instead of `std::size_t`. I don't use member initialization.

If you want to add any of these missing concepts to `dumb::vector`, go bananas. But you don't HAVE TO if you don't want to. Making these changes will improve performance, but the programs I see that would benefit from `dumb::vector` don't usually have a huge computing load.

<a name="initializer_list" />

### But the `initalizer_list`?
Okay, yes, `dumb::vector` has an `initializer_list` constructor. I wanted users to be able to do something like
```
dumb::vector dv = {1, 1, 2, 3, 5, 8, 13};
```
since this is a common way to initialize arrays, and I don't want users of `dumb::vector` to think that dynamic arrays are ever better than `dumb::vector`. If you don't understand `initializer_list`s, you can just remove this constructor and the `#include <initializer_list>` from your code.

<a name="namespace" />

### But the namespace?
Okay, yes, this one is just because I really like the idea of a namespace called "dumb". In my defense, `dumbestvector` is not encapsulated in a namespace.

<a name="default_constructor" />

### But what if `value_type` is a class that doesn't have a default constructor?
Then you're out of luck. We only use `new[]` and `delete[]`, so when we create a new `dumb::vector` of size 10, we create 10 objects using the default constructor. That's how `new[]` works. If you know how to use `operator new[]`, then feel free to use that, but again, at that point you're probably allowed to use `std::vector`.
