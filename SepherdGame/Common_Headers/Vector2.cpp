#include "stdafx.h"
#include "Vector2.h"

tagVector2::tagVector2(XMVECTOR vSimd)
{
	XMStoreFloat2(this, vSimd);
}

const tagVector2& tagVector2::TransformNormal(XMMATRIX mat)
{
	XMVECTOR vThis = ToSIMD();
	XMStoreFloat2(this, XMVector3TransformNormal(vThis, mat));
	return *this;
}

const tagVector2& tagVector2::TransformCoord(XMMATRIX mat)
{
	XMVECTOR vThis = ToSIMD();
	XMStoreFloat2(this, XMVector3TransformCoord(vThis, mat));
	return *this;
}

XMVECTOR tagVector2::ToSIMD(void)
{
	return XMLoadFloat2(this);
}

void tagVector2::LoadSIMD(XMVECTOR vSimd)
{
	XMStoreFloat2(this, vSimd);
}

void tagVector2::Normalize(void)
{
	XMVECTOR Vector = XMLoadFloat2(this);
	Vector = XMVector2Normalize(Vector);
	XMStoreFloat2(this, Vector);
}

float tagVector2::Length(tagVector2 & vVector)
{
	XMVECTOR vLength = XMVector2Length(ToSIMD() - vVector.ToSIMD());

	return vLength.m128_f32[0];
}

float tagVector2::Magnitude(void)
{
	
	XMVECTOR vLength = XMVector2Length(ToSIMD());

	return vLength.m128_f32[0];
}

float tagVector2::Dot(tagVector2 & vVector)
{
	return XMVector2Dot(TS(), vVector.TS()).m128_f32[0];;
}

tagVector2 tagVector2::operator+(const tagVector2 & AddedVec2)
{
	XMVECTOR VecInput = XMLoadFloat2(&AddedVec2);
	XMVECTOR VecThis = XMLoadFloat2(this);

	VecInput = VecInput + VecThis;
	return tagVector2(VecInput);
}

tagVector2 tagVector2::operator-(const tagVector2 & AddedVec2)
{
	XMVECTOR VecInput = XMLoadFloat2(&AddedVec2);
	XMVECTOR VecThis = XMLoadFloat2(this);

	VecInput = VecThis - VecInput;
	return tagVector2(VecInput);
}

// ========================== Vector 2 =================================
void tagVector2::operator +=(const tagVector2& AddedVec2)
{
	XMVECTOR vecInput = XMLoadFloat2(&AddedVec2);
	this->operator +=(vecInput);
}
void tagVector2::operator -=(const tagVector2& AddedVec2)
{
	XMVECTOR vecInput = XMLoadFloat2(&AddedVec2);
	this->operator -=(vecInput);
}
void tagVector2::operator *=(const tagVector2& AddedVec2)
{
	XMVECTOR vecInput = XMLoadFloat2(&AddedVec2);
	this->operator *=(vecInput);
}
void tagVector2::operator/=(const tagVector2 & AddedVec2)
{
	XMVECTOR vecInput = XMLoadFloat2(&AddedVec2);
	this->operator /=(vecInput);
}
void tagVector2::operator*=(const float & Float)
{
	XMVECTOR v = ToSIMD();
	this->LoadSIMD(v * Float);
}
void tagVector2::operator/=(const float & Float)
{
	XMVECTOR v = ToSIMD();
	this->LoadSIMD(v / Float);
}
//=============================== Vector2 SIMD ==========================
void tagVector2::operator +=(const XMVECTOR& Vector)
{
	XMVECTOR vecThis = XMLoadFloat2(this);
	vecThis += Vector;

	XMStoreFloat2(this, vecThis);
}
void tagVector2::operator *=(const XMVECTOR& Vector)
{
	XMVECTOR vecThis = XMLoadFloat2(this);
	vecThis *= Vector;

	XMStoreFloat2(this, vecThis);
}
void tagVector2::operator/=(const XMVECTOR & Vector)
{
	XMVECTOR vecThis = XMLoadFloat2(this);
	vecThis /= Vector;

	XMStoreFloat2(this, vecThis);
}
void tagVector2::operator -=(const XMVECTOR& Vector)
{
	XMVECTOR vecThis = XMLoadFloat2(this);
	vecThis -= Vector;

	XMStoreFloat2(this, vecThis);
}

tagVector2 tagVector2::operator*(const float & fFloat)
{
	XMVECTOR Vector = XMLoadFloat2(this);
	Vector = XMVectorScale(Vector, fFloat);

	return tagVector2(Vector);
}
