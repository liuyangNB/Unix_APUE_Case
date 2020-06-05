/*playagain1.c
 *加入了即时响应，配置tty
 *加入了 忽略非法键
 *加入了 非阻塞模式实现超时响应
 * purpose:	ask if users wants another transaction
 * method:	ask a question,wait for yes/no answer
 * trturn:	0 for yes/1 for no
 *
 * */

#include<stdio.h>
#include<termios.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

#define QUESTION "Do you want another transaction?"
#define TRIES 3
#define SLEEPTIME 2
#define BEEP putchar('\a')

int get_response(char*,int);
void tty_mode();
void set_cr_noecho_mode();
void set_nodelay_mode();
int get_ok_char();
int main(){
	int response;
	tty_mode(0);//save mode
	set_cr_noecho_mode();
	set_nodelay_mode();
	response = get_response(QUESTION,TRIES);
	tty_mode(1);//restore tty state
	return response;
}

int get_response(char*question,int maxtries){
	int input;
	printf("%s (y/n)",question);
	fflush(stdout);//force output
	while(1){
		sleep(SLEEPTIME);
	//	input = tolower(get_ok_char());
		
		input = get_ok_char();
		if(input == 'y') return 0;
		if(input == 'n') return 1;
		if(maxtries-- ==0) return 2;
		BEEP;
	}
}


int get_ok_char(){
	int c;
	while((c = getchar()) != EOF && strchr("yYnN",c) == NULL);//停止条件
	return c;
}


/*purpose:	put file descriptor  0 (i.e. stdin) into char-by-char mode
 * method:	use bits in termios
 *
 * */
void set_cr_noecho_mode(){
	struct termios ttystate;
	tcgetattr(0,&ttystate);
	ttystate.c_lflag &=~ICANON;//no buffering
	ttystate.c_lflag &=~ECHO;//no echo
	ttystate.c_cc[VMIN] = 1;//get 1 char at a time
	tcsetattr(0,TCSANOW,&ttystate);//install setting
}


void set_nodelay_mode(){
	int termflags;
	termflags = fcntl(0,F_GETFL);
	termflags |= O_NDELAY;
	fcntl(0,F_SETFL,termflags);
}

void tty_mode(int how){
	static struct termios original_mode;
	static int origin_flags;
	if(how == 0){
		tcgetattr(0,&original_mode);
		origin_flags = fcntl(0,F_GETFL);
	}else{
		tcsetattr(0,TCSANOW,&original_mode);
		fcntl(0,F_SETFL,origin_flags);
	}
}
