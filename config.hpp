/*  KEEFT - TCP/IP FILE TRANSFER TOOL
 *  © Landia (Rene Muala)
 *
 */

#pragma once
#include "net.hpp"

namespace keeft {
    static const char version [] = {"0.1.1"};
    void set_default_key();
    void set_default_port();
    void set_default_address();
    void set_default_buff_size();
    void set_defaults();
    void configure_sock_addr(sockaddr_in & addr , int port);
    bool configure_server(int);
    bool configure_client(const char * , int);
}
