/**
  **************************************************************************************************
  * @file   svconf.c
  * @author Chung Vinh Kien
  **************************************************************************************************
  *
  * Copyright (C) <?> Chung Vinh Kien cvkien1996@gmail.com. All rights reserved.
  *
  **************************************************************************************************
  */

/* Includes --------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svvars.h"
#include "svconf.h"

/* Namespace -------------------------------------------------------------------------------------*/

/* Private macros --------------------------------------------------------------------------------*/



/* Private data types ----------------------------------------------------------------------------*/

/* Private variables -----------------------------------------------------------------------------*/

static const char * const g_tz_list[] = {
    "(GMT -12:00) Eniwetok, Kwajalein",
    "(GMT -11:00) Midway Island, Samoa",
    "(GMT -10:00) Hawaii",
    "(GMT -9:00) Alaska",
    "(GMT -8:00) Pacific Time (US & Canada)",
    "(GMT -7:00) Mountain Time (US & Canada)",
    "(GMT -6:00) Central Time (US & Canada), Mexico City",
    "(GMT -5:00) Eastern Time (US & Canada), Bogota, Lima",
    "(GMT -4:00) Atlantic Time (Canada), Caracas, La Paz",
    "(GMT -3:30) Newfoundland",
    "(GMT -3:00) Brazil, Buenos Aires, Georgetown",
    "(GMT -2:00) Mid-Atlantic",
    "(GMT -1:00 hour) Azores, Cape Verde Islands",
    "(GMT) Western Europe Time, London, Lisbon, Casablanca",
    "(GMT +1:00 hour) Brussels, Copenhagen, Madrid, Paris",
    "(GMT +2:00) Kaliningrad, South Africa",
    "(GMT +3:00) Baghdad, Riyadh, Moscow, St. Petersburg",
    "(GMT +3:30) Tehran",
    "(GMT +4:00) Abu Dhabi, Muscat, Baku, Tbilisi",
    "(GMT +4:30) Kabul",
    "(GMT +5:00) Ekaterinburg, Islamabad, Karachi, Tashkent",
    "(GMT +5:30) Bombay, Calcutta, Madras, New Delhi",
    "(GMT +5:45) Kathmandu",
    "(GMT +6:00) Almaty, Dhaka, Colombo",
    "(GMT +7:00) Bangkok, Hanoi, Jakarta",
    "(GMT +8:00) Beijing, Perth, Singapore, Hong Kong",
    "(GMT +9:00) Tokyo, Seoul, Osaka, Sapporo, Yakutsk",
    "(GMT +9:30) Adelaide, Darwin",
    "(GMT +10:00) Eastern Australia, Guam, Vladivostok",
    "(GMT +11:00) Magadan, Solomon Islands, New Caledonia",
    "(GMT +12:00) Auckland, Wellington, Fiji, Kamchatka"    
};

/* Private function prototypes -------------------------------------------------------------------*/
static void
select_timezone (char * selected);

static void
resolution_to_wh (char * resolution, int res_len, char * width, char * height);

static void
get_number_only (char * str, int str_len, char * value);

static void
replace_config_value (char * replace_src, int src_len, char * replace_str, int replace_len);

static int
save_setting (svconfig_t config, char * filename);

static int
load_setting (svconfig_t * p_config, char * filename);

/* Public function bodies ------------------------------------------------------------------------*/

/*
0   -   cam_resolution
2   -   cam_fps
4   -   cam_bitrate
6   -   net_static, net_dhcp        7 - on
8   -   net_ip
10  -   net_subnet
12  -   net_gateway
14  -   net_mac
16  -   net_rtspport
18  -   net_httppport
20  -   date_format
22  -   date_timezone
24  -   date_current
26  -   date_time
28  -   user_name
30  -   user_pw
32  -   action_submit               33 - Save, Cancel, Logout
*/

