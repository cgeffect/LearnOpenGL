#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

typedef unsigned int	uint;
typedef unsigned char	byte;

struct ffRGBA
{
	byte m_r;
	byte m_g;
	byte m_b;
	byte m_a;

	ffRGBA(byte _r = 255,
		byte _g = 255,
		byte _b = 255,
		byte _a = 255)
	{
		m_r = _r;
		m_g = _g;
		m_b = _b;
		m_a = _a;
	}
};

template<typename T>
struct tVec3
{
	T	m_x;
	T	m_y;
	T	m_z;
	tVec3(T _x = 0, T _y = 0, T _z = 0)
	{
		m_x = _x;
		m_y = _y;
		m_z = _z;
	}
};
template<typename T>
struct tVec2
{
	T	m_x;
	T	m_y;

	tVec2(T _x = 0, T _y = 0)
	{
		m_x = _x;
		m_y = _y;
	}
};