/*
 * 关于原理看书好了，无非是去utmp文件读utmp.h里的结构体数据，然后显示
 *
 */
#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>	//open
#include <unistd.h>	//close read
#include <stdlib.h>
#define SHOWHOST	//???

void show_info(struct utmp* recode);

int main(){
	struct utmp  curent_recode;
	int utmpfd;
	int reclen = sizeof(curent_recode);

	if( (utmpfd = open(UTMP_FILE,O_RDONLY)) == -1){
		perror(UTMP_FILE);
		exit(1);
	}

	while( read(utmpfd,&curent_recode,reclen)== reclen)
		show_info(&curent_recode);
	close(utmpfd);
	return 0;
}


void show_info(struct utmp* recode){
	printf("name: %-8.8s", recode->ut_name);
	printf(" ");

	printf("tty: %-8.8s", recode->ut_line);
        printf(" ");

	printf("processid: %-8.8s",recode->ut_id);
	printf(" ");

#ifdef SHOWHOST
	printf("(%s)",recode->ut_host);
#endif
	printf("\n");
	

}
