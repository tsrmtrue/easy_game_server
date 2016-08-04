# -*- coding: gbk -*-

import string
from parse_h_struct import *


def buildMemberLuaTable(member, indent, needIndent=False):
    type = member[0]
    name = member[1]
    count = member[2]
    if needIndent:
        indent_str = string.join(["    " for i in range(indent)], "")
    else:
        indent_str = ""
    if count <> "":
        #脢媒脳茅
        if isMemberNumber(member):
            c=getNumber(count)
            values = "{ " + string.join(["0" for i in range(c)], ',') + " }"
        elif isMemberString(member):
            values = '\"\"'
        elif isMemberStruct(member):
            c=getNumber(count)
            values = "{ " + string.join([buildStructLuaTable(type, indent+1, True) for i in range(c)], '    %(indent_str)s,'%(locals())) + "%(indent_str)s}"%(locals())
        else:
            global g_struct_dict
            #print  member
            raise ValueError('build struct error not found the definition of: %(member)r' % locals())
    else :
        # 路脟脢媒脳茅
        if isMemberNumber(member):
            values = "0" 
        elif isMemberStruct(member):
            values = buildStructLuaTable(type, indent+1, True) 
        else :
            raise ValueError('build struct error not found the definition of: %(name)s %(member)r' % locals())
    return "%(indent_str)s%(name)s=%(values)s"%(locals())

def buildMemberLuaTableFunction(member, indent, needIndent=True):
    type = member[0]
    name = member[1]
    count = member[2]
    if needIndent:
        indent_str = string.join(["    " for i in range(indent)], "")
    else:
        indent_str = ""
    if count <> "":
        #脢媒脳茅
        if isMemberNumber(member):
            c=getNumber(count)
            values = "{ " + string.join(["0" for i in range(c)], ',') + " }"
        elif isMemberString(member):
            values = '\"\"'
        elif isMemberStruct(member):
            c=getNumber(count)
            values = "{ " + string.join([buildStructLuaTableFunction(type, indent+1, True) for i in range(c)], '    %(indent_str)s,'%(locals())) + "%(indent_str)s}"%(locals())
        else:
            global g_struct_dict
            #print  member
            raise ValueError('build struct error not found the definition of: %(member)r' % locals())
    else :
        # 路脟脢媒脳茅
        if isMemberNumber(member):
            values = "0" 
        elif isMemberStruct(member):
            values = buildStructLuaTableFunction(type, indent+1, True) 
        else :
            raise ValueError('build struct error not found the definition of: %(name)s %(member)r' % locals())
    return "%(indent_str)s%(name)s=%(values)s"%(locals())

    
def buildStructLuaTable(structName, indent=0, forEmbed=False, needIndent=False):
    global g_struct_dict
    struct = g_struct_dict.get(structName, None)
    if needIndent:
        indent_str = string.join(["    " for i in range(indent)], "")
    else:
        indent_str = ""

    if struct == None:
        raise ValueError('build member error not found the definition of: %(structName)s' % locals())
    if forEmbed:
        struct_json_template = """
%(indent_str)s{
%(members)s
%(indent_str)s}
"""        
    else :
        struct_json_template = """
%(indent_str)s%(structName)s={
%(members)s
%(indent_str)s}
"""
    indent = [indent+1 for i in range(len(struct))]
    members = string.join(map(buildMemberLuaTable, struct, indent), ',\n')
    return struct_json_template%(locals())

def buildStructLuaTableFunction(structName, indent=1, forEmbed=False, needIndent=True):
    global g_struct_dict
    struct = g_struct_dict.get(structName, None)
    if needIndent:
        indent_str = string.join(["    " for i in range(indent)], "")
    else:
        indent_str = ""

    if struct == None:
        raise ValueError('build member error not found the definition of: %(structName)s' % locals())
    if forEmbed:
        struct_json_template = """ new_%(structName)s()
"""
    else :
        struct_json_template = """function new_%(structName)s()
    return 
%(indent_str)s{
%(members)s
%(indent_str)s}
end
"""        
    indent = [indent+1 for i in range(len(struct))]
    members = string.join(map(buildMemberLuaTableFunction, struct, indent), ',\n')
    return struct_json_template%(locals())


def buildEnumValue4Lua(enumvalue):
    return "%s=%s"%(enumvalue[0], enumvalue[1])

