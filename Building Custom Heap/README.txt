The pm_heap program is a simple implementation of a memory allocator in C language. It provides two functions, pm_malloc and pm_free, that can be used to dynamically allocate and free memory from a pre-allocated heap.

The program defines a pm_block_t struct that represents a block of memory in the heap. Each block contains a pointer to the start of the block, the size of the block, and a flag indicating whether the block is free or in use.

The pm_heap_init function initializes the heap by setting up the first block to cover the entire heap and marking it as free.

The pm_malloc function searches through the list of blocks to find a free block with enough space to allocate the requested memory. If a block is found, it is marked as in use, and if there is enough remaining space in the block, a new free block is created to cover the remaining space.

The pm_free function finds the block corresponding to a given pointer and marks it as free. If adjacent blocks are also free, they are coalesced into a single larger free block.

To use the pm_heap program, you need to include the pm_heap.h header file in your source code, and link the pm_heap.c file with your program. The pm_heap.h header file defines the pm_heap_init, pm_malloc, and pm_free functions.

To run the pm_heap_test program, you can compile it with the provided makefile by running the make command. This will compile both the pm_heap.c and pm_heap_test.c files and link them together to create the pm_heap_test executable. You can then run the program by executing the ./pm_heap_test command. The program will run a series of tests to verify the correctness of the pm_malloc and pm_free functions.

Commands to compile and run the program.

>> make all
>> make run

-All this is a part of MSCS CS5600 - Computer Systems at Khoury College, Northeastern University, Boston, MA.
- Author: Ujwal Gupta 
ujwalgupta30@gmail.com
