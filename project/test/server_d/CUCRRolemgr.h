#ifndef _PNL_COROUTINE_ROLE_MGR_H_
#define _PNL_COROUTINE_ROLE_MGR_H_
#include "pnl_protocol.h"
#include "pnl_protocol_decode.h"
#include "pnl_protocol_encode.h"
#include "SqlOperationHlp_PNL.h"
#include "EasyLoopArray.h"

#define RECV_BUF_LENGTH 10240

#define MAX_INT 0x7fffffff

class CUCRRole
{
public:
	CUCRRole(int s):m_Socket(s)
	{
		m_State = E_NOT_INIT;
		m_ProtoclType = E_PROTOCOL_TYPE_BINARY;
		m_lastSaveTime = CUtility::getCurrentTimeInt();
		m_loginType = 0;
		m_DBTask_State = E_DBTASK_NO_TASK;
		m_CUR_State = E_COROUTINE_STAY_MAIN;

	};
	~CUCRRole()
	{};


	void reset(); //初始化
	void close();

	bool checkClosing()
	{
		return m_State == E_CLOSING;
	}

public:
	void onAddRecv(const unsigned char*pBuf, unsigned int size)
	{
		if (pBuf!= NULL && size + m_recvBufSize <= RECV_BUF_LENGTH)
		{
			// printf("on add recv size is  %d the first 4 head is %d %d %d %d \n", size, pBuf[0], pBuf[1], pBuf[2], pBuf[3]);
			memcpy(m_recvBuf + m_recvBufSize, pBuf, size);
			m_recvBufSize += size;
			m_recvBuf[m_recvBufSize] = 0;
		}
		else
		{
			printf("bufsize is  %d, recved size is %d  \n", m_recvBufSize, size);
		}
	};
	void doSend(const unsigned char*pBuf, unsigned int size);
	bool onTimer();

	bool onRun(bool& isBusy);
	
	bool onProtocolReport(SProtocolTypeRpt sptr);

	bool onEasyLogin(SEasyLoginReq selr);


