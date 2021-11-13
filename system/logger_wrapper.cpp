#include "logger_wrapper.h"

using namespace std;

const char *udp_hostname = "192.168.0.140";
const int udp_port = 9000;
const int bufferSize = 1024;


enum log_level
{
    INFO,
    DEBUG,
    ERROR
};
std::string enhance(std::string logLevel, std::string message)
{
    return logLevel + message;
}

void logInfo(std::string message)
{
    std::string output_message = enhance("INFO ", message);
    cout << output_message;
    udpSendMessage(output_message);
}

void logDebug(std::string message)
{
    std::string output_message = enhance("DEBUG ", message);
    cout << output_message;
    udpSendMessage(output_message);
}

void logError(std::string message)
{
    std::string output_message = enhance("ERROR ", message);
    cout << output_message;
    udpSendMessage(output_message);
}

// Client side implementation of UDP client-server model

// Driver code
void udpSendMessage(std::string message)
{
    int sockfd;
    //char buffer[bufferSize];
    struct sockaddr_in udpServerAddress;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&udpServerAddress, 0, sizeof(udpServerAddress));

    // Filling server information
    udpServerAddress.sin_family = AF_INET;

    udpServerAddress.sin_port = htons(udp_port);
    udpServerAddress.sin_addr.s_addr = inet_addr(udp_hostname);

    sendto(sockfd, (const char *)message.c_str(), strlen(message.c_str()),
           MSG_CONFIRM, (const struct sockaddr *)&udpServerAddress,
           sizeof(udpServerAddress));
    printf("Hello message sent.\n");

    close(sockfd);
}

int main() {
    logInfo("Bulbs");
    logError("Lights");
    logDebug("Power");
    return 0;
}




