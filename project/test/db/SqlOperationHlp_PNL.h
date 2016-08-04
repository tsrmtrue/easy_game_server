#ifndef PNL_DBSERVER_SQL_OPERATION_HLP_H
#define PNL_DBSERVER_SQL_OPERATION_HLP_H
/*made automatically,do NOT change manually*/
#include "pnl_protocol.h"

/****************************************************************************/
#define CREATE_TABLE_ROLE  "\
CREATE TABLE role (\
  userid INTEGER(11) UNSIGNED NOT NULL AUTO_INCREMENT,\
  accountid INTEGER(11) UNSIGNED NOT NULL ,  \
  rolename VARCHAR(64) COLLATE utf8_general_ci NOT NULL DEFAULT '',\
  professionId INTEGER(11) UNSIGNED DEFAULT '100001' COMMENT 'see the document for profession',\
  money INTEGER(11) UNSIGNED DEFAULT '0' COMMENT 'money',\
  diamond INTEGER(11) UNSIGNED DEFAULT '0' COMMENT 'diamond,rmb',\
  vigor INTEGER(11) UNSIGNED DEFAULT '0' COMMENT 'vigor for role ',\
  isInit INTEGER(11) DEFAULT '0' COMMENT 'if it is 0,it should be initialized',\
  loginCount INTEGER(11) UNSIGNED DEFAULT '0' COMMENT 'login count',\
  lastLogoffTime INTEGER(11) UNSIGNED DEFAULT '0' COMMENT 'lastLogoffTime',\
  currentGuid INTEGER(11) UNSIGNED DEFAULT '2' COMMENT 'current guid for all objects owned by one role',\
  todayFubenRecord BLOB COMMENT 'today hard Fuben play record',\
  todayPrizeRecord BLOB COMMENT 'today get prize record, shall be refresh everyday',\
  prizeRecord BLOB COMMENT 'obtain prize record,',\
  taskFinished BLOB COMMENT 'finished task record',\
  taskCurrent BLOB COMMENT 'detail info of the undergoing task',\
  misc BLOB COMMENT 'misc info  ,', \
  friends BLOB DEFAULT NULL COMMENT 'friend info  ,', \
  friendsApply BLOB DEFAULT NULL COMMENT 'friend apply info  ,',\
  package BLOB DEFAULT NULL COMMENT 'all items,',\
  titles BLOB DEFAULT NULL COMMENT 'all titles ,',\
  footmark BLOB DEFAULT NULL COMMENT 'recent things happened ,',  \
  paremeterNow BLOB DEFAULT NULL COMMENT 'life record of role  ,',\
  paremeterMin BLOB DEFAULT NULL COMMENT 'life record of role  ,',\
  paremeterMax BLOB DEFAULT NULL COMMENT 'life record of role  ,',\
\
  UNIQUE KEY userid (userid),\
  UNIQUE KEY idx_rolename (rolename),\
  KEY idx_accountid (accountid)\
)ENGINE=MyISAM,\
AUTO_INCREMENT=1 CHARACTER SET 'utf8' COLLATE 'utf8_general_ci';\
"
struct Sql_SelectAll_role
{
    unsigned int userid;
    unsigned int accountid;
    char rolename[64];
    unsigned int professionId;
    unsigned int money;
    unsigned int diamond;
    unsigned int vigor;
    int isInit;
    unsigned int loginCount;
    unsigned int lastLogoffTime;
    unsigned int currentGuid;
    unsigned char todayFubenRecord[None];int _current_todayFubenRecord_length;
    unsigned char todayPrizeRecord[None];int _current_todayPrizeRecord_length;
    unsigned char prizeRecord[None];int _current_prizeRecord_length;
    unsigned char taskFinished[None];int _current_taskFinished_length;
    unsigned char taskCurrent[None];int _current_taskCurrent_length;
    unsigned char misc[None];int _current_misc_length;
    unsigned char friends[None];int _current_friends_length;
    unsigned char friendsApply[None];int _current_friendsApply_length;
    unsigned char package[None];int _current_package_length;
    unsigned char titles[None];int _current_titles_length;
    unsigned char footmark[None];int _current_footmark_length;
    unsigned char paremeterNow[None];int _current_paremeterNow_length;
    unsigned char paremeterMin[None];int _current_paremeterMin_length;
    unsigned char paremeterMax[None];int _current_paremeterMax_length;
};

