#ifndef DIR_H
#define DIR_H

/*
 * We maintain three exclude pattern lists:
 * EXC_CMDL lists patterns explicitly given on the command line.
 * EXC_DIRS lists patterns obtained from per-directory ignore files.
 * EXC_FILE lists patterns from fallback ignore files.
 */
#define EXC_CMDL 0
#define EXC_DIRS 1
#define EXC_FILE 2


struct dir_entry {
	int len;
	char name[FLEX_ARRAY]; /* more */
};

struct exclude_list {
	int nr;
	int alloc;
	struct exclude {
		const char *pattern;
		const char *base;
		int baselen;
	} **excludes;
};

struct dir_struct {
	int nr, alloc;
	unsigned int show_ignored:1,
		     show_other_directories:1,
		     hide_empty_directories:1;
	struct dir_entry **entries;

	/* Exclude info */
	const char *exclude_per_dir;
	struct exclude_list exclude_list[3];
};

extern int common_prefix(const char **pathspec);
extern int match_pathspec(const char **pathspec, const char *name, int namelen, int prefix, char *seen);

extern int read_directory(struct dir_struct *, const char *path, const char *base, int baselen);
extern int excluded(struct dir_struct *, const char *);
extern void add_excludes_from_file(struct dir_struct *, const char *fname);
extern void add_exclude(const char *string, const char *base,
			int baselen, struct exclude_list *which);
extern int file_exists(const char *);

#endif
