# -*- coding: GBK -*-
import sys
sys.path.append('../autotest_lib')
from coder_hlp_lib import *
from test_namedlistPNL import *
g_decode_fun = {}
g_encode_fun = {}
S_2_C_Protocol_Version_Ntf = 1
C_2_S_Protocol_Type_Rpt = 2
C_2_S_Protocol_Type_Rsp = 3
S_2_C_General_Error_Ntf = 4
S_2_C_General_Words_Ntf = 5
C_2_S_Create_Req = 6
S_2_C_Create_Rsp = 7
C_2_S_Easy_Login_Req = 8
S_2_C_Easy_Login_Rsp = 9
C_2_S_Enter_Req = 10
S_2_C_Enter_Rsp = 11
S_2_C_Kick_Ntf = 12
C_2_S_Logoff_Req = 13
S_2_C_Logoff_Rsp = 14
C_2_S_LoadFinished_Req = 15
C_2_S_Create_Ex_Req = 16
C_2_S_GmCmd_Req = 17
S_2_C_GmCmd_Rsp = 18
S_2_C_Basic_DataEx_Ntf = 19
S_2_C_Global_Ntf = 20
S_2_C_Basic_Data_Broadcast_Ntf = 21
S_2_C_PROBE_NTF = 22
C_2_S_PROBE_ANSWER = 23
C_2_S_Leave_Msg_2_GM_Req = 24
S_2_C_GM_Answer_Rsp = 25
S_2_C_Server_Status_Ntf = 26
S_2_S_Server_Status_Reporter = 27
S_2_C_Server_Load_Finished_Ntf = 28
C_2_S_SGetAllStage_Req = 29
S_2_C_SGetAllStage_Rsp = 30
C_2_S_SGetStage_Req = 31
S_2_C_SGetStage_Rsp = 32
TOOL_SPackedFiles = 33
S_2_C_TeasureUpdate_Ntf = 34
C_2_S_Basic_Data_Change_Req = 35
S_2_C_Basic_Data_Change_Ntf = 36
C_2_S_Basic_String_Data_Change_Req = 37
S_2_C_Basic_String_Data_Change_Ntf = 38
C_2_S_GET_ROLE_INFO_REQ = 39
S_2_C_GET_ROLE_INFO_RSP = 40

def encode_SLoadFinishedReq(st):
    str=''

    str += addDword(st.intoScene)
    return str

def decode_SLoadFinishedReq(buf):
    st=SLoadFinishedReq()
    pos=0

    st.intoScene,length = getDword(buf[pos:])
    pos += length
    return st,pos

def encode_SCreateReq(st):
    str=''

    str += addString(st.rolename)
    str += addInt(st.professionId)
    return str

def decode_SCreateReq(buf):
    st=SCreateReq()
    pos=0

    st.rolename,length = getString(buf[pos:])
    pos += length
    st.professionId,length = getInt(buf[pos:])
    pos += length
    return st,pos

def encode_SCreateExReq(st):
    str=''

    str += addString(st.rolename)
    str += addInt(st.professionId)
    str += addInt(st.vip)
    return str

def decode_SCreateExReq(buf):
    st=SCreateExReq()
    pos=0

    st.rolename,length = getString(buf[pos:])
    pos += length
    st.professionId,length = getInt(buf[pos:])
    pos += length
    st.vip,length = getInt(buf[pos:])
    pos += length
    return st,pos

def encode_SLogoffReq(st):
    str=''

    return str

def decode_SLogoffReq(buf):
    st=SLogoffReq()
    pos=0

    return st,pos

def encode_SLogoffRsp(st):
    str=''

    return str

def decode_SLogoffRsp(buf):
    st=SLogoffRsp()
    pos=0

    return st,pos

def encode_SRegisterReq(st):
    str=''

    str += addString(st.account)
    str += addString(st.pwd)
    str += addString(st.mac)
    return str

def decode_SRegisterReq(buf):
    st=SRegisterReq()
    pos=0

    st.account,length = getString(buf[pos:])
    pos += length
    st.pwd,length = getString(buf[pos:])
    pos += length
    st.mac,length = getString(buf[pos:])
    pos += length
    return st,pos

def encode_SRegisterRsp(st):
    str=''

    str += addByte(st.errcode)
    return str

def decode_SRegisterRsp(buf):
    st=SRegisterRsp()
    pos=0

    st.errcode,length = getByte(buf[pos:])
    pos += length
    return st,pos

def encode_SKickNtf(st):
    str=''

    return str

def decode_SKickNtf(buf):
    st=SKickNtf()
    pos=0

    return st,pos

def encode_SEasyLoginReq(st):
    str=''

    str += addInt(st.type)
    str += addString(st.easyAccount)
    return str

