# include "handler.h"

# define ANSI_COLOR_RED "\x1b[31m"
# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_YELLOW "\x1b[33m"
# define ANSI_COLOR_RESET "\x1b[0m"
# define ANSI_COLOR_CYAN "\x1b[36m"

/* Variable global que se relaciona a la ruta óptima*/
route* optRoute;

/* Título del programa*/
void title()
{
	printf("\n");
	printf("  ######  ##        #######  ##     ## ######## ########     \n");
	printf(" ##    ## ##       ##     ## ##     ## ##       ##     ##    \n");
	printf(" ##       ##       ##     ## ##     ## ##       ##     ##    \n");
	printf(" ##       ##       ##     ## ##     ## ######   ########     \n");
	printf(" ##       ##       ##     ##  ##   ##  ##       ##   ##      \n");
	printf(" ##    ## ##       ##     ##   ## ##   ##       ##    ##     \n");
 	printf("  ######  ########  #######     ###    ######## ##     ##    \n\n");
}

/* Insrtucciones del programa*/
void instructions()
{
	printf("\t> Se debe tener los archivos de entrada en la carpeta input.\n");
	printf("\t> Se optimiza los valores entregados en el archivo de entrada, se espera que sigan el formato indicado en el enunciado.\n");
	printf("\t> El archivo de salida se creará en la carpeta output, con su respectivo nombre.\n");
	printf(ANSI_COLOR_GREEN"\t> Desarrollado por Javier Arredondo.\n\n"ANSI_COLOR_RESET);
}

/* Main del programa: llamados a funciones de otros archivos...1313*/
int main(int argc, char const *argv[])
{
	char inputFilename[40];
	char outputFilename[40];
	int option = 0;
	int show = -1;
	do
	{
		system("clear");
		title();
		instructions();

		printf(" A continuación debera ingresar el nombre del archivo que posee el mapa del reino Clover, para realizar las rutas.\n");
		printf(" Nombre del archivo (con extension): ");
		scanf("%s", inputFilename);
		FILE* _file = inDirectory(inputFilename);
		while(!_file)
		{
			printf(ANSI_COLOR_YELLOW"\n Archivo %s no esta en el directorio input.\n"ANSI_COLOR_RESET, inputFilename);
			printf(" Nombre del archivo (con extension): ");
			scanf("%s", inputFilename);
			_file = inDirectory(inputFilename);
		}
		printf(" ¿Quieres ver la traza de la solucion? (0: No | 1: Si)\n");
		scanf("%i", &show);
		printf("%i\n", show);
		while(show != 1 && show != 0)
		{
			printf("Seleccion invalida.  ¿Quieres ver la traza de la solucion? (0: No | 1: Si)\n");	
			scanf("%i", &show);
		}
		graph* myGraph = readGraph(_file);
		showGraph(myGraph);
		route* r = initRoute();
		optRoute = initRoute();
		add(0, 0, r);
		backTracking(myGraph, r, show);
		printf("\n");
		printf(" > ¿Con que nombre quieres guardar el archivo de salida (sin extension)?: \n");
		scanf("%s", outputFilename);
		writeOutput(optRoute, outputFilename);
		printf("\n\n\n ¿Deseas procesar otra mapa del reino clover? Ingresa \"1\" para procesarlo; otro numero para salir: ");
		scanf("%i", &option);
	}
	while(option==1);

	printf("\n Saludos desde marte, terricola!\n");
	return 0;
}