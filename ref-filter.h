#ifndef REF_FILTER_H
#define REF_FILTER_H

#include "sha1-array.h"
#include "refs.h"
#include "commit.h"
#include "parse-options.h"

/* Quoting styles */
#define QUOTE_NONE 0
#define QUOTE_SHELL 1
#define QUOTE_PERL 2
#define QUOTE_PYTHON 4
#define QUOTE_TCL 8

struct atom_value {
	const char *s;
	unsigned long ul; /* used for sorting when not FIELD_STR */
};

struct ref_sorting {
	struct ref_sorting *next;
	int atom; /* index into used_atom array (internal) */
	unsigned reverse : 1;
};

struct ref_array_item {
	unsigned char objectname[20];
	int flag;
	const char *symref;
	struct atom_value *value;
	char *refname;
};

struct ref_array {
	int nr, alloc;
	struct ref_array_item **items;
};

struct ref_filter {
	const char **name_patterns;
};

struct ref_filter_cbdata {
	struct ref_array array;
	struct ref_filter filter;
};

/*  Callback function for for_each_*ref(). This filters the refs based on the filters set */
int ref_filter_handler(const char *refname, const struct object_id *oid, int flag, void *cb_data);
/*  Clear all memory allocated to ref_array */
void ref_array_clear(struct ref_array *array);
/*  Parse format string and sort specifiers */
int parse_ref_filter_atom(const char *atom, const char *ep);
/*  Used to verify if the given format is correct and to parse out the used atoms */
int verify_ref_format(const char *format);
/*  Sort the given ref_array as per the ref_sorting provided */
void ref_array_sort(struct ref_sorting *sort, struct ref_array *array);
/*  Print the ref using the given format and quote_style */
void show_ref_array_item(struct ref_array_item *info, const char *format, int quote_style);
/*  Callback function for parsing the sort option */
int parse_opt_ref_sorting(const struct option *opt, const char *arg, int unset);
/*  Default sort option based on refname */
struct ref_sorting *ref_default_sorting(void);

#endif /*  REF_FILTER_H  */