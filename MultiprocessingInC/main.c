/*
 * main.c
 *
 *  Created on: Feb 7, 2023
 *      Author: ujwal
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "polybius.h"

#define OUTPUT_DIRECTORY "/outputDirectory/"

#define BUFSIZE 1024

char table[5][5] = {{'A', 'B', 'C', 'D', 'E'},
{'F', 'G', 'H', 'I', 'K'},
{'L', 'M', 'N', 'O', 'P'},
{'Q', 'R', 'S', 'T', 'U'},
{'V', 'W', 'X', 'Y', 'Z'}};

struct ThreadData {
	int index;
	char *token;
};

void* encryption(void *data) {
	struct ThreadData threadData = *((struct ThreadData *)data);
	int i = threadData.index;
	char *token = threadData.token;
	char fileName[100];
	snprintf(fileName, sizeof(fileName), "./outputDirectoryThread/output%d.txt", i);

	char *ciphertext = pbEncode(token, table);
	FILE *fp = fopen(fileName, "w");
	if (!fp) {
		perror("fopen");
		return (void*)1;
	}
	fprintf(fp, "%s", ciphertext);
	fclose(fp);
	free(ciphertext);
	return (void*)0;
}


/**
 * Takes a .txt filename as an argument.
 *
 * Returns 0 is everything works perfectly.
 * Returns 1 if opening any file fails.
 * Returns 2 if the filename provided to the function as the argument is a file that is empty.
 * Returns 3 if the cipher program executlable file is not found while trying to generate
 * 		the ciphers using it.
 */
int cipherizeFile(char* filename) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *token;
    const char *delim = ".?!\n";

    char *tokens_array[100];
    int token_count = 0;

//    fp = fopen("dataFile.txt", "r");
    fp = fopen( filename , "r");
    if (fp == NULL)
    {
        return 1;
    }

    int i = 0;

    //tokenising the sentences
    while ((read = getline(&line, &len, fp)) != -1)
    {
        token = strtok(line, delim);
        while (token != NULL)
        {
            tokens_array[token_count++] = strdup(token);
            token = strtok(NULL, delim);
        }
    }

    fclose(fp);
    if (token_count == 0) {
    	return 2;
    }

    printf("Printing the tokenized sentences\n");
    // Print the tokenized sentences
	for (int i = 0; i < token_count; i++) {
		printf("Token %d: %s\n", i, tokens_array[i]);
	}


	// recursive remove the directory containing the outfiles(if there exists) from the past runs of the program.
	// and then make a new empty directory for outputs
	system("if [ -d \"outputDirectory\" ]; then rm -r outputDirectory; fi");
	system("mkdir outputDirectory");


	printf("\nNow beginning to create ciphers of the tokens using runnable of the cipher file.\n");
	// declaring a char array for storing the command to use the runnable from cypher program to encrypt the sentence
	char command[1000];
	FILE *fp_arr[token_count];
	for(int i = 0; i < token_count; i++) {
		// create a new file with a unique name, open it in write mode and have the file pointer point at it.
		char fileName[100];
		snprintf(fileName, sizeof(fileName), "./outputDirectory/output%d.txt", i);
		fp_arr[i] = fopen(fileName, "w");
		if (!fp_arr[i]) {
		  perror("fopen");
		  return 1;
		}

		// Create the command to call the cipher program. Using the executable from the cipher program to encrypt.
		snprintf(command, sizeof(command) ,"./cipher -e \"%s\"", tokens_array[i]);
		fp = popen(command, "r");
		if(!fp) {
			perror("popen");
			return 3; //cipher command not found
		}
		while(fgets(command, sizeof(command), fp)) {
			fputs(command, fp_arr[i]);
		}
		fclose(fp);

	}


	printf("\nNow beginning to create ciphers of the tokens using threads.\n");

	// recursive remove the directory containing the outfiles(if there exists) from the past runs of the program.
	// and then make a new empty directory for outputs -- ALL IN CASE OF FILE GENERATION USING THREADS
	system("if [ -d \"outputDirectoryThread\" ]; then rm -r outputDirectoryThread; fi");
	system("mkdir outputDirectoryThread");


	pthread_t threads[token_count];
	struct ThreadData data[token_count];

	for(int i = 0; i < token_count; i++) {
	    data[i].index = i;
	    data[i].token = tokens_array[i];

	    int rc = pthread_create(&threads[i], NULL, encryption, (void*)&data[i]);
	    if (rc) {
	        perror("pthread_create");
	        return 1;
	    }
	}

	// wait for all the created threads to have finished their tasks before the function returns.
	for (int i = 0; i < token_count; i++) {
	    pthread_join(threads[i], NULL);
	}

	return 0;
}

int main()
{
	int status;


	printf("Stating the task of generating the ciphers from the tokens of an empty file");
	//testing for an empty file.
	status = cipherizeFile("emptyFile.txt");
	if (status == 0) {
		printf("\nThe task of generating ciphers for the text in the file was succcessful.\n");
	}
	else if(status == 1) {
		printf("\nUnable to open some file\n");
	}
	else if (status == 2) {
		printf("\nThe file provided is empty\n");
	}
	else if(status == 5) {
		printf("\nThe cipher program executable is not found.\n");
	}

	printf("\nPress any key to continue to check for an empty file");
	getchar();


	printf("Stating the task of generating the ciphers from the tokens of a file that contains over"
			"30 sentences");
	status = cipherizeFile("dataFile.txt");
	if (status == 0) {
		printf("\nThe task of generating ciphers for the text in the file was succcessful.\n");
	}
	else if(status == 1) {
		printf("\nUnable to open some file\n");
	}
	else if (status == 2) {
		printf("\nThe file provided is empty\n");
	}
	else if(status == 5) {
		printf("\nThe cipher program executable is not found.\n");
	}


	printf("Exiting out of main. Bye!");
    return 0;
}
