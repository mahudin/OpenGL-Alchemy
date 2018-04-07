#pragma once
#include<GL\glew.h>
#include<GL\freeglut.h>
#include<iostream>
#include<math.h>

class Wektor {

	GLfloat* wspolrzedne;

public:
	Wektor();
	Wektor(GLfloat x);
	Wektor(GLfloat x, GLfloat y, GLfloat z);
	Wektor(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	Wektor(GLfloat* tab);

	Wektor normalizuj();
	GLfloat obliczSkalarny(const Wektor& w);
	Wektor obliczWektorowy(const Wektor& w);

	Wektor operator = (const Wektor& w);
	Wektor operator + (const Wektor& w);
	Wektor operator += (const Wektor& w);
	Wektor operator - (const Wektor& w);
	Wektor operator -= (const Wektor& w);
	Wektor operator * (int l);
	Wektor operator *= (int l);

	friend std::ostream& operator << (std::ostream& out, const Wektor& w);

	void setX(GLfloat x);
	void setY(GLfloat y);
	void setZ(GLfloat z);
	void setW(GLfloat w);

	GLfloat getX() const;
	GLfloat getY() const;
	GLfloat getZ() const;
	GLfloat getW() const;

};