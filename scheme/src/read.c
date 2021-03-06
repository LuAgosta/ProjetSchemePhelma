
/**
 * @file read.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:31:05 2012
 * @brief Read routine for SFS.
 *
 * Read routine for SFS.
 */

#include <stdio.h>
#include <ctype.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "read.h"



void flip( uint *i ) {

    if ( *i == FALSE ) {
        *i = TRUE;
    }
    else {
        *i = FALSE;
    }
}

/*
 * @fn char* first_usefull_char(char* line)
 *
 * @brief retourne un pointeur sur le premier caractere utile dans line
 * ou NULL si line ne contient que des espaces et des commentaires
 */
char* first_usefull_char(char* line) {

    int i=0;
    if (line == NULL) {
        return NULL;
    }
    i = 0;
    /* on saute les espaces */
    while(line[i] != '\0' && isspace(line[i])) {
        i++;
    }
    /* si fin de ligne => ligne inutile */
    if(line[i] == '\0') {
        return NULL;
    }
    /* si premier caractere non espace est ';' => ligne inutile */
    if(line[i] == ';') {
        return NULL;
    }
    return line + i; /* ligne utile */
}

/**
 * @fn uint  sfs_get_sexpr( char *input, FILE *fp )
 *
 * @brief extrait la prochaine S-Expression dans le flux fp et la stocke dans input
 * (meme si elle est repartie sur plusieurs lignes)
 * @param fp (FILE *) flux d'entree (ouvert en ecriture, mode texte)
 * @param input (char *) chaine allouee de taille BIGSTRING, dans laquelle la S-Expression sera stockée
 *
 * @return S_OK si une S-Expression apparemment valide a ete trouvee
 * @return S_KO si on n'a pas trouve de S-Expression valide
 * @return S_END si fin de fichier atteinte sans avoir lu de caractere utile.
 *
 * sfs_get_sexpr commence par lire une ligne dans fp,
 * puis compte le nombre de parentheses ouvrantes et fermantes sur la ligne.
 * Les parentheses dans des chaines et les caracteres Scheme #\( et #\)
 * ne sont pas comptes.
 *
 * Si le compte devient zéro et que 
 *        - la ligne est fini, la fonction retourne S_OK
 * 				- la ligne n'est pas fini la fonction retourne S_KO
 *
 * S'il y a plus de parentheses fermantes qu'ouvrantes,
 * la fonction retourne S_KO.
 * Les commentaires et espaces qui figurent a la fin de chaque ligne
 * sont remplacés par un espace.
 * Les espaces qui figurent a la fin de la S-Expression (y compris '\n')
 * sont supprimés.
 *
 * Attention : cette fonction refuse les S-Expression multiple sur une seule ligne. Ainsi :
 *    a b c
 *    (qqchose) (autrechose)
 *    (qqchose) 78
 * seront considereees comme des erreurs
 * et la fonction retournera S_KO
 *
 * @pre fp doit etre prealablement ouvert en lecture
 * @pre input doit etre prealablement alloue en memoire, de taille BIGSTRING
 */

typedef enum {
    NOTHING,        /* rien n'a ete trouve encore.. */
    STRING_ATOME,   /* la premiere trouvee dans la ligne semble etre un atome */
    BASIC_ATOME,    /* la premiere trouvee dans la ligne semble etre d'une chaine */
    S_EXPR_PARENTHESIS, /* la premiere trouvee dans la ligne semble etre une expression parenthesee */
    FINISHED        /* on a trouve une S-Expr bien formee */
} EXPRESSION_TYPE_T;

