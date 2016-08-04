#-*- coding:utf8 -*-
import string
import re

g_structs = {}#strucname:memberlist

#生成结构
def getMemberList(fieldstr):
    memberlist = string.split(fieldstr, '，')
    #print fieldstr
    result = []
    for l in memberlist:
        #print "l is ", l
        if l[-1] == ",":
            print "hit"
            print l
            l = l[:-1]        
        if l[-2] == ",":
            l = l[:-2]
        pat = re.compile('[\,]?([^\,]*)\((\w+):(\w+):(\d*)\)')
        t = pat.findall(l)
        membercount = len(string.split(l, ','))
        if membercount <> len(t):
            print "membercount not equal ", membercount, "   ", len(t)
            print l
            print l[-1]
            print t
            
        r = []
        for member in t:
            m = list(member[1:])
            # print "nameis: //",member[0]
            s = "%s"%(member[0]) #.encode("utf8")
            #print "s is ",s
            m.append(s)
            #print "m is ",m
            r.append(m)
            
        result.append(r)
    #print result
    return result[0]

g_type_map={
            'int':'int',
            'str':'char',
            'enum':'int',}



def buildMemberDefine(member):
    name = member[0]
    type = g_type_map.get(member[1], None)
    if type == None:
        raise ValueError('build struct error not found the definition of: %(name)s %(member)r' % locals())

    count = member[2]
    comment = member[3]
    arrayindex = ""
    if count<>"":
        arrayindex = '[%s]'%count
    return '    %(type)s %(name)s%(arrayindex)s; //%(comment)s'%(locals())
    
def buildCppStruct(structname, memberlist):
    cppStruct_template = """
struct S%(name)s
{
%(members)s
};
"""
    name = structname
    #print memberlist
    members = string.join(map(buildMemberDefine, memberlist), '\n')
    return cppStruct_template%(locals())
    
def getCppStruct(structname,memberlist):
    return buildCppStruct(structname, memberlist)

def buildAllCppStruct():
    global g_structs
    str = ""
    for name in g_structs.keys():
        str += buildCppStruct(name, g_structs[name])
    return str

def writeStructHFile(wfilename):
    configure_hfile_template = """#ifndef __CONFIGURE_STRUCT_H__
#define __CONFIGURE_STRUCT_H__

%(structs)s

#endif 
"""
    structs=""
    structs  += buildAllCppStruct()
    w = open(wfilename, 'w')
    w.write(configure_hfile_template%(locals()))
    w.close()
    
#生成parse的hd文件
def buildParseFunction(structname):
    return "bool parseS%(structname)s(const char* pStr, S%(structname)s& st)"%(locals())

def buildParseFileFunction(structname):
    return "bool parseS%(structname)sFile(const char* pFilename, std::vector<S%(structname)s>& sts)"%(locals())
    
def buildHFile():
    global g_structs
    hfile_template = """#ifndef __CONFIGURE_PARSER_H__
#define __CONFIGURE_PARSER_H__
#include <vector>
#include "ConfigureStruct.h"

%(parsefunctions)s
%(parsefilefunctions)s
#endif"""
    parsefunctions = string.join(map(buildParseFunction, g_structs.keys()), ';\n') + ';\n'
    parsefilefunctions = string.join(map(buildParseFileFunction, g_structs.keys()), ';\n') + ';\n'
    return hfile_template%(locals())
    
def writeHFile(wfilename):
    w = open(wfilename, 'w')
    w.write(buildHFile())
    w.close()
    
#生成parse的cpp文件



def buildParseMember(member):
    parse_member_template = """
    foundIndex = s.find(',', start);
    if (foundIndex != std::string::npos)
    {
        %(assignMember)s
        start = foundIndex+1;
    }
    else
    {
        return false;
    }
"""
    name = member[0]
    type = member[1]
    count = member[2]
    if type == "int":
        assignMember = 'st.%(name)s = atoi(s.substr(start, foundIndex-start).c_str());'%(locals())
    elif type == "str":
        assignMember = 'strncpy(st.%(name)s, s.substr(start, foundIndex-start).c_str(), foundIndex - start);'%(locals())
    elif type == "enum":
        assignMember = 'st.%(name)s = getEnumValue(s.substr(start, foundIndex-start));'%(locals())
    return parse_member_template%(locals())


