#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <pthread.h>

#define CHECK_ERR(a, msg){if(a!=0) {perror(msg); exit(EXIT_FAILURE); } }

void * count_vocals();

void * count_not_vocals();

void * count_spacelines();

int main() {
	int res;

	char * content = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Mattis rhoncus urna neque viverra justo nec ultrices. Pretium quam vulputate dignissim suspendisse in est ante. Vitae congue mauris rhoncus aenean. Blandit cursus risus at ultrices mi. Ut lectus arcu bibendum at varius vel pharetra vel. Etiam non quam lacus suspendisse faucibus interdum posuere. Eget sit amet tellus cras adipiscing enim eu turpis egestas. Lectus magna fringilla urna porttitor rhoncus dolor purus non. Sit amet consectetur adipiscing elit duis tristique sollicitudin nibh. Nec tincidunt praesent semper feugiat nibh. Sapien pellentesque habitant morbi tristique senectus et netus et malesuada.";

	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;

	void * res1;
	void * res2;
	void * res3;


	res = pthread_create(&thread1, NULL, count_vocals, content);
		CHECK_ERR(res, "pthread_create");

	res = pthread_create(&thread2, NULL, count_not_vocals, content);
		CHECK_ERR(res, "pthread_create");

	res = pthread_create(&thread3, NULL, count_spacelines, content);
			CHECK_ERR(res, "pthread_create");


	res = pthread_join(thread1, &res1);
		CHECK_ERR(res, "pthread_join");

	res = pthread_join(thread2, &res2);
		CHECK_ERR(res, "pthread_join");

	res = pthread_join(thread3, &res3);
		CHECK_ERR(res, "pthread_join");

	printf("mi aspetto di trovare %d vocali e %d consonanti\n\n", 257, 359);

	printf("ho incontrato %d vocali, %d consonanti e %d tra spazi e newline\n", *((int *)res1), *((int *)res2), *((int *)res3));

	return 0;
}

void * count_vocals(void * string){

	char * stringa = (char*)string;

	int * vocals;
	vocals = malloc(sizeof(int));

	int string_length = strlen(stringa);


	for(int j=0; j<string_length; j++){
		if(stringa[j] == 'a' || stringa[j] == 'A' || stringa[j] == 'e' || stringa[j] == 'E' ||
				stringa[j] == 'i' || stringa[j] == 'I' || stringa[j] == 'o' || stringa[j] == 'O' ||
					stringa[j] == 'u' || stringa[j] == 'U'){
			(*vocals)++;

		}
	}
	return vocals;
}

void * count_not_vocals(void * string){

	char * stringa = (char*)string;

	int * not_vocals;
	not_vocals = malloc(sizeof(int));

	int string_length = strlen(stringa);



	for(int j=0; j<string_length; j++){
		if(stringa[j]!='a' && stringa[j]!='A' && stringa[j]!='e' && stringa[j]!= 'E' &&
				stringa[j]!='i' && stringa[j]!='I' && stringa[j] != 'o' && stringa[j] != 'O' &&
					stringa[j] != 'u' && stringa[j] !='U' && stringa[j] > 65){
			(*not_vocals)++;

		}
	}
	return not_vocals;
}

void * count_spacelines(void * string){

	char * stringa = (char*)string;

	int * spacelines;
	spacelines = malloc(sizeof(int));

	int string_length = strlen(stringa);



	for(int j=0; j<string_length; j++){
		if(stringa[j] == ' ' || stringa[j] == '\n')
			(*spacelines)++;
	}
	return spacelines;
}

