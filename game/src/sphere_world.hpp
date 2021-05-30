#pragma once

#include "types.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <raylib.h>

namespace Mb4
{

class SphereWorld
{
public:
	struct Triangle
	{
	public:
		u32 const index1;
		u32 const index2;
		u32 const index3;

		Triangle(u32 const index1, u32 const index2, u32 const index3);
	};
private:
	SphereWorld(std::tuple<std::vector<glm::fvec3>, std::vector<Triangle>>);

	/* Create a geodesic octahedron by subdividing the triangles of a tetrahedron */
	std::tuple<std::vector<glm::fvec3>, std::vector<Triangle>> CreateGeodesicPolyhedron(u32 divisions);

	std::tuple<std::vector<glm::fvec3>, std::vector<Triangle>> SubDivide(std::vector<glm::fvec3> const& points, std::vector<Triangle> const& triangles);
public:
	std::vector<glm::fvec3> const points;
	std::vector<Triangle> const triangles;

	/*
	 * @param divisions start with a tetrahedral and divide triangles this many times.
	 */
	SphereWorld(u32 divisions);

	f32 GetHeight(glm::fvec3 const& position) const;
	glm::fvec3 GetNormal(glm::fvec3 const& position) const;
};

}