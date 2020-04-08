#include "SupportingCalc.h"
#include "Vector2.h"
#include <algorithm> 
#include <vector>
#include <tuple>

bool PointInPolygon(Vector2f point, std::vector<Vector2f> polygonPoints) {
	int i, j, nvert = polygonPoints.size();
	bool c = false;

	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		if (((polygonPoints[i].y >= point.y) != (polygonPoints[j].y >= point.y)) &&
			(point.x <= (polygonPoints[j].x - polygonPoints[i].x) * (point.y - polygonPoints[i].y) / (polygonPoints[j].y - polygonPoints[i].y) + polygonPoints[i].x)
			)
			c = !c;
	}

	return c;
}



bool get_line_intersection(Vector2f p1, Vector2f q1, Vector2f p2, Vector2f q2, float *i_x, float *i_y)
{
	float s02_x, s02_y, s10_x, s10_y, s32_x, s32_y, s_numer, t_numer, denom, t;
	s10_x = q1.x - p1.x;
	s10_y = q1.y - p1.y;
	s32_x = q2.x - p2.x;
	s32_y = q2.y - p2.y;

	denom = s10_x * s32_y - s32_x * s10_y;
	if (denom == 0)
		return false; // Collinear
	bool denomPositive = denom > 0;

	s02_x = p1.x - p2.x;
	s02_y = p1.y - p2.y;
	s_numer = s10_x * s02_y - s10_y * s02_x;
	if ((s_numer < 0) == denomPositive)
		return false; // No collision

	t_numer = s32_x * s02_y - s32_y * s02_x;
	if ((t_numer < 0) == denomPositive)
		return false; // No collision

	if (((s_numer > denom) == denomPositive) || ((t_numer > denom) == denomPositive))
		return false; // No collision
	// Collision detected
	t = t_numer / denom;
	if (i_x != NULL)
		*i_x = p1.x + (t * s10_x);
	if (i_y != NULL)
		*i_y = p1.y + (t * s10_y);

	return true;
}
