#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void _find(char* path, char *tar) {
	int fd = open(path, 0);
	if (fd < 0) {
		fprintf(2, "cannot open %s\n", path);
		return;
	}
	
	struct stat st;
	if (fstat(fd, &st) < 0) {
		fprintf(2, "cannot stat %s\n", path);
		close(fd);
		return;
	}
	
	if (st.type == T_FILE) {
		char* p = path + strlen(path);
		while (p >= path && *p != '/') --p;
		++p;
		if (strcmp(p, tar) == 0) {
			printf("%s\n", path);
		}
		close(fd);
		return;
	} else if(st.type == T_DIR) {
		struct dirent de;
		while (read(fd, &de, sizeof(de)) == sizeof(de)) {
			if (de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) continue;//??? what read() gets, why "." ".."
			char* p = path + strlen(path);
			*p = '/';
			strcpy(p + 1, de.name);
			_find(path, tar);
			*p = 0;
		}
	}
	close(fd);
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("input error\n");
		exit(0);
	}
	char path[512];
	strcpy(path, argv[1]);
	_find(path, argv[2]);
	exit(0);
}
