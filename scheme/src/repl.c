
/**
 * @file repl.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:13:02 2012
 * @brief Main REPL for SFS.
 *
 * Main REPL for SFS.
 */



#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "object.h"
#include "read.h"
#include "eval.h"
#include "print.h"
#include "env.h"
#include "prim.h"

/* mode d'interaction avec l'interpreteur (exemple)*/
typedef enum {INTERACTIF,SCRIPT} inter_mode;


void usage_error( char *command ) {

    fprintf( stderr, "Usage: %s [file.scm]\n   If no file is given, executes in Shell mode.\n", command );
}


object nil;
object faux;
object vrai;
object noreturnscheme;
object schemesuccess;
object lenv;	/*liste d'environnements*/
object tsym; /*table de symbole*/

object define_f;
object set_f;
object begin_f;
object quote_f;
object and_f;
object or_f;
object if_f;
object lambda_f;
object let_f;
object let_s_f;
object load_f;

object ifnull_p;
object ifboolean_p;
object ifsymbol_p;
object ifinteger_p;
object ifchar_p;
object ifstring_p;
object ifpair_p;
object ifprocedure_p;

object chartointeger_p;
object integertochar_p;
object numbertostring_p;
object stringtonumber_p;
object symboltostring_p;
object stringtosymbol_p;

object plus_p;
object moins_p ; 
object egal_p ; 
object mult_p ;
object quotient_p ;
object remaind_p ;
object inf_p ;
object sup_p ;

object cons_p ;
object car_p ;
object cdr_p ;
object list_p;
object setcar_p;
object setcdr_p;

object eqv_p;
object eq_p;


void init_interpreter ( void ) {
    uint here = 0;
    nil      = make_nil();
    vrai     = make_boolean();
    faux    = make_boolean();
    noreturnscheme = make_noreturnscheme();
    schemesuccess = make_schemesuccess();
    lenv = make_pair(nil,nil);
    tsym = make_pair(nil,nil);
    
    
    define_f = make_object(SFS_FORM);
    addvar(make_symbol("define"),define_f);

    set_f = make_object(SFS_FORM);
    addvar(make_symbol("set!"),set_f);

    begin_f = make_object(SFS_FORM);
    addvar(make_symbol("begin"),begin_f);

    lambda_f = make_object(SFS_FORM);
    addvar(make_symbol("lambda"),lambda_f);

    let_f = make_object(SFS_FORM);
    addvar(make_symbol("let"),let_f);

    let_s_f = make_object(SFS_FORM);
    addvar(make_symbol("let*"),let_s_f);
    
    load_f = make_object(SFS_FORM);
    addvar(make_symbol("load"),load_f);
    
    ifnull_p = make_primitive(&ifnull);
    addvar(make_symbol("null?"),ifnull_p);

    ifboolean_p = make_primitive(&ifboolean);
    addvar(make_symbol("boolean?"),ifboolean_p);

    ifsymbol_p = make_primitive(&ifsymbol);
    addvar(make_symbol("symbol?"),ifsymbol_p);

    ifinteger_p = make_primitive(&ifinteger);
    addvar(make_symbol("integer?"),ifinteger_p);

    ifchar_p = make_primitive(&ifchar);
    addvar(make_symbol("char?"),ifchar_p);

    ifstring_p = make_primitive(&ifstring);
    addvar(make_symbol("string?"),ifstring_p);

    ifpair_p = make_primitive(&ifpair);
    addvar(make_symbol("pair?"),ifpair_p);
    
    ifprocedure_p = make_primitive(&ifprocedure);
    addvar(make_symbol("procedure?"),ifprocedure_p);

    chartointeger_p = make_primitive(&chartointeger);
    addvar(make_symbol("char->integer"),chartointeger_p);

    integertochar_p = make_primitive(&integertochar);
    addvar(make_symbol("integer->char"),integertochar_p);

    numbertostring_p = make_primitive(&numbertostring);
    addvar(make_symbol("number->string"),numbertostring_p);

    stringtonumber_p = make_primitive(&stringtonumber);
    addvar(make_symbol("string->number"),stringtonumber_p);

    symboltostring_p = make_primitive(&symboltostring);
    addvar(make_symbol("symbol->string"),symboltostring_p);

    stringtosymbol_p = make_primitive(&stringtosymbol);
    addvar(make_symbol("string->symbol"),stringtosymbol_p);
    
    plus_p = make_primitive (&plus) ; 
    addvar ( make_symbol("+"), plus_p) ; 
    
    moins_p = make_primitive (&moins) ; 
    addvar (make_symbol("-"), moins_p) ; 
    
    egal_p = make_primitive (&egal) ; 
    addvar (make_symbol("="),egal_p) ; 
    
    mult_p = make_primitive (&multiple) ; 
    addvar (make_symbol("*"),mult_p) ; 
    
    quotient_p= make_primitive (&quotient) ; 
    addvar (make_symbol("quotient"),quotient_p) ;
    
    remaind_p= make_primitive (&remainder) ; 
    addvar (make_symbol("remainder"),remaind_p) ;
    
    inf_p= make_primitive (&inf) ; 
    addvar (make_symbol("<"),inf_p) ;
    
    sup_p = make_primitive(&sup) ; 
    addvar (make_symbol(">"), sup_p) ; 
    
    cons_p = make_primitive(&cons) ; 
    addvar (make_symbol("cons"), cons_p) ;
    
    car_p = make_primitive(&car) ; 
    addvar (make_symbol("car"), car_p) ;
    
    cdr_p = make_primitive(&cdr) ; 
    addvar (make_symbol("cdr"), cdr_p) ;

    list_p = make_primitive(&list);
    addvar(make_symbol("list"),list_p);
    
    setcar_p = make_primitive(&setcar);
    addvar(make_symbol("set-car!"),setcar_p);

    setcdr_p = make_primitive(&setcdr);
    addvar(make_symbol("set-cdr!"),setcdr_p);
    
    eqv_p = make_primitive(&eqv);
    addvar(make_symbol("eqv?"),eqv_p);

    
    eq_p = make_primitive(&eq);
    addvar(make_symbol("eq?"),eq_p);

    sfs_eval(sfs_read("(define (map proc items) (if (null? items) '() (cons (proc (car items)) (map proc (cdr items)))))",&here),lenv); 
   
}

