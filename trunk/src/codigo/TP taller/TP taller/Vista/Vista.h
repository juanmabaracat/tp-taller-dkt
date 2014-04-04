#ifndef __VISTA_H__
#define __VISTA_H__

#include "Dibujables/DibujableTextura.h"
#include "Dibujables/CirculoDibujable.h"
#include "Dibujables/PoligonoDibujable.h"
#include "Dibujables\RectanguloDibujable.h"
#include "../Parser/yaml/ParserYaml.h"
#include <list>

using namespace std;

class Vista
{

private:

	SDL_Window* window;
	SDL_Renderer* renderer;
	list<Dibujable*>* listaDibujables;
	int anchoPx;
	int altoPx;

public:

	Vista(EscenarioParseado* e);
	~Vista();
	SDL_Renderer* getRenderer();
	DibujableTextura* crearDibujableTextura(int x , int y ,int ancho,int alto, string pathImagen, string imagenDEF);
	void crearSprite(int x, int y, int anchoFrame, int altoFrame, string path, int col, int fil, int anchoTex, int altoTex);
	void crearScrollingSprite(int x, int y, int ancho, int alto, string path);
	CirculoDibujable* crearCirculoDibujable(int x , int y ,int radioHorizontal,int radioVertical);
	PoligonoDibujable* crearPoligonoDibujable(short int n, float escalaAncho, float escalaAlto);
	RectanguloDibujable* crearRectanguloDibujable(float ancho, float alto);
	void agregarDibujable(Dibujable* dibujable);
	list<Dibujable*>* getListaDibujables();
	void Dibujar();
	int getAnchoPx();
	int getAltoPx();
	
};

#endif