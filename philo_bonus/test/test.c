
#include <stdio.h>
#include <semaphore.h>

int main(void)
{
	sem_t *sem;

	sem = sem_open("fork", O_EXCL);
	if (sem == SEM_FAILED)
	{
		printf("fail\n");
		return (1);
	}
	sem_wait(sem);
	printf("ok\n");
	while(1);
	sem_post(sem);
	sem_close(sem);
	sem_unlink("fork");
}
