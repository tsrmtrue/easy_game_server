# -*- coding: gbk -*-

import re
import string

#生成内存中的dict
g_struct_dict = {}
"""
{
"SInsert_role_new_roleinfo":{["rolename","char",32], ["pysAttack","int"]},
}
"""
g_enum_dict = {}
"""
{
EFightTargetAction:[E_HP_ADD,E_HP_DEC,E_ANGER_ADD,E_DEAD,],
}
"""
g_struct_name_list = []

def parseCppStructName(cppStructStr):
    pat = re.compile('[.]*struct[ ]+(\w+)[ ]*{([^{}]*)};[.]*')
    result = pat.findall(cppStructStr)
    #print result
    return result

def parseCppStructMember(members):
    pat = re.compile('[.]*(\w+[ A-Za-z]+\w+)[ ]+(\w+)[[]?(\d*)(/\*\w+\*/)?[]]?;[.]*')
    result = pat.findall(members)
    #print result
    return result

def parseCppEnumName(cppStructStr):
    pat = re.compile('[.]*enum[ ]+(\w+)[ ]*{([^{}]*)};[.]*')
    result = pat.findall(cppStructStr)
    #print result
    return result

def parseCppGetAllEnum(cppStructStr):
    pat = re.compile('[.]*(enum[^}]*};)[.]*')
    result = pat.findall(cppStructStr)
    #print result
    return result

def parseCppEnumValue(members):
    pat = re.compile('[.]*[ ]+(\w+[ A-Za-z]+\w+)[ ]*(=[\-]?[\da-fA-FXx]+)?,[ ]*(//\w+)?[.]*')#with msgid struct map
    #pat = re.compile('[.]*[ ]+(\w+[ A-Za-z]+\w+)[ ]*(=[\da-fA-FXx]+)?,[.]*')#without
    result = pat.findall(members)
    #print result
    #print members
    return result


#parseCppStructName(struct_str)

#parseCppStructMember("     char rolename[32];     int pysAttack; ")

def parseCppStruct(cppStructStr):
    global g_struct_dict 
    global g_struct_name_list
    structs = parseCppStructName(cppStructStr)
    for struct in structs:
        name = struct[0]
        # print name
        members = parseCppStructMember(struct[1])
        g_struct_dict[name] = members
        if name not in g_struct_name_list:
            g_struct_name_list.append(name)

def parseCppEnum(cppStructStr):
    global g_enum_dict 
    structs = parseCppEnumName(cppStructStr)
    for struct in structs:
        name = struct[0]
        members = parseCppEnumValue(struct[1])
        g_enum_dict[name] = members

#得到宏定义的数字值
def getNumber(count):
    return string.atoi(count)


#生辰lua中的table对象
g_int_type = ['int', 'unsigned int', 'short', 'unsigned short', 'long', 'unsigned long long', 'unsigned char']
g_char_type = ['char', ]

def isMemberNumber(member):
    global g_int_type
    global g_char_type
    if member[0] in g_int_type:
        return True
    if member[0] in g_char_type and member[2]=="":
        return True
    return False
    
def isMemberString(member):
    global g_char_type
    return member[0] in g_char_type and member[2]<>""

def isMemberStruct(member):
    global g_struct_dict
    return g_struct_dict.get(member[0], None) <> None

g_enum_value_list = []
g_enum_value_dict = {}

def parseEnumValue(enumlist):
    global g_enum_value_list
    global g_enum_value_dict
    autovalue=0
    for i in range(len(enumlist)):
        name = enumlist[i][0]
        value = enumlist[i][1]
        if value == "":
            value=autovalue
            autovalue += 1
        else:
            value=value[1:]
            if value[:2] == "0x":
                autovalue = int(value[2:], 16)+1
            else:
                autovalue = int(value)+1
        g_enum_value_list.append((name, value))
        g_enum_value_dict[name] = value


def parseEnumValueAll():
    global g_enum_dict
    map(parseEnumValue, g_enum_dict.values())
def buildEnumValue(enumlist):
    str = ""
    autovalue=0
    for i in range(len(enumlist)):
        name = enumlist[i][0]
        value = enumlist[i][1]
        if value == "":
            value=autovalue
            autovalue += 1
        else:
            value=value[1:]
            if value[:2] == "0x":
                autovalue = int(value[2:], 16)+1
            else:
                autovalue = int(value)+1
        str += "%(name)s=%(value)s\n"%(locals())
    return str

def buildEnumValueString():
    global g_enum_dict
    strEnum = string.join(map(buildEnumValue, g_enum_dict.values()), '\n')
    if strEnum == None:
        return ""
    return strEnum