int
svconf_action (char ** vars, char form_method)
{
    int ret         = 0;
    int varindex    = 0;
    
    if (POST == form_method && NULL != vars)
    {
        while (NULL != vars[varindex])
        {
            if (NULL != strstr(vars[varindex], "action_submit"))
            {
                int varvalue = varindex + 1;
                if (NULL != strstr(vars[varvalue], "Save"))
                    return 1;
                if (NULL != strstr(vars[varvalue], "Cancel"))
                    return 2;
                if (NULL != strstr(vars[varvalue], "Logout"))
                    return 3;
            }

            varindex++;
        }
    }

    return ret;
}

int
svconf_save_config (char ** vars, char form_method)
{
    svconfig_t main_conf;

    int ret         = 0;
    int varindex    = 0;
    int varvalue    = 0;

    if (POST != form_method || NULL == vars)
        return -1;

    if (POST == form_method && NULL != vars)
    {
        memset(&main_conf, 0, sizeof(main_conf));

        memcpy(main_conf.streampath, DEFAULT_STREAM_PATH, CONFIG_MAXBUF);

        while (NULL != vars[varindex])
        {
            varvalue = varindex + 1;

            switch (varindex)
            {
                case 0:
                    resolution_to_wh(vars[varvalue], strlen(vars[varvalue]), main_conf.cam_width, main_conf.cam_height);
                break;

                case 2:
                    get_number_only(vars[varvalue], strlen(vars[varvalue]), main_conf.cam_fps);
                break;

                case 4:
                    get_number_only(vars[varvalue], strlen(vars[varvalue]), main_conf.cam_bitrate);
                break;

                case 6:
                    memcpy(main_conf.net_is_dhcp, vars[varvalue], strlen(vars[varvalue]));
                break;

                case 8:
                    memcpy(main_conf.net_ip, vars[varvalue], strlen(vars[varvalue]));
                break;

                case 10:
                    memcpy(main_conf.net_subnet, vars[varvalue], strlen(vars[varvalue]));
                break;

                case 12:
                    memcpy(main_conf.net_gateway, vars[varvalue], strlen(vars[varvalue]));
                break;

                case 14:
                    memcpy(main_conf.net_mac, vars[varvalue], strlen(vars[varvalue]));
                break;

                case 16:
                    memcpy(main_conf.net_rtsp_port, vars[varvalue], strlen(vars[varvalue]));
                break;

                case 18:
                    memcpy(main_conf.net_http_port, vars[varvalue], strlen(vars[varvalue]));
                break;

                case 20:
                    memcpy(main_conf.date_format, vars[varvalue], strlen(vars[varvalue]));
                break;

                case 22:
                    memcpy(main_conf.date_timezone, vars[varvalue], strlen(vars[varvalue]));
                break;

                case 24:
                    memcpy(main_conf.date_current_1, vars[varvalue], strlen(vars[varvalue]));
                break;

                case 26:
                    memcpy(main_conf.date_current_2, vars[varvalue], strlen(vars[varvalue]));
                break;

                case 28:
                    memcpy(main_conf.date_current_3, vars[varvalue], strlen(vars[varvalue]));
                break;

                case 30:
                    memcpy(main_conf.date_time, vars[varvalue], strlen(vars[varvalue]));
                break;

                case 32:
                    memcpy(main_conf.username, vars[varvalue], strlen(vars[varvalue]));
                break;

                case 34:
                    memcpy(main_conf.password, vars[varvalue], strlen(vars[varvalue]));
                break;

                default:
                break;
            }

            varindex = varindex + 2;
        }

        // printf("<p>");
        // printf("%s<br>", main_conf.username);
        // printf("%s<br>", main_conf.password);
        // printf("%s %s %s %s<br>", main_conf.cam_width, main_conf.cam_height, main_conf.cam_fps, main_conf.cam_bitrate);
        // printf("%s %s %s %s %s %s %s<br>", main_conf.net_is_dhcp, main_conf.net_ip, main_conf.net_subnet, main_conf.net_gateway, main_conf.net_mac, main_conf.net_http_port, main_conf.net_rtsp_port);
        // printf("%s %s %s %s<br>", main_conf.date_format, main_conf.date_timezone, main_conf.date_current, main_conf.date_time);
        // printf("</p>");

        save_setting(main_conf, CONFIG_FILENAME);
    }

    return ret;
}

