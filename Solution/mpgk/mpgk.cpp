#include "mpgk.h"
#include "Wektor.h"
#include "Macierz.cpp"

float naRadiany(int stopien) {
	return (stopien * 3.1415) / 180;
}

int naStopnie(float radiany) {
	return (radiany * 180) / 3.1415;
}

ProgramMPGK::ProgramMPGK()
{
	wysokoscOkna = 768;
	szerokoscOkna = 1024;
	polozenieOknaX = 100;
	polozenieOknaY = 100;
}

ProgramMPGK::ProgramMPGK(GLint wysokoscOkna, GLint szerokoscOkna, GLint polozenieOknaX, GLint polozenieOknaY)
{
	this->wysokoscOkna = wysokoscOkna;
	this->szerokoscOkna = szerokoscOkna;
	this->polozenieOknaX = polozenieOknaX;
	this->polozenieOknaY = polozenieOknaY;
}

void ProgramMPGK::stworzenieOkna(GLint argc, GLchar** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(szerokoscOkna, wysokoscOkna);
	glutInitWindowPosition(polozenieOknaX, polozenieOknaY);
	glutCreateWindow("Program MPGK");
}

void ProgramMPGK::inicjalizacjaGlew()
{
	GLenum wynik = glewInit();
	if (wynik != GLEW_OK)
	{
		std::cerr << "Nie udalo sie zainicjalizowac GLEW. Blad: " << glewGetErrorString(wynik) << std::endl;
		system("pause");
		exit(1);
	}
}

void  ProgramMPGK::wyswietl()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat mJ[4][4];

	mJ[0][0] = 1.0f;  mJ[0][1] = 0.0f;	mJ[0][2] = 0.0f;  mJ[0][3] = 0.0f;
	mJ[1][0] = 0.0f;  mJ[1][1] = 1.0f;	mJ[1][2] = 0.0f;  mJ[1][3] = 0.0f;
	mJ[2][0] = 0.0f;  mJ[2][1] = 0.0f;  mJ[2][2] = 1.0f;  mJ[2][3] = 0.0f;
	mJ[3][0] = 0.0f;  mJ[3][1] = 0.0f;	mJ[3][2] = 0.0f;  mJ[3][3] = 1.0f;

	glUniformMatrix4fv(macierzShader, 1, GL_TRUE, &mJ[0][0]);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, CBO);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glutSwapBuffers();
}

void ProgramMPGK::stworzenieVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void ProgramMPGK::stworzenieVBO()
{
	GLfloat wierzcholki[9] =
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(wierzcholki), wierzcholki, GL_STATIC_DRAW);
}

void ProgramMPGK::stworzenieCBO()
{
	GLfloat kolory[] =
	{
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f
	};

	glGenBuffers(1, &CBO);
	glBindBuffer(GL_ARRAY_BUFFER, CBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(kolory), kolory, GL_STATIC_DRAW);
}

void ProgramMPGK::zapisz_shader(std::string shader, const char *vertShaderSrc) {
	std::ofstream outfile;

	outfile.open(shader, std::ios_base::app);
	outfile << vertShaderSrc;
}

int ProgramMPGK::naStopnie(float radian) {
	return radian * (180.0 / 3.141592653589793238463);
}

float ProgramMPGK::naRadiany(int stopien) {
	return 3.141592653589793238463/180.0 * stopien;
}