uint  sfs_get_sexpr( char *input, FILE *fp ) {
    int       parlevel = 0;
    uint      in_string = FALSE;
    uint      s = 0;
    char      k[BIGSTRING];
    char      *ret = NULL;
    char      *chunk = NULL;
    uint      i = 0;
    string    sfs_prompt;

    EXPRESSION_TYPE_T typeOfExpressionFound = NOTHING;

    parlevel = 0;
    memset( input, '\0', BIGSTRING );

    do {
        ret = NULL;
        chunk=k;

        /* si en mode interactif*/
        if ( stdin == fp ) {
            uint nspaces = 2*parlevel;

            init_string( sfs_prompt );

            /* le prompt indique le niveau de parenthese
               et decale la prochaine entrée en fonction
               de ce niveau (un peu à la python)*/
            sprintf( sfs_prompt, "SFS:%u > ", parlevel );

            for ( i= 0; i< nspaces; i++ ) {
                sfs_prompt[strlen(sfs_prompt)] = ' ';
            }

            /* si sur plusieurs lignes, le \n équivaut à un espace*/
            if (nspaces>0) {
                input[strlen(input)+1] = '\0';
                input[strlen(input)] = ' ';
            }

            /*saisie de la prochaine ligne à ajouter dans l'input*/
            chunk = readline( sfs_prompt );

        }
        /*si en mode fichier*/
        else {
            chunk=k;
            memset( chunk, '\0', BIGSTRING );
            ret = fgets( chunk, BIGSTRING, fp );

            if ( NULL == ret ) {
                /* fin de fichier...*/
                if ( parlevel != 0 ) {
                    WARNING_MSG( "Parse error: missing ')'" );
                    return S_KO;
                }
                return S_END;
            }

            if (strlen(chunk) == BIGSTRING-1
                    && chunk[BIGSTRING-1] != '\n'
                    && !feof(fp)) {
                WARNING_MSG( "Too long line for this interpreter!" );
                return S_KO;
            }
        }

        /* si la ligne est inutile
        	=> on va directement à la prochaine iteration */
        if (first_usefull_char(chunk) == NULL) {
            continue;
        }


        s = strlen( chunk );

        if ( s > 0 ) {
            if (strlen(input) + s > BIGSTRING-1 ) {
                WARNING_MSG( "Too long a S-expression for this interpreter!" );
                return S_KO;
            }

            for ( i = 0; i< strlen(chunk); i++ ) {
                /* si la fin de la ligne chunk est inutile,
                   on ajoute un espace dans input et on sort de la boucle*/
                if ( in_string == FALSE && first_usefull_char(chunk + i) == NULL ) {
                    chunk[i]='\0';
                    input[strlen(input)] = ' ';
                    break;
                }


                switch(chunk[i]) {
                case '(':
                    if (in_string == FALSE
                            && ! ( i>1 && chunk[i-1] == '\\' && chunk[i-2] == '#' ) ) {
                        parlevel++;
                        typeOfExpressionFound = S_EXPR_PARENTHESIS;
                    }
                    break;
                case ')':
                    if ( in_string == FALSE
                            && ! ( i>1 && chunk[i-1] == '\\' && chunk[i-2] == '#' ) ) {
                        parlevel--;
                        if (parlevel == 0 ) {
                            typeOfExpressionFound = FINISHED;
                        }
                        if ( parlevel < 0 ) {
                            WARNING_MSG( "Parse error : cannot start with ')'" );
                            return S_KO;
                        }
                    }
                    break;
                case '"':
                    if ( i<2 || chunk[i-1] != '\\') {
                        if ( in_string == FALSE ) {
                            if(typeOfExpressionFound == BASIC_ATOME && chunk[i-1] != '\'') {
                                WARNING_MSG("Parse error: invalid string after atom : '%s'", chunk+i);
                                return S_KO;
                            }
                            in_string = TRUE;
                            if(typeOfExpressionFound != S_EXPR_PARENTHESIS) {
                                typeOfExpressionFound = STRING_ATOME;
                            }
                        }
                        else {
                            in_string = FALSE;
                            if(typeOfExpressionFound == STRING_ATOME) {
                                typeOfExpressionFound = FINISHED;
                            }
                        }
                    }
                    break;
                default:
                    if(in_string == FALSE) {
                        if(isspace(chunk[i])) {
                            if(typeOfExpressionFound == BASIC_ATOME) {
                                typeOfExpressionFound = FINISHED;
                            }
                        } else if(typeOfExpressionFound != S_EXPR_PARENTHESIS) {
                            typeOfExpressionFound = BASIC_ATOME;
                        }
                    }
                    break;
                }


                if(typeOfExpressionFound == FINISHED) {
                    char *first_useful = first_usefull_char(chunk + i + 1);
                    if( first_useful != NULL) {
                        if(*first_useful == ')' ) {
                            WARNING_MSG( "Parse error: too many closing parenthesis')'" );
                        }
                        else {
                            WARNING_MSG("Parse error: invalid trailing chars after S-Expr : '%s'", chunk+i);
                        }
                        return S_KO;
                    }
                }

                /* recopie char par char*/
                input[strlen(input)] = chunk[i];
            }
            if(in_string == TRUE) {
                WARNING_MSG( "Parse error: non terminated string on line %s", chunk );
                return S_KO;
            }
        }


        if ( parlevel > 0 && fp != stdin ) {
            if ( feof( fp ) ) {
                WARNING_MSG( "Parse error: missing ')'" );
                return S_KO;
            }

            if (input[strlen(input)-1] == '\n') input[strlen(input)-1] = ' ';
        }
    } while ( parlevel > 0 );

    /* Suppression des espaces restant a la fin de l'expression, notamment le dernier '\n' */
    while (isspace(input[strlen(input)-1])) input[strlen(input)-1] = '\0';

    if(stdin == fp) {
        add_history( input );
    }
    return S_OK;
}