#define CONVERT_RECORD_ROLE_SELECTALL(RC,st) \
int _i = 0;\
autoAssign(RC,_i++,st.userid,0);\
autoAssign(RC,_i++,st.accountid,0);\
autoAssign(RC,_i++, st.rolename, sizeof(st.rolename));\
autoAssign(RC,_i++,st.professionId,0);\
autoAssign(RC,_i++,st.money,0);\
autoAssign(RC,_i++,st.diamond,0);\
autoAssign(RC,_i++,st.vigor,0);\
autoAssign(RC,_i++,st.isInit,0);\
autoAssign(RC,_i++,st.loginCount,0);\
autoAssign(RC,_i++,st.lastLogoffTime,0);\
autoAssign(RC,_i++,st.currentGuid,0);\
getFieldLength(RC, _i,(st._current_todayFubenRecord_length));autoAssignChunck(RC,_i++, st.todayFubenRecord, (st._current_todayFubenRecord_length));\
getFieldLength(RC, _i,(st._current_todayPrizeRecord_length));autoAssignChunck(RC,_i++, st.todayPrizeRecord, (st._current_todayPrizeRecord_length));\
getFieldLength(RC, _i,(st._current_prizeRecord_length));autoAssignChunck(RC,_i++, st.prizeRecord, (st._current_prizeRecord_length));\
getFieldLength(RC, _i,(st._current_taskFinished_length));autoAssignChunck(RC,_i++, st.taskFinished, (st._current_taskFinished_length));\
getFieldLength(RC, _i,(st._current_taskCurrent_length));autoAssignChunck(RC,_i++, st.taskCurrent, (st._current_taskCurrent_length));\
getFieldLength(RC, _i,(st._current_misc_length));autoAssignChunck(RC,_i++, st.misc, (st._current_misc_length));\
getFieldLength(RC, _i,(st._current_friends_length));autoAssignChunck(RC,_i++, st.friends, (st._current_friends_length));\
getFieldLength(RC, _i,(st._current_friendsApply_length));autoAssignChunck(RC,_i++, st.friendsApply, (st._current_friendsApply_length));\
getFieldLength(RC, _i,(st._current_package_length));autoAssignChunck(RC,_i++, st.package, (st._current_package_length));\
getFieldLength(RC, _i,(st._current_titles_length));autoAssignChunck(RC,_i++, st.titles, (st._current_titles_length));\
getFieldLength(RC, _i,(st._current_footmark_length));autoAssignChunck(RC,_i++, st.footmark, (st._current_footmark_length));\
getFieldLength(RC, _i,(st._current_paremeterNow_length));autoAssignChunck(RC,_i++, st.paremeterNow, (st._current_paremeterNow_length));\
getFieldLength(RC, _i,(st._current_paremeterMin_length));autoAssignChunck(RC,_i++, st.paremeterMin, (st._current_paremeterMin_length));\
getFieldLength(RC, _i,(st._current_paremeterMax_length));autoAssignChunck(RC,_i++, st.paremeterMax, (st._current_paremeterMax_length));



/****************************************************************************/
struct Sql_SelectAll_role_check_rolename_exist
{
    char rolename[64];
};
#define MACRO_ESCAPE_FIELDS_CHECK_ROLENAME_EXIST_ROLE(st) char _rolename[(64)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.rolename), strlen(st.rolename), _rolename, sizeof(_rolename));  

#define SELECT_SQL_ROLE_CHECK_ROLENAME_EXIST(st) "SELECT * FROM role WHERE rolename='%s'", _rolename

/****************************************************************************/
struct Sql_Insert_role_create_role_by_accountid
{
    unsigned int accountid;
    char rolename[64];
    unsigned int professionId;
};
#define INSERT_SQL_CREATE_ROLE_BY_ACCOUNTID_ROLE "INSERT INTO role (accountid,rolename,professionId) VALUES('%u','%s','%u') "
#define MACRO_ESCAPE_FIELDS_CREATE_ROLE_BY_ACCOUNTID_ROLE(st) ;char _rolename[(64)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.rolename), strlen(st.rolename), _rolename, sizeof(_rolename));;  
#define MACRO_STRUCT_FIELDS_CREATE_ROLE_BY_ACCOUNTID_ROLE(st) st.accountid,_rolename,st.professionId  

