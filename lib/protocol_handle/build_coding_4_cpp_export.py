# -*- coding: gbk -*-
# 需要封装动态库的时候，使用这个配置 生成
import string
from parse_h_struct import *
from build_coding_4_cpp import *


def build_struct_encode_function_4_cpp_definition(structName):
    return """__declspec(dllexport) int encode_%(structName)s(%(structName)s& st, unsigned char* pBuf, unsigned int bufLength )"""%(locals())

def build_struct_encode_function_4_cpp_declaration(structName):
    return """extern "C" int __cdecl encode_%(structName)s(%(structName)s& st, unsigned char* pBuf, unsigned int bufLength )"""%(locals())


def build_member_encode_4_cpp(member):
    type = member[0]
    name = member[1]
    count = member[2]
    refer = member[3]
    if refer <> "":
        refer = refer[2:-2]
    single_standard_type_template = """
    if (__used__ + sizeof(%(type)s) <= bufLength)
    {
        %(type)s* __i__ = (%(type)s *)(pBuf + __used__);
        *__i__ = %(hton_)s(st.%(name)s);
        __used__ += sizeof(%(type)s);
    }
    else
    {
        return -1;
    }

"""
    array_bytes_template = """
    {
        %(check_count)s
        if (__used__ + st.%(refer)s <= bufLength)
        {
            memcpy(pBuf+__used__, st.%(name)s, %(for_limit)s);
            __used__ += %(for_limit)s;
        }
        else
        {
            return -1;
        }
    }
"""
    array_standard_type_template = """
    {
        %(check_count)s
        if (__used__ + sizeof(st.%(name)s[0]) * %(for_limit)s <= bufLength)
        {
            for(unsigned int i=0; i<%(for_limit)s; ++i)
            {            
                %(type)s* __i__ = (%(type)s *)(pBuf + __used__);
                *__i__ = %(hton_)s(st.%(name)s[i]);
                __used__ += sizeof(%(type)s);
            }
        }
        else
        {
            return -1;
        }
    }
"""
    array_struct_type_template = """
    {
        %(check_count)s
        for (unsigned int i=0; i<%(for_limit)s; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_%(type)s(st.%(name)s%(array_ptr)s, pBuf+__used__, bufLength - __used__ );
            if (__r__>0)
            {
                __used__ += __r__;
            }
            else
            {
                return -1;
            }
        }
    }
"""
    string_type_template = """
    if (__used__ + sizeof(short) + strlen(st.%(name)s) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.%(name)s));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.%(name)s, strlen(st.%(name)s));
        __used__ += strlen(st.%(name)s);
    }
    else
    {
        return -1;
    }
"""
    for_limit = "%(count)s"%(locals())
    if count == "":
        for_limit = "1"
    if refer <> "":
        for_limit = "st.%(refer)s"%(locals())

    check_count = ""
    if count <> "" and refer <> "":
        check_count = """
        if (st.%(refer)s > %(count)s)
        {
            return -1;
        }"""%(locals())

    if isMemberNumber(member):

        hton_ = get_hton_by_type(type)
        if hton_ == None:
            raise ValueError('build struct error not found the definition of: %(member)r' % locals())
        #基本类型
        if count <> "":
            #bytes
            if type == "unsigend char":
                return array_bytes_template%(locals())
            #其他数组
            else:
                return array_standard_type_template%(locals())
        else:
        #非数组
            return single_standard_type_template%(locals())
    elif isMemberString(member):
        return string_type_template%(locals())
    elif isMemberStruct(member):
        if for_limit == "":
            print member
        array_ptr = ""
        if count <> "":
            array_ptr = "[i]"
        return array_struct_type_template%(locals())

