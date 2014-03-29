#include "ParserYaml.h"

ParserYaml* ParserYaml::parserInstancia = NULL;
EscenarioParseado* ParserYaml::escenario = NULL;
vector<ObjetoParseado>* ParserYaml::objetos = NULL;



ParserYaml::ParserYaml(string nombreArchivo){
	this->nombreArchivo = nombreArchivo;
}

ParserYaml::ParserYaml(){
}


ParserYaml* ParserYaml::getParser(){
	if(parserInstancia == NULL) {
		parserInstancia = new ParserYaml(configPath);
		parserInstancia->parsear();
	}
	return parserInstancia;
}

void ParserYaml::parsear()
{
	try{
		std::ifstream archivo(this->nombreArchivo,ios::out | ios::in);
		if(!archivo.is_open()){
			string mensaje = "El archivo config no se encuentra o es incorrecto.";
			Logger::getLogger()->escribir(mensaje);
			//TODO: Hay que levantar un config por default
			return;
		}
		YAML::Parser parser(archivo);
		YAML::Node doc;

		parser.GetNextDocument(this->documento);
		
		archivo.close();
	} catch(YAML::ParserException& e) {
		Logger::getLogger()->escribir(e.what());
	}
	Logger::getLogger()->guardarEstado();
}

EscenarioParseado* ParserYaml::parsearEscenario(){
	const YAML::Node *nodoEscenario = this->documento.FindValue("escenario");
	EscenarioParseado* esc = new EscenarioParseado();
	if(nodoEscenario) {
		esc->altoPx = this->getValorEscalar(*nodoEscenario,"altopx",altoPxDEF);
		esc->anchoPx = this->getValorEscalar(*nodoEscenario,"anchopx",altoPxDEF);
		esc->altoU = this->getValorEscalar(*nodoEscenario,"altoun",altoUDEF);
		esc->anchoU = this->getValorEscalar(*nodoEscenario,"anchoun",altoUDEF);
		esc->nivelAgua = this->getValorEscalar(*nodoEscenario,"nivel_agua",nivelAguaDEF);
		esc->imagenTierra = this->getValorCadena(*nodoEscenario,"imagen_tierra",mascaraTerrenoDEF);
		esc->imagenCielo = this->getValorCadena(*nodoEscenario,"imagen_cielo",texturaCieloDEF);
		//this->validarSecuencia(*nodoEscenario,"objetos");
		return esc;
	} else {
		Logger::getLogger()->escribir("Error en parseo del yaml - No se encuentra el nodo del escenario. Se utiliza un escenario default.");
		return this->getEscenarioDefault();
	}
	Logger::getLogger()->guardarEstado();
}

EscenarioParseado* ParserYaml::getEscenario(){
	//Si ya lo parsee no vuelvo a parsearlo
	if(escenario == NULL){
		escenario = ParserYaml::getParser()->parsearEscenario();
	}
	return escenario;
}

int ParserYaml::getValorEscalar(const YAML::Node & nodo, string clave, const int valorPorDefecto){
	int valor;
	if(this->validarEscalar(nodo,clave,valor)){
		return valor;
	}
	return valorPorDefecto;
}

string ParserYaml::getValorCadena(const YAML::Node & nodo, string clave, string valorPorDefecto){
	string valor;
	if(this->validarCadena(nodo,clave,valor)){
		return valor;
	}
	return valorPorDefecto;
}

bool ParserYaml::getValorBool(const YAML::Node & nodo, string clave, bool valorPorDefecto){
	string valor;
	//El bool viene como un string: si o no
	if(this->validarCadena(nodo,clave,valor)){
		if(valor == "si"){
			return true;
		}else if(valor == "no"){
			return false;
		}else{
			std::string message = "Error en parseo del yaml - " + this->getNodoInfo(nodo) + ": se esperaba un valor booleano(si o no). Se toma valor por defecto.";
			Logger::getLogger()->escribir(message);
		}
	}
	return valorPorDefecto;
}

