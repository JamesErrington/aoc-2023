#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void part1(char *buffer) {
	int total = 0;
	char *line = strtok(buffer, "\n");
	while (line != NULL) {
		int score = 0;

		char *winning_start = strchr(line, ':');
		char *numbers_start = strchr(line, '|');

		long winners[10];
		int winner_index = 0;

		char *left_index = winning_start + 2;
		while (left_index < numbers_start) {
			char *space_ptr;
			long winner = strtol(left_index, &space_ptr, 10);

			winners[winner_index++] = winner;
			left_index = space_ptr + 1;
		}

		char *numbers_index = numbers_start + 1;
		while (*numbers_index != '\0') {
			char *space_ptr;
			long number = strtol(numbers_index, &space_ptr, 10);

			for (int i = 0; i < winner_index; i++) {
				long winner = winners[i];
				if (number == winner) {
					if (score == 0) score = 1;
					else score = score << 1;
					break;
				}
			}

			numbers_index = space_ptr;
		}

		total += score;

		line = strtok(NULL, "\n");
	}

	printf("Answer: %d\n", total);
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

	// strtok modifies the buffer so these cannot both be uncommented
	part1(buffer);
	// part2(buffer);

	free(buffer);
}

