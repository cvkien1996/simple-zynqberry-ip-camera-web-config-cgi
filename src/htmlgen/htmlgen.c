/**
  **************************************************************************************************
  * @file   htmlgen.c
  * @author Chung Vinh Kien
  **************************************************************************************************
  *
  * Copyright (C) <?> Chung Vinh Kien cvkien1996@gmail.com. All rights reserved.
  *
  **************************************************************************************************
  */

/* Includes --------------------------------------------------------------------------------------*/

#include <stdio.h>
#include "htmlgen.h"

/* Namespace -------------------------------------------------------------------------------------*/

/* Private macros --------------------------------------------------------------------------------*/

/* Private data types ----------------------------------------------------------------------------*/

/* Private variables -----------------------------------------------------------------------------*/

/* Private function prototypes -------------------------------------------------------------------*/

/* Public function bodies ------------------------------------------------------------------------*/

void 
htmlHeader (char * title)
{
    printf("Content-type: text/html; charset=UTF-8\n\n");

    printf("<HTML><HEAD>");

    printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /> \
            <title>%s</title>", title);
}

void
htmlCssAdder (char * csslink)
{
    printf("<LINK REL=\"stylesheet\" HREF=\"%s\" TYPE=\"text/css\" />", csslink);
}

void 
htmlBody ()
{
    printf("</HEAD>\n<BODY>\n");
}

void 
htmlFooter () 
{
    printf("</BODY>\n</HTML>");
}

/* Private function bodies -----------------------------------------------------------------------*/

/* END OF FILE ************************************************************************************/