def buildAllJson():
    global g_struct_dict
    global g_enum_value_list
    strLuaTable = string.join(map(buildStructLuaTable, g_struct_dict.keys()), "\n")
    """global g_enum_dict
    strEnum = string.join(map(buildEnumValue, g_enum_dict.values()), '\n')
    print strEnum"""
    #print g_enum_dict[""]
    strEnum = string.join(map(buildEnumValue4Lua, g_enum_value_list), '\n')
    if strEnum == None:
        print "errrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr"
    if strLuaTable == None:
        strLuaTable = ""
    return strLuaTable + strEnum

def buildAllTableFunction():
    #创建table创建语句
    global g_struct_dict
    global g_enum_value_list
    global g_struct_name_list
    strLuaTable = string.join(map(buildStructLuaTableFunction, g_struct_name_list), "\n")
    """global g_enum_dict
    strEnum = string.join(map(buildEnumValue, g_enum_dict.values()), '\n')
    print strEnum"""
    #print g_enum_dict[""]
    strEnum = ""#string.join(map(buildEnumValue4Lua, g_enum_value_list), '\n')
    if strEnum == None:
        print "errrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr"
    if strLuaTable == None:
        strLuaTable = ""
    return strLuaTable + strEnum

#build encode decode麓煤脗毛
def getFormat(member):
    if isMemberNumber(member):
        return "%d"
    elif isMemberString(member):
        return "\\\"%s\\\""
    return ""
    
def build_member_encode(member):
    type = member[0]
    name = member[1]
    count = member[2]
    refer = member[3]
    if refer <> "":
        refer = refer[2:-2]
    single_standard_type_template = """
    memset(_t, 0, sizeof(_t));
    sprintf(_t, "\\\"%(name)s\\\":%(format)s,", st.%(name)s);
    buf += _t;
"""
    single_struct_template = """
    buf += "\\\"%(name)s\\\":";
    if (!encode_json_%(type)s(st.%(name)s, buf))
    {
        return false;
    }
    buf += ",";
"""
    array_standard_type_template = """
    buf +="\\\"%(name)s\\\":[";
    for(unsigned int i=0; i<%(ref)s ; ++i)
    {
        memset(_t, 0, sizeof(_t));
        sprintf(_t, "%(format)s,", st.%(name)s[i]);
        buf += _t;    
    }
    if(buf[buf.length()-1] == ',')
    {
        buf[buf.length()-1] = ']';
    }
    else
    {
        buf +="]";
    }
    buf +=",";
"""
#        sprintf(_t, "\\\"%(name)s\\\":%(format)s,", st.%(name)s[i]);

    array_struct_type_template = """
    buf +="\\\"%(name)s\\\":[";
    for(unsigned int i =0; i<%(ref)s; ++i)
    {
        if (!encode_json_%(type)s(st.%(name)s[i], buf))
        {
            return false;
        }
        buf += ",";
    }
    if(buf[buf.length()-1] == ',')
    {
        buf[buf.length()-1] = ']';
    }
    else
    {
        buf +="]";
    }
"""

    if count <> "":
        #脢媒脳茅
        if isMemberNumber(member):
            if refer <> "":
                ref = "st."+refer
            else:
                ref = count
            format = getFormat(member)
            return array_standard_type_template%(locals())
            #values = "{ " + string.join(["0" for i in range(c)], ',') + " }"
        elif isMemberString(member):
            format = getFormat(member)
            return single_standard_type_template%(locals())
        elif isMemberStruct(member):
            if refer <> "":
                ref = "st."+refer
            else:
                ref = count
            return array_struct_type_template%(locals())
        else:
            global g_struct_dict
            print  member
            raise ValueError('build struct error not found the definition of: %(member)r' % locals())
    else :
        # 路脟脢媒脳茅
        if isMemberNumber(member):
            format = getFormat(member)
            return single_standard_type_template%(locals())
        elif isMemberStruct(member):
            return single_struct_template%(locals())
        else :
            raise ValueError('build struct error not found the definition of: %(name)s %(member)r' % locals())



