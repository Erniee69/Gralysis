#pragma once
#include <cmath>
#include <AcidLib/Math/Constants.hpp>

namespace ac {

	float sin(float p1);
	double sin(double p1);

	float cos(float p1);
	double cos(double p1);

	float tan(float p1);
	double tan(double p1);

	float cot(float p1);
	double cot(double p1);

	float sec(float p1);
	double sec(double p1);

	float csc(float p1);
	double csc(double p1);

	float arcsin(float p1);
	double arcsin(double p1);

	float arccos(float p1);
	double arccos(double p1);

	float arctan(float p1);
	double arctan(double p1);

	float arctan2(float p1, float p2);
	double arctan2(double p1, double p2);

	float arccot(float p1);
	double arccot(double p1);

	float arccot2(float p1, float p2);
	double arccot2(double p1, double p2);

	float arcsec(float p1);
	double arcsec(double p1);

	float arccsc(float p1);
	double arccsc(double p1);

	float radToDeg(float p1);
	double radToDeg(double p1);

	float degToRad(float p1);
	double degToRad(double p1);
}