# dumb::vector
>I'm not allowed to use std::vector!

the student lamented in the comments of their stackoverflow question. Have no fear, this isn't `std::vector`. It's `dumb::vector`. Totally different.

`dumb::vector` was made with the design goal of providing a memory management container to students when they are forbidden from using `std::vector`. It was designed with the subgoal of reducing the cognitive load a new student to C++ would endure while juggling learning a a new language and learning about memory management. That means a lot of places you'd normally see move operations, `noexcept`, `std::size_t`, etc don't have those (if you don't know what those things are you can ignore them).

I'm trying to produce code that your average beginner student can read and understand if they're stuck in a course that believes "C++ is just C with extra stuff".

## Warning

Before using `dumb::vector` in your homework assignment, consult the academic integrity policy of your university, and ask your professor if using a class to handle memory management is allowed. Like, actually ask them. With an e-mail. Or during their office hours. They are people and their job is to teach you - take advantage of that. Heck, even send them a link to `dumb::vector`.

Despite my opinion that everyone who is managing memory should encapsulate it in a class, your professor may believe differently. It's not cheating to at least ask.

If you want to argue the point, first of all, be kind. Your professor is a person and they've been doing this longer than you (or likely I) have. Second of all, at least arm yourself with some [good advice on teaching C++](https://www.youtube.com/watch?v=YnWhqhNdYyk).

Read through the code you use. Copy-pasting code from the internet without understand it is never a good idea. If you don't understand any of the code you're using, or don't understand *why* the code you copy-pasted is doing something a certain way, consult your book, your professor, or the internet in that order. Despite the memes on reddit, software development is not just lifting code from stackoverflow.

## Getting started

### For basic single-.cpp-file projects

1. Copy `dumbvector.h` into your code directory and add `#include "dumbvector.h"` at the top of your `.cpp` file among the other `#include`s. You might want to rename it to smething less dumb.  
(Alternatively, copy and paste the `dumb::vector` code from `dumbvector.h` into your `.cpp` file above any code that uses `dumb::vector`) 
1. Remove the encapsulating `namespace dumb{}` around the class (don't forget the closing brace!). Or change it. Or keep it. Whatever. If you remove it, then instead of typing `dumb::vector` everywhere, you'd just type `vector` whenever you need to reference it. Note that this will cause problems if you're `using namespace std;`. If you're `using namespace std;`, then change `vector` to `MyVector` or something.
1. Find the line `typedef int value_type;` - this tells your compiler to treat any instance of "value_type" as an "int". Change `int` to the datatype you want to manage (`double`, `char`, `myClass`, etc.)
1. Delete the functions that don't provide functionality you need.
1. You MUST keep the copy constructor, the assignment operator, the destructor, and at least one non-copy constructor. These are labeled in the code.
1. I recommend keeping the `value_type& operator[](unsigned int pos)` function and the `unsigned int size()` function. These let you access your `vector` in the same way you'd access an array or a `std::vector`, like:
```
dumb::vector my_vec(5, 10); // make a dumb::vector of size 5 and set all elements to value 10
my_vec[0] = 0;
my_vec[1] = 1;
my_vec[2] = my_vec[0];
for (int i = 0; i < my_vec.size(); i++)
{
    std::cout << my_vec[i] << " ";  // outputs 0 1 0 10 10
}
std::cout << "\n";
```

### That's not simple enough!

Okay, fine. Copy `dumbestvector.h` instead and add `#include "dumbestvector.h"` to your `.cpp` file. Or copy the code from `dumbestvector.h` and paste it at the top of your `.cpp` file. That has all of the suggested changes. You still need to change the `typedef int value_type;` line because I can't guess what kind of things you want to throw in the container. You should also probably change every instance of the word `dumbestvector` to something less dumb.

### For multi-file projects

If you copy and paste this code into multiple compilation units (multiple `.cpp` files), you're going to have a bad time. Each of those will contain the definition for the `dumb::vector` functions, and when the compiler tries to link all of these object files, it won't know which definition to use (even though they're all the same).

In that case you need to split `dumb::vector` into a `.h` file with just the declarations, and a `.cpp` file with the definitions. But really at the point that your academic course has assignments that span multiple files you really should be allowed to just use `std::vector`. No examples are provided for this. You really should be using `std::vector` at this point.

## For using two or more `dumb::vector` with different `value_type`s

You want a `dumb::vector` that holds `int`s and `dumb::vector` that holds `double`s (or `char`s or `MyClass`es)? Well you'll either need to make TWO copies of `dumb::vector` into your code, name them something different (`intvector` and `doublevector` for example), and set the `value_type` for each to the desired type. Or use templates. If you know how to use templates, you're probably allowed to use `std::vector`, and should do so.

If you don't know how to use templates, well, you're out of luck: `dumb::vector` lives up to its name. It's too dumb for that.

## Why are you making this?

The pont of `dumb::vector` is to provide a container class to students  who:

- are first learning C++,
- understand only the basics,
- have an assignment that forbids the use of `std::vector`,
- could reasonably be expected to understand the code of `dumb::vector`,
- don't know what the Rule of 0/3/5 is, and desperately need to learn it (if you don't know what that is, you [desperately](https://stackoverflow.com/q/4172722/2027196) [need to](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-zero) [learn it](https://en.cppreference.com/w/cpp/language/rule_of_three)).

`dumb::vector` is very pro-Rule of 3. Resource management and [RAII](https://en.wikipedia.org/wiki/Resource_acquisition_is_initialization) are key concepts of C++, and should be taught. They are often not.

## Concessions

`dumb::vector` was made with the design goal of limiting the cognitive load a student would have to endure while learning a new language and figuring out how memory management works. That's a frustrating situation to be in. Because of that, I leave out a lot of keywords I would add to real code. I don't have any move operations. Nothing is `noexcept`. This isn't a `template` class. There's `unsigned int` instead of `std::size_t`. I don't use member initialization.

If you want to add any of these missing concepts to `dumb::vector`, you are more than free to. And I encourage it. But you don't HAVE TO if you don't want to. Making these changes will improve performance, but the types of programs I usually see that would benefit from `dumb::vector` don't usually have a huge computing load. Copying members of the `dumb::vector` everywhere isn't much of an issue.

### But the initalizer_list?
Okay, yes, I have an `initializer_list` constructor. Sue me. I want users to be able to do something like
```
dumb::vector dvec = {1, 1, 2, 3, 5, 8, 13};
```
since this is a common way to initialize arrays. I think the `initializer_list` is the most confusing part for someone new to the language. I might be talked out of having it in `dumb::vector`, but I currently think the benefits outweigh the costs. If you don't understand `initializer_list`s, remove this constructor from your code.

### But you're using a namespace?
Okay, yes, this one is just because I really like the idea of a namespace called "dumb". In my defense, `dumbestvector` is not encapsulated in a namespace.

### But what if my `value_type` is a class that doesn't have a defalut constructor?
Then you're out of luck. We only use `new[]` and `delete[]`, so when we create a new `dumb::vector` of size 10, we create 10 objects using the default constructor. That's how `new[]` works. If you know how to use `operator new[]`, then feel free to use that, but again, at that point you're probably allowed to use `std::vector`.