int blanks (char c ) {
	if (' '==c || '\t' == c || '\n' == c || '\0' == c )  {
		return 1 ;
	}
	return 0 ;
}

int parenthesis ( char c ) {
	if (40 == c || 41 == c ) {
		return 1 ;
	}
	return 0;
}

object sfs_read( char *input, uint *here) {
  uint     here2 = 0;
  object o = NULL;
  char input2[BIGSTRING];
  int nbpar;
  int k=1;
	while(blanks(input[*here])){
		*here += 1;
	}
  if (input[*here] == '\''){    /*Conversion de 'a en (quote a)'*/
    input2[0] = '(';
    input2[1] = 'q';
    input2[2] = 'u';
    input2[3] = 'o';
    input2[4] = 't';
    input2[5] = 'e';
    input2[6] = ' ';
    if(input[*here+1]=='('){
      input2[7] = '(';
      k++;
      nbpar=1;
      while(nbpar != 0){
        input2[6+k]=input[*here+k];
        if(input[*here+k]=='('){
          nbpar=nbpar+1;
        }
        if(input[*here+k]==')'){
          nbpar=nbpar-1;
        }
        k++;
      }
    }
    else{
      while(input[*here+k] != '\0' && input[*here+k] != '(' && input[*here+k] != ')' && input[*here+k] != ' '){
        input2[6+k]=input[*here+k];
        k++;
      }
    }
    input2[6+k] = ')';
    input2[7+k] = '\0';
    *here += k-1;
    o = sfs_read(input2, &here2);
    if(o == NULL){
      return NULL;
    }
    return o;
  }
  if ( input[*here] == '(' ) {
		*here += 1;
	   while(blanks(input[*here])){
		     *here += 1;
       }
        if ( input[(*here)] == ')' ) {
            return nil;
        }
        else {
            return sfs_read_pair( input, here);
        }
    }
    else {
        o=sfs_read_atom( input, here);
        if(o == NULL){
        return NULL;
        }
        return o;
    }
}


object sfs_read_atom( char *input, uint *here ) {
	int k = 0;
	string st;
	long nb = 0;
	char* p = NULL;
	int cond0 = 1;
	object atom = NULL;
	while(blanks(input[*here])){
		*here += 1;
	}
	
