#include <fstream>
#include <iostream>
#include <math.h>
#include "mesh.h"

TriangleMesh::TriangleMesh(std::string arq)
{

	std::string cabecalho;
	int temp;
	Vec3<float> zero(0.0,0.0,0.0);
	std::ifstream infile(arq);

	infile >> cabecalho;
	infile >> numVertices >> numTriangles >> temp;

	// Guarda vertices
	for(int i = 0; i < numVertices; i++)
	{
		float x, y, z;
		infile >> x >> y >> z;
		Vec3<float> temp(x,y,z);
		vertices.push_back(temp);
		normal_area.push_back(zero);
		normal_angulo.push_back(zero);
	}

	// Guarda triangulos
	for(int i = 0; i < numTriangles; i++)
	{
		int v1, v2, v3;
		infile >> temp >> v1 >> v2 >> v3;
		Vec3<int> temp(v1,v2,v3);
		triangles.push_back(temp);
	}

	// Calcula normais por face
	for(int i = 0 ; i < numTriangles; i++)
	{
		Vec3<float> v1 = vertices[triangles[i].getX()];
		Vec3<float> v2 = vertices[triangles[i].getY()];
		Vec3<float> v3 = vertices[triangles[i].getZ()];

		Vec3<float> a1 = v3 - v1;
		Vec3<float> a2 = v2 - v1;
		
		Vec3<float> n = a2.cross(a1);
		normal.push_back(n);
	}

	// calcula normais por area
	for(int i = 0 ; i < numTriangles; i++)
	{
		normal_area[triangles[i].getX()] += normal[i];
		normal_area[triangles[i].getY()] += normal[i];
		normal_area[triangles[i].getZ()] += normal[i];
	}

	for(int i = 0 ; i < numTriangles; i++)
	{
		normal[i] = normal[i] / normal[i].norm();
	}
	for(int i = 0 ; i < numVertices; i++)
	{
		normal_area[i] = normal_area[i] / normal_area[i].norm();
	}

	// calcula normais por angulo
	for(int i = 0 ; i < numTriangles; i++)
	{
		Vec3<float> v1 = vertices[triangles[i].getX()];
		Vec3<float> v2 = vertices[triangles[i].getY()];
		Vec3<float> v3 = vertices[triangles[i].getZ()];

		Vec3<float> vec1 = v2 - v1;
		Vec3<float> vec2 = v3 - v1;

		float a1 = acos(vec1.dot(vec2) / (vec1.norm() * vec2.norm()));

		vec1 = v1 - v2;
		vec2 = v3 - v2;

		float a2 = acos(vec1.dot(vec2) / (vec1.norm() * vec2.norm()));

		float a3 = M_PI - a1 - a2;

		normal_angulo[triangles[i].getX()] += normal[i] * a1;
		normal_angulo[triangles[i].getY()] += normal[i] * a2;
		normal_angulo[triangles[i].getZ()] += normal[i] * a3;
	}

	for(int i = 0 ; i < numVertices; i++)
	{
		normal_angulo[i] = normal_angulo[i] / normal_angulo[i].norm();
	}

	Vec3<float> min(vertices[0].getX(), vertices[0].getY(), vertices[0].getZ());
	Vec3<float> max(vertices[0].getX(), vertices[0].getY(), vertices[0].getZ());
	bounding_box.push_back(min);
	bounding_box.push_back(max);

	// Calcula bounding box
	for(int i = 0; i < numVertices; i++)
	{
		if(vertices[i].getX() < bounding_box[0].getX()) 
			bounding_box[0].setX(vertices[i].getX());
		if(vertices[i].getY() < bounding_box[0].getY()) 
			bounding_box[0].setY(vertices[i].getY());
		if(vertices[i].getZ() < bounding_box[0].getZ()) 
			bounding_box[0].setZ(vertices[i].getZ());
		if(vertices[i].getX() > bounding_box[1].getX()) 
			bounding_box[1].setX(vertices[i].getX());
		if(vertices[i].getY() > bounding_box[1].getY()) 
			bounding_box[1].setY(vertices[i].getY());
		if(vertices[i].getZ() > bounding_box[1].getZ()) 
			bounding_box[1].setZ(vertices[i].getZ());

	}

}

std::vector<Vec3<float> > TriangleMesh::getVertices()
{
	return vertices;
}

std::vector<Vec3<float> > TriangleMesh::getBoundingBox()
{
	return bounding_box;
}


std::vector<Vec3<float> > TriangleMesh::getNormal()
{
	return normal;
}

std::vector<Vec3<int> > TriangleMesh::getTriangles()
{
	return triangles;
}

int TriangleMesh::getNumTriangles()
{
	return numTriangles;
}

int TriangleMesh::getNumVertices()
{
	return numVertices;
}
std::vector<Vec3<float> > TriangleMesh::getNormalArea(){
	return normal_area;
}
std::vector<Vec3<float> > TriangleMesh::getNormalAngulo(){
	return normal_angulo;
}