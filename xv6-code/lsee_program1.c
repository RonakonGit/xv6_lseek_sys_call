#include"stat.h"
#include"fcntl.h"
#include"types.h"
#include"user.h"
// block 

void string_check(char *filename,int offset,int len ,char *string){
	int fd = open(filename,O_RDONLY);
	int stringlen = 0;
	char tempblock[len+1];
	int lopper1=0;
	
	
	while(string[lopper1] != '\0'){
		stringlen++;
	}
	
	
	lseek(fd,offset,SEEK_CUR); // call lseek
	read(fd,tempblock,len);
	
	// check len
	if(stringlen ==len){
		int lopper2;
		mcount = 0;
		for(lopper2=0;lopper2<len;lopper2++){
			if(string[lopper2] == tempblock[lopper2])//matching strings
				mcount++;
		}
		if(mcount == len) {
		
			printf("Same ");
		}
		else {
			printf("Not same");
		}
	}
	else {
		printf("not Same");
	}
	close(fd);
}

int main(int argc,char *args){
	char *str = "heyyy";
	char *file = args[1];
	string_check(file,10,5,str);
	return 0;
}
