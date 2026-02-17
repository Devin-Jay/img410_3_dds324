#include "raycast.h"

// function that reads object's properties and updates scene objects
// returns true if property is valid, false otherwise
bool readProperty(FILE *file, char *property, Scene *scene)
{
    if (strcmp(property, "width:") == 0)
    {
        // read width value
        fscanf(file, "%f", &scene->camera.width);
        return true;
    }
    else if (strcmp(property, "height:") == 0)
    {
        // read height value
        fscanf(file, "%f", &scene->camera.height);
        return true;
    }
    else if (strcmp(property, "position:") == 0)
    {
        // read position values
        fscanf(file, "%f %f %f", &scene->objects[scene->objectNum].pos.x, &scene->objects[scene->objectNum].pos.y, &scene->objects[scene->objectNum].pos.z);
        return true;
    }
    else if (strcmp(property, "c_diff:") == 0)
    {
        // read color values
        fscanf(file, "%f %f %f", &scene->objects[scene->objectNum].color.x, &scene->objects[scene->objectNum].color.y, &scene->objects[scene->objectNum].color.z);
        return true;
    }
    else if (strcmp(property, "radius:") == 0)
    {
        // read radius value
        fscanf(file, "%f", &scene->objects[scene->objectNum].radius);
        return true;
    }
    else if (strcmp(property, "normal:") == 0)
    {
        // read normal values
        fscanf(file, "%f %f %f", &scene->objects[scene->objectNum].normal.x, &scene->objects[scene->objectNum].normal.y, &scene->objects[scene->objectNum].normal.z);
        return true;
    }

    return false; // invalid property ; object found
}

Scene *readInputScene(char* filename)
{
    Scene *scene = (Scene*)malloc(sizeof(Scene));
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return NULL;
    }

    // read scene identifier
    char identifier[20];
    fscanf(file, "%12s", identifier);

    if (strcmp(identifier, "img410scene") != 0)
    {
        fprintf(stderr, "Error: Invalid scene file format\n");
        fclose(file);
        free(scene);
        return NULL;
    }

    // initialize scene variables
    scene->objectNum = 0;
    scene->objects = (Object*)malloc(sizeof(Object) * 128);

    // check for one object
    int result = fscanf(file, "%s", identifier);
    
    if (result == EOF || strcmp(identifier, "end") == 0)
    {
        fprintf(stderr, "Error: No objects found in scene file\n");
        fclose(file);
        free(scene->objects);
        free(scene);
        return NULL;
    }

    // loop until end of file
    while (strcmp(identifier, "end") != 0)
    {
        // check for object type
        if (strcmp(identifier, "camera") == 0 || strcmp(identifier, "camera;") == 0)
        {
            // set default camera values
            scene->camera.pos.x = 0.0f;
            scene->camera.pos.y = 0.0f;
            scene->camera.pos.z = 0.0f;
            scene->camera.width = 0.0f;
            scene->camera.height = 0.0f;

            // read properties
            while (1)
            {
                result = fscanf(file, "%s", identifier);

                // if not a valid property
                if (!readProperty(file, identifier, scene))
                {
                    // check for ;
                    if (strcmp(identifier, ";") == 0)
                    {
                        result = fscanf(file, "%s", identifier);
                    }

                    // assume next object or end
                    break;
                }
            }
        }
        else if (strcmp(identifier, "sphere") == 0 || strcmp(identifier, "sphere;") == 0)
        {
            // set default sphere values
            scene->objects[scene->objectNum].type = SPHERE;
            scene->objects[scene->objectNum].pos.x = 0.0f;
            scene->objects[scene->objectNum].pos.y = 0.0f;
            scene->objects[scene->objectNum].pos.z = 0.0f;
            scene->objects[scene->objectNum].radius = 0.0f;
            scene->objects[scene->objectNum].color.x = 0.0f;
            scene->objects[scene->objectNum].color.y = 0.0f;
            scene->objects[scene->objectNum].color.z = 0.0f;

            // read properties
            while (1)
            {
                result = fscanf(file, "%s", identifier);

                // if not a valid property
                if (!readProperty(file, identifier, scene))
                {
                    // check for ;
                    if (strcmp(identifier, ";") == 0)
                    {
                        // get next object or end
                        result = fscanf(file, "%s", identifier);
                    }

                    scene->objectNum++;

                    // assume next object or end
                    break;
                }
            }
        }
        else if (strcmp(identifier, "plane") == 0)
        {
            // set default plane values
            scene->objects[scene->objectNum].type = PLANE;
            scene->objects[scene->objectNum].pos.x = 0.0f;
            scene->objects[scene->objectNum].pos.y = 0.0f;
            scene->objects[scene->objectNum].pos.z = 0.0f;
            scene->objects[scene->objectNum].normal.x = 0.0f;
            scene->objects[scene->objectNum].normal.y = 0.0f;
            scene->objects[scene->objectNum].normal.z = 0.0f;
            scene->objects[scene->objectNum].color.x = 0.0f;
            scene->objects[scene->objectNum].color.y = 0.0f;
            scene->objects[scene->objectNum].color.z = 0.0f;

            // read properties
            while (1)
            {
                result = fscanf(file, "%s", identifier);

                // if not a valid property
                if (!readProperty(file, identifier, scene))
                {
                    // check for ;
                    if (strcmp(identifier, ";") == 0)
                    {
                        result = fscanf(file, "%s", identifier);
                    }

                    scene->objectNum++;

                    // assume next object or end
                    break;
                }
            }
        }
        else
        {
            fprintf(stderr, "Error: Invalid object type '%s' in scene file\n", identifier);
            fclose(file);
            free(scene->objects);
            free(scene);
            return NULL;
        }

        if (result == EOF) {
            break;
        }
    }

    fclose(file);
    return scene;
}

PPMImage *raycast(Scene *scene, int width, int height)
{
    // create new image
    PPMImage *img = (PPMImage*)malloc(sizeof(PPMImage));
    img->width = width;
    img->height = height;
    img->pixels = (uint8_t*)malloc(3 * img->width * img->height);

    // loop through each pixel in the image
    for (int x = 0; x < img->width; x++)
    {
        for (int y = 0; y < img->height; y++)
        {
            // compute ray from camera through pixel (x, y)
            // check for intersection with each object in scene
            // set pixel color based on closest intersecting object

            // set pixel color to black for now
            img->pixels[3 * (y * img->width + x)] = 0;
            img->pixels[3 * (y * img->width + x) + 1] = 255;
            img->pixels[3 * (y * img->width + x) + 2] = 0;
        }
    }

    return img;
}