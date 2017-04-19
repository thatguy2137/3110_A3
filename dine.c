/*	Saatvik Bhayana
*	0939774
*	3110 A3
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct{
	int pos, count;
	sem_t *fork, *lock;
}params;

int num_eat;

void think(int pos){
	printf("Philosopher %d is thinking...\n", pos+1);
}
void eat(int pos){
	printf("Philosopher %d is eating...\n", pos+1);
}
void * philo(void* param){
	params self = *(params*)param;

	for (int i = 0; i < num_eat; i++){
		think(self.pos);
		sem_wait(self.lock);
		sem_wait(&self.fork[self.pos]);
		sem_wait(&self.fork[(self.pos+1) % self.count]);
		eat(self.pos);
		sem_post(&self.fork[self.pos]);
		sem_post(&self.fork[(self.pos + 1) % self.count]);
		sem_post(self.lock);
	}
	think(self.pos);
	pthread_exit(NULL);
}

void init(sem_t *lock, sem_t *forks, int fNum){
	for (int i = 0; i < fNum; i++){
		sem_init(&forks[i], 0 , 1);
	}

	sem_init (lock, 0, fNum - 1);
}

void run_all_threads(pthread_t* threads, sem_t * forks, sem_t* lock, int pNum){
	for (int i = 0; i < pNum; i++){
		params* arg = malloc(sizeof(params));
		arg->pos = i;
		arg->count = pNum;
		arg->lock = lock;
		arg->fork = forks;

		pthread_create(&threads[i], NULL, philo, (void*)arg);
	}
}
int main(int argc, char** argv){

	int num_philosophers = atoi(argv[1]);
	num_eat = atoi(argv[2]);
	sem_t lock, forks[num_philosophers];
	pthread_t philos[num_philosophers];

	init(&lock, forks, num_philosophers);
	run_all_threads(philos, forks, &lock, num_philosophers);
	pthread_exit(NULL);
	return 0;

}