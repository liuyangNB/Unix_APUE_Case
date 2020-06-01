#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>

ino_t get_inode(char*);//在目录表根据文件名返回对应的inode
void print_path_to(ino_t);
void inum_to_name(ino_t,char*, int);


int main(){
	print_path_to(get_inode("."));//从当前的目录的"."开始找
	putchar('\n');
	return 0;
}

//用递归方法写
void print_path_to(ino_t thisnode){
	ino_t my_inode;
	char its_name[BUFSIZ];
	if(get_inode("..")!= thisnode){
		chdir("..");
		inum_to_name(thisnode,its_name,BUFSIZ);//获得当前节点的名字到buf
		my_inode = get_inode(".");
		print_path_to(my_inode);//
		printf("/%s",its_name);
	}
}

//当前目录下，根据inot查找名字
void inum_to_name(ino_t inodetofind, char* namebuf, int buflen){

	DIR* dir_ptr;
	struct dirent* direntp;
	dir_ptr = opendir(".");
	if(dir_ptr == NULL){
		perror(".");
		exit(1);
	}
	
	//遍历当前文件夹的文件inode
	while((direntp = readdir(dir_ptr)) != NULL ){
		if(direntp ->d_ino == inodetofind){
			strncpy(namebuf,direntp->d_name,buflen);
			namebuf[buflen-1] = '\0';//以防万一
			closedir(dir_ptr);
			return;
		}
	}

	fprintf(stderr,"error looking for inum:%ld",inodetofind);
	exit(1);

}


ino_t get_inode(char* fname){
	struct stat info;
	if(stat(fname,&info) == -1){
		fprintf(stderr,"can not stat");
		perror(fname);
		exit(1);
	}

	return info.st_ino;
}
