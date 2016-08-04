#ifndef __CONFIGURE_STRUCT_H__
#define __CONFIGURE_STRUCT_H__


struct SServerConfig
{
    int id; //﻿服务器组编号
    char name[64]; //名字
    char ip[16]; //ip
    int port; //port
    char db_ip[16]; //db_ip
    int db_port; //db_port
    char db_u[16]; //db_u
    char db_p[32]; //db_p
    char db[32]; //db
    int rolelimit; //玩家上限
    int sleep; //主循环睡眠
    int iocpworkers; //完成端口工作者线程
    int isopen; //是否公开
    char globalNtf[2048]; //公告
    int canRegister; //是否允许注册
    int isNew; //是否新服
};


#endif 
