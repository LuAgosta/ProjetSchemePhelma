#ifndef _ENV_H_
#define _ENV_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "object.h"

void addvar(object var, object val);
void addvarenv(object var, object val, object env);
object addenv(void);
object in_envc(object var);
object in_lenv(object var);

#ifdef __cplusplus
}
#endif

#endif