std::string ProgramMPGK::readFile(const char *filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void ProgramMPGK::stworzenieProgramu()
{
	programZShaderami = glCreateProgram();

	if (programZShaderami == 0)
	{
		std::cerr << "Blad podczas tworzenia progrmu shaderow." << std::endl;
		system("pause");
		exit(1);
	}

	/*GLchar * vertexShader =
		"	#version 330\n																			\
			layout (location = 0) in vec3 polozenie;												\
			layout (location = 1) in vec4 kolorPrzychodzacyVS;										\
			uniform mat4 macierz;																	\
			out vec4 kolorWychodzacyVS;																\
			void main()																				\
			{																						\
				 gl_Position = macierz * vec4(polozenie, 1.0);										\
				 kolorWychodzacyVS = kolorPrzychodzacyVS;											\
			}";

	GLchar * fragmentShader =
		"	#version 330\n									\
			in vec4 kolorWychodzacyVS;						\
			out vec4 kolorWychodzacyFS;						\
			void main()										\
			{												\
				kolorWychodzacyFS = kolorWychodzacyVS;	    \
			}";*/

	std::string vertShaderStr = readFile("vertexShader");
	std::string fragShaderStr = readFile("fragmentShader");
	const char *vertShaderSrc = vertShaderStr.c_str();
	const char *fragShaderSrc = fragShaderStr.c_str();

	dodanieDoProgramu(programZShaderami, vertShaderSrc, GL_VERTEX_SHADER);
	dodanieDoProgramu(programZShaderami, fragShaderSrc, GL_FRAGMENT_SHADER);

	GLint linkowanieOK = 0;
	glLinkProgram(programZShaderami);
	glGetProgramiv(programZShaderami, GL_LINK_STATUS, &linkowanieOK);
	if (linkowanieOK == GL_FALSE)
	{
		GLint dlugoscLoga = 0;
		glGetProgramiv(programZShaderami, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector<GLchar> log(dlugoscLoga);
		glGetProgramInfoLog(programZShaderami, dlugoscLoga, NULL, &log[0]);
		std::cerr << "Blad podczas linkowania programu shaderow." << std::endl;
		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i)
			std::cerr << *i;
		std::cerr << std::endl;
		glDeleteProgram(programZShaderami);
		system("pause");
		exit(1);
	}

	GLint walidacjaOK = 0;
	glValidateProgram(programZShaderami);
	glGetProgramiv(programZShaderami, GL_VALIDATE_STATUS, &walidacjaOK);
	if (walidacjaOK == GL_FALSE)
	{
		GLint dlugoscLoga = 0;
		glGetProgramiv(programZShaderami, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector<GLchar> log(dlugoscLoga);
		glGetProgramInfoLog(programZShaderami, dlugoscLoga, NULL, &log[0]);
		std::cerr << "Blad podczas walidacji programu shaderow." << std::endl;
		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i)
			std::cerr << *i;
		std::cerr << std::endl;
		glDeleteProgram(programZShaderami);
		system("pause");
		exit(1);
	}

	glUseProgram(programZShaderami);

	macierzShader = glGetUniformLocation(programZShaderami, "macierz");
	if (macierzShader == -1)
	{
		std::cerr << "Nie znaleziono zmiennej uniform." << std::endl;
		system("pause");
		exit(1);
	}
}

GLuint ProgramMPGK::dodanieDoProgramu(GLuint programZShaderami, const GLchar * tekstShadera, GLenum typShadera)
{
	GLuint shader = glCreateShader(typShadera);

	GLchar * typShaderaTekst = typShadera == 35633 ? "vertex" : "fragment";

	if (shader == 0)
	{
		std::cerr << "Blad podczas tworzenia " << typShaderaTekst << " shadera." << std::endl;
		system("pause");
		exit(0);
	}

	const GLchar * tekstShaderaTab[1];
	tekstShaderaTab[0] = tekstShadera;
	GLint dlugoscShadera[1];
	dlugoscShadera[0] = strlen(tekstShadera);
	glShaderSource(shader, 1, tekstShaderaTab, dlugoscShadera);

	glCompileShader(shader);
	GLint kompilacjaOK = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &kompilacjaOK);
	if (kompilacjaOK == GL_FALSE)
	{
		GLint dlugoscLoga = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector<GLchar> log(dlugoscLoga);
		glGetShaderInfoLog(shader, dlugoscLoga, NULL, &log[0]);
		std::cerr << "Blad podczas kompilacji " << typShaderaTekst << " shadera." << std::endl;
		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i)
			std::cerr << *i;
		std::cerr << std::endl;
		glDeleteShader(shader);
		system("pause");
		exit(1);
	}

	glAttachShader(programZShaderami, shader);
	return shader;
}

