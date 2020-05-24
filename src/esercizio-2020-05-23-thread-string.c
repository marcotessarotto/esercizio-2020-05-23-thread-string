/******* esercizio-2020-05-23-thread-string *******/

/*
prendere la stringa di caratteri:

char * content = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Mattis rhoncus urna neque viverra justo nec ultrices. Pretium quam vulputate dignissim suspendisse in est ante. Vitae congue mauris rhoncus aenean. Blandit cursus risus at ultrices mi. Ut lectus arcu bibendum at varius vel pharetra vel. Etiam non quam lacus suspendisse faucibus interdum posuere. Eget sit amet tellus cras adipiscing enim eu turpis egestas. Lectus magna fringilla urna porttitor rhoncus dolor purus non. Sit amet consectetur adipiscing elit duis tristique sollicitudin nibh. Nec tincidunt praesent semper feugiat nibh. Sapien pellentesque habitant morbi tristique senectus et netus et malesuada.";

il processo crea tre threads; passa la stringa di caratteri content come parametro a ciascuno dei tre threads.

il primo thread conta il numero di vocali nella stringa e restituisce questo valore.

il secondo thread conta il numero di consonanti nella stringa e restituisce questo valore.

il terzo thread conta il numero di spazi e newline nella stringa e restituisce questo valore.

il thread principale aspetta il risultato dei tre threads e poi scrive su stdout i risultati.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>

char * content = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Mattis rhoncus urna neque viverra justo nec ultrices. Pretium quam vulputate dignissim suspendisse in est ante. Vitae congue mauris rhoncus aenean. Blandit cursus risus at ultrices mi. Ut lectus arcu bibendum at varius vel pharetra vel. Etiam non quam lacus suspendisse faucibus interdum posuere. Eget sit amet tellus cras adipiscing enim eu turpis egestas. Lectus magna fringilla urna porttitor rhoncus dolor purus non. Sit amet consectetur adipiscing elit duis tristique sollicitudin nibh. Nec tincidunt praesent semper feugiat nibh. Sapien pellentesque habitant morbi tristique senectus et netus et malesuada.";
char * vocals = "aeiou";
char * consonant = "qwrtypsdfghjklzxcvbnm";
//char vocals = {'a','e','i','o','u'};
//char consonant = {'q','w','r','t','y','p','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m'};
#define THREAD_ERR(a,msg) {if ((a) != 0) { perror((msg)); exit(EXIT_FAILURE); } }

int * prepare_return_value(int value) {

	int * result_value_ptr;

	result_value_ptr = malloc(sizeof(int));

	if (result_value_ptr == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	*result_value_ptr = value;

	return result_value_ptr;
}

void * thread_function_1(void * arg) {

	printf("[thread_1]start\n");

	char * str = (char *) arg;

	int number_of_vocals = 0;

	for (int i = 0; str[i] != '\0'; i++) {
		int ch = tolower(str[i]);
		for (int j = 0; vocals[j] != '\0'; j++) {
			if (ch == vocals[j])
				number_of_vocals++;
		}
	}

	return (void *) prepare_return_value(number_of_vocals);
}

void * thread_function_2(void * arg) {

	printf("[thread_2]start\n");

	char * str = (char *) arg;

	int number_of_consonants = 0;

	for (int i = 0; str[i] != '\0'; i++) {
		int ch = tolower(str[i]);
		for (int j = 0; consonant[j] != '\0'; j++) {
			if (ch == consonant[j])
				number_of_consonants++;
		}
	}

	return (void *) prepare_return_value(number_of_consonants);
}

void * thread_function_3(void * arg) {

	printf("[thread_3]start\n");

	char * str = (char *) arg;

	int * space_and_newline = malloc(2*sizeof(int));

	if (space_and_newline == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == ' ')
			space_and_newline[0]++;
		if (str[i] == '\n')
			space_and_newline[1]++;
	}

	return (void *) space_and_newline;
}



int main(int argc, char * argv[]) {

	pthread_t t1, t2, t3;
	void * res1, * res2, * res3;
	int * ret1, * ret2, * ret3;

	int s;
	// create threads
	s = pthread_create(&t1, NULL, thread_function_1, content);

	THREAD_ERR(s, "pthread_create")

	s = pthread_create(&t2, NULL, thread_function_2, content);

	THREAD_ERR(s, "pthread_create")

	s = pthread_create(&t3, NULL, thread_function_3, content);

	THREAD_ERR(s, "pthread_create")

	// join threads
	s = pthread_join(t1, &res1);

	THREAD_ERR(s, "pthread_join")

	s = pthread_join(t2, &res2);

	THREAD_ERR(s, "pthread_join")

	s = pthread_join(t3, &res3);

	THREAD_ERR(s, "pthread_join")

	ret1 = (int *) res1;
	ret2 = (int *) res2;
	ret3 = (int *) res3;

	printf("\nAnalisi del testo:\n- %d vocali\n- %d consonanti\n- %d spazi e %d newline",  *ret1, *ret2, ret3[0], ret3[1]);

	exit(EXIT_SUCCESS);

}



