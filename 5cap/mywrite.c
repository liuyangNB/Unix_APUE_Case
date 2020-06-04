/*
 *send message to another terminal
 *
 * */
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(int ac, char* av[]){

	int fd;
	char buf[BUFSIZ];


	/*check args*/
	if(ac != 2){
		fprintf(stderr,"usage:mywrite ttyname\n");
		exit(1);
	}

	/*open device*/
	fd = open(av[1],O_WRONLY);
	if(fd == -1){
		perror(av[1]);
		exit(1);
	}

	/*loop until EOF on output*/
	while(fgets(buf,BUFSIZ,stdin) != NULL){
		if(write(fd,buf,strlen(buf))==-1)
			break;
	}
	close(fd);
	return 0;
}
