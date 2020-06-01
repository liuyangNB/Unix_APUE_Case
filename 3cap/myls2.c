/*这个函数想要实现的是 ls-l的功能，要用到stat、group等概念
 *
 *
 * */

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

void do_ls(char[]);//对mou目录做ls
void do_stat(char*);
void show_file_info(char*, struct stat*);
void mode_2_letters(int, char[]);
char* uid_2_name(uid_t);
char* gid_2_name(gid_t);

int main(int ac, char* av[]){
	
	if(ac == 1){
		do_ls(".");
	}else{
		while(--ac){
			printf("%s:\n",*++av);//打印这个目录
			do_ls(*av);
		}
	}
}


void do_ls(char dirname[]){
	DIR* dir_ptr;//文件夹”标志符“
	struct dirent* direntp;//文件夹里面的文件

	if((dir_ptr = opendir(dirname)) == NULL){
		fprintf(stderr,"can not open  %s\n",dirname);
	}else{
		//遍历这个文件夹里面所有文件
		while((direntp = readdir(dir_ptr)) != NULL){
			do_stat(direntp->d_name);//根据文件名打印信息。
		}
		closedir(dir_ptr);
	}
}

void do_stat(char* filename){
	struct stat info;
	if(stat(filename,&info) == -1){
		perror(filename);
	}else{
		show_file_info(filename,&info);
	}
}

void show_file_info(char* filename, struct stat * info_p){
	//需要一些局部函数
	char* uid_2_name(), *gid_2_name(),*filemode();
	void mode_2_letters();
	char modestr[11];

	mode_2_letters(info_p->st_mode,modestr);//根据mode数字转为字符串表述

	printf("%s",modestr);
	printf("%4d ",(int)info_p->st_nlink);//文件的连接数
	printf("%-8s ",uid_2_name(info_p->st_uid));
	printf("%-8s ",gid_2_name(info_p->st_gid));
	printf("%8ld ",(long)info_p->st_size);
	//这里打印时间
	printf("%s\n",filename);
}

/*
 *utility functions
 *
 * */
//这一部分需要去了解stat中的mode
#include<string.h>
void mode_2_letters(int mode, char str[]){
	strcpy(str,"----------");

	if(S_ISDIR(mode)) str[0] = 'd';
	if(S_ISCHR(mode)) str[0] = 'c';
	if(S_ISBLK(mode)) str[0] = 'b';

	if(mode & S_IRUSR) str[1] = 'r';
	if(mode & S_IWUSR) str[2] = 'w';
	if(mode & S_IXUSR) str[3] = 'x';

	if(mode & S_IRGRP) str[4] = 'r';
	if(mode & S_IWGRP) str[5] = 'w';
	if(mode & S_IXGRP) str[6] = 'x';

	if(mode & S_IROTH) str[7] = 'r';
	if(mode & S_IWOTH) str[8] = 'w';
	if(mode & S_IXOTH) str[9] = 'x';
}



#include<pwd.h>
char* uid_2_name(uid_t uid){
	struct passwd* getpwuid(),*pw_ptr;
	static char numstr[10];

	if((pw_ptr = getpwuid(uid)) == NULL){
		sprintf(numstr,"%d",uid);//将int -- str
		return numstr;
	}else{
		return pw_ptr->pw_name;
	}

}

#include<grp.h>
char* gid_2_name(gid_t gid){
	struct group* getgrgid(),*grp_ptr;
	static char numstr[10];

	if((grp_ptr = getgrgid(gid)) == NULL){
		sprintf(numstr,"%d",gid);
		return numstr;
	}else{
	return grp_ptr->gr_name;
	}
}


