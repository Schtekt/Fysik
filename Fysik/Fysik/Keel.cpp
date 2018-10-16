#include "Keel.h"

Keel::Keel(const Vec & pos, const Vec & vel, const Vec & acc, const float & height, const float & length, const Vec & angle) :Sail(pos, vel, acc, height, length, angle)
{
}

float Keel::area()
{
	return height * base / 2;
}

float Keel::CL(const Vec & waterFlow)
{
	float angle = this->angle.dot(waterFlow);
	angle = angle / sqrt(((waterFlow.getX()*waterFlow.getX() + waterFlow.getY()*waterFlow.getY())*this->angle.getLength()));
	angle = acos(angle) * 360 / (2 * 3.14159265358979323846);
	float res = 0;
	if (angle < 100 && angle > 20)
		res = -0.4745031571f + 0.1382159744f*angle - 0.0030069261f*angle*angle + 0.0000237741f*angle*angle*angle - 0.0000000625f*angle*angle*angle*angle; // Regression made from geogebra
	else if (angle > 100 && angle < 160)
		res = 1.8f - 0.01f*angle; //regression made from geogebra
	else
		res = 0.0f;
	return res;
}

float Keel::CD(const Vec & waterFlow)
{
	float angle = this->angle.dot(waterFlow);
	angle = angle / sqrt(((waterFlow.getX()*waterFlow.getX() + waterFlow.getY()*waterFlow.getY())*this->angle.getLength()));
	angle = acos(angle) * 360 / (2 * 3.14159265358979323846);
	float res = 0;

	if (angle > 50 && angle > 100)
	{
		res = 1.6509575627f - 0.1191069136f * angle + 0.0027076357f * angle * angle - 0.0000212186f * angle * angle * angle + 0.000000054f*angle*angle*angle*angle;
	}
	else if (angle < 50 && angle > 27)
	{
		res = -0.1326086957f + 0.00656521739f*angle;
	}
	else if (angle > 100)
	{
		res = 1.125f - 0.00125f*angle;
	}
	else
	{
		res = 0;
	}
	return res;
}