int main ( int argc, char *argv[] ) {

    char     input[BIGSTRING];
    uint     here = 0;
    object   output = NULL;
    object   sexpr = NULL;
    inter_mode mode;
    FILE *   fp = NULL; /* le flux dans lequel les commande seront lues : stdin (mode shell) ou un fichier */

    /* exemples d'utilisation des macros du fichier notify.h */
    /* WARNING_MSG : sera toujours affiche */
    WARNING_MSG("Un message WARNING_MSG !");

    /* macro INFO_MSG : uniquement si compil avec -DVERBOSE. Cf Makefile*/
    INFO_MSG("Un message INFO_MSG : Debut du programme %s", argv[0]);

    /* macro DEBUG_MSG : uniquement si compil avec -DDEBUG (ie : compil avec make debug). Cf Makefile */
    DEBUG_MSG("Un message DEBUG_MSG !");

    /* La ligne suivante provoquerait l'affichage du message
       puis la sortie du programme avec un code erreur non nul (EXIT_FAILURE) */
    /* ERROR_MSG("Erreur. Arret du programme"); */

    if ( argc > 2 ) {
        usage_error( argv[0] );
        exit( EXIT_FAILURE );
    }
    if(argc == 2 && strcmp(argv[1], "-h") == 0) {
        usage_error( argv[0] );
        exit( EXIT_SUCCESS );
    }

    init_interpreter();

    /*par defaut : mode shell interactif */
    fp = stdin;
    mode = INTERACTIF;
    if(argc == 2) {
        /* mode fichier de commandes */
        fp = fopen( argv[1], "r" );
        if ( fp == NULL ) {
            perror( "fopen" );
            exit( EXIT_FAILURE );
        }
        mode = SCRIPT;
    }


    while ( 1 ) {
        input[0]='\0';
        here = 0;
        output = NULL;
        sexpr = NULL;
        uint Sexpr_err;

        Sexpr_err = sfs_get_sexpr( input, fp );

        if ( S_OK != Sexpr_err) {
            /* si fichier alors on sort*/
            if (mode == SCRIPT) {
                fclose( fp );
                if (Sexpr_err==S_END) {
                    /* Cas fin de fichier script */
                    exit(EXIT_SUCCESS);
                }
                /* Cas S-Expression mal formee dans le fichier script */
                ERROR_MSG("Malformed S-expression --- Aborts");
            }
            /*sinon on rend la main à l'utilisateur*/
            continue;
        }

        if ( 0 == strlen( input ) ) {
            continue;
        }

        /* Pour le step 0 on se contente d'afficher */
        /* la S-Expression lue */
        /* puis d'en lire une autre */
        /* METTRE EN COMMENTAIRE LES DEUX LIGNES SUIVANTES */
        /* POUR PASSER A L'INCREMENT 1 */
        /*printf("%s\n", input );*/
        /*continue;*/

        here  = 0;
        sexpr = sfs_read( input, &here );
        if ( NULL == sexpr ) {
            /* si fichier alors on sort*/
            if (mode == SCRIPT) {
                fclose( fp );
                /*macro ERROR_MSG : message d'erreur puis fin de programme ! */
                ERROR_MSG("Invalid S-expression --- Aborts");
            }
            /*sinon on rend la main à l'utilisateur*/
            continue ;
        }

        output = sfs_eval( sexpr, lenv );
        if( NULL == output) {
            /* si fichier alors on sort*/
            if (mode == SCRIPT) {
                fclose( fp );
                /*macro ERROR_MSG : message d'erreur puis fin de programme ! */
                ERROR_MSG("Error while evaluating input --- Aborts");
            }
            /*sinon on rend la main à l'utilisateur*/
            continue ;
        }

        if(output != noreturnscheme){
          printf( "==> " );
          sfs_print(output);
          printf( "\n" );
        }
    }

    if (mode == SCRIPT) {
        fclose( fp );
    }
    exit( EXIT_SUCCESS );
}
