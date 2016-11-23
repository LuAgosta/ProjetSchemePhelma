
/**
 * @file prim.h
 * @author Agosta Lucie and Noé Paul-Gauthier>
 * @date Sat Nov 12 16:39:11 2016
 * 
 */

#ifndef _PRIM_H_
#define _PRIM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "object.h"

object plus(object);

object ifnull(object o);
object ifboolean(object o);
object ifsymbol(object o);
object ifinteger(object o);
object ifchar(object o);
object ifstring(object o);
object ifpair(object o);

object chartointeger(object o);
object integertochar(object o);
object numbertostring(object o);
object stringtonumber(object o);
object symboltostring(object o);
object stringtosymbol(object o);
  
object cons(object list);
object list(object o);

#ifdef __cplusplus
}
#endif

#endif
