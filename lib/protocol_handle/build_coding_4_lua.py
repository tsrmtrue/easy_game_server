# -*- coding: gbk -*-


import string
from parse_h_struct import *

g_encode_dict = {
              "unsigned int"        :"encode_long",
              "int"                 :"encode_long",              
              "short"               :"encode_short",
              "unsigned short"      :"encode_short",
              "unsigned long long"  :"nolonglong",
              "long long"           :"nolonglong",              
              "char"                :"encode_byte",
              "unsigned char"       :"encode_byte",
              }


g_decode_dict = {
              "unsigned int"        :"decode_long",
              "int"                 :"decode_long_signed",              
              "short"               :"decode_short",
              "unsigned short"      :"decode_short",
              "unsigned long long"  :"nolonglong",
              "long long"           :"nolonglong",
              "char"                :"decode_byte",
              "unsigned char"       :"decode_byte",
               }

g_type_len_dict = {
              "unsigned int"        :"4",
              "int"                 :"4",              
              "short"               :"2",
              "unsigned short"      :"2",
              "unsigned long long"  :"8",
              "long long"           :"8",
              "char"                :"1",
              "unsigned char"       :"1",
               }

g_decode_func_list = []
g_encode_func_list = []

g_projectPrefix = ""

def get_type_len_by_type(type):
    global g_type_len_dict
    return g_type_len_dict.get(type, "")
    
def get_decode_by_type(type):
    global g_projectPrefix
    global g_hton_dict
    projectPrefix = g_projectPrefix
    s = g_decode_dict.get(type, None)
    if s == "nolonglong":
        raise ValueError('longlong of: %(type)r' % locals())
    
    if s == None:
        s = "%(projectPrefix)sprotocol_decode_lua.decode_%(type)s(buf, __used__)"%(locals())
    else:
        s=s+"(buf, __used__)"
    return s

def get_encode_by_type(type):
    global g_projectPrefix
    global g_ntoh_dict
    projectPrefix = g_projectPrefix

    s = g_encode_dict.get(type, None)
    if s == "nolonglong":
        raise ValueError('longlong of: %(type)r' % locals())

    if s == None:
        s = "%(projectPrefix)sprotocol_encode_lua.encode_%(type)s"%(locals())
    return s

def build_member_encode_4_lua(member):
    type = member[0]
    name = member[1]
    count = member[2]
    refer = member[3]
    if refer <> "":
        refer = refer[2:-2]
    encode_ = get_encode_by_type(type)
    single_standard_type_template = """
    local _s = %(encode_)s(st.%(name)s)
    if _s == nil then
        error(" return nil %(name)s")
        return nil
    else
        buf = buf .. _s
    end
"""
    array_bytes_template = """
    if %(for_limit)s > %(count)s then 
        error(" return nil %(name)s forlimit" .. %(for_limit)s .."count" .. %(count)s)
        return nil
    end
    buf = buf..st.%(name)s
"""
    array_standard_type_template = """
    if %(for_limit)s > %(count)s then
        error(" return nil %(name)s forlimit" .. %(for_limit)s .."count" .. %(count)s)
        return nil
    end
    for i=1, %(for_limit)s do
        local _s = %(encode_)s(st.%(name)s[i])
        if _s == nil then
            error(" return nil %(name)s")
            return nil
        end
        buf = buf.._s
    end

"""
    array_struct_type_template = """
    %(check_count)s
    for i=1, %(for_limit)s do
        local _s = %(encode_)s(st.%(name)s%(array_ptr)s)
        if _s == nil then
            error(" return nil %(name)s")
            return nil
        end
        buf = buf.._s
    end
"""
    string_type_template = """
    if string.len(st.%(name)s) > %(count)s then
        error(" return nil %(name)s")
        return nil
    end
    local _s = encode_short(string.len(st.%(name)s))
    if _s == nil then
        error(" return nil %(name)s")
        return nil
    else
        buf = buf .. _s
    end
    buf = buf..st.%(name)s
"""
    for_limit = "%(count)s"%(locals())
    if count == "":
        for_limit = "1"
    if refer <> "":
        for_limit = "st.%(refer)s"%(locals())

    check_count = ""
    if count <> "" and refer <> "":
        check_count = """
    if st.%(refer)s > %(count)s then
        error(" return nil %(name)s forlimit" .. st.%(refer)s .. "count" .. %(count)s)
        return nil
    end"""%(locals())

    if isMemberNumber(member):
        #»ù±¾ÀàÐÍ
        if count <> "":
            #bytes
            if type == "unsigned char  nouse":
                for_limit = "string.len(st.%(name)s)"%(locals())
                return array_bytes_template%(locals())
            #ÆäËûÊý×é
            else:
                return array_standard_type_template%(locals())
        else:
        #·ÇÊý×é
            return single_standard_type_template%(locals())
    elif isMemberString(member):
        for_limit = "string.len(st.%(name)s)"%(locals())
        return string_type_template%(locals())
    elif isMemberStruct(member):
        if for_limit == "":
            print member
        array_ptr = ""
        if count <> "":
            array_ptr = "[i]"
        return array_struct_type_template%(locals())

