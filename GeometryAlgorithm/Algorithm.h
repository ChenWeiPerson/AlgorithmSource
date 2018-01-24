#ifndef Algorithm_h__
#define Algorithm_h__
#include <math.h>

namespace Algorithm
{
	#define  AlgorithmMin(a,b) (a<b?a:b)
	#define  AlgorithmMax(a,b) (a>b?a:b)

	typedef float AlgorithmType;
	struct Vector2D
	{
		Vector2D()
			:x(0), y(0)
		{}
		Vector2D(AlgorithmType a1, AlgorithmType a2)
			:x(a1), y(a2)
		{}
		AlgorithmType x;
		AlgorithmType y;
		AlgorithmType length()
		{
			return sqrt( x* x + y * y);
		}
		Vector2D normalize() 
		{
			AlgorithmType l = length();
			return Vector2D(x / l, y / l);
		}
	};


	struct Line2d
	{
		Line2d()
			:A(0),B(0),C(0)
		{}
		AlgorithmType A;
		AlgorithmType B;
		AlgorithmType C;
		typedef AlgorithmType NumberType;
		//Ax+By+C = 0;
	};

	struct Rect2d
	{
		Rect2d()
		{

		}

		Rect2d(Vector2D min, Vector2D max)
		{
			this->min = min;
			this->max = max;
		}

		bool includePoint(Vector2D p)
		{
			return (p.x >= min.x && p.x <= max.x) && (p.y >= min.y && p.y <= max.y);
		}

		void mergePoint(Vector2D p)
		{
			min.x = AlgorithmMin(p.x, min.x);
			min.y = AlgorithmMin(p.y, min.y);
			max.x = AlgorithmMax(p.x, max.x);
			max.y = AlgorithmMax(p.y, max.y);
		}

		Vector2D leftBottom()
		{
			return min;
		}
		Vector2D rightBottom()
		{
			return Vector2D(max.x,min.y);
		}

		Vector2D leftTop()
		{
			return Vector2D(min.x, max.y);
		}

		Vector2D rightTop()
		{
			return max;
		}

		bool include(Rect2d r)
		{
			return includePoint(r.leftBottom()) && includePoint(r.rightBottom()) && 
				includePoint(r.leftTop()) && includePoint(r.rightTop());
		}

		bool intersect(Rect2d r)
		{
			return includePoint(r.leftBottom()) || includePoint(r.rightBottom()) ||
				includePoint(r.leftTop()) || includePoint(r.rightTop()) ||
				 r.includePoint(leftBottom()) || r.includePoint(rightBottom()) ||
				 r.includePoint(leftTop()) || r.includePoint(rightTop());
		}
		Vector2D min;
		Vector2D max;
	};
	//************************************
	// Method:    两点转换为直线
	// FullName:  PointToLine
	// Access:    public 
	// Returns:   Line2d
	// Qualifier:
	// Parameter: Vector2D p1
	// Parameter: Vector2D p2
	//************************************
	Line2d PointToLine(Vector2D p1, Vector2D p2);


	//************************************
	// Method:    直线交点
	// FullName:  LineAcrossPoint
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: Vector2D * p
	// Parameter: Line2d line1
	// Parameter: Line2d line2
	//************************************

	bool LineAcrossPoint(Vector2D * p, Line2d line1, Line2d line2 );

	//************************************
	// Method:    直线平行
	// FullName:  LineParallel
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: Line2d line1
	// Parameter: Line2d line2
	//************************************

	bool LineParallel(Line2d line1,Line2d line2 );
	bool LineParallel(Vector2D line1, Vector2D line2);

	//************************************
	// Method:    直线垂直
	// FullName:  LineVertical
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: Line2d line1
	// Parameter: Line2d line2
	//************************************
	bool LineVertical(Line2d line1,Line2d line2 );
	bool LineVertical(Vector2D line1, Vector2D line2);

	//************************************
	// Method:    点到直线距离
	// FullName:  DistancePointToLine
	// Access:    public 
	// Returns:   AlgorithmType
	// Qualifier:
	// Parameter: Vector2D p
	// Parameter: Line2d line
	//************************************
	AlgorithmType DistancePointToLine(Vector2D p, Line2d line );

	//************************************
	// Method:    点是是否在直线上
	// FullName:  PointOnLine
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: Vector2D p
	// Parameter: Line2d line
	//************************************
	bool PointOnLine(Vector2D p, Line2d line );

	//************************************
	// Method:    点是否在线段上
	// FullName:  PointOnSegment
	// Access:    public 
	// Returns:   bool 是否在线段上
	// Qualifier:
	// Parameter: 判断点 p
	// Parameter: 线段起点 Vector2D p1
	// Parameter: 线段终点 Vector2D p2
	//************************************
	bool PointOnSegment(Vector2D p, Vector2D p1, Vector2D p2 );

	//************************************
	// Method:    两点之间的距离
	// FullName:  PointDistance
	// Access:    public 
	// Returns:   AlgorithmType 距离
	// Qualifier:
	// Parameter: Vector2D p1
	// Parameter: Vector2D p2
	//************************************

	AlgorithmType PointDistance(Vector2D p1, Vector2D p2);

	//************************************
	// Method:    线段交点
	// FullName:  SegmentAcrossPoint
	// Access:    public 
	// Returns:   bool 是否有交点
	// Qualifier:
	// Parameter: Vector2D p1
	// Parameter: Vector2D p2
	// Parameter: Vector2D q1
	// Parameter: Vector2D q2
	// Parameter: Vector2D * across 交点
	//************************************
	bool SegmentAcrossPoint(Vector2D p1, Vector2D p2, Vector2D q1, Vector2D q2, Vector2D * across = NULL );

	
	//************************************
	// Method:    两点到矩形
	// FullName:  Algorithm::PointToRect
	// Access:    public 
	// Returns:   Algorithm::Rect2d
	// Qualifier:
	// Parameter: Vector2D p1
	// Parameter: Vector2D p2
	//************************************
	Rect2d PointToRect(Vector2D p1, Vector2D p2);
};




namespace AlgorithmPoint
{
	struct Point
	{
		Point(float a, float b)
			:x(a),y(b)
		{

		}
		Point()
		{}
		float x, y;
	};
}

bool ab_cross_cd(AlgorithmPoint::Point & a, AlgorithmPoint::Point & b, AlgorithmPoint::Point & c, AlgorithmPoint::Point & d, AlgorithmPoint::Point & P);
void test();
#endif // Algorithm_h__

