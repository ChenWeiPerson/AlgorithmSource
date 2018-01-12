//#include "stdafx.h"
#include "Algorithm.h"
#include <math.h>
#define ZeroNumber(a) (fabs(a)<1e-6)

namespace Algorithm
{


	// 已知直线上的两点P1(X1, Y1) P2(X2, Y2)， P1 P2两点不重合。则直线的一般式方程AX + BY + C = 0中，A B C分别等于：
	// A = Y2 - Y1
	// B = X1 - X2
	// C = X2*Y1 - X1*Y2
	Line2d PointToLine(Vector2D p1, Vector2D p2)
	{
		Line2d line;
		line.A = p2.y - p1.y;
		line.B = p1.x - p2.x;
		line.C = p2.x * p1.y - p1.x * p2.y;

		return line;
	}

	bool LineAcrossPoint(Vector2D * p, Line2d line1, Line2d line2)
	{
		if (LineParallel(line1, line2))
		{
			return false;
		}

		if (line1.A == 0 && line2.A == 0)
		{
			return false;
		}

		if ( ZeroNumber(line1.A) && !ZeroNumber(line1.B) )
		{
			AlgorithmType y = -line1.C / line1.B;
			AlgorithmType x = -(line2.B*y+line2.C)/line2.A;
			p->x = x;
			p->y = y;
		}
		else if (ZeroNumber(line2.A) && !ZeroNumber(line2.B) )
		{
			AlgorithmType y = -line2.C / line2.B;
			AlgorithmType x = -(line1.B*y + line1.C) / line1.A;
			p->x = x;
			p->y = y;
		}
		else if (ZeroNumber(line1.B) && !ZeroNumber(line1.A))
		{
			AlgorithmType x = -line1.C / line1.A;
			AlgorithmType y = -(line2.A*x + line2.C) / line2.B;
			p->x = x;
			p->y = y;
		}
		else if (ZeroNumber(line2.B) && !ZeroNumber(line2.A))
		{
			AlgorithmType x = -line2.C / line2.A;
			AlgorithmType y = -(line1.A*x + line1.C) / line1.B;
			p->x = x;
			p->y = y;
		}
// 		if ( ( fabs(line1.A ) < 1e-6 ) && (fabs(line1.B) > 1e-6))
// 		{
// 			AlgorithmType y = -line1.C / line1.B;
// 			AlgorithmType x = (-line2.C - line2.B * y)/line2.A;
// 			p->x = x;
// 			p->y = y;
// 		}
// 		else if ((fabs(line2.A) < 1e-6) && (fabs(line2.B) > 1e-6))
// 		{
// 			AlgorithmType y = -line2.C / line2.B;
// 			AlgorithmType x = (-line1.C - line1.B * y) / line1.A;
// 			p->x = x;
// 			p->y = y;
// 		}
		else
		{
			AlgorithmType  d = line1.A / line2.A;
			AlgorithmType y = (line1.C - line2.C*d) / (line1.B - d *line2.B);
			AlgorithmType x = -(y * line1.B + line1.C) / line1.A;
			p->x = x;
			p->y = y;
		}
		
		return true;
	}

	// 设直线L1:A1x + B1y + C1 = 0
	// 	L1 : A2x + B2y + C2 = 0
	// 	（1）平行：A1B2 - A2B1 = 0且两直线不重合
	// 	（2）垂直：A1A2 + B1B2 = 0
	// 	（3）相交：A1B2 - A2B1≠0


	// a, b是两个向量
	// a = （a1, a2） b = （b1, b2）
	// a//b：a1/b1=a2/b2 或 a1b1=a2b2 或a=λb,λ是一个常数
	// a垂直b：a1b1 + a2b2 = 0

	bool LineParallel(Line2d line1, Line2d line2)
	{
		return fabs(line1.A*line2.B - line2.A * line1.B) < 1e-6;
	}

	bool LineParallel(Vector2D line1, Vector2D line2)
	{
		Vector2D l1 = line1.normalize();
		Vector2D l2 = line1.normalize();

		return l1.x*l2.y == l2.x * l1.y;
	}

	bool LineVertical(Line2d line1, Line2d line2)
	{
		return fabs(line1.A*line2.A - line2.B * line1.B) < 1e-6;
	}

	bool LineVertical(Vector2D line1, Vector2D line2)
	{
		Vector2D l1 = line1.normalize();
		Vector2D l2 = line1.normalize();

		return fabs(l1.x*l2.x + l1.y* l2.y) < 1e-6;
	}

	AlgorithmType DistancePointToLine(Vector2D p, Line2d line)
	{
		return fabs(line.A * p.x + line.B * p.y + line.C) / sqrt(line.A* line.A + line.B * line.B);
	}

	bool PointOnLine(Vector2D p, Line2d line)
	{
		return fabs(line.A * p.x + line.B * p.y + line.C) < 1e-6;
	}

	bool PointOnSegment(Vector2D p, Vector2D p1, Vector2D p2)
	{
		AlgorithmType d = PointDistance(p1, p2);
		AlgorithmType d1 = PointDistance(p, p1);
		AlgorithmType d2 = PointDistance(p, p2);

		return fabs(d - (d1 + d2)) < 1e-6;
	}

	AlgorithmType PointDistance(Vector2D p1, Vector2D p2)
	{
		return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	}

	bool SegmentAcrossPoint(Vector2D p1, Vector2D p2, Vector2D q1, Vector2D q2, Vector2D * across /*= NULL */)
	{
		if (!PointToRect(p1, p2).intersect(PointToRect(q1, q2)))
		{
			return false;
		}

		Line2d l1 = PointToLine(p1, p2);
		Line2d l2 = PointToLine(q1, q2);
		if (LineParallel(l1, l2))
		{
			return false;
		}

		Vector2D t;
		if (LineAcrossPoint(&t, l1, l2))
		{
			if (PointOnSegment(t, p1, p2) && PointOnSegment(t, q1, q2) )
			{
				if (across)
				{
					*across = t;
				}
				return true;
			}
		}

		return false;
	}

	bool SegmentAcrossPoint(AlgorithmType * x, AlgorithmType * y)
	{
		AlgorithmType x1 = x[0];//s1
		AlgorithmType y1 = y[0];

		AlgorithmType x2 = x[1];
		AlgorithmType y2 = y[1];



		AlgorithmType x3 = x[2];//s2
		AlgorithmType y3 = y[2];

		AlgorithmType x4 = x[3];
		AlgorithmType y4 = y[3];

		intersect(x, y);

		return false;
	}

	bool intersect(AlgorithmType * x, AlgorithmType * y)
	{
		AlgorithmType x1 = x[0];//s1
		AlgorithmType y1 = y[0];

		AlgorithmType x2 = x[1];
		AlgorithmType y2 = y[1];



		AlgorithmType x3 = x[2];//s2
		AlgorithmType y3 = y[2];

		AlgorithmType x4 = x[3];
		AlgorithmType y4 = y[3];


		AlgorithmType minx1 = AlgorithmMax(x1, x2);
		AlgorithmType miny1 = AlgorithmMax(y1, y2);

		AlgorithmType minx2 = AlgorithmMax(x3, x4);
		AlgorithmType miny2 = AlgorithmMax(y3, y4);



	}

	Rect2d PointToRect(Vector2D p1, Vector2D p2)
	{
		Rect2d r(p1,p2);
		r.mergePoint(p1);
		r.mergePoint(p2);
		return r;
	}

}