	bool checkWrongProtocol();
	void save2Db();
	void buildRole(SRole & role);
	void checkAndSaveAuto();
	bool init(Sql_SelectAll_role& roleInfo);
	bool initOnCreate();//创建角色的时候,执行一些初始化,一般的数据可以放在数据库中的default值,blob字段不太好办,因此放在这里, 在init完成之后调用
	unsigned int getUserId();//获得数据库索引id
	unsigned int getRoleGuid(){return m_Socket;};//m_guid 暂时使用socket替代数据库id,控制范围
	void sendInitDataOnLoginSuccess();//当登陆成功以后,发送其他的初始包


	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//检查字符串函数
	bool checkInvalid(const char* , unsigned int len);
	bool checkIOS7Mac(const char* );

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//数据库辅助函数,一般异步的过程需要一个发起接口,一个响应接口
	bool tryGetRoleInfoByUserid(unsigned int userid);
	// void onGetRoleInfoByUserid(SDB_Wrap*p);
	// bool tryGetTarget(unsigned int targetUserid, EGetTargetType type, int userData);
	bool deleteAccountId();
	// bool tryEnterGameByAccountIdAndUserid(unsigned int userid);
	// bool onEnterGameByAccountIdAndUserid(SDB_Wrap*p);
	// bool tryGetAccountidByMac(SEasyLoginReq &req);
	// bool onGetAccountidByMac(SDB_Wrap*p);
	// bool tryCreateRoleByRoleName(SCreateReq& st, unsigned int starLevel);
	// bool onCreateRoleByRoleName(SDB_Wrap*p);
	// void onDbEvent(SDB_Wrap*);//数据库回调


	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//发送协议方便函数,命名方式为 send+结构名字
	void buildBasicDataNtf(map<int, int >&mapInfo, SBasicDataNtf&ntf);
	void buildBasicDataStringNtf(map<int, std::string >&mapInfo, SBasicDataStringNtf&ntf);
	void sendSingleBasicDataNtf(unsigned int t, unsigned int v);
	void sendGeneralError_p(const char* pError, unsigned int d1, unsigned int errcode);
	void sendGeneralError_p(const char* pError, unsigned int d1, unsigned int d2, unsigned int errcode);
	void sendGeneralError_p(const char* pError, const char* ps1, unsigned int errcode);
	void sendGeneralError_p(const char* pError, const char* ps1, unsigned int d1, unsigned int errcode);
	void sendGeneralError_p(const char* pError, const char* ps1, unsigned int d1, unsigned int d2, unsigned int errcode);
	void sendGeneralError(const char* pError, unsigned int errcode=0);
	void sendSGeneralWords(const char* pWords);
	void sendSGeneralWords(const char* pWords, unsigned int );
	void sendSProtocolTypeRsp(SProtocolTypeRsp& ); //	C_2_S_Protocol_Type_Rsp, //SProtocolTypeRsp，当可以用的时候,服务器返回下0. 
	void sendSBasicDataExNtf(SBasicDataExNtf& sbden); //S_2_C_Basic_DataEx_Ntf, //
	void sendSGeneralWordsNtf(SGeneralWordsNtf& sgwn); //S_2_C_General_Words_Ntf
	void sendSLoginRsp(SEasyLoginRsp& slr);
	void sendSEnterRsp(SEnterRsp& ser);
	void sendSCreateRsp(SCreateRsp& scr);
	void sendProtocolVersionNtf();//	S_2_C_Protocol_Version_Ntf, //SProtocolVersionNtf
	void sendSGlobalNtf(unsigned int type, const char* pMsg);//	S_2_C_Global_Ntf, //SGlobalNtf
	void sendSGlobalNtf(unsigned int type, const char* pMsg, const char* s1);//	S_2_C_Global_Ntf, //SGlobalNtf
	void sendSGlobalNtf(unsigned int type, const char* pMsg, unsigned int p1);//	S_2_C_Global_Ntf, //SGlobalNtf
	void sendSGlobalNtf(unsigned int type, const char* pMsg, unsigned int p1, unsigned int p2);//	S_2_C_Global_Ntf, //SGlobalNtf
	void sendSGlobalNtf(unsigned int type, const char* pMsg, const char* s1, unsigned int p1);//	S_2_C_Global_Ntf, //SGlobalNtf
	void sendSGlobalNtf(unsigned int type, const char* pMsg, unsigned int p1, const char* s1);//	S_2_C_Global_Ntf, //SGlobalNtf
	void sendSGlobalNtf(SGlobalNtf& sgn);//	S_2_C_Global_Ntf, //SGlobalNtf
	void sendSProbeNtf(SProbeNtf& );//		S_2_C_PROBE_NTF, //SProbeNtf生存判断通知
	void sendSServerStatusReporter(SServerStatusReporter& ); //,S_2_C_Server_Status_Ntf, //SServerStatusReporter
	void sendSServerLoadFinishNtf(SServerLoadFinishNtf &);  //S_2_C_Server_Load_Finished_Ntf, //SServerLoadFinishNtf
	//stage信息
	void sendSGetAllStageRsp(SGetAllStageDescRsp &ntf);
	void sendSGetStageRsp(SGetStageRsp &ntf);//	S_2_C_SGetStage_Rsp, //。

	void sendSBasicDataChangeNtf(SBasicDataChangeNtf& sbdcn);//S_2_C_Basic_Data_Change_Ntf, //
	void sendSBasicDataStringChangeNtf(SBasicDataStringChangeNtf& sbdscn);//	S_2_C_Basic_String_Data_Change_Ntf, 


	//剧本更新
	void buildAllStageRsp(SGetAllStageDescRsp& rsp);

	/////////////////////////////////////////////////////////////////////////////////////
	//coroutine mode
	void onRunCoroutine(bool& isBusy);
	bool checkFirstProtocolRecved(unsigned int needProtocolId, unsigned int & bodySize, unsigned char*& pStart);
	void popFirstProtocol();
	enum ECoroutineState
	{
		E_COROUTINE_STAY_MAIN ,
		E_COROUTINE_STAY_DB,
	};
	ECoroutineState m_CUR_State;

