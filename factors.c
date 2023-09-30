#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *stream;
	char *line = NULL;
	int not_exit = 1;
	size_t len = 0;
	long long div = 0, rest = 0, number = 0;
	ssize_t nread = 0;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	stream = fopen(argv[1], "r");
	if (stream == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	while ((nread = getline(&line, &len, stream)) != -1) {
		not_exit = 1, div = 2;
		number = atoll(line);
		while (not_exit) {
			rest = number % div;
			if (!rest) {
				printf("%lld=%lld*%lld\n", number, number / div, div);
				not_exit = 0;
			}
			div++;
		}
	}

	free(line);
	fclose(stream);
	exit(EXIT_SUCCESS);
}
