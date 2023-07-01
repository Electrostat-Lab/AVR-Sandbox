# Hello-Arrays
> Created by [Pavly G.](https://github.com/Scrappers-glitch)

## Table of contents:
1) Uni-dimensional arrays (aka "automatic/direct" buffers) and pointers.
2) Multi-dimensional arrays.
3) Character arrays or String literals.
4) DIY Tasks.

## Uni-dimensional arrays and pointers:

An array is a collection of objects of the same data type, allocated contiguously in memory.

- Individual objects in an array, called elements, are accessed by their position in the array.
- The subscripting operator ([]) provides the mechanics for creating an index to array elements or the created memory cells out of the main buffer. 
- An array facilitates the coding of repetitive tasks by allowing the statements executed on each element to be put into a loop that iterates through each element in the array.
- Accesing the array elements are called indexing or dereferencing the pointer location.

Here is a simple example:
```c
int number_of_elements = 3;
int numbers[number_of_elements];

/* initialize the elements of this array */
numbers[0] = 30;
numbers[1] = 40;
numbers[2] = 50;
```

This example creates and initializes an automatic memory buffer of 3 elements with size [3 * 4 = 12] bytes.

Another way we could write this example using operations on pointers:
```c
const int number_of_elements = 3;
int numbers[number_of_elements];

int* numbers_address = &numbers[0];

/* initialize the elements of this array */
*(numbers + 0) = 30;
*(numbers + 1) = 40;
*(numbers + 2) = 50;
```

This example can be demonstrated using the following scheme: 

<img src="https://software-hardware-codesign.github.io/AVR-Sandbox/HelloArrays/.thumbnails/unidimensional-buffer.png" height=550 width=950/>

## Multi-dimensional arrays:

A multi-dimensional array is a collection of a matrix-like array where the elements can be accessed by specifying a `row` and a `column`, there may be multiple levels of rows.

For example:
```cpp
char name_elements[2][12] = { {'E', 'm', 'b', 'e', 'd', 'd', 'e', 'd', '\32', '\0'}, 
                             {'E', 'n', 'g', 'i', 'n', 'e', 'e', 'r', 'i', 'n', 'g', '\0'} };
```
This example creates a memory buffer of [2 * 12 =  24] elements with a total size of [24 * 1 = 24] bytes.

In this example, the first subscript notation represents the most outer parenthesis, while the second subscript notation represents the most inner parenthesis.

To access a cell (array element) using the subscript notation, you need to specify the row levels and the column (if you want to use the subscript notations), just the same as a table or a matrix with some cells: 
```c
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
        printf("%c", name_elements[i][j]);
    }
}
```

To access a cell (array element) using the memory address, you don't need to specify the row levels and the column; because memory pages are linear components, so all elements are placed in adjacent to each other bounded by their `start_address` and their `end_address`: 
```c
for (int i = 0; i < rows; i++) {
    const char* str = *(name_elements + i);
    printf("%s", str);
}
```

Here is the representation in terms of memory:

<img src="https://software-hardware-codesign.github.io/AVR-Sandbox/HelloArrays/.thumbnails/memory-chunks-cells.png" height=550 width=950/>

And this is an equivalent syntax, dealing with the array as a memory buffer in terms of memory:
```c
/* Treating multidimensional array as a single buffer of memory */
/* 1) Get the total number of cells of an array */
int cells = rows * columns;
for (int cell = 0; cell < cells; cell++) {
    /* Get the actual buffer */
    const char* buffer = name_elements;
    /* print buffer cells */
    printf("%c", buffer[cell]);
}
```

> Remark: 
> The multi-dimensional arrays represent a buffer that is internally divided into large chunks (arrays), de-referencing will
> get you to the inner most value of those chunks as you go.
> Casting an array to a buffer (pointer) will manipulate it as a linear memory buffer (unidimensional buffer).

## Character arrays or String literals:

A string literal is an array of characters aka `char[]` or `char*`.

The `char*` variable type specifier declares a buffer (array) of characters with a user-decided variable length of characters, on the other hand `char[const int]` declares a buffer with a user-decided constant length which is evaluated at the compile-time.

As for `char*` types, the compiler evaluates the length of them at the compile-time according to the initialization length.