	enum EDBTaskState
	{
		E_DBTASK_NO_TASK,
		E_DBTASK_JUMP_2_DB,
		E_DBTASK_BACK_FROM_DB,
	};
	EDBTaskState m_DBTask_State;


private:
	int m_Socket;
	unsigned char m_recvBuf[RECV_BUF_LENGTH];
	unsigned int m_recvBufSize;
	unsigned int m_nCurrentProtocolId;
	unsigned int m_guid;
	enum EState
	{//
		E_NOT_INIT,					//
		E_REGISTING_ACCOUNT,			//ÕýÔÚ×¢²áÕÊºÅ
		E_ACCOUNT_READY,            //Í¨¹ýÕÊºÅµÇÂ½,¿ÉÒÔ½øÐÐ½ÇÉ«¼¶±ðµÄ²Ù×÷
		E_CREATING_ROLE,			//ÕýÔÚ´´½¨Êý¾Ý¿âÊý¾Ý,²»¿ÉÒÔÈÎºÎ²Ù×÷,µÈ´ý·þÎñÆ÷·µ»Ø
		E_VERIFYING_FROM_PASSPORT,  //ÕýÔÚÕÒpassportÇëÇóÑéÖ¤sessionid
		E_ROLE_READY,				//¿ÉÒÔÖ´ÐÐÓÎÏ·Âß¼­£¬²»¿ÉÒÔÖ´ÐÐ´´½¨»òÕßµÇÂ½Ð­Òé
		E_DATABASE_ERROR,			//Ö´ÐÐÊý¾Ý¿â²Ù×÷Ê§°Ü£¬²»ÔÙÖ´ÐÐÈÎºÎÐ­Òé£¬×¼±¸¹Ø±Õ
		E_CLOSING,					//ÔÚ¹Ø±Õ¹ý³ÌÖÐ,²»¿ÉÒÔÖ´ÐÐÈÎºÎÐ­Òé 
		E_SEND_BUF_NOT_ENOUGH,      //·¢ËÍ»º³åÇøÒç³ö,ÐèÒª¹Ø±ÕÁ¬½Ó
		E_LOBBY_FULL,				//´óÌüÂúÁË,ÐèÒª¹Ø±ÕÁ¬½Ó

	};
	Sql_SelectAll_account m_AccountInfo;  //角色信息
	EState m_State;
	enum EProtocolType
	{
		E_PROTOCOL_TYPE_BINARY,  //¶þ½øÖÆ¸ñÊ½Ð­Òé
		E_PROTOCOL_TYPE_JSON,  //json¸ñÊ½Ð­Òé,ÓÃÀ´»úÆ÷ÈË²âÊÔ 
	};

	unsigned int m_ProtoclType;
	
	unsigned int m_lastSaveTime;
	Sql_SelectAll_role m_RoleInfo;  //角色信息
	SMiscDB* m_pMiscDB;

	unsigned int temp_my_userid; //当使用通行证登陆时候，记录目标角色账号的名字。
	int m_loginType; //登陆状态,mac,帐号,两种情况


	SDB_Wrap m_sdbw_temp;

};

class CUCRRoleMgr : public ITask
{
public:
	CUCRRoleMgr(unsigned int id):ITask(id)
	{

	}

	/**
	Description:	Destructor
	*/
	virtual ~CUCRRoleMgr()
	{
	};

	virtual bool init() 
	{
		m_pMyConn = new CMySQLConn();

		if (m_pMyConn == NULL)
		{
			return false;
		}
		if (!m_pMyConn->Connect(g_pConfigureMgr->getThisServerConfig().db_ip
								, g_pConfigureMgr->getThisServerConfig().db_port
								, g_pConfigureMgr->getThisServerConfig().db
								, g_pConfigureMgr->getThisServerConfig().db_u
								, g_pConfigureMgr->getThisServerConfig().db_p
								, "utf8"))
		{
			printf("connect db failed , ip:%s, port:%d, db:%s, user:%s, pwd:%s", g_pConfigureMgr->getThisServerConfig().db_ip
				, g_pConfigureMgr->getThisServerConfig().db_port
				, g_pConfigureMgr->getThisServerConfig().db
				, g_pConfigureMgr->getThisServerConfig().db_u
				, g_pConfigureMgr->getThisServerConfig().db_p);
			return false;
		}
		m_pThread = new CEasyThread();
		if (m_pThread == NULL)
		{
			return false;
		}
		if (!m_pThread->start(WorkThreadFunc, this))
		{
			return false;
		}
		LOG(E_LOG_EVENT_SERVER_OPEN, 0, "databases ok", "", 0, 0, 0, 0);

		m_tCheckAlive  = CUtility::getCurrentTimeInt();

		m_bIsConnectionOK = true;

		m_bThreadTerminated = false;
		// m_dbArray.init();

		return true;
	}

