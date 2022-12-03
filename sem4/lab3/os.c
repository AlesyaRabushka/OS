#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
# include <unistd.h>


#define PHILOSOPHERS 5
#define FORKS 5

pthread_t  philosophers[PHILOSOPHERS];
pthread_mutex_t forks[FORKS];




void dine(int i){
	int count = 0;
	//while(1==1){
	
    // philosopher starts thinking about LIFE
    printf("Philosopher %d is thinking\n", i+1);
    
    if (i + 1 == 1){
        // philosopher picks LEFT fork
        pthread_mutex_lock(&forks[i]);
        //printf("take fork %d\n", i+1);

        // philosopher picks RIGHT fork
        pthread_mutex_lock(&forks[FORKS-1]);
        //printf("take fork %d\n", FORKS);
        // when philosopher picks up two forks he starts eating
        printf("\tPhilosopher %d is dining with ", i+1);
        printf("forks %d and %d\n", i+1, FORKS);

        sleep(10);
    } else{
        // philosopher picks LEFT fork
        pthread_mutex_lock(&forks[i-1]);
        //printf("%d take fork %d\n", i+1, i);

        // philosopher picks RIGHT fork
        pthread_mutex_lock(&forks[i]);
        //printf("%d take fork %d\n", i+1, i+1);

        // when philosopher picks up two forks he starts eating
        printf("\tPhilosopher %d is dining with ", i+1);
        printf("forks %d and %d\n", i, i+1);
	sleep(10);
    }



    // after eating
    if (i + 1 == 1){
        // philosopher puts down LEFT fork
        pthread_mutex_unlock(&forks[i]);

        // philosopher puts down RIGHT fork
        pthread_mutex_unlock(&forks[FORKS-1]);
        // philosopher starts thinking about LIFE
        printf("Philosopher %d finished dinner\n", i+1);
        sleep(10);

    } else{
        // philosopher puts down LEFT fork
        pthread_mutex_unlock(&forks[i-1]);

        // philosopher puts down RIGHT fork
        pthread_mutex_unlock(&forks[i]);
        // philosopher starts thinking about LIFE
        printf("Philosopher %d finished dinner\n", i+1);
        sleep(10);
    }
    count ++;
    //}
}


int main() {
    printf("\tTHE DINNER IS ABOUT TO START\n");
    
    // define message status
    int i;
    int status_message = 0;
    void* msg;


    // 
    for (i = 0; i < FORKS; i++){
        status_message = pthread_mutex_init(&forks[i], NULL);
        if (status_message == -1){
            printf("Failed\n");
        }

    }
    printf("\tThe table is served!\n");

//
    for (i = 0; i < PHILOSOPHERS; i++){
        status_message = pthread_create(&philosophers[i], NULL, (void*)dine, (int*)(intptr_t)i);
        if (status_message != 0){
            printf("Thread error\n");
        }
    }

//
//
    //waiting for all the PHILOSOPHERS to finish dining
    for (i = 0; i < PHILOSOPHERS; i++){
        status_message = pthread_join(philosophers[i], &msg);
        if (status_message != 0){
            printf("Join\n");
        }

    }
//
    // destroy forks array
    for (i = 0; i < FORKS; i++){
        status_message = pthread_mutex_destroy(&forks[i]);
        if (status_message != 0){
            printf("Destroy\n");
        }
    }



    return 0;
}

