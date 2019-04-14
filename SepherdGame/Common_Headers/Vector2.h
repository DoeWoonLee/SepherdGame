#ifndef Vector2_h__
#define Vector2_h__

#pragma  warning (disable : 4275)

#include "Engine_Macro.h"
#include <DirectXMath.h>
using namespace DirectX;


typedef  struct tagVector2 : public XMFLOAT2
{
	tagVector2(float fX = 0.f, float fY = 0.f)
		: XMFLOAT2(fX, fY) {};
	explicit tagVector2(XMVECTOR vSimd);
	explicit tagVector2(_In_reads_(2) const float *pArray) : XMFLOAT2(pArray){}
	const tagVector2& TransformNormal(XMMATRIX mat);
	const tagVector2& TransformCoord(XMMATRIX mat);
	XMVECTOR ToSIMD(void);
	void LoadSIMD(XMVECTOR vSimd);
	void Normalize(void);
	float Length(tagVector2& vVector);
	float Magnitude(void);

	float Dot(tagVector2& vVector);

	tagVector2& operator= (const tagVector2& Float2) { x = Float2.x; y = Float2.y; return *this; }

	tagVector2 operator+(const tagVector2& AddedVec2);
	tagVector2 operator-(const tagVector2& AddedVec2);

	void operator+=(const tagVector2& AddedVec2);
	void operator-=(const tagVector2& AddedVec2);
	void operator*=(const tagVector2& AddedVec2);
	void operator/=(const tagVector2& AddedVec2);

	void operator*=(const float& Float);
	void operator/=(const float& Float);

	void operator+=(const XMVECTOR& Vector);
	void operator*=(const XMVECTOR& Vector);
	void operator/=(const XMVECTOR& Vector);
	void operator-=(const XMVECTOR& Vector);

	tagVector2 operator*(const float& fFloat);
	friend tagVector2 operator*( const tagVector2& rln, const float& fFloat);
	friend tagVector2 operator/( const tagVector2& Vector, const float& fFloat);
}_vec2;

inline tagVector2 operator*( const tagVector2& rln, const float& fFloat)
{
	XMVECTOR Vector = XMLoadFloat2(&rln);
	Vector = XMVectorScale(Vector, fFloat);

	return tagVector2(Vector);
}
inline tagVector2 operator/(const tagVector2& Vector, const float& fFloat)
{
	//XMVECTOR FVector = XMVectorSet(fFloat, fFloat, fFloat, 0.f) / XMLoadFloat2(&Vector);
	XMVECTOR FVector = XMLoadFloat2(&Vector) / XMVectorSet(fFloat, fFloat, fFloat, 0.f);

	return tagVector2(FVector);
}
#endif // !Vector2_h__
