/*  KEEFT - TCP/IP FILE TRANSFER TOOL
 *  © Landia (Rene Muala)
 *
 */

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
    
extern size_t 
    param_buffsize;
    
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
    opt_get_key         (false),
    opt_get_buffsize    (false),
    opt_print_help      (false),
    opt_print_ver       (false),
    opt_print_config    (false);

std::unordered_map<std::string, std::string> command_options;
    
void reset_get_opts(){
    opt_get_IPv4 =
    opt_get_IPv6 =
    opt_get_filename =
    opt_get_key  = 
    opt_get_port = false;
}

void log(const char* message)
{
    printf("[log]:\t%s", message);
}

bool handle_opt(in_option option){
    switch(option){
        case _H: opt_print_help = true; break;
        case _V: opt_print_ver  = true; break;
        case _R: on_receiver_mode = true; break;
        case _B: opt_get_buffsize = true; return true;
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
        default: keeft::perror("Invalid sintax (_NULL in_option), see keeft -H");
    } return false;
}
  
in_option convert_str_to_option(const char * str){
    if (str[1] == 'H') return _H;
    else if (str[1] == 'V') return _V;
    else if (str[1] == 'B') return _B;
    else if (str[1] == 'R') return _R;
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
    else if (opt_get_buffsize) param_buffsize  = atoll(value);
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
    print_version();
    std::cout 
    << "*\tmode: " << ((on_receiver_mode) ? "on_receiver_mode" : "on_sender_mode") << std::endl 
    << "*\tfilename: " << param_filename << std::endl
    << "*\tbuffsize: " << param_buffsize << std::endl 
    << "*\tIPv4: " << param_IPv4 << std::endl 
    << "*\tIPv6: " << param_IPv6 << "(unused)" << std::endl
    << "*\tKey: " << param_key << std::endl;
}

void print_addresses(std::vector<std::string> addresses, const char * type){
    for(auto addr : addresses)
        std::cout << "(" << type << "): " << addr << std::endl;
}

void list_machine_addresses(bool print_v4s, bool print_v6s) {
    std::vector<std::string> addresses;
    if(print_v4s) print_addresses(get_machine_IPv4_addrs(), "IPv4");
    if(print_v6s) print_addresses(get_machine_IPv6_addrs(), "IPv6");
}

void print_progress(double done, double total){
    char str [10];
    static int last_pos = 0;
    int current_pos = (done/total)*100;
    if(current_pos > last_pos){
        sprintf(str,"%3d%% ", current_pos);
            printf("\r%10s", str);
            setbuf(stdout, NULL);
        last_pos = current_pos;
    }
}

void print_version() {
    std::cout << "Landia::Keeft " << version << std::endl; 
}


void load_command_options() {
    command_options["-H"]="Prints this glossary.";
    command_options["-R"]="Enables receiver mode.";
    command_options["-S <File>"] = "Enables sender mode, indicating the file to be sent.";
    command_options["--IPv4 <Address>"] = "[param for  -S] Specifies the IPv4 address of the receiver.";
    command_options["--IPv6 <Address>"] = "[param for  -S] Specifies the IPv6 address of the receiver.";
    command_options["-L"]="Lists all avaliable addresses.";
    command_options["--only-IPv4"]="[param for  -L] List only IPv4 addresses.";
    command_options["--only-IPv6"]="[param for  -L] List only IPv6 addresses.";
    command_options["-P <Port>"]="Specifies the port to be used.";
    command_options["-K <Password>"]="Specifies a Password.";
    command_options["-B <Size-in-bytes>"]="Sets the buffer size.";
    command_options["-C"]="Prints the current keeft config.";
}

void print_command_options() {
     for(auto option : command_options){
         std::cout << option.first << "\t: " << option.second << std::endl;
    }
}

}
