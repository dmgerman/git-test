#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "cache.h"
#include "remote.h"

struct transport {
	struct remote *remote;
	const char *url;
	void *data;
	struct ref *remote_refs;

	/**
	 * Returns 0 if successful, positive if the option is not
	 * recognized or is inapplicable, and negative if the option
	 * is applicable but the value is invalid.
	 **/
	int (*set_option)(struct transport *connection, const char *name,
			  const char *value);

	struct ref *(*get_refs_list)(const struct transport *transport);
	int (*fetch)(struct transport *transport, int refs_nr, struct ref **refs);
	int (*push)(struct transport *connection, int refspec_nr, const char **refspec, int flags);

	int (*disconnect)(struct transport *connection);
	char *pack_lockfile;
	signed verbose : 2;
};

#define TRANSPORT_PUSH_ALL 1
#define TRANSPORT_PUSH_FORCE 2
#define TRANSPORT_PUSH_DRY_RUN 4
#define TRANSPORT_PUSH_VERBOSE 8

/* Returns a transport suitable for the url */
struct transport *transport_get(struct remote *, const char *);

/* Transport options which apply to git:// and scp-style URLs */

/* The program to use on the remote side to send a pack */
#define TRANS_OPT_UPLOADPACK "uploadpack"

/* The program to use on the remote side to receive a pack */
#define TRANS_OPT_RECEIVEPACK "receivepack"

/* Transfer the data as a thin pack if not null */
#define TRANS_OPT_THIN "thin"

/* Keep the pack that was transferred if not null */
#define TRANS_OPT_KEEP "keep"

/* Limit the depth of the fetch if not null */
#define TRANS_OPT_DEPTH "depth"

/**
 * Returns 0 if the option was used, non-zero otherwise. Prints a
 * message to stderr if the option is not used.
 **/
int transport_set_option(struct transport *transport, const char *name,
			 const char *value);

int transport_push(struct transport *connection,
		   int refspec_nr, const char **refspec, int flags);

struct ref *transport_get_remote_refs(struct transport *transport);

int transport_fetch_refs(struct transport *transport, struct ref *refs);
void transport_unlock_pack(struct transport *transport);
int transport_disconnect(struct transport *transport);

#endif
