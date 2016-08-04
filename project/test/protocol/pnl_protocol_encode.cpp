#ifdef WIN32
#include <Winsock2.h>
#else
#include <arpa/inet.h> 
#endif
#include "pnl_protocol_encode.h"
#include <string.h>

int encode_SBasicDataEx(SBasicDataEx& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.guid);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    {
        
        for (unsigned int i=0; i<1; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_SBasicDataNtf(st.ns, pBuf+__used__, bufLength - __used__ );
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


    return __used__;
}


int encode_SGetStageReq(SGetStageReq& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.stageId);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short *)(pBuf + __used__);
        *__i__ = htons(st.blockId);
        __used__ += sizeof(unsigned short);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SProtocolTypeRsp(SProtocolTypeRsp& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pBuf + __used__);
        *__i__ = (st.errcode);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SKickNtf(SKickNtf& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    

    return __used__;
}


int encode_SPackedFiles(SPackedFiles& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short *)(pBuf + __used__);
        *__i__ = htons(st.count);
        __used__ += sizeof(unsigned short);
    }
    else
    {
        return -1;
    }



    {
        
        if (st.count > 100)
        {
            return -1;
        }
        for (unsigned int i=0; i<st.count; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_SPackedFileIndex(st.files[i], pBuf+__used__, bufLength - __used__ );
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


    return __used__;
}


int encode_SBasicDataString(SBasicDataString& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.t);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(short) + strlen(st.sv) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.sv));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.sv, strlen(st.sv));
        __used__ += strlen(st.sv);
    }
    else
    {
        return -1;
    }


    return __used__;
}


int encode_SBasicDataNtf(SBasicDataNtf& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.count);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    {
        
        if (st.count > 32)
        {
            return -1;
        }
        for (unsigned int i=0; i<st.count; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_SBasicData(st.t[i], pBuf+__used__, bufLength - __used__ );
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


    return __used__;
}


int encode_SRole(SRole& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    {
        
        for (unsigned int i=0; i<1; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_SBasicRoleInfo(st.roleBasic, pBuf+__used__, bufLength - __used__ );
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


    {
        
        for (unsigned int i=0; i<1; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_SRoleParameters(st.paraNow, pBuf+__used__, bufLength - __used__ );
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


    return __used__;
}


int encode_SEasyLoginRsp(SEasyLoginRsp& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.type);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.errcode);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    {
        
        for (unsigned int i=0; i<1; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_SEasyRoleInfo4LoginList(st.roleList, pBuf+__used__, bufLength - __used__ );
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


    return __used__;
}


int encode_SEasyRoleInfo4Login(SEasyRoleInfo4Login& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) + strlen(st.rolename) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.rolename));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.rolename, strlen(st.rolename));
        __used__ += strlen(st.rolename);
    }
    else
    {
        return -1;
    }


    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.userid);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SRegisterReq(SRegisterReq& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) + strlen(st.account) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.account));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.account, strlen(st.account));
        __used__ += strlen(st.account);
    }
    else
    {
        return -1;
    }


    if (__used__ + sizeof(short) + strlen(st.pwd) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.pwd));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.pwd, strlen(st.pwd));
        __used__ += strlen(st.pwd);
    }
    else
    {
        return -1;
    }


    if (__used__ + sizeof(short) + strlen(st.mac) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.mac));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.mac, strlen(st.mac));
        __used__ += strlen(st.mac);
    }
    else
    {
        return -1;
    }


    return __used__;
}


int encode_SBasicRoleInfo(SBasicRoleInfo& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.userid);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.guid);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.showLevel);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.mateid);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(short) + strlen(st.macAddress) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.macAddress));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.macAddress, strlen(st.macAddress));
        __used__ += strlen(st.macAddress);
    }
    else
    {
        return -1;
    }


    if (__used__ + sizeof(short) + strlen(st.rolename) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.rolename));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.rolename, strlen(st.rolename));
        __used__ += strlen(st.rolename);
    }
    else
    {
        return -1;
    }


    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.level);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.professionId);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.exp);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.popularity);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.expTotal);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.diamond);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.money);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.exploit);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.vigor);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.vigorMax);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.leaderForce);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.killingValue);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.halliconId);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SLeaveMsg2GMReq(SLeaveMsg2GMReq& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) + strlen(st.msg) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.msg));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.msg, strlen(st.msg));
        __used__ += strlen(st.msg);
    }
    else
    {
        return -1;
    }


    return __used__;
}