"""
def get_build_struct_encode_4_lua(structName):
    return build_struct_encode_4_lua(structName, "")

def get_build_struct_encode_4_lua_4_passport(structName):
    return build_struct_encode_4_lua(structName, "passport")
"""

def build_struct_encode_4_lua(structName):
    global g_struct_dict
    global g_projectPrefix
    projectPrefix = g_projectPrefix

    struct = g_struct_dict.get(structName, None)
    if struct == None:
        raise ValueError('build build_struct_encode_4_cpp not found the definition of: %(structName)s' % locals())
    
    encode_template = """
%(projectPrefix)sprotocol_encode_lua["%(func_name)s"] = function (st)
    local buf = ""
    
    %(encode_member)s
    
    return buf
end
"""
    func_name = "encode_%(structName)s"%(locals())
    global g_encode_func_list
    g_encode_func_list.append(func_name)
    
    encode_member = string.join(map(build_member_encode_4_lua, struct), '\n');
    return encode_template%(locals())    
    
def build_encode_4_lua():
    global g_projectPrefix
    projectPrefix = g_projectPrefix
    encode_template = """
function encode_long(l)
    local a = l/(0x100*0x100*0x100)%%0x100
    local b = l/(0x100*0x100)%%0x100
    local c = l/(0x100)%%0x100
    local d = l%%0x100
    a = math.modf(a, 1)
    b = math.modf(b, 1)
    c = math.modf(c, 1)
    d = math.modf(d, 1)

    return string.char(a,b,c,d)
end

function encode_short(s)
    local a = s/(0x100)%%0x100
    local b = s%%0x100
    a = math.modf(a, 1)
    b = math.modf(b, 1)
    return string.char(a, b)
end

function encode_byte(b)
    local a = b%%0x100
    a = math.modf(a, 1)
    return string.char(a)
end
 
%(projectPrefix)sprotocol_encode_lua = {}
%(encodes)s

"""
    global g_struct_dict
    encodes = string.join(map(build_struct_encode_4_lua, g_struct_dict.keys()), '\n')
    return encode_template%(locals())