string ParserYaml::getValorColor(const YAML::Node & nodo, string clave, string valorPorDefecto){
	string valor;
	if(this->validarCadena(nodo,clave,valor)){
		//Primero tengo que validar que el color sea un string. Si lo es, valido que sean caracteres 0-1 y A-F
		if( !(valor.length() > 6)){
			for(int i=1; i<valor.length();i++){
				if(!isxdigit(valor[i])){
					//Si alguno de los caracteres no pertenece a los hexa devuelvo el valor por defecto
					std::string message = "Error en parseo del yaml - " + this->getNodoInfo(nodo) + ": se esperaba un valor Hexa(valores 0-9 y a-f). Se toma valor por defecto.";
					Logger::getLogger()->escribir(message);
					return valorPorDefecto;
				}
			}
		}
		else{
			std::string message = "Error en parseo del yaml - " + this->getNodoInfo(nodo) + ": se esperaba un valor Hexa, el largo no puede ser mayor a 7. Se toma valor por defecto.";
			Logger::getLogger()->escribir(message);
			return valorPorDefecto;
		}
		
	}else{
		return valorPorDefecto;
	}
	return valor;
}

int ParserYaml::getValorTipoObjeto(const YAML::Node & nodo, string clave, int valorPorDefecto){
	string valor;
	//Tengo que validar que el tipo sea un string
	if(this->validarCadena(nodo,clave,valor)){
		if(valor ==  circuloString){
			return circuloTipo;
		}
		else if(valor ==  rectanguloString){
			return rectanguloTipo;
		}
		else if(valor ==  trianguloString){
			return trianguloTipo;
		}
		else if(valor ==  cuadradoString){
			return cuadradoTipo;
		}
		else if(valor ==  pentagonoString){
			return pentagonoTipo;
		}
		else if(valor ==  hexagonoString){
			return hexagonoTipo;
		}
		else{
			std::string message = "Error en parseo del yaml - " + this->getNodoInfo(nodo) + ": el tipo no es correcto. Se toma valor por defecto.";
			Logger::getLogger()->escribir(message);
		}
	}
	return valorPorDefecto;
}

vector<ObjetoParseado>* ParserYaml::getValorSecuencia(const YAML::Node & nodo, string clave){
	vector<ObjetoParseado>* valor = new vector<ObjetoParseado>();
	const YAML::Node *nodo_aux;
	//Obtengo el nodo que tiene los objectos
	nodo_aux = nodo.FindValue(clave);
	//Tengo que recorrer la secuencia
	for(unsigned int i = 0; i < nodo_aux->size(); i++){
		//Cada elemento es un nodo. Lo parseo y lo agrego al vector
		ObjetoParseado objeto = this->parsearObjeto((*nodo_aux)[i]);
		valor->push_back(objeto);
	}
	return valor;
}

bool ParserYaml::validarEscalar(const YAML::Node & nodo, string clave, int &valor){
	const YAML::Node *nodo_aux;
	std::string str;
	if(nodo_aux = nodo.FindValue(clave)) {
		if ((*nodo_aux).Type() == YAML::NodeType::Scalar ){
			*nodo_aux >> str;
			if (esNumero(str)){
				int value_aux;
				*nodo_aux >> value_aux;
				if(value_aux < 0){
					//value_aux = value_aux * (-1);
					std::string message = "Error en parseo del yaml - " + this->getNodoInfo(*nodo_aux) + ": se esperaba un valor de la clave " + clave + " no es positivo.";
					Logger::getLogger()->escribir(message);
					return false;
				}
				valor = value_aux;
				return true;
			}
			else{
				std::string message = "Error en parseo del yaml - " + this->getNodoInfo(*nodo_aux) + ": el valor de la clave " + clave + " no es numerico.";
				Logger::getLogger()->escribir(message);
			}
		}
		else{
			std::string message = "Error en parseo del yaml - " + this->getNodoInfo(*nodo_aux) + ": el valor de la clave " + clave + " no es Scalar.";
			Logger::getLogger()->escribir(message);
		}
	}
	else{
		std::string message = "Error en parseo del yaml - " + this->getNodoInfo(nodo) + ": no se encontro la clave " + clave + ".";
		Logger::getLogger()->escribir(message);
	}
	return false;
}

string ParserYaml::getNodoInfo(const YAML::Node & nodo){
	YAML::Mark mark = nodo.GetMark();
	std::stringstream info;
	info << "Linea " << mark.line + 1 << ", Columna " << mark.pos + 1;
	return info.str();
}

