/**
  **************************************************************************************************
  * @file   sv_login.c
  * @author Chung Vinh Kien
  **************************************************************************************************
  *
  * Copyright (C) <?> Chung Vinh Kien cvkien1996@gmail.com. All rights reserved.
  *
  **************************************************************************************************
  */

/* Includes --------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "sv_login.h"
#include "svvars.h"
#include "../htmlgen/htmlgen.h"
#include "svcgi.h"
#include "svconf.h"

/* Namespace -------------------------------------------------------------------------------------*/

/* Private macros --------------------------------------------------------------------------------*/

/* Private data types ----------------------------------------------------------------------------*/

/* Private variables -----------------------------------------------------------------------------*/

/* Private function prototypes -------------------------------------------------------------------*/

/* Public function bodies ------------------------------------------------------------------------*/

int
main (int argc, char ** argv) 
{
    char ** postvars    = NULL; /* POST request data repository */
    char ** getvars     = NULL; /* GET request data repository */
    char form_method    = 0;    /* POST = 1, GET = 0 */  
    
    /* get request method: GET or POST */
    form_method = svvars_getRequestMethod();

    if (form_method == POST) 
    {
        //getvars = svvars_getGETvars();
        postvars = svvars_getPOSTvars();
    }
    else if (form_method == GET)
    {

    }
    // else if(form_method == GET) 
    // {
    //  getvars = svvars_getGETvars();
    // }
    // else
    // {
    //  // error
    // }

    if (1 == svconf_action(postvars, form_method))
    {
        svconf_save_config(postvars, form_method);
    }

    if (GET == form_method)
    {
        /* header */
        htmlHeader(CFG_TITLE);

        /* add css */
        htmlCssAdder(CFG_CSS_SCRIPT_1);
        htmlCssAdder(CFG_CSS_SCRIPT_2);

        /* add script */
        htmlScriptAdder(CFG_JS_SCRIPT_1);
        //htmlScriptAdder(CFG_JS_SCRIPT_2);

        /* body */
        //htmlBody();
        printf("</HEAD>\n<BODY onload = \"focusUsername();\">\n");
        /* process and save config */

        //printf("<h1>DEBUG LOG</h1>");

        // if (postvars != NULL)
        // {
        //     // int varindex = 0;
        //     // while (postvars[varindex] != NULL)
        //     // {
        //     //     printf("<p>%s</p>", postvars[varindex]);
        //     //     varindex++;
        //     // }
            
        // }
        // else
        // {
        //     printf("<h1>NULL</h1>");
        // }

        /* bind data */
        svcgi_body(postvars, form_method);

        /* footer */
        htmlFooter();
    }
    else if (POST == form_method)
    {
        printf("HTTP/1.0 303 See Other\r\n");
        printf("Location: %s\r\n\r\n", argv[0]);
        //printf("Content-type: text/html; charset=UTF-8\n\n");
        
    }

    /* cleanup */
    svvars_cleanUp(form_method, getvars, postvars);

    fflush(stdout);
    exit(0);
    return 0;
}

/* Private function bodies -----------------------------------------------------------------------*/

/* END OF FILE ************************************************************************************/