The string literal is marked in memory by its start address (the address of the first character) and it usually ends with the terminating character `'\0'`, note how the zero here is escaped; because `'0'` in ASCII is encoded by `'48'` in decimals and `'\0'` is equivalent to `0` without "single quotes" and can be also replaced by `NULL`.

For example: 
```c
/* create a variable length constant string; the length is evaluated by the compiler at the compile-time */
const char* test_var_str = "Testing the variable length string literal";
for (int i = 0; i < strlen(test_var_str); i++) {
    printf("%c", test_var_str[i]);
}
printf("\n");
```

And this is code shows how to create an automatically allocated character buffer copy of the previous string literal:
```c
/* declares a buffer of characters with the same length as the pre-defined string literal; 
    notice: the [+1] for the null terminating character which can be used to identify the end of a string literal */
char test_const_str[strlen(test_var_str) + 1]; 
/* fill the buffer with the previous string literal, notice how the [+1] handles the null terminating character */
for (int i = 0; i < strlen(test_var_str) + 1; i++) {
    test_const_str[i] = test_var_str[i];
}
for (int i = 0; i < strlen((const char*) test_const_str); i++) {
    printf("%c", test_var_str[i]);
}
printf("\n");
```

Remark: the `int strlen(const char*)` accepts a `const char*` reference and returns the number of elements or cells without counting the terminating character and it's fairly equivalent to this step counter: 
```c
static inline int get_length(const char* str) {
    int step;
    for (; str[step] != NULL; step++);
    return step;
}
```
To use `int strlen(const char*)` function, make sure to add `#include <string.h>` to your include directives.

---------------------------
## DIY Tasks

### Task-A: A Square Matrix Utility

Linear equations are represented graphically by straight lines and algebrically by first order unkowns.

For example:
- Player-coordinates = 2x + 3y + 4z
- NPC-coordinates = 5x + 6y + 6z
- Ball-coordinates = 10x + 20y + 8z

Can be represented by this square matrix:
[ 2, 3, 4 ]
[ 5, 6, 6 ]
[ 10, 20, 8]

So, in C, it should be represented by: 
```c
int mat_a[3][3] = { {2, 3, 4},
                   {5, 6, 6},
                   {10, 20, 8} };
/* add 2 matrices here by adding their entries and outputing the result in a new matrix */
```

An n × n matrix is called a `square matrix`, since it has the same number of rows as columns.

In linear algebra, a collection of linear equations can be represented as matrices, operations on linear equations can be obtained from the matrices as well.

Arrays or buffers and they are memory addresses or pointers.
Memory is a linear component and so the above matrix can be passed to a function as a pointer variable, the pointer variable holds the address of its first member.

Create a header file `sqmatrix.h` which should hold the following function prototypes:
- `int* mat_add(int* a, int* b, int entries)`: adds 2 square matrices and obtains the result in the return statement.
- `int* mat_subtract(int* a, int* b, int entries)`: subtracts 2 square matrices and obtains the result in the return statement.
- `int* mat_scalar_product(int* a, int entries, int scalar)`: multiples the matrix A enteries (elements) with the scalar number.
- `int mat_get_length(int* a, int entries)`: returns the total number of elements of matrix A.
- `int mat_get_size(int* a, int entries)`: returns the total size of matrix A.

And the source files for each function: 
- `mat_add.c`
- `mat_subtract.c`
- `mat_scalar_product.c`
- `mat_length.c`
- `mat_size.c`

Here is a simple example: [mat_addition](https://gist.github.com/Scrappers-glitch/95f323f35c8285f64d322dbf01bfa5d3).

### Task-B: Extended Utility

The sum of the main diagonal elements of an n × n matrix A is called the trace of
A and is denoted tr(A). Thus,

`tr(A) = a[1][1] + a[2][2] + · · · + a[n][n]`

To check if 2 matrices are equal, first there should be the same number of rows as of the columns and then matrix A entries and matrix B entries should be identical.

Extend the previously created utility and add the following function definitions to the header `sqmatrix.h`:
- `int mat_trace(int*)`: finds the trace of a square matrix.
- `bool mat_are_equal(int*, int*)`: tests whether 2 square matrices are equal.

In the following source files:
- `mat_trace.c`: holds the function definition of `int mat_trace(int*)`.
- `mat_are_equal.c`: holds the function definition of `bool mat_are_equal(int*, int*)`.

> Notice: `bool` is a plugin datatype defined by GNU, make sure to add this directive `stdbool.h`.
