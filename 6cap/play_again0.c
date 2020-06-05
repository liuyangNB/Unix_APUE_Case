/*playagain.c
 *
 * purpose:	ask if users wants another transaction
 * method:	ask a question,wait for yes/no answer
 * trturn:	0 for yes/1 for no
 *
 * */

#include<stdio.h>
#include<termios.h>

#define QUESTION "Do you want another transaction?"

int get_response(char*);

int main(){
	int response;
	response = get_response(QUESTION);
	return response;
}

int get_response(char*question){
	printf("%s (y/n)",question);
	while(1){
		switch(getchar()){
			case 'y':
			case 'Y': return 0;
			case 'n':
			case 'N': return 1;
			case EOF:return 1;
		}
	}
}
