#ifndef SUBMODULE_CONFIG_CACHE_H
#define SUBMODULE_CONFIG_CACHE_H

#include "hashmap.h"
#include "strbuf.h"

/*
 * Submodule entry containing the information about a certain submodule
 * in a certain revision.
 */
struct submodule {
	const char *path;
	const char *name;
	const char *url;
	int fetch_recurse;
	const char *ignore;
	/* the sha1 blob id of the responsible .gitmodules file */
	unsigned char gitmodules_sha1[20];
};

const struct submodule *submodule_from_name(const unsigned char *commit_sha1,
		const char *name);
const struct submodule *submodule_from_path(const unsigned char *commit_sha1,
		const char *path);
void submodule_free(void);

#endif /* SUBMODULE_CONFIG_H */
