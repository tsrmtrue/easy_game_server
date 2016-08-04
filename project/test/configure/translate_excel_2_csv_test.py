#-*- coding:utf8 -*-
# 联系作者 qq 150237442
# 需要安装xlrd，请自行安装

import sys
sys.path.append('../../../lib/convert_excel_2_cvs')
import translate_excel_2_csv

def translateExcelAndParse(excelFilePath, targetPath):
    
    translate_excel_2_csv.translateExcel2Csv(excelFilePath+'服务器配置.xls', targetPath+"server_configure_utf8.csv")
    translate_excel_2_csv.parseFile(targetPath+'server_configure_utf8.csv', 'ServerConfig')


    translate_excel_2_csv.writeStructHFile('ConfigureStruct.h')
    translate_excel_2_csv.writeHFile('ConfigureParser.h')
    translate_excel_2_csv.writeCppFile('ConfigureParser.cpp')



translateExcelAndParse('', '')


# translateExcelAndParse_4_cocos('../configure/配置表', '../clientResource/config')

print "OK!"

