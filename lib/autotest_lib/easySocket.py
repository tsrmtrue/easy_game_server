# -*- coding: utf8 -*-
# 联系作者 qq 150237442

import socket


class easySocket:
    client = None
    sendbuf = ""
    recvbuf = ""
    lastErrcode = 0
    def __init__(self, client):
        self.client = client
        self.sendbuf  = ""
        self.recvbuf  = ""

    def add2send(self, buf):
        self.sendbuf = self.sendbuf + buf
        
    def trySend(self):
        if self.sendbuf == "":
            return True
        try:
            #print "do send ",self.sendbuf
            sent = self.client.send(self.sendbuf)
            self.sendbuf = self.sendbuf[sent:]
        except socket.error,e :
            if e[0] in [10035, 11, 35]: #windows下异步错误为10035，linux下为11，EAGAIN,macOS 是35
                return True
            print "send exception ", e
            return False
        return True
         
    def tryRecv(self):
        try:
            s = self.client.recv(1024*100)
            if s <> "":
                #print "recv s"
                self.recvbuf = self.recvbuf + s
            else :
                #print "try recv empty",s
                return False
        except socket.error,e :
            #print "tryrecv exception ", e
            if e[0] in [10035, 11, 35]:
                #print "try recv return true"
                return True
            self.lastErrcode = e[0]
            #print "tryrecv return false exception"
            return False
        except :
            pass
            #print "tryrecv unknown exception"
        return True
    
    def onRecv(self):
        #tobe override
        return False
    
    def onActiveTimer(self):
        return True

    
    def run(self):
        if self.trySend() == False:
            print "trysend return false"
            return False
        if self.tryRecv() == False:
            print "tryrecv return false"
            return False
        if self.onRecv() == False:
            print "onrecv return false"
            return False
        if self.onActiveTimer() == False:
            print "onrecv return false"
            return False
        return True
    
    def close(self):    
        self.client.close()
        self.client = None
        

        
        
        
        
        
        
        
        
        
        
        
        
        
        