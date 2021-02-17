/*  KEEFT - TCP/IP FILE TRANSFER TOOL
 *  © Landia (Rene Muala)
 *
 */

#pragma once

#include <iostream>
#include <cstring>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ifaddrs.h>

#define keeft_key_len 515
#define keeft_filename_len 2048

namespace keeft {
    int create_stream_tcpip_socket();
    void perror(const char *);
    bool init();
    /* server */
    bool wait_for_client();
    bool verify_password(const char *);
    bool get_file_specs(char *, size_t &);
    bool receive_file(FILE *, size_t, size_t);
    ;; void ignore_path_in_filename(char *);
    ;; size_t get_file_size(FILE*, size_t);
    /* client */
    bool connect_to_server();
    bool send_password(const char *);
    bool send_file_specs(const char *, size_t);
    bool send_file(FILE *, size_t, size_t);
    ;;
    bool end();
    std::vector<std::string> get_machine_IPv4_addrs();
    std::vector<std::string> get_machine_IPv6_addrs();
    std::string get_current_name(size_t = 1024);
    int get_current_port();
    /* receive */
    namespace receive
    {
        void receive();
        void wait();
        void verify();
        void receive_file();   
    }
    namespace send 
    {
        void send();
        void open_file();
        void configure();
        void connect();
        void send_password();
        void send_file();
    }
    /* send */
};
