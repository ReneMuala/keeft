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

#include <iostream>
#include "libkeeft.hpp"

int main(int argc, char **argv) {
   
    std::cout << "Avaliable IP Addresses: " << std::endl;
    std::cout << lan::get_machine_IPv4_addrs()[1] << std::endl;
    std::cout << lan::get_machine_IPv6_addrs()[1] << std::endl;
    
    return 0;
}
