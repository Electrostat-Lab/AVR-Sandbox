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
	
	printf("*********************************** Array Declarators with instant initializer ***********************************\n");
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
	printf("*********************************** Multi-dimensional arrays with late initialization ***********************************\n");
	// 1st dimension = ['P'-'a'-'v'-'l'-'y'], 2nd dimension = ['G'-'e'-'r'-'g'-'e'-'s']
	/* declare a buffer of [2 * 8 * 1] = 16 bytes */
	char name_elements[2][9] = {{'P', 'a', 'v', 'l', 'y', '\0'}, {'G', 'e', 'r', 'g', 'e', 's', '\0'}};
	for (int i = 0; i < 2; i++) {
		if (i == 0) {
			printf("First name = ");
		} else {
			printf("Second name = ");
		}
		for (int j = 0; j < 8; j++) {
			printf("%c", name_elements[i][j]);
		}
		printf("\n");
	}

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
	return 0;
}
