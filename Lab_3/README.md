# EECS 281: Lab 3 - String Library

## Introduction

This assignment supplements the "Arrays and Containers" lecture of the course. In this lab assignment, students gain exposure to how array operations are implemented (i.e. insert and erase require shifting of elements, copy-swap, etc.), get practice with the C++ string library, and are introduced to STL concepts.

## Problem Statement

In lab and lecture, you learned about C++ strings and the C++ string library. The string class provides many helpful member functions that simplify the usage of string objects (such as find, insert, erase, just to name a few!). While you do not have to fully understand how a string object works under the hood, knowing these string operations will be helpful for future projects and interviews. In this lab assignment, you will implement five of these operations within a String class that we have provided for you.

Please complete the lab assignment in the `String.cpp` file. Do not include any libraries beyond the ones given to you or modify the file outside the portions labeled with a **TODO**. Doing so may cause your program to fail on the autograder. Your program will be graded on 71 test cases, with 11 testing `erase()`, 11 testing `insert()`, 20 testing `replace()`, 14 testing `find_first_of()`, and 15 testing `find_last_of()`. The test cases provided to you here are the same as the test cases on the autograder.

It is recommended that you review the "Arrays and Containers" lecture before starting this assignment.

### TODO #1: Erase Function

The erase() function is defined as follows:

``` c++
String& String::erase(size_t pos, size_t len);
```

When `erase()` is called using two parameters, `pos` and `len`, this function erases the portion of the String that begins at index `pos` and spans `len` characters, or until the end of the String, whichever comes first. If `len` is not defined, the String is erased from `pos` to the end. A reference to the modified String is then returned. For example:

``` c++
String str = "Darden";
str.erase(3, 2);
```

erasing would begin at index 3 of `str`, and 2 characters would get erased. In this case, "de" would be removed from the interior, and the contents of `str` after the call would be "Darn". You may assume that `pos` will always be valid, and `len` will be positive.

HINT: it may be helpful to begin with two pointers of the underlying c-string, one that points to the position where erasing should begin, and one that points to the first character that should not be erased (`len` away from `pos`). Then, you can overwrite the characters at the first pointer with the characters of the second until you have shifted all characters after the erased segment of the String to their correct positions.

WARNING: make sure that the final c-string you end up with has a sentinel at the end. This can be done by assigning a character in the c-string with `a_null_byte`, a member variable that has a value of `'\0'`:

``` c++
*ptr_to_pos = a_null_byte;
```

where `ptr_to_pos` is a pointer to a position within the c-string that you want to assign with the null character. Also, make sure the size of the String is properly maintained at all times.

### TODO #2: Insert Function

The `insert()` function is defined as follows:

``` c++
String& String::insert(size_t pos, const String& str);
```

When `insert()` is called using two parameters, `pos` and `str`, this function inserts the contents of `str` BEFORE the character at position `pos`. A reference to the modified String is returned. For example:

``` c++
String str = "shelf";
str.insert(0, "book");
```

the string "book" would be added at the beginning of `str`, resulting in a final `str` value of "bookshelf". You may assume that the starting position `pos` will always be valid.

NOTE: since insertion may cause the underlying c-string to exceed its capacity, a check needs to be done to ensure that there is enough memory allocated to hold the new String once everything has been inserted. This check has been provided for you; you do not need to worry about it.

HINT: recall how an array works when you try to insert an element - all other elements after the insertion point must be shifted. This is true here as well. First, you must shift all characters after the insertion point by a certain distance. Then, you would insert the contents of the new String into the slots you have freed up for insertion.

WARNING: once again, make sure that your new c-string includes the sentinel at the very end, and that the size is properly updated after the insert is complete.

### TODO #3: Replace Function

The `replace()` function is defined as follows:

``` c++
String& String::replace(size_t pos, size_t len, const String& str);
```

When `replace()` is called using three parameters, `pos`, `len`, and `str`, this function replaces the portion of the String that begins at character `pos` and spans `len` characters with the contents of `str`. For example:

``` c++
String truth = "EECS 281 is hard";
truth.replace(12, 4, "fun");
```

