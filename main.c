#include "raycast.h"

// argv[1] -> width
// argv[2] -> height
// argv[3] -> input file
// argv[4] -> output file
// argc -> 5

int main(int argc, char* argv[])
{
    // Handle improper arguments
    if (argc < 5) {
        fprintf(stderr, "Error: Missing input/output filenames\n");
        return 1;
    }

    Scene *scene = readInputScene(argv[3]);

    // write new image to output file
    // writeOutputPPMFile(argv[2], filtered_img);

    // free allocated memory
    // free(filtered_img);
    free(scene);

	return 0;
}