int encode_SCreateRsp(SCreateRsp& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.errcode);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(short) + strlen(st.name) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.name));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.name, strlen(st.name));
        __used__ += strlen(st.name);
    }
    else
    {
        return -1;
    }


    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.userid);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SProbeAnswer(SProbeAnswer& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pBuf + __used__);
        *__i__ = (st.a);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pBuf + __used__);
        *__i__ = (st.b);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pBuf + __used__);
        *__i__ = (st.c);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pBuf + __used__);
        *__i__ = (st.d);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SBasicDataChangeReq(SBasicDataChangeReq& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    {
        
        for (unsigned int i=0; i<1; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_SBasicDataNtf(st.sbdn, pBuf+__used__, bufLength - __used__ );
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


    return __used__;
}


int encode_SGetRoleInfoRsp(SGetRoleInfoRsp& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    {
        
        for (unsigned int i=0; i<1; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_SRole(st.role, pBuf+__used__, bufLength - __used__ );
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


    return __used__;
}


int encode_SBasicDataBroadcastNtf(SBasicDataBroadcastNtf& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.guid);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.t);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.v);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.jerseyId);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SGetRoleInfoReq(SGetRoleInfoReq& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.i);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SBindAccountReq(SBindAccountReq& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) + strlen(st.account) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.account));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.account, strlen(st.account));
        __used__ += strlen(st.account);
    }
    else
    {
        return -1;
    }


    if (__used__ + sizeof(short) + strlen(st.pwd) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.pwd));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.pwd, strlen(st.pwd));
        __used__ += strlen(st.pwd);
    }
    else
    {
        return -1;
    }


    return __used__;
}


int encode_SGmcmdRsp(SGmcmdRsp& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.nouse);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SLogoffReq(SLogoffReq& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    

    return __used__;
}


int encode_SEnterRsp(SEnterRsp& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.errcode);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.roleCount);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    {
        
        if (st.roleCount > 1)
        {
            return -1;
        }
        for (unsigned int i=0; i<st.roleCount; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_SRole(st.roles[i], pBuf+__used__, bufLength - __used__ );
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


    return __used__;
}


int encode_SGMAnswerRsp(SGMAnswerRsp& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) + strlen(st.answer) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.answer));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.answer, strlen(st.answer));
        __used__ += strlen(st.answer);
    }
    else
    {
        return -1;
    }


    return __used__;
}


int encode_SEasyLoginReq(SEasyLoginReq& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.type);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(short) + strlen(st.easyAccount) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.easyAccount));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.easyAccount, strlen(st.easyAccount));
        __used__ += strlen(st.easyAccount);
    }
    else
    {
        return -1;
    }


    return __used__;
}


