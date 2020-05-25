/*
 * esercizio-2020-05-23-thread-string.c
 *
 *  Created on: May 21, 2020
 *      Author: marco
 *
 *      prendere la stringa di caratteri:

char * content = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Mattis rhoncus urna neque viverra justo nec ultrices. Pretium quam vulputate dignissim suspendisse in est ante. Vitae congue mauris rhoncus aenean. Blandit cursus risus at ultrices mi. Ut lectus arcu bibendum at varius vel pharetra vel. Etiam non quam lacus suspendisse faucibus interdum posuere. Eget sit amet tellus cras adipiscing enim eu turpis egestas. Lectus magna fringilla urna porttitor rhoncus dolor purus non. Sit amet consectetur adipiscing elit duis tristique sollicitudin nibh. Nec tincidunt praesent semper feugiat nibh. Sapien pellentesque habitant morbi tristique senectus et netus et malesuada.";

il processo crea tre threads; passa la stringa di caratteri content come parametro
a ciascuno dei tre threads.

il primo thread conta il numero di vocali nella stringa e restituisce questo valore.

il secondo thread conta il numero di consonanti nella stringa e restituisce questo valore.

il terzo thread conta il numero di spazi e newline nella stringa e restituisce questo valore.

il thread principale aspetta il risultato dei tre threads e poi scrive su stdout i risultati.
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <errno.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
	int n_vocali;
	int n_consonanti;
	int n_speciali;
	int string_len;
}counter;

counter* caratteri; // puntatore dei risultati

void * thread_vocali(void * arg) {
	char* str = (char*) arg;
	int i = 0;
	while(*(str+i) != '\0'){
		if (*(str+i) == 'a' || *(str+i) == 'A' || *(str+i) == 'e' || *(str+i) == 'E' || *(str+i) == 'i' ||
				*(str+i) == 'I' || *(str+i) == 'o' || *(str+i) == 'O' || *(str+i) == 'u' || *(str+i) == 'U')
			caratteri->n_vocali++;
		i++;
	}

	return NULL;
}

void * thread_consonanti(void * arg) {

	char* str = (char*) arg;
	int i = 0;
	while(*(str+i) != '\0'){
		if (*(str+i) != 'a' && *(str+i) != 'A' && *(str+i) != 'e' && *(str+i) != 'E' && *(str+i) != 'i' &&
				*(str+i) != 'I' && *(str+i) != 'o' && *(str+i) != 'O' && *(str+i) != 'u' && *(str+i) != 'U'
				&& *(str+i) != '\n' && *(str+i) != '\t' && *(str+i) != ' ')
			caratteri->n_consonanti++;
		i++;
	}


	return NULL;
}

void * thread_speciali(void * arg) {

	char* str = (char*) arg;
	int i = 0;
	while(*(str+i) != '\0'){
		if(*(str+i) == ' ' || *(str+i) == '\n')
			caratteri->n_speciali++;
		i++;
	}

	return NULL;
}



int main() {

	char * content = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Mattis rhoncus urna neque viverra justo nec ultrices. Pretium quam vulputate dignissim suspendisse in est ante. Vitae congue mauris rhoncus aenean. Blandit cursus risus at ultrices mi. Ut lectus arcu bibendum at varius vel pharetra vel. Etiam non quam lacus suspendisse faucibus interdum posuere. Eget sit amet tellus cras adipiscing enim eu turpis egestas. Lectus magna fringilla urna porttitor rhoncus dolor purus non. Sit amet consectetur adipiscing elit duis tristique sollicitudin nibh. Nec tincidunt praesent semper feugiat nibh. Sapien pellentesque habitant morbi tristique senectus et netus et malesuada.";

	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	//counter * caratteri;
	void * res;

	int s;

	caratteri = malloc(sizeof(counter));
	if(caratteri == NULL){
		perror("malloc!");
		exit(EXIT_FAILURE);

	}

	caratteri->string_len = strlen(content);

	s = pthread_create(&t1, NULL, thread_vocali, content);

	if (s != 0) {
		perror("pthread_create vocali");
		exit(EXIT_FAILURE);
	}

	s = pthread_create(&t2, NULL, thread_consonanti, content);

	if (s != 0) {
		perror("pthread_create consonanti");
		exit(EXIT_FAILURE);
	}

	s = pthread_create(&t3, NULL, thread_speciali, content);

	if (s != 0) {
		perror("pthread_create caratteri speciali");
		exit(EXIT_FAILURE);
	}

	s = pthread_join(t1, &res);

	if (s != 0) {
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}

	s = pthread_join(t2, &res);

	if (s != 0) {
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}

	s = pthread_join(t3, &res);

	if (s != 0) {
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}

	// crivo su stdout i risultati
	printf(" Numero di vocali: %d\n", caratteri->n_vocali);
	printf(" Numero di consonanti %d\n", caratteri->n_consonanti);
	printf(" Numero di spazi e newline %d\n",caratteri->n_speciali);
	printf("TOTALI: %d\n", caratteri->n_consonanti+caratteri->n_speciali+caratteri->n_vocali);
	printf("strlen: %d\n", caratteri->string_len);

	return 0;
}