def buildParseCpp(structname,memberlist):
    parse_cpp_template = """
%(parsefunction)s
{
    memset(&st, 0, sizeof(st));
    std::string s = pStr;
    size_t start = 0;
    size_t foundIndex = 0;

%(parseMembers)s
    return true;
}
"""
    parsefunction = buildParseFunction(structname)
    parseMembers = string.join(map(buildParseMember, memberlist), '\n')
    return parse_cpp_template%(locals())

def buildParseFileCpp(structname,memberlist):
    parsefile_cpp_template = """
%(parsefilefunction)s
{
    ifstream inf(pFilename);
    if (!inf.is_open())
    {
        return false;
    }
    char temp[20480] = "";
    inf.getline(temp, sizeof(temp));
    while (!inf.eof())
    {
        memset(temp, 0, sizeof(temp));
        inf.getline(temp, sizeof(temp));
        temp[strlen(temp)]=',';
        S%(structname)s st = {0};
        if (parseS%(structname)s(temp, st))
        {
            sts.push_back(st);
        }
    }
    inf.close();
    return true;
}
"""
    parsefilefunction = buildParseFileFunction(structname)
    return parsefile_cpp_template%(locals())

def buildParseFileCpp4COCOS2dx(structname,memberlist):
    parsefile_cpp_template = """
%(parsefilefunction)s
{

    unsigned long size = 0;
    unsigned char *pData = CCFileUtils::sharedFileUtils()->getFileData(pFilename, "rb", &size);
    unsigned char temp[20480] = "";
    unsigned long start = 0;
    unsigned long readData = 0;
    start = getLine(pData, size, start, temp, sizeof(temp), readData);
    start = getLine(pData, size, start, temp, sizeof(temp), readData);
    while(readData > 0)
    {
        temp[readData]=',';
        S%(structname)s st = {0};
        if (parseS%(structname)s((const char*)temp, st))
        {
            sts.push_back(st);
        }
        memset(temp, 0, sizeof(temp));
        start = getLine(pData, size, start, temp, sizeof(temp), readData);
    }
    CC_SAFE_DELETE_ARRAY(pData);

    return true;
}
"""
    parsefilefunction = buildParseFileFunction(structname)
    return parsefile_cpp_template%(locals())


def buildAllParseCpp():
    global g_structs
    str = ""
    for name in g_structs.keys():
        str += buildParseCpp(name, g_structs[name])
    return str

def buildAllParseFileCpp(isCocos=False):
    global g_structs
    str = ""
    for name in g_structs.keys():
        if isCocos==True :
            str += buildParseFileCpp4COCOS2dx(name, g_structs[name])
        else:
            str += buildParseFileCpp(name, g_structs[name])
    return str



def writeCppFile(wfilename, isCocos=False):
    cppfile_template="""#include "ConfigureParser.h"
#include <string>
#include <fstream>
#include "ConfigureEnumMap.h"
#include <string.h>
#include <stdlib.h>
using namespace std;
%(parses)s
%(parsefiles)s
"""
    if isCocos == True:
        cppfile_template="""#include "ConfigureParser.h"
#include <string>
#include <stdlib.h>
#include "ConfigureEnumMap.h"
#include "configure_help.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
%(parses)s
%(parsefiles)s
"""
    parses = buildAllParseCpp()
    parsefiles = buildAllParseFileCpp(isCocos)
    w = open(wfilename, 'w')
    w.write(cppfile_template%(locals()))
    w.close()
    #print cppfile_template%(locals())

#-----------------------------
def parseFile(filename, structname):
    global g_structs
    f = open(filename, 'r')
    filestr = f.readline()
    memberlist = getMemberList(filestr)
    g_structs[structname] = memberlist

def clean_temp():
    global g_structs
    g_structs = {}

