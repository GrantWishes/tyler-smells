#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>

#define MAX_INPUT (513) // 512 characters + carriage return

char *outFile = NULL;

void error() {
	/* The one true error message. */
	char error_message[30] = "An error has occured\n";
	write(STDERR_FILENO, error_message, strlen(error_message));
}

void batch


char **parse(char arguments[], size_t size) {
	/* the array of commands and args
	   char array filled with char arrays so it's ** */	
	char **words = (char **) malloc(size);
	char *ptr = NULL;


	
	// TYLER'S GARBAGE CODE STARTS HERE

//	char argCopy[strlen(arguments)];
//	strcpy(argCopy, arguments);
//	char *myPtr = NULL; // the > substring we're looking for
//        bool redirect; // boolean to determine whether > is valid
//	myPtr = strstr(arguments, ">"); // is > present? Well if it is then gg
//	int count; // initialize a count variable, will be used later
//	bool arrowActive; // this boolean keeps track of when we hit a ">"
  //      char *myPtr2 = NULL; // initialize a ptr
//	char *myPtr3 = NULL; // initialize another ptr
//	if (myPtr != NULL) {
//	  myPtr2 = strtok(argCopy, ">"); // split the string
//	  // at the > marker
//	  count = 0; // Initialize count to be 0
//	  while (myPtr2 != NULL) { // while the second pointer has
//	    // a value, keep incrementing count
//	    count++ ;
//	    myPtr2 = strtok(NULL, ">");
//	  }
//	  if (count == 2) { // At this point, count needs to equal
//	    // 2 otherwise there were too many ">" marks
//	    strcpy(argCopy,arguments);
//	    myPtr3 = strtok(argCopy, " "); // split the string at spaces
//	    arrowActive = false; //arrowActive boolean is currently set to false
//	    count = 0;
//	    while (myPtr3 != NULL) {
//	      // if the arrow has already been passed then we need to
//	      // increment count to keep track of args after it
//	      if (arrowActive) {
//		count++;
//	      }
//	      // active the arrow boolean if we have encountered the arrow in
//	      // the line
//	      if (strcmp(myPtr3, ">") == 0) {
//		arrowActive = true;
//	      }
//	      myPtr3 = strtok(NULL, " ");
//	    }
//	    // if there was only one argument after it, then the Redirection
//	    // command is valid
//	    if (count == 1) {
//	      redirect = true;
//	      printf("Redirection flag raised\n");
//	    }
//	    else {
//	      redirect = false;
//	    }
//	  }
//	}

	// END TYLER'S GARBAGE CODE
	// grant's garbo code here
	
	bool redirect = false;
	if(strstr(arguments,">") != NULL) {
		redirect = true;
//		int counter = 0;
//		for(int i = 0; i<strlen(arguments); i++){
//			if(arguments[i] == '>') {
//				counter++;
//			}
//		}
//		if(counter == 1) {
//			redirect = true;
//			printf("Yeah, this works\n");
//		}
	}		

	// grant's garbo ends here
	
	
	/* pointer to each individual word */
	ptr = strtok(arguments, "> ");

	/* for empty or only space strings, makes it work properly */
	if(ptr == NULL){
		words[0] = "";
		return words;
	}


	
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

	/* adding the words to the array */
	
	for (i; ptr != NULL; i++) {
//		printf("Adding \"%s\" to index %d\n", ptr, i);
		words[i] = ptr;
		ptr = strtok(NULL, "> ");
		if(ptr == NULL) {
			if(redirect == true) {
				//printf("Output file is %s\n", words[i]);
				outFile = strdup(words[i]);
				words[i] = '\0';
				break;
			}
		}
	}

	//	Debug print
	for(int j = 0; words[j] != NULL; j++) {
		printf("Word: %s\n", words[j]);

	}
	return words;
}

int main(int argc, char *argv[]) {

	char input[MAX_INPUT];	// for the input string
	char **args;		// for the command and arguments parsed
	char pwd[MAX_INPUT*2];	// for the pwd functionality, size seemed common

	for(int i = 0; i < argc; i++) {
		//printf("Argument: %s\n", argv[i]);
	}

	while(1) {
		/* The shell prompt */	
		printf("mysh> ");
		/* read in from standard input */
		if(fgets(input,sizeof(input),stdin) == NULL) {
			error();
		}

		/* If the input is too large takes up 512 bytes with no termination
  		   we just eat the remaining input into temp			 */
		if((strlen(input) == (MAX_INPUT-1)) && (input[MAX_INPUT] != '\0')) {
			error();
			int temp;
			while(temp = fgetc(stdin) != '\n' && temp != EOF);
			continue;
		}


		/* black magic code that gets rid of a stupid newline character */
		input[strcspn(input,"\n")] = '\0';

		/* get our arguments in an array form */
		args = parse(input,sizeof(input));

		//printf("Output file is %s\n", outFile);

		/* Exit command */	
		if(strcmp(args[0],"exit") == 0) {
			exit(0);
		}
		
		/* print working directory command */
		else if(strcmp(args[0],"pwd")==0) {
			if(getcwd(pwd,sizeof(pwd)) != NULL) {
				if(outFile != NULL) {
					int out = dup(1);
					close(STDOUT_FILENO);
					int file = open(outFile, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
					if(file < 0) {
						error();
						continue;
					}	
					printf("%s\n",pwd);
					close(file);
					dup2(out, STDOUT_FILENO);
				}
				else {
				printf("%s\n", pwd);
				}
			}
			else {
				error();
			}
		}
		/* change directory command */
		else if(strcmp(args[0],"cd")==0) {
			// if no directory, go to home
			if(args[1] == '\0') {
				chdir(getenv("HOME"));		
			}
			// otherwise, go to the directory specified
			else {
				int c;
				if(c = chdir(args[1]) < 0) {
					error();
				}
			}
		}
		/* Handles empty inputs */
		else if(strcmp(args[0], "") == 0) {
		}
		/* If it's not one of these (or wait), try execvp */
		else {
			pid_t pid = fork();   //i accidentally fork bombed here
			int status;
			
			if(pid < 0) {
				error();
			}
			/* The child process runs the command */
			else if(pid ==  0) {
				if(outFile != NULL) {
					close(1);
					int fd = open(outFile, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
					if(fd < 0) {
						error();
						exit(1);
					}

					if(execvp(args[0],args) < 0) {
						error();
						exit(1);	
					}
				}



				else if(execvp(args[0],args) < 0) {
					error();
					exit(1);
				}
			}
			/* The parent process waits on the child */
			else {
				while(wait(&status)!=pid);
			}
		}
	


		/* clears the array for the next batch of arguments */
		args[0] = '\0';		
		outFile = NULL;	
	}

	return 0;
	
}
