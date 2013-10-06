#pragma once

class Vertex
{
public:
	Vertex();
	Vertex(float _x, float _y, float _z);
	void Normalize();
	float x, y, z, h;
};

class Vector
{
public:
	float i, j, k;
};

class Face
{
public:
	int v1, v2, v3;
};

class Object
{
public:
	Object();
	~Object();
	void Load(char* file, float s, float rx, float ry, float rz,
				  float tx, float ty, float tz);
	void WorldTranslate(float tx, float ty, float tz);
	void WorldRotate(float rx, float ry, float rz);
	void LocalRotate(float rx, float ry, float rz);
	void LocalScale(float s);
	Vertex* pBoundingBox;
	Vertex* pVertexList;
	int VertexCount;
	Face* pFaceList;
	int FaceCount;
	float ModelMatrix[16];
};

class Scene
{
public:
	void Load(char* file);
	Object* pObjectList;
	int ObjectCount;
};

class Camera
{
public:
	Camera();
	
	void Pan(float y, float p);
	void ScaleView(float s);
	void MoveView(float d);
	void EnforceVectors();
	void Perspective();
	void Orthographic();
	void LookAt();
	Vertex Position;
	float Pitch, Yaw;
	Vector n;
	Vector v;
	Vector u;
	float FarPlane, NearPlane, ViewPlane;
	float ViewWidth, ViewHeight;
	float ViewingMatrix[16];
	float ProjectionMatrix[16];
};

Vertex Transform(float* matrix, Vertex& point);