def decode_SEasyLoginReq(buf):
    st=SEasyLoginReq()
    pos=0

    st.type,length = getInt(buf[pos:])
    pos += length
    st.easyAccount,length = getString(buf[pos:])
    pos += length
    return st,pos

def encode_SBasicRoleInfo(st):
    str=''

    str += addDword(st.userid)
    str += addInt(st.guid)
    str += addDword(st.showLevel)
    str += addDword(st.mateid)
    str += addString(st.macAddress)
    str += addString(st.rolename)
    str += addInt(st.level)
    str += addInt(st.professionId)
    str += addInt(st.exp)
    str += addInt(st.popularity)
    str += addInt(st.expTotal)
    str += addInt(st.diamond)
    str += addInt(st.money)
    str += addInt(st.exploit)
    str += addInt(st.vigor)
    str += addInt(st.vigorMax)
    str += addInt(st.leaderForce)
    str += addInt(st.killingValue)
    str += addInt(st.halliconId)
    return str

def decode_SBasicRoleInfo(buf):
    st=SBasicRoleInfo()
    pos=0

    st.userid,length = getDword(buf[pos:])
    pos += length
    st.guid,length = getInt(buf[pos:])
    pos += length
    st.showLevel,length = getDword(buf[pos:])
    pos += length
    st.mateid,length = getDword(buf[pos:])
    pos += length
    st.macAddress,length = getString(buf[pos:])
    pos += length
    st.rolename,length = getString(buf[pos:])
    pos += length
    st.level,length = getInt(buf[pos:])
    pos += length
    st.professionId,length = getInt(buf[pos:])
    pos += length
    st.exp,length = getInt(buf[pos:])
    pos += length
    st.popularity,length = getInt(buf[pos:])
    pos += length
    st.expTotal,length = getInt(buf[pos:])
    pos += length
    st.diamond,length = getInt(buf[pos:])
    pos += length
    st.money,length = getInt(buf[pos:])
    pos += length
    st.exploit,length = getInt(buf[pos:])
    pos += length
    st.vigor,length = getInt(buf[pos:])
    pos += length
    st.vigorMax,length = getInt(buf[pos:])
    pos += length
    st.leaderForce,length = getInt(buf[pos:])
    pos += length
    st.killingValue,length = getInt(buf[pos:])
    pos += length
    st.halliconId,length = getInt(buf[pos:])
    pos += length
    return st,pos

def encode_SRoleParameters(st):
    str=''

    str += addInt(st.quizCount)
    str += addInt(st.quizScore)
    str += addInt(st.moral)
    str += addInt(st.tidy)
    return str

def decode_SRoleParameters(buf):
    st=SRoleParameters()
    pos=0

    st.quizCount,length = getInt(buf[pos:])
    pos += length
    st.quizScore,length = getInt(buf[pos:])
    pos += length
    st.moral,length = getInt(buf[pos:])
    pos += length
    st.tidy,length = getInt(buf[pos:])
    pos += length
    return st,pos

def encode_SRole(st):
    str=''


    for i in range(1):
        _tempstr = encode_SBasicRoleInfo(st.roleBasic)
        str += _tempstr


    for i in range(1):
        _tempstr = encode_SRoleParameters(st.paraNow)
        str += _tempstr

    return str

def decode_SRole(buf):
    st=SRole()
    pos=0


    for i in range(1):
        st.roleBasic,length = decode_SBasicRoleInfo(buf[pos:])
    
        pos += length


    for i in range(1):
        st.paraNow,length = decode_SRoleParameters(buf[pos:])
    
        pos += length

    return st,pos

def encode_SEasyRoleInfo4Login(st):
    str=''

    str += addString(st.rolename)
    str += addInt(st.userid)
    return str

def decode_SEasyRoleInfo4Login(buf):
    st=SEasyRoleInfo4Login()
    pos=0

    st.rolename,length = getString(buf[pos:])
    pos += length
    st.userid,length = getInt(buf[pos:])
    pos += length
    return st,pos

def encode_SEasyRoleInfo4LoginList(st):
    str=''

    str += addByte(st.count)

    for i in range(st.count):
        _tempstr = encode_SEasyRoleInfo4Login(st.easyRoleList[i])
        str += _tempstr

    return str

def decode_SEasyRoleInfo4LoginList(buf):
    st=SEasyRoleInfo4LoginList()
    pos=0

    st.count,length = getByte(buf[pos:])
    pos += length

    for i in range(st.count):
        st.easyRoleList[i],length = decode_SEasyRoleInfo4Login(buf[pos:])
    
        pos += length

    return st,pos