def build_struct_encode_4_cpp(structName):
    global g_struct_dict
    struct = g_struct_dict.get(structName, None)
    if struct == None:
        raise ValueError('build build_struct_encode_4_cpp not found the definition of: %(structName)s' % locals())
    
    encode_template = """
%(encodeFunction_definition)s
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    %(members_encode)s

    return __used__;
}
"""
    initializeStruct = ""
    if len(struct) <> 0:
        initializeStruct = """={0};"""
    encodeFunction_declaration = build_struct_encode_function_4_cpp_declaration(structName)        
    encodeFunction_definition = build_struct_encode_function_4_cpp_definition(structName)
    
    global g_encoding_function_decl
    g_encoding_function_decl.append(encodeFunction_declaration)
    
    members_encode = string.join(map(build_member_encode_4_cpp, struct), '\n');
    return encode_template%(locals())

    
def build_encode_4_cpp_cpp():
    encode_template = """#include <Winsock2.h>
#include "protocols.h"
#pragma   comment(   lib,   "ws2_32.lib"   ) 

%(encodes)s

"""
    global g_struct_dict
    encodes = string.join(map(build_struct_encode_4_cpp, g_struct_name_list), '\n')
    return encode_template%(locals())

def build_struct_decode_function_4_cpp_definition(structName):
    return """__declspec(dllexport) int decode_%(structName)s(%(structName)s& st, unsigned char* pSrc, unsigned int bufLength )"""%(locals())

def build_struct_decode_function_4_cpp_declaration(structName):
    return """extern "C" int __cdecl decode_%(structName)s(%(structName)s& st, unsigned char* pSrc, unsigned int bufLength )"""%(locals())


def build_member_decode_4_cpp(member):
    type = member[0]
    name = member[1]
    count = member[2]
    refer = member[3]
    if refer <> "":
        refer = refer[2:-2]
    single_standard_type_template = """
    if (__used__ + sizeof(%(type)s) <= bufLength)
    {
        %(type)s* __i__ = (%(type)s *)(pSrc + __used__);
        st.%(name)s = %(ntoh_)s(*__i__);
        __used__ += sizeof(%(type)s);
    }
    else
    {
        return -1;
    }
"""
    array_bytes_template = """
    {
        %(check_count)s
        if (__used__ + %(for_limit)s <= bufLength)
        {
            memcpy(st.%(name)s, pSrc+__used__, %(for_limit)s);
            __used__ += %(for_limit)s;
        }
        else
        {
            return -1;
        }
    }
"""
    array_standard_type_template = """
    {
        %(check_count)s
        if (__used__ + sizeof(st.%(name)s[0]) * %(for_limit)s <= bufLength)
        {
            for(unsigned int i=0; i<%(for_limit)s; ++i)
            {            
                %(type)s* __i__ = (%(type)s *)(pSrc + __used__);
                st.%(name)s[i] = %(ntoh_)s(*__i__);
                __used__ += sizeof(%(type)s);
            }
        }
        else
        {
            return -1;
        }
    }
"""
    array_struct_type_template = """
    {
        %(check_count)s
        for (unsigned i=0; i<%(for_limit)s; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_%(type)s(st.%(name)s%(array_ptr)s, pSrc+__used__, bufLength-__used__);
            if (__r__>0)
            {
                __used__ += __r__;
            }
            else
            {
                return -1;
            }
        }
    }
"""
    string_type_template = """
    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.%(name)s, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }

"""
    for_limit = "%(count)s"%(locals())
    if count == "":
        for_limit = "1"
    if refer <> "":
        for_limit = "st.%(refer)s"%(locals())

    check_count = ""
    if count <> "" and refer <> "":
        check_count = """
        if (st.%(refer)s > %(count)s)
        {
            return -1;
        }"""%(locals())
    if isMemberNumber(member):
        ntoh_ = get_ntoh_by_type(type)
        if ntoh_ == None:
            raise ValueError('build struct error not found the definition of: %(member)r' % locals())
        #基本类型
        if count <> "":
            #bytes
            if type == "unsigned char":
                return array_bytes_template%(locals())
            #其他数组
            else:
                return array_standard_type_template%(locals())
        else:
        #非数组
            return single_standard_type_template%(locals())
    elif isMemberString(member):
        return string_type_template%(locals())
    elif isMemberStruct(member):
        array_ptr = ""
        if count <> "":
            array_ptr = "[i]"
        return array_struct_type_template%(locals())

