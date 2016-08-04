from test_namedlist_codingPNL_0_001 import *
def getEncodebufByMsgid(msgid, st):
    encode_fun = g_encode_fun.get(msgid,None)
    if encode_fun == None:
        return None
    return encode_fun(st)
def getStructByMsgid(msgid, buf):
    decode_fun = g_decode_fun.get(msgid,None)
    if decode_fun == None:
        return None,0
    return decode_fun(buf)
    
def getSendbuf(msgid, st):
    s= getEncodebufByMsgid(msgid, st)
    length = len(s)
    headbuf, headlen = EncodeMsgHead_Gate(msgid, length)
    return (headbuf+s, headlen+length)
def getStruct(buf):
    msgid, structlen, headlen = DecodeMsgHead_Gate(buf)
    if headlen == 0 or headlen+structlen>len(buf):
        return None,0,0
    st,length = getStructByMsgid(msgid, buf[headlen:headlen+structlen])
    return st, structlen+headlen, msgid
    