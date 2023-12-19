#pragma once
class DrawableObject
{
public:
	virtual void bind(Shader& shader) = 0;
	virtual void release() = 0;
	virtual int nVertices() = 0;

};