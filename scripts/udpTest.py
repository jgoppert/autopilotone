#!/usr/bin/env python

import time
import socket
import thread

class UdpTest:
    """ a udp test class"""

    def __init__(self,host,portSend,portReceive):
        """initialize the socket"""

        # send socket
        self.host = host
        self.portSend = portSend
        self.sockSend = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        # receive socket
        self.portReceive = portReceive
        self.sockReceive = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sockReceive.bind((host,portReceive))

        thread.start_new_thread(self.sendMessage,())
        thread.start_new_thread(self.receiveMessage,())
        time.sleep(1000)

    def sendMessage(self):
        """send a message"""
        while True:
            message = "hello\n"
            print "sending", message
            self.sockSend.sendto(message, (self.host, self.portSend))
            time.sleep(0.1)

    def receiveMessage(self):
        """receive a message"""
        while True:
            data, addr = self.sockReceive.recvfrom(1024)
            print "received message:", data
            time.sleep(0.1)


if __name__ == "__main__":
    udp = UdpTest("127.0.0.1",5002,5001)
