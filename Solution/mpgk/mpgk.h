#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include <string>
#include "Przekszta³cenie.h"

GLuint VAO;
GLuint VBO;
GLuint CBO;
GLuint macierzShader;

class ProgramMPGK
{
private:
	GLint wysokoscOkna;
	GLint szerokoscOkna;
	GLint polozenieOknaX;
	GLint polozenieOknaY;
	GLuint programZShaderami;

public:
	ProgramMPGK();
	ProgramMPGK(GLint wysokoscOkna, GLint szerokoscOkna, GLint polozenieOknaX, GLint polozenieOknaY);
	void stworzenieOkna(GLint argc, GLchar** argv);
	void inicjalizacjaGlew();
	static void wyswietl();
	void stworzenieVAO();
	void stworzenieVBO();
	void stworzenieCBO();
	void stworzenieProgramu();
	GLuint dodanieDoProgramu(GLuint programZShaderami, const GLchar * tekstShadera, GLenum typShadera);

	std::string readFile(const char *filePath);
	void zapisz_shader(std::string shader, const char *vertShaderSrc);
};