	virtual bool run() 
	{
		// printf("cpnrole mgr total role count%d \n", m_mpRoles.size());
		bool isBusy = false;

		std::map<int, int> removeMap ;

		MAPROLES::iterator iter = m_mpRoles.begin();
		while(iter != m_mpRoles.end())
		{
			if (iter->second->m_CUR_State == CUCRRole::E_COROUTINE_STAY_MAIN)
			{
			// 	printf("run  main \n");
				if (iter->second->checkClosing())
				{
					/* code */
					// shuru dao map 
					removeMap[iter->first] = iter->first;
				}
				else
				{
					iter->second->onRunCoroutine(isBusy);
				}
				
			}
			iter ++;
		}

		//delay 
		for (std::map<int, int>::iterator i = removeMap.begin(); i != removeMap.end(); ++i)
		{
			onDelayRemoveRole(i->first);
		}


		return true;
	}
	virtual void uninit() 
	{
		return ;
	}
	void onAddRecv(unsigned int socket, const unsigned char*pBuf, unsigned int size)
	{
		// printf("role mgr on add recv %d, size %d \n",socket, size);
		MAPROLES::iterator iter = m_mpRoles.find(socket);
		if (iter != m_mpRoles.end())
		{
			(iter->second)->onAddRecv(pBuf, size);
		}
	}
	void onAddRole(unsigned int socket)
	{
		m_mpRoles[socket] = new CUCRRole(socket);
		m_mpRoles[socket]->reset();
		// m_mpRoles[socket]->sendProtocolVersionNtf();
	}
	void onRemoveRole(unsigned int socket)
	{
		MAPROLES::iterator iter = m_mpRoles.find(socket);
		if (iter != m_mpRoles.end())
		{
			printf("on remove the  role  socket %d\n", socket);
			iter->second->close();
			// delete iter->second;
			// m_mpRoles.erase(iter);
		}
	}

	void onDelayRemoveRole(unsigned int socket)
	{
		MAPROLES::iterator iter = m_mpRoles.find(socket);
		if (iter != m_mpRoles.end())
		{
			if (iter->second->m_DBTask_State == CUCRRole::E_DBTASK_NO_TASK)
			{
				iter->second->m_DBTask_State = CUCRRole::E_DBTASK_JUMP_2_DB;
				iter->second->m_CUR_State = CUCRRole::E_COROUTINE_STAY_DB;
				sinkIntoDB(iter->second);
			}
			else if (iter->second->m_DBTask_State == CUCRRole::E_DBTASK_BACK_FROM_DB)
			{
				delete iter->second;
				m_mpRoles.erase(iter);
				printf("on delay remove the  role  socket %d\n", socket);
			} 
		}
	}

	void doSend(unsigned int socket, const unsigned char* pBuf, unsigned int size)
	{
		g_pListenerLbv->doSend(socket, pBuf, size);
	}

	CUCRRole* getRole(int socket)
	{
		MAPROLES::iterator iter = m_mpRoles.find(socket);
		if (iter != m_mpRoles.end())
		{
			return iter->second;
		}
		return NULL;
	}

	CMySQLConn* getMysqlConn()
	{
		return m_pMyConn;
	}

	void addLog2DB(int userId, char* userName, char* type, char* log)
	{
		Sql_Insert_log_insert_log * pSILIL = new Sql_Insert_log_insert_log;
		if (pSILIL != NULL)
		{
			memset(pSILIL, 0, sizeof(Sql_Insert_log_insert_log));
			pSILIL->userId = userId;
			CUtility::safeStrCpyNoRet(pSILIL->type, sizeof(pSILIL->type), type);
			CUtility::safeStrCpyNoRet(pSILIL->log, sizeof(pSILIL->log), log);
			CUtility::safeStrCpyNoRet(pSILIL->userName, sizeof(pSILIL->userName), userName);	
			m_dbArrayLog.addTail(pSILIL);
		}
	}

