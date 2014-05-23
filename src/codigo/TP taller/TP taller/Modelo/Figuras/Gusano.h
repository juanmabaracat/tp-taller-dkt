#ifndef __GUSANO_H__
#define __GUSANO_H__

#include <iostream>
#include <string>
#include <vector>
#include "Box2D/Box2D.h"
#include "../../Observador/Observable.h"
#include "../../constantes.h"
#include "../Armas/Arma.h"
#include "../Armas/Bazooka.h"
#include "Figura.h"

class Gusano: public Figura
{
private:
	int numContactos;
	bool meClick;
	vector<bool> meClickearon;
	bool congelado;
	int maximosCLientes;
	//Para probar
	bool tieneArma;
	Arma* armaSeleccionada;

public:
	Gusano();
	Gusano(float x, float y, short int rotacion, b2World* world, bool estatico, float ancho, float alto, float masa,int maximosClientes);
	~Gusano(void);
	bool meClickeo(float x,float y);
	void agregarContacto();
	void sacarContacto();
	bool puedeSaltar();
	void simularAgua(int nivelAgua);
	void reiniciar();
	bool getMeClickearon(int cliente);
	void setMeClickearon(bool d);
	void setMeClickearon(bool meClickearon, int cliente);
	bool getCongelado();
	void setCongelado(bool congelado);
	Arma* getArmaSeleccionada();
	void setArma(Arma* nuevaArma);
	bool tieneUnArma();
};

#endif