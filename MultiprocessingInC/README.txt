Run the following commands to run the main():

>> make all
>> ./runMultiprocessing

make all makes the executable for both main and cypher. The executable of cipher is inturn used 
in the main.c
Run the 'runMultiprocessing' file to run the program.

- or each token from the text file, I am saving its cipher in a separate text file. 

- The 'outputDirectory' contains all the files generated after creating ciphers using the executable of the 
cipher program.

- The 'outputDirectoryThread' contains all the files generated after creating ciphers using the functions of the 
polybius program and running each on a separate thread.

- Everytime the program tries to save the outputs from a run, it recursively deletes these directories containing
data from the past run and the creates new directories and adds relevant .txt files to them.

- The naming convention for output file in both of the directories is : "output" + token_id + ".txt"

To verrify the program against your own inputs, you may alter the data in the 'dataFile.txt' which is our
input data source file, run the program and then verify the no of file, ciphers, etc in the output directories.

