#pragma once
#include "Przekszta³cenie.h"

template<unsigned int S>
Macierz<S>* Przeksztalcenia<S>::generujMacierzSkalowania(GLfloat val) {
	Macierz<S>* skal = new Macierz<S>();
	for (int i = 0; i < S; i++) {
		skal->setAt(i, i, val);
	}
	skal->setAt(S, S, 1);

	return skal;
}

template<unsigned int S>
Macierz<S>* Przeksztalcenia<S>::generujMacierzSkalowania(GLfloat valX, GLfloat valY) {
	if (S > 2) {
		Macierz<S>* skal = new Macierz<S>();
		for (int i = 0; i < S; i++) {
			skal->setAt(i, i, 1);
		}
		skal->setAt(0, 0, valX);
		skal->setAt(1, 1, valY);
		skal->setAt(S, S, 1);

		return skal;
	}
	return nullptr;
}

template<unsigned int S>
Macierz<S>* Przeksztalcenia<S>::generujMacierzSkalowania(GLfloat valX, GLfloat valY, GLfloat valZ) {
	if (S > 3) {
		Macierz<S>* skal = new Macierz<S>();

		for (int i = 0; i < S; i++) {
			skal->setAt(i, i, 1);
		}
		skal->setAt(0, 0, valX);
		skal->setAt(1, 1, valY);
		skal->setAt(2, 2, valZ);
		skal->setAt(S, S, 1);
		return skal;
	}
	return nullptr;
}

template<unsigned int S>
Macierz<S>* Przeksztalcenia<S>::generujMacierzSkalowania(GLfloat* tab) {
	Macierz<S>* skal = new Macierz<S>();
	for (int i = 0; i < S - 1; i++) {
		skal->setAt(i, i, tab[i]);
	}
	skal->setAt(S, S, 1);
	return skal;
}

template<unsigned int S>
Macierz<S>* Przeksztalcenia<S>::generujMacierzObrotu(GLfloat kat, OS os) {
	if (S == 3 || S == 4) {

		GLfloat radiany = naRadiany(kat);

		Macierz<S>* ob = new Macierz<S>();
		if (os == OS::X) {

			ob->setAt(0, 0, 1);
			ob->setAt(1, 1, cos(radiany));
			ob->setAt(1, 2, -sin(radiany));
			ob->setAt(2, 1, sin(radiany));
			ob->setAt(2, 2, cos(radiany));
			if (S == 4) {
				ob->setAt(3, 3, 1);
			}
		}
		else if (os == OS::Y) {
			ob->setAt(0, 0, cos(radiany));
			ob->setAt(0, 2, sin(radiany));
			ob->setAt(1, 1, 1);
			ob->setAt(2, 0, -sin(radiany));
			ob->setAt(2, 2, cos(radiany));
			if (S == 4) {
				ob->setAt(3, 3, 1);
			}
		}
		else if (os == OS::Z) {
			ob->setAt(0, 0, cos(radiany));
			ob->setAt(0, 1, -sin(radiany));
			ob->setAt(1, 0, sin(radiany));
			ob->setAt(1, 1, cos(radiany));
			ob->setAt(2, 2, 1);
			if (S == 4) {
				ob->setAt(3, 3, 1);
			}
		}
		return ob;
	}
	return nullptr;
}

template<unsigned int S>
Macierz<S>* Przeksztalcenia<S>::getMacierz() const {
	Macierz<S>* mac = new Macierz<S>(*m);
	return mac;
}

template<unsigned int S>
Macierz<S>* Przeksztalcenia<S>::generujMacierzPrzesuniecia(GLfloat val) {
	Macierz<S>* tran = new Macierz<S>();
	for (int i = 0; i < S; i++) {
		tran->setAt(i, i, 1);
	}
	for (int i = 0; i < S - 1; i++) {
		tran->setAt(i, S - 1, val);
	}
	return tran;
}

template<unsigned int S>
Macierz<S>* Przeksztalcenia<S>::generujMacierzPrzesuniecia(GLfloat valX, GLfloat valY) {
	if (S == 4) {
		Macierz<S>* tran = new Macierz<S>();
		for (int i = 0; i < S; i++) {
			tran->setAt(i, i, 1);
		}
		tran->setAt(0, S - 1, valX);
		tran->setAt(1, S - 1, valY);
		return tran;
	}
	return nullptr;
}

template<unsigned int S>
Macierz<S>* Przeksztalcenia<S>::generujMacierzPrzesuniecia(GLfloat valX, GLfloat valY, GLfloat valZ) {
	if (S == 4) {
		Macierz<S>* tran = new Macierz<S>();
		for (int i = 0; i < S; i++) {
			tran->setAt(i, i, 1);
		}
		tran->setAt(0, S - 1, valX);
		tran->setAt(1, S - 1, valY);
		tran->setAt(2, S - 1, valZ);
		return tran;
	}
	return nullptr;
}

template<unsigned int S>
Macierz<S>* Przeksztalcenia<S>::generujMacierzPrzesuniecia(GLfloat* tab) {
	Macierz<S>* tran = new Macierz<S>();
	for (int i = 0; i < S; i++) {
		tran->setAt(i, i, 1);
	}
	for (int i = 0; i < S - 1; i++) {
		tran->setAt(i, S - 1, tab[i]);
	}
	return tran;
}

template<unsigned int S>
GLdouble Przeksztalcenia<S>::naStopnie(GLdouble radiany) {
	return radiany * 180 / M_PI;
}

template<unsigned int S>
GLdouble Przeksztalcenia<S>::naRadiany(GLint stopnie) {
	return stopnie * M_PI / 180;
}

template<unsigned int S>
Macierz<S>* Przeksztalcenia<S>::polaczTransformacje(Macierz<S>* tab, int size) {

	if (size > 0) {
		Macierz<S>* result = new Macierz<S>;
		*result = tab[size - 1];

		for (int i = size - 2; i >= 0; i--) {
			*result = *result * tab[i];
		}
		return result;
	}
	else {
		return nullptr;
	}
}

/*template<unsigned int S>
Macierz<S>* Przeksztalcenia<S>::generujMacierzPerspektywy(GLfloat kat, GLfloat wys, GLfloat szer, GLfloat blZ, GLfloat dlZ) {

GLfloat rad = naRadiany(kat);
GLfloat ar = szer / wys;
Macierz<S>* persp = new Macierz<S>;

persp->setAt(0, 0, 1 / (ar * tan(rad / 2)));
persp->setAt(1, 1, 1 / tan(rad / 2));
persp->setAt(2, 2, (-blZ - dlZ) / (blZ - dlZ));
persp->setAt(2, 3, (2 * dlZ*blZ) / (blZ - dlZ));
persp->setAt(3, 2, 1);
if (S > 3) {
persp->setAt(3, 3, 1);
}

return persp;
}*/