def build_member_decode(member):
    type = member[0]
    name = member[1]
    count = member[2]
    refer = member[3]
    jsonTypeReturn = ""
    if refer <> "":
        refer = refer[2:-2]
    single_standard_type_template = """
    st.%(name)s = (%(type)s)(v.get("%(name)s", 0).%(jsonTypeReturn)s);
"""
    single_struct_type_template = """
    {
        Json::Value _t = v["%(name)s"];
        st.%(name)s = decode_json_%(type)s(_t);
    }
"""
    array_standard_type_template = """
    {
        Json::Value _t = v["%(name)s"];
        unsigned int _total = %(count)s>_t.size()?_t.size():%(count)s;
        for (unsigned int i=0; i<_total; i++)
        {
            st.%(name)s[i] = (%(type)s)(_t[i].%(jsonTypeReturn)s);
        }
    }
"""
    array_struct_type_template = """
    {
        Json::Value _t = v["%(name)s"];
        unsigned int _total = %(count)s>_t.size()?_t.size():%(count)s;
        _total = _total>%(ref)s?%(ref)s:_total;
        for (unsigned int i=0; i<_total; i++)
        {
            st.%(name)s[i] = decode_json_%(type)s(_t[i]);
        }
    }
"""
    if count <> "":
        #脢媒脳茅
        if isMemberNumber(member):
            if refer <> "":
                ref = "st."+refer
            else:
                ref = count
            format = getFormat(member)
            jsonTypeReturn = "asInt()"
            return array_standard_type_template%(locals())
        elif isMemberString(member):
            format = getFormat(member)
            return """
    strncpy(st.%(name)s, v.get("%(name)s", "").asCString(), sizeof(st.%(name)s)-1);\n"""%(locals())
        elif isMemberStruct(member):
            if refer <> "":
                ref = "st."+refer
            else:
                ref = count
            return array_struct_type_template%(locals())
        else:
            global g_struct_dict
            print  member
            raise ValueError('build struct error not found the definition of: %(member)r' % locals())
    else :
        # 路脟脢媒脳茅
        if isMemberNumber(member):
            format = getFormat(member)
            jsonTypeReturn = "asInt()"
            return single_standard_type_template%(locals())
        elif isMemberStruct(member):
            return single_struct_type_template%(locals())
        else :
            raise ValueError('build struct error not found the definition of: %(name)s %(member)r' % locals())

def build_struct_encode_function(structName):
    return "bool encode_json_%(structName)s(%(structName)s& st, string& buf)"%(locals())

def build_struct_decode_function(structName):
    return "%(structName)s decode_json_%(structName)s(Json::Value& v)"%(locals())

def build_lua_json_test_code(structName):
    return """jsonTest = json.encode(%(structName)s)
out:write('%(structName)s ='..'\"\"\"'..jsonTest..'\"\"\"\\n')"""%(locals())


def build_struct_encode(structName):
    global g_struct_dict
    struct = g_struct_dict.get(structName, None)
    if struct == None:
        raise ValueError('build build_encode not found the definition of: %(structName)s' % locals())
    
    encode_template = """
%(encodeFunction)s
{
    char _t[1024]="";
    buf += "{";

    %(memberEncode)s
    
    if(buf[buf.length()-1] == ',')
    {
        buf[buf.length()-1] = '}';
    }
    else
    {
        buf +="}";
    }
    return true;
}
"""
    encodeFunction = build_struct_encode_function(structName)
    memberEncode = string.join(map(build_member_encode, struct), '\n');
    return encode_template%(locals())

def build_struct_decode(structName):
    global g_struct_dict
    struct = g_struct_dict.get(structName, None)
    if struct == None:
        raise ValueError('build build_encode not found the definition of: %(structName)s' % locals())
    
    decode_template = """
%(decodeFunction)s
{
    %(structName)s st %(initializeStruct)s;

    %(memberDecode)s
    
    return st;
}
"""
    initializeStruct = ""
    if len(struct) <> 0:
        initializeStruct = """={0};"""
    decodeFunction = build_struct_decode_function(structName)
    memberDecode = string.join(map(build_member_decode, struct), '\n');
    return decode_template%(locals())

    
def build_encode_cpp():
    encode_template = """#include "protocolEncode.h"
#include <string.h>

%(encodes)s

"""
    global g_struct_dict
    encodes = string.join(map(build_struct_encode, g_struct_dict.keys()), '\n')
    return encode_template%(locals())

def build_decode_cpp():
    decode_template = """#include "protocolDecode.h"
#include <string.h>
%(decodes)s

"""
    global g_struct_dict
    decodes = string.join(map(build_struct_decode, g_struct_dict.keys()), '\n')
    return decode_template%(locals())

    