def encode_SEasyLoginRsp(st):
    str=''

    str += addInt(st.type)
    str += addDword(st.errcode)

    for i in range(1):
        _tempstr = encode_SEasyRoleInfo4LoginList(st.roleList)
        str += _tempstr

    return str

def decode_SEasyLoginRsp(buf):
    st=SEasyLoginRsp()
    pos=0

    st.type,length = getInt(buf[pos:])
    pos += length
    st.errcode,length = getDword(buf[pos:])
    pos += length

    for i in range(1):
        st.roleList,length = decode_SEasyRoleInfo4LoginList(buf[pos:])
    
        pos += length

    return st,pos

def encode_SEnterReq(st):
    str=''

    str += addDword(st.userid)
    return str

def decode_SEnterReq(buf):
    st=SEnterReq()
    pos=0

    st.userid,length = getDword(buf[pos:])
    pos += length
    return st,pos

def encode_SEnterRsp(st):
    str=''

    str += addDword(st.errcode)
    str += addDword(st.roleCount)

    for i in range(st.roleCount):
        _tempstr = encode_SRole(st.roles[i])
        str += _tempstr

    return str

def decode_SEnterRsp(buf):
    st=SEnterRsp()
    pos=0

    st.errcode,length = getDword(buf[pos:])
    pos += length
    st.roleCount,length = getDword(buf[pos:])
    pos += length

    for i in range(st.roleCount):
        st.roles[i],length = decode_SRole(buf[pos:])
    
        pos += length

    return st,pos

def encode_SBindAccountReq(st):
    str=''

    str += addString(st.account)
    str += addString(st.pwd)
    return str

def decode_SBindAccountReq(buf):
    st=SBindAccountReq()
    pos=0

    st.account,length = getString(buf[pos:])
    pos += length
    st.pwd,length = getString(buf[pos:])
    pos += length
    return st,pos

def encode_SBindAccountRsp(st):
    str=''

    str += addDword(st.errcode)
    return str

def decode_SBindAccountRsp(buf):
    st=SBindAccountRsp()
    pos=0

    st.errcode,length = getDword(buf[pos:])
    pos += length
    return st,pos

def encode_SCreateRsp(st):
    str=''

    str += addDword(st.errcode)
    str += addString(st.name)
    str += addDword(st.userid)
    return str

def decode_SCreateRsp(buf):
    st=SCreateRsp()
    pos=0

    st.errcode,length = getDword(buf[pos:])
    pos += length
    st.name,length = getString(buf[pos:])
    pos += length
    st.userid,length = getDword(buf[pos:])
    pos += length
    return st,pos

def encode_SBasicData(st):
    str=''

    str += addDword(st.t)
    str += addDword(st.v)
    return str

def decode_SBasicData(buf):
    st=SBasicData()
    pos=0

    st.t,length = getDword(buf[pos:])
    pos += length
    st.v,length = getDword(buf[pos:])
    pos += length
    return st,pos

def encode_SBasicDataString(st):
    str=''

    str += addDword(st.t)
    str += addString(st.sv)
    return str

def decode_SBasicDataString(buf):
    st=SBasicDataString()
    pos=0

    st.t,length = getDword(buf[pos:])
    pos += length
    st.sv,length = getString(buf[pos:])
    pos += length
    return st,pos

def encode_SBasicDataStringNtf(st):
    str=''

    str += addDword(st.count)

    for i in range(st.count):
        _tempstr = encode_SBasicDataString(st.t[i])
        str += _tempstr

    return str

def decode_SBasicDataStringNtf(buf):
    st=SBasicDataStringNtf()
    pos=0

    st.count,length = getDword(buf[pos:])
    pos += length

    for i in range(st.count):
        st.t[i],length = decode_SBasicDataString(buf[pos:])
    
        pos += length

    return st,pos

def encode_SBasicDataNtf(st):
    str=''

    str += addDword(st.count)

    for i in range(st.count):
        _tempstr = encode_SBasicData(st.t[i])
        str += _tempstr

    return str

def decode_SBasicDataNtf(buf):
    st=SBasicDataNtf()
    pos=0

    st.count,length = getDword(buf[pos:])
    pos += length

    for i in range(st.count):
        st.t[i],length = decode_SBasicData(buf[pos:])
    
        pos += length

    return st,pos

def encode_SBasicDataEx(st):
    str=''

    str += addDword(st.guid)

    for i in range(1):
        _tempstr = encode_SBasicDataNtf(st.ns)
        str += _tempstr

    return str

def decode_SBasicDataEx(buf):
    st=SBasicDataEx()
    pos=0

    st.guid,length = getDword(buf[pos:])
    pos += length

    for i in range(1):
        st.ns,length = decode_SBasicDataNtf(buf[pos:])
    
        pos += length

    return st,pos

