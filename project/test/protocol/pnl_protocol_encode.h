#ifndef __PROTOCOLENCODE_CPP_H__
#define    __PROTOCOLENCODE_CPP_H__

#include <string>
#include <stdio.h>
#include "pnl_protocol.h"
using namespace std;

int encode_SBasicDataEx(SBasicDataEx& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SGetStageReq(SGetStageReq& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SProtocolTypeRsp(SProtocolTypeRsp& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SKickNtf(SKickNtf& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SPackedFiles(SPackedFiles& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SBasicDataString(SBasicDataString& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SBasicDataNtf(SBasicDataNtf& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SRole(SRole& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SEasyLoginRsp(SEasyLoginRsp& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SEasyRoleInfo4Login(SEasyRoleInfo4Login& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SRegisterReq(SRegisterReq& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SBasicRoleInfo(SBasicRoleInfo& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SLeaveMsg2GMReq(SLeaveMsg2GMReq& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SCreateRsp(SCreateRsp& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SProbeAnswer(SProbeAnswer& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SBasicDataChangeReq(SBasicDataChangeReq& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SGetRoleInfoRsp(SGetRoleInfoRsp& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SBasicDataBroadcastNtf(SBasicDataBroadcastNtf& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SGetRoleInfoReq(SGetRoleInfoReq& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SBindAccountReq(SBindAccountReq& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SGmcmdRsp(SGmcmdRsp& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SLogoffReq(SLogoffReq& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SEnterRsp(SEnterRsp& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SGMAnswerRsp(SGMAnswerRsp& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SEasyLoginReq(SEasyLoginReq& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SLogConsumeDiamond(SLogConsumeDiamond& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SBasicDataChangeNtf(SBasicDataChangeNtf& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SBasicDataExNtf(SBasicDataExNtf& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SGetAllStageDescReq(SGetAllStageDescReq& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SLoadFinishedReq(SLoadFinishedReq& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SGetAllStageDescRsp(SGetAllStageDescRsp& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SProbeNtf(SProbeNtf& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SGlobalNtf(SGlobalNtf& st, unsigned char* pBuf, unsigned int bufLength );
int encode_STreasureUpdateNtf(STreasureUpdateNtf& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SRoleParameters(SRoleParameters& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SGmcmdReq(SGmcmdReq& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SGeneralErrorNtf(SGeneralErrorNtf& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SEnterReq(SEnterReq& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SProtocolTypeRpt(SProtocolTypeRpt& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SCreateExReq(SCreateExReq& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SBasicData(SBasicData& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SServerStatusReporter(SServerStatusReporter& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SBasicDataStringNtf(SBasicDataStringNtf& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SGeneralWordsNtf(SGeneralWordsNtf& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SRegisterRsp(SRegisterRsp& st, unsigned char* pBuf, unsigned int bufLength );
int encode_STreasureInBag(STreasureInBag& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SBindAccountRsp(SBindAccountRsp& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SCreateReq(SCreateReq& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SGetStageRsp(SGetStageRsp& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SEasyRoleInfo4LoginList(SEasyRoleInfo4LoginList& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SLogoffRsp(SLogoffRsp& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SServerLoadFinishNtf(SServerLoadFinishNtf& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SBasicDataStringChangeReq(SBasicDataStringChangeReq& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SBasicDataStringChangeNtf(SBasicDataStringChangeNtf& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SMiscDB(SMiscDB& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SStageFile(SStageFile& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SPackedFileIndex(SPackedFileIndex& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SStageInfo(SStageInfo& st, unsigned char* pBuf, unsigned int bufLength );
int encode_STreasure(STreasure& st, unsigned char* pBuf, unsigned int bufLength );
int encode_SProtocolVersionNtf(SProtocolVersionNtf& st, unsigned char* pBuf, unsigned int bufLength );

#endif    //__PROTOCOLENCODE_CPP_H__
