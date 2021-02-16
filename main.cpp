/*  KEEFT - TCP/IP FILE TRANSFER TOOL
 *  © Landia (Rene Muala)
 *  
 *  Usage: 
 * 
 *  See HowToUse.md
 *
 */

#include <iostream>
#include "config.hpp"
#include "io.hpp"
#include "net.hpp"


namespace keeft 
{

extern char 
    param_filename  [keeft_filename_len],
    param_IPv4      [INET_ADDRSTRLEN] ,
    param_IPv6      [INET6_ADDRSTRLEN], // currently unsused
    param_key       [keeft_key_len];
    
extern uint16_t
    param_port;
    
extern size_t 
    param_filesize;
    
extern FILE *
    current_file;

extern bool 
    on_receiver_mode,
    opt_get_filename,
    opt_get_IPv4    ,
    opt_get_IPv6    ,
    on_list_mode    ,
    opt_list_IPv4   ,
    opt_list_IPv6   ,
    opt_get_port    ,
    opt_get_key     ,
    opt_print_help  ,
    opt_print_ver   ,
    opt_print_config;
    
} // namespace keeft

using namespace keeft;

int main(int argc, char **argv) {
    
    load_command_options();
    
    if(argc < 2)
        keeft::perror("Invalid sintax, see keeft -H");
    
    init();
    
    set_defaults();
    
    parse_args(argc, argv);
    
    if(on_list_mode)            list_machine_addresses(opt_list_IPv4, opt_list_IPv6);
    else if(opt_print_config)   print_config();
    else if(opt_print_ver)      print_version();
    else if(opt_print_help)     print_command_options();
    else if(on_receiver_mode){
        receive::receive();
    } else {
        send::send();
    } end();
   
    return 0;
}