def encode_SBasicDataExNtf(st):
    str=''

    str += addDword(st.count)

    for i in range(st.count):
        _tempstr = encode_SBasicDataEx(st.updates[i])
        str += _tempstr

    return str

def decode_SBasicDataExNtf(buf):
    st=SBasicDataExNtf()
    pos=0

    st.count,length = getDword(buf[pos:])
    pos += length

    for i in range(st.count):
        st.updates[i],length = decode_SBasicDataEx(buf[pos:])
    
        pos += length

    return st,pos

def encode_SBasicDataChangeReq(st):
    str=''


    for i in range(1):
        _tempstr = encode_SBasicDataNtf(st.sbdn)
        str += _tempstr

    return str

def decode_SBasicDataChangeReq(buf):
    st=SBasicDataChangeReq()
    pos=0


    for i in range(1):
        st.sbdn,length = decode_SBasicDataNtf(buf[pos:])
    
        pos += length

    return st,pos

def encode_SBasicDataChangeNtf(st):
    str=''


    for i in range(1):
        _tempstr = encode_SBasicDataNtf(st.sbdn)
        str += _tempstr

    return str

def decode_SBasicDataChangeNtf(buf):
    st=SBasicDataChangeNtf()
    pos=0


    for i in range(1):
        st.sbdn,length = decode_SBasicDataNtf(buf[pos:])
    
        pos += length

    return st,pos

def encode_SBasicDataStringChangeReq(st):
    str=''


    for i in range(1):
        _tempstr = encode_SBasicDataStringNtf(st.sbdn)
        str += _tempstr

    return str

def decode_SBasicDataStringChangeReq(buf):
    st=SBasicDataStringChangeReq()
    pos=0


    for i in range(1):
        st.sbdn,length = decode_SBasicDataStringNtf(buf[pos:])
    
        pos += length

    return st,pos

def encode_SBasicDataStringChangeNtf(st):
    str=''


    for i in range(1):
        _tempstr = encode_SBasicDataStringNtf(st.sbdn)
        str += _tempstr

    return str

def decode_SBasicDataStringChangeNtf(buf):
    st=SBasicDataStringChangeNtf()
    pos=0


    for i in range(1):
        st.sbdn,length = decode_SBasicDataStringNtf(buf[pos:])
    
        pos += length

    return st,pos

def encode_SGlobalNtf(st):
    str=''

    str += addWord(st.t)
    str += addString(st.msg)
    str += addString(st.role)
    return str

def decode_SGlobalNtf(buf):
    st=SGlobalNtf()
    pos=0

    st.t,length = getWord(buf[pos:])
    pos += length
    st.msg,length = getString(buf[pos:])
    pos += length
    st.role,length = getString(buf[pos:])
    pos += length
    return st,pos

def encode_SBasicDataBroadcastNtf(st):
    str=''

    str += addDword(st.guid)
    str += addDword(st.t)
    str += addDword(st.v)
    str += addDword(st.jerseyId)
    return str

def decode_SBasicDataBroadcastNtf(buf):
    st=SBasicDataBroadcastNtf()
    pos=0

    st.guid,length = getDword(buf[pos:])
    pos += length
    st.t,length = getDword(buf[pos:])
    pos += length
    st.v,length = getDword(buf[pos:])
    pos += length
    st.jerseyId,length = getDword(buf[pos:])
    pos += length
    return st,pos

def encode_SProtocolVersionNtf(st):
    str=''

    str += addDword(st.v)
    return str

def decode_SProtocolVersionNtf(buf):
    st=SProtocolVersionNtf()
    pos=0

    st.v,length = getDword(buf[pos:])
    pos += length
    return st,pos

def encode_SProtocolTypeRpt(st):
    str=''

    str += addByte(st.type)
    str += addByte(st.version)
    return str

def decode_SProtocolTypeRpt(buf):
    st=SProtocolTypeRpt()
    pos=0

    st.type,length = getByte(buf[pos:])
    pos += length
    st.version,length = getByte(buf[pos:])
    pos += length
    return st,pos

def encode_SProtocolTypeRsp(st):
    str=''

    str += addByte(st.errcode)
    return str

def decode_SProtocolTypeRsp(buf):
    st=SProtocolTypeRsp()
    pos=0

    st.errcode,length = getByte(buf[pos:])
    pos += length
    return st,pos

def encode_SGmcmdReq(st):
    str=''

    str += addString(st.cmd)
    return str

def decode_SGmcmdReq(buf):
    st=SGmcmdReq()
    pos=0

    st.cmd,length = getString(buf[pos:])
    pos += length
    return st,pos

