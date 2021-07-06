#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]) {

	char buff[64];
	int p1[2], p2[2];
	pipe(p1);
	pipe(p2);
	
	if (fork() == 0){
		close(p1[1]);
		close(p2[0]);
		
		read(p1[0], buff,4);
		
		printf("%d: received %s\n", getpid(), buff);//": "
		
		write(p2[1], "pong", strlen("pong"));

	} else {
		close(p1[0]);
		close(p2[1]);
		
		write(p1[1], "ping", strlen("ping"));
		
		read(p2[0], buff, 4);
		
		printf("%d: received %s\n", getpid(), buff);

	}	
	
	exit(0);


}
