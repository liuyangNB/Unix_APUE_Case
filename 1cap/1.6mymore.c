#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE* fp);
int see_more();


/*
 *主要还是业务逻辑：	当只有more就针对stdin进行more
 			当后面跟随了多个文件，就分别对其more
 *
 * */
int main(int ac, char* av[]){
	FILE* fp;

	if(ac == 1){
		/*
		 *用于管道操作，ls | more，其中ls的内容作为more的输入，而这里more没有其他参数 
		 * */
		do_more(stdin);
	}else{
		while(--ac){
		/*when you have more than 1 file charector you whill show them all
		 * */
			if((fp = fopen(* ++av,"r")) != NULL){
				do_more(fp);
				fclose(fp);
			}else{
				exit(1);
			}
		}
	}
	
}


/**
 *主逻辑： do_more 具体的操作
	读PAGELEN行内容，然后等待see_more的操作
 */

 void do_more(FILE* fp){
 	char line[LINELEN];//define a arr to store line
	int num_of_lines = 0;
	int see_more(),reply;
	while(fgets(line,LINELEN,fp)){
		//出口，读完规定的行数
		if(num_of_lines == PAGELEN){
			reply = see_more();//等待下一步操作,再看几行
			if(reply == 0){
				break;
			}
			num_of_lines -=reply;
		}
		//显示每行
		if( fputs(line,stdout) == EOF){

			printf("\n------这里因该输出一行---\n");
			exit(1);
		}

		num_of_lines++;

	}
 }


int see_more(){
	/*
	 *等待一些用户的操作
	 * */
	int c;
	printf("\033[7m more? \033[m");

	while((c = getchar()) != EOF){
		if(c == 'q') return 0;
		if(c == ' ') return PAGELEN;//如果是空格，那就是下一页，也会是重新看PAGELEN行
		if(c == '\n') return 1;
	}
	return 0;
}


