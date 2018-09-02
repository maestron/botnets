void HttpServerMain(struct darkness_d *darkness);

struct sendfile_d {
       int remote_addr;
       char fname[0x40];
};
