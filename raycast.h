#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

// structures
typedef struct
{
    float x;
    float y;
    float z;
} Vector3;

typedef enum {SPHERE, PLANE} ObjectType;

typedef struct
{
    Vector3 pos;
    float width;
    float height;
} Camera;

typedef struct
{
    ObjectType type;
    Vector3 pos;
    Vector3 normal; // For planes
    float radius;   // For spheres
    Vector3 color;
} Object;

typedef struct 
{
    Object* objects;
    Camera camera;
    int objectNum;
} Scene;

// function declarations
bool readProperty(FILE *file, char *property, Scene *scene);
Scene *readInputScene(char* filename);
PPMImage *raycast(Scene *scene, int width, int height);