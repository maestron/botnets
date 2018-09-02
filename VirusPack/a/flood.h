void HttpFlood(char *, unsigned long);

struct flood_d {
       int activated;
       int count;
       int nextsend;
};

struct flood_d flood;
