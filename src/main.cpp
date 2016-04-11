/* Projeto de Tópicos em Computação Gráfica - IME-USP 2014 */
/* Caio de Freitas Valente */
/* Thiago de Gouveia Nunes */


#include <iostream>
#include <FreeImage.h>

#include "input.h"


#include "hdrimage.h"
int main(int argc, char** argv) 
{
	DLL_API void DLL_CALLCONV FreeImage_Initialise(BOOL load_local_plugins_only FI_DEFAULT(FALSE));
	for(int i = 1; i < argc; i++)
	{
		fileRead(argv[i]);
	}
	FreeImage_DeInitialise();
	return 0;
};
