#include "Matrix.h"
#include "Vector.h"

Matrix* modelMatrix(Matrix* r, Vector3* p);
Matrix* viewMatrix(Vector3* P, Vector3* N, Vector3* V);
Matrix* rotateMatrix(float thetaDeg, char axis);
Matrix* translateMatrix(float x, float y, float z);
Matrix* perspectiveMatrix(Vector3 prp, Vector3 vp, float s, float t, float d);
Matrix* perspectiveMatrix(float d, float xMin, float xMax, float yMin, float yMax, float n, float f);
Matrix* viewportMatrix(float xvMin, float xvMax, float yvMin, float yvMax);