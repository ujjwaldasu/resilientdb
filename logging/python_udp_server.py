import socket


class UDPServer:

    def __init__(self):
        self.localIP     = "192.168.0.140"
        self.localPort   = 9000
        self.bufferSize  = 1024

        self.numLinesWritten = 0;
        self.loglineThreshold = 1000;
        self.currFileIndex = 0;
        self.logFileDirectory = "./"
        self.logFileNamePrefix = "resilientDBLog_";
        self.currentOpenFile = None;
        #self.currentLogLines = [];


    def runServer(self):
        # Create a datagram socket
        UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

        # Bind to address and ip
        UDPServerSocket.bind((self.localIP, self.localPort))

        print("UDP server up and listening on port " + str(self.localPort))
        # Listen for incoming datagrams
        while(True):
            bytesAddressPair = UDPServerSocket.recvfrom(self.bufferSize)
            message = bytesAddressPair[0]
            address = bytesAddressPair[1]

            logOutputLine = str.format("Message: {}, From Address {}\n", message, address);
            try:
                print(logOutputLine)
                self.getCurrentLoggerFile().write(logOutputLine)
                self.numLinesWritten += 1;
                    
            except Exception as ex:
                if(self.currentOpenFile is not None):
                    self.currentOpenFile.close();
                print(ex)

    def getCurrentLoggerFile(self):
        if self.currentOpenFile is None:
            self.numLinesWritten = 0;
            print("Opening New File: " + str(self.currFileIndex));
            self.currentOpenFile = open(self.logFileDirectory + self.logFileNamePrefix + str(self.currFileIndex) + ".log", "w");

        elif self.numLinesWritten >= self.loglineThreshold:
            self.currFileIndex += 1;
            print("Log File Line Threshold Reached. Close and Open New File: " + str(self.currFileIndex ));
            self.currentOpenFile.close();
            # Open New File
            self.currentOpenFile = open(self.logFileDirectory + self.logFileNamePrefix + str(self.currFileIndex) + ".log", "w");
            self.numLinesWritten = 0;

        #self.numLinesWritten+=1;
        return self.currentOpenFile;
        

if __name__ == '__main__':
    udp = UDPServer();
    udp.runServer();