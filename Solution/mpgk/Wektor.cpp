#pragma once
#include "Wektor.h"

Wektor::Wektor() {
	wspolrzedne = new GLfloat[4];

	for (int i = 0; i < 4; i++) {
		wspolrzedne[i] = NULL;
	}

}

Wektor::Wektor(GLfloat x) :Wektor() {
	wspolrzedne[0] = x;
}

Wektor::Wektor(GLfloat x, GLfloat y, GLfloat z) : Wektor() {
	wspolrzedne[0] = x;
	wspolrzedne[1] = y;
	wspolrzedne[2] = z;
}

Wektor::Wektor(GLfloat x, GLfloat y, GLfloat z, GLfloat w) : Wektor() {
	wspolrzedne[0] = x;
	wspolrzedne[1] = y;
	wspolrzedne[2] = z;
	wspolrzedne[3] = w;
}

Wektor::Wektor(GLfloat* tab) :Wektor() {
	for (int i = 0; i < 4; i++) {
		wspolrzedne[0] = tab[0];
	}
}

void Wektor::setX(GLfloat x) {
	wspolrzedne[0] = x;
}

void Wektor::setY(GLfloat y) {
	wspolrzedne[1] = y;
}

void Wektor::setZ(GLfloat z) {
	wspolrzedne[2] = z;
}

void Wektor::setW(GLfloat w) {
	wspolrzedne[3] = w;
}

GLfloat Wektor::getX() const {
	return wspolrzedne[0];
}

GLfloat Wektor::getY() const {
	return wspolrzedne[1];
}

GLfloat Wektor::getZ() const {
	return wspolrzedne[2];
}

GLfloat Wektor::getW() const {
	return wspolrzedne[3];
}

Wektor Wektor::operator = (const Wektor& w) {
	wspolrzedne[0] = w.getX();
	wspolrzedne[1] = w.getY();
	wspolrzedne[2] = w.getZ();
	wspolrzedne[3] = w.getW();
	return *this;
}

Wektor Wektor::operator + (const Wektor& w) {
	Wektor n = Wektor();
	n.setX(wspolrzedne[0] + w.getX());
	n.setY(wspolrzedne[1] + w.getY());
	n.setZ(wspolrzedne[2] + w.getZ());
	n.setW(wspolrzedne[3] + w.getW());
	return n;
}

Wektor Wektor::operator += (const Wektor& w) {
	wspolrzedne[0] = wspolrzedne[0] + w.getX();
	wspolrzedne[1] = wspolrzedne[1] + w.getY();
	wspolrzedne[2] = wspolrzedne[2] + w.getZ();
	wspolrzedne[3] = wspolrzedne[3] + w.getW();
	return *this;
}

Wektor Wektor::operator - (const Wektor& w) {
	Wektor n = Wektor();
	n.setX(wspolrzedne[0] - w.getX());
	n.setY(wspolrzedne[1] - w.getY());
	n.setZ(wspolrzedne[2] - w.getZ());
	n.setW(wspolrzedne[3] - w.getW());
	return n;
}

Wektor Wektor::operator -= (const Wektor& w) {
	wspolrzedne[0] = wspolrzedne[0] - w.getX();
	wspolrzedne[1] = wspolrzedne[1] - w.getY();
	wspolrzedne[2] = wspolrzedne[2] - w.getZ();
	wspolrzedne[3] = wspolrzedne[3] - w.getW();
	return *this;
}

Wektor Wektor::operator * (int l) {
	Wektor n = Wektor();
	n.setX(wspolrzedne[0] * l);
	n.setY(wspolrzedne[1] * l);
	n.setZ(wspolrzedne[2] * l);
	n.setW(wspolrzedne[3] * l);
	//std::cout << n << std::endl;
	return n;
}

Wektor Wektor::operator *= (int l) {
	wspolrzedne[0] = wspolrzedne[0] * l;
	wspolrzedne[1] = wspolrzedne[1] * l;
	wspolrzedne[2] = wspolrzedne[2] * l;
	wspolrzedne[3] = wspolrzedne[3] * l;
	return *this;
}

std::ostream& operator << (std::ostream& out, const Wektor& w) {
	if (w.wspolrzedne[0]) {
		out << "(" << w.wspolrzedne[0];
	}

	if (w.wspolrzedne[1]) {
		out << ", " << w.wspolrzedne[1];
	}

	if (w.wspolrzedne[2] && w.wspolrzedne[3] == NULL) {
		out << ", " << w.wspolrzedne[2] << ")";
	}
	else {
		out << ", " << w.wspolrzedne[2] << ", " << w.wspolrzedne[3] << ")";
	}

	return out;
}

Wektor Wektor::normalizuj() {

	GLfloat dlugosc = std::sqrt(std::pow(wspolrzedne[0], 2) + std::pow(wspolrzedne[1], 2) + std::pow(wspolrzedne[2], 2));

	Wektor w;
	w.setX(wspolrzedne[0] / dlugosc);
	w.setY(wspolrzedne[1] / dlugosc);
	w.setZ(wspolrzedne[2] / dlugosc);

	return w;
}

GLfloat Wektor::obliczSkalarny(const Wektor& w) {
	return (this->wspolrzedne[0] * w.getX()) + (this->wspolrzedne[1] * w.getY()) + (this->wspolrzedne[2] * w.getZ()) + (this->wspolrzedne[3] * w.getW());
}

Wektor Wektor::obliczWektorowy(const Wektor& w) {

	Wektor n;
	n.setX(this->wspolrzedne[1] * w.getZ() - wspolrzedne[2] * w.getY());
	n.setY(this->wspolrzedne[2] * w.getX() - wspolrzedne[0] * w.getZ());
	n.setZ(this->wspolrzedne[0] * w.getY() - wspolrzedne[1] * w.getX());

	return n;
}
