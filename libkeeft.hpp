/*  KEEFT - TCP/IP FILE TRANSFER TOOL
 *  © Landia (Rene Muala)
 *  
 *  Usage: 
 * 
 *  [if sending]
 *  Keeft IP Port FileToSend
 * 
 *  [else if receiving]
 *  Keeft Port
 *
 */

#pragma once

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ifaddrs.h>

namespace lan {
    void display_error(const char *);
    bool init_cli_keeft(const char *, int);
    bool init_ser_keeft(int);
    std::vector<std::string> get_machine_IPv4_addrs();
    std::vector<std::string> get_machine_IPv6_addrs();
    std::string get_current_name(size_t = 1024);
    int get_current_port();
    bool wait_for_cli();
};
