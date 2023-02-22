>> make all
>> make run

make all compiles Main.java and BoundedBuffer.java to bytecode(.class) that can be executed by JVM.
make run runs the Main().

 - Main() is a multi-threaded program in Java that inserts strings of the form ThreadID-RandomNumber (e.g., 23-77483) into the Bounded Buffer (BoundedBuffer.java) above.
 - The random numbers must be 5 digits. You must create at least three concurrent threads, and each must insert at least 30 random number strings into the buffer. 
- This simulates a bounded buffer that collects data from a sensor network of IoT devices. 