svconfig_t
svconf_load_config ()
{
    svconfig_t ret;

    memset(&ret, 0, sizeof(ret));

    //if ((GET == form_method) && (NULL != vars))
    {
        load_setting(&ret, CONFIG_FILENAME); 

        printf("<div id=\"container\">  \
            <div id=\"main-head\">  \
                <div id=\"banner\"></div>   \
            </div>  \
            <div id=\"main-content\">   \
                <div>   \
                    <form name=\"CONFIG_FORM\" target=\"_self\" method=\"POST\"> \
                    <ul class=\"cfg_cat_ul\">");

                printf("<li class=\"cfg_cat_li\">   \
                            <div>   \
                                <div class=\"cat_name\"><h1>Camera</h1></div>   \
                                <div class=\"cat_values\">  \
                                    <ul class=\"cat_ul\">   \
                                        <li class=\"cat_li\">   \
                                            <div>   \
                                                <span class=\"cat_li_name\">Resolution</span>   \
                                                <select name=\"cam_resolution\" class=\"cat_li_select\">");

                                                if ((NULL != strstr(ret.cam_width, "1280")) && 
                                                    (NULL != strstr(ret.cam_height, "720")))
                                                {
                                                printf("<option selected=\"selected\">1280x720</option>   \
                                                        <option>640x480</option>");
                                                }
                                                else
                                                {
                                                printf("<option>1280x720</option>   \
                                                        <option selected=\"selected\">640x480</option>");
                                                }

                                                printf("</select>   \
                                            </div>  \
                                        </li>   \
                                        <li class=\"cat_li\">   \
                                            <div>   \
                                                <span class=\"cat_li_name\">Frame rate</span>   \
                                                <select name=\"cam_fps\" class=\"cat_li_select\">");

                                                if (NULL != strstr(ret.cam_fps, "30"))
                                                {
                                                printf("<option selected=\"selected\">30 fps</option>     \
                                                        <option>20 fps</option>");
                                                }
                                                else
                                                {
                                                printf("<option>30 fps</option>     \
                                                        <option selected=\"selected\">20 fps</option>");
                                                }

                                                printf("</select>   \
                                            </div>  \
                                        </li>   \
                                        <li class=\"cat_li\">   \
                                            <div>   \
                                                <span class=\"cat_li_name\">Bit rate</span> \
                                                <select name=\"cam_bitrate\" class=\"cat_li_select\">");

                                                if (NULL != strstr(ret.cam_bitrate, "400"))
                                                {
                                                printf("<option selected=\"selected\">400 kbit/s</option> \
                                                        <option>750 kbit/s</option> \
                                                        <option>1 Mbit/s</option>   \
                                                        <option>2.5 Mbit/s</option>");
                                                }
                                                else if (NULL != strstr(ret.cam_bitrate, "750"))
                                                {
                                                printf("<option>400 kbit/s</option> \
                                                        <option selected=\"selected\">750 kbit/s</option> \
                                                        <option>1 Mbit/s</option>   \
                                                        <option>2.5 Mbit/s</option>");
                                                }
                                                else if (NULL != strstr(ret.cam_bitrate, "1"))
                                                {
                                                printf("<option>400 kbit/s</option> \
                                                        <option>750 kbit/s</option> \
                                                        <option selected=\"selected\">1 Mbit/s</option>   \
                                                        <option>2.5 Mbit/s</option>");
                                                }
                                                else
                                                {
                                                printf("<option>400 kbit/s</option> \
                                                        <option>750 kbit/s</option> \
                                                        <option>1 Mbit/s</option>   \
                                                        <option selected=\"selected\">2.5 Mbit/s</option>");
                                                }

                                                printf("</select>   \
                                            </div>  \
                                        </li>   \
                                    </ul>   \
                                </div>  \
                            </div>  \
                        </li>");

                printf("<li class=\"cfg_cat_li\">   \
                            <div>   \
                                <div class=\"cat_name\"><h1>Network</h1></div>  \
                                <div class=\"cat_values\">  \
                                    <ul class=\"cat_ul\">   \
                                        <li class=\"cat_li\">   \
                                            <div>   \
                                                <span class=\"cat_li_name\">Mode</span>");

                                            if (NULL != strstr(ret.net_is_dhcp, "1"))
                                            {
                                            printf("<span class=\"cat_li_rad\"><input id=\"rad1\" type=\"radio\" name=\"net_is_dhcp\" value=\"0\"/><label for=\"rad1\">Static</label></span> \
                                                    <span class=\"cat_li_rad\"><input id=\"rad2\" type=\"radio\" name=\"net_is_dhcp\" value=\"1\" checked=\"checked\"/><label for=\"rad2\">DHCP</label></span> \
                                                    ");
                                            }
                                            else
                                            {
                                            printf("<span class=\"cat_li_rad\"><input id=\"rad1\" type=\"radio\" name=\"net_is_dhcp\" value=\"0\" checked=\"checked\"/><label for=\"rad1\">Static</label></span> \
                                                    <span class=\"cat_li_rad\"><input id=\"rad2\" type=\"radio\" name=\"net_is_dhcp\" value=\"1\"/><label for=\"rad2\">DHCP</label></span> \
                                                    ");
                                            }

                                        printf("</div>  \
                                        </li>   \
                                        <li class=\"cat_li\">   \
                                            <div>   \
                                                <span class=\"cat_li_name\">IP address</span>");

                                        printf("<input type=\"text\" name=\"net_ip\" class=\"cat_li_text\" autocomplete=\"off\" value=\"%s\">", ret.net_ip);

                                        printf("</div>  \
                                        </li>   \
                                        <li class=\"cat_li\">   \
                                            <div>   \
                                                <span class=\"cat_li_name\">Subnet mask</span>");

                                        printf("<input type=\"text\" name=\"net_subnet\" class=\"cat_li_text\" autocomplete=\"off\" value=\"%s\">", ret.net_subnet);
                                        
                                        printf("</div>  \
                                        </li>   \
                                        <li class=\"cat_li\">   \
                                            <div>   \
                                                <span class=\"cat_li_name\">Default gateway</span>");

                                        printf("<input type=\"text\" name=\"net_gateway\" class=\"cat_li_text\" autocomplete=\"off\" value=\"%s\">", ret.net_gateway);
                                        
                                        printf("</div>  \
                                        </li>   \
                                        <li class=\"cat_li\">   \
                                            <div>   \
                                                <span class=\"cat_li_name\">MAC address</span>");

                                        printf("<input type=\"text\" name=\"net_mac\" class=\"cat_li_text\" autocomplete=\"off\" value=\"%s\" readonly>", ret.net_mac);

                                        printf("</div>  \
                                        </li>   \
                                        <li class=\"cat_li\">   \
                                            <div>   \
                                                <span class=\"cat_li_name\">RTSP Port</span>");

                                        printf("<input type=\"text\" name=\"net_rtspport\" class=\"cat_li_text\" autocomplete=\"off\" value=\"%s\">", ret.net_rtsp_port);

                                        printf("</div>  \
                                        </li>   \
                                        <li class=\"cat_li\">   \
                                            <div>   \
                                                <span class=\"cat_li_name\">HTTP Port</span>");

                                        printf("<input type=\"text\" name=\"net_httpport\" class=\"cat_li_text\" autocomplete=\"off\" value=\"%s\">", ret.net_http_port);

                                        printf("</div>  \
                                        </li>   \
                                    </ul>   \
                                </div>  \
                            </div>  \
                        </li>");

                printf("<li class=\"cfg_cat_li\">   \
                            <div>   \
                                <div class=\"cat_name\"><h1>Date & time</h1></div>  \
                                <div class=\"cat_values\">  \
                                    <ul class=\"cat_ul\">   \
                                        <li class=\"cat_li\">   \
                                            <div>   \
                                                <span class=\"cat_li_name\">Date format</span>");

                                                printf("<select name=\"date_format\" class=\"cat_li_select\" id=\"id_dateFormat\">");

                                                if (NULL != strstr(ret.date_format, "dd/mm/yyyy")) 
                                                {
                                                printf("<option selected=\"selected\">dd/mm/yyyy</option>   \
                                                        <option>mm/dd/yyyy</option>    \
                                                        <option>yyyy/mm/dd</option>");
                                                }
                                                else if (NULL != strstr(ret.date_format, "mm/dd/yyyy")) 
                                                {
                                                printf("<option>dd/mm/yyyy</option>   \
                                                        <option selected=\"selected\">mm/dd/yyyy</option> \
                                                        <option>yyyy/mm/dd</option>");
                                                }
                                                else  
                                                {
                                                printf("<option>dd/mm/yyyy</option>   \
                                                        <option>mm/dd/yyyy</option> \
                                                        <option selected=\"selected\">yyyy/mm/dd</option>");
                                                }

                                                printf("</select>");


                                        printf("</div>  \
                                        </li>   \
                                        <li class=\"cat_li\">   \
                                            <div>   \
                                                <span class=\"cat_li_name\">Timezone</span>");
                                        printf("<select name=\"date_timezone\" class=\"cat_li_select\">");
                                        select_timezone(ret.date_timezone);
                                        printf("</select>");

                                        printf("</div>  \
                                        </li>   \
                                        <li class=\"cat_li\">   \
                                            <div>   \
                                                <span class=\"cat_li_name\">Current date</span>");

                                        printf("<input style=\"width:65px;\" type=\"text\" name=\"date_current_1\" class=\"cat_li_text\" autocomplete=\"off\" value=\"%s\">", ret.date_current_1);
                                        printf("<input style=\"width:65px;\" type=\"text\" name=\"date_current_2\" class=\"cat_li_text\" autocomplete=\"off\" value=\"%s\">", ret.date_current_2);
                                        printf("<input style=\"width:65px;\" type=\"text\" name=\"date_current_3\" class=\"cat_li_text\" autocomplete=\"off\" value=\"%s\">", ret.date_current_3);

                                        printf("</div>  \
                                        </li>   \
                                        <li class=\"cat_li\">   \
                                            <div>   \
                                                <span class=\"cat_li_name\">Current time</span>");

                                        printf("<input type=\"time\" id=\"id_curTime\" name=\"date_time\" class=\"cat_li_text\" step=\"any\" value=\"%s\">", ret.date_time);

                                        printf("</div>  \
                                        </li>   \
                                    </ul>   \
                                </div>  \
                            </div>  \
                        </li>");

                printf("<li class=\"cfg_cat_li\">   \
                            <div>   \
                                <div class=\"cat_name\"><h1>User</h1></div> \
                                <div class=\"cat_values\">  \
                                    <ul class=\"cat_ul\">   \
                                        <li class=\"cat_li\">   \
                                            <div>   \
                                                <span class=\"cat_li_name\">Username</span>");

                                        printf("<input type=\"text\" name=\"user_name\" class=\"cat_li_text\" autocomplete=\"off\" value=\"%s\">", ret.username);

                                        printf("</div>  \
                                        </li>   \
                                        <li class=\"cat_li\">   \
                                            <div>   \
                                                <span class=\"cat_li_name\">Password</span>");

                                        printf("<input id=\"id_passWord\" type=\"text\" name=\"user_pw\" class=\"cat_li_text\" autocomplete=\"off\" value=\"%s\">", ret.password);

                                        printf("</div>  \
                                        </li>   \
                                    </ul>   \
                                </div>  \
                            </div>  \
                        </li>");

                printf("<li class=\"cfg_cat_li\">   \
                            <div>   \
                                <div class=\"cat_name\"><h1>About</h1></div>    \
                                <div class=\"cat_li_about\"><p>ZB Camera v1.0<br>Contact: 14520437@gm.uit.edu.vn</p></div>  \
                            </div>  \
                        </li>   \
                        <li class=\"cfg_cat_li\">   \
                            <div style=\"color:red;text-align:center;\" id=\"error_log\"></div> \
                            <div style=\"margin-top:20px;margin-bottom:30px;\"> \
                                <input class=\"cat_btn cat_save\" type=\"submit\" name=\"action_submit\" value=\"Save\" onclick=\"return doSave()\"> \
                                <input class=\"cat_btn cat_cancel\" type=\"submit\" name=\"action_submit\" value=\"Cancel\" onclick=\"return doCancel()\"> \
                                <a href=\"%s\"><input class=\"cat_btn cat_logout\" type=\"button\" name=\"action_logout\" value=\"Logout\" onclick=\"return doLogout()\"></a> \
                            </div>  \
                        </li>", LOGIN_FILENAME);

            printf("</ul>   \
                    </form> \
                </div>  \
            </div>  \
            <div id=\"main-bottom\">    \
                <div class=\"bottom_line\"> \
                        <h5 style=\"text-align:center;color:white\">Chung Vinh Kien - 14520437@gm.uit.edu.vn</h5>   \
                </div>  \
                <div id=\"bottomx\"></div>  \
            </div>  \
        </div>");
    }

    {
        printf("<script>    \
        var preFormat, curFormat;   \
        document.getElementById(\"rad1\").addEventListener(\"change\", function () {    \
            document.forms[\"CONFIG_FORM\"][\"net_ip\"].readOnly = false;   \
            document.forms[\"CONFIG_FORM\"][\"net_subnet\"].readOnly = false;   \
            document.forms[\"CONFIG_FORM\"][\"net_gateway\"].readOnly = false;  \
        }); \
        document.getElementById(\"rad2\").addEventListener(\"change\", function () {    \
            document.forms[\"CONFIG_FORM\"][\"net_ip\"].readOnly = true;    \
            document.forms[\"CONFIG_FORM\"][\"net_subnet\"].readOnly = true;    \
            document.forms[\"CONFIG_FORM\"][\"net_gateway\"].readOnly = true;   \
        }); \
        document.getElementById(\"id_dateFormat\").addEventListener(\"focus\", function () {    \
            preFormat = this.value; \
        }); \
        document.getElementById(\"id_dateFormat\").addEventListener(\"change\", function () {   \
            curFormat = this.value; \
            changeDateFormat(preFormat, curFormat); \
            preFormat = this.value; \
        }); \
        document.getElementById(\"id_curTime\").addEventListener(\"focus\", function () {   \
            clearTimeout(secTimeInc);   \
        }); \
        initDate(); \
        setTimeout(updateDate, 1000);   \
        </script>");
    }

    return ret;
}

