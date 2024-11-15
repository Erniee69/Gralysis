#pragma once
#include <cmath>

namespace ac {

	int min(int p1, int p2);
	float min(float p1, float p2);
	double min(double p1, double p2);

	int max(int p1, int p2);
	float max(float p1, float p2);
	double max(double p1, double p2);

	float trunc(float p1);
	double trunc(double p1);

	float frac(float p1);
	double frac(double p1);

	int abs(int p1);
	float abs(float p1);
	double abs(double p1);

	float floor(float p1);
	double floor(double p1);

	float ceil(float p1);
	double ceil(double p1);

	float round(float p1);
	double round(double p1);

	int mod(int p1, int p2);
	float mod(float p1, float p2);
	double mod(double p1, double p2);

	float sqrt(float p1);
	double sqrt(double p1);

	float root(float p1, float p2);
	double root(double p1, double p2);

	int pow(int p1, int p2);
	float pow(float p1, float p2);
	double pow(double p1, double p2);

	float exp(float p1);
	double exp(double p1);

	float ln(float p1);
	double ln(double p1);

	float log2(float p1);
	double log2(double p1);

	float log(float p1, float p2);
	double log(double p1, double p2);
}