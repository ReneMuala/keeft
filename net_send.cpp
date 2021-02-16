#include "net.hpp"
#include "config.hpp"

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
    
    namespace send
    {
        void send_file(){
            send_file_specs(param_filename, param_filesize);
            keeft::send_file(current_file);
        }
        void send_password(){
            if(keeft::send_password(param_key)){
                send_file();
            } else 
                keeft::perror("Connection failed, wrong param_key (-K)."); 
        }
        
        void connect(){
            if(connect_to_server()){
                send_password();
                } else 
                    keeft::perror("Connection failed, wrong param_IPv4 (--IPv4) or param_port (-P).");
        }
        
        void configure(){
            ignore_path_in_filename(param_filename);
            param_filesize = get_file_size(current_file);
            std::cout << "filename: " << param_filename << "\t (" << param_filesize << "bytes)"<< std::endl;
            if(configure_client(param_IPv4, param_port)){
                connect();
            } else 
                keeft::perror("Configuration failed.");
        }
        
        void open_file(){
            if((current_file = fopen(param_filename, "r"))){
                configure();
            } else 
                keeft::perror("Unable to open file.");
        }
        
        void send(){
            open_file();
        }
    }
}
