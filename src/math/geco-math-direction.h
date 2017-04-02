//{future header message}
#ifndef __GecoDirection3_H__
#define __GecoDirection3_H__

#include "geco-math-power.h"

struct GecoDegree
{
	GecoDegree(float fValue)
	{
		m_fDegree = fValue;
	}

	float m_fDegree;
};

struct GecoRadians
{
	GecoRadians(float fValue)
	{
		m_fRadians = fValue;
	}

	float m_fRadians;
};

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

INLINE geco_bit_stream_t & operator >> (geco_bit_stream_t& kIS, GecoDirection3& kDes)
{
	if (kIS.is_compression_mode())
	{
		kIS.read_ranged_float(kDes.m_fYaw, -GECO_MATH_PI_F, GECO_MATH_PI_F);
		kIS.read_ranged_float(kDes.m_fPitch, -GECO_MATH_PI_F, GECO_MATH_PI_F);
		kIS.read_ranged_float(kDes.m_fRoll, -GECO_MATH_PI_F, GECO_MATH_PI_F);
	}
	else
	{
		kIS.Read(kDes.m_fYaw);
		kIS.Read(kDes.m_fPitch);
		kIS.Read(kDes.m_fRoll);
	}
	return kIS;
}
INLINE geco_bit_stream_t& operator << (geco_bit_stream_t& kOS, const GecoDirection3& kDes)
{
	if (kOS.is_compression_mode())
	{
		kOS.write_ranged_float(kDes.m_fYaw, -GECO_MATH_PI_F, GECO_MATH_PI_F);
		kOS.write_ranged_float(kDes.m_fPitch, -GECO_MATH_PI_F, GECO_MATH_PI_F);
		kOS.write_ranged_float(kDes.m_fRoll, -GECO_MATH_PI_F, GECO_MATH_PI_F);
	}
	else
	{
		kOS.Write(kDes.m_fYaw);
		kOS.Write(kDes.m_fPitch);
		kOS.Write(kDes.m_fRoll);
	}
	return kOS;
}

#endif /* __GecoVector2_H__ */