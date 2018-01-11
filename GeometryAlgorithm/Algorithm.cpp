#include "Algorithm.h"
#include <math.h>


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
		if (line1.A == 0 && line2.A == 0)
		{
			return false;
		}

		AlgorithmType  d = line1.A / line2.A;
		AlgorithmType y = (line1.C - line2.C*d) / (line1.B - d *line2.B);
		AlgorithmType x = -(y * line1.B + line1.C) / line1.A;
		p->x = x;
		p->y = y;
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
		Line2d l1 = PointToLine(p1, p2);
		Line2d l2 = PointToLine(q1, q2);
		if (LineParallel(l1, l2))
		{
			return false;
		}

		Vector2D t;
		if (LineAcrossPoint(&t, l1, l2))
		{
			if (PointOnSegment(t, p1, p2))
			{
				if (across)
				{
					*across = t;
				}
				return true;
			}

			if (PointOnSegment(t, q1, q2))
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
}