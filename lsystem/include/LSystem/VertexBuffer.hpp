#pragma once

#include <vector>

#include <glm/glm.hpp>



namespace LSystem
{

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 color; // No transparency for now
		// no uv's or normals for now either
	};

	struct Line
	{
		Vertex point_a;
		Vertex point_b;
	};

	// TODO: think about winding order
	struct Triangle
	{
		Vertex point_1;
		Vertex point_2;
		Vertex point_3;
	};

	struct VertexBuffer
	{
		std::vector<Line> lines;
		std::vector<Triangle> triangles;

		Triangle& AddTriangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
		{
			triangles.emplace_back();
			triangles.back().point_1.position = a;
			triangles.back().point_2.position = b;
			triangles.back().point_3.position = c;
			return triangles.back();
		}

	};

}
