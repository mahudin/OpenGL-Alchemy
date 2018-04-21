#pragma once

#include "Wektor.h"
#include "Macierz.h"
#include <math.h>

//przy ka¿dym skalowaniu: utworzenie macierzy S+1 z wewnêtrznej macierzy S, przemno¿enie przez macierz skalowania, konwersja do macierzy S+1 do S, zwrócenie.
//przy ka¿dym przesuniêciu: utworzenie macierzy S+1 z wewnêtrznej macierzy S, przemno¿enie przez macierz przesuniêcia, konwersja do macierzy S+1 do S, zwrócenie.
//przy obracaniu: utworzenie macierzy S+1 z wewnêtrznej macierzy S, przemno¿enie przez macierze obrotu wed³ug ka¿dej osi, konwersja do macierzy S+1 do S, zwrócenie.

enum class OS {
	X, Y, Z
};

template<unsigned int S>
class Przeksztalcenia {

private:
	Macierz<S>* m;

	GLdouble naStopnie(GLdouble);
	GLdouble naRadiany(GLint);

public:

	Macierz<S>* getMacierz() const;

	Macierz<S>* generujMacierzSkalowania(GLfloat);
	Macierz<S>* generujMacierzSkalowania(GLfloat, GLfloat); // dla macierzy 3 x 3
	Macierz<S>* generujMacierzSkalowania(GLfloat, GLfloat, GLfloat); // dla macierzy 4 x 4
	Macierz<S>* generujMacierzSkalowania(GLfloat*);

	Macierz<S>* generujMacierzObrotu(GLfloat, OS); // dla macierzy 3 x 3

	Macierz<S>* generujMacierzPrzesuniecia(GLfloat);
	Macierz<S>* generujMacierzPrzesuniecia(GLfloat, GLfloat); // dla macierzy 3 x 3
	Macierz<S>* generujMacierzPrzesuniecia(GLfloat, GLfloat, GLfloat); // dla macierzy 4 x 4
	Macierz<S>* generujMacierzPrzesuniecia(GLfloat*);

	Macierz<S>* polaczTransformacje(Macierz<S>* tab, int size);
};