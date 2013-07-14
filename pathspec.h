#ifndef PATHSPEC_H
#define PATHSPEC_H

/* Pathspec magic */
#define PATHSPEC_FROMTOP	(1<<0)
#define PATHSPEC_MAXDEPTH	(1<<1)
#define PATHSPEC_ALL_MAGIC	  \
	(PATHSPEC_FROMTOP	| \
	 PATHSPEC_MAXDEPTH)

#define PATHSPEC_ONESTAR 1	/* the pathspec pattern sastisfies GFNM_ONESTAR */

struct pathspec {
	const char **raw; /* get_pathspec() result, not freed by free_pathspec() */
	int nr;
	unsigned int has_wildcard:1;
	unsigned int recursive:1;
	unsigned magic;
	int max_depth;
	struct pathspec_item {
		const char *match;
		const char *original;
		unsigned magic;
		int len;
		int nowildcard_len;
		int flags;
	} *items;
};

#define GUARD_PATHSPEC(ps, mask) \
	do { \
		if ((ps)->magic & ~(mask))	       \
			die("BUG:%s:%d: unsupported magic %x",	\
			    __FILE__, __LINE__, (ps)->magic & ~(mask)); \
	} while (0)

/* parse_pathspec flags */
#define PATHSPEC_PREFER_CWD (1<<0) /* No args means match cwd */
#define PATHSPEC_PREFER_FULL (1<<1) /* No args means match everything */
#define PATHSPEC_MAXDEPTH_VALID (1<<2) /* max_depth field is valid */
/* strip the trailing slash if the given path is a gitlink */
#define PATHSPEC_STRIP_SUBMODULE_SLASH_CHEAP (1<<3)
/* die if a symlink is part of the given path's directory */
#define PATHSPEC_SYMLINK_LEADING_PATH (1<<4)
/*
 * This is like a combination of ..LEADING_PATH and .._SLASH_CHEAP
 * (but not the same): it strips the trailing slash if the given path
 * is a gitlink but also checks and dies if gitlink is part of the
 * leading path (i.e. the given path goes beyond a submodule). It's
 * safer than _SLASH_CHEAP and also more expensive.
 */
#define PATHSPEC_STRIP_SUBMODULE_SLASH_EXPENSIVE (1<<5)
#define PATHSPEC_PREFIX_ORIGIN (1<<6)
#define PATHSPEC_KEEP_ORDER (1<<7)

extern void parse_pathspec(struct pathspec *pathspec,
			   unsigned magic_mask,
			   unsigned flags,
			   const char *prefix,
			   const char **args);
extern void copy_pathspec(struct pathspec *dst, const struct pathspec *src);
extern void free_pathspec(struct pathspec *);

extern int limit_pathspec_to_literal(void);

extern char *find_pathspecs_matching_against_index(const char **pathspec);
extern void add_pathspec_matches_against_index(const char **pathspec, char *seen, int specs);
extern const char *check_path_for_gitlink(const char *path);
extern void die_if_path_beyond_symlink(const char *path, const char *prefix);

#endif /* PATHSPEC_H */