/****************************************************************************/
struct Sql_Insert_role_create_role_by_passport
{
    unsigned int accountid;
    char rolename[64];
    unsigned int professionId;
};
#define INSERT_SQL_CREATE_ROLE_BY_PASSPORT_ROLE "INSERT INTO role (accountid,rolename,professionId) VALUES('%u','%s','%u') "
#define MACRO_ESCAPE_FIELDS_CREATE_ROLE_BY_PASSPORT_ROLE(st) ;char _rolename[(64)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.rolename), strlen(st.rolename), _rolename, sizeof(_rolename));;  
#define MACRO_STRUCT_FIELDS_CREATE_ROLE_BY_PASSPORT_ROLE(st) st.accountid,_rolename,st.professionId  

/****************************************************************************/
struct Sql_SelectAll_role_get_role_by_accountid_userid
{
    unsigned int userid;
    unsigned int accountid;
};
#define MACRO_ESCAPE_FIELDS_GET_ROLE_BY_ACCOUNTID_USERID_ROLE(st) ;  

#define SELECT_SQL_ROLE_GET_ROLE_BY_ACCOUNTID_USERID(st) "SELECT * FROM role WHERE userid='%u' AND accountid='%u'", st.userid,st.accountid

/****************************************************************************/
struct Sql_SelectAll_role_get_role_by_accountid_first
{
    unsigned int accountid;
};
#define MACRO_ESCAPE_FIELDS_GET_ROLE_BY_ACCOUNTID_FIRST_ROLE(st)   

#define SELECT_SQL_ROLE_GET_ROLE_BY_ACCOUNTID_FIRST(st) "SELECT * FROM role WHERE accountid='%u'", st.accountid

/****************************************************************************/
struct Sql_Update_role_save_role_by_userid
{
    unsigned int accountid;
    char rolename[64];
    unsigned int professionId;
    unsigned int money;
    unsigned int diamond;
    unsigned int vigor;
    int isInit;
    unsigned int loginCount;
    unsigned int lastLogoffTime;
    unsigned int currentGuid;
    unsigned char todayFubenRecord[None];int _current_todayFubenRecord_length;
    unsigned char todayPrizeRecord[None];int _current_todayPrizeRecord_length;
    unsigned char prizeRecord[None];int _current_prizeRecord_length;
    unsigned char taskFinished[None];int _current_taskFinished_length;
    unsigned char taskCurrent[None];int _current_taskCurrent_length;
    unsigned char misc[None];int _current_misc_length;
    unsigned char friends[None];int _current_friends_length;
    unsigned char friendsApply[None];int _current_friendsApply_length;
    unsigned char package[None];int _current_package_length;
    unsigned char titles[None];int _current_titles_length;
    unsigned char footmark[None];int _current_footmark_length;
    unsigned char paremeterNow[None];int _current_paremeterNow_length;
    unsigned char paremeterMin[None];int _current_paremeterMin_length;
    unsigned char paremeterMax[None];int _current_paremeterMax_length;
    unsigned int userid;
};
#define MACRO_ESCAPE_FIELDS_SAVE_ROLE_BY_USERID_ROLE(st) ;char _rolename[(64)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.rolename), strlen(st.rolename), _rolename, sizeof(_rolename));;;;;;;;;;char _todayFubenRecord[(1024*50)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.todayFubenRecord), st._current_todayFubenRecord_length, _todayFubenRecord, sizeof(_todayFubenRecord));;char _todayPrizeRecord[(1024*50)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.todayPrizeRecord), st._current_todayPrizeRecord_length, _todayPrizeRecord, sizeof(_todayPrizeRecord));;char _prizeRecord[(1024*50)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.prizeRecord), st._current_prizeRecord_length, _prizeRecord, sizeof(_prizeRecord));;char _taskFinished[(1024*50)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.taskFinished), st._current_taskFinished_length, _taskFinished, sizeof(_taskFinished));;char _taskCurrent[(1024*50)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.taskCurrent), st._current_taskCurrent_length, _taskCurrent, sizeof(_taskCurrent));;char _misc[(1024*50)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.misc), st._current_misc_length, _misc, sizeof(_misc));;char _friends[(1024*50)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.friends), st._current_friends_length, _friends, sizeof(_friends));;char _friendsApply[(1024*50)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.friendsApply), st._current_friendsApply_length, _friendsApply, sizeof(_friendsApply));;char _package[(1024*50)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.package), st._current_package_length, _package, sizeof(_package));;char _titles[(1024*50)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.titles), st._current_titles_length, _titles, sizeof(_titles));;char _footmark[(1024*50)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.footmark), st._current_footmark_length, _footmark, sizeof(_footmark));;char _paremeterNow[(1024*50)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.paremeterNow), st._current_paremeterNow_length, _paremeterNow, sizeof(_paremeterNow));;char _paremeterMin[(1024*50)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.paremeterMin), st._current_paremeterMin_length, _paremeterMin, sizeof(_paremeterMin));;char _paremeterMax[(1024*50)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.paremeterMax), st._current_paremeterMax_length, _paremeterMax, sizeof(_paremeterMax));  