def build_member_decode_4_lua(member):
    type = member[0]
    name = member[1]
    count = member[2]
    refer = member[3]
    if refer <> "":
        refer = refer[2:-2]
    decode_ = get_decode_by_type(type)
    type_len = get_type_len_by_type(type)
    for_limit = "%(count)s"%(locals())
    if count == "":
        for_limit = "1"
    if refer <> "":
        for_limit = "st.%(refer)s"%(locals())

    
    single_standard_type_template = """
    st.%(name)s = %(decode_)s
    if st.%(name)s == nil then
        error(" return nil %(name)s")
        return nil
    else
        __used__ = __used__ + %(type_len)s
    end
"""
    array_bytes_template = """
    if %(for_limit)s > %(count)s then
        error(" return nil %(name)s for limit:" .. %(for_limit)s .. " count " .. %(count)s )
        return nil
    end
    if %(for_limit)s + __used__>string.len(buf) + 1 then
        error(" return nil %(name)s for limit:" .. %(for_limit)s .. " buf len " .. string.len(buf))
        return nil
    end
    st.%(name)s = string.sub(buf, __used__, __used__+%(for_limit)s)
    __used__ = __used__ + %(for_limit)s
"""
    array_standard_type_template = """
    if %(for_limit)s > %(count)s then
        error(" return nil %(name)s for limit:" .. %(for_limit)s .. " count " .. %(count)s )
        return nil
    end
    st.%(name)s = {}
    for i=1, %(for_limit)s do
        st.%(name)s[i] = %(decode_)s
        if st.%(name)s[i] == nil then
            error(" return nil %(name)s")
            return nil
        else
            __used__ = __used__ + %(type_len)s
        end
    end
"""
    array_struct_type_template = """
    %(check_count)s
    st.%(name)s = {}
    for i=1, %(for_limit)s do
        if  __used__>string.len(buf) + 1 then
            error(" return nil %(name)s")
            return nil
        end

        st.%(name)s%(array_ptr)s = %(decode_)s
        if st.%(name)s%(array_ptr)s == nil then
            error(" return nil %(name)s")
            return nil
        else
            __used__ =  st.%(name)s%(array_ptr)s.__used__
        end
    end
"""
    string_type_template = """
    local _s_l = decode_short(buf, __used__)
    if _s_l == nil then
        error(" return nil %(name)s")
        return nil
    else
        __used__ = __used__ + 2
    end
    if _s_l + __used__>string.len(buf) + 1 then
        error(" return nil %(name)s")
        return nil
    end
    st.%(name)s = string.sub(buf, __used__, __used__+_s_l -1)
    __used__ = __used__ + _s_l
"""

    check_count = ""
    if count <> "" and refer <> "":
        check_count = """
    if st.%(refer)s > %(count)s then
        error(" return nil %(name)s for limit:" .. st.%(refer)s .. " count " .. %(count)s )
        return nil
    end"""%(locals())
    if isMemberNumber(member):
        #»ù±¾ÀàÐÍ
        if count <> "":
            #bytes
            if type == "unsigned char":
                return array_bytes_template%(locals())
            #ÆäËûÊý×é
            else:
                return array_standard_type_template%(locals())
        else:
        #·ÇÊý×é
            return single_standard_type_template%(locals())
    elif isMemberString(member):
        return string_type_template%(locals())
    elif isMemberStruct(member):
        array_ptr = ""
        if count <> "":
            array_ptr = "[i]"
        return array_struct_type_template%(locals())

def build_struct_decode_4_lua(structName):
    global g_projectPrefix
    global g_struct_dict
    projectPrefix = g_projectPrefix
    struct = g_struct_dict.get(structName, None)
    if struct == None:
        raise ValueError('build build_encode not found the definition of: %(structName)s' % locals())
    
    decode_template = """
%(projectPrefix)sprotocol_decode_lua["%(fun_name)s"] = function (buf, i)
    local __used__ = i
    local st = {}
    
    %(members_decode)s
    
    st.__used__ = __used__
    return st
end
"""         
    fun_name = "decode_%(structName)s"%(locals())
    global g_decode_func_list
    g_decode_func_list.append(fun_name)
    
    members_decode = string.join(map(build_member_decode_4_lua, struct), '\n');
    return decode_template%(locals())

def build_decode_4_lua():
    global g_projectPrefix
    projectPrefix = g_projectPrefix
    decode_template = """
function decode_long(s, i)
    if i + 4 > string.len(s) + 1 then
        return nil
    end
    local a = string.byte(s,i,i)
    if a == nil then a = 0 end
    local b = string.byte(s,i+1,i+1)
    if b == nil then b = 0 end
    local c = string.byte(s,i+2,i+2)
    if c == nil then c = 0 end
    local d = string.byte(s,i+3,i+3)
    if d == nil then d = 0 end
    --print(a,b,c,d)
    return a*0x100*0x100*0x100 + b*0x100*0x100 + c*0x100 + d
end

function decode_long_signed(s, i)
    if i + 4 > string.len(s) + 1 then
        return nil
    end
    local a = string.byte(s,i,i)
    if a == nil then a = 0 end
    local b = string.byte(s,i+1,i+1)
    if b == nil then b = 0 end
    local c = string.byte(s,i+2,i+2)
    if c == nil then c = 0 end
    local d = string.byte(s,i+3,i+3)
    if d == nil then d = 0 end
    --print(a,b,c,d)
    e = a*0x100*0x100*0x100 + b*0x100*0x100 + c*0x100 + d
    if e < 0x80000000 then
        return e
    else 
        return -(0x7fffffff - (e - 0x80000000 - 1))
    end
end

function decode_short(s, i)
    if i + 2 > string.len(s)+1 then
        return nil
    end
    local a = string.byte(s,i,i)
    if a == nil then a = 0 end
    local b = string.byte(s,i+1,i+1)
    if b == nil then b = 0 end
    return a*0x100 + b
end

function decode_byte(s, i)
    if i + 1 > string.len(s)+1 then
        return nil
    end
    local a = string.byte(s,i,i)
    if a == nil then a = 0 end
    return a
end

%(projectPrefix)sprotocol_decode_lua = {}
%(decodes)s
"""
    global g_struct_dict
    decodes = string.join(map(build_struct_decode_4_lua, g_struct_dict.keys()), '\n')
    return decode_template%(locals())

