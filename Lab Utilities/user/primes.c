#include "kernel/types.h"
#include "user/user.h"


void helper(int* p, int cnt) {
	if (cnt == 1) {
		printf("prime %d\n", *p);
		exit(0);
	}
	int curr = *p;
	printf("prime %d\n", curr);
	int fd[2];
	pipe(fd);
	
	if (fork() == 0) {
		close(fd[1]);
		int i = 0;
		while (read(fd[0], &p[i], sizeof(int)) != 0) {
			++i;
		}
		close(fd[0]);
		helper(p, i);
	} else {
		close(fd[0]);
		for (int i = 1; i < cnt; ++i) {
			if (*(p + i) % curr == 0) continue;
			write(fd[1], p + i, sizeof(int));
		}
		close(fd[1]);
		wait((int *) 0);
	}
	exit(0);
}

int main() {
	int nums[34];
	for (int i = 0; i < 34; ++i) nums[i] = i + 2;
	helper(nums, 34);
	return 0;

}
