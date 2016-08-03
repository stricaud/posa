#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <posa/pos-parser.h>
#include <posa/pos-instructions.h>
#include <posa/pos-table.h>
#include <posa/pos-table-read.h>

#define MAX_LINE_LENGTH 2048

pos_instructions_t *handle_line(const char *line, size_t linesize, int linenb, void *user)
{
  //  printf("%d:%s\n", linenb, line);
  pos_instructions_t *pi;
  size_t pos;
  int first_char_found = 0;
  int space_count = 0;
  char tokenbuf[MAX_LINE_LENGTH];// No need to bound check since the line was checked previously
  int tokenbuf_pos = 0;
  int token_nb = 1;

  pi = malloc(sizeof(pos_instructions_t));
  if (!pi) {
    fprintf(stderr, "Error allocating the pos instructions\n");
    return NULL;
  }
  pi->line_in_file = linenb;
  pi->nbspaces = 0;
  pi->token1 = NULL;
  pi->token2 = NULL;
  pi->token3 = NULL;
  pi->token4 = NULL;
  pi->token5 = NULL;
  pi->token6 = NULL;
  pi->token7 = NULL;

  token_nb = 1;
  //  printf("line=[%s]\n", line);
  for (pos = 0; pos <= linesize; pos++) {
    if ((line[pos] == ' ') || (line[pos] == '\t') || (pos == linesize)) {
      if ((!pi->token1) && (tokenbuf_pos == 0)) {
	space_count++;
      } else {
	if (tokenbuf_pos) {
	  tokenbuf[tokenbuf_pos] = '\0';

	  switch(token_nb) {
	  case 1:
	    pi->token1 = strdup(tokenbuf);
	    break;
	  case 2:
	    pi->token2 = strdup(tokenbuf);
	    break;
	  case 3:
	    pi->token3 = strdup(tokenbuf);
	    break;
	  case 4:
	    pi->token4 = strdup(tokenbuf);
	    break;
	  case 5:
	    pi->token5 = strdup(tokenbuf);
	    break;
	  case 6:
	    pi->token6 = strdup(tokenbuf);
	    break;
	  case 7:
	    pi->token7 = strdup(tokenbuf);
	    break;
	  default:
	    fprintf(stderr, "Error, token number %d not handled: incorrect syntax\n", token_nb);
	  }

	  token_nb++;
	  tokenbuf_pos = 0;
	}
      }
    } else {
      if (!pi->token1) {
	//	printf("ohoh:%s\n", line);
	// I have a char, wether this is the first char or further, I still have a char :-)
	pi->nbspaces = space_count;
	if (line[pos] == '#') {
	  // This is a comment, so I drop the whole thing.
	  pi_free(pi);
	  return NULL;
	}
      } else {
	//	printf("ohoh:%s\n",line);
      }
      tokenbuf[tokenbuf_pos] = line[pos];
      tokenbuf_pos++;

    }
  }

  if ((!pi->token1) && (!pi->token2) && (!pi->token3) && (!pi->token4) && (!pi->token5) && (!pi->token6)) {
    pi_free(pi);
    return NULL;
  }

  return pi;
}

int posa_parser_count_lines(char *buffer, size_t bufsize) 
{
  size_t pos;
  int counter = 0;

  for (pos = 0; pos < bufsize; pos++) {
    // Find lines that have only empty spaces
    // Find lines that start with #
    if (buffer[pos] == '\n') {
      counter++;
    }
  }

  return counter;
}

void _print_buffer(char *buffer, size_t bufsize)
{
  size_t pos;

  for (pos = 0; pos < bufsize; pos++) {
    printf("%c", buffer[pos]);
  }

}

pos_table_t *posa_parser_handle_buffer(char *buffer, size_t bufsize, int nblines)
{
  size_t pos = 0;
  int start_line = 1;
  char line[MAX_LINE_LENGTH];
  int linepos = 0;
  int cur_line = 1;
  pos_instructions_t *pi = NULL;
  pos_table_t *pos_table;
  //  printf("bufsize = %ld\n", bufsize);

  pos_table = pos_table_new(nblines);

  for (pos = 0; pos < bufsize; pos++) {
    if (linepos > MAX_LINE_LENGTH) {
      fprintf(stderr, "Line too long, go fix your file.");
      return NULL;
    }
    if (buffer[pos] == '\n') {
      line[linepos] = '\0';
      
      pi = handle_line((char *)line, linepos, cur_line, NULL);
      //      if (pi) {
      //	printf("pi->token1=%s\n", pi->token1);
      //      }
      //      printf("Adding a new line:[%s]\n", line);
      pos_table_append(pos_table, pi);

      linepos = 0;
      cur_line++;
    } else {
      line[linepos] = buffer[pos];
      linepos++;
    }

  }

  
  return pos_table;
}