int encode_SLogConsumeDiamond(SLogConsumeDiamond& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.type);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.gID);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.itemID);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SBasicDataChangeNtf(SBasicDataChangeNtf& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    {
        
        for (unsigned int i=0; i<1; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_SBasicDataNtf(st.sbdn, pBuf+__used__, bufLength - __used__ );
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


    return __used__;
}


int encode_SBasicDataExNtf(SBasicDataExNtf& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.count);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    {
        
        if (st.count > 21)
        {
            return -1;
        }
        for (unsigned int i=0; i<st.count; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_SBasicDataEx(st.updates[i], pBuf+__used__, bufLength - __used__ );
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


    return __used__;
}


int encode_SGetAllStageDescReq(SGetAllStageDescReq& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    

    return __used__;
}


int encode_SLoadFinishedReq(SLoadFinishedReq& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.intoScene);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SGetAllStageDescRsp(SGetAllStageDescRsp& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.count);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    {
        
        if (st.count > 50)
        {
            return -1;
        }
        for (unsigned int i=0; i<st.count; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_SStageInfo(st.stages[i], pBuf+__used__, bufLength - __used__ );
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


    return __used__;
}


int encode_SProbeNtf(SProbeNtf& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pBuf + __used__);
        *__i__ = (st.a);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pBuf + __used__);
        *__i__ = (st.b);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pBuf + __used__);
        *__i__ = (st.c);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pBuf + __used__);
        *__i__ = (st.d);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SGlobalNtf(SGlobalNtf& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short *)(pBuf + __used__);
        *__i__ = htons(st.t);
        __used__ += sizeof(unsigned short);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(short) + strlen(st.msg) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.msg));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.msg, strlen(st.msg));
        __used__ += strlen(st.msg);
    }
    else
    {
        return -1;
    }


    if (__used__ + sizeof(short) + strlen(st.role) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.role));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.role, strlen(st.role));
        __used__ += strlen(st.role);
    }
    else
    {
        return -1;
    }


    return __used__;
}


int encode_STreasureUpdateNtf(STreasureUpdateNtf& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.count);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    {
        
        if (st.count > 100)
        {
            return -1;
        }
        for (unsigned int i=0; i<st.count; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_STreasureInBag(st.treasures[i], pBuf+__used__, bufLength - __used__ );
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


    return __used__;
}


int encode_SRoleParameters(SRoleParameters& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.quizCount);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.quizScore);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.moral);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.tidy);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SGmcmdReq(SGmcmdReq& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) + strlen(st.cmd) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.cmd));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.cmd, strlen(st.cmd));
        __used__ += strlen(st.cmd);
    }
    else
    {
        return -1;
    }


    return __used__;
}


int encode_SGeneralErrorNtf(SGeneralErrorNtf& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.errcode);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(short) + strlen(st.msg) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.msg));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.msg, strlen(st.msg));
        __used__ += strlen(st.msg);
    }
    else
    {
        return -1;
    }


    return __used__;
}


int encode_SEnterReq(SEnterReq& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.userid);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SProtocolTypeRpt(SProtocolTypeRpt& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pBuf + __used__);
        *__i__ = (st.type);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pBuf + __used__);
        *__i__ = (st.version);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SCreateExReq(SCreateExReq& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) + strlen(st.rolename) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.rolename));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.rolename, strlen(st.rolename));
        __used__ += strlen(st.rolename);
    }
    else
    {
        return -1;
    }


    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.professionId);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.vip);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SBasicData(SBasicData& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.t);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.v);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SServerStatusReporter(SServerStatusReporter& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) + strlen(st.servername) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.servername));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.servername, strlen(st.servername));
        __used__ += strlen(st.servername);
    }
    else
    {
        return -1;
    }


    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.maxLoad);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.currentLoad);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.protocolVer);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SBasicDataStringNtf(SBasicDataStringNtf& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.count);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    {
        
        if (st.count > 32)
        {
            return -1;
        }
        for (unsigned int i=0; i<st.count; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_SBasicDataString(st.t[i], pBuf+__used__, bufLength - __used__ );
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


    return __used__;
}


int encode_SGeneralWordsNtf(SGeneralWordsNtf& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) + strlen(st.msg) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.msg));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.msg, strlen(st.msg));
        __used__ += strlen(st.msg);
    }
    else
    {
        return -1;
    }


    return __used__;
}


