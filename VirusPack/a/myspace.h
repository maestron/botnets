struct myspace_param_d {
       int bRawData;
       char lpLoginData[0x4E20];
       char lpEditData[0x500];
};

struct myspace_d {
       char request[0x400];
       char url[0x80];
       char username[0x40];
       char password[0x40];
       char editdata[0x200];
       unsigned long stat;
};

void MySpaceMain(struct myspace_param_d *);
