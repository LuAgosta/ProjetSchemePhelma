
#include <stdlib.h>
#include <stdio.h>

#include "load.h"
#include "eval.h"
#include "print.h"
#include "read.h"


object load(char* namefile){
  char str[BIGSTRING];
  uint here = 0;
  FILE* file = NULL;
  file = fopen(namefile,"r");
  if(file == NULL){
    WARNING_MSG("Ouverture du fichier impossible");
    return NULL;
  }
  strcpy(str,"");
  if (file != NULL) {
    while(fgets(str, BIGSTRING, file) != NULL){
      sfs_eval(sfs_read(str, &here),lenv);
      here = 0;
    }
  }
  fclose(file);
  return schemesuccess;
}
