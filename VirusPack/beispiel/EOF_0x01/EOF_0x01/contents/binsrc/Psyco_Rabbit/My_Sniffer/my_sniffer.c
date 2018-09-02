/***************************************************************************
 *   Copyright (C) 14/09/2006 by Psyco_Rabbit                              *
 *   PsycoRabbit@gmail.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the Berkeley Software Distribution (BSD)        *
 *   license.                                                              *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY.                                             *
 *                                                                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <time.h>

#define MAX_LEN 1024*8            //packet's lenght


void print_tcp_ip(struct iphdr * ip_,struct tcphdr * tcp_,char *buffer_){

struct sockaddr_in addr;


        printf("-- IP HEADER --\n");
        printf("Header lenght: %d bytes\n",ip_->ihl*4);	
        printf("Version: %d\n",ip_->version);
        printf("Priorità: %d\n",ip_->tos);
        printf("Packet lenght: %d bytes\n",ntohs(ip_->tot_len));
        printf("ID: %d\n",ntohs(ip_->id));
        printf("Offset: %d\n",ip_->frag_off);
        printf("Time to live: %d\n",ip_->ttl);
        printf("Protocol: %d\n",ip_->protocol);
        printf("Checksum: %d\n",ip_->check);
        addr.sin_addr.s_addr=ip_->saddr;
        printf("Source address: %s\n",inet_ntoa(addr.sin_addr));
        addr.sin_addr.s_addr=ip_->daddr;
        printf("Destination address: %s\n",inet_ntoa(addr.sin_addr));


        printf("\n");
        printf("-- TCP HEADER --\n");
        printf("Source port: %d\n",ntohs(tcp_->source));
        printf("Destination port: %d\n",ntohs(tcp_->dest));
        printf("Sequence number: %u\n",ntohl(tcp_->seq));
        printf("ACK sequence: %u\n",ntohl(tcp_->ack_seq));
        printf("Header TCP lenght: %d bytes\n", tcp_->doff*4);
        printf("Flag FIN: %d\n",tcp_->fin);
        printf("Flag SYN: %d\n",tcp_->syn);
        printf("Flag RST: %d\n",tcp_->rst);
        printf("Flag PSH: %d\n",tcp_->psh);
        printf("Flag ACK: %d\n",tcp_->ack);
        printf("Flag URG: %d\n",tcp_->urg);
        printf("Window TCP: %d\n",ntohs(tcp_->window));
        printf("Checksum: %d\n",tcp_->check);
        printf("Urgent pointer: %d\n",tcp_->urg_ptr);

        printf("**********************************************\n");

memset(buffer_,0,MAX_LEN);
}

void print_udp(struct udphdr * udp_,char *buffer_){

        printf("-- UDP HEADER --\n");
        printf("Source port: %d\n",ntohs(udp_->source));
        printf("Destination port: %d\n",ntohs(udp_->dest));
        printf("Header UDP lenght: %d bytes\n", udp_->len);
        printf("Checksum: %d\n",udp_->check);

        printf("**********************************************\n");

memset(buffer_,0,MAX_LEN);
}


void help(){
        printf("COMMAND LIST\n");
        printf("tcp       :    print tcp traffic\n");
        printf("udp       :    print udp traffic\n");
        printf("-A        :    print tcp or udp traffic on ALL ports\n");
        printf("'port'    :    print tcp or udp traffic on 'port'\n\n");
        printf("To run program type 'program name' 'protocol' 'port'\n");
}

void title(){
        printf("SNIFFER v1.2 by Psyco_Rabbit\n");
        printf("E-mail: PsycoRabbit@gmail.com\n\n");
}


int main(int argc,char *argv[]){
        struct iphdr *ip;	
        struct tcphdr *tcp;	
        struct udphdr *udp;

        int sock;
        char *buffer;           //packets buffer

        title();

        if(argc<2){
           printf("Type --help for basic commands!\n");
           exit(-1);
          }

        if ((buffer=malloc(MAX_LEN))==NULL){
           perror("Memory exhausted!");
          }

        memset(buffer,0,MAX_LEN);


        if ((strcmp(argv[1],"--help"))==0){
           help();
          }

        if ((strcmp(argv[1],"tcp"))!=0 && (strcmp(argv[1],"udp"))!=0){
           printf("Type tcp or udp to specify protocol!\n");
           printf("TYpe --help for basic commands!\n");
           exit(-1);
          }

        if ((strcmp(argv[1],"tcp"))==0){

          if ((sock=socket(AF_INET,SOCK_RAW,IPPROTO_TCP))==-1)         //RAW socket
             perror("Socket_TCP() Error!");
          if(strcmp(argv[2],"-A")==0){

             while(read(sock,buffer,MAX_LEN)!=-1){

                ip=(struct iphdr *)buffer;                            //header IP=begin buffer
                tcp=(struct tcphdr *)(buffer+ip->ihl*4);              //header TCP=buffer+size header IP
                print_tcp_ip(ip,tcp,buffer);
                sleep(3);

               }
            }
          else

           while(read(sock,buffer,MAX_LEN)!=-1){

               ip=(struct iphdr *)buffer;
               tcp=(struct tcphdr *)(buffer+ip->ihl*4);
               if(tcp->source==htons(atoi(argv[2])))
                  print_tcp_ip(ip,tcp,buffer);
               sleep(3);

              }
          }
        if ((strcmp(argv[1],"udp"))==0){

          if ((sock=socket(AF_INET,SOCK_RAW,IPPROTO_UDP))==-1)         //RAW socket
             perror("Socket_UDP() Error!");
          if(strcmp(argv[2],"-A")==0){

             while(read(sock,buffer,MAX_LEN)!=-1){

                udp=(struct udphdr *)buffer;                          //header UDP=begin buffer
                print_udp(udp,buffer);
                sleep(3);

               }
            }
          else

           while(read(sock,buffer,MAX_LEN)!=-1){

               udp=(struct udphdr *)buffer;
               if(udp->source==htons(atoi(argv[2])))
                  print_udp(udp,buffer);
               sleep(3);

              }
          }
        close(sock);
        return 0;
}
