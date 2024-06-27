#include <stdio.h> 
#include "lib_ppm.h"

void zoom_image(struct image_s *input, struct image_s *output) {
    new_ppm(output, 3 * input->width, 3 * input->height);

    for (int y = 0; y < input->height; y++) {
        for (int x = 0; x < input->width; x++) {
            struct pixel_s current_pixel = input->pix[y * input->width + x];
            int index_base = (3 * y * output->width + 3 * x);

            for (int dy = 0; dy < 3; dy++) {
                for (int dx = 0; dx < 3; dx++) {
                    struct pixel_s *output_pixel = &output->pix[index_base + dy * output->width + dx];
                    output_pixel->r = output_pixel->g = output_pixel->b = 0; // Default to black

                    // Red sub-pixel logic
                    if (current_pixel.r >= 180) output_pixel->r = 255;
                    else if (current_pixel.r >= 135) output_pixel->r = (dx != 1) ? 255 : 0;
                    else if (current_pixel.r >= 75) output_pixel->r = (dx == 1) ? 255 : 0;

                    // Green sub-pixel logic
                    if (current_pixel.g >= 180) output_pixel->g = 255;
                    else if (current_pixel.g >= 135) output_pixel->g = (dx != 1) ? 255 : 0;
                    else if (current_pixel.g >= 75) output_pixel->g = (dx == 1) ? 255 : 0;

                    // Blue sub-pixel logic
                    if (current_pixel.b >= 180) output_pixel->b = 255;
                    else if (current_pixel.b >= 135) output_pixel->b = (dx != 1) ? 255 : 0;
                    else if (current_pixel.b >= 75) output_pixel->b = (dx == 1) ? 255 : 0;
                }
            }
        }
    }
}

int main() {
    struct image_s input_image, output_image;
    
    if (read_ppm("input.ppm", &input_image) != 0) {
        fprintf(stderr, "Error reading input file\n");
        return -1;
    }

    zoom_image(&input_image, &output_image);

    if (write_ppm("output.ppm", &output_image) != 0) {
        fprintf(stderr, "Error writing output file\n");
        return -1;
    }

    free_ppm(&input_image);
    free_ppm(&output_image);

    return 0;
}
