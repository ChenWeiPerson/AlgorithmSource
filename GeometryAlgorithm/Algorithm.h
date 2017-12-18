#ifndef Algorithm_h__
#define Algorithm_h__
#include <math.h>

class Algorithm
{
public:
	Algorithm();
	~Algorithm();
};

typedef float Type;


struct Vector2D
{
	Vector2D()
		:x(0), y(0)
	{}
	Vector2D(Type a1, Type a2)
		:x(a1), y(a2)
	{}
	Type x;
	Type y;
	double length()
	{
		return sqrt( x* x + y * y);
	}
	Vector2D normalize() 
	{
		double l = length();
		return Vector2D(x / l, y / l);
	}
};


struct Line2d
{
	Line2d()
		:A(0),B(0),C(0)
	{}
	Type A;
	Type B;
	Type C;
	typedef Type NumberType;
	//Ax+By+C = 0;
};

//直线到点
Line2d PointToLine(Vector2D p1, Vector2D p2);
//求直线交点
bool LineAcrossPoint(Vector2D * p, Line2d line1, Line2d line2 );
bool LineAcrossPoint(Vector2D * p, Vector2D line1, Vector2D line2);
//求直线平行
bool LineParallel(Line2d line1,Line2d line2 );
bool LineParallel(Vector2D line1, Vector2D line2);
//求直线垂直
bool LineVertical(Line2d line1,Line2d line2 );
bool LineVertical(Vector2D line1, Vector2D line2);

#endif // Algorithm_h__