#define UPDATE_SQL_ROLE_SAVE_ROLE_BY_USERID "UPDATE role SET accountid='%u',rolename='%s',professionId='%u',money='%u',diamond='%u',vigor='%u',isInit='%d',loginCount='%u',lastLogoffTime='%u',currentGuid='%u',todayFubenRecord='%s',todayPrizeRecord='%s',prizeRecord='%s',taskFinished='%s',taskCurrent='%s',misc='%s',friends='%s',friendsApply='%s',package='%s',titles='%s',footmark='%s',paremeterNow='%s',paremeterMin='%s',paremeterMax='%s'  WHERE userid='%u'", st.accountid,_rolename,st.professionId,st.money,st.diamond,st.vigor,st.isInit,st.loginCount,st.lastLogoffTime,st.currentGuid,_todayFubenRecord,_todayPrizeRecord,_prizeRecord,_taskFinished,_taskCurrent,_misc,_friends,_friendsApply,_package,_titles,_footmark,_paremeterNow,_paremeterMin,_paremeterMax,st.userid

/****************************************************************************/
struct Sql_SelectAll_role_get_role_by_userid
{
    unsigned int userid;
};
#define MACRO_ESCAPE_FIELDS_GET_ROLE_BY_USERID_ROLE(st)   

#define SELECT_SQL_ROLE_GET_ROLE_BY_USERID(st) "SELECT * FROM role WHERE userid='%u'", st.userid

/****************************************************************************/
struct Sql_SelectAll_role_get_max_userid_limit
{
    
};
#define MACRO_ESCAPE_FIELDS_GET_MAX_USERID_LIMIT_ROLE(st)   

#define GET_MAX_USERID_LIMIT_LIMIT 1 
#define SELECT_SQL_ROLE_GET_MAX_USERID_LIMIT(st) "SELECT * FROM role  order by userid DESC limit 1"

/****************************************************************************/
struct Sql_Select_role_get_all_role_snapshot
{
    unsigned int userid;
    char rolename[64];
    unsigned int professionId;
    unsigned int lastLogoffTime;
    unsigned char misc[None];int _current_misc_length;
    unsigned char friends[None];int _current_friends_length;
};

#define CONVERT_RECORD_ROLE_GET_ALL_ROLE_SNAPSHOT(RC,st) \
int _i = 0;\
autoAssign(RC,_i++,st.userid,0);\
autoAssign(RC,_i++, st.rolename, sizeof(st.rolename));\
autoAssign(RC,_i++,st.professionId,0);\
autoAssign(RC,_i++,st.lastLogoffTime,0);\
getFieldLength(RC, _i,(st._current_misc_length));autoAssignChunck(RC,_i++, st.misc, (st._current_misc_length));\
getFieldLength(RC, _i,(st._current_friends_length));autoAssignChunck(RC,_i++, st.friends, (st._current_friends_length));


#define MACRO_ESCAPE_FIELDS_GET_ALL_ROLE_SNAPSHOT_ROLE(st)   

#define SELECT_SQL_ROLE_GET_ALL_ROLE_SNAPSHOT(st) "SELECT userid,rolename,professionId,lastLogoffTime,misc,friends FROM role "

/****************************************************************************/
struct Sql_Select_role_get_rolelist_by_accountid
{
    unsigned int userid;
    char rolename[64];
};

#define CONVERT_RECORD_ROLE_GET_ROLELIST_BY_ACCOUNTID(RC,st) \
int _i = 0;\
autoAssign(RC,_i++,st.userid,0);\
autoAssign(RC,_i++, st.rolename, sizeof(st.rolename));