def encode_SGmcmdRsp(st):
    str=''

    str += addDword(st.nouse)
    return str

def decode_SGmcmdRsp(buf):
    st=SGmcmdRsp()
    pos=0

    st.nouse,length = getDword(buf[pos:])
    pos += length
    return st,pos

def encode_SProbeNtf(st):
    str=''

    str += addByte(st.a)
    str += addByte(st.b)
    str += addByte(st.c)
    str += addByte(st.d)
    return str

def decode_SProbeNtf(buf):
    st=SProbeNtf()
    pos=0

    st.a,length = getByte(buf[pos:])
    pos += length
    st.b,length = getByte(buf[pos:])
    pos += length
    st.c,length = getByte(buf[pos:])
    pos += length
    st.d,length = getByte(buf[pos:])
    pos += length
    return st,pos

def encode_SProbeAnswer(st):
    str=''

    str += addByte(st.a)
    str += addByte(st.b)
    str += addByte(st.c)
    str += addByte(st.d)
    return str

def decode_SProbeAnswer(buf):
    st=SProbeAnswer()
    pos=0

    st.a,length = getByte(buf[pos:])
    pos += length
    st.b,length = getByte(buf[pos:])
    pos += length
    st.c,length = getByte(buf[pos:])
    pos += length
    st.d,length = getByte(buf[pos:])
    pos += length
    return st,pos

def encode_SLeaveMsg2GMReq(st):
    str=''

    str += addString(st.msg)
    return str

def decode_SLeaveMsg2GMReq(buf):
    st=SLeaveMsg2GMReq()
    pos=0

    st.msg,length = getString(buf[pos:])
    pos += length
    return st,pos

def encode_SGMAnswerRsp(st):
    str=''

    str += addString(st.answer)
    return str

def decode_SGMAnswerRsp(buf):
    st=SGMAnswerRsp()
    pos=0

    st.answer,length = getString(buf[pos:])
    pos += length
    return st,pos

def encode_SServerLoadFinishNtf(st):
    str=''

    str += addInt(st.temp)
    return str

def decode_SServerLoadFinishNtf(buf):
    st=SServerLoadFinishNtf()
    pos=0

    st.temp,length = getInt(buf[pos:])
    pos += length
    return st,pos

def encode_SStageInfo(st):
    str=''

    str += addDword(st.stageId)
    for i in range(32):
        str += addByte(st.md5[i])
    str += addString(st.name)
    str += addString(st.desc)
    str += addDword(st.size)
    return str

def decode_SStageInfo(buf):
    st=SStageInfo()
    pos=0

    st.stageId,length = getDword(buf[pos:])
    pos += length
    for i in range(32):
        st.md5[i],length = getByte(buf[pos:])
        pos += length
    st.name,length = getString(buf[pos:])
    pos += length
    st.desc,length = getString(buf[pos:])
    pos += length
    st.size,length = getDword(buf[pos:])
    pos += length
    return st,pos

def encode_SStageFile(st):
    str=''

    str += addDword(st.stageId)
    str += addWord(st.blockId)
    str += addWord(st.nextBlcokId)
    str += addWord(st.length)
    for i in range(st.length):
        str += addByte(st.file[i])
    return str

def decode_SStageFile(buf):
    st=SStageFile()
    pos=0

    st.stageId,length = getDword(buf[pos:])
    pos += length
    st.blockId,length = getWord(buf[pos:])
    pos += length
    st.nextBlcokId,length = getWord(buf[pos:])
    pos += length
    st.length,length = getWord(buf[pos:])
    pos += length
    for i in range(st.length):
        st.file[i],length = getByte(buf[pos:])
        pos += length
    return st,pos

def encode_SGetAllStageDescReq(st):
    str=''

    return str

def decode_SGetAllStageDescReq(buf):
    st=SGetAllStageDescReq()
    pos=0

    return st,pos

def encode_SGetAllStageDescRsp(st):
    str=''

    str += addDword(st.count)

    for i in range(st.count):
        _tempstr = encode_SStageInfo(st.stages[i])
        str += _tempstr

    return str

def decode_SGetAllStageDescRsp(buf):
    st=SGetAllStageDescRsp()
    pos=0

    st.count,length = getDword(buf[pos:])
    pos += length

    for i in range(st.count):
        st.stages[i],length = decode_SStageInfo(buf[pos:])
    
        pos += length

    return st,pos

def encode_SGetStageReq(st):
    str=''

    str += addDword(st.stageId)
    str += addWord(st.blockId)
    return str

def decode_SGetStageReq(buf):
    st=SGetStageReq()
    pos=0

    st.stageId,length = getDword(buf[pos:])
    pos += length
    st.blockId,length = getWord(buf[pos:])
    pos += length
    return st,pos

