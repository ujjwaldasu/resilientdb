#ifndef _LOGGERWRAPPER_H_
#define _LOGGERWRAPPER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>

//#define MSG_CONFIRM 1

void logInfo(std::string message);
void logDebug(std::string message);
void logError(std::string message);
void udpSendMessage(std::string message);

#endif