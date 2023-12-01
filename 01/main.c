#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void part1(char *buffer) {
	long value = 0;

	char *line = strtok(buffer, "\n");
	while (line != NULL) {
		char digits[3] = {0};

		int i = 0;
		for (char current = line[i]; current != 0; current = line[++i]) {
			if (isdigit(current)) {
				digits[1] = current;
				if (digits[0] == 0) digits[0] = current;
			}
		}

		char *end;
		value += strtol(digits, &end, 10);

		line = strtok(NULL, "\n");
	}

	printf("Part 1 Answer: %ld\n", value);
}

void part2(char *buffer) {
	long value = 0;

	char *line = strtok(buffer, "\n");

	const int count = 9;
	char strings[count][6] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	int indices[count] = {0};
	char values[count] = {49, 50, 51, 52, 53, 54, 55, 56, 57};

	while (line != NULL) {
		char digits[3] = {0};

		int i = 0;
		for (char current = line[i]; current != 0; current = line[++i]) {
			if (isdigit(current)) {
				digits[1] = current;
				if (digits[0] == 0) digits[0] = current;
				continue;
			}

			for (int j = 0; j < count; j++) {
				char *target = strings[j]; int index = indices[j];
				if (current == target[index]) {
					indices[j]++;
					if (target[indices[j]] == 0) {
						digits[1] = values[j];
						if (digits[0] == 0) digits[0] = values[j];
						indices[j] = 0;
					}
				} else if (current == target[0]) {
					indices[j] = 1;
				} else {
					indices[j] = 0;
				}
			}
		}

		char *end;
		value += strtol(digits, &end, 10);

		line = strtok(NULL, "\n");
		memset(indices, 0, sizeof(int) * count);
	}

	printf("Part 1 Answer: %ld\n", value);
}


int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Not enough arguments provided\n");
		exit(1);
	}

	char *buffer;
	long fsize;

	{
		// This only works because 'example' and 'problem' have the same number of letters
		// and we know the day will always be 2 letters
		char path[2 + 2 + 12 + 1];
		sprintf(path, "./%s/problem.txt", argv[1]);
		FILE *fptr = fopen(path, "rb");
		if (fptr == NULL) {
			perror("Unable to open file");
			exit(1);
		}

		fseek(fptr, 0, SEEK_END);
		fsize = ftell(fptr);
		rewind(fptr);

		buffer = malloc(fsize + 1);
		if (buffer == NULL) {
			perror("Unable to read file");
			fclose(fptr);
			exit(1);
		}

		fsize = fread(buffer, 1, fsize, fptr);
		buffer[fsize] = 0;
		fclose(fptr);
	}

	// I think strtok modifies the buffer so these cannot both be uncommented
	// part1(buffer);
	part2(buffer);

	free(buffer);
}

