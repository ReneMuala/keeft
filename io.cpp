#include "io.hpp"
#include <sys/types.h>
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
    
size_t 
    param_filesize;
    
FILE *
    current_file;

bool 
    on_receiver_mode(false),
    opt_get_filename(false),
    opt_get_IPv4    (false),
    opt_get_IPv6    (false),
    on_list_mode    (false),
    opt_list_IPv4   (true),
    opt_list_IPv6   (true),
    opt_get_port        (false),
    opt_get_key         (true),
    opt_print_config    (false);

    
    
void reset_get_opts(){
    opt_get_IPv4 =
    opt_get_IPv6 =
    opt_get_filename =
    opt_get_key  = 
    opt_get_port = false;
}

bool handle_opt(in_option option){
    switch(option){
        case _R: on_receiver_mode = true; break;
        case _S: on_receiver_mode = false;
                 opt_get_filename = true; return true;
        case __IPv4: opt_get_IPv4 = true; return true;
        case __IPv6: opt_get_IPv6 = true; return true;
        case _L: on_list_mode = true; break;
        case __only_IPv4: opt_list_IPv6 = false; break;
        case __only_IPv6: opt_list_IPv4 = false; break;
        case _P: opt_get_port = true; return true;
        case _K: opt_get_key = true; return true;
        case _C: opt_print_config = true; break;
        default: keeft::perror("Invalid sintax (_NULL in_option), see HowToUse.mid");
    } return false;
}
  
in_option convert_str_to_option(const char * str){
    if (str[1] == 'R') return _R;
    else if (str[1] == 'S') return _S;
    else if (str[1] == 'L') return _L;
    else if (str[1] == 'P') return _P;
    else if (str[1] == 'K') return _K;
    else if (str[1] == 'C') return _C;
    else if (strcmp(str, "--IPv4") == 0 ) return __IPv4;
    else if (strcmp(str, "--IPv6") == 0) return __IPv6;
    else if (strcmp(str, "--only-IPv4") == 0) return __only_IPv4;
    else if (strcmp(str, "--only-IPv6") == 0) return __only_IPv6;
    else return _NULL;
}

void get_value(const char * value){
    if (opt_get_filename) strcpy(param_filename, value);
    else if (opt_get_IPv4) strcpy(param_IPv4, value);
    else if (opt_get_IPv6) strcpy(param_IPv6, value);
    else if (opt_get_port) param_port = htons(atoi(value));
    else if (opt_get_key)  strcpy(param_key, value);
}

void parse_args(int argc, char **argv){
    char * arg = nullptr;
    in_option option = _NULL;
    bool get_nex_arg_as_opt = true;
    
    for(int i = 1 ; i < argc ; i ++ ){
        arg = argv[i];
        option = convert_str_to_option(arg);
        if(get_nex_arg_as_opt) {
            reset_get_opts();
            get_nex_arg_as_opt =! handle_opt(option);
        } else {
           get_value(arg); 
           get_nex_arg_as_opt = true;
        }
    }
}

void print_config(){
    std::cout << "Landia-keeft (" << keeft::version << ")" << std::endl
    << "*\tmode: " << ((on_receiver_mode) ? "on_receiver_mode" : "on_sender_mode") << std::endl 
    << "*\tfilename: " << param_filename << std::endl
    << "*\tIPv4: " << param_IPv4 << std::endl 
    << "*\tIPv6: " << param_IPv6 << "(unused for connection)" << std::endl
    << "*\tKey: " << param_key << std::endl;
}

void print_addresses(std::vector<std::string> addresses, const char * type){
    for(auto addr : addresses)
        std::cout << "(" << type << "): " << addr << std::endl;
}

void list_machine_addresses(bool print_v4s, bool print_v6s) {
    std::vector<std::string> addresses;
    if(print_v4s)  print_addresses(get_machine_IPv4_addrs(), "IPv4");
    if(print_v6s)  print_addresses(get_machine_IPv6_addrs(), "IPv6");
}

}
