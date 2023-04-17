#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char r, g, b;
} Pixel;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "rb");
    if (input_file == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    fseek(input_file, 10, SEEK_SET);
    unsigned int data_offset;
    fread(&data_offset, 4, 1, input_file);

    fseek(input_file, 18, SEEK_SET);
    unsigned int width, height;
    fread(&width, 4, 1, input_file);
    fread(&height, 4, 1, input_file);

    fseek(input_file, data_offset, SEEK_SET);
    Pixel *pixels = malloc(sizeof(Pixel) * width * height);
    fread(pixels, sizeof(Pixel), width * height, input_file);

    fclose(input_file);

    FILE *output_file_x = fopen("output_x.rom", "w");
    if (output_file_x == NULL) {
        printf("Error opening output_x file.\n");
        return 1;
    }

    FILE *output_file_y = fopen("output_y.rom", "w");
    if (output_file_y == NULL) {
        printf("Error opening output_y file.\n");
        return 1;
    }

    FILE *output_file_rgb = fopen("output_rgb.rom", "w");
    if (output_file_rgb == NULL) {
        printf("Error opening output_rgb file.\n");
        return 1;
    }

    fprintf(output_file_x, "v3.0 hex words plain\n");
    fprintf(output_file_y, "v3.0 hex words plain\n");
    fprintf(output_file_rgb, "v3.0 hex words plain\n");

    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            Pixel pixel = pixels[x + y * width];
            fprintf(output_file_x, "%02x ", x);
            fprintf(output_file_y, "%02x ", height - 1 - y);
            fprintf(output_file_rgb, "%02x%02x%02x ", pixel.b, pixel.g, pixel.r);
        }
        fprintf(output_file_x, "\n");
        fprintf(output_file_y, "\n");
        fprintf(output_file_rgb, "\n");
    }

    fclose(output_file_x);
    fclose(output_file_y);
    fclose(output_file_rgb);
    free(pixels);

    return 0;
}
