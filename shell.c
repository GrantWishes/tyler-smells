#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>

#define MAX_INPUT (512)

void error() {
	char error_message[30] = "An error has occured\n";
	write(STDERR_FILENO, error_message, strlen(error_message));
}


int main(int argc, char *argv[]) {
	char input[MAX_INPUT];
	while(1) {
		printf("mysh> ");
		fgets(input,MAX_INPUT,stdin);		
		printf("You inputted: %s\n", input);


	






	}



}
