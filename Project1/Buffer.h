#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Buffer
{
public:
	~Buffer() = default;

	virtual void create() = 0;
	virtual void destroy() = 0;

	virtual void bind() = 0;

	virtual void allocate(void *data, unsigned int size) = 0;
};


