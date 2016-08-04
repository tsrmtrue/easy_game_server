#ifndef __PROTOCOLDECODE_CPP_H__
#define    __PROTOCOLDECODE_CPP_H__

#include <string>
#include <stdio.h>
#include "pnl_protocol.h"
using namespace std;

int decode_SBasicDataEx(SBasicDataEx& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SGetStageReq(SGetStageReq& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SProtocolTypeRsp(SProtocolTypeRsp& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SKickNtf(SKickNtf& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SPackedFiles(SPackedFiles& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SBasicDataString(SBasicDataString& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SBasicDataNtf(SBasicDataNtf& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SRole(SRole& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SEasyLoginRsp(SEasyLoginRsp& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SEasyRoleInfo4Login(SEasyRoleInfo4Login& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SRegisterReq(SRegisterReq& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SBasicRoleInfo(SBasicRoleInfo& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SLeaveMsg2GMReq(SLeaveMsg2GMReq& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SCreateRsp(SCreateRsp& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SProbeAnswer(SProbeAnswer& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SBasicDataChangeReq(SBasicDataChangeReq& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SGetRoleInfoRsp(SGetRoleInfoRsp& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SBasicDataBroadcastNtf(SBasicDataBroadcastNtf& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SGetRoleInfoReq(SGetRoleInfoReq& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SBindAccountReq(SBindAccountReq& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SGmcmdRsp(SGmcmdRsp& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SLogoffReq(SLogoffReq& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SEnterRsp(SEnterRsp& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SGMAnswerRsp(SGMAnswerRsp& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SEasyLoginReq(SEasyLoginReq& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SLogConsumeDiamond(SLogConsumeDiamond& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SBasicDataChangeNtf(SBasicDataChangeNtf& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SBasicDataExNtf(SBasicDataExNtf& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SGetAllStageDescReq(SGetAllStageDescReq& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SLoadFinishedReq(SLoadFinishedReq& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SGetAllStageDescRsp(SGetAllStageDescRsp& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SProbeNtf(SProbeNtf& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SGlobalNtf(SGlobalNtf& st, unsigned char* pSrc, unsigned int bufLength );
int decode_STreasureUpdateNtf(STreasureUpdateNtf& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SRoleParameters(SRoleParameters& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SGmcmdReq(SGmcmdReq& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SGeneralErrorNtf(SGeneralErrorNtf& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SEnterReq(SEnterReq& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SProtocolTypeRpt(SProtocolTypeRpt& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SCreateExReq(SCreateExReq& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SBasicData(SBasicData& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SServerStatusReporter(SServerStatusReporter& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SBasicDataStringNtf(SBasicDataStringNtf& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SGeneralWordsNtf(SGeneralWordsNtf& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SRegisterRsp(SRegisterRsp& st, unsigned char* pSrc, unsigned int bufLength );
int decode_STreasureInBag(STreasureInBag& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SBindAccountRsp(SBindAccountRsp& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SCreateReq(SCreateReq& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SGetStageRsp(SGetStageRsp& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SEasyRoleInfo4LoginList(SEasyRoleInfo4LoginList& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SLogoffRsp(SLogoffRsp& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SServerLoadFinishNtf(SServerLoadFinishNtf& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SBasicDataStringChangeReq(SBasicDataStringChangeReq& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SBasicDataStringChangeNtf(SBasicDataStringChangeNtf& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SMiscDB(SMiscDB& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SStageFile(SStageFile& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SPackedFileIndex(SPackedFileIndex& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SStageInfo(SStageInfo& st, unsigned char* pSrc, unsigned int bufLength );
int decode_STreasure(STreasure& st, unsigned char* pSrc, unsigned int bufLength );
int decode_SProtocolVersionNtf(SProtocolVersionNtf& st, unsigned char* pSrc, unsigned int bufLength );

#endif    //__PROTOCOLDECODE_CPP_H__
