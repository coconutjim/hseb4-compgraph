#pragma once

// size for torus and sphere
const int size = 1;

// for holding point with 3 coordinates
struct point3D {
	double x;
	double y;
	double z;
};

// for holding point with 2 coordinates
struct point2D {
	double x;
	double y;
};

// for parsing vertex
struct vertex {
	point3D point;
	point2D texture;
	point3D part;
};