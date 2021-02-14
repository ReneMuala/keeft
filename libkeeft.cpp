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

#include "libkeeft.hpp"

int 
    main_sock,
    file_sock;
    
hostent * 
    temp_sock;

sockaddr_in 
    server_addr;
    

int create_stream_tcpip_socket()
{
    return socket(AF_INET, SOCK_STREAM, 0); 
}

void configure_sock_addr(sockaddr_in & addr , int port)
{
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
}

void lan::display_error(const char * message)
{
    fprintf(stderr, "Error: %s", message);
    exit(1);
}

bool lan::init_cli_keeft(const char *server_IPv4, int port)
{
    return true;
}

bool lan::init_ser_keeft(int port)
{
    if(!(main_sock = create_stream_tcpip_socket()))
        display_error("unanble to create main_sock at init_ser_keeft");
    
    configure_sock_addr(server_addr, port);
    
    if(bind(main_sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        display_error("unable to bind main_sock in init_ser_keeft (try another port)");
    return true;
}

std::string lan::get_current_name(size_t length){
    std::string name;
    char buffer [length];
    gethostname(buffer, length);
    name = buffer; 
    return name;
}

std::vector<std::string> lan::get_machine_IPv4_addrs()
{
    std::vector<std::string> IPv4_addrs;
    char IPv4[INET_ADDRSTRLEN];
    in_addr * temp_addr;
    ifaddrs * all, * ifa;
    getifaddrs(&all);
    for(ifa = all ; ifa ; ifa = ifa->ifa_next){
        if(!ifa->ifa_addr) continue;
        if(ifa->ifa_addr->sa_family == AF_INET){
            temp_addr = &((sockaddr_in*)ifa->ifa_addr)->sin_addr;
            inet_ntop(AF_INET, temp_addr, IPv4, INET_ADDRSTRLEN);
            IPv4_addrs.resize(IPv4_addrs.size()+1);
            IPv4_addrs.at(IPv4_addrs.size()-1) = IPv4;
        }
    } freeifaddrs(all);
    return IPv4_addrs;
}

std::vector<std::string> lan::get_machine_IPv6_addrs()
{
    std::vector<std::string> IPv6_addrs;
    char IPv6[INET6_ADDRSTRLEN];
    in6_addr * temp_addr;
    ifaddrs * all, * ifa;
    getifaddrs(&all);
    for(ifa = all ; ifa ; ifa = ifa->ifa_next){
        if(!ifa->ifa_addr) continue;
        if(ifa->ifa_addr->sa_family == AF_INET6){
            temp_addr = &((sockaddr_in6*)ifa->ifa_addr)->sin6_addr;
            inet_ntop(AF_INET6, temp_addr, IPv6, INET6_ADDRSTRLEN);
            IPv6_addrs.resize(IPv6_addrs.size()+1);
            IPv6_addrs.at(IPv6_addrs.size()-1) = IPv6;
        }
    } freeifaddrs(all);
    return IPv6_addrs;
}


bool lan::wait_for_cli()
{
    if(listen(main_sock, 5) < 0)
        display_error("unable to listen main_sock at wait_for_cli");
    return true;
}