int encode_SRegisterRsp(SRegisterRsp& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pBuf + __used__);
        *__i__ = (st.errcode);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_STreasureInBag(STreasureInBag& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.index);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    {
        
        for (unsigned int i=0; i<1; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_STreasure(st.t, pBuf+__used__, bufLength - __used__ );
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


    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.leftTimeSecond);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SBindAccountRsp(SBindAccountRsp& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.errcode);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SCreateReq(SCreateReq& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) + strlen(st.rolename) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.rolename));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.rolename, strlen(st.rolename));
        __used__ += strlen(st.rolename);
    }
    else
    {
        return -1;
    }


    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.professionId);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SGetStageRsp(SGetStageRsp& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.totalSize);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    {
        
        for (unsigned int i=0; i<1; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_SStageFile(st.file, pBuf+__used__, bufLength - __used__ );
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


    return __used__;
}


int encode_SEasyRoleInfo4LoginList(SEasyRoleInfo4LoginList& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pBuf + __used__);
        *__i__ = (st.count);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    {
        
        if (st.count > 5)
        {
            return -1;
        }
        for (unsigned int i=0; i<st.count; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_SEasyRoleInfo4Login(st.easyRoleList[i], pBuf+__used__, bufLength - __used__ );
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


    return __used__;
}


int encode_SLogoffRsp(SLogoffRsp& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    

    return __used__;
}


int encode_SServerLoadFinishNtf(SServerLoadFinishNtf& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.temp);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SBasicDataStringChangeReq(SBasicDataStringChangeReq& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    {
        
        for (unsigned int i=0; i<1; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_SBasicDataStringNtf(st.sbdn, pBuf+__used__, bufLength - __used__ );
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


    return __used__;
}


int encode_SBasicDataStringChangeNtf(SBasicDataStringChangeNtf& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    {
        
        for (unsigned int i=0; i<1; ++i)
        {
            if (__used__ > bufLength)
            {
                return -1;
            }
            int __r__ = encode_SBasicDataStringNtf(st.sbdn, pBuf+__used__, bufLength - __used__ );
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


    return __used__;
}


int encode_SMiscDB(SMiscDB& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.shootMonsterCount);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SStageFile(SStageFile& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.stageId);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short *)(pBuf + __used__);
        *__i__ = htons(st.blockId);
        __used__ += sizeof(unsigned short);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short *)(pBuf + __used__);
        *__i__ = htons(st.nextBlcokId);
        __used__ += sizeof(unsigned short);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short *)(pBuf + __used__);
        *__i__ = htons(st.length);
        __used__ += sizeof(unsigned short);
    }
    else
    {
        return -1;
    }



    {
        
        if (st.length > 20480)
        {
            return -1;
        }
        if (__used__ + sizeof(st.file[0]) * st.length <= bufLength)
        {
            for(unsigned int i=0; i<st.length; ++i)
            {            
                unsigned char* __i__ = (unsigned char *)(pBuf + __used__);
                *__i__ = (st.file[i]);
                __used__ += sizeof(unsigned char);
            }
        }
        else
        {
            return -1;
        }
    }


    return __used__;
}


int encode_SPackedFileIndex(SPackedFileIndex& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) + strlen(st.name) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.name));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.name, strlen(st.name));
        __used__ += strlen(st.name);
    }
    else
    {
        return -1;
    }


    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.startIndex);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.endIndex);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SStageInfo(SStageInfo& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.stageId);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    {
        
        if (__used__ + sizeof(st.md5[0]) * 32 <= bufLength)
        {
            for(unsigned int i=0; i<32; ++i)
            {            
                unsigned char* __i__ = (unsigned char *)(pBuf + __used__);
                *__i__ = (st.md5[i]);
                __used__ += sizeof(unsigned char);
            }
        }
        else
        {
            return -1;
        }
    }


    if (__used__ + sizeof(short) + strlen(st.name) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.name));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.name, strlen(st.name));
        __used__ += strlen(st.name);
    }
    else
    {
        return -1;
    }


    if (__used__ + sizeof(short) + strlen(st.desc) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pBuf + __used__);
        *__i__ = htons(strlen(st.desc));
        __used__ += sizeof(unsigned short);
    
        memcpy(pBuf + __used__, st.desc, strlen(st.desc));
        __used__ += strlen(st.desc);
    }
    else
    {
        return -1;
    }


    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.size);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_STreasure(STreasure& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.guid);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.count);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.itemId);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pBuf + __used__);
        *__i__ = htonl(st.createTime);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int encode_SProtocolVersionNtf(SProtocolVersionNtf& st, unsigned char* pBuf, unsigned int bufLength )
{
    if (pBuf == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pBuf + __used__);
        *__i__ = htonl(st.v);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


