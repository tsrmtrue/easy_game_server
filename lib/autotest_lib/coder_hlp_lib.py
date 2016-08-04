# -*- coding: GBK -*-
# 联系作者 qq 150237442

from struct import *

"""def addByte(str, B):
    str += pack('B', B)
    return str

def addChar(str, b):
    str += pack('b', b)
    return str

def addWord(str, H):
    str += pack("!H", H)
    return str

def addShort(str, h):
    str += pack('!h', h)
    return str

def addDword(str, I):
    str += pack('!I', I)
    return str

def addInt(str, i):
    str += pack('!i', i)
    return str

def addUint64(str, Q):
    str += pack('!Q', Q)
    return str

def addInt64(str, q):
    str += pack('!q', q)
    return str

def addFloat(str, f):
    str += pack('!f', f)
    return str

def addDouble(str, d):
    str += pack('!d', d)
    return str

def addString(str, s):
    n = len(s)
    str = addWord(str, n)
    str += pack("%ds"%n, s)
    return str
"""

def addByte(B):
    if B == None:
        B = 0
    return pack('B', B)

def getByte(buf):
    return (unpack('B', buf[:1])[0],1)

def addChar(b):
    if b == None:
        b = 0
    return pack('b', b)

def getChar(buf):
    return (unpack('b', buf[:1])[0],1)

def addWord(H):
    if H == None:
        H = 0
    return pack("!H", H)

def getWord(buf):
    return (unpack('!H', buf[:2])[0],2)

def addShort(h):
    if h == None:
        h = 0
    return pack('!h', h)

def getShort(buf):
    return (unpack('!h', buf[:2])[0],2)

def addDword(I):
    if I == None:
        I = 0
    return pack('!I', I)

def getDword(buf):
    return (unpack('!I', buf[:4])[0],4)

def addInt(i):
    if i == None:
        i = 0
    return pack('!i', i)

def getInt(buf):
    return (unpack('!i', buf[:4])[0],4)

"""#test
s = addInt(1234)
print getInt(s)+"4" """


def addUint64(Q):
    if Q == None:
        Q = 0
    return pack('!Q', Q)

def getUint64(buf):
    return (unpack('!Q', buf[:8])[0],8)

def addInt64(q):
    if q == None:
        q = 0
    return pack('!q', q)

def getInt64(buf):
    return (unpack('!q', buf[:8])[0],8)

def addFloat(f):
    if f == None:
        f = 0.0
    return pack('!f', f)

def getFloat(buf):
    return (unpack('!f', buf[:4])[0],4)

def addDouble(d):
    if d == None:
        d = 0.0
    return pack('!d', d)

def getDouble(buf):
    return (unpack('!d', buf[:8])[0],8)

def addString(s):
    if s == None:
        s = ''
    n = len(s)
    str = addWord(n)
    str += pack("%ds"%n, s)
    return str

def getString(buf):
    length = getWord(buf[:2])[0]
    #print length
    #print buf[2:2+length]
    str = unpack('%ds'%length, buf[2:2+length])
    return (str[0], length+2)

def getStringWithCount(buf, count):
    str = unpack('%ds'%count, buf[:count])
    return (str[0], count)
 

"""temp = addString("hello")
print temp
print getString(temp)"""

def Init2Zero(buf):
    if buf == None:
        return 0
    return buf

def addBuf(buf, count):
    if count == None:
        count = 0
        return ""
    #print buf
    if buf == None:
        buf = [0 for i in range(count)]
    if type(buf) == type('s'):
        return pack('%ds'%count, buf)
    elif type(buf) == type([]):
        buf = map(Init2Zero, buf)
        return pack('%dB'%count, *buf[0:count])
    else :
        return ""
def getBuf(buf, count):
    return (list(unpack('%dB'%count, buf[:count])), count)

#test
"""templ = [1,2,3,4,5]
tempbuf = addBuf(templ, len(templ))
print getBuf(tempbuf, len(templ))
t= None
tb = addBuf(t,5)
print getBuf(tb, 5)
t=[None,None,2,None]
tb = addBuf(t,None)
print getBuf(tb, 0)"""

"""s=""
s += addString("hello")
print s
s += addString("world")
s += addInt64(232323)
print s, len(s)"""

"""from structFmt_ML2 import *
from PythonStruct_ML2 import *
loginReq = struct_LGPKG_LOGIN_REQ._make(DV_T_LGPKG_LOGIN_REQ)
dict = {"a":"Type=^f%s^f"%("help"), "b":"InfoLen=4", "c":"Info[0]=1", "d":"Info[1]=2", "e":"Info[2]=3", "f":"Info[3]=4"}
loginReq = loginReq._replace(**dict)"""

"""loginReq.InfoLen = 4
loginReq.Info[0] = 1
loginReq.Info[1] = 2
loginReq.Info[2] = 3
loginReq.Info[3] = 4"""
"""
def EncodeLogin_Login_Req(st):
    s = ''
    s += addString(st.Type)
    s += addDword(st.InfoLen)
    s += addBuf(st.InfoLen, st.Info[:st.InfoLen])
    return s

def DecodeLogin_Login_Req(buf):
    l = list()
    pos = 0
    length, str = getString(buf[pos:])
    print length, str
    pos += 2 + length 
    print pos
    l.append(str)
    length = getDword(buf[pos:])
    l.append(length)
    pos += 4
    print pos
    #print length
    l.append(getBuf(buf[pos:], length))
    return l"""

import socket
def EncodeMsgHead_Gate(msgid, len):
    return (pack('0H H H', socket.htons(len+4), socket.htons(msgid)), calcsize('0H H H'))


def DecodeMsgHead_Gate(buf):
    headsize = calcsize('0H H H')
    if len(buf) < headsize:
        return 0,0,0
    head = unpack("0H H H", buf[:headsize])
    head = [socket.ntohs(head[1]), socket.ntohs(head[0]) - 4, ]
    return head + [headsize,]

#test
"""s, len = EncodeMsgHead_Gate(14001, 2)
print s, len
print DecodeMsgHead_Gate(s)"""


#print loginReq.Info
#s += addBuf(loginReq.InfoLen, loginReq.Info[:loginReq.InfoLen])
#print s, len(s)
#print loginReq
#print ''.join(loginReq.Info)
"""s = EncodeLogin_Login_Req(loginReq)
print s,len(s)"""
#新增函数，检测标志位
def has_tag(st,idx):
    return ( st._tag[idx/8] & (1<<(idx%8)) ) > 0 
