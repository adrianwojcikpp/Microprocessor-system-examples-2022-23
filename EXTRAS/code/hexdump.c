#include <stdio.h>

#define BUFFER_SIZE 16

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    fprintf(output_file, "v3.0 hex words plain\n");

    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, input_file)) > 0) {
        for (size_t i = 0; i < bytes_read; i++) {
            fprintf(output_file, "%02x ", buffer[i]);
        }
        for (size_t i = bytes_read; i < BUFFER_SIZE; i++) {
            fprintf(output_file, "00 ");
        }
        fprintf(output_file, "\n");
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}
