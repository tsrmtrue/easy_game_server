#-*- coding:utf8 -*-
# 联系作者 qq 150237442
# 需要安装xlrd，请自行安装
import xlrd
import string
import codecs
import types
import sys

def translateValue2String(value):
    #print type(value.value)
    if type(value.value) is types.UnicodeType:
        s = "%s"%(value.value.encode("utf8"))
        if s.find(",") <> -1:
            #print s
            s = s.replace(",", "\xef\xbc\x8c")
            #print s
        if s.find("\n") <> -1:
            print "unicode found \\n"
            print s
            s = s.replace("\n", "")
            print s
        return s
    if types.FloatType == type(value.value):
        return "%d"%(value.value)
    if types.StringType == type(value.value):
        s = "%s"%(value.value)
        if s.find(",") <> -1:
            #print s
            s = s.replace(",", "\xef\xbc\x8c")
            #print s
        if s.find("\n") <> -1:
            print "string found \\n"
            print s
            s = s.replace("\r\n", "")
            print s
        return s
    

def translateSheet2String(sheet):
    l = list()
    for r in range(0, sheet.nrows):
        row = sheet.row(r)
        #print row
        l.append(string.join(map(translateValue2String, row), ",").replace("''", ""))
    return string.join(l, "\n")

def translateExcel2Csv(excelPath, csvPath, sheet="Sheet1"):
    try :
        #print codecs.getdecoder(excelPath)
        p1 = excelPath.decode("utf8").encode("gbk")
#        print p1
        workbook = xlrd.open_workbook(p1)
        sheet = workbook.sheet_by_name(sheet)
        w = open(csvPath, 'w')
        s=translateSheet2String(sheet)
#        print s
        
        w.write("\xEF\xBB\xBF"+s+"\x0a")
        w.close()
    except:
        print "error"
        pass

from build_cpp_config import *
