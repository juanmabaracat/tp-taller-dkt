#include "ServidorRed.h"
#include "../Figuras/Gusano.h"
#include "../../Parser/yaml/ParserYaml.h"
#include "../../constantes.h"
#include "../StringUtil.h"
#include "../Reproductor.h"

typedef struct structCliente{
	string username;
	int time;
	SOCKET socket;
	bool enviandoData;
	bool activo;
	list<Gusano*> figuras;
	string ultimoEventoSerializado;
	//Sesion* sesion;
}cliente;

typedef struct{
	SOCKET emisor;
	string msj;
	int tiempoActivo;
}mensajeStru;

class Servidor
{

public:

    Servidor();
    ~Servidor();
	static int tiempo;
	static mensajeStru mensaje;
	static EscenarioParseado* escenario;
    static void actualizar(void* clienteN);
	static void recibirDeCliente(int* clienteN);
	static void enviarCliente(int* clienteN, int tipoPaquete, string mensaje);
	static string dibujablesSerializados;
	static void enviarTerreno(SOCKET sock);

	static void enviarImagen(SOCKET sock, string direccion, int tipoPaquete);
	static ServidorRed* red;
	static void aceptarClientes(void* arg);
	static void enviarEscenario(int num_cliente);
	static void enviarImagenes(SOCKET sock);
	static cliente* clientes;
	static bool terrenoModificado;
	static void setTerrenoModificado(bool estado);
	static string siguienteJugador();
	static unsigned int getCantidadDeClientes();
	static void darArranque();
	

private:

   // IDs for the clients connecting for table in ServerNetwork 
    static unsigned int cliente_id;
   static int buscarCliente(string nombre);
   static void EnviarSonido(int id, audioEnCola aMandar);
   static void enviarPaquete(SOCKET sock, int tipoPaquete, string mensaje);
   bool clienteEnEspera;
   static int idJugando;

   // The ServerNetwork object 

   
    
};