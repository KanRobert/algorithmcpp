#pragma once
#include"stdrandom.h"
#include<functional>
#include<iostream>
#include<cmath>
#include<stdexcept>
#include<string>
#include<vector>
#include<algorithm>

namespace algorithmcpp {
	class Point2D final {
		friend bool operator<(const Point2D &, const Point2D &);
		friend bool operator>(const Point2D &, const Point2D &);
		friend bool operator==(const Point2D &, const Point2D &);
		friend bool operator<=(const Point2D &, const Point2D &);
		friend bool operator>=(const Point2D &, const Point2D &);
		friend int Compare(const Point2D &, const Point2D &);
	public:
		static const std::function<int(Point2D, Point2D)> x_order_;
		static const std::function<int(Point2D, Point2D)> y_order_;
		static const std::function<int(Point2D, Point2D)> r_order_;
		
	private:
		double xcoordinate_;
	    double ycoordinate_;

	public:
		Point2D() = default;
		Point2D(const Point2D &) = default;
		Point2D &operator=(const Point2D &p) = default;
		Point2D(Point2D &&) noexcept = default;
		Point2D &operator=(Point2D &&) noexcept = default;
		~Point2D() = default;

		Point2D(double x, double y) :xcoordinate_(x), ycoordinate_(y) {
			if (!std::isfinite(x) || !std::isfinite(y))
				throw std::invalid_argument("Coordinates must be finite");
			if(std::isnan(x) || std::isnan(y))
				throw std::invalid_argument("Coordinates cannot be NaN");
		}

		static double Area(const Point2D &a, const Point2D &b, const Point2D &c) {
			return (b.xcoordinate_ - a.xcoordinate_)*(c.ycoordinate_ - a.ycoordinate_)
				- (b.ycoordinate_ - a.ycoordinate_)*(c.xcoordinate_ - a.xcoordinate_);
		}

		static int Ccw(const Point2D &a, const Point2D &b, const Point2D &c) {
			double area = Area(a, b, c);
			if (area < 0) return -1;
			if (area > 0) return +1;
			else return 0;
		}

		static int XOrder(const Point2D &p, const Point2D &q) {
			if (p.xcoordinate_ < q.xcoordinate_) return -1;
			if (p.xcoordinate_ > q.xcoordinate_) return +1;
			return 0;
		}

		static int YOrder(const Point2D &p, const Point2D &q) {
			if (p.ycoordinate_ < q.ycoordinate_) return -1;
			if (p.ycoordinate_ > q.ycoordinate_) return +1;
			return 0;
		}

		static int ROrder(const Point2D &p, const Point2D &q) {
			double delta= (p.xcoordinate_*p.xcoordinate_ + p.ycoordinate_*p.ycoordinate_) - (q.xcoordinate_*q.xcoordinate_ + q.ycoordinate_*q.ycoordinate_);
			if (delta<0) return -1;
			if (delta>0) return +1;
			return 0;
		}

		int Atan2Order(const Point2D &p, const Point2D &q) {
			double angle1 = AngleTo(p);
			double angle2 = AngleTo(q);
			if (angle1<angle2) return -1;
			if (angle1>angle2) return +1;
			return 0;
		}

		int PolorOrder(const Point2D &p, const Point2D &q) {
			double dx1 = p.xcoordinate_ - xcoordinate_;
			double dy1 = p.ycoordinate_ - ycoordinate_;
			double dx2 = q.xcoordinate_ - xcoordinate_;
			double dy2 = q.ycoordinate_ - ycoordinate_;

			if (dy1 >= 0 && dy2 < 0) return -1;
			else if (dy2 >= 0 && dy1 < 0) return +1;
			else if (dy1 == 0 && dy2 == 0) {
				if (dx1 >= 0 && dx2 < 0) return -1;
				if (dx2 >= 0 && dx1 < 0) return +1;
				else return 0;
			}
			else return -Ccw(*this, p, q);
		}

		int DistanceOrder(const Point2D &p, const Point2D &q) {
			double dist1 = DistanceSquaredTo(p);
			double dist2 = DistanceSquaredTo(q);
			if (dist1<dist2) return -1;
			if (dist1>dist2) return +1;
			return 0;
		}

		double X(){
			return xcoordinate_;
		}

		double Y() {
			return ycoordinate_;
		}

		double R() {
			return std::sqrt(xcoordinate_*xcoordinate_ + ycoordinate_*ycoordinate_);
		}

		double Theta() {
			return std::atan2(ycoordinate_, xcoordinate_);
		}

		double AngleTo(const Point2D &that) {
			double dx = that.xcoordinate_ - xcoordinate_;
			double dy = that.ycoordinate_ - ycoordinate_;
			return std::atan2(dy, dx);
		}

		double DistanceTo(Point2D that) {
			double dx = xcoordinate_ - that.xcoordinate_;
			double dy = xcoordinate_ - that.xcoordinate_;
			return std::sqrt(dx*dx + dy*dy);
		}

		double DistanceSquaredTo(Point2D that) {
			double dx = xcoordinate_ - that.xcoordinate_;
			double dy = xcoordinate_ - that.xcoordinate_;
			return dx*dx + dy*dy;
		}

		std::string ToString() const {
			return "(" + std::to_string(xcoordinate_) + ", " + std::to_string(ycoordinate_) + ")";
		}

		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			std::vector<Point2D> pvec;
			for (size_t i = 0; i != 10; ++i) {
				double X = StdRandom::Uniform() * 100;
				double Y = StdRandom::Uniform() * 100;
				pvec.push_back(Point2D(X,Y));
			}

			for (const auto &p : pvec) {
				std::cout << p.ToString() << std::endl;
			}

			std::cout << std::endl << "After sort:" << std::endl;

			std::sort(pvec.begin(), pvec.end(), [](const Point2D &p, const Point2D &q) {return p < q; });
			for (const auto &p : pvec) {
				std::cout << p.ToString() << std::endl;
			}
		}

	};

	bool operator<(const Point2D &, const Point2D &);
	bool operator>(const Point2D &, const Point2D &);
	bool operator==(const Point2D &, const Point2D &);
	bool operator<=(const Point2D &, const Point2D &);
	bool operator>=(const Point2D &, const Point2D &);
	int Compare(const Point2D &, const Point2D &);
}