def build_test_coding_4_lua_struct(structName):
    global g_projectPrefix
    projectPrefix = g_projectPrefix
    test_struct_template = """
print("-------------------test %(structName)s--------------")
s = %(projectPrefix)sprotocol_encode_lua.encode_%(structName)s(%(structName)s)
print(type(s))
print(string.len(s))
st = %(projectPrefix)sprotocol_decode_lua.decode_%(structName)s(s, 1)
if st == nil then
    error("-----error %(structName)s")
end
print_r(st)
"""
    return test_struct_template%(locals())

def build_test_coding_4_lua():
    global g_projectPrefix
    projectPrefix = g_projectPrefix
    test_template = """
package.path = package.path .. ";" ..  "C:/X_H_W/trunk/Common/Protocols/?.lua"
local print = print
local tconcat = table.concat
local tinsert = table.insert
local srep = string.rep
local type = type
local pairs = pairs
local tostring = tostring
local next = next
 
function print_r(root)
    local cache = {  [root] = "." }
    local function _dump(t,space,name)
        local temp = {}
        for k,v in pairs(t) do
            local key = tostring(k)
            if cache[v] then
                tinsert(temp,"+" .. key .. " {" .. cache[v].."}")
            elseif type(v) == "table" then
                local new_key = name .. "." .. key
                cache[v] = new_key
                tinsert(temp,"+" .. key .. _dump(v,space .. (next(t,k) and "|" or " " ).. srep(" ",#key),new_key))
            else
                tinsert(temp,"+" .. key .. " [" .. tostring(v).."]")
            end
        end
        return tconcat(temp,"\\n"..space)
    end
    print(_dump(root, "",""))
end

require('protocols_table')
require('protocolEncode4lua')
require('protocolDecode4lua')

%(struct_test)s
print("OK")
"""
    global g_struct_dict
    struct_test = string.join(map(build_test_coding_4_lua_struct, g_struct_dict.keys()), '\n')

    return test_template%(locals())
    
    
#def parseHFile(filename):
#    f = open(filename, 'r')
#    filestr = f.read()
#    filestr = string.replace(filestr, "\n", " ")
#    filestr = string.replace(filestr, "\t", " ")
#    #print [filestr, ]
#    parseCppStruct(filestr)
#    parseCppEnum(filestr)
#    global g_enum_dict 
#    # print g_enum_dict 
#    
#    w = open('../Common/Protocols/protocolEncode4lua.lua', 'w')
#    w.write(build_encode_4_lua())
#    w.close()
#    
#    w = open('../Common/Protocols/protocolDecode4lua.lua', 'w')
#    w.write(build_decode_4_lua())
#    w.close()
#    
##    w = open('../Resources/script/protocolCodingTest.lua', 'w')
##    w.write(build_test_coding_4_lua())
##    w.close()
#
#    
#    print "OK"

def parseHFileWithTarget(hFile,targetEncodeFile,targetDecodeFile):
    f = open(hFile, 'r')
    filestr = f.read()
    filestr = string.replace(filestr, "\n", " ")
    filestr = string.replace(filestr, "\t", " ")   #windows  \t  ubuntu \r
    #print [filestr, ]
    parseCppStruct(filestr)
    parseCppEnum(filestr)
    global g_enum_dict 
    print g_enum_dict 
    
    w = open(targetEncodeFile, 'w')
    w.write(build_encode_4_lua())
    w.close()
    
    w = open(targetDecodeFile, 'w')
    w.write(build_decode_4_lua())
    w.close()


# def main():
#     parseHFile("../Common/Protocols/protocols.h")

# print "hello "
