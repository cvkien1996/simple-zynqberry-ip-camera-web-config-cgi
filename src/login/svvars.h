/* svvars.h */

#ifndef SVVARS_H
#define SVVARS_H

/* method */
#define GET	    0
#define POST	1

/* function prototypes */
char 
svvars_getRequestMethod ();

char **
svvars_getGETvars ();

char **
svvars_getPOSTvars ();

void 
svvars_cleanUp (char form_method, char ** getvars, char ** postvars);

#endif	/* SVVARS_H */

/*** end of file ***/
