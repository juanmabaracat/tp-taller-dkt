#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "DataRed.h"

class Servicio{

public:

static int enviarMensaje(SOCKET curSocket, char * mensaje, int mensajeTamano);
static int recibirMensaje(SOCKET curSocket, char * buffer, int bufferTamano);

};