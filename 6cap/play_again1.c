/*playagain1.c
 *加入了即时响应，配置tty
 * purpose:	ask if users wants another transaction
 * method:	ask a question,wait for yes/no answer
 * trturn:	0 for yes/1 for no
 *
 * */

#include<stdio.h>
#include<termios.h>

#define QUESTION "Do you want another transaction?"

int get_response(char*);
void tty_mode();
void set_crmode();
int main(){
	int response;
	tty_mode(0);//new add
	set_crmode();//new add
	response = get_response(QUESTION);
	tty_mode(1);//new add
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

/*purpose:	put file descriptor  0 (i.e. stdin) into char-by-char mode
 * method:	use bits in termios
 *
 * */
void set_crmode(){
	struct termios ttystate;
	tcgetattr(0,&ttystate);
	ttystate.c_lflag &=~ICANON;//no buffering
	ttystate.c_cc[VMIN] = 1;//get 1 char at a time
	tcsetattr(0,TCSANOW,&ttystate);//install setting
}

void tty_mode(int how){
	static struct termios original_mode;
	if(how == 0){
		tcgetattr(0,&original_mode);
	}else{
		tcsetattr(0,TCSANOW,&original_mode);
	}
}