// int main ()
// {
//     svconfig_t main_conf;

//     memset(&main_conf, 0, sizeof(main_conf));

//     memcpy(main_conf.username, "chungkien", CONFIG_MAXBUF);
//     memcpy(main_conf.password, "abc", CONFIG_MAXBUF);
//     memcpy(main_conf.cam_width, "1280", CONFIG_MAXBUF);
//     memcpy(main_conf.cam_height, "720", CONFIG_MAXBUF);
//     memcpy(main_conf.cam_fps, "15", CONFIG_MAXBUF);
//     memcpy(main_conf.cam_bitrate, "2.5", CONFIG_MAXBUF);
//     memcpy(main_conf.net_is_dhcp, "1", CONFIG_MAXBUF);
//     memcpy(main_conf.net_ip, "192.168.1.12", CONFIG_MAXBUF);
//     memcpy(main_conf.net_subnet, "255.255.255.0", CONFIG_MAXBUF);
//     memcpy(main_conf.net_gateway, "192.168.1.255", CONFIG_MAXBUF);
//     memcpy(main_conf.net_mac, "kjfla92501", CONFIG_MAXBUF);
//     memcpy(main_conf.net_rtsp_port, "8555", CONFIG_MAXBUF);
//     memcpy(main_conf.net_http_port, "8080", CONFIG_MAXBUF);
//     memcpy(main_conf.streampath, "/main", CONFIG_MAXBUF);
//     memcpy(main_conf.date_format, "dd/mm/yy", CONFIG_MAXBUF);
//     memcpy(main_conf.date_timezone, "+7", CONFIG_MAXBUF);
//     memcpy(main_conf.date_current, "26/12/2018", CONFIG_MAXBUF);
//     memcpy(main_conf.date_time, "10:15:55", CONFIG_MAXBUF);

