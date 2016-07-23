#include <stdio.h>
#include <strings.h>

#include <posa/pos-parser.h>
#include <posa/pos-table.h>
#include <posa/pos-instructions.h>

int pos_objects_list(pos_table_t *pt)
{
  int i;
#if 0

  for (i = 0; i <= pt->len; i++) {
    if (pt->pi[i]) {
      if (!strcasecmp(pt->pi[i]->token1, "object")) {
	printf("object:%s\n", pt->pi[i]->token2);
      }
      if (!strcasecmp(pt->pi[i]->token1, "object<main>")) {
	printf("object main:%s\n", pt->pi[i]->token2);
      }

    }
  }  
#endif
}