GLint main(GLint argc, GLchar** argv)
{
	ProgramMPGK obiektMPGK(786, 1024, 100, 100);

	obiektMPGK.stworzenieOkna(argc, argv);
	obiektMPGK.inicjalizacjaGlew();
	obiektMPGK.stworzenieVAO();
	obiektMPGK.stworzenieVBO();
	obiektMPGK.stworzenieCBO();
	obiektMPGK.stworzenieProgramu();
	glutDisplayFunc(obiektMPGK.wyswietl);
	glutIdleFunc(obiektMPGK.wyswietl);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	std::cout << "Wersja GL: " << glGetString(GL_VERSION) << std::endl;

	Wektor w1 = Wektor(1.0, 2.0, 3.0);
	Wektor w2 = Wektor(0.0, 5.0, 1.0);
	Wektor w3 = w1 + w2;
	std::cout << w3;
	std::cout << std::endl;
	Wektor w4 = w1 - w2;
	std::cout << w4;
	std::cout << std::endl;
	Wektor w5 = w1 * 4;
	std::cout << w5;
	std::cout << std::endl;
	Wektor w5a = w5.normalizuj();
	std::cout << w5a;

	std::cout << std::endl << std::endl << "Macierze" << std::endl << std::endl;

	Macierz<3> mac1 = Macierz<3>();
	mac1.setAt(0, 0, 1);
	mac1.setAt(0, 1, 5);
	mac1.setAt(0, 2, 2);
	mac1.setAt(1, 2, 2);
	mac1.setAt(1, 1, 0);
	mac1.setAt(1, 3, 1);
	mac1.setAt(2, 0, 3);
	mac1.setAt(2, 1, 4);
	mac1.setAt(2, 2, 1);
	std::cout << "mac1: " << std::endl << mac1 << std::endl << std::endl;

	Macierz<3> mac2 = Macierz<3>();
	mac2.setAt(0, 0, 1);
	mac2.setAt(0, 1, 6);
	mac2.setAt(0, 2, 1);
	mac2.setAt(1, 0, 4);
	mac2.setAt(1, 1, 0);
	mac2.setAt(1, 2, 1);
	mac2.setAt(2, 0, 2);
	mac2.setAt(2, 1, 1);
	mac2.setAt(2, 2, 0);

	std::cout << "macierz 2: " << std::endl << mac2 << std::endl << std::endl;

	if (mac1.getMacierzJednostokowa() == nullptr) {
		std::cout << "Macierz jednostkowa z macierzy 1 nie istnieje" << std::endl;
	}
	else {
		std::cout << "Macierz jednostkowa z macierz 1: " << std::endl;
		std::cout << *(mac1.getMacierzJednostokowa()) << std::endl;
	}

	std::cout << "Macierz transponowana z macierz 1: " << std::endl;
	std::cout << *(mac1.getMacierzTransponowana()) << std::endl;

	std::cout << "Dodawanie (macierz 1 + macierz 2): " << std::endl << (mac1 + mac2) << std::endl;
	std::cout << "Odejmowanie (macierz 1 - macierz 2): " << std::endl << (mac1 - mac2) << std::endl;
	std::cout << "Mnozenie przez macierz (macierz 1 * macierz 2): " << std::endl << (mac1 * mac2) << std::endl;
	std::cout << "Mnozenie przez liczbe (macierz 1 * 2): " << std::endl << (mac1 * 2) << std::endl;


	std::cout << "macierz 1: " << std::endl << mac1 << std::endl << std::endl;
	std::cout << "Przypisanie (macierz 1 = macierz 2): " << std::endl << (mac1 = mac2) << std::endl;

	mac1 += mac2;
	std::cout << "Po dodaniu z przypisaniem (macierz 1 += macierz 2): " << std::endl << mac1 << std::endl;
	mac1 -= mac2;
	std::cout << "Po odejmowaniu z przypisaniem (macierz 1 -= macierz 2): " << std::endl << mac1 << std::endl;

	mac1 *= mac2;

	std::cout << "Po mnozeniu przez macierz z przypisaniem (macierz 1 *= macierz 2): " << std::endl << mac1 << std::endl;
	mac1 *= 3;
	std::cout << "Po mnozeniu przez liczbe z przypisaniem (macierz 1 * 3): " << std::endl << mac1 << std::endl;

	std::cout << std::endl;

	std::cout << "90 stopni w radianach to: " << naRadiany(90) << std::endl;
	std::cout << "a na stopnie to: " << naStopnie(1.5708) << std::endl;


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glutMainLoop();

	return 0;
}