//     save_setting(main_conf, CONFIG_FILENAME);

//     return 0;
// }

/* Private function bodies -----------------------------------------------------------------------*/

static void
select_timezone (char * selected)
{
    int temp = 24; // +7
    int i = 0;

    for (i = 0; i < 31; i++)
    {
        temp = atoi(selected);

        if (temp == i)
            printf("<option value=\"%d\" selected=\"selected\">%s</option>", i, g_tz_list[i]);
        else
            printf("<option value=\"%d\">%s</option>", i, g_tz_list[i]);
    }

    return ;
}

static void
resolution_to_wh (char * resolution, int res_len, char * width, char * height)
{
    int i, j;

    for (i = 0; i < res_len; i++)
    {
        if (resolution[i] == 'x')
            break;
        if ('0' <= resolution[i] && '9' >= resolution[i])
            width[i] = resolution[i];
    }
    
    i++;

    for (j = 0; j < res_len; j++)
    {
        if ('0' <= resolution[i] && '9' >= resolution[i])
            height[j] = resolution[i];
        else
            break;
        i++;
    }
}

static void
get_number_only (char * str, int str_len, char * value)
{
    int i;

    for (i = 0; i < str_len; i++)
    {
        if (('0' <= str[i] && '9' >= str[i]) || '.' == str[i])
            value[i] = str[i];
        else
            break;
    }
}

