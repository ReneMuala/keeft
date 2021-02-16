/*  KEEFT - TCP/IP FILE TRANSFER TOOL
 *  © Landia (Rene Muala)
 *  
 * Usage:
 * See HowToUse.md
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
#define keeft_sock_len 0x50B4

namespace keeft {
    static double version = 0.1;
    int create_stream_tcpip_socket();
    void perror(const char *);
    bool init();
    void log(const char * );
    ;;
    bool wait_for_client();
    bool verify_password(const char *);
    bool get_file_specs(char *, size_t &);
    bool receive_file(FILE *, size_t);
    ;; void ignore_path_in_filename(char *);
    ;; size_t get_file_size(FILE*);
    bool connect_to_server();
    bool send_password(const char *);
    bool send_file_specs(const char *, size_t);
    bool send_file(FILE *);
    ;;
    bool end();
    std::vector<std::string> get_machine_IPv4_addrs();
    std::vector<std::string> get_machine_IPv6_addrs();
    std::string get_current_name(size_t = 1024);
    int get_current_port();
};
