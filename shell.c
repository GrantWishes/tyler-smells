#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_INPUT (513) // 512 characters + carriage return

void error() {
	/* The one true error message. */
	char error_message[30] = "An error has occured\n";
	write(STDERR_FILENO, error_message, strlen(error_message));
}

char **parse(char arguments[], size_t size) {
	/* the array of commands and args
	   char array filled with char arrays so it's ** */	
	char **words = (char **) malloc(size);
	char *ptr = NULL;


	
	// TYLER'S GARBAGE CODE STARTS HERE
	
	char *myPtr = NULL; // the > substring we're looking for
        bool validOutputCommand = false; // boolean to determine whether > is valid
	myPtr = strstr(arguments, " >"); // is > present? Well if it is then gg
	int count;
	bool arrowActive;
        char *myPtr2 = NULL;
	if (myPtr != NULL) {
	  printf("You made it to the > branch\n");
	  myPtr2 = strtok(arguments, " >"); // split the string at the > marker
	  count = 0; // Initialize count to be 0
	  while (myPtr2 != NULL) { // while the second pointer has a value, keep incrementing count
	    count += 1;
	    myPtr2 = strtok(NULL, " >");
	  }
	  if (count == 2) { // At this point, count needs to equal 2 otherwise there were too many ">" marks
	    printf("You made it this far\n");
	    myPtr2 = strtok(arguments, " "); // split the string at spaces
	    arrowActive = false; //arrowActive boolean is currently set to false
	    while (myPtr2 != NULL) {
	      // if the arrow has already been passed then we need to increment count to keep track of args after it
	      if (arrowActive) {
		count += 1;
	      }
	      // active the arrow boolean if we have encountered the arrow in the line
	      else if (strcmp(myPtr2, " >") == 0) {
		count = 0;
		arrowActive = true;
	      }
	      myPtr2 = strtok(NULL, " ");
	    }
	    // if there was only one argument after it, then the Redirection command is valid
	    if (count = 1) {
	      validOutputCommand = true;
	      printf("OMFG IT WORKED!!!!\n");
	    }
	  }
	}

	// END TYLER'S GARBAGE CODE

	
	
	/* pointer to each individual word */
	ptr = strtok(arguments, " ");
	
	int i = 0;		//this variable taught me about undefined behavior
	char* pyPtr;		//the substring we're looking for
	pyPtr = strstr(ptr, ".py\0");
	/*if it's a python file, we gotta do something diff */
	if (pyPtr != NULL) {
	  i = 1;
	  words[0] = "python";
        }
	/* error checking */
	if (words == NULL) {				
		perror("words mem"); // delete at end
		error();
	}

	/* for empty or only space strings, makes it work properly */
	if(ptr == NULL){
		words[0] = "";
		return words;
	}
	/* adding the words to the array */
	
	
	for (i; ptr != NULL; i++) {
		words[i] = ptr;
		ptr = strtok(NULL, " ");
	}

	//	Debug print
//	for(int j = 0; words[j] != NULL; j++) {
//		printf("Word: %s\n", words[j]);
//
//	}
	return words;
}

int main(int argc, char *argv[]) {

	char input[MAX_INPUT];	// for the input string
	char **args;		// for the command and arguments parsed
	char pwd[MAX_INPUT*2];	// for the pwd functionality, size seemed common

	

	while(1) {
		// the shell print	
		printf("mysh> ");
		// read in from standard input
		if(fgets(input,sizeof(input),stdin) == NULL) {
			error();
		}
		if((strlen(input) == (MAX_INPUT-1)) && (input[MAX_INPUT] != '\0')) {
			error();
			int temp;
			while(temp = fgetc(stdin) != '\n' && temp != EOF);
			continue;
		}


		// black magic code that gets rid of a stupid newline character
		input[strcspn(input,"\n")] = '\0';
		args = parse(input,sizeof(input));
		// exits the shell	
		if(strcmp(args[0],"exit") == 0) {
			exit(0);
		}
		
		// prints working directory
		else if(strcmp(args[0],"pwd")==0) {
			if(getcwd(pwd,sizeof(pwd)) != NULL) {
				printf("%s\n", pwd);
			}
			else {
				error();
			}
		}
		else if(strcmp(args[0],"cd")==0) {
			if(args[1] == '\0') {
				chdir(getenv("HOME"));		
			}
			else {
				int c;
				if(c = chdir(args[1]) < 0) {
					error();
				}
			}
		}
		else if(strcmp(args[0], "") == 0) {
			continue;
		}
		else {
			pid_t pid = fork();   //i accidentally fork bombed here
			int status;
			
			if(pid < 0) {
				error();
			}
			else if(pid == 0) {
				if(execvp(args[0],args) < 0) {
					error();
					exit(1);
				}
			}

			else {
				while(wait(&status)!=pid) ;
			}
		}
	



		args[0] = '\0';			// clears the array
	}

	return 0;
	
}