#define MACRO_ESCAPE_FIELDS_GET_ROLELIST_BY_ACCOUNTID_ROLE(st)   

#define GET_ROLELIST_BY_ACCOUNTID_LIMIT 10 
#define SELECT_SQL_ROLE_GET_ROLELIST_BY_ACCOUNTID(st) "SELECT userid,rolename FROM role WHERE accountid='%u' order by userid DESC limit 10", 

/****************************************************************************/
struct Sql_Update_role_update_role_change_rolename_by_userid
{
    char rolename[64];
    unsigned int userid;
};
#define MACRO_ESCAPE_FIELDS_UPDATE_ROLE_CHANGE_ROLENAME_BY_USERID_ROLE(st) char _rolename[(64)*2 + 1]="";m_pMyConn->EscapeString((const char*)(st.rolename), strlen(st.rolename), _rolename, sizeof(_rolename));  

#define UPDATE_SQL_ROLE_UPDATE_ROLE_CHANGE_ROLENAME_BY_USERID "UPDATE role SET rolename='%s'  WHERE userid='%u'", _rolename,st.userid


struct SDB_Wrap
{
    int socket;//用来寻找发起的玩家
    int operateId;//操作id
    int operateType;
    int operateUserData;
    int rcCount;//返回结果的多少,0,没有结果,1,一个结果,2,二个...
    int dbErrcode;//错误值
    unsigned long long insertId;//如果是insert操作，这里是返回插入id
    unsigned int dbId;//具体连哪个db，需要有配置文件支持
    union{
        Sql_SelectAll_role st_Sql_SelectAll_role;
        Sql_SelectAll_role_check_rolename_exist st_Sql_SelectAll_role_check_rolename_exist;
        Sql_Insert_role_create_role_by_accountid st_Sql_Insert_role_create_role_by_accountid;
        Sql_Insert_role_create_role_by_passport st_Sql_Insert_role_create_role_by_passport;
        Sql_SelectAll_role_get_role_by_accountid_userid st_Sql_SelectAll_role_get_role_by_accountid_userid;
        Sql_SelectAll_role_get_role_by_accountid_first st_Sql_SelectAll_role_get_role_by_accountid_first;
        Sql_Update_role_save_role_by_userid st_Sql_Update_role_save_role_by_userid;
        Sql_SelectAll_role_get_role_by_userid st_Sql_SelectAll_role_get_role_by_userid;
        Sql_SelectAll_role_get_max_userid_limit st_Sql_SelectAll_role_get_max_userid_limit;
        Sql_Select_role_get_all_role_snapshot st_Sql_Select_role_get_all_role_snapshot;
        Sql_Select_role_get_rolelist_by_accountid st_Sql_Select_role_get_rolelist_by_accountid;
        Sql_Update_role_update_role_change_rolename_by_userid st_Sql_Update_role_update_role_change_rolename_by_userid;
        char temp[512]; //特殊情况下使用
        } _u;
};

enum {
        NONE_OPERATION=0,
        DB_OPRATOR_SELECTALL_ROLE,
        DB_OPRATOR_SELECTALL_ROLE_CHECK_ROLENAME_EXIST,
        DB_OPRATOR_INSERT_ROLE_CREATE_ROLE_BY_ACCOUNTID,
        DB_OPRATOR_INSERT_ROLE_CREATE_ROLE_BY_PASSPORT,
        DB_OPRATOR_SELECTALL_ROLE_GET_ROLE_BY_ACCOUNTID_USERID,
        DB_OPRATOR_SELECTALL_ROLE_GET_ROLE_BY_ACCOUNTID_FIRST,
        DB_OPRATOR_UPDATE_ROLE_SAVE_ROLE_BY_USERID,
        DB_OPRATOR_SELECTALL_ROLE_GET_ROLE_BY_USERID,
        DB_OPRATOR_SELECTALL_ROLE_GET_MAX_USERID_LIMIT,
        DB_OPRATOR_SELECT_ROLE_GET_ALL_ROLE_SNAPSHOT,
        DB_OPRATOR_SELECT_ROLE_GET_ROLELIST_BY_ACCOUNTID,
        DB_OPRATOR_UPDATE_ROLE_UPDATE_ROLE_CHANGE_ROLENAME_BY_USERID,

    };


#endif
