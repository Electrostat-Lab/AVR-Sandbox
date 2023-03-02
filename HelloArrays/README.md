# Hello-Arrays

## Uni-dimensional arrays and pointers:

An array is a collection of objects of the same data type, allocated contiguously in memory.

- Individual objects in an array, called elements, are accessed by their position in the array.
- The subscripting operator ([]) provides the mechanics for creating an index to array elements. 
- An array facilitates the coding of repetitive tasks by allowing the statements executed on each element to be put into a loop that iterates through each element in the array.
- Accesing the array elements are called indexing or dereferencing the pointer location.

Here is a simple example:
```c
int numbers[number_of_elements];

/* initialize the elements of this array */
numbers[0] = 30;
numbers[1] = 40;
numbers[2] = 50;
```

Another way we could write this example using operations on pointers:
```c
int numbers[number_of_elements];

int* numbers_address = &numbers[0];

/* initialize the elements of this array */
*(numbers + 0) = 30;
*(numbers + 1) = 40;
*(numbers + 2) = 50;
```

This example can be demonstrated using the following scheme: 


## Multi-dimensional arrays:

## Charachter arrays or String literals: