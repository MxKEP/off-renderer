#ifndef _MAT_H_
#define _MAT_H_

float rad(float deg);

// vector functions
void normalize(float v[]);
void add(float v1[], float v2[], float res[]);
void sub(float v1[], float v2[], float res[]);
void cross (float a[], float b[], float res[]);

// matrix functions
void zero(float m[]);
void identity(float m[]);
void translate(float m[], float t[3]);
void scale(float m[], float s[3]);
void rotate(float m[], float angle, float x, float y, float z);
void mult(float A[], float B[]);

// function to compute perspective projection matrix 
void frustum(float m[], float left, float right, float bottom, float top, float znear, float zfar);
void perspective(float m[], float fovy, float aspect, float near, float far);

// function to compute transformation matrix for camera coordinate frame
void lookat(float m[], float eye[], float at[], float up[]);
#endif