	switch(input[*here]){
	
	case '#' :

		switch(input[*here+1]){

			/*Booléen*/

			case 't' :
				if(blanks(input[*here+2]) || parenthesis(input[*here+2])){
					*here += 1;
					return vrai;
				}
				else{
					WARNING_MSG("Erreur, booléen invalide");
          				return NULL;
				}

			case 'f' :
				if(blanks(input[*here+2]) || parenthesis(input[*here+2])){
					*here += 1;
					return faux;
				}
				else{
					WARNING_MSG("Erreur, booléen invalide");
          				return NULL;
				}

			/*Caractères*/

			case '\\' :

				if(input[*here+2]=='n' && input[*here+3]=='e' && input[*here+4]=='w' && input[*here+5]=='l' && input[*here+6]=='i' && input[*here+7]=='n' && input[*here+8]=='e'){
					if(blanks(input[*here+9]) || parenthesis(input[*here+9])){
						*here += 8;
						atom = make_char('\n');
						return atom;
					}
					else{
            					WARNING_MSG("Erreur, caractère invalide");
						return NULL;
					}
				}
				if(input[*here+2]=='s' && input[*here+3]=='p' && input[*here+4]=='a' && input[*here+5]=='c' && input[*here+6]=='e'){
					if(blanks(input[*here+7]) || parenthesis(input[*here+7])){
						*here += 6;
						atom = make_char(' ');
						return atom;
					}
					else{
            					WARNING_MSG("Erreur, caractère invalide");
						return NULL;
					}

				}
				if(((33 <= input[*here+2]) && (input[*here+2] <= 253))){
					if(blanks(input[*here+3]) || parenthesis(input[*here+3])){
						atom = make_char(input[*here+2]);
						*here += 2;
						return atom;
					}
					else{
            					WARNING_MSG("Erreur, caractère invalide");
						return NULL;
					}
				}
		}
		break;

	/*chaîne de caractères*/

	case '\"' :
		
		while(input[*here+k+1] != '\"'){

			if((input[*here+k+1] == '\\') && (input[*here+k+2] == '\"' )){		/*string with an anti-slash*/
				st[k] = '\"';
				k += 1;
				*here += 1;
			}

			st[k] = input[*here+k+1];
			k += 1;
		}
		st[k]='\0';
		
		*here += k+1;
		atom = make_string(st);
		return atom;
		

	}

	/*booléen invalide*/

	if(input[*here]==35){
		WARNING_MSG("Erreur, booléen invalide");
		return NULL;
	}

	/*Entier*/
		
	if((strtol(input+*here, &p, 10)!=0) || (input[*here]=='0') || ((input[*here]=='+') && (input[*here+1]=='0')) || ((input[*here]=='-') && (input[*here+1]=='0'))){
		if(p[0]==' ' || p[0]=='\t' || p[0]==')' || p[0]=='(' || p[0]=='\0'){	/*Il est possible d'avoir par exemple 01fonction. Dans ce cas, l'objet sera considéré comme un symbole et non une erreur*/
			if(strtol(input+*here, &p, 10)==0){
				if((input[*here]=='0') || (input[*here]=='+') || (input[*here]=='-')){
					while((input[*here+k+1]!=' ') && (input[*here+k+1]!='(') && (input[*here+k+1]!=')') && (input[*here+k+1]!='\0')&& (input[*here+k+1]!='\n')){
						if(input[*here+k+1]!='0'){
							cond0 = 0;
						}
						k += 1;
					}
					*here += k;
					if(cond0==1){
						atom = make_integer(0);
						return atom;
					}
				}
			}
			nb = strtol(input+*here, &p, 10);
			atom = make_integer(nb);
			while((input[*here+k+1]!=' ') && (input[*here+k+1]!='(') && (input[*here+k+1]!=')') && (input[*here+k+1]!='\"') && (input[*here+k+1]!='\0')){
				k += 1;
			}
			*here += k;
			return atom;
		}

	}

	/*Symbole*/
	
	while ( (33 <= input[*here+k] ) && ( input[*here+k] <= 126 ) && ( input[*here+k]!=40 ) && ( input[*here+k]!=41 ) && ( input[*here+k]!=34 ) ) {
        
            st[k] = input[*here+k] ;
            k += 1 ;
	}
        
	st[k]= '\0';
	*here += k-1;
        atom = make_symbol(st) ;
        return atom ;     
    	
	
	return(NULL);
}
	



object sfs_read_pair( char *stream, uint *i ){
	object o = NULL;
	object pair = NULL;
	pair = make_object(SFS_PAIR);
  	o = sfs_read( stream, i);
  	if(o == NULL){
  	  return NULL;
	}
	pair->this.pair.car = o;
	while(blanks(stream[*i+1])){
		*i += 1;
	}
	if(stream[*i+1] == ')'){
		pair->this.pair.cdr = nil;
		*i += 1;
	}
	else{
		*i += 1;
		pair->this.pair.cdr = sfs_read_pair(stream, i);
	}
	
	return pair;
}
