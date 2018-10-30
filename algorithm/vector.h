#pragma once
#include<vector>
#include<initializer_list>
#include<stdexcept>
#include<cmath>
#include<iostream>

namespace algorithmcpp {
	class Vector {
	private:
		size_t d_;
		std::vector<double> data_;

	public:
		Vector(const Vector &) = default;
		Vector &operator=(const Vector &) = default;
		Vector(Vector &&) noexcept = default;
		Vector &operator=(Vector &&) noexcept = default;
		~Vector() = default;

		Vector(size_t D):d_(D),data_(std::vector<double>(d_)) {

		}

		Vector(std::initializer_list<double> a):d_(a.size()) {
			data_.reserve(d_);
			for (double x : a) {
				data_.push_back(x);
			}
		}

		size_t Length() const {
			return d_;
		}

		size_t Dimension() const {
			return d_;
		}

		double Dot(const Vector &that) const {
			Check(that);
			double sum = 0.0;
			for (size_t i = 0; i != d_;++i) {
				sum += (data_[i] * that.data_[i]);
			}
			return sum;
		}

		double Magnitude() const {
			return std::sqrt(Dot(*this));
		}

		double DistanceTo(const Vector &that) const {
			return (*this-that).Magnitude();
		}

		Vector operator+(const Vector &that) const {
			Check(that);
			Vector c(d_);
			for (size_t i = 0; i != d_; ++i) {
				c.data_[i] = data_[i] + that.data_[i];
			}
			return c;
		}

		Vector operator-(const Vector &that) const {
			Check(that);
			Vector c(d_);
			for (size_t i = 0; i != d_; ++i) {
				c.data_[i] = data_[i] - that.data_[i];
			}
			return c;
		}

		bool operator==(const Vector &that) const {
			if (Dimension() != that.Dimension()) return false;
			for (size_t i = 0; i != d_; ++i) {
				if (data_[i] != that.data_[i]) return false;
			}
			return true;
		}

		bool operator!=(const Vector &that) const {
			return !(*this == that);
		}

		double Cartesian(size_t i) const {
			return data_[i];
		}

		Vector Times(double alpha) {
			return Scale(alpha);
		}

		Vector Scale(double alpha) const {
			Vector c(d_);
			for (size_t i = 0; i != d_; ++i) {
				c.data_[i] = alpha*data_[i];
			}
			return c;
		}

		Vector Direction() const {
			if (Magnitude() == 0.0) throw std::overflow_error("Zero-vector has no Direction");
			return Scale(1.0 / Magnitude());
		}

	private:
		void Check(const Vector &that) const {
			if (d_ != that.d_) throw std::invalid_argument("Dimensions don't agree");
		}

	public:
		static void MainTest(int argc = 0, char *argv[] = nullptr) {
			Vector vec(10);
			Vector vec2({ 1,2,3,4,5 });
			vec2 = vec2.Scale(static_cast<double>(vec.Dimension()));
		}

	};
}