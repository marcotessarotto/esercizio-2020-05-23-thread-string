#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define N	3

void err_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void *thread_1(void *arg)
{
	char *str = (char *) arg;
	uintptr_t count = 0;
	for (int i = 0; i < strlen(str); i++) {
		switch (tolower((unsigned char) str[i])) {
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u':
			count++;
			break;
		default:
			break;
		}
	}
	return (void *) count;
}

void *thread_2(void *arg)
{
	char *str = (char *) arg;
	uintptr_t count = 0;
	for (int i = 0; i < strlen(str); i++) {
		if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)) {
			switch (tolower((unsigned char) str[i])) {
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				break;
			default:
				count++;
				break;
			}
		}
	}
	return (void *) count;
}

void *thread_3(void *arg)
{
	char *str = (char *) arg;
	uintptr_t count = 0;
	for (int i = 0; i < strlen(str); i++) {
		switch (str[i]) {
		case ' ':
		case '\n':
			count++;
			break;
		default:
			break;
		}
	}
	return (void *) count;
}

int main()
{
	char *content = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. "
			"Mattis rhoncus urna neque viverra justo nec ultrices. Pretium quam vulputate dignissim suspendisse in est ante. "
			"Vitae congue mauris rhoncus aenean. Blandit cursus risus at ultrices mi. Ut lectus arcu bibendum at varius vel pharetra vel. "
			"Etiam non quam lacus suspendisse faucibus interdum posuere. Eget sit amet tellus cras adipiscing enim eu turpis egestas. "
			"Lectus magna fringilla urna porttitor rhoncus dolor purus non. Sit amet consectetur adipiscing elit duis tristique sollicitudin nibh. "
			"Nec tincidunt praesent semper feugiat nibh. Sapien pellentesque habitant morbi tristique senectus et netus et malesuada.";

	pthread_t threads[N];
	void *(*thread_funcs[N])(void *arg);
	thread_funcs[0] = thread_1;
	thread_funcs[1] = thread_2;
	thread_funcs[2] = thread_3;

	for (int i = 0; i < N; i++) {
		if (pthread_create(&threads[i], NULL, &(*thread_funcs[i]), content))
			err_exit("pthread_create() error");
	}

	void *retvals[N];
	for (int i = 0; i < N; i++) {
		if (pthread_join(threads[i], &retvals[i]))
			err_exit("pthread_join() error");
	}

	printf("vowels: %ld\nconsonants: %ld\nspaces & newlines: %ld\n",
			(uintptr_t) retvals[0], (uintptr_t) retvals[1], (uintptr_t) retvals[2]);

	return 0;
}
