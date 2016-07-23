#include <stdio.h>
#include <stdlib.h>

#include <posa/pos-instructions.h>

void pi_debug(pos_instructions_t *pi)
{
  if (!pi) {
    return;
  }
  printf("%d:[%d] 1=[%s], 2=[%s], 3=[%s], 4=[%s], 5=[%s], 6=[%s] 7=[%s]\n", 
	 pi->line_in_file, pi->nbspaces, 
	 pi->token1?pi->token1:"", 
	 pi->token2?pi->token2:"", 
	 pi->token3?pi->token3:"", 
	 pi->token4?pi->token4:"", 
	 pi->token5?pi->token5:"", 
	 pi->token6?pi->token6:"",
	 pi->token6?pi->token6:"");
}

void pi_free(pos_instructions_t *pi)
{
  if (!pi) return;
  free(pi->token1);
  free(pi->token2);
  free(pi->token3);
  free(pi->token4);
  free(pi->token5);
  free(pi->token6);
  free(pi->token7);
  free(pi);
}
