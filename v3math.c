#include "v3math.h"

// DEVIN
void v3_from_points(float *dst, float *a, float *b) // form v3 from a to b
{
    dst[0] = b[0] - a[0];
    dst[1] = b[1] - a[1];
    dst[2] = b[2] - a[2];
}

// JAKE
void v3_add(float *dst, float *a, float *b)
{
    dst[0] = a[0] + b[0];
    dst[1] = a[1] + b[1];
    dst[2] = a[2] + b[2];
}

// DEVIN
void v3_subtract(float *dst, float *a, float *b)
{
    dst[0] = a[0] - b[0];
    dst[1] = a[1] - b[1];
    dst[2] = a[2] - b[2];
}

// JAKE
float v3_dot_product(float *a, float *b)
{
    return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
}

// DEVIN
void v3_cross_product(float *dst, float *a, float *b)
{
    dst[0] = a[1]*b[2] - a[2]*b[1];
    dst[1] = a[2]*b[0] - a[0]*b[2];
    dst[2] = a[0]*b[1] - a[1]*b[0];
}

// JAKE
void v3_scale(float *dst, float s)
{
    dst[0] *= s;
    dst[1] *= s;
    dst[2] *= s;
}

// DEVIN
float v3_angle(float *a, float *b) // angle between a and b
{
    return acosf(v3_dot_product(a, b) / (v3_length(a) * v3_length(b)));
}

// JAKE
float v3_angle_quick(float *a, float *b) // angle between a and b; no cos-1
{
    //dot product / length of a * length of b = cos0
    //do I need to check to make sure I don't divide by 0?
    
    return v3_dot_product(a, b) / (v3_length(a) * v3_length(b));
}

// DEVIN
void v3_reflect(float *dst, float *v, float *n)
{
    dst[0] = v[0] - 2 * v3_dot_product(v, n) * n[0];
    dst[1] = v[1] - 2 * v3_dot_product(v, n) * n[1];
    dst[2] = v[2] - 2 * v3_dot_product(v, n) * n[2];
}

// JAKE
float v3_length(float *a)
{
    //this is getting the length squared (aax + aay + aaz) and then getting the sqrt of that, which is length
    return sqrtf(v3_dot_product(a, a));
}

// DEVIN
void v3_normalize(float *dst, float *a)
{
    float length = v3_length(a);
    if (length == 0.0) {
        dst[0] = 0.0;
        dst[1] = 0.0;
        dst[2] = 0.0;
        return;
    }

    dst[0] = a[0] / length;
    dst[1] = a[1] / length;
    dst[2] = a[2] / length;
}