bool ParserYaml::esNumero(const std::string& s){
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

//para validar los elementos de las secuencias lo deberia hacer el metodo invocante, luego de validar q sea una secuencia.
bool ParserYaml::validarSecuencia(const YAML::Node &nodo, string clave){
	const YAML::Node *nodo_aux;
	if(nodo_aux = nodo.FindValue(clave)){
		if((*nodo_aux).Type() == YAML::NodeType::Sequence){
			return true;
		}
		else{
			std::string message = "Error en parseo del yaml - " + this->getNodoInfo(*nodo_aux) + ": el valor de la clave " + clave + " no es una secuencia.";
			Logger::getLogger()->escribir(message);
		}
	}
	else{
		std::string message = "Error en parseo del yaml - " + this->getNodoInfo(nodo) + ": no se encontro la clave " + clave + ".";
		Logger::getLogger()->escribir(message);
	}
return false;
}


//valida que la cadena almacenada sea la correcta.
bool ParserYaml::validarCadena(const YAML::Node &nodo, string clave, string &cadenaValida){
	const YAML::Node *nodo_aux;
	if(nodo_aux = nodo.FindValue(clave)){
		string cadena_aux;
		*nodo_aux >> cadena_aux;
		if(cadena_aux != ""){
			*nodo_aux >> cadenaValida;
			return true;
		}
		else{
			std::string message = "Error en parseo del yaml - " + this->getNodoInfo(*nodo_aux) + ": el valor de la clave " + clave + " no es correcto.";
			Logger::getLogger()->escribir(message);
		}
	}
	else{
		std::string message = "Error en parseo del yaml - " + this->getNodoInfo(nodo) + ": no se encontro la clave " + clave + ".";
		Logger::getLogger()->escribir(message);
	}
return false;
}


bool ParserYaml::validarImagen(string path){
	std::ifstream archivo(path,ios::out | ios::in);
	return archivo.is_open();
}

EscenarioParseado* ParserYaml::getEscenarioDefault(){
	EscenarioParseado* esc = new EscenarioParseado();
	esc->altoPx = altoPxDEF;
	esc->anchoPx = altoPxDEF;
	esc->altoU = altoUDEF;
	esc->anchoU = altoUDEF;
	esc->nivelAgua = nivelAguaDEF;
	esc->imagenTierra = mascaraTerrenoDEF;
	esc->imagenCielo = texturaCieloDEF;
	return esc;
}


vector<ObjetoParseado>* ParserYaml::parsearObjetos(){
	const YAML::Node *nodoEscenario = this->documento.FindValue("escenario");
	if(nodoEscenario){
		if(this->validarSecuencia(*nodoEscenario,"objetos")){
			//Si es una secuencia, obtengo los objetos
			return this->getValorSecuencia(*nodoEscenario,"objetos");
		}
		//Si no hay nodo objetis tengo que devolver un vector de objetos default
	}else{
		//Si no hay nodo escenario tengo que devolver un vector de objetos default
		Logger::getLogger()->escribir("Error en parseo del yaml - No se encuentra el nodo del escenario. Se utilizan figuras default.");
	}
	Logger::getLogger()->guardarEstado();
}

vector<ObjetoParseado>* ParserYaml::getObjetos(){

	if(objetos == NULL){
		objetos = ParserYaml::getParser()->parsearObjetos();
	}
	return objetos;
}

vector<ObjetoParseado>* ParserYaml::getObjetosDefault(){
	//Devuelvo un vector de objetos default
	vector<ObjetoParseado>* resultado = new vector<ObjetoParseado>();
	resultado->push_back(this->getObjetoDefault());
	return resultado;
}

ObjetoParseado ParserYaml::getObjetoDefault(){
	ObjetoParseado obj;
	obj.tipo = tipoObjDEF;
	obj.x = xDEF;
	obj.y = yDEF;
	obj.ancho = anchoObjDEF;
	obj.alto = altoObjDEF;
	obj.rotacion = rotacionDEF;
	obj.masa = masaDEF;
	obj.color = colorDEF;
	obj.estatico = estaticoDEF;
	return obj;
}

ObjetoParseado ParserYaml::parsearObjeto(const YAML::Node &nodo){
	ObjetoParseado obj;
	obj.tipo = this->getValorTipoObjeto(nodo,"tipo",tipoObjDEF);
	obj.x = this->getValorEscalar(nodo,"x",xDEF);
	obj.y = this->getValorEscalar(nodo,"y",yDEF);
	obj.ancho = this->getValorEscalar(nodo,"ancho",anchoObjDEF);
	obj.alto = this->getValorEscalar(nodo,"alto",altoObjDEF);
	obj.rotacion = this->getValorEscalar(nodo,"rot",rotacionDEF);
	obj.masa = this->getValorEscalar(nodo,"masa",masaDEF);
	obj.color = this->getValorColor(nodo,"color",colorDEF);
	obj.estatico = this->getValorBool(nodo,"estatico",estaticoDEF);
	return obj;
}