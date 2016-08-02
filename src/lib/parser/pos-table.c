#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <posa/pos-table.h>
#include <posa/pos-instructions.h>
#include <posa/log.h>


pos_table_t *pos_table_new(int nblines)
{
  pos_table_t *pos_table;
  
  pos_table = malloc(sizeof(pos_table_t));
  if (!pos_table) {
    fprintf(stderr, "Error allocating the pos instructions\n");
    return NULL;
  }
  pos_table->len = 0;
  pos_table->nblines = nblines;

  pos_table->pi = (pos_instructions_t **)calloc(nblines, sizeof(pos_instructions_t *));
  if (!pos_table->pi) {
    fprintf(stderr, "Error allocating pos_table->pi!\n");
    return NULL;
  }
  
  return pos_table;
}

void pos_table_free(pos_table_t *pos_table)
{
  if (!pos_table) return;
  int i;
  for (i = 0; i <= pos_table->len; i++) {
    pi_free(pos_table->pi[i]);
  }
  free(pos_table->pi);
  free(pos_table);
}

int pos_table_append(pos_table_t *pos_table, pos_instructions_t *pi)
{
  log_debug(">>> %s\n", __FUNCTION__);

  int len = pos_table->len;
  //  printf("current len:%d\n", len);

  if (!pi) {
    return -1;
  }
  
  if (!pos_table) {
    log_notice("Cannot append instruction to non-existing table.\n");
    return -1;
  }

  if (pos_table->len + 1 > pos_table->nblines) {
    log_crit("Cannot add a value since the table length cannot be greater than the number of lines\n");
    return -1;
  }

  //  printf("hey\n");
  //  pos_table->pi[len] = (pos_instructions_t *)malloc(sizeof(pos_instructions_t *));
  pos_table->pi[len] = pi;
  //  printf("just add pi->token1=%s and pi->token2=%s at len %d\n", pi->token1, pi->token2, len);
  
  pos_table->len++;
  
  //  pi_debug(pi);

  
  return 0;
}

void pos_table_debug(pos_table_t *pos_table)
{
  int i;
  
  log_notice("pos_table\n");
  log_notice("=========\n");
  log_notice("len:%d\n", pos_table->len);
  log_notice("nblines:%d\n", pos_table->nblines);
  log_notice("pos table length:%d\n", pos_table->len);
  log_notice("instructions:\n");
  for(i=0; i < pos_table->len; i++) {
    printf("\t");
    pi_debug(pos_table->pi[i]);
  }
}

