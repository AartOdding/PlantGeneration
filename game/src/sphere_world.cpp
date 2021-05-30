#include "sphere_world.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include "debug.hpp"
#include <string>
#include <map>

#include <glm/gtc/noise.hpp>

using namespace Mb4;

SphereWorld::Triangle::Triangle(u32 const index1, u32 const index2, u32 const index3) :
	index1(index1),
	index2(index2),
	index3(index3)
{}

SphereWorld::SphereWorld(u32 divisions) :
	SphereWorld(CreateGeodesicPolyhedron(divisions))
{}

SphereWorld::SphereWorld(std::tuple<std::vector<glm::fvec3>, std::vector<SphereWorld::Triangle>> pointsAndTriangles) :
	points(std::get<0>(pointsAndTriangles)),
	triangles(std::get<1>(pointsAndTriangles))
{}

std::tuple<std::vector<glm::fvec3>, std::vector<SphereWorld::Triangle>> SphereWorld::CreateGeodesicPolyhedron(u32 divisions)
{
	/*
    const f32 coord1 = glm::normalize(glm::fvec2(1.0_f32, 1.0_f32 / std::sqrt(2.0_f32))).x;
    const f32 coord2 = glm::normalize(glm::fvec2(1.0_f32, 1.0_f32 / std::sqrt(2.0_f32))).y;

	std::vector<glm::fvec3> points = {
		{coord1, 0.0_f32, -coord2},
		{-coord1, 0.0_f32, -coord2},
		{0.0_f32, coord1, coord2},
		{0.0_f32, -coord1, coord2}
	};
	std::vector<SphereWorld::Triangle> triangles = {
		{0, 2, 1},
		{0, 1, 3},
		{0, 3, 2},
		{1, 2, 3}
	};*/

	std::vector<glm::fvec3> points = {
		{1.0_f32, 0.0_f32, 0.0_f32},
		{-1.0_f32, 0.0_f32, 0.0_f32},
		{0.0_f32, 1.0_f32, 0.0_f32},
		{0.0_f32, -1.0_f32, 0.0_f32},
		{0.0_f32, 0.0_f32, 1.0_f32},
		{0.0_f32, 0.0_f32, -1.0_f32}
	};
	std::vector<SphereWorld::Triangle> triangles = {
		{0, 2, 4},
		{0, 4, 3},
		{0, 3, 5},
		{0, 5, 2},
		{1, 4, 2},
		{1, 3, 4},
		{1, 5, 3},
		{1, 2, 5}
	};

	for (u32 i = 0; i < divisions; ++i)
	{
		auto [new_points, new_triangles] = SubDivide(points, triangles);
		points = std::move(new_points);
		triangles = std::move(new_triangles);
	}

	for (glm::fvec3& point : points)
	{
		glm::fvec3 noise({0.0_f32,  0.0_f32, 0.0_f32});
		noise += point * std::pow(glm::simplex(point * 0.9_f32), 3.0_f32) * 0.4_f32;
		//noise += point * glm::simplex(point * 1.0_f32) * 0.1_f32;
		point += noise;
	}

	return {points, triangles};
}

std::tuple<std::vector<glm::fvec3>, std::vector<SphereWorld::Triangle>> SphereWorld::SubDivide(std::vector<glm::fvec3> const& points, std::vector<Triangle> const& triangles)
{
	std::vector<glm::fvec3> new_points = points;
	// points in between two original points. (smallest original, largest original) -> new point
	std::map<std::tuple<u32, u32>, u32> points_inbetween;
	std::vector<Triangle> new_triangles;

	for (Triangle const& triangle : triangles)
	{
		// create new points
		u32 point12index;
		auto point12find = points_inbetween.find(std::make_tuple(std::min(triangle.index1, triangle.index2), std::max(triangle.index1, triangle.index2)));
		if (point12find == points_inbetween.end())
		{
			new_points.emplace_back(glm::normalize(points[triangle.index1] + points[triangle.index2]));
			point12index = new_points.size() - 1;
			points_inbetween.emplace(std::make_pair(std::make_tuple(triangle.index1, triangle.index2), point12index));
		}
		else
		{
			point12index = point12find->second;
		}

		u32 point13index;
		auto point13find = points_inbetween.find(std::make_tuple(std::min(triangle.index1, triangle.index3), std::max(triangle.index1, triangle.index3)));
		if (point13find == points_inbetween.end())
		{
			new_points.emplace_back(glm::normalize(points[triangle.index1] + points[triangle.index3]));
			point13index = new_points.size() - 1;
			points_inbetween.emplace(std::make_pair(std::make_tuple(triangle.index1, triangle.index3), point13index));
		}
		else
		{
			point13index = point13find->second;
		}

		u32 point23index;
		auto point23find = points_inbetween.find(std::make_tuple(std::min(triangle.index2, triangle.index3), std::max(triangle.index2, triangle.index3)));
		if (point23find == points_inbetween.end())
		{
			new_points.emplace_back(glm::normalize(points[triangle.index2] + points[triangle.index3]));
			point23index = new_points.size() - 1;
			points_inbetween.emplace(std::make_pair(std::make_tuple(triangle.index2, triangle.index3), point23index));
		}
		else
		{
			point23index = point23find->second;
		}

		// create new triangles
		new_triangles.emplace_back(SphereWorld::Triangle(triangle.index1, point12index, point13index));
		new_triangles.emplace_back(SphereWorld::Triangle(point12index, triangle.index2, point23index));
		new_triangles.emplace_back(SphereWorld::Triangle(point13index, point23index, triangle.index3));
		new_triangles.emplace_back(SphereWorld::Triangle(point12index, point23index, point13index));
	}

	return {new_points, new_triangles};
}