struct mxlist_t {
	struct mxlist_t *next;
	int pref;
	char mx[256];
};

struct mxlist_t *get_mx_list(const char *domain);
void free_mx_list(struct mxlist_t *);