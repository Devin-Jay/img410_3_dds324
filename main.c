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

    printf("Camera: pos(%.2f, %.2f, %.2f), width: %.2f, height: %.2f\n", scene->camera.pos.x, scene->camera.pos.y, scene->camera.pos.z, scene->camera.width, scene->camera.height);
    for (int i = 0; i < scene->objectNum; i++)
    {
        Object obj = scene->objects[i];
        if (obj.type == SPHERE)
        {
            printf("Object %d: SPHERE, color(%.2f, %.2f, %.2f), pos(%.2f, %.2f, %.2f), radius: %.2f\n", i, obj.color.x, obj.color.y, obj.color.z,obj.pos.x, obj.pos.y, obj.pos.z, obj.radius);
        }
        else if (obj.type == PLANE)
        {
            printf("Object %d: PLANE, color(%.2f, %.2f, %.2f), pos(%.2f, %.2f, %.2f), normal(%.2f, %.2f, %.2f)\n", i, obj.color.x, obj.color.y, obj.color.z, obj.pos.x, obj.pos.y, obj.pos.z, obj.normal.x, obj.normal.y, obj.normal.z);
        }
    }

    PPMImage *result = raycast(scene, atoi(argv[1]), atoi(argv[2]));

    writeOutputPPMFile(argv[4], result);

    // free allocated memory
    free(scene->objects);
    free(scene);

	return 0;
}