static void
replace_config_value (char * replace_src, int src_len, char * replace_str, int replace_len)
{
    memset(replace_src, 0, src_len);
    memcpy(replace_src, replace_str, replace_len);

    replace_src[replace_len] = '\n';
    replace_src[replace_len + 1] = '\0';
}

static int
save_setting (svconfig_t config, char * filename)
{
    FILE * file;
    FILE * tmp_file;

    char line[100] = {0};
    char newline[100] = {0};
    int  i = 0;

    file = fopen(filename, "r");
    tmp_file = fopen("replace.conf", "w");

    if (file == NULL || tmp_file == NULL)
    {
        return -1;
    }

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char * cnote = strstr(line, CONFIG_NOTE);
        /* ignore NOTE symbol */
        if (cnote == NULL)
        {
            char * cfline = strstr(line, CONFIG_DELIM);
            /* parse */
            if (cfline != NULL)
            {
                cfline = cfline + strlen(CONFIG_DELIM);

                int replace_length = strlen(cfline);

                switch (i)
                {
                    case 0:
                        replace_config_value(cfline, replace_length, config.username, strlen(config.username));
                    break;

                    case 1:
                        replace_config_value(cfline, replace_length, config.password, strlen(config.password));
                    break;

                    case 2:
                        replace_config_value(cfline, replace_length, config.cam_width, strlen(config.cam_width));
                    break;

                    case 3:
                        replace_config_value(cfline, replace_length, config.cam_height, strlen(config.cam_height));
                    break;

                    case 4:
                        replace_config_value(cfline, replace_length, config.cam_fps, strlen(config.cam_fps));
                    break;

                    case 5:
                        replace_config_value(cfline, replace_length, config.cam_bitrate, strlen(config.cam_bitrate));
                    break;

                    case 6:
                        replace_config_value(cfline, replace_length, config.net_is_dhcp, strlen(config.net_is_dhcp));
                    break;

                    case 7:
                        replace_config_value(cfline, replace_length, config.net_ip, strlen(config.net_ip));
                    break;

                    case 8:
                        replace_config_value(cfline, replace_length, config.net_subnet, strlen(config.net_subnet));
                    break;

                    case 9:
                        replace_config_value(cfline, replace_length, config.net_gateway, strlen(config.net_gateway));
                    break;

                    case 10:
                        replace_config_value(cfline, replace_length, config.net_mac, strlen(config.net_mac));
                    break;

                    case 11:
                        replace_config_value(cfline, replace_length, config.net_rtsp_port, strlen(config.net_rtsp_port));
                    break;

                    case 12:
                        replace_config_value(cfline, replace_length, config.net_http_port, strlen(config.net_http_port));
                    break;

                    case 13:
                        replace_config_value(cfline, replace_length, config.streampath, strlen(config.streampath));
                    break;

                    case 14:
                        replace_config_value(cfline, replace_length, config.date_format, strlen(config.date_format));
                    break;

                    case 15:
                        replace_config_value(cfline, replace_length, config.date_timezone, strlen(config.date_timezone));
                    break;

                    case 16:
                        replace_config_value(cfline, replace_length, config.date_current_1, strlen(config.date_current_1));
                    break;

                    case 17:
                        replace_config_value(cfline, replace_length, config.date_current_2, strlen(config.date_current_2));
                    break;

                    case 18:
                        replace_config_value(cfline, replace_length, config.date_current_3, strlen(config.date_current_3));
                    break;

                    case 19:
                        replace_config_value(cfline, replace_length, config.date_time, strlen(config.date_time));
                    break;

                    default:
                    break;
                }

                i++;
            }
        }

        //printf("%s\n", line);

        fputs(line, tmp_file);
    }

    fclose(file);
    fclose(tmp_file);

    remove(filename);
    rename("replace.conf", filename);

    return 0;
}

