# -*- coding: utf8 -*-
import sys
sys.path.append('../../../lib/db_handle')

import parse_sql_base

#这里的sql语句是从数据库得到的建表语句，可以是在图形界面完成建表，然后直接提取sql语句，放在这里以后，直接生成c++的结构

create_roleinfo_biogame = """
CREATE TABLE `role` (
  `userid` INTEGER(11) UNSIGNED NOT NULL AUTO_INCREMENT,
  `accountid` INTEGER(11) UNSIGNED NOT NULL ,  
  `rolename` VARCHAR(64) COLLATE utf8_general_ci NOT NULL DEFAULT '',
  `professionId` INTEGER(11) UNSIGNED DEFAULT '100001' COMMENT 'see the document for profession',
  `money` INTEGER(11) UNSIGNED DEFAULT '0' COMMENT 'money',
  `diamond` INTEGER(11) UNSIGNED DEFAULT '0' COMMENT 'diamond,rmb',
  `vigor` INTEGER(11) UNSIGNED DEFAULT '0' COMMENT 'vigor for role ',
  `isInit` INTEGER(11) DEFAULT '0' COMMENT 'if it is 0,it should be initialized',
  `loginCount` INTEGER(11) UNSIGNED DEFAULT '0' COMMENT 'login count',
  `lastLogoffTime` INTEGER(11) UNSIGNED DEFAULT '0' COMMENT 'lastLogoffTime',
  `currentGuid` INTEGER(11) UNSIGNED DEFAULT '2' COMMENT 'current guid for all objects owned by one role',
  `todayFubenRecord` BLOB COMMENT 'today hard Fuben play record',
  `todayPrizeRecord` BLOB COMMENT 'today get prize record, shall be refresh everyday',
  `prizeRecord` BLOB COMMENT 'obtain prize record,',
  `taskFinished` BLOB COMMENT 'finished task record',
  `taskCurrent` BLOB COMMENT 'detail info of the undergoing task',
  `misc` BLOB COMMENT 'misc info  ,', 
  `friends` BLOB DEFAULT NULL COMMENT 'friend info  ,', 
  `friendsApply` BLOB DEFAULT NULL COMMENT 'friend apply info  ,',
  `package` BLOB DEFAULT NULL COMMENT 'all items,',
  `titles` BLOB DEFAULT NULL COMMENT 'all titles ,',
  `footmark` BLOB DEFAULT NULL COMMENT 'recent things happened ,',  
  `paremeterNow` BLOB DEFAULT NULL COMMENT 'life record of role  ,',
  `paremeterMin` BLOB DEFAULT NULL COMMENT 'life record of role  ,',
  `paremeterMax` BLOB DEFAULT NULL COMMENT 'life record of role  ,',

  UNIQUE KEY `userid` (`userid`),
  UNIQUE KEY `idx_rolename` (`rolename`),
  KEY `idx_accountid` (`accountid`)
)ENGINE=MyISAM,
AUTO_INCREMENT=1 CHARACTER SET 'utf8' COLLATE 'utf8_general_ci';
"""

g_sql_map = {} #{tblname:create_table_sql}}

g_sql_map['role'] = create_roleinfo_biogame


parse_sql_base.set_sql_map(g_sql_map)

#数据库操作
#1  用mac地址登录,试玩用户
#2  注册帐号密码,和mac地址绑定,检查是否已经登录
#3  用帐号密码登录,试玩用户
#4  用帐号密码mac地址登录,正常玩家

def main(sqlHelpHFile):
    str = ''
    str += parse_sql_base.build_sql_by_createsql(['role'])
    
    #-----------------------角色数据
    #用户名测试
    str += parse_sql_base.build_select_sql_all_by_field_list(['rolename'], 'role', 'check_rolename_exist')
    #创建角色,根据mac地址对应的account创建角色
    str += parse_sql_base.build_insert_sql_by_field_list(['rolename', 'accountid', 'professionId', ], 'role','create_role_by_accountid')
    #创建角色,使用通行证登录的创建角色
    str += parse_sql_base.build_insert_sql_by_field_list(['rolename', 'accountid', 'professionId', ], 'role','create_role_by_passport')
    #简单帐号验证成功以后，使用accountid, userid登陆 
    str += parse_sql_base.build_select_sql_all_by_field_list(['accountid', 'userid'], 'role', 'get_role_by_accountid_userid')
    #简单帐号验证成功以后，使用accountid创建,并且第一次获得
    str += parse_sql_base.build_select_sql_all_by_field_list(['accountid',], 'role', 'get_role_by_accountid_first')
    #记录回数据库
    str += parse_sql_base.build_update_sql_by_field_list([ "accountid", "rolename", "professionId", "money", "diamond", "vigor", "isInit", "loginCount", "lastLogoffTime", "todayFubenRecord", "todayPrizeRecord", "prizeRecord", "misc", "friends", "friendsApply", "package", "titles", "footmark", 'taskFinished', 'taskCurrent', 'currentGuid', 'paremeterMin', 'paremeterMax', 'paremeterNow' ], ['userid',], 'role','save_role_by_userid')
    #使用userid登陆,
    str += parse_sql_base.build_select_sql_all_by_field_list(['userid',], 'role', 'get_role_by_userid')
    #获得最大的userid
    str += parse_sql_base.build_limit_select_sql_all_by_field_list([], 'role', "get_max_userid_limit", "userid", "1", True)
    #插入现成的角色
    #str += build_insert_sql_by_field_list(["accountid", 'challengeRecord', 'currentGuid', 'currentArrayId', 'diamond', 'exp', "equipmentStrengthen", 'exploit', 'expTotal', 'isInit',  'itemsPacket', "loginCount", 'level', "misc", 'money', 'mates', 'prizeRecord', "professionId", 'popularity', 'randomRecruit', 'rolename', "showLevel", 'starlevel', 'taskFinished', 'taskCurrent', 'todayPrizeRecord', 'todayFubenRecord', 'vigor', "userid", 'wingPage', 'wingCompoundStar', 'friends', 'friendsApply', 'playerTalks','nobility', 'lastLogoffTime','scenesdiscuss','coachs','roleClubCondition','roleIntoGameData','arrayEquipment','refreshItemArray','playerGuideRecord'], 'role','insert_role_all')
    #获取快照
    str += parse_sql_base.build_select_sql_by_field_list(['userid', 'professionId', 'rolename', 'lastLogoffTime', "misc", "friends"], [], "role", "get_all_role_snapshot")
    #根据mac地址获取角色列表
    str += parse_sql_base.build_select_sql_by_field_list_limit(["userid", "rolename"], ["accountid"], "role", "get_rolelist_by_accountid", "userid", "10", True)
    #角色改名字
    str += parse_sql_base.build_update_sql_by_field_list([ 'rolename', ], ['userid',], 'role','update_role_change_rolename_by_userid')
    
           
    str += "\n\n"
    str += parse_sql_base.build_wrap_struct("")
    str += parse_sql_base.build_operation_enum("")
    #test==============
    
    file_template = """#ifndef PNL_DBSERVER_SQL_OPERATION_HLP_H
#define PNL_DBSERVER_SQL_OPERATION_HLP_H
/*made automatically,do NOT change manually*/
#include "pnl_protocol.h"
%s

#endif
"""
    w = open(sqlHelpHFile, "w")
    #w = open('testSqlOperationHlp.h', 'w')
    w.write(file_template%str)
    w.close()
    print "OK"
    #print file_template%str

    
main('SqlOperationHlp_PNL.h')
