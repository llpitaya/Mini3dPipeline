#ifndef VERTEX_H
#define VERTEX_H
#include"Vec.h"
typedef struct
{
	float r, g, b;
}color_t;

typedef struct
{
	float u, v;
}texcoord_t;

typedef Vec<float> point_t;

class Vertex
{
public:
	void Init();
	void Interp(const Vertex& v1, const Vertex& v2, float t);
	void Division(const Vertex& v1, const Vertex& v2, float w);
	Vertex operator+(const Vertex& v1) const;
	point_t GetPos() const{ return pos;}
	texcoord_t GetTC() const{ return tc;}
	color_t GetColor() const{ return color;}
	void Swap(Vertex& v2);
private:
	point_t pos;
	texcoord_t tc;
	color_t color;
	float rhw;
};
#endif

typedef struct
{
	Vertex v, v1, v2; // v1和v2是端点,v是v1和v2中间的任意一点
} edge_t;

typedef struct
{
	edge_t left, right;
	float up, bottom;

}trapezoid_t;

typedef struct
{
	Vertex v, step;// v: left vertex of scanline, step: (RightVertex - LeftVertex) / width
	int x, y, w; // w = width
}scanline_t;


//对三角形进行拆分
static int trapezoid_init_triangle(trapezoid_t *trap, Vertex &p1,
	Vertex& p2, Vertex& p3)
{
	Vertex temp;
	if (p1.GetPos().GetY() > p2.GetPos().GetY())
	{
		p1.Swap(p2);
	}

	if (p1.GetPos().GetY() > p3.GetPos().GetY())
	{
		p1.Swap(p3);
	}

	if (p2.GetPos().GetY() > p3.GetPos().GetY())
	{
		p2.Swap(p3);
	}

	if (p1.GetPos().GetY()==p2.GetPos().GetY() && p1.GetPos().GetY() == p3.GetPos().GetY())
	{
		return 0;
	}
	if (p1.GetPos().GetX() == p2.GetPos().GetX() && p1.GetPos().GetX()==p3.GetPos().GetX())
	{
		return 0;
	}
	// triangle down
	if (p1.GetPos().GetY() == p2.GetPos().GetY())
	{
		if (p1.GetPos().GetX() > p2.GetPos().GetX())
		{
			p1.Swap(p2);
		}
		trap[0].left.v1 = p1;
		trap[0].left.v2 = p3;
		trap[0].right.v1 = p2;
		trap[0].right.v2 = p3;
		trap[0].up = p1.GetPos().GetY();
		trap[0].bottom = p3.GetPos().GetY();
		return trap[0].bottom > trap[0].up ? 1 : 0;
	}
	
	// triangle up
	if (p2.GetPos().GetY() == p3.GetPos().GetY())
	{
		if (p2.GetPos().GetX() > p3.GetPos().GetX())
		{
			p2.Swap(p3);
		}
		trap[0].left.v1 = p1;
		trap[0].left.v2 = p2;
		trap[0].right.v1 = p1;
		trap[0].right.v2 = p3;
		trap[0].bottom = p2.GetPos().GetY();
		trap[0].up = p1.GetPos().GetY();
		return trap[0].bottom > trap[0].up ? 1 : 0;
	}
	trap[0].bottom = p2.GetPos().GetY();
	trap[0].up = p1.GetPos().GetY();
	trap[1].bottom = p3.GetPos().GetY();
	trap[1].up = p2.GetPos().GetY();

	float k = (p3.GetPos().GetY() - p1.GetPos().GetY()) / (p2.GetPos().GetY() - p1.GetPos().GetY());
	float p4 = p1.GetPos().GetX() + (p2.GetPos().GetX() - p1.GetPos().GetX()) * k;

	//triangle left
	if (p4 <= p3.GetPos().GetX())
	{
		trap[0].left.v1 = p1;
		trap[0].left.v2 = p2;
		trap[0].right.v1 = p1;
		trap[0].right.v2 = p3;

		trap[1].left.v1 = p2;
		trap[1].left.v2 = p3;
		trap[1].right.v1 = p1;
		trap[1].right.v2 = p3;
	}
	else // triangle right
	{
		trap[0].left.v1 = p1;
		trap[0].left.v2 = p3;
		trap[0].right.v1 = p1;
		trap[0].right.v2 = p2;

		trap[1].left.v1 = p1;
		trap[1].left.v2 = p3;
		trap[1].right.v1 = p2;
		trap[1].right.v2 = p3;
	}
	return 2;
}

// 根据Y坐标计算出左右两条边纵坐标等于Y的顶点
static void trapezoid_edge_interp(trapezoid_t &trap, float y)
{
	float s1 = trap.left.v2.GetPos().GetY() - trap.left.v1.GetPos().GetY();
	float s2 = trap.right.v2.GetPos().GetY() - trap.right.v1.GetPos().GetY();
	float t1 = (y - trap.left.v1.GetPos().GetY()) / s1;
	float t2 = (y - trap.right.v2.GetPos().GetY()) / s2;
	trap.left.v.Interp(trap.left.v1, trap.left.v2, t1);
	trap.left.v.Interp(trap.right.v1, trap.right.v2, t2);

}

//根据左右两边的端点初始化扫描线的起点和步长
static void trapezoid_init_scan_line(const trapezoid_t &trap, scanline_t& scanline, int y)
{
	float width = trap.right.v.GetPos().GetX() - trap.left.v.GetPos().GetX();
	scanline.x = (int)(trap.left.v.GetPos().GetX() + 0.5);
	scanline.y = y;
	scanline.w = (int)(trap.right.v.GetPos().GetX() + 0.5) - scanline.x;
	scanline.v = trap.left.v;
	if (trap.left.v.GetPos().GetX() == trap.right.v.GetPos().GetX())
		scanline.w = 0;
	scanline.step.Division(trap.left.v, trap.right.v, width);
}