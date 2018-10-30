#pragma once
#include<random>
#include<ctime>
#include<stdexcept>
#include<limits>
#include<cmath>
#include<vector>
#include<string>
#include<cassert>
#include<iostream>

namespace algorithmcpp {

	class StdRandom final{
	public:
		StdRandom(const StdRandom &) = delete;
		StdRandom &operator=(const StdRandom &) = delete;
		~StdRandom() = delete;

	private:
		static time_t seed_;
		static std::default_random_engine random_;
		static int upperbound_;
		static std::uniform_int_distribution<int> iu_;
		static std::uniform_real_distribution<double> du_;

		template<typename T>
		static T Minus(T l, T r) {
			if ((l < 0 && r>0 && l < std::numeric_limits<T>::min()) || (l >= 0 && r < 0 && std::numeric_limits<T>::max() + r < l)) {
				throw std::invalid_argument("Range overflow");
			}
			return l - r;
		}

		template<typename T>
		static T Plus(T l, T r) {
			if ((l > 0 && std::numeric_limits<T>::max() - l < r) || l<0 && std::numeric_limits<T>::min() - l>r) {
				throw std::invalid_argument("Range overflow");
			}
			return l + r;
		}

	public:
		static int Uniform(int n) {
			if(n<=0) throw std::invalid_argument("Parameter N must be positive");
			if (n != upperbound_)  {
				upperbound_ = n;
				iu_= std::uniform_int_distribution<int>(0,upperbound_-1);
			}		
			return iu_(random_);
		}

		static size_t Uniform(size_t n) {
			return static_cast<size_t>(Uniform(static_cast<int>(n)));
		}

		static double Uniform() {
			return du_(random_);
		}

		static int Uniform(int a, int b) {
			if(b<=a) throw std::invalid_argument("Invalid range");
			return a+Uniform(Minus(b,a));
		}

		static double Uniform(double a, double b) {
			if(b<=a) throw std::invalid_argument("Invalid range");
			return a + Uniform()*(b - a);
		}

		static bool Bernoulli(double p) {
			if (!(p >= 0.0 && p <= 1.0)) {
				throw std::invalid_argument("Probability must be between 0.0 and 1.0");
			}
			return Uniform() < p;
		}

		static bool Bernoulli() {
			return Bernoulli(0.5);
		}

		static double Gaussian() {
			double r, x, y;
			do {
				x = Uniform(-1.0, 1.0);
				y = Uniform(-1.0, 1.0);
			} while (r >= 1 || r == 0);
			return x*std::sqrt(-2 * std::log(r));
		}

		static double Gaussian(double mu, double sigma) {
			return mu + sigma*Gaussian();
		}

		static int Geometric(double p) {
			if (!(p >= 0.0 && p <= 1.0)) {
				throw std::invalid_argument("Probability must be between 0.0 and 1.0");
			}
			return static_cast<int>(std::ceil(std::log(Uniform()) / std::log(1.0 - p)));
		}

		static int Poisson(double lambda) {
			if (!(lambda > 0.0)) {
				throw std::invalid_argument("Parameter lambda must be positive");
			}
			if (std::isinf(lambda)) {
				throw std::invalid_argument("Parameter lambda must not be infinite");
			}
			int k = 0;
			double p = 1.0;
			double L = std::exp(-lambda);
			do {
				++k;
				p *= Uniform();
			} while (p >= L);
			return k - 1;
		}

		static double Pareto() {
			return Pareto(1.0);
		}

		static double Pareto(double alpha) {
			if(!(alpha>0.0)) throw std::invalid_argument("Shape parameter alpha must be positive");
			return std::pow(1 - Uniform(),- 1.0 / alpha) - 1.0;
		}

		static double Cauchy() {
			return std::tan(std::_Pi*(Uniform() - 0.5));
		}

		static int Discrete(const std::vector<double> &probabilities) {
			double EPSILON = 1E-14;
			double sum = 0.0;
			for (std::vector<double>::size_type i = 0; i < probabilities.size(); ++i) {
				if(!(probabilities[i]>=0.0))
					throw std::invalid_argument("array entry"+std::to_string(i)+"must be nonnegative: "+std::to_string(probabilities[i]));
				sum += probabilities[i];
			}
			if(sum>1.0+EPSILON || sum<1.0-EPSILON)
				throw std::invalid_argument("sum of array entries does not approximately equal 1.0: " + std::to_string(sum));

			while (true) {
				double r = Uniform();
				sum = 0.0;
				for (std::vector<double>::size_type i = 0; i < probabilities.size(); ++i) {
					sum += probabilities[i];
					if (sum > r) return static_cast<int>(i);
				}
			}
		}

		static int Discrete(const std::vector<int> &frequencies) {
			int sum = 0;
			for (std::vector<int>::size_type i = 0; i < frequencies.size(); ++i) {
				if(frequencies[i]<0)
					throw std::invalid_argument("array entry" + std::to_string(i) + "must be nonnegative: " + std::to_string(frequencies[i]));
				sum = Plus(sum, frequencies[i]);
			}
			if(sum==0)
				throw std::invalid_argument("at least one array entry must be positive");

			double r = Uniform(sum);
			sum = 0;
			for (std::vector<int>::size_type i = 0; i < frequencies.size(); ++i) {
				sum += frequencies[i];
				if (sum > r) return static_cast<int>(i);
			}

			assert(false);
			return -1;
		}

		static double Exp(double lambda) {
			if (!(lambda > 0.0))
				throw std::invalid_argument("Rate lambda must be positive");
			return -std::log(1 - Uniform()) / lambda;
		}

		template<typename Item> 
		static void Shuffle(std::vector<Item> &a) {
			typename std::vector<Item>::size_type n = a.size();
			for (size_t i = 0; i < n; ++i) {
				size_t r = i + Uniform(n - i);
				Item temp= a[i];
				a[i] = a[r];
				a[r] = temp;
			}
		}

		template<typename Item>
		static void Shuffle(std::vector<Item> &a, int lo, int hi) {
			if (lo<0 || lo>hi || hi >= a.size()) {
				throw std::invalid_argument("Illegal subarray range");
			}
			for (int i = lo; i <= hi; ++i) {
				int r = i + Uniform(hi - i + 1);
				Item temp = a[i];
				a[i] = a[r];
				a[r] = temp;
			}
		}


		static void SetSeed(time_t s) {
			seed_ = s;
			random_.seed(static_cast<unsigned>(seed_));
		}

		static time_t GetSeed() {
			return seed_;
		}

		public:

			static void MainTest(int argc = 0, char *argv[] = nullptr) {
				std::vector<double> probabilities{ 0.5,0.3,0.1,0.1 };
				std::vector<int> frequencies{ 5,3,1,1 };
				std::vector<std::string> a{ "A","B","C","D","E","F","G" };

				std::cout << "seed = " << GetSeed() << std::endl;

				for (int i = 0; i < 5; ++i) {
					std::cout << Uniform(100) << " "
						<< Uniform(10.0, 99.0) << " "
						<< Bernoulli(0.5) << " "
						<< Discrete(probabilities) << " "
						<< Discrete(frequencies) << " ";
					Shuffle(a);
					for (const auto &s : a) {
						std::cout << s;
					}
					std::cout << std::endl;
				}


			}

	};

}