def encode_SGetStageRsp(st):
    str=''

    str += addDword(st.totalSize)

    for i in range(1):
        _tempstr = encode_SStageFile(st.file)
        str += _tempstr

    return str

def decode_SGetStageRsp(buf):
    st=SGetStageRsp()
    pos=0

    st.totalSize,length = getDword(buf[pos:])
    pos += length

    for i in range(1):
        st.file,length = decode_SStageFile(buf[pos:])
    
        pos += length

    return st,pos

def encode_STreasure(st):
    str=''

    str += addInt(st.guid)
    str += addInt(st.count)
    str += addInt(st.itemId)
    str += addInt(st.createTime)
    return str

def decode_STreasure(buf):
    st=STreasure()
    pos=0

    st.guid,length = getInt(buf[pos:])
    pos += length
    st.count,length = getInt(buf[pos:])
    pos += length
    st.itemId,length = getInt(buf[pos:])
    pos += length
    st.createTime,length = getInt(buf[pos:])
    pos += length
    return st,pos

def encode_STreasureInBag(st):
    str=''

    str += addInt(st.index)

    for i in range(1):
        _tempstr = encode_STreasure(st.t)
        str += _tempstr

    str += addInt(st.leftTimeSecond)
    return str

def decode_STreasureInBag(buf):
    st=STreasureInBag()
    pos=0

    st.index,length = getInt(buf[pos:])
    pos += length

    for i in range(1):
        st.t,length = decode_STreasure(buf[pos:])
    
        pos += length

    st.leftTimeSecond,length = getInt(buf[pos:])
    pos += length
    return st,pos

def encode_STreasureUpdateNtf(st):
    str=''

    str += addInt(st.count)

    for i in range(st.count):
        _tempstr = encode_STreasureInBag(st.treasures[i])
        str += _tempstr

    return str

def decode_STreasureUpdateNtf(buf):
    st=STreasureUpdateNtf()
    pos=0

    st.count,length = getInt(buf[pos:])
    pos += length

    for i in range(st.count):
        st.treasures[i],length = decode_STreasureInBag(buf[pos:])
    
        pos += length

    return st,pos

def encode_SGeneralErrorNtf(st):
    str=''

    str += addDword(st.errcode)
    str += addString(st.msg)
    return str

def decode_SGeneralErrorNtf(buf):
    st=SGeneralErrorNtf()
    pos=0

    st.errcode,length = getDword(buf[pos:])
    pos += length
    st.msg,length = getString(buf[pos:])
    pos += length
    return st,pos

def encode_SGeneralWordsNtf(st):
    str=''

    str += addString(st.msg)
    return str

def decode_SGeneralWordsNtf(buf):
    st=SGeneralWordsNtf()
    pos=0

    st.msg,length = getString(buf[pos:])
    pos += length
    return st,pos

def encode_SServerStatusReporter(st):
    str=''

    str += addString(st.servername)
    str += addDword(st.maxLoad)
    str += addDword(st.currentLoad)
    str += addDword(st.protocolVer)
    return str

def decode_SServerStatusReporter(buf):
    st=SServerStatusReporter()
    pos=0

    st.servername,length = getString(buf[pos:])
    pos += length
    st.maxLoad,length = getDword(buf[pos:])
    pos += length
    st.currentLoad,length = getDword(buf[pos:])
    pos += length
    st.protocolVer,length = getDword(buf[pos:])
    pos += length
    return st,pos

def encode_SLogConsumeDiamond(st):
    str=''

    str += addDword(st.type)
    str += addDword(st.gID)
    str += addDword(st.itemID)
    return str

def decode_SLogConsumeDiamond(buf):
    st=SLogConsumeDiamond()
    pos=0

    st.type,length = getDword(buf[pos:])
    pos += length
    st.gID,length = getDword(buf[pos:])
    pos += length
    st.itemID,length = getDword(buf[pos:])
    pos += length
    return st,pos

def encode_SPackedFileIndex(st):
    str=''

    str += addString(st.name)
    str += addDword(st.startIndex)
    str += addDword(st.endIndex)
    return str

def decode_SPackedFileIndex(buf):
    st=SPackedFileIndex()
    pos=0

    st.name,length = getString(buf[pos:])
    pos += length
    st.startIndex,length = getDword(buf[pos:])
    pos += length
    st.endIndex,length = getDword(buf[pos:])
    pos += length
    return st,pos

def encode_SPackedFiles(st):
    str=''

    str += addWord(st.count)

    for i in range(st.count):
        _tempstr = encode_SPackedFileIndex(st.files[i])
        str += _tempstr

    return str

