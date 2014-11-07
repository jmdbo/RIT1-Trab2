/*****************************************************************************\
 * Redes Integradas de Telecomunicacoes I
 * MIEEC - FCT/UNL  2014/2015
 *
 * callbacks.h
 *
 * Header file of functions that handle main application logic for UDP communication,
 *    controlling query forwarding
 *
 * Updated on October 20, 16:00
 * @author  Luis Bernardo
\*****************************************************************************/

#include <gtk/gtk.h>
#include <glib.h>

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif


// Program constants
#define CNAME_LENGTH		80		// Maximum filename
#define MSG_BUFFER_SIZE		64000	// Message buffer size
#define QUERY_JITTER		100		/* Jitter time for Query retransmission - 100 mseconds */
#define QUERY_TIMEOUT		10000	/* Query timeout - 10 seconds */


struct Hit;
struct Query;



#ifndef INCL_CALLBACKS_
#define INCL_CALLBACKS_

#include "gui.h"



// typedef enum { ... } QueryState;
// typedef enum { ... } ConnectState;


// Query information
typedef struct Query {
	char name[CNAME_LENGTH];	// Query filename
	int seq;					// Sequence number
	gboolean is_ipv6;			// if TRUE, comes from IPv6, otherwise comes from IPv4.
	struct in6_addr ipv6;
	struct in_addr ipv4;
	u_short port;
	int state;
	/*
	 * 	...
	 * 	Put here everything you need to store about a Query, including the information about
	 * 	the Hit, the server socket, the accepted socket, the connection socket, buffers, etc.
	 */
} Query;



/**********************\
|*  Global variables  *|
\**********************/

extern gboolean active; // TRUE if server is active

// Main window
extern WindowElements *main_window;
/*******************************************************
 * Function to write the qlist
 ******************************************************/
void put_in_qlist(const char* fname, int seq, gboolean is_ipv6, struct in6_addr *ipv6, struct in_addr *ipv4, u_short port);

/*******************************************************\
|* Functions to control the state of the application   *|
\*******************************************************/

// Handle the reception of a Query packet
void handle_Query(char *buf, int buflen, gboolean is_ipv6, struct in6_addr *ipv6, struct in_addr *ipv4, u_short port);
// Handle the reception of an Hit packet
void handle_Hit(char *buf, int buflen, struct in6_addr *ip, u_short port, gboolean is_ipv6);
// Handle the reception of a new connection on a server socket
// Return TRUE if it should accept more connections; FALSE otherwise
gboolean handle_new_connection(int sock, void *ptr, struct sockaddr_in6 *cli_addr);

// Closes everything
void close_all(void);

// Button that starts and stops the application
void on_togglebutton1_toggled(GtkToggleButton *togglebutton, gpointer user_data);

// Callback button 'Stop': stops the selected TCP transmission and associated proxy
void on_buttonStop_clicked(GtkButton *button, gpointer user_data);

// Callback function that handles the end of the closing of the main window
gboolean on_window1_delete_event (GtkWidget * widget,
		GdkEvent * event, gpointer user_data);

#endif