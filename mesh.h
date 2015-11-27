#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include "Vec3.h"

class TriangleMesh
{
private:
	int numVertices;
	int numTriangles;
	std::vector<Vec3<float> > vertices;
	std::vector<Vec3<float> > normal;
	std::vector<Vec3<float> > normal_area;
	std::vector<Vec3<float> > normal_angulo;
	std::vector<Vec3<int> > triangles;
	std::vector<Vec3<float> > bounding_box;
public:
	TriangleMesh(std::string arq);
	std::vector<Vec3<float> > getVertices();
	std::vector<Vec3<float> > getNormal();
	std::vector<Vec3<float> > getNormalArea();
	std::vector<Vec3<float> > getNormalAngulo();
	std::vector<Vec3<int> > getTriangles();
	int getNumTriangles();
	int getNumVertices();
	std::vector<Vec3<float> > getBoundingBox();
};

#endif