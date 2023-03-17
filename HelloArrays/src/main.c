/**
 * @brief Examines the arrays and the array elements' memory addresses in GNU C.
 * @author pavl_g
 * @note This file is subjected to frequent changes by the author according to the agile principles.
 * @copyright The AVR-Sandbox Project, the Open-Source BSD-3-Clause-License
 */
#include <stdio.h>
#include <inttypes.h>

/**
 * An array is a collection of objects of the same data type, allocated contiguously in memory.
 * Individual objects in an array, called elements, are accessed by their position in the array.
 * The subscripting operator ([]) provides the mechanics for creating an index to array elements. 
 * An array facilitates the coding of repetitive tasks by allowing the statements executed on each element to be put into a loop that iterates through each element in the array.
 */
void define_array() {

	/* initialize an array of 3 integers */
	/* the size of the array is a constant number, once assigned never changes, and can be calculated by [nOfElements x sizeof(type)] */
	const int number_of_elements = 3;
	/* array declaration without an initializer (i.e without an assignment operation) */
	/* this statement defines a memory buffer consisting of 3 elements (pieces), each of which 
	   has a size of 4 bytes, so the total memory buffer weighs 4 x 3 = 12 bytes */
	int numbers[number_of_elements];

	/* initialize the elements of this array */
	numbers[0] = 30;
	numbers[1] = 40;
	numbers[2] = 50;

	printf("*********************************** Array Declarators with late initialization ***********************************\n");
	/* the [&] is the called the "Address of" operator can be used to get the memory address of an element */
	printf("Size of buffer [%p] = [%i] bytes \n", &numbers, sizeof(numbers));
	/* the memory address of the array reference is the same as the memory reference to its first element */
	printf("Memory address of the array [%p] = Memory address of the 1st element [%p] bytes (%d) \n", &numbers, &numbers[0], (int*) &numbers == &numbers[0]);
	printf("Data at chunk [%p] = [%i]\n", &numbers[0], numbers[0]);
	printf("Data at chunk [%p] = [%i]\n", &numbers[1], numbers[1]);
	printf("Data at chunk [%p] = [%i]\n", &numbers[2], numbers[2]);
	printf("*****************************************************************************************************\n");
	
	/**************************************************************************/
	
	printf("*********************************** Array Declarators with instant initialization ***********************************\n");
	long long pre_init_numbers[] = {50000, INT32_MAX, INT8_MAX * 2};
	printf("Size of buffer [%p] = [%i] bytes \n", &pre_init_numbers, sizeof(pre_init_numbers));
	printf("Data at chunk [%p] = [%i]\n", &pre_init_numbers[0], pre_init_numbers[0]);
	printf("Data at chunk [%p] = [%i]\n", &pre_init_numbers[1], pre_init_numbers[1]);
	printf("Data at chunk [%p] = [%i]\n", &pre_init_numbers[2], pre_init_numbers[2]);

	/* A Charachter Uni-dimensional array with an instant initializer, 
	   known as an array of charachters or a string and is equivalent to char[] */
	const char* test_str = "Pavly";
	printf("%s\n", test_str);

	const char test_str_replica1[] = "Pavly";
	printf("%s\n", test_str_replica1);

	const char test_str_replica2[] = {'P', 'a', 'v', 'l', 'y', '\0'};
	printf("%s\n", test_str_replica2);

	printf("*****************************************************************************************************\n");

	/**************************************************************************/
	printf("*********************************** Multi-dimensional arrays with instant initialization ***********************************\n");
	/* declare a buffer of [2 * 8 * 1] = 16 bytes */
	/* When thinking of multi-dimensional arrays think of matrices from linear algebra (however a matrix is not an array)*/
	/* The First subscript expression comprises the rows and the second subscript notation comprises the columns */
	
	// 1st element in the 1st dimension (row 1) = ['P'-'a'-'v'-'l'-'y'], 2nd element in the 1st dimension (row2) = ['G'-'e'-'r'-'g'-'e'-'s']
	// the 2nd dimension is comprised by the columns
	// total elements = rows * columns = 2 * 9 = 18 elements
	// total size = 18 * sizeof(char) = 18 bytes.
	char name_elements[2][12] = {{'E', 'm', 'b', 'e', 'd', 'd', 'e', 'd', 32, '\0'}, 
                             {'E', 'n', 'g', 'i', 'n', 'e', 'e', 'r', 'i', 'n', 'g', '\0'}};
	const int rows = 2;
	const int columns = 12;
	
	/* Those are 3 equivalent ways to access the data inside the [name_elements] */

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			printf("%c", name_elements[i][j]);
		}
	}
	printf("\n");

	for (int i = 0; i < rows; i++) {
		printf("%s", name_elements[i]);
	}
	printf("\n");

	/* Here is another equivalent HACK !! */
	/* In this hack, we designated the first dimension values as strings (aka const char*) */
	/* The multi-dimensional array variable is an actual pointer to another pointer; the other pointer points to the beginning of the string literals */
	for (int i = 0; i < rows; i++) {
		const char* str = *(name_elements + i);
		printf("%s", str);
	}
	printf("\n");

	/* Treating multidimensional array as a single buffer of memory */
	for (int cell = 0; cell < rows * columns; cell++) {
		/* Get the actual buffer */
		const char* buffer = (const char*) name_elements;
		/* print buffer cells */
		printf("%c", buffer[cell]);
	}

	printf("\n");

	/**************************************************************************/
}

