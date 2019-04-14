#include "stdafx.h"
#include "Vector4.h"

tagVector4::tagVector4(XMVECTOR vSimd)
{
	XMStoreFloat4(this, vSimd);
}

const tagVector4& tagVector4::TransformNormal(XMMATRIX mat)
{
	XMVECTOR vThis = ToSIMD();
	XMStoreFloat4(this, XMVector3TransformNormal(vThis, mat));
	return *this;
}

const tagVector4& tagVector4::TransformCoord(XMMATRIX mat)
{
	XMVECTOR vThis = ToSIMD();
	XMStoreFloat4(this, XMVector3TransformCoord(vThis, mat));
	return *this;
}

void tagVector4::Normalize(void)
{
	XMVECTOR Vector = XMLoadFloat4(this);
	Vector = XMVector4Normalize(Vector);
	XMStoreFloat4(this, Vector);
}

XMVECTOR tagVector4::ToSIMD(void)
{
	return XMLoadFloat4(this);
}

void tagVector4::LoadSIMD(XMVECTOR vSimd)
{
	XMStoreFloat4(this, vSimd);
}

tagVector4 tagVector4::operator+(const tagVector4 & AddedVec4)
{
	return tagVector4(XMLoadFloat4(this) + XMLoadFloat4(&AddedVec4));
}

tagVector4 tagVector4::operator-(const tagVector4 & AddedVec4)
{
	return tagVector4(XMLoadFloat4(this) - XMLoadFloat4(&AddedVec4));
}

//============================= Vector 4 ================================
void tagVector4::operator +=(const tagVector4& AddedVec4)
{
	XMVECTOR vecInput = XMLoadFloat4(&AddedVec4);
	this->operator +=(vecInput);
}
void tagVector4::operator -=(const tagVector4& AddedVec4)
{
	XMVECTOR vecInput = XMLoadFloat4(&AddedVec4);
	this->operator -=(vecInput);

}
void tagVector4::operator*=(const float & Float)
{
	XMVECTOR v = ToSIMD();
	this->LoadSIMD(v * Float);
}
void tagVector4::operator/=(const float & Float)
{
	XMVECTOR v = ToSIMD();
	this->LoadSIMD(v / Float);
}
void tagVector4::operator *=(const tagVector4& AddedVec4)
{
	XMVECTOR vecInput = XMLoadFloat4(&AddedVec4);
	this->operator *=(vecInput);
}
void tagVector4::operator/=(const tagVector4 & AddedVec4)
{
	XMVECTOR vecInput = XMLoadFloat4(&AddedVec4);
	this->operator /=(vecInput);
}
//=============================== Vector4 SIMD ==========================
void tagVector4::operator +=(const XMVECTOR& Vector)
{
	XMVECTOR vecThis = XMLoadFloat4(this);
	vecThis += Vector;

	XMStoreFloat4(this, vecThis);
}
void tagVector4::operator *=(const XMVECTOR& Vector)
{
	XMVECTOR vecThis = XMLoadFloat4(this);
	vecThis *= Vector;

	XMStoreFloat4(this, vecThis);
}
void tagVector4::operator/=(const XMVECTOR & Vector)
{
	XMVECTOR vecThis = XMLoadFloat4(this);
	vecThis /= Vector;

	XMStoreFloat4(this, vecThis);
}
void tagVector4::operator -=(const XMVECTOR& Vector)
{
	XMVECTOR vecThis = XMLoadFloat4(this);
	vecThis -= Vector;

	XMStoreFloat4(this, vecThis);
}

tagVector4 tagVector4::operator*(const float & fFloat)
{
	return tagVector4(XMVectorScale(XMLoadFloat4(this), fFloat));
}
