//{future header message}
#ifndef __GecoDirection3_H__
#define __GecoDirection3_H__

#include "geco-math-power.h"

struct GecoDegree;
struct GecoRadians;

/**
*	This method is used to compress an angle in the range [-pi, pi) to an int8.
*
*	@see int8ToAngle
*/
INLINE uchar AngleToInt8(float angle)
{
	return (uchar)floorf((angle * 128.f) / GECO_MATH_PI_F + 0.5f);
}
/**
*	This method is used to convert an compressed angle to an angle in the range
*	[-pi, pi).
*
*	@see angleToInt8
*/
INLINE float Int8ToAngle(uchar angle)
{
	return float(angle) * (GECO_MATH_PI_F / 128.f);
}
/**
*	This method is used to convert an angle in the range [-pi/2, pi/2) to an
*	int8.
*
*	@see int8ToHalfAngle
*/
INLINE uchar HalfAngleToInt8(float angle)
{
	return (uchar)GecoClampEx(-128.f, floorf((angle * 254.f) / GECO_MATH_PI_F + 0.5f), 127.f);
}
/**
*	This method is used to convert an compressed angle to an angle in the range
*	[-pi/2, pi/2).
*
*	@see halfAngleToInt8
*/
INLINE float Int8ToHalfAngle(uchar angle)
{
	return float(angle) * (GECO_MATH_PI_F / 254.f);
}

class GECOAPI GecoAngle
{
public:
	GecoAngle();
	GecoAngle(const GecoAngle& rAngle);
	GecoAngle(float fValueInRadians);
	GecoAngle(GecoRadians fValue);
	GecoAngle(GecoDegree fValue);
	~GecoAngle();

	const GecoAngle& operator = (GecoAngle kAngle);
	const GecoAngle& operator = (float fValueInRadians);
	const GecoAngle& operator = (GecoRadians fValue);
	const GecoAngle& operator = (GecoDegree fValue);

	const GecoAngle& operator += (GecoAngle kAngle);
	const GecoAngle& operator += (float fValueInRadians);
	const GecoAngle& operator += (GecoRadians fValue);
	const GecoAngle& operator += (GecoDegree fValue);

	const GecoAngle& operator -= (GecoAngle kAngle);
	const GecoAngle& operator -= (float fValueInRadians);
	const GecoAngle& operator -= (GecoRadians fValue);
	const GecoAngle& operator -= (GecoDegree fValue);

	//operator float& ();

	operator float() const;
	float GetAngle()const;

	static void Normalise(float& fAngle);
	static GecoAngle Decay(GecoAngle kSrc, GecoAngle kDst, float fHalfLife, float fDeltaTime);
	static float SameSignAngle(GecoAngle kAngle, GecoAngle kClosest);
	static GecoAngle TurnRange(GecoAngle kFrom, GecoAngle kTo);

	bool ClampBetween(GecoAngle kMin, GecoAngle kMax);
	bool IsBetween(GecoAngle kMin, GecoAngle kMax) const;
	void Lerp(GecoAngle a, GecoAngle b, float t);
	void Normalise();

private:
	float m_fAngle;
};

class GECOAPI GecoDirection3
{
public:
	GecoDirection3();
	GecoDirection3(const float fYaw, const float fPitch, const float fRoll);

	float Yaw()const;
	float Pitch()const;
	float Roll()const;
	void SetYaw(const float fYaw);
	void SetPitch(const float fPitch);
	void SetRoll(const float fRoll);

	bool IsEqual(const GecoDirection3& kOther)const;
	static bool IsEqual(const GecoDirection3& kOne, const GecoDirection3& kOther);

	float m_fYaw;
	float m_fPitch;
	float m_fRoll;
};

#endif /* __GecoVector2_H__ */