the substring of length 4 starting at position 12 of `truth` ("hard") would be replaced with the string "fun". The final contents of `truth` after the call to `replace()` would be "EECS 281 is fun". You may assume that `pos` is valid. If the value of `len` is greater than the length of `str`, only replace `len` characters.

NOTE: since replacing may cause the underlying c-string to exceed its capacity (if the portion being replaced is smaller than the String being added in), a check needs to be done to ensure that there is enough memory allocated to hold the new String once everything has been replaced. This check has been provided for you; you do not need to worry about it.

HINT: the implementation for `replace()` is very similar to the implementation of `insert()`. Shift all the characters after the segment to replace, and move the new String into the space you opened up. If `str` is shorter than `len`, the replaced section will be shorter than it was before, and if `str` is longer than `len`, the replaced section will be longer than it was before. However, there is an alternative solution that can allow you to complete this function is just a few lines. If you want to replace a portion of the String with a new String, you need to erase the portion that you want to replace and insert in the new String that you want to add. Does this sound familiar to something you already have?

In addition, think about edge cases that can come up. Similar to `insert()`, you can pass in any String into the `str` argument of the `replace()` function. Are there certain arguments that can cause trouble? See some of the edge cases mentioned in the `insert()` section of the spec, if you are having trouble coming up with them.

### TODO #4: Find-First-Of Function

The `find_first_of()` function is defined as follows:

``` c++
size_t String::find_first_of(const String& str, size_t pos);
```

This function is very similar to the `find()` function covered above. However, instead of checking if `str` can be found in the String in its entirety, it checks if ANY characters of `str` can be found in the String. In other words, given two parameters `str` and `pos`, this function searches the String for the first character that matches ANY of the characters in str, starting from position `pos` of the String. Characters before `pos` are ignored. It is enough for a single character of `str` to match for the search to be successful. If a match is found, the function returns a `size_t` that represents the position of the first character that matches. Otherwise, the function returns `npos`. If `pos` exceeds the length of the String, the function will never find a match. If `pos` is not specified, the value of `pos` is assumed to be 0.

As long as a single character in `str` can be found in the String, the search is successful and returns the position of the match, as demonstrated in the examples below:

``` c++
String truth = "EECS 281 is fun";
size_t found = 0;
found = truth.find_first_of("281", 0); // found is 5 since '2' can be found at index 5
found = truth.find_first_of("280", 0); // found is 5 since '2' can be found at index 5
found = truth.find_first_of("281", 6); // found is 6 since '8' can be found at index 6
```

HINT: the implementation of `find_first_of()` is similar to that of `find()`, which is provided, but it only checks for the existence of one character match rather than an entire String match.

### TODO #5: Find-Last-Of Function

The `find_last_of()` function is defined as follows:

``` c++
size_t String::find_last_of(const String& str, size_t pos);
```

The `find_last_of()` function is very similar to the `find_first_of()` function. However, this function looks for the last character in a String that matches any of the characters in `str`, rather than the first. The search begins at position `pos` of the String and moves toward position 0, searching for a match along the way. Characters after position `pos` are ignored. If a match is found, the function returns a `size_t` that represents the position of the last character that matches. Otherwise, the function returns `npos`. If `pos` exceeds the length of the String, the entire String is searched. For example:

``` c++
String truth = "EECS 281 is fun";
size_t found = 0;
found = truth.find_last_of("Eggs", 14); // found is 10 since an 's' can be found at index 10 
```

WARNING: unlike `find()` and `find_first_of()`, which both default to zero, it is possible for `find_last_of()` to take in a value of `pos` that exceeds the size of the String. Make sure you take this into consideration.

## Submitting to the Autograder

You may work with a partner on this lab. To submit to the autograder, create a .tar.gz file containing just String.h, as shown below. Do not modify the String.h file name, or your submission won't run! Make sure the capitalization of your command matches.

``` console
$ tar -czvf lab3.tar.gz String.cpp
```

If you are working with a partner, both partners must submit separately to the autograder. Only students who submit code to the autograder will receive points. It's perfectly fine for both partners to submit identical code, as long as the code was written by both of the partners. You will be able to make five submissions to the autograder per day, up until the due date. Make sure the project identifier is included in `String.cpp`.

You may use the provided Makefile to generate a tarball:

``` console
$ make fullsubmit
```
