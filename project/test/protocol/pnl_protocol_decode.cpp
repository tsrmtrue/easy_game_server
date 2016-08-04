#ifdef WIN32
#include <Winsock2.h>
#else
#include <arpa/inet.h> 
#endif
#include "pnl_protocol_decode.h"
#include <string.h>

int decode_SBasicDataEx(SBasicDataEx& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.guid = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    {
        
        for (unsigned i=0; i<1; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_SBasicDataNtf(st.ns, pSrc+__used__, bufLength-__used__);
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


int decode_SGetStageReq(SGetStageReq& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.stageId = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short *)(pSrc + __used__);
        st.blockId = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SProtocolTypeRsp(SProtocolTypeRsp& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pSrc + __used__);
        st.errcode = (*__i__);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SKickNtf(SKickNtf& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    

    return __used__;
}


int decode_SPackedFiles(SPackedFiles& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short *)(pSrc + __used__);
        st.count = ntohs(*__i__);
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
        for (unsigned i=0; i<st.count; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_SPackedFileIndex(st.files[i], pSrc+__used__, bufLength-__used__);
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


int decode_SBasicDataString(SBasicDataString& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.t = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.sv, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SBasicDataNtf(SBasicDataNtf& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.count = ntohl(*__i__);
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
        for (unsigned i=0; i<st.count; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_SBasicData(st.t[i], pSrc+__used__, bufLength-__used__);
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


int decode_SRole(SRole& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    {
        
        for (unsigned i=0; i<1; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_SBasicRoleInfo(st.roleBasic, pSrc+__used__, bufLength-__used__);
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
        
        for (unsigned i=0; i<1; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_SRoleParameters(st.paraNow, pSrc+__used__, bufLength-__used__);
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


int decode_SEasyLoginRsp(SEasyLoginRsp& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.type = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.errcode = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    {
        
        for (unsigned i=0; i<1; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_SEasyRoleInfo4LoginList(st.roleList, pSrc+__used__, bufLength-__used__);
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


int decode_SEasyRoleInfo4Login(SEasyRoleInfo4Login& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.rolename, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.userid = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SRegisterReq(SRegisterReq& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.account, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.pwd, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.mac, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SBasicRoleInfo(SBasicRoleInfo& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.userid = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.guid = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.showLevel = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.mateid = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.macAddress, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.rolename, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.level = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.professionId = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.exp = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.popularity = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.expTotal = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.diamond = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.money = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.exploit = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.vigor = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.vigorMax = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.leaderForce = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.killingValue = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.halliconId = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SLeaveMsg2GMReq(SLeaveMsg2GMReq& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.msg, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SCreateRsp(SCreateRsp& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.errcode = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.name, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.userid = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SProbeAnswer(SProbeAnswer& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pSrc + __used__);
        st.a = (*__i__);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pSrc + __used__);
        st.b = (*__i__);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pSrc + __used__);
        st.c = (*__i__);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pSrc + __used__);
        st.d = (*__i__);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SBasicDataChangeReq(SBasicDataChangeReq& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    {
        
        for (unsigned i=0; i<1; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_SBasicDataNtf(st.sbdn, pSrc+__used__, bufLength-__used__);
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


int decode_SGetRoleInfoRsp(SGetRoleInfoRsp& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    {
        
        for (unsigned i=0; i<1; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_SRole(st.role, pSrc+__used__, bufLength-__used__);
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


int decode_SBasicDataBroadcastNtf(SBasicDataBroadcastNtf& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.guid = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.t = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.v = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.jerseyId = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SGetRoleInfoReq(SGetRoleInfoReq& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.i = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SBindAccountReq(SBindAccountReq& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.account, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.pwd, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SGmcmdRsp(SGmcmdRsp& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.nouse = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SLogoffReq(SLogoffReq& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    

    return __used__;
}


int decode_SEnterRsp(SEnterRsp& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.errcode = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.roleCount = ntohl(*__i__);
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
        for (unsigned i=0; i<st.roleCount; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_SRole(st.roles[i], pSrc+__used__, bufLength-__used__);
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


int decode_SGMAnswerRsp(SGMAnswerRsp& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.answer, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SEasyLoginReq(SEasyLoginReq& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.type = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.easyAccount, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SLogConsumeDiamond(SLogConsumeDiamond& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.type = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.gID = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.itemID = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SBasicDataChangeNtf(SBasicDataChangeNtf& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    {
        
        for (unsigned i=0; i<1; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_SBasicDataNtf(st.sbdn, pSrc+__used__, bufLength-__used__);
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


int decode_SBasicDataExNtf(SBasicDataExNtf& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.count = ntohl(*__i__);
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
        for (unsigned i=0; i<st.count; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_SBasicDataEx(st.updates[i], pSrc+__used__, bufLength-__used__);
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


int decode_SGetAllStageDescReq(SGetAllStageDescReq& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    

    return __used__;
}


int decode_SLoadFinishedReq(SLoadFinishedReq& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.intoScene = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SGetAllStageDescRsp(SGetAllStageDescRsp& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.count = ntohl(*__i__);
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
        for (unsigned i=0; i<st.count; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_SStageInfo(st.stages[i], pSrc+__used__, bufLength-__used__);
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


int decode_SProbeNtf(SProbeNtf& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pSrc + __used__);
        st.a = (*__i__);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pSrc + __used__);
        st.b = (*__i__);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pSrc + __used__);
        st.c = (*__i__);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pSrc + __used__);
        st.d = (*__i__);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SGlobalNtf(SGlobalNtf& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short *)(pSrc + __used__);
        st.t = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.msg, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.role, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_STreasureUpdateNtf(STreasureUpdateNtf& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.count = ntohl(*__i__);
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
        for (unsigned i=0; i<st.count; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_STreasureInBag(st.treasures[i], pSrc+__used__, bufLength-__used__);
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


int decode_SRoleParameters(SRoleParameters& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.quizCount = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.quizScore = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.moral = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.tidy = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SGmcmdReq(SGmcmdReq& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.cmd, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SGeneralErrorNtf(SGeneralErrorNtf& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.errcode = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.msg, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SEnterReq(SEnterReq& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.userid = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SProtocolTypeRpt(SProtocolTypeRpt& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pSrc + __used__);
        st.type = (*__i__);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pSrc + __used__);
        st.version = (*__i__);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SCreateExReq(SCreateExReq& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.rolename, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.professionId = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.vip = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SBasicData(SBasicData& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.t = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.v = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SServerStatusReporter(SServerStatusReporter& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.servername, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.maxLoad = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.currentLoad = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.protocolVer = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SBasicDataStringNtf(SBasicDataStringNtf& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.count = ntohl(*__i__);
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
        for (unsigned i=0; i<st.count; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_SBasicDataString(st.t[i], pSrc+__used__, bufLength-__used__);
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


int decode_SGeneralWordsNtf(SGeneralWordsNtf& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.msg, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SRegisterRsp(SRegisterRsp& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pSrc + __used__);
        st.errcode = (*__i__);
        __used__ += sizeof(unsigned char);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_STreasureInBag(STreasureInBag& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.index = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    {
        
        for (unsigned i=0; i<1; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_STreasure(st.t, pSrc+__used__, bufLength-__used__);
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
        int* __i__ = (int *)(pSrc + __used__);
        st.leftTimeSecond = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SBindAccountRsp(SBindAccountRsp& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.errcode = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SCreateReq(SCreateReq& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.rolename, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.professionId = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SGetStageRsp(SGetStageRsp& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.totalSize = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    {
        
        for (unsigned i=0; i<1; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_SStageFile(st.file, pSrc+__used__, bufLength-__used__);
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


int decode_SEasyRoleInfo4LoginList(SEasyRoleInfo4LoginList& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned char) <= bufLength)
    {
        unsigned char* __i__ = (unsigned char *)(pSrc + __used__);
        st.count = (*__i__);
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
        for (unsigned i=0; i<st.count; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_SEasyRoleInfo4Login(st.easyRoleList[i], pSrc+__used__, bufLength-__used__);
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


int decode_SLogoffRsp(SLogoffRsp& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    

    return __used__;
}


int decode_SServerLoadFinishNtf(SServerLoadFinishNtf& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.temp = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SBasicDataStringChangeReq(SBasicDataStringChangeReq& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    {
        
        for (unsigned i=0; i<1; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_SBasicDataStringNtf(st.sbdn, pSrc+__used__, bufLength-__used__);
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


int decode_SBasicDataStringChangeNtf(SBasicDataStringChangeNtf& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    {
        
        for (unsigned i=0; i<1; ++i)
        {
            if (__used__  > bufLength)
            {
                return -1;
            }
            int __r__ = decode_SBasicDataStringNtf(st.sbdn, pSrc+__used__, bufLength-__used__);
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


int decode_SMiscDB(SMiscDB& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.shootMonsterCount = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SStageFile(SStageFile& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.stageId = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short *)(pSrc + __used__);
        st.blockId = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short *)(pSrc + __used__);
        st.nextBlcokId = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short *)(pSrc + __used__);
        st.length = ntohs(*__i__);
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
        if (__used__ + st.length <= bufLength)
        {
            memcpy(st.file, pSrc+__used__, st.length);
            __used__ += st.length;
        }
        else
        {
            return -1;
        }
    }


    return __used__;
}


int decode_SPackedFileIndex(SPackedFileIndex& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.name, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.startIndex = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.endIndex = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SStageInfo(SStageInfo& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.stageId = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    {
        
        if (__used__ + 32 <= bufLength)
        {
            memcpy(st.md5, pSrc+__used__, 32);
            __used__ += 32;
        }
        else
        {
            return -1;
        }
    }


    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.name, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(short) <= bufLength)
    {
        unsigned short* __i__ = (unsigned short*)(pSrc + __used__);
        unsigned short __l__ = ntohs(*__i__);
        __used__ += sizeof(unsigned short);
        if (__used__ + __l__> bufLength)
        {
            return -1;
        }
        memcpy(st.desc, pSrc + __used__, __l__);
        __used__ += __l__;
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.size = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_STreasure(STreasure& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.guid = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.count = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.itemId = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    if (__used__ + sizeof(int) <= bufLength)
    {
        int* __i__ = (int *)(pSrc + __used__);
        st.createTime = ntohl(*__i__);
        __used__ += sizeof(int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


int decode_SProtocolVersionNtf(SProtocolVersionNtf& st, unsigned char* pSrc, unsigned int bufLength )
{
    if (pSrc == NULL)
    {
        return -1;
    }
    unsigned int __used__ = 0;

    
    if (__used__ + sizeof(unsigned int) <= bufLength)
    {
        unsigned int* __i__ = (unsigned int *)(pSrc + __used__);
        st.v = ntohl(*__i__);
        __used__ += sizeof(unsigned int);
    }
    else
    {
        return -1;
    }



    return __used__;
}


