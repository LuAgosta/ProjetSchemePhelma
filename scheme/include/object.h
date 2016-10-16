
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

typedef struct object_t {

    uint type;

    union {

        num              number;
        char             character;
        string           string;
        string           symbol;
	pair 		 pair;


        struct object_t *special;

    } this;

} *object;


object make_object( uint type );
object make_nil( void );
object make_empty_list(void);
object make_boolean(void);
object make_integer(long n);
object make_symbol(string sym);
object make_char(char ch);
object make_pair(object o1, object o2);
object make_string(string st);
object caar(object o);
object cadr(object o);
object cdar(object o);
object cddr(object o);
object cadar(object o);
object caddr(object o);
object cdaar(object o);


#define SFS_NUMBER       0x00
#define SFS_CHARACTER    0x01
#define SFS_STRING       0x02
#define SFS_PAIR         0x03
#define SFS_NIL          0x04
#define SFS_BOOLEAN      0x05
#define SFS_SYMBOL       0x06


extern object nil;
extern object vrai;
extern object faux;
extern object lenv;	/*liste d'environnements*/
extern object tsym; 	/*table de symbole*/

#ifdef __cplusplus
}
#endif

#endif /* _OBJECT_H_ */
