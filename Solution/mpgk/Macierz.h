#pragma once
#include<GL\glew.h>
#include<GL\freeglut.h>
#include<iostream>
#include<math.h>
#include "Wektor.h"

template<unsigned int SIZE>
class Macierz {
	GLfloat** wspolczynniki;
public:
	Macierz();
	Macierz(GLfloat);
	Macierz(GLfloat**);
	Macierz(const Macierz&);
	~Macierz();
	Macierz operator + (const Macierz&);
	Macierz operator - (const Macierz&);
	Macierz operator = (const Macierz&);
	Macierz operator * (int);
	Macierz operator * (const Macierz&);
//	Wektor<SIZE> operator * (const Wektor<SIZE> &);

	Macierz& operator += (const Macierz&);
	Macierz& operator -= (const Macierz&);
	Macierz& operator *= (int);
	Macierz& operator *= (const Macierz&);

	void setAt(int, int, GLfloat);
	GLfloat getAt(int, int) const;
	GLfloat** getTab() const;

	Macierz* getMacierzJednostokowa();
	Macierz* getMacierzTransponowana();
	friend std::ostream& operator << (std::ostream& out, const Macierz<SIZE>& m) {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) out << m.wspolczynniki[i][j] << " ";
			out << std::endl;
		}
		return out;
	}
};