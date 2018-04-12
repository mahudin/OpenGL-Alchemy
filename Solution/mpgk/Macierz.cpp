#pragma once
#include "Macierz.h"

template<unsigned int SIZE>
Macierz<SIZE>::Macierz() {
	wspolczynniki = new GLfloat*[SIZE];
	for (int i = 0; i < SIZE; i++) {
		wspolczynniki[i] = new GLfloat[SIZE];
		for (int j = 0; j < SIZE; j++) {
			wspolczynniki[i][j] = 0;
		}
	}
};

template<unsigned int SIZE>
Macierz<SIZE>::Macierz(GLfloat x) : Macierz() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			wspolczynniki[i][j] = x;
		}
	}
};

template<unsigned int SIZE>
Macierz<SIZE>::Macierz(GLfloat** tab) : Macierz() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			wspolczynniki[i][j] = tab[i][j];
		}
	}
};

template<unsigned int SIZE>
Macierz<SIZE>::Macierz(const Macierz<SIZE>& m) : Macierz() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			wspolczynniki[i][j] = m.getAt(i, j);
		}
	}
};

template<unsigned int SIZE>
void Macierz<SIZE>::setAt(int wiersz, int kolumna, GLfloat wartosc) {
	if (wiersz < SIZE && kolumna < SIZE) {
		wspolczynniki[wiersz][kolumna] = wartosc;
	};
};

template<unsigned int SIZE>
GLfloat Macierz<SIZE>::getAt(int wiersz, int kolumna) const {
	if (wiersz < SIZE && kolumna < SIZE) {
		return wspolczynniki[wiersz][kolumna];
	}
	else {
		return NULL;
	}
};

template<unsigned int SIZE>
GLfloat** Macierz<SIZE>::getTab() const {
	return wspolczynniki;
};

template<unsigned int SIZE>
Macierz<SIZE>* Macierz<SIZE>::getMacierzJednostokowa() {
	Macierz<SIZE>* m = new Macierz<SIZE>();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (i == j) {
				m->setAt(i, j, 1);
			}
			else {
				m->setAt(i, j, 0);
			}
		}
	}
	return m;
};

template<unsigned int SIZE>
Macierz<SIZE>* Macierz<SIZE>::getMacierzTransponowana() {
	Macierz<SIZE>* m = new Macierz<SIZE>();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			m->setAt(i, j, wspolczynniki[j][i]);
		}
	}
	return m;
};

template<unsigned SIZE>
Macierz<SIZE> Macierz<SIZE>::operator + (const Macierz<SIZE>& m) {
	Macierz<SIZE> n = Macierz<SIZE>();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			n.setAt(i, j, wspolczynniki[i][j] + m.getAt(i, j));
		}
	}
	return n;
};

template<unsigned int SIZE>
Macierz<SIZE> Macierz<SIZE>::operator - (const Macierz<SIZE>& m) {
	Macierz<SIZE> n = Macierz<SIZE>();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			n.setAt(i, j, wspolczynniki[i][j] - m.getAt(i, j));
		}
	}
	return n;
};

template<unsigned int SIZE>
Macierz<SIZE> Macierz<SIZE>::operator = (const Macierz<SIZE>& m) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			wspolczynniki[i][j] = m.getAt(i, j);
		}
	}
	return *this;
};

template<unsigned int SIZE>
Macierz<SIZE> Macierz<SIZE>::operator * (int mnoznik) {
	Macierz<SIZE> n = Macierz<SIZE>();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			n.setAt(i, j, wspolczynniki[i][j] * mnoznik);
		}
	}
	return n;
};

template<unsigned int SIZE>
Macierz<SIZE> Macierz<SIZE>::operator * (const Macierz<SIZE>& m) {
	Macierz<SIZE> n = Macierz<SIZE>();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			GLfloat s = 0;
			for (int k = 0; k < SIZE; k++) {
				s += (wspolczynniki[i][k] * m.getAt(k, j));
			}
			n.setAt(i, j, s);
		}
	}
	return n;
}

template<unsigned int SIZE>
Macierz<SIZE>& Macierz<SIZE>::operator *= (const Macierz<SIZE>& m) {
	Macierz<SIZE> n = Macierz<SIZE>();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			GLfloat s = 0;
			for (int k = 0; k < SIZE; k++) {
				s += (wspolczynniki[i][k] * m.getAt(k, j));
			}
			n.setAt(i, j, s);
		}
	}
	*this = n;
	return *this;
};


template<unsigned int SIZE>
Macierz<SIZE>& Macierz<SIZE>::operator += (const Macierz<SIZE>& m) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			wspolczynniki[i][j] = wspolczynniki[i][j] + m.getAt(i, j);
		}
	}
	return *this;
};

template<unsigned int SIZE>
Macierz<SIZE>& Macierz<SIZE>::operator -= (const Macierz<SIZE>& m) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			wspolczynniki[i][j] = wspolczynniki[i][j] - m.getAt(i, j);
		}
	}
	return *this;
};

template<unsigned int SIZE>
Macierz<SIZE>& Macierz<SIZE>::operator *= (int mnoznik) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			wspolczynniki[i][j] = wspolczynniki[i][j] * mnoznik;
		}
	}
	return *this;
};

/*template<unsigned int SIZE>
Wektor<SIZE> Macierz<SIZE>::operator * (const Wektor<SIZE>& w) {

	Wektor<SIZE> n = Wektor<SIZE>();

	for (int i = 0; i < SIZE; i++) {
		GLfloat s = 0;
		for (int j = 0; j < SIZE; j++) {
			s += (wspolczynniki[i][j] * w.getAt(j));
		}
		n.setAt(i, s);
	}
	return n;
};*/

template<unsigned int SIZE>
Macierz<SIZE>::~Macierz() {
	for (int i = 0; i < SIZE; i++) {
		delete[] wspolczynniki[i];
	}
	delete[] wspolczynniki;
}