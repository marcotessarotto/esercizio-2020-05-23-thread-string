#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <errno.h>
#include <pthread.h>

#define M 3
int number_of_threads = M;
int vowels, consonant, space;

void * thread_function1(void * arg) {

	char * text = (char *) arg;
	//thread1

	for (int i = 0; text[i] != '\0'; i++) {

	    if (text[i] == 'a' || text[i] == 'e' || text[i] == 'i' ||
	        	text[i] == 'o' || text[i] == 'u' || text[i] == 'A' ||
				text[i] == 'E' || text[i] == 'I' || text[i] == 'O' ||
				text[i] == 'U'){

	        vowels++;
	     }
	 }

	 return NULL;

}

void * thread_function2(void * arg) {

	char * text = (char *) arg;
	//thread1

	for (int i = 0; text[i] != '\0'; ++i) {

		if (((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z' ))

			    && text[i] != 'a' && text[i] != 'e' && text[i] != 'i' &&
			    text[i] != 'o' && text[i] != 'u' && text[i] != 'A' &&
				text[i] != 'E' && text[i] != 'I' && text[i] != 'O' &&
				text[i] != 'U')
			consonant++;

	}

	return NULL;
}

void * thread_function3(void * arg) {

	char * text = (char *) arg;
	//thread3
	for (int i = 0; text[i] != '\0'; ++i) {

		if (text[i] == ' ')

			space++;

		}
    return NULL;
}

int main(int argc, char *argv[]) {

	int s;

	pthread_t threads[M];
	char * content = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Mattis rhoncus urna neque viverra justo nec ultrices. Pretium quam vulputate dignissim suspendisse in est ante. Vitae congue mauris rhoncus aenean. Blandit cursus risus at ultrices mi. Ut lectus arcu bibendum at varius vel pharetra vel. Etiam non quam lacus suspendisse faucibus interdum posuere. Eget sit amet tellus cras adipiscing enim eu turpis egestas. Lectus magna fringilla urna porttitor rhoncus dolor purus non. Sit amet consectetur adipiscing elit duis tristique sollicitudin nibh. Nec tincidunt praesent semper feugiat nibh. Sapien pellentesque habitant morbi tristique senectus et netus et malesuada.";

	s = pthread_create(&threads[0], NULL, thread_function1, content);

	if (s != 0) {
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}

	s = pthread_create(&threads[1], NULL, thread_function2, content);

	if (s != 0) {
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}


	s = pthread_create(&threads[2], NULL, thread_function3, content);

	if (s != 0) {
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}



	for (int i=0; i < number_of_threads; i++) {


		s = pthread_join(threads[i], NULL);

		if (s != 0) {
			perror("pthread_join");
			exit(EXIT_FAILURE);
		}
	}

	printf("I have found: %d vowels, %d consonant, %d space\n", vowels, consonant, space);
	printf("bye\n");

	return 0;
}




