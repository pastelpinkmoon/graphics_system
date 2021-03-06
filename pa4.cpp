#include "stdafx.h"
#include"PA4.h" 
#include<iostream>
using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////
//CLASS POINT
Point::Point(int a, int b)
{
	x = a;
	y = b;
}
Point::Point(const Point&a)
{
	x = a.x;
	y = a.y;
}
Point& Point::operator =(Point&a)
{
	this->x = a.x;
	this->y = a.y;
	return *this;
}
Point& Point::operator+(Point a)
{
	x += a.x;
	y += a.y;
	return *this;
}
Point& Point::operator+=(Point a)
{
	x += a.x;
	y += a.y;
	return *this;
}
/*Point& Point::operator*(float a)
{
	x *= a;
	y *= a;
	return *this;
}*/
Point Point::right(int n)
{
	this->x += n;
	return *this;
}
Point Point::left(int n)
{
	this->x -= n;
	return *this;
}
Point Point::up(int n)
{
	this->y -= n;
	return *this;
}
Point Point::down(int n)
{
	this->y += n;
	return *this;
}
int Point::get_x()
{
	return this->x;
}
int Point::get_y()
{
	return this->y;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//CLASS DISPWINDOW
DispWindow::DispWindow(int a, int b)
{
	Point x(0, 0);
	orijin = x;
	n = a;
	m = b;
	buffer = new char*[m];
	for (int i = 0; i < m; i++)
		buffer[i] = new char[n];
	//lets make it empty
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			buffer[i][j] = ' ';
}
void DispWindow::show()
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cout << buffer[i][j];
		cout << endl;
	}

}

/*template<typename T>
void DispWindow::draw(T& a)
{
	a.draw(*this);
}
/*
template<typename T>
void DispWindow<Dot>::draw(T a)
{
	a.draw(*this);
}
template<typename T>
void DispWindow<Line>::draw(T a)
{
	a.draw(*this);
}
template<typename T>
void DispWindow<Rectangle>::draw(T a)
{
	a.draw(*this);
}*/
Point DispWindow::current()
{
	return this->orijin;
}
Point DispWindow::current(Point _p)
{
	this->orijin = _p;
	return this->orijin;
}
int DispWindow::get_n()
{
	return this->n;
}
int DispWindow::get_m()
{
	return this->m;
}
void DispWindow::set_orijin(Point a)
{
	this->orijin = a;
}
void DispWindow::get_buffer(int a, int b, char c)
{
	this->buffer[b][a] = c;
}
//CLASS DOT
Dot::Dot(Point x)//constructor
{
	a = x;
}
void Dot::draw(DispWindow& w)
{
	if (this->a.get_x() < w.get_n() && this->a.get_y() < w.get_m())
		w.get_buffer(this->a.get_x(), this->a.get_y(), '*');
	w.set_orijin(this->a);

}

