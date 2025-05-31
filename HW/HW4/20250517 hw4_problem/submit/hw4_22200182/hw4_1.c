/*
Comments to 철호
	- 1번 문제 43번 줄에서 define때문에 헛갈렸다
		- #define WRITE_END 0
		- #define WRITE_END 1
	- 2번 문제 거의 손 못대었다.


Comments to 승주
	- 3번 문제 13번 Free가 아니라 unmap을 해야하였지만, free를 사용하였다.
		- munmap(buffer, sizeof(Buffer)); shm_unlink(name); close(shm_fd);
*/