def build_encode_h():
    encode_template = """#ifndef __PROTOCOLENCODE_H__
#define    __PROTOCOLENCODE_H__

#include <string.h>
#include <stdio.h>
#include "protocols.h"
using namespace std;

%(encodeFunctions)s;

#endif    //__PROTOCOLENCODE_H__
"""
    global g_struct_dict
    encodeFunctions = string.join(map(build_struct_encode_function, g_struct_dict.keys()), ";\n")
    return encode_template%(locals())

def build_decode_h():
    decode_template = """#ifndef __PROTOCOL_DECODE_H__
#define    __PROTOCOL_DECODE_H__

#include <string.h>
#include <stdio.h>
#include "json/value.h"
#include "protocols.h"
using namespace std;

%(decodeFunctions)s;

#endif    //__PROTOCOL_DECODE_H__
"""
    global g_struct_dict
    decodeFunctions = string.join(map(build_struct_decode_function, g_struct_dict.keys()), ";\n")
    return decode_template%(locals())
    
def build_lua_json_test():
    lua_json_test_template = """require('protocols_table')
json = require('json')
local out = assert(io.open("../../Server/tools/protocol_json_str.py", "w"))
out:write('#generated automatically,do NOT change manually')
%(luajsontest)s
out:close()
"""
    global g_struct_dict
    luajsontest = string.join(map(build_lua_json_test_code, g_struct_dict.keys()), ";\n")
    return lua_json_test_template%(locals())
    
def build_all_enum_py():
    all_enum_template = """#generated automatically,do NOT change manually
%(enums)s
"""
    global g_enum_dict
    enums = string.join(map(buildEnumValue, g_enum_dict.values()), '\n')
    return (all_enum_template%(locals()))

def build_all_enum_lua():
    all_enum_template = """--generated automatically,do NOT change manually
%(enums)s
"""
    global g_enum_dict
    enums = string.join(map(buildEnumValue, g_enum_dict.values()), '\n')
    return (all_enum_template%(locals()))

#def parseHFile(filename):
#    f = open(filename, 'r')
#    filestr = f.read()
#    filestr = string.replace(filestr, "\n", " ")
#    filestr = string.replace(filestr, "\t", " ")
#    #print [filestr, ]
#    parseCppStruct(filestr)
#    parseCppEnum(filestr)
#    parseEnumValueAll()
#    #global g_enum_dict 
#    #print g_enum_dict 
#    
#    #太占用资源.
#    #w = open('../Resources/script/protocols_table.lua', 'w')
#    #w.write(buildAllJson())
#    #w.close()
#
#    w = open('../Common/Protocols/protocols_table_function.lua', 'w')
#    w.write(buildAllTableFunction())
#    w.close()
#
#
##    w = open('../Resources/script/protocols_output_json.lua', 'w')
##    w.write(build_lua_json_test())
##    w.close()
#
#    
#    w = open('../Common/Protocols/protocolEncode.h', 'w')
#    w.write(build_encode_h())
#    w.close()
#    w = open('../Common/Protocols/protocolEncode.cpp', 'w')
#    w.write(build_encode_cpp())
#    w.close()
#    
#    w = open('../Common/Protocols/protocolDecode.h', 'w')
#    w.write(build_decode_h())
#    w.close()
#
#    w = open('../Common/Protocols/protocolDecode.cpp', 'w')
#    w.write(build_decode_cpp())
#    w.close()
#
#    w = open('protocol_enums.py', 'w')
#    w.write(build_all_enum_py())
#    w.close()
#
#    w = open('autotest_client/protocol_enums.py', 'w')
#    w.write(build_all_enum_py())
#    w.close()
#    
#    w = open('../Common/Protocols/protocol_enums.lua', 'w')
#    w.write(build_all_enum_lua())
#    w.close()
#
#
#    print "OK"
#    
def parseHFile2LuaProtocol(hFilename, targetEnumFile, targetTableStructFile):
    f = open(hFilename, 'r')
    filestr = f.read()
    filestr = string.replace(filestr, "\n", " ")
    filestr = string.replace(filestr, "\t", " ")
    #print [filestr, ]
    parseCppStruct(filestr)
    parseCppEnum(filestr)
    parseEnumValueAll()

    w = open(targetEnumFile, 'w')
    w.write(build_all_enum_lua())
    w.close()

    w = open(targetTableStructFile, 'w')
    w.write(buildAllTableFunction())
    w.close()



#def main():  
#    parseHFile("../Common/Protocols/protocols.h")
#    
"""global g_enum_dict
for k in sorted(g_enum_dict.keys()):
    print k
    print "    ",g_enum_dict[k]
"""
