/*
 *a tyne user app: a->b b->c ...z->a
 *used to show tty mode
 * */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main(){
	int c;
	while( (c = getchar()) != EOF){
		if(c == 'z') c = 'a';
		else if( islower(c)) c++;
		putchar(c);
	}
	return 0;
}