	void doInsertLog(Sql_Insert_log_insert_log* pSILIL)
	{
		if (pSILIL == NULL)
		{
			return;
		}
		Sql_Insert_log_insert_log& st = *pSILIL;

		try
		{

			MACRO_ESCAPE_FIELDS_INSERT_LOG_LOG(st);
			char temp[1024] = "";
			snprintf(temp, sizeof(temp)-1, INSERT_SQL_INSERT_LOG_LOG, MACRO_STRUCT_FIELDS_INSERT_LOG_LOG(st));
			printf("INSERT_SQL_INSERT_LOG_LOG  %s  \n" ,temp);
			//CMySQLRecordSet * poRs = NULL;
			unsigned long long insertId = 0;
			int ret = getMysqlConn()->ExecuteSql(temp, &(insertId));
			if (ret < 0)
			{
				printf("insert log failed !!!");
			}
			else
			{
			}
		}
		catch(...)
		{
			// LOG(E_LOG_EVENT_DB_FAILED,0,"db except","",p->operateId,0,0,0);
			printf("insert log catche exception !!!!!!!!!!!!!!!!\n");
		}

	}

	void executeDBSEH()
	{
		while(!m_bThreadTerminated)
		{
			//cout<<"DB THREAD"<<endl;
			if (m_bIsConnectionOK == false)
			{
				//¼ì²éÒì³£ÖÐ¶Ï
				break;
			}
			bool isBusy = false;
			// MAPROLES::iterator iter = m_mpRoles.begin();
			// while(iter != m_mpRoles.end())
			// {
			// 	if (iter->second->m_CUR_State == CUCRRole::E_COROUTINE_STAY_DB)
			// 	{
			// 		printf("run  db \n");
			// 		iter->second->onRunCoroutine(isBusy);
			// 	}
			// 	iter ++;
			// }
			CUCRRole* pRole = (CUCRRole* )m_dbArray.getHead();
			while(pRole != NULL)
			{
				if (pRole->m_CUR_State == CUCRRole::E_COROUTINE_STAY_DB)
				{
					printf("run  db \n");
					if (pRole->checkClosing())
					{
						/* code */
						if (pRole->m_DBTask_State == CUCRRole::E_DBTASK_JUMP_2_DB)
						{
							pRole->save2Db();
							backFromDB();
							pRole->m_DBTask_State = CUCRRole::E_DBTASK_BACK_FROM_DB;
							pRole->m_CUR_State = CUCRRole::E_COROUTINE_STAY_MAIN;
						}
					}
					else
					{
						pRole->onRunCoroutine(isBusy);
					}
				}
				pRole = (CUCRRole* )m_dbArray.getHead();
			}


			// handle log 
			Sql_Insert_log_insert_log *pSILIL = (Sql_Insert_log_insert_log*)m_dbArrayLog.getHead();
			while(pSILIL != NULL)
			{
				doInsertLog(pSILIL);
				delete pSILIL;
				m_dbArrayLog.popHead();
				pSILIL = (Sql_Insert_log_insert_log*)m_dbArrayLog.getHead();
			}

		}
	}

	bool sinkIntoDB( CUCRRole* p)
	{
		if (p != NULL) 
		{
			return m_dbArray.addTail(p);
		} 
		return false;
	}
	bool backFromDB()
	{
		m_dbArray.popHead();
		return true;
	}



private:
	typedef std::map<int, CUCRRole*> MAPROLES;
	MAPROLES m_mpRoles;

	CMySQLConn* m_pMyConn;

	bool m_bIsConnectionOK;
	unsigned int m_tCheckAlive;

	CEasyThread* m_pThread;
	static EASYTHREAD_DECLARE( WorkThreadFunc)(VOID *pArg);
	bool m_bThreadTerminated ;

	CEasyLoopArray m_dbArray;
	CEasyLoopArray m_dbArrayLog;


};
extern CUCRRoleMgr* g_pUCRRoleMgr;

#endif