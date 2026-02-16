#include "raycast.h"

Scene *readInputScene(char* filename)
{
    Scene *scene = (Scene*)malloc(sizeof(Scene));
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return NULL;
    }

    // read scene identifier
    char identifier[20];
    fscanf(file, "%s", identifier);
    printf("Scene Identifier: %s\n", identifier);

    fclose(file);
    return scene;
}