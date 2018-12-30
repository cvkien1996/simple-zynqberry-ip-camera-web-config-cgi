/* svconf.h */

#ifndef SVCONF_H
#define SVCONF_H

#define CONFIG_FILENAME    "../camera.conf"
#define CONFIG_MAXBUF      40
#define CONFIG_DELIM       "="
#define CONFIG_NOTE        "#"

#define DEFAULT_STREAM_PATH     "/main"

typedef struct
{
    /* user account */
    /* 0 */     char username[CONFIG_MAXBUF];
    /* 1 */     char password[CONFIG_MAXBUF];

    /* camera config */
    /* 2 */     char cam_width[CONFIG_MAXBUF];      /* cam width */
    /* 3 */     char cam_height[CONFIG_MAXBUF];     /* cam height */
    /* 4 */     char cam_fps[CONFIG_MAXBUF];        /* cam fps */
    /* 5 */     char cam_bitrate[CONFIG_MAXBUF];    /* cam bitrate */

    /* network */
    /* 6 */     char net_is_dhcp[CONFIG_MAXBUF];    /* is dhcp ? */
    /* 7 */     char net_ip[CONFIG_MAXBUF];         /* ip */
    /* 8 */     char net_subnet[CONFIG_MAXBUF];     /* subnet mask */
    /* 9 */     char net_gateway[CONFIG_MAXBUF];    /* gateway */
    /* 10 */    char net_mac[CONFIG_MAXBUF];        /* mac address */
    /* 11 */    char net_rtsp_port[CONFIG_MAXBUF];  /* rtsp port */
    /* 12 */    char net_http_port[CONFIG_MAXBUF];  /* http port */
    /* 13 */    char streampath[CONFIG_MAXBUF];     /* stream path */

    /* date time */
    /* 14 */    char date_format[CONFIG_MAXBUF];    /* date format */
    /* 15 */    char date_timezone[CONFIG_MAXBUF];  /* timezone */
    /* 16 */    char date_current[CONFIG_MAXBUF];   /* current date */
    /* 17 */    char date_time[CONFIG_MAXBUF];      /* current time */
} svconfig_t;

int
svconf_action (char ** vars, char form_method);

int
svconf_save_config (char ** vars, char form_method);

svconfig_t
svconf_load_config ();

#endif /* SVCONF_H */
