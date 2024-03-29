#include "Turno.h"


Turno::Turno(void){
	terminado = true;
	detenido = true;
	this->tiempoPorTurno = tiempoTurno;
	this->tiempoPorDisparo = tiempoDisparo;
	this->tiempoActual = tiempoTurno;
	this->tiempoPorGolpe = tiempoGolpe;
}


Turno::~Turno(void)
{
}


void Turno::reiniciar(){
	detenido = false;
	terminado = false;
	huboDisparo = false;
	huboGolpe = false;
	tiempoInicial = time(NULL);
	tiempoActual = tiempoTurno;
}

void Turno::detener(){
	detenido = true;
}

void Turno::avanzarTiempo(){
	tiempoActual++;
}

void Turno::setJugadorActual(string jugador){
	jugadorActual = jugador;
}

string Turno::getJugadorActual(){
	return jugadorActual;
}

bool Turno::estaDetenido(){
	return detenido;
}

bool Turno::estaTerminado(){
	return terminado;
}

void Turno::terminar(){
	terminado = true;
	detener();
	
}

void Turno::actualizar(){
	if(!detenido){
		//Juego::tiempo = tiempoActual;
		int tiempo = time(NULL) - tiempoInicial - tiempoActual;

		if (tiempo != 0){
			if ( tiempoActual >= tiempoPorTurno )	terminar();
			else									tiempoActual++;
		}
	}
	else{
		if(huboDisparo){
			//espero tiempoPorDisparo:
			if( (time(NULL) - tiempoDiferido) >= tiempoPorDisparo ) {
				terminar();
				huboDisparo = false;
				tiempoDiferido = 0;
			}
		}
		if(huboGolpe && !huboDisparo){
			//espero tiempoPorGolpe:
			if( (time(NULL) - tiempoDiferidoGolpe) >= tiempoPorGolpe ) {
				terminar();
				huboGolpe = false;
				tiempoDiferidoGolpe = 0;
			}
		}
	}
}

void Turno::comenzar(){
	detenido = false;
	terminado = false;
	huboDisparo = false;
	huboGolpe = false;
	tiempoInicial = time(NULL);
	tiempoActual = 0;
	tiempoDiferido = 0;
	tiempoDiferidoGolpe = 0;
}

int Turno::getTiempoActual(){
	return (tiempoPorTurno - tiempoActual);
}

void Turno::esperarDisparo(){
	detener();
	huboDisparo=true;
	tiempoDiferido = time(NULL);
}

void Turno::esperarGolpe(){
	detener();
	huboGolpe=true;
	tiempoDiferidoGolpe = time(NULL);
}
