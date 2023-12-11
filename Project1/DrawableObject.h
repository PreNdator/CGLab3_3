#pragma once
class DrawableObject
{
public:
	virtual void bind() = 0;
	virtual void release() = 0;
	virtual int nVertices() = 0;
};