# -*- coding: utf8 -*-
import sys
sys.path.append('../../')

import MySQLdb
import build_cpp_db_PNL 

import string


def init_create_db_for_gameserver(_host, _user, _pwd, _dbname, _port, serverid):
    conn=MySQLdb.connect(host="127.0.0.1", user=_user, passwd = _pwd, port=_port)
    cursor=conn.cursor()
    # cursor.execute("DROP database %(_dbname)s "%(locals()))
    #创建数据库
    create_template = """
CREATE DATABASE IF NOT EXISTS %(_dbname)s CHARACTER SET 'utf8' COLLATE 'utf8_general_ci';
"""
    cursor.execute(create_template%(locals()))
    #创建用户
    create_user =  """GRANT ALL ON %(_dbname)s.* TO '%(_user)s'@'%(_host)s'  IDENTIFIED BY '%(_pwd)s';"""%(locals())
    print create_user
    cursor.execute(create_user)
   
    cursor.execute("use %(_dbname)s;"%(locals()))

    for x in build_cpp_db_PNL.g_sql_map:
        r = build_cpp_db_PNL.g_sql_map[x]
        print r
        try:
            cursor.execute(r)
        except Exception, e:
            pass
        else:
            pass
        finally:
            pass
        

    cursor.close()
    conn.close()
    
    
#
#init_db_from_cfg(8)
# init_create_db_for_gameserver(server_cfg.db_ip, server_cfg.db_user, server_cfg.db_pwd, server_cfg.db_name, server_cfg.db_port, server_cfg.serverid)
init_create_db_for_gameserver("127.0.0.1", "root", "root", "pnl_db_test", 3306, 4)
#init_create_db_for_gameserver("192.168.1.114", "root", "root", "lj_ts_2", 7002, 1)
print "OK"
#init_db_from_cfg(8)