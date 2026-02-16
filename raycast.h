#include <stdio.h>

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
    void *data; // Pointer to either SphereData or PlaneData
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
Scene readInputScene(char* filename);