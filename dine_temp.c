/* TEST CODE, KEEPING FOR REFERENCE PLEASE IGNORE
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct philo{
	int pos;
	int count;
	sem_t* forks;
	sem_t* lock;
}philo;

int eNum;

/*void * philos(void* params){

	philo temp = *(philo*)params;

	for(int i = 0; i < eNum; i++){
		printf("Philosopher %d is thinking...\n", temp.pos+1);

		sem_wait(temp.lock);
		sem_wait(&temp.forks[temp.pos]);
		sem_wait(&temp.forks[(temp.pos+1) % temp.count]);
		printf("Philosopher %d is eating...\n", temp.pos+1);
		sem_post(&temp.forks[temp.pos]);
		sem_post(&temp.forks[(temp.pos + 1) & temp.count]);
		sem_post(temp.lock);
	}

	printf("Philosopher %d is thinking...", temp.pos+1);
	pthread_exit(NULL);

}*/

void * philos(void * params){
    int i;
    philo self = *(philo*)params;
    
    for(i = 0; i < eNum; i++){
		printf("Philosopher %d is thinking...\n", self.pos+1);
        
        sem_wait(self.lock);
        sem_wait(&self.forks[self.pos]);
        sem_wait(&self.forks[(self.pos+1) % self.count]);
		printf("Philosopher %d is eating...\n", self.pos+1);
        sem_post(&self.forks[self.pos]);
        sem_post(&self.forks[(self.pos + 1) % self.count]);
        sem_post(self.lock);
    }
    
	printf("Philosopher %d is thinking...\n", self.pos+1);
    pthread_exit(NULL);
}


void initP(sem_t * lock, sem_t * forks, int pNum){
	for (int i = 0; i < pNum; i++){
		sem_init(&forks[i], 0 , 1);
	}

	sem_init(lock, 0, pNum-1);
}

int main(int argc, char* argv[]){
	
	int pNum;
	pNum = atoi(argv[1]);
	eNum = atoi(argv[2]);

	sem_t lock;
	sem_t forks[pNum];
	pthread_t phils[pNum];

	initP(&lock, forks, pNum);


	for (int i = 0; i < pNum; i++){

		philo * temp =  malloc(sizeof(philo));
		temp->pos = i;
		temp->count = pNum;
		temp->forks = forks;
		temp->lock = &lock;

		pthread_create(&phils[i], NULL, philos, (void*)temp);
	}

}