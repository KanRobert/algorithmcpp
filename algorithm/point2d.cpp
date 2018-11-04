#include"point2d.h"

namespace algorithmcpp {

	const std::function<int(Point2D, Point2D)> Point2D::x_order_(Point2D::XOrder);
	const std::function<int(Point2D, Point2D)> Point2D::y_order_(Point2D::YOrder);
	const std::function<int(Point2D, Point2D)> Point2D::r_order_(Point2D::ROrder);

	int Compare(const Point2D &lhs, const Point2D &rhs) {
		if (lhs.ycoordinate_ < rhs.ycoordinate_) return -1;
		if (lhs.ycoordinate_ > rhs.ycoordinate_) return +1;
		if (lhs.xcoordinate_ < rhs.xcoordinate_) return -1;
		if (lhs.xcoordinate_ > rhs.xcoordinate_) return +1;
		return 0;
	}

	bool operator<(const Point2D &lhs, const Point2D &rhs) {
		return Compare(lhs, rhs) < 0;
	}

	bool operator>(const Point2D &lhs, const Point2D &rhs) {
		return Compare(lhs, rhs) > 0;
	}

	bool operator==(const Point2D &lhs, const Point2D &rhs) {
		if (lhs.ycoordinate_ != rhs.ycoordinate_) return false;
		if (lhs.xcoordinate_ != rhs.xcoordinate_) return false;
		return true;
	}

	bool operator!=(const Point2D &lhs, const Point2D &rhs) {
		return !(lhs == rhs);
	}

	bool operator<=(const Point2D &lhs, const Point2D &rhs) {
		return Compare(lhs, rhs) <= 0;
	}

	bool operator>=(const Point2D &lhs, const Point2D &rhs) {
		return Compare(lhs, rhs) >= 0;
	}

}