Point Dot::se()
{
	return this->_se;
}
Point Dot::s()
{
	return this->_s;
}
Point Dot::e()
{
	return this->_e;
}
Point Dot::w()
{
	return this->_w;
}
Point Dot::n()
{
	return this->_n;
}
Point Dot::ne()
{
	return this->_ne;
}
Point Dot::nw()
{
	return this->_nw;
}
Point Dot::sw()
{
	return this->_sw;
}
Point Dot::c()
{
	return this->_c;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//CLASS RECTANGLE
Rectangle::Rectangle(Point _a, Point _b)//construcor
{
	a = _a;
	b = _b;
	Point ne(b.get_x(), a.get_y());
	Point nw(a.get_x(), a.get_y());
	Point sw(a.get_x(), b.get_y());
	Point se(b.get_x(), b.get_y());
	int l_x = a.get_x();
	int b_x = b.get_x();
	if (a.get_x()>b.get_x())
	{
		l_x = b.get_x();
		b_x = a.get_x();
	}
	int l_y = a.get_y();
	int b_y = b.get_y();
	if (a.get_y()>b.get_y())
	{
		l_y = b.get_y();
		b_y = a.get_y();
	}
	Point n(((b_x - l_x) / 2 + l_x), a.get_y());
	Point s(((b_x - l_x) / 2 + l_x), b.get_y());
	Point c(((b_x - l_x) / 2 + l_x), ((b_y - l_y) / 2 + l_y));
	this->_ne = ne;
	this->_n = n;
	this->_nw = nw;
	this->_sw = sw;
	this->_c = c;
	this->_se = se;
	this->_s = s;
}
void Rectangle::draw(DispWindow& w)
{
	int less_y = this->a.get_y();
	int big_y = this->b.get_y();
	int less_x = this->a.get_x();
	int big_x = this->b.get_x();
	if (this->a.get_y() > this->b.get_y())
	{
		big_x = this->a.get_x();
		less_x = this->b.get_x();
		less_y = this->b.get_y();
		big_y = this->a.get_y();
	}

	for (int j = less_y; j< big_y; j++)
	{
		if (j<w.get_m())
		{
			if (less_x<big_x)
			{
				for (int i = less_x; i<big_x + 1; i++)
				{
					if (i <= w.get_n())
					{
						w.get_buffer(i, this->a.get_y(), '*');
						if (this->b.get_y()<w.get_m())
							w.get_buffer(i, this->b.get_y(), '*');
					}
				}
				w.get_buffer(this->a.get_x(), j, '*');
				if (this->b.get_x()<w.get_n())
					w.get_buffer(this->b.get_x(), j, '*');
			}
			if (less_x>big_x)
			{
				for (int i = less_x; i>big_x + 1; i--)
				{
					if (i <= w.get_n())
					{
						w.get_buffer(i, this->a.get_y(), '*');
						if (this->b.get_y()<w.get_m())
							w.get_buffer(i, this->b.get_y(), '*');
					}
				}
				w.get_buffer(this->a.get_x(), j, '*');
				if (this->b.get_x()<w.get_n())
					w.get_buffer(this->b.get_x(), j, '*');
			}
		}

	}

	w.set_orijin(this->b);

}
Point Rectangle::se()
{
	return this->_se;
}
Point Rectangle::s()
{
	return this->_s;
}
Point Rectangle::e()
{
	return this->_e;
}
Point Rectangle::w()
{
	return this->_w;
}
Point Rectangle::n()
{
	return this->_n;
}
Point Rectangle::ne()
{
	return this->_ne;
}
Point Rectangle::nw()
{
	return this->_nw;
}
Point Rectangle::sw()
{
	return this->_sw;
}
Point Rectangle::c()
{
	return this->_c;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//CLASS LINE
Line::Line(Point _a, Point _b)//constructor
{
	a = _a;
	b = _b;
	Point ne(b.get_x(), a.get_y());
	Point nw(a.get_x(), a.get_y());
	Point sw(a.get_x(), b.get_y());
	Point se(b.get_x(), b.get_y());
	int l_x = a.get_x();
	int b_x = b.get_x();
	if (a.get_x()>b.get_x())
	{
		l_x = b.get_x();
		b_x = a.get_x();
	}
	int l_y = a.get_y();
	int b_y = b.get_y();
	if (a.get_y()>b.get_y())
	{
		l_y = b.get_y();
		b_y = a.get_y();
	}
	Point n(((b_x - l_x) / 2 + l_x), a.get_y());
	Point s(((b_x - l_x) / 2 + l_x), b.get_y());
	Point c(((b_x - l_x) / 2 + l_x), ((b_y - l_y) / 2 + l_y));
	this->_ne = ne;
	this->_n = n;
	this->_nw = nw;
	this->_sw = sw;
	this->_c = c;
	this->_se = se;
	this->_s = s;
}
void Line::draw(DispWindow& w)
{
	int x1 = a.x, x2 = b.x, y1 = a.y, y2 = b.y;
	int dx, dy, i, e;
	int inc_x, inc_y, inc_1, inc_2;
	int x, y;

	dx = x2 - x1;
	dy = y2 - y1;

	if (dx < 0) dx = -1 * dx;
	if (dy < 0) dy = -1 * dy;
	inc_x = 1;
	if (x2 < x1)
		inc_x = -1;

	inc_y = 1;
	if (y2 < y1)
		inc_y = -1;

	x = x1; y = y1;


	if (dx > dy)
	{
		if (x<w.get_n() && y<w.get_m())
			w.get_buffer(x, y, '*');
		e = 2 * dy - dx;
		inc_1 = 2 * (dy - dx);
		inc_2 = 2 * dy;
		for (i = 0; i<dx; i++)
		{
			if (e >= 0)
			{
				y += inc_y;
				e += inc_1;
			}
			else
			{
				e += inc_2;
			}
			x += inc_x;
			if (x<w.get_n() && y<w.get_m())
				w.get_buffer(x, y, '*');
		}

	}
	else
	{
		if (x<w.get_n() && y<w.get_m())
			w.get_buffer(x, y, '*');
		e = 2 * dx - dy;
		inc_1 = 2 * (dx - dy);
		inc_2 = 2 * dx;
		for (i = 0; i<dy; i++)
		{
			if (e >= 0)
			{
				x += inc_x;
				e += inc_1;
				y += inc_y;

			}
			else
			{
				if (a.x>b.x)
				{
					if (x + 1<w.get_n() && y<w.get_m())
						w.get_buffer(x + 1, y, '*');
				}
				if (a.x<b.x)
				{
					if (x - 1<w.get_n() && y<w.get_m())
						w.get_buffer(x - 1, y, '*');
				}
				e += inc_2;
				y += inc_y;

			}
			if (x<w.get_n() && y<w.get_m())
				w.get_buffer(x, y, '*');
		}
	}


	w.set_orijin(this->b);

}
Point Line::se(){return this->_se;}
Point Line::s(){return this->_s;}
Point Line::e(){return this->_e;}
Point Line::w(){return this->_w;}
Point Line::n(){return this->_n;}
Point Line::ne(){return this->_ne;}
Point Line::nw(){return this->_nw;}
Point Line::sw(){return this->_sw;}
Point Line::c(){return this->_c;}
///////////////////////////////////////////////////////////////////////////////////////////////////
