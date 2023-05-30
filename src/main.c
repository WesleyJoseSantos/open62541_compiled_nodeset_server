/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <signal.h>
#include <stdio.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>
#include <namespace_example_generated.h>

UA_Boolean running = true;
void signalHandler(int sig) {
    running = false;
}

int main(int argc, char** argv)
{
    signal(SIGINT, signalHandler); /* catch ctrl-c */

    /* Create a server listening on port 4840 */
    UA_Server *server = UA_Server_new();
    UA_ServerConfig *config = UA_Server_getConfig(server);
    UA_ServerConfig_setDefault(config);

    UA_StatusCode retval = namespace_example_generated(server);

    if(retval != UA_STATUSCODE_GOOD) {
        UA_LOG_ERROR(&config->logger, UA_LOGCATEGORY_SERVER, "Could not add the example nodeset. "
            "Check previous output for any error.");
        retval = UA_STATUSCODE_BADUNEXPECTEDERROR;
    } else {
        retval = UA_Server_run(server, &running);
    }

    UA_Server_delete(server);
    return retval;
}
