#ifndef __ARMA_H__
#define __ARMA_H__

#include <iostream>
#include <string>
#include "Box2D/Box2D.h"
#include "../../Observador/Observable.h"
#include "../../constantes.h"
#include "../../constantesFisicas.h"
#include "../../constantesArmas.h"

class Arma: public Observable
{
protected:
	b2Body* body;
	b2Vec2 posicionInicial;
public:
	tipoArma armaTipo;
	Arma(void);
	Arma(float x, float y, short int rotacion, b2World* world, bool estatico, bool rotacionFija);
	void setPosicion(float x, float y, float angulo);
	b2Body* getBody();
	b2Vec2 getPosicion();
	virtual void disparar(bool sentido, int potencia, float angulo);
	virtual void explotar();

	~Arma(void);
};

#endif