def build_struct_decode_4_cpp(structName):
    global g_struct_dict
    struct = g_struct_dict.get(structName, None)
    if struct == None:
        raise ValueError('build build_encode not found the definition of: %(structName)s' % locals())
    
    decode_template = """
%(decodeFunction_definition)s
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    %(members_encode)s

    return __used__;
}
"""
    initializeStruct = ""
    if len(struct) <> 0:
        initializeStruct = """={0};"""
    decodeFunction_declaration = build_struct_decode_function_4_cpp_declaration(structName)
    decodeFunction_definition = build_struct_decode_function_4_cpp_definition(structName)
    
    global g_decoding_function_decl
    g_decoding_function_decl.append(decodeFunction_declaration)
    
    members_encode = string.join(map(build_member_decode_4_cpp, struct), '\n');
    return decode_template%(locals())

def build_decode_4_cpp_cpp():
    decode_template = """#include <Winsock2.h>
#include "protocols.h"
#pragma   comment(   lib,   "ws2_32.lib"   ) 

%(decodes)s

"""
    global g_struct_dict
    decodes = string.join(map(build_struct_decode_4_cpp, g_struct_name_list), '\n')
    return decode_template%(locals())

    
def build_encoding_4_cpp_h():
    encode_template = """#ifndef __PROTOCOLENCODE_EXTERN_CPP_H__
#define    __PROTOCOLENCODE_EXTERN_CPP_H__

#include <string>
#include <stdio.h>
#include "protocols.h"
using namespace std;

%(encodeFunctions)s;

#endif    //__PROTOCOLENCODE_EXTERN_CPP_H__
"""
    global g_encoding_function_decl
    encodeFunctions = string.join(g_encoding_function_decl, ";\n")
    return encode_template%(locals())

def build_decoding_4_cpp_h():
    encode_template = """#ifndef __PROTOCOLDECODE_EXTERN_CPP_H__
#define    __PROTOCOLDECODE_EXTERN_CPP_H__

#include <string>
#include <stdio.h>
#include "protocols.h"
using namespace std;

%(encodeFunctions)s;

#endif    //__PROTOCOLDECODE_EXTERN_CPP_H__
"""
    global g_decoding_function_decl
    encodeFunctions = string.join(g_decoding_function_decl, ";\n")
    return encode_template%(locals())


#def parseHFile(filename):
#    global g_enum_dict 
#    g_enum_dict = {}
#    global g_decoding_function_decl
#    g_decoding_function_decl = []
#    global g_encoding_function_decl
#    g_encoding_function_decl = []
#    f = open(filename, 'r')
#    filestr = f.read()
#    filestr = string.replace(filestr, "\n", " ")
#    filestr = string.replace(filestr, "\t", " ")
#    #print [filestr, ]
#    parseCppStruct(filestr)
#    parseCppEnum(filestr)
#
#    
#    w = open('../Common/ProtocolExtern/protocolEncode4cpp_extern.cpp', 'w')
#    w.write(build_encode_4_cpp_cpp())
#    w.close()
#    
#    w = open('../Common/ProtocolExtern/protocolEncode4cpp_extern.h', 'w')
#    w.write(build_encoding_4_cpp_h())
#    w.close()
#
#    w = open('../Common/ProtocolExtern/protocolDecode4cpp_extern.cpp', 'w')
#    w.write(build_decode_4_cpp_cpp())
#    w.close()
#    
#    w = open('../Common/ProtocolExtern/protocolDecode4cpp_extern.h', 'w')
#    w.write(build_decoding_4_cpp_h())
#    w.close()
#    print "OK"
#
#def main():
#    parseHFile("../Common/Protocols/protocols.h")

