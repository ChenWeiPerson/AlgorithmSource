#include "Algorithm.h"
#include <math.h>
#define ZeroNumber(a) (fabs(a)<1e-6)

namespace Algorithm
{


	// ��ֱ֪���ϵ�����P1(X1, Y1) P2(X2, Y2)�� P1 P2���㲻�غϡ���ֱ�ߵ�һ��ʽ����AX + BY + C = 0�У�A B C�ֱ���ڣ�
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

	// ��ֱ��L1:A1x + B1y + C1 = 0
	// 	L1 : A2x + B2y + C2 = 0
	// 	��1��ƽ�У�A1B2 - A2B1 = 0����ֱ�߲��غ�
	// 	��2����ֱ��A1A2 + B1B2 = 0
	// 	��3���ཻ��A1B2 - A2B1��0


	// a, b����������
	// a = ��a1, a2�� b = ��b1, b2��
	// a//b��a1/b1=a2/b2 �� a1b1=a2b2 ��a=��b,����һ������
	// a��ֱb��a1b1 + a2b2 = 0

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

	Rect2d PointToRect(Vector2D p1, Vector2D p2)
	{
		Rect2d r(p1,p2);
		r.mergePoint(p1);
		r.mergePoint(p2);
		return r;
	}

}


namespace AlgorithmPoint
{
	const int N = 100010;
	int mark[N];
	struct stline
	{
		Point a, b;
	} line1, line2, p[N];

	int dblcmp(float a, float b)
	{
		if (fabs(a - b) <= 1E-6) return 0;
		if (a>b) return 1;
		else return -1;
	}
	//***************����е��Ƿ����߶���***************
	float dot(float x1, float y1, float x2, float y2) //���
	{
		return x1*x2 + y1*y2;
	}

	int point_on_line(Point a, Point b, Point c) //��a���ǲ������߶�bc�ϣ�>0���ڣ�=0��˵��غϣ�<0�ڡ�
	{
		return dblcmp(dot(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y), 0);
	}
	//**************************************************
	float cross(float x1, float y1, float x2, float y2)
	{
		return x1*y2 - x2*y1;
	}
	float ab_cross_ac(Point a, Point b, Point c) //ab��ac�Ĳ��
	{
		return cross(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
	}
	int ab_cross_cd(Point a, Point b, Point c, Point d, Point & acorss) //��ab�Ƿ���cd�ཻ������Ϊp��1�淶�ཻ��0������һ�߶εĶ˵㣬-1���ཻ��
	{
		float s1, s2, s3, s4;
		int d1, d2, d3, d4;
		Point p;
		d1 = dblcmp(s1 = ab_cross_ac(a, b, c), 0);
		d2 = dblcmp(s2 = ab_cross_ac(a, b, d), 0);
		d3 = dblcmp(s3 = ab_cross_ac(c, d, a), 0);
		d4 = dblcmp(s4 = ab_cross_ac(c, d, b), 0);

		//����淶�ཻ���󽻵�
		if ((d1^d2) == -2 && (d3^d4) == -2)
		{
			p.x = (c.x*s2 - d.x*s1) / (s2 - s1);
			p.y = (c.y*s2 - d.y*s1) / (s2 - s1);
			acorss = p;
			return 1;
		}

		//������淶�ཻ
		if (d1 == 0 && point_on_line(c, a, b) <= 0)
		{
			p = c;
			acorss = p;
			return 0;
		}
		if (d2 == 0 && point_on_line(d, a, b) <= 0)
		{
			p = d;
			acorss = p;
			return 0;
		}
		if (d3 == 0 && point_on_line(a, c, d) <= 0)
		{
			p = a;
			acorss = p;
			return 0;
		}
		if (d4 == 0 && point_on_line(b, c, d) <= 0)
		{
			p = b;
			acorss = p;
			return 0;
		}
		//������ཻ
		return -1;
	}

}

bool ab_cross_cd(AlgorithmPoint::Point & a, AlgorithmPoint::Point & b, AlgorithmPoint::Point & c, AlgorithmPoint::Point & d, AlgorithmPoint::Point & P)
{
	AlgorithmPoint::Point  t;

	if (AlgorithmPoint::ab_cross_cd(a, b, c, d, t) >= 0)
	{
		P = t;
		return true;
	}
	return false;
}

void test()
{
	float as = AlgorithmPoint::cross(1, 2, 4, 5);
	int a = 0;
}
