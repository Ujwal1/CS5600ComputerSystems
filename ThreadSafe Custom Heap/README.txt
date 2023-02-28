To make the heap thread-safe, we can use a mutex to ensure that only one thread accesses the heap at a time. 

To test that the modified code is thread-safe, we can create multiple threads and have them allocate and free memory simultaneously. We can use a synchronization primitive like a mutex to ensure that only one thread accesses the heap at a time.

Commands to compile and run the program.

>> make all
>> make run

-All this is a part of MSCS CS5600 - Computer Systems at Khoury College, Northeastern University, Boston, MA.
- Author: Ujwal Gupta 
ujwalgupta30@gmail.com