def decode_SPackedFiles(buf):
    st=SPackedFiles()
    pos=0

    st.count,length = getWord(buf[pos:])
    pos += length

    for i in range(st.count):
        st.files[i],length = decode_SPackedFileIndex(buf[pos:])
    
        pos += length

    return st,pos

def encode_SMiscDB(st):
    str=''

    str += addInt(st.shootMonsterCount)
    return str

def decode_SMiscDB(buf):
    st=SMiscDB()
    pos=0

    st.shootMonsterCount,length = getInt(buf[pos:])
    pos += length
    return st,pos

def encode_SGetRoleInfoReq(st):
    str=''

    str += addInt(st.i)
    return str

def decode_SGetRoleInfoReq(buf):
    st=SGetRoleInfoReq()
    pos=0

    st.i,length = getInt(buf[pos:])
    pos += length
    return st,pos

def encode_SGetRoleInfoRsp(st):
    str=''


    for i in range(1):
        _tempstr = encode_SRole(st.role)
        str += _tempstr

    return str

def decode_SGetRoleInfoRsp(buf):
    st=SGetRoleInfoRsp()
    pos=0


    for i in range(1):
        st.role,length = decode_SRole(buf[pos:])
    
        pos += length

    return st,pos
g_decode_fun[S_2_C_Protocol_Version_Ntf] = decode_SProtocolVersionNtf
g_encode_fun[S_2_C_Protocol_Version_Ntf] = encode_SProtocolVersionNtf
g_decode_fun[C_2_S_Protocol_Type_Rpt] = decode_SProtocolTypeRpt
g_encode_fun[C_2_S_Protocol_Type_Rpt] = encode_SProtocolTypeRpt
g_decode_fun[C_2_S_Protocol_Type_Rsp] = decode_SProtocolTypeRsp
g_encode_fun[C_2_S_Protocol_Type_Rsp] = encode_SProtocolTypeRsp
g_decode_fun[S_2_C_General_Error_Ntf] = decode_SGeneralErrorNtf
g_encode_fun[S_2_C_General_Error_Ntf] = encode_SGeneralErrorNtf
g_decode_fun[S_2_C_General_Words_Ntf] = decode_SGeneralWordsNtf
g_encode_fun[S_2_C_General_Words_Ntf] = encode_SGeneralWordsNtf
g_decode_fun[C_2_S_Create_Req] = decode_SCreateReq
g_encode_fun[C_2_S_Create_Req] = encode_SCreateReq
g_decode_fun[S_2_C_Create_Rsp] = decode_SCreateRsp
g_encode_fun[S_2_C_Create_Rsp] = encode_SCreateRsp
g_decode_fun[C_2_S_Easy_Login_Req] = decode_SEasyLoginReq
g_encode_fun[C_2_S_Easy_Login_Req] = encode_SEasyLoginReq
g_decode_fun[S_2_C_Easy_Login_Rsp] = decode_SEasyLoginRsp
g_encode_fun[S_2_C_Easy_Login_Rsp] = encode_SEasyLoginRsp
g_decode_fun[C_2_S_Enter_Req] = decode_SEnterReq
g_encode_fun[C_2_S_Enter_Req] = encode_SEnterReq
g_decode_fun[S_2_C_Enter_Rsp] = decode_SEnterRsp
g_encode_fun[S_2_C_Enter_Rsp] = encode_SEnterRsp
g_decode_fun[S_2_C_Kick_Ntf] = decode_SKickNtf
g_encode_fun[S_2_C_Kick_Ntf] = encode_SKickNtf
g_decode_fun[C_2_S_Logoff_Req] = decode_SLogoffReq
g_encode_fun[C_2_S_Logoff_Req] = encode_SLogoffReq
g_decode_fun[S_2_C_Logoff_Rsp] = decode_SLogoffRsp
g_encode_fun[S_2_C_Logoff_Rsp] = encode_SLogoffRsp
g_decode_fun[C_2_S_LoadFinished_Req] = decode_SLoadFinishedReq
g_encode_fun[C_2_S_LoadFinished_Req] = encode_SLoadFinishedReq
g_decode_fun[C_2_S_Create_Ex_Req] = decode_SCreateExReq
g_encode_fun[C_2_S_Create_Ex_Req] = encode_SCreateExReq
g_decode_fun[C_2_S_GmCmd_Req] = decode_SGmcmdReq
g_encode_fun[C_2_S_GmCmd_Req] = encode_SGmcmdReq
g_decode_fun[S_2_C_GmCmd_Rsp] = decode_SGmcmdRsp
g_encode_fun[S_2_C_GmCmd_Rsp] = encode_SGmcmdRsp
g_decode_fun[S_2_C_Basic_DataEx_Ntf] = decode_SBasicDataExNtf
g_encode_fun[S_2_C_Basic_DataEx_Ntf] = encode_SBasicDataExNtf
g_decode_fun[S_2_C_Global_Ntf] = decode_SGlobalNtf
g_encode_fun[S_2_C_Global_Ntf] = encode_SGlobalNtf
g_decode_fun[S_2_C_Basic_Data_Broadcast_Ntf] = decode_SBasicDataBroadcastNtf
g_encode_fun[S_2_C_Basic_Data_Broadcast_Ntf] = encode_SBasicDataBroadcastNtf
g_decode_fun[S_2_C_PROBE_NTF] = decode_SProbeNtf
g_encode_fun[S_2_C_PROBE_NTF] = encode_SProbeNtf
g_decode_fun[C_2_S_PROBE_ANSWER] = decode_SProbeAnswer
g_encode_fun[C_2_S_PROBE_ANSWER] = encode_SProbeAnswer
g_decode_fun[C_2_S_Leave_Msg_2_GM_Req] = decode_SLeaveMsg2GMReq
g_encode_fun[C_2_S_Leave_Msg_2_GM_Req] = encode_SLeaveMsg2GMReq
g_decode_fun[S_2_C_GM_Answer_Rsp] = decode_SGMAnswerRsp
g_encode_fun[S_2_C_GM_Answer_Rsp] = encode_SGMAnswerRsp
g_decode_fun[S_2_C_Server_Status_Ntf] = decode_SServerStatusReporter
g_encode_fun[S_2_C_Server_Status_Ntf] = encode_SServerStatusReporter
g_decode_fun[S_2_S_Server_Status_Reporter] = decode_SServerStatusReporter
g_encode_fun[S_2_S_Server_Status_Reporter] = encode_SServerStatusReporter
g_decode_fun[S_2_C_Server_Load_Finished_Ntf] = decode_SServerLoadFinishNtf
g_encode_fun[S_2_C_Server_Load_Finished_Ntf] = encode_SServerLoadFinishNtf
g_decode_fun[C_2_S_SGetAllStage_Req] = decode_SGetAllStageDescReq
g_encode_fun[C_2_S_SGetAllStage_Req] = encode_SGetAllStageDescReq
g_decode_fun[S_2_C_SGetAllStage_Rsp] = decode_SGetAllStageDescRsp
g_encode_fun[S_2_C_SGetAllStage_Rsp] = encode_SGetAllStageDescRsp
g_decode_fun[C_2_S_SGetStage_Req] = decode_SGetStageReq
g_encode_fun[C_2_S_SGetStage_Req] = encode_SGetStageReq
g_decode_fun[S_2_C_SGetStage_Rsp] = decode_SGetStageRsp
g_encode_fun[S_2_C_SGetStage_Rsp] = encode_SGetStageRsp
g_decode_fun[TOOL_SPackedFiles] = decode_SPackedFiles
g_encode_fun[TOOL_SPackedFiles] = encode_SPackedFiles
g_decode_fun[S_2_C_TeasureUpdate_Ntf] = decode_STreasureUpdateNtf
g_encode_fun[S_2_C_TeasureUpdate_Ntf] = encode_STreasureUpdateNtf
g_decode_fun[C_2_S_Basic_Data_Change_Req] = decode_SBasicDataChangeReq
g_encode_fun[C_2_S_Basic_Data_Change_Req] = encode_SBasicDataChangeReq
g_decode_fun[S_2_C_Basic_Data_Change_Ntf] = decode_SBasicDataChangeNtf
g_encode_fun[S_2_C_Basic_Data_Change_Ntf] = encode_SBasicDataChangeNtf
g_decode_fun[C_2_S_Basic_String_Data_Change_Req] = decode_SBasicDataStringChangeReq
g_encode_fun[C_2_S_Basic_String_Data_Change_Req] = encode_SBasicDataStringChangeReq
g_decode_fun[S_2_C_Basic_String_Data_Change_Ntf] = decode_SBasicDataStringChangeNtf
g_encode_fun[S_2_C_Basic_String_Data_Change_Ntf] = encode_SBasicDataStringChangeNtf
g_decode_fun[C_2_S_GET_ROLE_INFO_REQ] = decode_SGetRoleInfoReq
g_encode_fun[C_2_S_GET_ROLE_INFO_REQ] = encode_SGetRoleInfoReq
g_decode_fun[S_2_C_GET_ROLE_INFO_RSP] = decode_SGetRoleInfoRsp
g_encode_fun[S_2_C_GET_ROLE_INFO_RSP] = encode_SGetRoleInfoRsp
