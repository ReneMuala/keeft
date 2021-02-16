/*  KEEFT - TCP/IP FILE TRANSFER TOOL
 *  © Landia (Rene Muala)
 *  
 *  Usage: 
 * 
 *  See HowToUse.md
 *
 */

#include <iostream>
#include "net.hpp"
#include "config.hpp"
#include "io.hpp"

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
    opt_print_config;

} // namespace keeft

using namespace keeft;

int main(int argc, char **argv) {
   
    if(argc < 2)
        keeft::perror("Invalid sintax, see HowToUse.md");
    
    init();
    
    set_defaults();
    
    parse_args(argc, argv);
    
    if(on_list_mode) list_machine_addresses(opt_list_IPv4, opt_list_IPv6);
    
    if(opt_print_config) print_config();
    
    if(on_receiver_mode){
        configure_server(param_port);
        if(wait_for_client()){
            if(verify_password(param_key)){
                get_file_specs(param_filename, param_filesize);  
                if((current_file = fopen(param_filename, "w"))){
                    if(keeft::receive_file(current_file, param_filesize))
                        std::cout << "file: " << param_filename << " (" << param_filesize << "bytes) received" << std::endl;
                }
            } else keeft::perror("Wrong password from sender");
        }
    } else {
        if((current_file = fopen(param_filename, "r"))){
            ignore_path_in_filename(param_filename);
            param_filesize = get_file_size(current_file);
            std::cout << "filename: " << param_filename << "\tsize: " << param_filesize;
            if(configure_client(param_IPv4, param_port)){
                if(connect_to_server()){
                    if(send_password(param_key)){
                        send_file_specs(param_filename, param_filesize);
                        send_file(current_file);
                    } else keeft::perror("Wrong password"); 
                }
            }
        }
    }
    
    end();
   
    return 0;
}
