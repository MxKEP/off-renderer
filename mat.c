#include "mat.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>

// all matrices are column major

float rad(float deg) {
  return (deg/180)*M_PI;
}

void normalize(float v[]) {
  float len = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
  v[0] /= len;
  v[1] /= len;
  v[2] /= len;
}

void add(float v1[], float v2[], float res[]) {
  for (int i=0; i<3; i++) {
    res[i] = v1[i] + v2[i];
  }
}

void sub(float v1[], float v2[], float res[]) {
  for (int i=0; i<3; i++) {
    res[i] = v1[i] - v2[i];
  }
}

void cross (float a[], float b[], float res[]) {
  res[0] = a[1] * b[2] - a[2] * b[1];
  res[1] = a[2] * b[0] - a[0] * b[2];
  res[2] = a[0] * b[1] - a[1] * b[0];
}

//---------------------------------------------------------------------------
void zero(float m[]) {
  memset(m, 0, 16*sizeof(float));
}
//---------------------------------------------------------------------------
void identity(float m[]) {
  zero(m);
  m[0] = m[5] = m[10] = m[15] = 1.0f;
}

//---------------------------------------------------------------------------
// generates a translation matrix T, and multiplies it onto m
void translate(float m[], float t[3]) {
  float T[16];
  identity(T);

  T[12] = t[0]; 
  T[13] = t[1];
  T[14] = t[2];
  mult(m, T);
}

//--------------------------------------------------------------------------
// generates a scaling matrix S, and multiplies it onto m
void scale(float m[], float s[3]) {
  float S[16];
  identity(S);

  S[0] = s[0]; 
  S[5] = s[1];
  S[10] = s[2];
  mult(m, S);
}

//---------------------------------------------------------------------------
// generates a rotation matrix R, and multiplies it onto m
void rotate(float m[], float angle, float x, float y, float z) {
  float len, nx, ny, nz, c, s;
  float R[16];
  identity(R);
  len = sqrt(x*x+y*y+z*z);
  nx = x/len;
  ny = y/len;
  nz = z/len;
  c = (float) cos(rad(angle));
  s = (float) sin(rad(angle));

  R[0]=nx*nx*(1-c)+c;
  R[1]=ny*nx*(1-c)+nz*s;
  R[2]=nx*nz*(1-c)-ny*s;
  R[4]=ny*nx*(1-c)-nz*s;
  R[5]=ny*ny*(1-c)+c;
  R[6]=ny*nz*(1-c)+nx*s;
  R[8]=nz*nx*(1-c)+ny*s;
  R[9]=nz*ny*(1-c)-nx*s;
  R[10]=nz*nz*(1-c)+c;

  mult(m, R);
}

//---------------------------------------------------------------------------
// 4x4 matrix multiplication
// A = A*B
void mult(float A[], float B[]) {
  int row, col, inner, i;
  float res[16];
  float sum;
  for (col=0; col<4; col++) {
    for (row=0; row<4; row++) {
      sum = 0;
      for (inner=0; inner<4; inner++) {
        sum += A[inner*4+col]*B[row*4+inner];
      }
      res[row*4+col] = sum;
    }
  }
   
  for (i=0; i<16; i++)
    A[i] = res[i];
}

//---------------------------------------------------------------------------
//m contrains the projection matrix for general perspective projection

void frustum(float m[], float left, float right, float bottom, float top, float znear, float zfar){
    float temp, temp2, temp3, temp4;
    zero(m);
    temp = 2.0*znear;
    temp2 = right - left;
    temp3 = top - bottom;
    temp4 = zfar - znear;
    m[0] = temp / temp2;
    m[5] = temp / temp3;
    m[8] = (right + left) / temp2;
    m[9] = (top + bottom) / temp3;
    m[10] = (-zfar - znear) / temp4;
    m[11] = -1.0;
    m[14] = (-temp * zfar) / temp4;
}

//----------------------------------------------------------------------------------
//m contains the perpsective projection matrix for view volume centered about z axis

void perspective(float m[], float fovy, float aspect, float near, float far) {
  float ymax = near*tan(rad(fovy)/2);
  float xmax = ymax*aspect;
  frustum(m, -xmax, xmax, -ymax, ymax, near, far);
}

//---------------------------------------------------------------------------
//m contains the transformation matrix for camera's coordinate frame

void lookat(float m[], float eye[], float at[], float up[]) {
  float mat[16];
  float f[3], s[3], u[3], eyet[3];

  sub(at, eye, f);
  normalize(f);
  cross(f, up, s);
  normalize(s);
  cross(s, f, u);
  normalize(u);

  identity(mat);
  mat[0] = s[0];
  mat[4] = s[1];
  mat[8] = s[2];
  mat[1] = u[0];
  mat[5] = u[1];
  mat[9] = u[2];
  mat[2] = -f[0];
  mat[6] = -f[1];
  mat[10] = -f[2];

  mult(m, mat);
  for (int i=0; i<3; i++)
    eyet[i] = -eye[i];
  translate(m, eyet);
}
