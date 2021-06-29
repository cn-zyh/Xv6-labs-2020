#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char* argv[]) {
	
	char* xargv[MAXARG];
	int xargc = 0;
	while ((xargv[xargc] = argv[xargc + 1]) != 0) {
		++xargc;
	}
	
	char buf[MAXARG][32];
	int row = 0, col = 0;
	int j = xargc;

	while (read(0, &buf[row][col], sizeof(char))) {
		if (buf[row][col] == '\n') {
			buf[row][col] = 0;
			xargv[j++] = &buf[row][0];
			xargv[j] = 0;
			if (fork() == 0) {
				exec(xargv[0], xargv);
				exit(0);
			}
			else {
				wait((int*)0);
				row = 0;
				col = 0;
				j = xargc;
			}
			
		}
		else if (buf[row][col] == ' ') {
			buf[row][col] = 0;
			xargv[j++] = &buf[row][0];
			++row;
			col = 0;
		}
		else {
			++col;
		}
	}
	exit(0);

}
