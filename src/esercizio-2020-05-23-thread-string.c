#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>

int* prepare_return_value_int(int value) {

	int *result_value_ptr;

	result_value_ptr = malloc(sizeof(int));

	if (result_value_ptr == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	*result_value_ptr = value;

	return result_value_ptr;
}

void* thread_nvocali(void *arg) {

	char *str = (char*) arg;

	int length = strlen(str);

	int res = 0;

	for (int i = 0; i <= length; i++) {
		if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o'
				|| str[i] == 'u' || str[i] == 'A' || str[i] == 'E'
				|| str[i] == 'I' || str[i] == 'O' || str[i] == 'U') {
			res++;
		}
	}

	return (void*) prepare_return_value_int(res);

}

void* thread_nconsonanti(void *arg) {

	char *str = (char*) arg;

	int length = strlen(str);

	int res = 0;

	for (int i = 0; i <= length; i++) {
		if (str[i] == 'b' || str[i] == 'c' || str[i] == 'd' || str[i] == 'f'
				|| str[i] == 'g' || str[i] == 'h' || str[i] == 'j'
				|| str[i] == 'k' || str[i] == 'l' || str[i] == 'm'
				|| str[i] == 'n' || str[i] == 'p' || str[i] == 'q'
				|| str[i] == 'r' || str[i] == 's' || str[i] == 't'
				|| str[i] == 'v' || str[i] == 'w' || str[i] == 'x'
				|| str[i] == 'y' || str[i] == 'z' || str[i] == 'A'
				|| str[i] == 'B' || str[i] == 'C' || str[i] == 'D'
				|| str[i] == 'F' || str[i] == 'G' || str[i] == 'H'
				|| str[i] == 'J' || str[i] == 'K' || str[i] == 'L'
				|| str[i] == 'M' || str[i] == 'N' || str[i] == 'P'
				|| str[i] == 'Q' || str[i] == 'R' || str[i] == 'S'
				|| str[i] == 'T' || str[i] == 'V' || str[i] == 'W'
				|| str[i] == 'X' || str[i] == 'Y' || str[i] == 'Z') {
			res++;
		}
	}

	return (void*) prepare_return_value_int(res);

}

void* thread_nblank(void *arg) {

	char *str = (char*) arg;

	int length = strlen(str);

	int res = 0;

	for (int i = 0; i <= length; i++) {
		if (str[i] == ' ' || str[i] == '\n') {
			res++;
		}
	}

	return (void*) prepare_return_value_int(res);

}

int main() {

	char *content =
			"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Mattis rhoncus urna neque viverra justo nec ultrices. Pretium quam vulputate dignissim suspendisse in est ante. Vitae congue mauris rhoncus aenean. Blandit cursus risus at ultrices mi. Ut lectus arcu bibendum at varius vel pharetra vel. Etiam non quam lacus suspendisse faucibus interdum posuere. Eget sit amet tellus cras adipiscing enim eu turpis egestas. Lectus magna fringilla urna porttitor rhoncus dolor purus non. Sit amet consectetur adipiscing elit duis tristique sollicitudin nibh. Nec tincidunt praesent semper feugiat nibh. Sapien pellentesque habitant morbi tristique senectus et netus et malesuada.";

	pthread_t t1;
	pthread_t t2;
	pthread_t t3;

	void *res_t1;
	void *res_t2;
	void *res_t3;

	int *voc;
	int *cons;
	int *blank;

	int s;

	s = pthread_create(&t1, NULL, thread_nvocali, content);

	if (s != 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	s = pthread_create(&t2, NULL, thread_nconsonanti, content);

	if (s != 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	s = pthread_create(&t3, NULL, thread_nblank, content);

	if (s != 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	s = pthread_join(t1, &res_t1);

	if (s != 0) {
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}

	s = pthread_join(t2, &res_t2);

	if (s != 0) {
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}

	s = pthread_join(t3, &res_t3);

	if (s != 0) {
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}

	voc = (int*) res_t1;
	cons = (int*) res_t2;
	blank = (int*) res_t3;

	printf("Primo thread return value %d\n", *voc);
	printf("Secondo thread return value %d\n", *cons);
	printf("Terzo thread return value %d\n", *blank);
	printf("La stringa è lunga %d\n", strlen(content));
	printf("In totale ho contato %d volte\n", (*voc+*cons+*blank));

//free(res_t1);

	return 0;
}

