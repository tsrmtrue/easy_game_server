# -*- coding: utf-8 -*-
from parseProtocolXmlFile_lib import *
from parse_h_struct import *

def buildLocalType():
    global g_datatype_map
    global g_datatype_lst
    
    g_datatype_map["char"] = ("char","1","b")
    g_datatype_lst.append(("char","1","b"))
    
    g_datatype_map["unsigned char"] = ("unsigned char","1","B")
    g_datatype_lst.append(("unsigned char","1","B"))
    
    g_datatype_map["short"] = ("short","2","h")
    g_datatype_lst.append(("short","2","h"))
    
    g_datatype_map["unsigned short"] = ("unsigned short","2","H")
    g_datatype_lst.append(("unsigned short","2","H"))
    
    g_datatype_map["int"] = ("int","4","i")
    g_datatype_lst.append(("int","4","i"))
    
    g_datatype_map["unsigned int"] = ("unsigned int","4","I")
    g_datatype_lst.append(("unsigned int","4","I"))

    g_datatype_map["long"] = ("long","4","l")
    g_datatype_lst.append(("long","4","l"))
    
    g_datatype_map["unsigned long"] = ("unsigned long","4","L")
    g_datatype_lst.append(("unsigned long","4","L"))
    
    g_datatype_map["long long"] = ("long long","8","q")
    g_datatype_lst.append(("long long","8","q"))
    
    g_datatype_map["unsigned long long"] = ("unsigned long long","8","Q")
    g_datatype_lst.append(("unsigned long long","8","Q"))

    g_datatype_map["float"] = ("float","4","f")
    g_datatype_lst.append(("float","4","f"))
    
    g_datatype_map["double"] = ("double","4","d")
    g_datatype_lst.append(("double","4","d"))
    
    g_datatype_map["string"] = ("string","1","s")
    g_datatype_lst.append(("string","1","s"))

def translateHStruct2pylib():
    global g_type_map
    global g_type_list
    global g_struct_dict
    global g_struct_name_list
    for name in g_struct_name_list:
        s = g_struct_dict[name]
        memberList = []
        for member in s:
            _d ={}
            _d["name"] = member[1]
            _d["type"] = member[0]
            _d["count"] = member[2]
            refer = member[3]
            if refer <> "":
                refer = refer[2:-2]
            _d['refer'] = refer
            memberList.append(_d)
        g_type_map[name] = memberList
        g_type_list.append((name, memberList))


def build_all_enum_py():
    all_enum_template = """# -*- coding: utf8 -*-
#generated automatically,do NOT change manually
%(enums)s
"""
    global g_enum_dict
    enums = string.join(map(buildEnumValue, g_enum_dict.values()), '\n')
    return (all_enum_template%(locals()))


def buildMsgId2StructMap(protocolEnum="EProtocolId"):
    global g_enum_dict
    global g_protocol_list
    global g_protocol_list_list
    global g_enum_value_dict
    p = g_enum_dict.get(protocolEnum, None)
    if p != None:
        for member in p:
            if member[2] <> "":
                name = member[0]
                value = g_enum_value_dict.get(name, None)
                if value == None:
                    raise TypeError("string count empty")
                value = "%r"%(value)
                struct = member[2][2:]
                protocol = {}
                protocol["name"] = name
                protocol["value"]   = value
                protocol["struct"] = struct
                g_protocol_list.append(protocol)
                g_protocol_list_list.append([name,value,struct])
                #print protocol
            

def parseAndBuild(hfile, moduleName="", protocolEnum="EProtocolId", relativePath=""):
    f = open(hfile, 'r')
    filestr = f.read()
    filestr = string.replace(filestr, "\n", " ")
    filestr = string.replace(filestr, "\t", " ")   #windows  \t  ubuntu \r
    #print [filestr, ]
    parseCppStruct(filestr)
    parseCppEnum(filestr)
    parseEnumValueAll()

    global g_enum_dict 
    # print g_enum_dict 
    global g_enum_value_dict
    global g_enum_value_list
    global g_define_map
    global g_define_list


    translateHStruct2pylib()
    buildMsgId2StructMap(protocolEnum)
    fun_test_print_all()
    # print "g_enum_value_dict"
    # print g_enum_value_dict
    g_define_list = g_enum_value_list
    g_define_map = g_enum_value_dict
    buildLocalType()
    fun_addAssignmentAll()
    fun_addAssignment()
    fun_buildPyStruct_namedlist("test_namedlist%(moduleName)s.py"%(locals()))
    fun_buildCodingFun_namedlist("test_namedlist_coding%(moduleName)s"%(locals()), "0_001", "test_namedlist%(moduleName)s"%(locals()))
    fun_test_print_all()


    w = open('protocol_enums_%(moduleName)s.py'%(locals()), 'w')
    w.write(build_all_enum_py())
    w.close()

    
    print "OK"

#def main():
#    parseAndBuild("../Common/Protocols/protocols.h")
#    

