/* Wes Rupert - wesrupert@outlook.com (wkr3)  *
 * Josh Braun - jxb532@case.edu (jxb532)      *
 * Case Western Reserve University - EECS 366 *
 * 10/07/2013 - Assignment 4                  */

// Allow use of M_PI constant
#define _USE_MATH_DEFINES

#include <math.h>
#include "Camera.h"
#include "Vector3.h"
#include "Matrix.h"
#include "MatrixMakers.h"

using namespace std;

Camera::Camera()
{
	Position.x = 10.0;
	Position.y = 0.0;
	Position.z = 0.0;

	Pitch = ((float) M_PI)/2;
	Yaw = 0.0;
	v.i = 0; v.j = 0; v.k = 1;
	EnforceVectors();

	ViewWidth = 8.0;
	ViewHeight = 8.0;

	FarPlane = 10.0;
	NearPlane = 2.0;
	ViewPlane = 10.0;

	LookAt();
}



// Pan the camera about its local axes
void Camera::Pan(float y, float p)
{
	Yaw += y;
	Pitch += p;
	EnforceVectors();
	LookAt();
}

// Scale the viewing plane
void Camera::ScaleView(float s)
{
	ViewWidth = s*ViewWidth;
	ViewHeight = s*ViewHeight;
}
// Move the viewing plane toward/away from the camera
void Camera::MoveView(float d)
{
	if(ViewPlane + d > 1.0)
        ViewPlane = ViewPlane + d;
}

// Set (and normalize) the camera vectors based on the viewing angles
void Camera::EnforceVectors()
{
	float magnitude;
	Vector temp;

	n.i = sin(Pitch)*cos(Yaw);
	n.j = sin(Pitch)*sin(Yaw);
	n.k = cos(Pitch);

	if(((n.i == 0) && (n.j == 0) && (n.k == 1)) || ((n.i == 0) && (n.j == 0) && (n.k == -1)))
	{
        v.i = 1; v.j = 0; v.k = 0;
	}
	else
	{
        v.i = 0; v.j = 0; v.k = 1;
	}

	temp.i = v.j*n.k - v.k*n.j;
	temp.j = v.k*n.i - v.i*n.k;
	temp.k = v.i*n.j - v.j*n.i;
	magnitude = sqrt(temp.i*temp.i + temp.j*temp.j + temp.k*temp.k);
	u.i = temp.i/magnitude; u.j = temp.j/magnitude; u.k = temp.k/magnitude;

	v.i = n.j*u.k - n.k*u.j;
	v.j = n.k*u.i - n.i*u.k;
	v.k = n.i*u.j - n.j*u.i;
}


// Calculate the new perspective projection matrix
void Camera::Perspective()
{
	//ADD YOUR CODE HERE!!
	// need to set ViewingMatrix[16] and ProjectionMatrix[16];
	// I think we need to use ViewWidth, ViewHeight, FarPlane, NearPlane, ViewPlane
	Matrix* perspective = perspectiveMatrix(ViewPlane, - (ViewWidth / 2.0), (ViewWidth / 2), - (ViewHeight / 2), (ViewHeight / 2), NearPlane, FarPlane);
	float* persArray = perspective->toArray();

	for(int i = 0; i < 16; i++) {
		ProjectionMatrix[i] = persArray[i];
	}

	delete perspective;
	delete [] persArray;
}

// Calculate the new orthographic projection matrix
void Camera::Orthographic()
{
	//ADD YOUR CODE HERE!!
	// need to set ViewingMatrix[16] and ProjectionMatrix[16];
	// I think we need to use ViewWidth, ViewHeight, FarPlane, NearPlane, ViewPlane

	Vector3* V = new Vector3(v.i, v.j, v.k);
	Matrix* ortho = orthographicMatrix(V, - (ViewWidth / 2.0), (ViewWidth / 2), - (ViewHeight / 2), (ViewHeight / 2), NearPlane, FarPlane);

	float* orthoArray = ortho->toArray();
	
	for (int i = 0; i < 16; i++) {
		ProjectionMatrix[i] = orthoArray[i];
	}

	delete V, ortho;
	delete [] orthoArray;
}

// Calculate the new viewing transform matrix
void Camera::LookAt()
{
	//ADD YOUR CODE HERE!!
	// hmm, might need to change this to use the existing u, n, v, and dot them with Position, instead of recalculating everything in viewMatrix()
	Vector3* P = new Vector3(Position.x, Position.y, Position.z);
	Vector3* N = new Vector3(n.i, n.j, n.k);
	Vector3* V = new Vector3(v.i, v.j, v.k);

	Matrix* view = viewMatrix(P, N, V);
	float* viewArray = view->toArray();
	
	for (int i = 0; i < 16; i++) {
		ViewingMatrix[i] = viewArray[i];
	}

	delete view, P, N, V;
	delete [] viewArray;
}
