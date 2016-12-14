
/**
 * @file object.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 17:49:46 2012
 * @brief Object definition for SFS.
 *
 * Object definition for SFS.
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "number.h"


typedef struct pair_t {

            struct object_t* car;
            struct object_t* cdr;

} pair;
	
typedef struct object_t *(*primitive)( struct object_t *);

typedef struct compound_t{
 
	struct object_t *parms ; 
	struct object_t *body ; 
	struct object_t *env ; 
} compound ; 


typedef struct object_t {

    uint type;

    union {

        num              number;
        char             character;
        string           string;
        string           symbol;
	pair 		 pair;
  	primitive        primitive;
	compound 	 compound  ;
        struct object_t *special;

    } this;

} *object;


object make_object( uint type );
object make_primitive(primitive);
object make_nil( void );
object make_empty_list(void);
object make_boolean(void);
object make_integer(long n);
object make_symbol(string sym);
object make_char(char ch);
object make_pair(object o1, object o2);
object make_string(string st);
object make_noreturnscheme(void);
object make_schemesuccess(void);
object make_compound(object parms, object body, object env);
object caar(object o);
object cadr(object o);
object cdar(object o);
object cddr(object o);
object cadar(object o);
object caddr(object o);
object cdaar(object o);
object caadr(object o);
object cdadr(object o);
object cdddr(object o);
object cadddr(object o);
object copyobject(object input);
int nbelem(object o);




#define SFS_NUMBER       0x00
#define SFS_CHARACTER    0x01
#define SFS_STRING       0x02
#define SFS_PAIR         0x03
#define SFS_NIL          0x04
#define SFS_BOOLEAN      0x05
#define SFS_SYMBOL       0x06
#define SFS_PRIMITIVE    0x07
#define SFS_COMPOUND	 0x08
#define SFS_NORETURNSCHEME	 0x09
#define SFS_FORM         0x0A
#define SFS_SCHEMESUCCESS 0x0B


extern object nil;
extern object vrai;
extern object faux;
extern object noreturnscheme;
extern object schemesuccess;
extern object lenv;	/*liste d'environnements*/
extern object tsym; 	/*table de symbole*/
	
extern object define_f;
extern object set_f;
extern object quote_f;
extern object and_f;
extern object or_f;
extern object if_f;
extern object begin_f;
extern object lambda_f;
extern object let_f;
extern object let_s_f;
extern object load_f;

/**Primitives**/

/*predicat*/
extern object ifnull_p;
extern object ifboolean_p;
extern object ifsymbol_p;
extern object ifinteger_p;
extern object ifchar_p;
extern object ifstring_p;
extern object ifpair_p;
extern object ifprocedure_p;

extern object chartointeger_p;
extern object integertochar_p;
extern object numbertostring_p;
extern object stringtonumber_p;
extern object symboltostring_p;
extern object stringtosymbol_p;

/* arithmétique*/
extern object plus_p ;
extern object moins_p ; 
extern object egal_p ;  
extern object mult_p ;  
extern object quotient_p ;
extern object remaind_p ;
extern object inf_p ;
extern object sup_p ;
	
/* manipulation liste*/
extern object cons_p ;
extern object car_p ;
extern object cdr_p ;
extern object list_p;
extern object setcar_p;
extern object setcdr_p;
	
extern object eqv_p;
extern object eq_p;

#ifdef __cplusplus
}
#endif

#endif /* _OBJECT_H_ */