static int
load_setting (svconfig_t * p_config, char * filename)
{
    FILE * file = fopen(filename, "r");

    if (file == NULL)
        return -1;

    char line[100];
    int i = 0;
    /* loop getting each line in file */
    while (NULL != fgets(line, sizeof(line), file))
    {
        char * cnote = strstr(line, CONFIG_NOTE);
        /* ignore NOTE symbol */
        if (cnote == NULL)
        {
            char * cfline = strstr(line, CONFIG_DELIM);
            /* parse */
            if (cfline != NULL)
            {
                cfline = cfline + strlen(CONFIG_DELIM);

                int copy_length = strlen(cfline) - 1;

                switch (i)
                {
                    case 0:
                        memcpy(p_config->username, cfline, copy_length);
                    break;

                    case 1:
                        memcpy(p_config->password, cfline, copy_length);
                    break;

                    case 2:
                        memcpy(p_config->cam_width, cfline, copy_length);
                    break;

                    case 3:
                        memcpy(p_config->cam_height, cfline, copy_length);
                    break;

                    case 4:
                        memcpy(p_config->cam_fps, cfline, copy_length);
                    break;

                    case 5:
                        memcpy(p_config->cam_bitrate, cfline, copy_length);
                    break;

                    case 6:
                        memcpy(p_config->net_is_dhcp, cfline, copy_length);
                    break;

                    case 7:
                        memcpy(p_config->net_ip, cfline, copy_length);
                    break;

                    case 8:
                        memcpy(p_config->net_subnet, cfline, copy_length);
                    break;

                    case 9:
                        memcpy(p_config->net_gateway, cfline, copy_length);
                    break;

                    case 10:
                        memcpy(p_config->net_mac, cfline, copy_length);
                    break;

                    case 11:
                        memcpy(p_config->net_rtsp_port, cfline, copy_length);
                    break;

                    case 12:
                        memcpy(p_config->net_http_port, cfline, copy_length);
                    break;

                    case 13:
                        memcpy(p_config->streampath, cfline, copy_length);
                    break;

                    case 14:
                        memcpy(p_config->date_format, cfline, copy_length);
                    break;

                    case 15:
                        memcpy(p_config->date_timezone, cfline, copy_length);
                    break;

                    case 16:
                        memcpy(p_config->date_current_1, cfline, copy_length);
                    break;

                    case 17:
                        memcpy(p_config->date_current_2, cfline, copy_length);
                    break;

                    case 18:
                        memcpy(p_config->date_current_3, cfline, copy_length);
                    break;

                    case 19:
                        memcpy(p_config->date_time, cfline, copy_length);
                    break;

                    default:
                    break;
                }

                i = i + 1;
            }
        }
    }

    fclose(file); 

    return 0;
}

/* END OF FILE ************************************************************************************/
