#include "CUCRRolemgr.h"
#include "ConfigureMgr.h"
#include "EasyLog.h"


using namespace XXXBuffPacker;

CUCRRoleMgr* g_pUCRRoleMgr = NULL;


void CUCRRole::doSend(const unsigned char*pBuf, unsigned int size)
{
	g_pUCRRoleMgr->doSend(m_Socket, pBuf, size);
};



#define DO_PARSE(STYPE)\
	STYPE st={0};\
	if (m_ProtoclType == E_PROTOCOL_TYPE_BINARY)\
	{\
		unsigned char temp[IOCP_RECVBUF_LENGTH] = "";\
		memcpy(temp, pStart, bodySize-sizeof(SHead));\
		int ret = 0;\
		if (0>(ret = decode_##STYPE(st, temp, bodySize-sizeof(SHead))))\
		{\
			errHappen = true;\
			break;\
		}\
	}\
	else\
	{\
		errHappen = true;\
		break;\
	}


#define DO_PARSE_NOBREAK(STYPE)\
	STYPE st={0};\
	if (m_ProtoclType == E_PROTOCOL_TYPE_BINARY)\
	{\
		unsigned char temp[IOCP_RECVBUF_LENGTH] = "";\
		memcpy(temp, pStart, bodySize-sizeof(SHead));\
		int ret = 0;\
		if (0>(ret = decode_##STYPE(st, temp, bodySize-sizeof(SHead))))\
		{\
			errHappen = true;\
		}\
	}\
	else\
	{\
		errHappen = true;\
	}


//else if (m_ProtoclType == E_PROTOCOL_TYPE_JSON)\
//{\
//Json::Reader r;\
//Json::Value v;\
//char temp[IOCP_RECVBUF_LENGTH] = "";\
//memcpy(temp, pStart, bodySize-sizeof(SHead));\
//string s = temp;\
//if (r.parse(s, v))\
//{\
//st = decode_json_##STYPE(v);\
//}\
//else\
//{\
//errHappen = true;\
//break;\
//}\
//}\


#define PREPARE_FOR_PARSE 

//
//#ifdef CODING_BINARY
//	#define PREPARE_FOR_PARSE \
//		unsigned char temp[IOCP_RECVBUF_LENGTH] = "";\
//		memcpy(temp, pStart, bodySize-sizeof(SHead));
//#elseSProtocolTypeRsp
//
//	#define PREPARE_FOR_PARSE \
//		Json::Reader r;\
//		Json::Value v;\
//		char temp[2048] = "";\
//		memcpy(temp, pStart, bodySize-sizeof(SHead));\
//		string s = temp;
//#endif

#define CHECK_ROLE_STATE(b) \
	if (m_State!=b)\
{\
	errHappen = true;\
	break;\
}



#define SENDPACKET(s, o, id)\
	unsigned char temp[1024*50+4] = "";\
	unsigned char encode[1024*50] = "";\
	unsigned int totalsize = 0;\
	int ret = 0;\
	if (0<= (ret = encode_##s(o, encode, sizeof(encode))))\
	{\
		if (pack4Server(temp, sizeof(temp), (const unsigned char *)(encode), ret, id, totalsize))\
		{\
			if (!g_pListenerLbv->doSend(m_Socket, temp, totalsize))\
			{\
				m_State = CUCRRole::E_SEND_BUF_NOT_ENOUGH;\
			}\
		}\
	}


void CUCRRole::reset()
{
	memset(&m_RoleInfo, 0, sizeof(m_RoleInfo));
	memset(&m_AccountInfo, 0, sizeof(m_AccountInfo));
	// m_Socket = socket;
	m_recvBufSize = 0;
	m_State = E_NOT_INIT;
	// x=y=0;
	m_guid = 0;
	m_loginType = -1;
	m_nCurrentProtocolId = 0;
	m_ProtoclType = E_PROTOCOL_TYPE_BINARY;

	temp_my_userid = 0;
	m_pMiscDB = NULL;

}

void CUCRRole::close()
{
	if (m_State == E_ROLE_READY)
	{
		g_pUCRRoleMgr->addLog2DB(m_RoleInfo.userid, m_RoleInfo.rolename, "log_off", m_AccountInfo.macAddress);
	}
	m_State = E_CLOSING;

}




void CUCRRole::sendGeneralError_p(const char* pError, unsigned int n, unsigned int errcode)
{
	char _t[256] = "";
	snprintf(_t, sizeof(_t)-1, pError, n);
	sendGeneralError(_t, errcode);
}

void CUCRRole::sendGeneralError_p(const char* pError, unsigned int d1, unsigned int d2, unsigned int errcode)
{
	char _t[256] = "";
	snprintf(_t, sizeof(_t)-1, pError, d1, d2);
	sendGeneralError(_t, errcode);
}

void CUCRRole::sendGeneralError_p(const char* pError, const char* ps1, unsigned int errcode)
{
	char _t[256] = "";
	snprintf(_t, sizeof(_t)-1, pError, ps1);
	sendGeneralError(_t, errcode);
}

void CUCRRole::sendGeneralError_p(const char* pError, const char* ps1, unsigned int d1, unsigned int errcode)
{
	char _t[256] = "";
	snprintf(_t, sizeof(_t)-1, pError, ps1, d1);
	sendGeneralError(_t, errcode);
}

void CUCRRole::sendGeneralError_p(const char* pError, const char* ps1, unsigned int pd1, unsigned int pd2, unsigned int errcode)
{
	char _t[256] = "";
	snprintf(_t, sizeof(_t)-1, pError, ps1, pd1, pd2);
	sendGeneralError(_t, errcode);
}


void CUCRRole::sendGeneralError(const char* pError, unsigned int errcode)
{
	SGeneralErrorNtf rsp={0};
	rsp.errcode = errcode;
	snprintf(rsp.msg, sizeof(rsp.msg)-1, pError);
	SENDPACKET(SGeneralErrorNtf, rsp, S_2_C_General_Error_Ntf);
}
void CUCRRole::sendSGeneralWords(const char* pWords, unsigned int p1)
{
	char temp[256] = "";
	snprintf(temp, sizeof(temp)-1, pWords, p1);
	sendSGeneralWords(temp);
}
void CUCRRole::sendSGeneralWords(const char* pWords)
{
	SGeneralWordsNtf sgwn = {0};
	unsigned int c = strlen(pWords)>(sizeof(sgwn.msg)-1)?(sizeof(sgwn.msg)-1):strlen(pWords);
	memcpy(sgwn.msg, pWords, c);
	sendSGeneralWordsNtf(sgwn);
	// sendGeneralError(WU_CUOWU);
}

void CUCRRole::sendSGlobalNtf(unsigned int type, const char* pMsg, const char* s1)//	S_2_C_Global_Ntf, //SGlobalNtf
{
	if (pMsg != NULL)
	{
		char temp[128] = "";
		snprintf(temp, sizeof(temp)-1, pMsg, s1);
		sendSGlobalNtf(type, temp);
	}
}

void CUCRRole::sendSGlobalNtf(unsigned int type, const char* pMsg, unsigned int p1)//	S_2_C_Global_Ntf, //SGlobalNtf
{
	if (pMsg != NULL)
	{
		char temp[128] = "";
		snprintf(temp, sizeof(temp)-1, pMsg, p1);
		sendSGlobalNtf(type, temp);
	}
}

void CUCRRole::sendSGlobalNtf(unsigned int type, const char* pMsg, unsigned int p1, unsigned int p2)//	S_2_C_Global_Ntf, //SGlobalNtf
{
	if (pMsg != NULL)
	{
		char temp[128] = "";
		snprintf(temp, sizeof(temp)-1, pMsg, p1, p2);
		sendSGlobalNtf(type, temp);
	}
}

void CUCRRole::sendSGlobalNtf(unsigned int type, const char* pMsg, const char* s1, unsigned int p1)//	S_2_C_Global_Ntf, //SGlobalNtf
{
	if (pMsg != NULL)
	{
		char temp[128] = "";
		snprintf(temp, sizeof(temp)-1, pMsg, s1, p1);
		sendSGlobalNtf(type, temp);
	}
}

void CUCRRole::sendSGlobalNtf(unsigned int type, const char* pMsg, unsigned int p1, const char* s1)//	S_2_C_Global_Ntf, //SGlobalNtf
{
	if (pMsg != NULL)
	{
		char temp[128] = "";
		snprintf(temp, sizeof(temp)-1, pMsg, p1, s1);
		sendSGlobalNtf(type, temp);
	}
}

void CUCRRole::sendSGlobalNtf(SGlobalNtf& sgn)
{
	SENDPACKET( SGlobalNtf, sgn, S_2_C_Global_Ntf);
}

void CUCRRole::sendProtocolVersionNtf()//	S_2_C_Protocol_Version_Ntf, //SProtocolVersionNtf
{
	SProtocolVersionNtf ntf = {E_PROTOCOL_NOW};
	SENDPACKET( SProtocolVersionNtf, ntf, S_2_C_Protocol_Version_Ntf);
}

void CUCRRole::sendSGlobalNtf(unsigned int type, const char* pMsg)//	S_2_C_Global_Ntf, //SGlobalNtf
{
	SGlobalNtf ntf = {0};
	ntf.t = type;
	CUtility::safeStrCpy(ntf.msg, sizeof(ntf.msg), pMsg);
	SENDPACKET( SGlobalNtf, ntf, S_2_C_Global_Ntf);
}

void CUCRRole::sendSBasicDataExNtf(SBasicDataExNtf& sbden) //S_2_C_Basic_DataEx_Ntf, //
{
	if (sbden.count == 0)
	{
		return;
	}
	SENDPACKET( SBasicDataExNtf, sbden, S_2_C_Basic_DataEx_Ntf);
}

void CUCRRole::sendSGeneralWordsNtf(SGeneralWordsNtf& sgwn) //S_2_C_General_Words_Ntf
{
	SENDPACKET( SGeneralWordsNtf, sgwn, S_2_C_General_Words_Ntf);
}

void CUCRRole::sendSProbeNtf(SProbeNtf& ntf) //		S_2_C_PROBE_NTF, //SProbeNtf生存判断通知
{
	SENDPACKET(SProbeNtf, ntf, S_2_C_PROBE_NTF);
}

// void CUCRRole::sendBindPassportNtf()
// {
// 	BASICDATAMAP mapinfo ;
// 	if (m_loginType == E_Login_Passport)
// 	{
// 		addBasicDataEx(mapinfo, 0, E_Basic_Data_Passport_Bind, 1);
// 	}
// 	else
// 	{
// 		addBasicDataEx(mapinfo, 0, E_Basic_Data_Passport_Bind, 0);
// 	}
// 	SBasicDataExNtf sbden = {0};
// 	buildSBasicDataExNtf(sbden, mapinfo);
// 	sendSBasicDataExNtf(sbden);

// }

void CUCRRole::sendSServerStatusReporter(SServerStatusReporter& ssr) //,S_2_C_Server_Status_Ntf, //SServerStatusReporter
{
	SENDPACKET(SServerStatusReporter, ssr, S_2_C_Server_Status_Ntf);
}

void CUCRRole::sendSProtocolTypeRsp(SProtocolTypeRsp& rsp) //	C_2_S_Protocol_Type_Rsp, //SProtocolTypeRsp，当可以用的时候,服务器返回下0. 
{
	SENDPACKET(SProtocolTypeRsp, rsp, C_2_S_Protocol_Type_Rsp);
}

// void CUCRRole::sendSTreasureUpdateNtf(STreasureUpdateNtf& stun)
// {
// 	SENDPACKET(STreasureUpdateNtf, stun, S_2_C_TeasureUpdate_Ntf);

// }


void CUCRRole::sendSLoginRsp(SEasyLoginRsp& slr)
{
	SENDPACKET(SEasyLoginRsp, slr, S_2_C_Easy_Login_Rsp);
}
void CUCRRole::sendSEnterRsp(SEnterRsp& ser)
{
	SENDPACKET(SEnterRsp, ser, S_2_C_Enter_Rsp);
}

void CUCRRole::sendSCreateRsp(SCreateRsp& scr)
{
	SENDPACKET(SCreateRsp, scr, S_2_C_Create_Rsp);
}

void CUCRRole::sendSServerLoadFinishNtf(SServerLoadFinishNtf & slfn)  //S_2_C_Server_Load_Finished_Ntf, //SServerLoadFinishNtf
{
	SENDPACKET(SServerLoadFinishNtf, slfn, S_2_C_Server_Load_Finished_Ntf);

}

void CUCRRole::sendSGetAllStageRsp(SGetAllStageDescRsp & ntf)
{
	SENDPACKET(SGetAllStageDescRsp, ntf, S_2_C_SGetAllStage_Rsp);
}

void CUCRRole::sendSGetStageRsp(SGetStageRsp &ntf)//	S_2_C_SGetStage_Rsp, //。
{
	SENDPACKET(SGetStageRsp, ntf, S_2_C_SGetStage_Rsp);
}

void CUCRRole::sendSBasicDataChangeNtf(SBasicDataChangeNtf& sbdcn)//S_2_C_Basic_Data_Change_Ntf, //
{
	SENDPACKET(SBasicDataChangeNtf, sbdcn, S_2_C_Basic_Data_Change_Ntf);
}
void CUCRRole::sendSBasicDataStringChangeNtf(SBasicDataStringChangeNtf& sbdscn)//	S_2_C_Basic_String_Data_Change_Ntf, 
{
	SENDPACKET(SBasicDataStringChangeNtf, sbdscn, S_2_C_Basic_String_Data_Change_Ntf);
}

void CUCRRole::buildBasicDataNtf(map<int, int >&mapInfo, SBasicDataNtf&ntf)
{
	map<int, int >::iterator iter = mapInfo.begin();
	unsigned int max = sizeof(ntf.t)/sizeof(ntf.t[0]);
	for(; iter!=mapInfo.end() && ntf.count<max; ++iter)
	{
		ntf.t[ntf.count].v = iter->second;
		ntf.t[ntf.count].t = iter->first;
		++ntf.count;
	}
}

void CUCRRole::buildBasicDataStringNtf(map<int, std::string >&mapInfo, SBasicDataStringNtf&ntf)
{
	map<int, std::string >::iterator iter = mapInfo.begin();
	unsigned int max = sizeof(ntf.t)/sizeof(ntf.t[0]);
	for(; iter!=mapInfo.end() && ntf.count<max; ++iter)
	{
		CUtility::safeStrCpy(ntf.t[ntf.count].sv, sizeof(ntf.t[ntf.count].sv), iter->second.c_str());
		ntf.t[ntf.count].t = iter->first;
		++ntf.count;
	}
}


bool CUCRRole::onProtocolReport(SProtocolTypeRpt sptr)
{
	printf("the protocol report type is %d, version is %d \n", sptr.type, sptr.version);
	struct SProtocolTypeRsp sptrsp ;
	sptrsp.errcode = 76;
	SENDPACKET(SProtocolTypeRsp, sptrsp, C_2_S_Protocol_Type_Rsp);
	return true;
}

bool CUCRRole::onEasyLogin(SEasyLoginReq selr)
{
	// printf("recv the easy login %d , account is %s\n", selr.type, selr.easyAccount);
	// SLoginRsp rsp = {0};
	// rsp.type = 12;
	// rsp.errcode = 34;
	// // sprintf(rsp.roleList.easyRoleList.rolename,"hello nike");
	// rsp.roleList.easyRoleList.userid = 12345;
	// SENDPACKET(SEasyLoginRsp, rsp, S_2_C_Login_Rsp);
	return true;
}

void CUCRRole::checkAndSaveAuto()
{
	if (m_lastSaveTime >= CUtility::getCurrentTimeInt())
	{
		m_lastSaveTime = CUtility::getCurrentTimeInt();
	}
	if (m_lastSaveTime + 2*60 < CUtility::getCurrentTimeInt())
	{
		m_lastSaveTime = CUtility::getCurrentTimeInt();
		// save2Db();
	}
}

#define TREATE_INT_OVERLOAD(target, max, defaultMax) \
	if ((unsigned int)(target) > max)\
{\
	target = defaultMax;\
}



#define CONVERT_ALL_UPDATE \
	tgt.diamond				= src.diamond;\
	tgt.money				= src.money;\
	tgt.vigor				= src.vigor;\
	tgt.isInit				= src.isInit;\
	tgt.userid				= src.userid;\
	tgt.accountid			= src.accountid;\
	tgt.professionId		= src.professionId;\
	tgt.money				= src.money;\
	tgt.diamond				= src.diamond;\
	tgt.vigor				= src.vigor;\
	tgt.isInit				= src.isInit;\
	tgt.loginCount			= src.loginCount;\
	tgt.lastLogoffTime		= src.lastLogoffTime;\
	tgt.currentGuid			= src.currentGuid;\
	memcpy(tgt.rolename, src.rolename, sizeof(src.rolename));\
	/*ÈÎÎñ*/\
	tgt._current_taskFinished_length = src._current_taskFinished_length;\
	memcpy(tgt.taskFinished, src.taskFinished, src._current_taskFinished_length);\
	tgt._current_taskCurrent_length = src._current_taskCurrent_length;\
	memcpy(tgt.taskCurrent, src.taskCurrent, src._current_taskCurrent_length);\
	/*guid*/\
	tgt.currentGuid = src.currentGuid;\
	/*¾«Ó¢¸±±¾×ã¼£*/\
	tgt._current_todayFubenRecord_length = src._current_todayFubenRecord_length;\
	memcpy(tgt.todayFubenRecord, src.todayFubenRecord, src._current_todayFubenRecord_length);\
	/*½ñÈÕÁìÈ¡½±Àø¼ÇÂ¼*/\
	tgt._current_todayPrizeRecord_length = src._current_todayPrizeRecord_length;\
	memcpy(tgt.todayPrizeRecord, src.todayPrizeRecord, src._current_todayPrizeRecord_length);\
	/*ÁìÈ¡½±Àø¼ÇÂ¼*/\
	tgt._current_prizeRecord_length = src._current_prizeRecord_length;\
	memcpy(tgt.prizeRecord, src.prizeRecord, src._current_prizeRecord_length);\
	/*miscÐÅÏ¢*/\
	tgt._current_misc_length = src._current_misc_length;\
	memcpy(tgt.misc, src.misc, src._current_misc_length);\
	tgt.loginCount = src.loginCount;\
	tgt.professionId = src.professionId;\
	tgt.accountid = src.accountid;\
	tgt.lastLogoffTime = src.lastLogoffTime;\
	/*°ü¹üÐÅÏ¢*/\
	tgt._current_package_length = src._current_package_length;\
	memcpy(tgt.package, src.package, src._current_package_length);\
	/*³ÆºÅÐÅÏ¢*/\
	tgt._current_titles_length = src._current_titles_length;\
	memcpy(tgt.titles, src.titles, src._current_titles_length);\
	/*×ã¼£ÐÅÏ¢*/\
	tgt._current_footmark_length = src._current_footmark_length;\
	memcpy(tgt.footmark, src.footmark, src._current_footmark_length);\
	/*²ÎÊýÐÅÏ¢*/\
	tgt._current_paremeterNow_length = src._current_paremeterNow_length;\
	memcpy(tgt.paremeterNow, src.paremeterNow, src._current_paremeterNow_length);\
	/*²ÎÊýÐÅÏ¢ÀúÊ·×î´ó*/\
	tgt._current_paremeterMax_length = src._current_paremeterMax_length;\
	memcpy(tgt.paremeterMax, src.paremeterMax, src._current_paremeterMax_length);\
	/*²ÎÊýÐÅÏ¢ÀúÊ·×îÐ¡*/\
	tgt._current_paremeterMin_length = src._current_paremeterMin_length;\
	memcpy(tgt.paremeterMin, src.paremeterMin, src._current_paremeterMin_length);\



void convertAll2Update(Sql_SelectAll_role &src, Sql_Update_role_save_role_by_userid& tgt)
{
	CONVERT_ALL_UPDATE;
}

void convertUpdate2All(Sql_Update_role_save_role_by_userid &src, Sql_SelectAll_role& tgt)
{
	CONVERT_ALL_UPDATE;
}


void CUCRRole::save2Db()
{
	if (m_RoleInfo.userid > 0)
	{
		CMySQLConn* m_pMyConn = g_pUCRRoleMgr->getMysqlConn();

		TREATE_INT_OVERLOAD(m_RoleInfo.money, MAX_INT, MAX_INT);
		TREATE_INT_OVERLOAD(m_RoleInfo.diamond, MAX_INT, MAX_INT)
		//TREATE_INT_OVERLOAD(m_RoleInfo.level, MAX_INT, MAX_INT)
		TREATE_INT_OVERLOAD(m_RoleInfo.professionId, MAX_INT, MAX_INT)
		//TREATE_INT_OVERLOAD(m_RoleInfo.exp, MAX_INT, MAX_INT)
		//TREATE_INT_OVERLOAD(m_RoleInfo.popularity, MAX_INT, MAX_INT)
		//TREATE_INT_OVERLOAD(m_RoleInfo.expTotal, MAX_INT, MAX_INT)
		//TREATE_INT_OVERLOAD(m_RoleInfo.starlevel, MAX_INT, MAX_INT)
		TREATE_INT_OVERLOAD(m_RoleInfo.currentGuid, MAX_INT, MAX_INT)
		//TREATE_INT_OVERLOAD(m_RoleInfo.exploit, MAX_INT, MAX_INT)
		TREATE_INT_OVERLOAD(m_RoleInfo.vigor, MAX_INT, MAX_INT)
		TREATE_INT_OVERLOAD(m_RoleInfo.isInit, MAX_INT, MAX_INT)
		TREATE_INT_OVERLOAD(m_RoleInfo.loginCount, MAX_INT, MAX_INT)
		//TREATE_INT_OVERLOAD(m_RoleInfo.showLevel, MAX_INT, MAX_INT)
		//TREATE_INT_OVERLOAD(m_RoleInfo.currentArrayId, MAX_INT, MAX_INT)


		m_RoleInfo.lastLogoffTime = CUtility::getCurrentTimeInt();
	    //同时更新玩家快照最后下线的时间
		//g_pFriendMgr->updateRoleLastLogoffTime(this);

		Sql_Update_role_save_role_by_userid st = {0};
		//m_RoleInfo.showLevel = getShowLevelNew();
		convertAll2Update(m_RoleInfo, st);
		char temp[1024*100] = "";
		MACRO_ESCAPE_FIELDS_SAVE_ROLE_BY_USERID_ROLE(st);
		snprintf(temp, sizeof(temp)-1, UPDATE_SQL_ROLE_SAVE_ROLE_BY_USERID);
		//CMySQLRecordSet * poRs = NULL;
		unsigned long long insertId = 0;
		int ret = g_pUCRRoleMgr->getMysqlConn()->ExecuteSql(temp, &insertId);
		if(ret < 0)
		{
			// LOG(ELog_Save_Role_Failed, st.userid, "", "", 0, 0, 0, 0);
			// //dump »úÖÆtodo
			// g_Log->addFailedRole(st);
		}
		else
		{
			printf("save role info %d into db \n", insertId);
		}
	}
}

bool CUCRRole::checkIOS7Mac(const char* pMac)
{
	string _t("020000000000");
	if(pMac != NULL 
		&& _t == pMac)
	{
		return true;
	}
	return false;
}

bool CUCRRole::checkInvalid(const char* pSrc, unsigned int len)
{
	if (pSrc == NULL)
	{
		return false;
	}
	for(unsigned int i=0; i<len; ++i)
	{
		unsigned char c = (unsigned char)*(pSrc+i);
		if(c<=47
			|| (58<=c && c<=64)
			|| (91<=c && c<=96)
			|| (123<=c && c<=127)
			)
		{
			return true;
		}
	}
	return false;
}



unsigned int CUCRRole::getUserId()
{
	return m_RoleInfo.userid;
}


void CUCRRole::buildRole(SRole & role)
{

	role.roleBasic.userid = getUserId();
	// role.roleBasic.showLevel = getShowLevelNew();
	//role.roleBasic.exp = m_RoleInfo.exp;
	role.roleBasic.guid = getRoleGuid();
	//role.roleBasic.level = m_RoleInfo.level;
	//role.roleBasic.popularity = m_RoleInfo.popularity;
	role.roleBasic.professionId = m_RoleInfo.professionId;
	memcpy(role.roleBasic.rolename ,m_RoleInfo.rolename, sizeof(m_RoleInfo.rolename));
	role.roleBasic.diamond = m_RoleInfo.diamond;
	role.roleBasic.money = m_RoleInfo.money;
	//role.roleBasic.exploit = m_RoleInfo.exploit;
	// role.roleBasic.vigor = getVigour();
	// role.roleBasic.vigorMax = getMaxVigor();
	// role.roleBasic.leaderForce = getLeaderForce();
	unsigned int tempLevel = 0;
}


bool CUCRRole::init(Sql_SelectAll_role& roleInfo)
{

	// g_pRoleMgr->checkAndAddUsrId(roleInfo, m_Socket);
	m_RoleInfo = roleInfo;
	m_RoleInfo.loginCount ++;
	m_State = E_ROLE_READY;
	m_guid = roleInfo.userid;

	//称号相关参数信息 

	if (sizeof(SMiscDB) > sizeof(m_RoleInfo.misc))
	{
		return false;
	}
	m_pMiscDB = (SMiscDB*)m_RoleInfo.misc;
	m_RoleInfo._current_misc_length = sizeof(SMiscDB);

	//包裹仓库
	// m_pDBTreasureArray = new CEasyTreasureArray(m_RoleInfo.package, m_RoleInfo._current_package_length, sizeof(m_RoleInfo.package), MAX_TREASURE_CAPACITY);
	//检测初始化
	if (m_RoleInfo.isInit == 0)
	{
		initOnCreate();
	}
	// LOG(E_LOG_EVENT_LOGIN, m_RoleInfo.userid, "ok", "", m_RoleInfo.loginCount, 0,0,0);

	return true;
}


bool CUCRRole::initOnCreate()
{
	m_RoleInfo.isInit = 1;

	return true;
}

#define CHECK_CLOSING_ON_DB_EVENT \
	m_State = E_DATABASE_ERROR;



void CUCRRole::sendInitDataOnLoginSuccess()//当登陆成功以后,发送其他的初始包
{
	SBasicDataChangeNtf sbdcn = {0};
	map<int, int > mapInfo;
	mapInfo[E_BDT_KILL_COUNT] = m_pMiscDB->shootMonsterCount;
	buildBasicDataNtf(mapInfo, sbdcn.sbdn);
	sendSBasicDataChangeNtf(sbdcn);
}

void CUCRRole::buildAllStageRsp(SGetAllStageDescRsp& rsp)
{
	STAGECONFIGVECTOR v;
	if (g_pConfigureMgr->getAllStageFileInfo(v))
	{
		for (int i = 0; i < v.size(); i++)
		{
			CUtility::safeStrCpy(rsp.stages[i].desc, sizeof(rsp.stages[i].desc), v[i].desc);
			memcpy((char*)(rsp.stages[i].md5), v[i].md5, sizeof(rsp.stages[i].md5));
			CUtility::safeStrCpy(rsp.stages[i].name, sizeof(rsp.stages[i].name), v[i].stageName);
			rsp.stages[i].size = v[i].length;
			rsp.stages[i].stageId = v[i].id;
			rsp.count ++;
		}
	}
}

bool CUCRRole::checkWrongProtocol()
{
	// if (m_State == )
	{
		/* code */
	}
	return true;
}

bool CUCRRole::onTimer()
{
	// checkAndRefreshDaily();
	//环任务，如果是老号，还没到刷新的时候,也没有接受任何环任务，强制刷新
	
	//自动保存数据
	checkAndSaveAuto();
	return true;
}

bool CUCRRole::onRun(bool & isBusy)
{

	if (!checkWrongProtocol())
	{
		return false;
		/* code */
	}
	bool errHappen = false;
	unsigned char* pStart = NULL;
	unsigned int protoclId = 0;
	unsigned int curIndex = 0;
	unsigned int bodySize = 0;
	if (m_State == E_DATABASE_ERROR)
	{
		return false;
	}
	if (m_State == E_ROLE_READY)
	{
		onTimer();
	}

	if (m_recvBufSize == 0)
	{
		return true;
	}

	m_nCurrentProtocolId = 0;
	if (unPack4Server(m_recvBuf+curIndex, m_recvBufSize, protoclId, pStart, bodySize))
	{

		m_nCurrentProtocolId = protoclId;
		switch (protoclId)
		{
			case C_2_S_Enter_Req:
			{
				DO_PARSE(SEnterReq);
			}
			break;
			case C_2_S_LoadFinished_Req:
			{
				CHECK_ROLE_STATE(E_ROLE_READY);
				DO_PARSE(SLoadFinishedReq);
				SServerLoadFinishNtf slfn;
				sendSServerLoadFinishNtf(slfn);

			}
			break;
			case C_2_S_GmCmd_Req:
			{
				CHECK_ROLE_STATE(E_ROLE_READY);
				DO_PARSE(SGmcmdReq);
			}
			break;
			case C_2_S_SGetAllStage_Req:
				{
					CHECK_ROLE_STATE(E_ROLE_READY);
					SGetAllStageDescRsp rsp = {0};
					buildAllStageRsp(rsp);
					sendSGetAllStageRsp(rsp);
					printf("C_2_S_SGetAllStage_Req  %d    \n", rsp.count);
				}
				break;
			case C_2_S_SGetStage_Req:
				{
					CHECK_ROLE_STATE(E_ROLE_READY);
					DO_PARSE(SGetStageReq);
					SGetStageRsp rsp = {0};
					rsp.file.stageId = st.stageId;
					rsp.file.blockId = st.blockId;
					g_pConfigureMgr->getStageFileById(rsp.file, rsp.totalSize);
					sendSGetStageRsp(rsp);
					printf("C_2_S_SGetStage_Req stageid %d  blockid %d \n", st.stageId, st.blockId);

				}
				break;

			default:
				{
					errHappen = true;
				}
				break;

		}
		curIndex += bodySize ;
		m_recvBufSize -= bodySize ;
		memmove(m_recvBuf, m_recvBuf+curIndex, m_recvBufSize);
	}
	return true;
}

bool CUCRRole::checkFirstProtocolRecved(unsigned int needProtocolId, unsigned int & bodySize, unsigned char*& pStart)
{
	unsigned int protocolId = 0;
	bodySize = 0;
	unPack4Server(m_recvBuf, m_recvBufSize, protocolId, pStart, bodySize);
	return needProtocolId == protocolId;
}

void CUCRRole::popFirstProtocol()
{
	unsigned int protocolId = 0;
	unsigned char* pStart = NULL;
	unsigned int bodySize = 0;
	unPack4Server(m_recvBuf, m_recvBufSize, protocolId, pStart, bodySize);
	if (bodySize > 0)
	{
		m_recvBufSize -= bodySize ;
		memmove(m_recvBuf, m_recvBuf+bodySize, m_recvBufSize);
	}
}


void CUCRRole::onRunCoroutine(bool& isBusy)
{
	if (m_State == E_DATABASE_ERROR 
		|| m_State == E_CLOSING
		|| m_State == E_SEND_BUF_NOT_ENOUGH)
	{
		// release and destroy
		return ;
	}

	if (m_State == E_ROLE_READY)
	{
		onRun(isBusy);
	}
	else
	{
		if (m_State == E_NOT_INIT )
		{
			sendProtocolVersionNtf();
			m_State = E_REGISTING_ACCOUNT;
			return;
		}
		//

		if (m_State == E_REGISTING_ACCOUNT)
		{
			unsigned int bodySize = 0;
			unsigned char* pStart = NULL;
			if (checkFirstProtocolRecved(C_2_S_Easy_Login_Req, bodySize, pStart))
			{
				bool errHappen = false;

				DO_PARSE_NOBREAK(SEasyLoginReq);
				CMySQLConn* m_pMyConn = g_pUCRRoleMgr->getMysqlConn();
				if (m_DBTask_State == E_DBTASK_NO_TASK)
				{
					m_DBTask_State = E_DBTASK_JUMP_2_DB;
					m_CUR_State = E_COROUTINE_STAY_DB;

					g_pUCRRoleMgr->sinkIntoDB(this);
					return ;
				}
				// jump to db pthread
				else if (m_DBTask_State == E_DBTASK_JUMP_2_DB)
				{

					memset(&m_sdbw_temp, 0, sizeof(SDB_Wrap));
					unsigned int macLength = strlen(st.easyAccount);
					if (macLength >= sizeof(m_sdbw_temp._u.st_Sql_SelectAll_account_login_by_MAC.macAddress))
					{
						macLength = sizeof(m_sdbw_temp._u.st_Sql_SelectAll_account_login_by_MAC.macAddress) - 1;
					}
					strncpy(m_sdbw_temp._u.st_Sql_SelectAll_account_login_by_MAC.macAddress, st.easyAccount, macLength);
					printf(" 3.1. macLength > 12 \n" );

					int ret = 0;
					CMySQLRecordSet * poRs = NULL;
					try
					{
						char temp[1024] = "";
						Sql_SelectAll_account_login_by_MAC& ssalbm = m_sdbw_temp._u.st_Sql_SelectAll_account_login_by_MAC;
						MACRO_ESCAPE_FIELDS_LOGIN_BY_MAC_ACCOUNT(ssalbm);
						snprintf(temp, sizeof(temp)-1, SELECT_SQL_ACCOUNT_LOGIN_BY_MAC(ssalbm));
						printf("login by mac %s \n", temp);
						ret = g_pUCRRoleMgr->getMysqlConn()->ExecuteSqlRs(temp, &poRs);
						if(SDDB_HAS_RECORDSET == ret && poRs != NULL )
						{
							//µÃµ½Êý¾Ý,·µ»Ø
							m_sdbw_temp.rcCount = poRs->GetRecordCount();
							if (m_sdbw_temp.rcCount > 0)
							{
								m_sdbw_temp.rcCount = 1;
								memset(&(m_sdbw_temp._u), 0, sizeof(m_sdbw_temp._u));
								Sql_SelectAll_account &_saa = *(Sql_SelectAll_account*)(m_sdbw_temp._u.temp);
								if (poRs->GetRecord())
								{
									CONVERT_RECORD_ACCOUNT_SELECTALL(*poRs, _saa);
								}

								// printf("---------------find account macaddress  %s\n", _saa.macAddress);
								poRs->Release();
								poRs = NULL;
								//µÃµ½½ÇÉ«ÁÐ±í
								SEasyRoleInfo4LoginList &_roleList = *(SEasyRoleInfo4LoginList*)(m_sdbw_temp._u.temp + sizeof(Sql_SelectAll_account));
								if (_saa.accountid > 0)
								{
									int _anchor = 0;
									char temp2[256] = "";
									snprintf(temp2, sizeof(temp2)-1, SELECT_SQL_ROLE_GET_ROLELIST_BY_ACCOUNTID(_anchor) _saa.accountid);
									
									printf("find by account %s \n", temp2);
									
									int ret2 = g_pUCRRoleMgr->getMysqlConn()->ExecuteSqlRs(temp2, &poRs);
									if(SDDB_HAS_RECORDSET == ret2 && poRs != NULL )
									{
										//µÃµ½Êý¾Ý,·µ»Ø
										int _max_role_list = sizeof(_roleList.easyRoleList)/sizeof(_roleList.easyRoleList[0]);
										while (poRs->GetRecord() && _roleList.count < _max_role_list)
										{
											SEasyRoleInfo4Login &_st = _roleList.easyRoleList[_roleList.count];
											CONVERT_RECORD_ROLE_GET_ROLELIST_BY_ACCOUNTID(*poRs, _st);
											_roleList.count ++;
											break;
										}
										poRs->Release();
										poRs = NULL;
										// get role info directly
										{
											char temp3[256] = "";
											Sql_SelectAll_role_get_role_by_accountid_userid ssrgrbau = {};
											ssrgrbau.userid = _roleList.easyRoleList[0].userid;
											ssrgrbau.accountid = _saa.accountid;
											snprintf(temp3, sizeof(temp3)-1, SELECT_SQL_ROLE_GET_ROLE_BY_ACCOUNTID_USERID(ssrgrbau));
											int ret3 = g_pUCRRoleMgr->getMysqlConn()->ExecuteSqlRs(temp3, &poRs);
											if(SDDB_HAS_RECORDSET == ret3 && poRs != NULL)
											{
												if (poRs->GetRecord())
												{
													memset(&m_RoleInfo, 0, sizeof(m_RoleInfo));
													CONVERT_RECORD_ROLE_SELECTALL(*poRs, m_RoleInfo);
													// printf("get roleinfo directly  %s \n", m_RoleInfo.rolename);
													// addRoleData(p->_u.st_Sql_SelectAll_role);
													// addAccount2UserId(p->_u.st_Sql_SelectAll_role.accountid, p->_u.st_Sql_SelectAll_role.userid);
												}
												poRs->Release();
												poRs = NULL;

											}
											else if (SDDB_NO_RECORDSET == ret)
											{
												//checked before ,can not be here
											}

										}


									}
									else
									{
									
									}
								}
							}
							m_sdbw_temp.dbErrcode = SDDB_HAS_RECORDSET;

						}
						else if (SDDB_NO_RECORDSET == ret)
						{
							//Èç¹ûÃ»ÓÐ»ñµÃ,Ôò´´½¨
							char temp2[1024] = "";
							MACRO_ESCAPE_FIELDS_CREATE_ACCOUNT_BY_MAC_ACCOUNT(ssalbm);
							snprintf(temp2, sizeof(temp2)-1, INSERT_SQL_CREATE_ACCOUNT_BY_MAC_ACCOUNT, MACRO_STRUCT_FIELDS_CREATE_ACCOUNT_BY_MAC_ACCOUNT(ssalbm));
							//CMySQLRecordSet * poRs = NULL;

							printf("------------create account by mac %s \n", temp2);

							m_sdbw_temp.insertId = 0;
							ret = g_pUCRRoleMgr->getMysqlConn()->ExecuteSql(temp2, &(m_sdbw_temp.insertId));
							if (ret > 0)
							{
								Sql_SelectAll_account _ssa = {0};
								_ssa.accountid = (int)m_sdbw_temp.insertId;
								CUtility::safeStrCpy(_ssa.macAddress, sizeof(_ssa.macAddress), ssalbm.macAddress);
								memset(&(m_sdbw_temp._u), 0, sizeof(m_sdbw_temp._u));
								Sql_SelectAll_account &ssaa = *(Sql_SelectAll_account*)(m_sdbw_temp._u.temp);
								ssaa = _ssa;
								m_sdbw_temp.dbErrcode = SDDB_HAS_RECORDSET;
								m_sdbw_temp.rcCount = 1;
								printf("create account macaddress  %s\n", ssaa.macAddress);
							}
						}
					}
					catch(...)
					{
						// LOG(E_LOG_EVENT_DB_FAILED,0,"db except","",p->operateId,0,0,0);
						ret = SDDB_INVALID_OP;
					}
					if (poRs != NULL)
					{
						poRs->Release();
						poRs = NULL;
					}

					m_DBTask_State = E_DBTASK_BACK_FROM_DB;

					/* code */
					m_CUR_State = E_COROUTINE_STAY_MAIN;
					g_pUCRRoleMgr->backFromDB();

					return;
				}
				// back from db pthread
				else if (m_DBTask_State == E_DBTASK_BACK_FROM_DB)
				{
					Sql_SelectAll_account &_saa = *(Sql_SelectAll_account*)(m_sdbw_temp._u.temp);
					SEasyRoleInfo4LoginList &_roleList = *(SEasyRoleInfo4LoginList*)(m_sdbw_temp._u.temp + sizeof(Sql_SelectAll_account));

					//使用mac登陆
					SEasyLoginRsp st = {0};
					st.type = m_loginType;
					if (m_sdbw_temp.dbErrcode == SDDB_HAS_RECORDSET)
					{
						st.errcode = E_LOGIN_ACCOUNT_SUCCESS;
						m_AccountInfo = _saa;
						st.roleList = _roleList;
						m_State = E_ACCOUNT_READY;
						if (st.roleList.count > 0)
						{
							m_State = E_ROLE_READY;							
							printf("username  %s account %s\n", m_RoleInfo.rolename, m_AccountInfo.macAddress);
							g_pUCRRoleMgr->addLog2DB(m_RoleInfo.userid, m_RoleInfo.rolename, "log_in", m_AccountInfo.macAddress);
							init(m_RoleInfo);
						}
						else
						{
							m_State = E_CREATING_ROLE;
						}
						//LOG(E_LOG_EVENT_LOGIN_NUMBER, 0, "3.4login account success ", "", 34,0,0,0);
					}
					else
					{
						st.errcode = E_LOGIN_ACCOUNT_DATABASE_ERR;
					}
					printf("send login rsp \n");
					sendSLoginRsp(st);

					if (st.roleList.count > 0)
					{
						// fasong SRole
						SEnterRsp st = {0};
						st.errcode = E_LOGIN_ROLE_SUCCESS;
						st.roleCount = 1;
						buildRole(st.roles[0]);
						sendSEnterRsp(st);


						sendInitDataOnLoginSuccess();
					}

					/* code */
					m_DBTask_State = E_DBTASK_NO_TASK;
					// switch E_CREATING_ROLE or E_ROLE_READY
					popFirstProtocol();
					return ;

				}
				// remove recved protocol
			}
			else
			{
				return ;
			}
		}

		if (m_State == E_CREATING_ROLE)
		{
			unsigned int bodySize = 0;
			unsigned char* pStart = NULL;

			if (checkFirstProtocolRecved(C_2_S_Create_Req, bodySize, pStart))
			{

				bool errHappen = false;

				DO_PARSE_NOBREAK(SCreateReq);
				CMySQLConn* m_pMyConn = g_pUCRRoleMgr->getMysqlConn();

				if (m_DBTask_State == E_DBTASK_NO_TASK)
				{
					m_DBTask_State = E_DBTASK_JUMP_2_DB;	
					m_CUR_State = E_COROUTINE_STAY_DB;
					g_pUCRRoleMgr->sinkIntoDB(this);
					return;
				}
				// back from db pthread
				else if (m_DBTask_State == E_DBTASK_JUMP_2_DB)
				{


					printf("tryCreateRoleByRoleName  %s, accountid is %d", st.rolename, m_AccountInfo.accountid );
					if(false)  //g_pConfigureMgr->getThisServerConfig().canRegister == E_NO
					{	//服务器配置上是否可以注册
						sendGeneralError(BENFU_ZANTINGZHUCE);
					}
					else if (checkInvalid(st.rolename, strlen(st.rolename)))
					{
						//查询名字中的非法字符
						sendGeneralError(MINGZI_FEIFA_ZIFU);
						printf(" checkInvalid  \n");
					}
					else if (strlen(st.rolename) > 19)
					{
						sendGeneralError(MINGZI_FEIFA_ZIFU);
						printf("strlen(st.rolename) > 19\n");
					}
					else
					{
						//创建请求
						//m_tempProfessionId = st.professionId;
						memset(&m_sdbw_temp, 0, sizeof(SDB_Wrap));
						if (m_loginType == E_Login_Passport)
						{
							printf("通行证登录的角色,不可以绑定mac地址 \n");
						}
						else
						{
							Sql_Insert_role_create_role_by_accountid & sircrba = m_sdbw_temp._u.st_Sql_Insert_role_create_role_by_accountid;
							sircrba.accountid = m_AccountInfo.accountid;
							CUtility::safeStrCpy(sircrba.rolename, sizeof(sircrba.rolename), st.rolename);
							sircrba.professionId = 0;
							printf("pNew->operateId = DB_OPRATOR_INSERT_ROLE_CREATE_ROLE_BY_ACCOUNTID\n");

							try
							{

								MACRO_ESCAPE_FIELDS_CREATE_ROLE_BY_ACCOUNTID_ROLE(sircrba);
								char temp[1024] = "";
								snprintf(temp, sizeof(temp)-1, INSERT_SQL_CREATE_ROLE_BY_ACCOUNTID_ROLE, MACRO_STRUCT_FIELDS_CREATE_ROLE_BY_ACCOUNTID_ROLE(sircrba));
								printf("DB_OPRATOR_INSERT_ROLE_CREATE_ROLE_BY_ACCOUNTID  %s  \n" ,temp);
								//CMySQLRecordSet * poRs = NULL;
								m_sdbw_temp.insertId = 0;
								int ret = g_pUCRRoleMgr->getMysqlConn()->ExecuteSql(temp, &(m_sdbw_temp.insertId));
								if (ret < 0)
								{
									// LOG(ELog_Insert_Role_Failed, 0, temp, _t.rolename, _t.accountid, 0, 0, 0);
									//p->operateUserData = -1;
									m_sdbw_temp.dbErrcode = SDDB_INVALID_OP;

								}
								else
								{
									m_sdbw_temp.dbErrcode = SDDB_HAS_RECORDSET;
								}
							}
							catch(...)
							{
								// LOG(E_LOG_EVENT_DB_FAILED,0,"db except","",p->operateId,0,0,0);
								m_sdbw_temp.dbErrcode = SDDB_INVALID_OP;
							}


						}
					}


					/* code */
					m_DBTask_State = E_DBTASK_BACK_FROM_DB;
					m_CUR_State = E_COROUTINE_STAY_MAIN;

					g_pUCRRoleMgr->backFromDB();

					return;
				}
				// switch E_CREATING_ROLE or E_ROLE_READY
				else if (m_DBTask_State == E_DBTASK_BACK_FROM_DB)
				{


					printf("onCreateRoleByRoleName   return roleid %d \n", m_sdbw_temp.insertId);

					bool success = false;
					SEnterRsp st = {0};

					if (m_sdbw_temp.dbErrcode < 0 || m_sdbw_temp.dbErrcode == SDDB_INVALID_OP)
					{
						//返回错误，提示客户端要自己提交创建指令
						st.errcode = E_LOGIN_ROLE_NORECORD;
						sendGeneralError(MINGZI_CHONGFU);
						m_State = E_CREATING_ROLE;
						printf("返回错误，提示客户端要自己提交创建指令\n");
					}
					else
					{
						Sql_SelectAll_role _temp_role_all = {0};
						_temp_role_all.userid = (unsigned int )(m_sdbw_temp.insertId);
						//_temp_role_all.level = 1;//默认等级
						_temp_role_all.currentGuid = 2; //默认的guid从2开始
						//_temp_role_all.currentArrayId = 111101;//默认的阵型
						if (m_loginType == E_Login_Passport)
						{
						}
						else 
						{
							Sql_Insert_role_create_role_by_accountid & _t = m_sdbw_temp._u.st_Sql_Insert_role_create_role_by_accountid;
							CUtility::safeStrCpy(_temp_role_all.rolename, sizeof(_temp_role_all.rolename), _t.rolename);
							_temp_role_all.professionId = _t.professionId;
							_temp_role_all.accountid = _t.accountid;
						}

						if (init(_temp_role_all) /*&& initOnCreate()*/)
						{
							st.errcode = E_LOGIN_ROLE_SUCCESS;
							st.roleCount = 1;
							buildRole(st.roles[0]);
							success = true;
							printf("chuangjian chenggong \n");

							g_pUCRRoleMgr->addLog2DB(m_RoleInfo.userid, m_RoleInfo.rolename, "create_role", m_AccountInfo.macAddress);
						}
						else
						{
							st.errcode = E_LOGIN_ROLE_DATA_WRONG;
						}
					}
					sendSEnterRsp(st);
					if (success)
					{
						sendInitDataOnLoginSuccess();
						m_State = E_ROLE_READY;
					}
					/* code */
					m_DBTask_State = E_DBTASK_NO_TASK;
					popFirstProtocol();
				}
			}
			else
			{
				return ;
			}
		}
	}
}


EASYTHREAD_DECLARE(CUCRRoleMgr::WorkThreadFunc)( void* arg )
{
	CUCRRoleMgr* pThis = (CUCRRoleMgr* )arg;
	if (pThis == NULL)
	{
		return NULL;
	}
	pThis->executeDBSEH();
	return NULL;
}


