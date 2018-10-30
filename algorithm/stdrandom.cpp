#include"stdrandom.h"
namespace algorithmcpp {
	time_t StdRandom::seed_ = std::time(nullptr);
	std::default_random_engine StdRandom::random_(static_cast<int>(seed_));
	int StdRandom::upperbound_ = 1;
	std::uniform_int_distribution<int> StdRandom::iu_(0, upperbound_ - 1);
	std::uniform_real_distribution<double> StdRandom::du_(0, 1);
}

