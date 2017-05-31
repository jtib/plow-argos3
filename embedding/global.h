#include "environment.h"
#include "sockets.h"

extern Environment env;
extern Sockets soc;
extern std::map<std::string, int> fb_to_ids;
extern std::map<int, std::string> ids_to_fb;

void init_global();
