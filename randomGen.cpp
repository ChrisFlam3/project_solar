#pragma once
#include "randomGen.h"
long double randomGen(long double min, long double max) {
	std::random_device rd;
	std::default_random_engine e(rd());
	std::uniform_real_distribution<> d(min, max);
	long double result = d(e);
	return result;
}

long long randomGen(long long min, long long max) {
	std::random_device rd;
	std::default_random_engine e(rd());
	std::uniform_real_distribution<> d(min, max);
	long long result = d(e);
	return result;
}