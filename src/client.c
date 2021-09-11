#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	//Loggear "soy un log"

	config = leer_config();

	//asignar valor de config a la variable valor

	//Loggear valor de config

	t_paquete* paquete = crear_paquete();
	leer_consola(logger,paquete);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	//crear conexion
	ip=config_get_string_value(config, "IP");
	puerto=config_get_string_value(config,"PUERTO");
	int socketCliente = crear_conexion(ip,puerto);

	//enviar CLAVE al servirdor

	valor= config_get_string_value(config,"CLAVE");

	enviar_mensaje(valor,socketCliente);
	enviar_paquete(paquete,socketCliente);

	terminar_programa(socketCliente, logger, config);
}

t_log* iniciar_logger(void)
{
	t_log* logger = log_create("tp0.log","tp0", 1,LOG_LEVEL_INFO);
	return logger;
}

t_config* leer_config(void)
{
	t_config* config= config_create("/home/utnso/workspace/cliente TP0/tp0.config");
	return config;
}

void leer_consola(t_log* logger, t_paquete* paquete)
{
	char* leido = readline(">");

	while(strncmp(leido,"",1)){
		log_info(logger,leido);
		int size = strlen(leido)+1;
		agregar_a_paquete(paquete,leido,size);

		free(leido);
		leido = readline(">");
	}


	//El primero te lo dejo de yapa

}

void paquete(int conexion)
{
	//Ahora toca lo divertido!

	char* leido;
	t_paquete* paquete;


}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	close(conexion);
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
}
