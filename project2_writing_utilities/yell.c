#include <fcntl.h> // open()
#include <unistd.h> // read(), write(), close()
#include <ctype.h> //toupper()
#include <stdio.h> //perror()
#include <stdlib.h> //exit()

int main(int argc, char const *argv[]) {
	const int STDIN = 0;
	const int STDOUT = 1;
	const int MAX_BUFFER_SIZE = 2048;
	const int TRUE = 1;
	const int NO_ARGS = 1;

	char buffer[MAX_BUFFER_SIZE];

	if (argc == NO_ARGS) {
		while (TRUE) {
			int bytesRead = read(STDIN, &buffer, MAX_BUFFER_SIZE);
			// EOF will have 0 bytes, an error will return -1
			if (bytesRead <= 0) {
				break;
			} else {
				for (int i = 0; i < bytesRead; i++) {
					buffer[i] = toupper(buffer[i]);
				}

				write(STDOUT, &buffer, bytesRead);
			}
		}
	} else {
		for (int i = 1; i < argc; i++) {
			int fildes = open(argv[i], O_RDONLY);
			int bytesRead = 0;

			if (fildes == -1) {
				perror("open");
				exit(1);
			}

			while ((bytesRead = read(fildes, &buffer, MAX_BUFFER_SIZE)) != 0) {
				for (int i = 0; i < bytesRead; i++) {
					buffer[i] = toupper(buffer[i]);
				}
				write(STDOUT, &buffer, bytesRead);
			}
			close(fildes);
		}
	}
	return 0;
}