/**
 * The array operations can be performed either on the elements or on the elements' memory addresses for accessiblity. 
 */
void array_operations() {
	/* operations on elements */
	int test_operations[] = {3, 5};
	printf("Summation of [%i + %i] = [%lld]\n", test_operations[0], test_operations[1], test_operations[0] + test_operations[1]);

	/* Operations on elements addresses */
	/* A memory address is a pointer to a memory location or memory chunk that stores a value */
	/* Each memory chunk has a start address and an end address */
	/* The memory chunks are also known as virtual memory partitions */
	/* Subtracting the end address from the start address will render the size of the memory chunk */
	/* You can jump from element A to element B on an array by adding on the memory address of element A */
	int elements[] = {10, 20, 30, 40};
	int* elements_address = &elements[0];
	printf("Elements from reference address = \n");
	for (int step = 0; step < sizeof(elements) / sizeof(int); step++) {
		printf("%d ", *(elements_address + step));
	}
	printf("\n");
} 

int* pass_by_value(int test) {
    return &test;
}

int* pass_by_reference(int* test) {
    return test;
}

void pointers_example() {
    
    /* A pointer is variable that holds an integer number which represents a memory address to a memory buffer or chunk */ 
    /* Pointers are 64-bit (8 bytes) integer positive numbers in case of 64-bit binaries and 32-bit (4 bytes) in case of 32-bit binaries */ 
    
    /* create a null pointer -- a generic pointer (a pointer with indeterminate memory type) */
    void* ptr0 = NULL;
    /* another way to create an un-initialized pointer */
    void* ptr1 = (void*) 0;
    
    printf("Size of pointer-0 = %d \n", sizeof(ptr0));
    printf("Size of pointer-1 = %d \n", sizeof(ptr1));
    
    int number = 220;
    
    /* initialize the pointer variable with the memory address of the [number] */
    /* the ampersand operator [&] is called the "address-of operator" in C and it is used to fetch the memory address of a memory location */
    ptr0 = &number;
    /* A pointer pointing to a location storing another memory reference (pointer to pointer) */
    ptr1 = &ptr0;

    /* the asterisk operation [*] is called the "de-reference operator" in C and it is used to fetch the value stored in a memory location from a memory address or a pointer */
    printf("The value of the memory referenced by %p is %d\n", ptr0, *((int*) ptr0));
    printf("The value of the memory referenced by %p is %p\n", ptr1, *((long*) ptr1));
    printf("The value of the memory referenced by %p is %d\n", ptr0, *((int*)*((long*) ptr1)));
    /* changing the value of the memory buffer by dereferencing a memory reference */
    *((int*)*((long*) ptr1)) = 300;
    /* printing the memory location value by dereferencing the second memory reference */
    printf("The value of the memory referenced by %p is %d\n", ptr0, *((int*) ptr0));
    
    /* operations on pointers are covered in the automatic buffer (arrays) section */

    /* create a non-generic pointer -- a pointer with determinate memory type helps in avoiding explicit casting when dereferencing and enhances user readability */
    int* ageneric_ptr = &number;
    /* no explicit casting is needed when dereferencing */
    printf("The value of the memory referenced by %p is %d\n", ageneric_ptr, *ageneric_ptr);
    printf("The value of the memory referenced by %p is %d\n", ageneric_ptr, ageneric_ptr[0]);
    
    /* pointer to pointer is the same as the multidimensional array */
    int** ptr_to_ptr = &ageneric_ptr;
    
    printf("The value of the memory referenced by %p is %d\n", ageneric_ptr, ptr_to_ptr[0][0]);
    
    /* Test by reference V.S. Pass by value */

    printf("Test lifecycle of memory variables %d\n", *pass_by_reference(ageneric_ptr));

    /* Pass by value cannot be utilized outside of the function block */
    /* Further using of the locally defined variables outside of the function block will throw 
       a memory Segmentation Fault indicating faulty memory section */
    printf("Test lifecycle of local variables %d\n", *pass_by_value(240));
}

/**
 * Examines a dirty way of expanding an array.
 * @note This is a hack for demonstration only, please never use on production code.
 * 		 Use the dynamic memory allocation API for these purposes.
 */
void expandables_example() {
	#ifndef __AVR_ATmega32__
		/* tests expandable buffers using array declarators and initializers */
		int* array = (int[]) {10, 20, 30};
		/* copy items to another array before re-initializing it */
		int copy[sizeof(array) + 1];
		for (int i = 0; i < 3; i++) {
			copy[i] = array[i];
		}
		/* re-initialize the array with the copy expanded by an additional element */
		/* the memory of the old automatic allocation will be cleared automatically 
		after returning from this function */
		array = copy;
		/* add new item */
		array[3] = 50;
		printf("Test expanding an automatically allocated array = \n");
		/* print the values for demonstration only */
		for (int i = 0; i < 4; i++) {
			printf("%d\n", array[i]);
		}
	#endif
}

int main() {
	define_array();
	array_operations();
	expandables_example();
	pointers_example();
	return 0;
}
