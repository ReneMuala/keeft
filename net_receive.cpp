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
    opt_print_help  ,
    opt_print_ver   ,
    opt_print_config;
    
    namespace receive
    {
        
        void receive_file(){
            get_file_specs(param_filename, param_filesize);  
            if((current_file = fopen(param_filename, "w"))){
                if(keeft::receive_file(current_file, param_filesize))
                    std::cout << "file: " << param_filename << " (" << param_filesize << "bytes) received" << std::endl;
                else 
                    keeft::perror("Unexpected EOF");
            } else 
                    keeft::perror("Unable to open file for writing.");
        }

        void verify(){
            if(verify_password(param_key)){
                receive_file();
                } else 
                    keeft::perror("Wrong password from sender.");
        }

        void wait(){    
            if(wait_for_client()){
                verify();
            } else 
                keeft::perror("Unable to wait_for_client.");
        }

        void receive(){
            if(configure_server(param_port)){
                    wait();
                } else 
                    keeft::perror("Configuration failed, try another port.");
        }
    } // namespace receive
} // namespace keeeft
