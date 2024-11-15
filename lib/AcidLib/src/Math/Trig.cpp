#include <AcidLib/Math/Trig.hpp>

namespace ac {

	float sin(float p1) {

		return std::sin(p1);
	}

	double sin(double p1) {

		return std::sin(p1);
	}

	float cos(float p1) {

		return std::cos(p1);
	}

	double cos(double p1) {

		return std::cos(p1);
	}

	float tan(float p1) {

		return std::tan(p1);
	}

	double tan(double p1) {

		return std::tan(p1);
	}

	float cot(float p1) {

		return 1 / std::tan(p1);
	}

	double cot(double p1) {

		return 1 / std::tan(p1);
	}

	float sec(float p1) {

		return 1 / std::cos(p1);
	}

	double sec(double p1) {

		return 1 / std::cos(p1);
	}

	float csc(float p1) {

		return 1 / std::sin(p1);
	}

	double csc(double p1) {

		return 1 / std::sin(p1);
	}


	float arcsin(float p1) {

		return std::asin(p1);
	}

	double arcsin(double p1) {

		return std::asin(p1);
	}

	float arccos(float p1) {

		return std::acos(p1);
	}

	double arccos(double p1) {

		return std::acos(p1);
	}

	float arctan(float p1) {

		return std::atan(p1);
	}

	double arctan(double p1) {

		return std::atan(p1);
	}

	float arctan2(float p1, float p2) {

		return std::atan2(p1, p2);
	}

	double arctan2(double p1, double p2) {

		return std::atan2(p1, p2);
	}

	float arccot(float p1) {

		return std::atan(-p1) + (Constants::PI / 2);
	}

	double arccot(double p1) {

		return std::atan(-p1) + (Constants::PI / 2);
	}

	float arccot2(float p1, float p2) {

		return std::atan2(p2, p1);
	}

	double arccot2(double p1, double p2) {

		return std::atan2(p2, p1);
	}

	float arcsec(float p1) {

		return std::acos(1 / p1);
	}

	double arcsec(double p1) {

		return std::acos(1 / p1);
	}

	float arccsc(float p1) {

		return std::asin(1 / p1);
	}

	double arccsc(double p1) {

		return std::asin(1 / p1);
	}

	float radToDeg(float p1) {

		return p1 / (2 * Constants::PI) * 360;
	}

	double radToDeg(double p1) {

		return p1 / (2 * Constants::PI) * 360;
	}

	float degToRad(float p1) {

		return p1 / 360 * (2 * Constants::PI);
	}

	double degToRad(double p1) {

		return p1 / 360 * (2 * Constants::PI);
	}
}