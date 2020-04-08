#pragma once
#include"Vector2.h"
#include <vector>

//bool doIntersect(Vector2f p1, Vector2f q1, Vector2f p2, Vector2f q2);

//Vector2f lineLineIntersection(Vector2f A, Vector2f B, Vector2f C, Vector2f D);

bool PointInPolygon(Vector2f point, std::vector<Vector2f> polygonPoints);

struct Line
{
	public:
	Vector2f p;
	Vector2f q;
};

bool get_line_intersection(Vector2f p1, Vector2f q1, Vector2f p2, Vector2f q2, float *i_x, float *i_y);


//void Line(Vector2f p1, Vector2f q1);
