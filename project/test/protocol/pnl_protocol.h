
#ifndef __PNL_PROTOCOLS_H__
#define	__PNL_PROTOCOLS_H__
/*
登陆指南--废除-2013-01-09
暂时只有mac登陆和mac创建
1,
	使用mac登陆  -----》 获得返回值S_2_C_Login_Rsp
	使用mac登陆  -----》 报告没有创建
2，
	使用mac创建  -----》 创建成功，获得 S_2_C_Login_Rsp
	使用mac创建  -----》 创建失败，mac已经被创建过了

现在登陆拆分成 
登陆帐号, 进入游戏
1,**************登陆过程
使用mac登陆C_2_S_Login_Req  -----》 有记录,而且没有绑定,返回成功S_2_C_Login_Rsp
使用mac登陆C_2_S_Login_Req  -----》 没有创建,自动创建mac地址帐号,返回成功S_2_C_Login_Rsp

2,**************进入游戏过程
请求进入C_2_S_Enter_Req  -----》 成功S_2_C_Enter_Rsp
请求进入C_2_S_Enter_Req  -----》 没有帐号,提示创建S_2_C_Enter_Rsp

创建角色C_2_S_Create_Req  -----》 成功,进入游戏S_2_C_Enter_Rsp
创建角色C_2_S_Create_Req  -----》 失败,重复名字C_2_S_Create_Rsp


日志：E_PROTOCOL_NOW=0x1b, //当前版本2013-08-10,更改了佣兵的数据结构
日志：E_PROTOCOL_NOW=0x1c, //当前版本2013-08-19,更改了排行榜结构
日志：E_PROTOCOL_NOW=0x1d, //当前版本2013-09-17,更改了mac地址可以登陆多个帐号,整理了老的协议
日志：E_PROTOCOL_NOW=0x1e, //当前版本2013-10-16,正式1.5版本
日志：E_PROTOCOL_NOW=0x1f, //当前版本2016-07-28,正式lmp版本

*/


/*
协议id-------------------------------------------------------------------------------------------------------------------
*/
enum EProtocolVersion
{
	E_PROTOCOL_NOW=0x1f, //当前版本2016-07-28,正式lmp版本
};

enum EProtocolId
{
	Protocol_Start,

	//版本号校验,这两个协议都必须是二进制格式coding。
	S_2_C_Protocol_Version_Ntf, //SProtocolVersionNtf
	C_2_S_Protocol_Type_Rpt, //SProtocolTypeRpt，当要使用json协议格式的时候，可以发这个正常流程可以不发 
	C_2_S_Protocol_Type_Rsp, //SProtocolTypeRsp，当可以用的时候,服务器返回下0. 

	//general-errcode-notify
	S_2_C_General_Error_Ntf, //SGeneralErrorNtf
	S_2_C_General_Words_Ntf, //SGeneralWordsNtf

	//basic-account-related-operation
	C_2_S_Create_Req, //SCreateReq
	S_2_C_Create_Rsp, //SCreateRsp
	C_2_S_Easy_Login_Req, //SEasyLoginReq
	S_2_C_Easy_Login_Rsp, //SEasyLoginRsp
	C_2_S_Enter_Req, //SEnterReq
	S_2_C_Enter_Rsp, //SEnterRsp
	S_2_C_Kick_Ntf,	//SKickNtf
	C_2_S_Logoff_Req, //SLogoffReq
	S_2_C_Logoff_Rsp, //SLogoffRsp
	C_2_S_LoadFinished_Req, //SLoadFinishedReq
	//创建角色附加vip信息
	C_2_S_Create_Ex_Req, //SCreateExReq。

	//gmcmd
	C_2_S_GmCmd_Req, //SGmcmdReq
	S_2_C_GmCmd_Rsp, //SGmcmdRsp

	//basic-data-notify
	S_2_C_Basic_DataEx_Ntf, //SBasicDataExNtf

	//global-notify
	S_2_C_Global_Ntf, //SGlobalNtf
	S_2_C_Basic_Data_Broadcast_Ntf, //SBasicDataBroadcastNtf


	//心跳包
	S_2_C_PROBE_NTF, //SProbeNtf生存判断通知
	C_2_S_PROBE_ANSWER, //SProbeAnswer客户端返回

	//游戏管理员交互
	C_2_S_Leave_Msg_2_GM_Req, //SLeaveMsg2GMReq
	S_2_C_GM_Answer_Rsp, //SGMAnswerRsp

	
	//服务器状态报告，只后台用
	S_2_C_Server_Status_Ntf, //SServerStatusReporter，只给gm用，
	S_2_S_Server_Status_Reporter, //SServerStatusReporter


	//服务器发送场景信息完毕包
	S_2_C_Server_Load_Finished_Ntf, //SServerLoadFinishNtf。



	//剧场更新信息
	C_2_S_SGetAllStage_Req, //SGetAllStageDescReq。
	S_2_C_SGetAllStage_Rsp, //SGetAllStageDescRsp。

	//下载单个剧场
	C_2_S_SGetStage_Req, //SGetStageReq。
	S_2_C_SGetStage_Rsp, //SGetStageRsp。

	//剧场压缩
	TOOL_SPackedFiles, //SPackedFiles。并不是给网络协议使用

	//包裹内容相关
	S_2_C_TeasureUpdate_Ntf, //STreasureUpdateNtf。

	//包裹内容相关
	C_2_S_Basic_Data_Change_Req, //SBasicDataChangeReq
	S_2_C_Basic_Data_Change_Ntf, //SBasicDataChangeNtf

	C_2_S_Basic_String_Data_Change_Req, //SBasicDataStringChangeReq
	S_2_C_Basic_String_Data_Change_Ntf, //SBasicDataStringChangeNtf
	
	C_2_S_GET_ROLE_INFO_REQ, //SGetRoleInfoReq
	S_2_C_GET_ROLE_INFO_RSP, //SGetRoleInfoRsp



};

/*
登陆-------------------------------------------------------------------------------------------------------------------
*/

enum ESceneType
{
	E_SCENETYPE_OTHER =0,  //其他场景
	E_SCENETYPE_IDOL =10000,  //偶像场景
};
struct SLoadFinishedReq
{
	unsigned int intoScene;//具体查看ESceneType。
};

enum EAccountLoginErrcode   
{
	E_LOGIN_ACCOUNT_SUCCESS, //帐号登陆成功
	E_LOGIN_ACCOUNT_CANT_MAC_ONLY, //帐号已经绑定,客户端不可以用E_Login_MAC_ONLY的方式登陆
	E_LOGIN_ACCOUNT_REGISTED,// 绑定操作失败,账户已经被使用
	E_LOGIN_ACCOUNT_FAILED,//登陆失败,密码或者帐号错误,或不匹配
	E_LOGIN_ACCOUNT_TYPE_ERR,//请求类型错误
	E_LOGIN_ACCOUNT_DATABASE_ERR,//数据库操作错误
};

enum ERoleLoginErrcode   
{
	E_LOGIN_ROLE_SUCCESS, //角色登陆成功
	E_LOGIN_ROLE_NORECORD,//客户端需要发送创建协议，带上职业和角色名字
	E_LOGIN_ROLE_DATA_WRONG, //角色数据错误

};

struct SCreateReq 
{
	char rolename[64];
	int professionId;
};

struct SCreateExReq
{
	char rolename[64];
	int professionId;
	int vip; //如果是2,表示是vip
};


enum ECreateErrcode
{
	E_CREATE_SUCCESS, //
	E_CREATE_NAME_ALREADY_USED, //角色用户名已经被占用
};

struct SLogoffReq
{
};

struct SLogoffRsp
{
};

struct SRegisterReq
{
	char account[32];
	char pwd[32];
	char mac[32];
};

enum ERegisterErrcode
{
	E_REGISTER_SUCCESS, //
	E_REGISTER_MAC_ALREADY_REGISTED, //
	E_REGISTER_ACCOUNT_ALREADY_USED, //
};
struct SRegisterRsp
{
	unsigned char errcode/*ERegisterErrcode*/;
};

struct SKickNtf
{
};

enum ELoginType
{
	E_Login_MAC, //使用mac登录,如果有别的登陆方式,需要增加新的类型
	E_Login_Passport, //通行证登陆方式,不属于简易登录方式
};
struct SEasyLoginReq
{
	int type/*ELoginType*/;
	char easyAccount[128]; //简易账号,根据type的不同,有可能是mac地址,也有可能是别的号码,一般采用字符串
};

enum EShowLevel
{
	E_Show_Level_1, //对应最原始的状态
	E_Show_Level_2, //
	E_Show_Level_3, //
	E_Show_Level_4, //
	E_Show_Level_5, //
	E_Show_Level_6, //
	E_Show_Level_7, //
	E_Show_Level_8, //
};

struct SBasicRoleInfo
{
	unsigned int userid;
	int guid;
	unsigned int showLevel;  //参见EShowLevel。
	unsigned int mateid;
	char macAddress[20];
	char rolename[64];
	int level;
	int professionId;
	int exp;
	int popularity;
	int expTotal;
	int diamond;
	int money;
	int exploit; //功勋
	int vigor; //体力
	int vigorMax; //体力上限
	int leaderForce; //领导力
	int killingValue;//杀戮值
	int halliconId; //主城头像
};

//角色属性信息结构
struct SRoleParameters
{
	int quizCount;//考试次数
	int quizScore;//考试分数
	int moral;    //道德
	int tidy;     //整洁
};

struct SRole
{
	SBasicRoleInfo roleBasic;
	SRoleParameters paraNow; //当前的参数,显示给自己看
};

struct SEasyRoleInfo4Login
{
	char rolename[32];
	int userid;
};

struct SEasyRoleInfo4LoginList
{
	unsigned char count;
	SEasyRoleInfo4Login easyRoleList[5/*count*/]; //简易帐号对应的userid列表,如果是0,则客户端进入创建界面
};

struct SEasyLoginRsp
{
	int type/*ELoginType*/;
	unsigned int errcode/*EAccountLoginErrcode*/;
	SEasyRoleInfo4LoginList roleList;
};

struct SEnterReq
{
	unsigned int userid; //选定一个,不可以为0,应该提前创建.
};

struct SEnterRsp
{
	unsigned int  errcode/*ERoleLoginErrcode*/;
	unsigned int  roleCount;
	SRole		  roles[1/*roleCount*/];
};

struct SBindAccountReq
{
	char account[32];
	char pwd[32];
};
enum EBindErrcode
{
	E_Bind_Success, //
	E_Bind_Account_Used, //
};

struct SBindAccountRsp
{
	unsigned int errcode/*EBindErrcode*/;
};

struct SCreateRsp
{
	unsigned int  errcode/*ECreateErrcode*/;
	char		  name[32];
	unsigned int  userid;
};

struct SBasicData
{
	unsigned int t;  //参考EBasicDataType索引值
	unsigned int v;  //值
};

struct SBasicDataString
{
	unsigned int t;  //参考EBasicDataType索引值
	char    sv[32];  //值
};

struct SBasicDataStringNtf
{
	unsigned int count;
	SBasicDataString t[32/*count*/];
};

struct SBasicDataNtf
{
	unsigned int count;
	SBasicData t[32/*count*/];
};

struct SBasicDataEx
{
	unsigned int guid;//如果是1表示主角,否则是伙伴的guid.
	SBasicDataNtf ns;
};

struct SBasicDataExNtf
{
	unsigned int count;//伙伴加主角一共21个最多
	SBasicDataEx updates[21/*count*/];
};

enum EBasicDataType
{
	E_BDT_KILL_COUNT = 0,     
};

struct SBasicDataChangeReq
{
	SBasicDataNtf sbdn;
};

struct SBasicDataChangeNtf
{
	SBasicDataNtf sbdn;
};

struct SBasicDataStringChangeReq
{
	SBasicDataStringNtf sbdn;
};

struct SBasicDataStringChangeNtf
{
	SBasicDataStringNtf sbdn;
};


/*
全服务器文字广播----------------------------------------------------------------------------------------------------
*/
enum EGlobalNtfType
{
	E_GN_Tips,			//tips公告
	E_GN_Shopping,		//商店界面的公告
	E_GN_Chat,			//聊天广播
	E_GN_System,		//系统消息
	E_GN_PublicTavern,  // 公共酒馆
	E_GN_Team,          // 队伍频道
	E_GN_GlobalBroadCast, //全服务器滚动条通知 
};
struct SGlobalNtf
{ 
	unsigned short t; //显示公告的位置
	char msg[512];      //公告的内容
	char role[64];		//发起人的名字,在聊天的时候用
};

enum EBasicDataBroadcastType
{
	E_BDBT_SHOWLEVEL,   //
	E_BDBT_SHOWID, // 
	E_BDBT_SHOW_WING_STRONGLEVEL, //
	E_BDBT_SHOW_NOBILITYLEVEL, //爵位等级
	E_BDBT_SHOW_KILLINGVALUE,//杀戮值
	E_BDBT_CHANGE_COACH,//更换教练
};

struct SBasicDataBroadcastNtf
{
	unsigned int guid; //如果是自己,就不用折腾了,自己的guid从登陆包里获得,别人的guid从STargetIntoSightNtf获得.
	unsigned int t; //见EBasicDataBroadcastType.
	unsigned int v;
	unsigned int jerseyId;
};

/*
客户端连接第一个报文---强制使用 二进制格式
*/
struct SProtocolVersionNtf
{
	unsigned int v;
};

enum EProtocolType
{
	E_PROTOCOL_TYPE_BINARY,  //二进制格式协议
	E_PROTOCOL_TYPE_JSON,  //json格式协议,用来机器人测试 
};
struct SProtocolTypeRpt
{
	unsigned char type;  //参考EProtocolType。
	unsigned char version; //参考EProtocolVersion，重大升级版本里程碑编号。
};

struct SProtocolTypeRsp
{
	unsigned char errcode;  //0表示许可。
};

/*
管理员命令-------------------------------------------------------------------------------------------------------------------
*/
struct SGmcmdReq
{
	char cmd[64]; //注意必须是ascii码
};
struct SGmcmdRsp
{
	unsigned int nouse; //收到表示成功,如果有出错,使用通用协议发送
};

/*心跳包*/
struct SProbeNtf
{
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
};

struct SProbeAnswer
{
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
};

struct SLeaveMsg2GMReq
{//游戏管理员
	char msg[256];
};
struct SGMAnswerRsp
{
	char answer[256];
};

struct SServerLoadFinishNtf
{
	int temp;
};

/********************************************************************************
剧目信息
*/
struct  SStageInfo
{
	unsigned int stageId;		//排序id。
	unsigned char md5[32];		//检查完整性md5。
	char name[64];				//压缩包文件,其实可以不用了,使用stageid生成名字id。
	char desc[256];				//剧情描述
	unsigned int size;			//压缩包文件大小
};

enum SStageFileConfig
{
	E_STAGE_FILE_BLOCK_SIZE = 20480,  //每次40k，约定好
};

struct SStageFile
{
	unsigned int stageId;
	unsigned short blockId; //表示当前的块从0开始。
	unsigned short nextBlcokId; //0表示就没有下文了
	unsigned short length;
	unsigned char file[20480/*length*/]; //40k的速率下载，需要跟E_STAGE_FILE_BLOCK_SIZE同步。
};

struct  SGetAllStageDescReq
{

};

struct SGetAllStageDescRsp
{
	unsigned int count;
	SStageInfo  stages[50/*count*/];
};

struct SGetStageReq
{
	unsigned int stageId; //1表示，需要lobby脚本的stage。
	unsigned short blockId;
};

struct SGetStageRsp
{
	unsigned int totalSize;
	SStageFile file;
};

/************************************************************************************************
财物相关协议，后台操作数据，更新给前台 
*/
struct STreasure
{
	int guid; //角色给予，递增。
	int count; //可以用来表示数量，耐久，因为所有物品都有时间不同，因此不同的道具不能合并。数量不做操作
	int itemId;
	int createTime; //创建时间
};

struct STreasureInBag
{
	int index; //包裹里的数组下标
	STreasure t;
	int leftTimeSecond; //剩下的时间，单位为秒。
};

struct STreasureUpdateNtf
{
	int count;
	STreasureInBag treasures[100/*count*/];
};



/*
通用错误-------------------------------------------------------------------------------------------------------------------
*/
enum EGeneralErrcode
{
	E_GE_PLAY_FUBEN_FAILED, //副本中游戏失败，退出副本，回到大厅
};

struct SGeneralErrorNtf
{
	unsigned int errcode;
	char msg[512];
};

struct SGeneralWordsNtf
{
	char msg[512];
};

//服务器状态通知
struct SServerStatusReporter
{
	char servername[64]; //服务器名字
	unsigned int maxLoad; //一个百分比数字
	unsigned int currentLoad;
	unsigned int protocolVer;
};


/*
各种宏-------------------------------------------------------------------------------------------------------------------
*/
enum EAutoFightTimeFactor
{
	E_AUTOFIGHTTIME_FREE_FACTOR		= 60,//自动战斗免费时间，单位为分
	E_AUTOFIGHTTIME_EXPENSE_FACTOR	= 180,//自动战斗付费之后
	E_AUTOFIGHTTIME_BUYTIME_FACTOR  = 60,//花钱购买单位
};
enum EInvalidGuid
{
	E_INVALID_GUID=0xffffffff, //非法的guid值
};



enum EObjType
{
	E_OBJECT_TYPE_NONE,							//
	E_OBJECT_TYPE_PROFESSION,					//职业
	E_OBJECT_TYPE_ARRAY,						//阵型
	E_OBJECT_TYPE_ITEM,							//道具
	E_OBJECT_TYPE_EQUIPEMENT,					//装备
	E_OBJECT_TYPE_NPC,							//npc.
	E_OBJECT_TYPE_TASK,  						//任务
	E_OBJECT_TYPE_MILITARYRANK,					//军衔
	E_OBJECT_TYPE_FUBEN,						//副本
	E_OBJECT_TYPE_FUBEN_ARRAY,					//副本阵型
	E_OBJECT_TYPE_SKILL,						//技能
	E_OBJECT_TYPE_BUFF,							//buff状态
	E_OBJECT_TYPE_PRIZE,						//奖励
	E_OBJECT_TYPE_NOTIFY,						//公告
	E_OBJECT_TYPE_SUIT,							//套装

	E_OBJECT_TYPE_ITEM_PORTION,					//道具.药水
	E_OBJECT_TYPE_ITEM_FORGE_FORMULA,           //道具.打造卷轴
	E_OBJECT_TYPE_ITEM_MATERIAL,				//道具.材料
	E_OBJECT_TYPE_ITEM_NEWER_GIFT,				//道具.新手礼包
	E_OBJECT_TYPE_ITEM_WUSOUL,					//道具.武魂	//E_OBJECT_TYPE_ITEM_GIFT,					//道具.礼包

 	E_OBJECT_TYPE_EQUIPEMENT_HELMET,			//装备.头盔
 	E_OBJECT_TYPE_EQUIPEMENT_WEAPON,			//装备.武器
 	E_OBJECT_TYPE_EQUIPEMENT_GLOVE,				//装备.手套
 	E_OBJECT_TYPE_EQUIPEMENT_NECKLACE,			//装备.项链
 	E_OBJECT_TYPE_EQUIPEMENT_CLOTH,				//装备.胸甲
 	E_OBJECT_TYPE_EQUIPEMENT_RING,				//装备.戒指
 	E_OBJECT_TYPE_EQUIPEMENT_BELT,				//装备.腰带
 	E_OBJECT_TYPE_EQUIPEMENT_SHOE,				//装备.鞋子
 	E_OBJECT_TYPE_EQUIPEMENT_AMULATE,			//装备.护符

	E_OBJECT_TYPE_EQUIPEMENT_ARRAY_HELMET,		//装备.头部
	E_OBJECT_TYPE_EQUIPEMENT_ARRAY_JERSEY,		//装备.球衣
	E_OBJECT_TYPE_EQUIPEMENT_ARRAY_TROUSER,		//装备.球裤
	E_OBJECT_TYPE_EQUIPEMENT_ARRAY_SHOE,		//装备.球鞋
	E_OBJECT_TYPE_EQUIPEMENT_ARRAY_GLOVES,		//装备.手套
	E_OBJECT_TYPE_EQUIPEMENT_ARRAY_PROTECT,		//装备.护具

	E_OBJECT_TYPE_EQUIPEMENT_WING1,				//装备.翅膀1
	E_OBJECT_TYPE_EQUIPEMENT_WING2,				//装备.翅膀2
	E_OBJECT_TYPE_EQUIPEMENT_WING3,				//装备.翅膀3
	E_OBJECT_TYPE_EQUIPEMENT_WING4,				//装备.翅膀4
	E_OBJECT_TYPE_EQUIPEMENT_WING5,				//装备.翅膀5
	E_OBJECT_TYPE_EQUIPEMENT_WING6,				//装备.翅膀6
	E_OBJECT_TYPE_EQUIPEMENT_WING7,				//装备.翅膀7
	E_OBJECT_TYPE_EQUIPEMENT_WING8,				//装备.翅膀8
	E_OBJECT_TYPE_NPC_MAJOR,					//npc.主角
	E_OBJECT_TYPE_NPC_POPULARITY,				//npc.声望伙伴
	E_OBJECT_TYPE_NPC_EXPLORER,					//npc.探索伙伴
	E_OBJECT_TYPE_NPC_MONSTER,					//npc.怪物
	E_OBJECT_TYPE_NPC_SCENE_OBJ,				//npc.场景对象
	E_OBJECT_TYPE_NPC_JUMPER,	     			//npc.传送门
	E_OBJECT_TYPE_TASK_CHALLENGE,				//任务.挑战
	E_OBJECT_TYPE_TASK_BRANCH,  				//任务.支线
	E_OBJECT_TYPE_TASK_MAIN,  					//任务.主线
	E_OBJECT_TYPE_FUBEN_NORMAL,					//副本.普通
	E_OBJECT_TYPE_FUBEN_HARD,					//副本.精英
	E_OBJECT_TYPE_FUBEN_SHENJIANG,				//副本.神将
	E_OBJECT_TYPE_FUBEN_XINMO,					//副本.心魔
	E_OBJECT_TYPE_FUBEN_HUODONG,				//副本.活动
	E_OBJECT_TYPE_FUBEN_ARRAY_NORMAL,			//副本阵型.普通
	E_OBJECT_TYPE_FUBEN_ARRAY_HARD,				//副本阵型.精英
	E_OBJECT_TYPE_FUBEN_ARRAY_SHENJIANG,		//副本阵型.神将
	E_OBJECT_TYPE_FUBEN_ARRAY_XINMO,			//副本阵型.心魔
	E_OBJECT_TYPE_FUBEN_ARRAY_HUODONG,			//副本阵型.活动
	E_OBJECT_TYPE_SKILL_NORMAL,					//技能.普通
	E_OBJECT_TYPE_SKILL_SPECIAL,				//技能.特殊
	E_OBJECT_TYPE_SKILL_BUFFCALL,				//技能.buff调用
	E_OBJECT_TYPE_PRIZE_DAILY,					//奖励.每日奖励
	E_OBJECT_TYPE_PRIZE_FIRST_RMB,				//奖励.首次充值
	E_OBJECT_TYPE_PRIZE_TOTAL_RMB,				//奖励.累积充值
	E_OBJECT_TYPE_PRIZE_LEVEL,					//奖励.等级
	E_OBJECT_TYPE_PRIZE_FUBEN,					//奖励.副本

	E_OBJECT_TYPE_FRAGMENT,						//碎片.各种子类型碎片

	E_OBJECT_TYPE_TASK_LOOP,  					//任务.环

	E_OBJECT_TYPE_ITEM_MATERIAL_EQUIPMENT,		//道具.材料.装备材料
	E_OBJECT_TYPE_ITEM_MATERIAL_WING,			//道具.材料.翅魂材料
	E_OBJECT_TYPE_PRIZE_ACTIVE_DAILY,			//奖励.活动每日
	E_OBJECT_TYPE_EQUIPMENT_WUSOUL,				//装备.武魂
	E_OBJECT_TYPE_ITEM_PASSIVESKILLBOOK,		//道具.被动技能书
};

enum EObjIdScale
{

	/*奖励*/
	E_OIS_PRIZE_START						=120000,  //
	E_OIS_PRIZE_END							=149999,  //
	E_OIS_PRIZE_DAILY_START					=120000,    //
	E_OIS_PRIZE_DAILY_END					=129999,  //
	E_OIS_PRIZE_TOTAL_RMB_START				=130000,  //
	E_OIS_PRIZE_TOTAL_RMB_END				=139999,  //
	E_OIS_PRIZE_FIRST_RMB_START				=140000,  //
	E_OIS_PRIZE_FIRST_RMB_END				=149999,  //
	E_OIS_PRIZE_LEVEL_START					=150000,  //
	E_OIS_PRIZE_LEVEL_END					=159999,  //
	E_OIS_PRIZE_FUBEN_START					=160000,  //
	E_OIS_PRIZE_FUBEN_END					=199999,  //
	E_OIS_PRIZE_ACTIVE_DAILY_START			=200000,  //
	E_OIS_PRIZE_ACTIVE_DAILY_END			=209999,  //

	/*公告*/
	E_OIS_NOTIFY_START						=1000,  //
	E_OIS_NOTIFY_END						=1999,  //

	/*套装*/
	E_OIS_SUIT_START						=2000,  //
	E_OIS_SUIT_END							=2999,  //

	/*职业*/
	E_OIS_PROFESSION_START					=100001,  //
	E_OIS_PROFESSION_END					=100009,  //

	E_OIS_ARRAY_START						=110101,  //
	E_OIS_ARRAY_END							=119999,  //

	E_OIS_ITEM_START						=10010000,  //
	E_OIS_ITEM_END							=10059999,  //

	E_OIS_ITEM_POTION_START					=10010000,  //
	E_OIS_ITEM_POTION_END					=10019999,  //

	E_OIS_ITEM_FORGE_FORMULA_START		    =10020000,  //
	E_OIS_ITEM_FORGE_FORMULA_END            =10029999,  //

	E_OIS_ITEM_MATERIAL_START		        =10030000,  //
	E_OIS_ITEM_MATERIAL_END					=10039999,  //

	E_OIS_ITEM_MATERIAL_EQUIPMENT_START_1	=10030000,  //
	E_OIS_ITEM_MATERIAL_EQUIPMENT_END_1		=10030110,  //

	E_OIS_ITEM_MATERIAL_EQUIPMENT_START_2	=10031000,  //
	E_OIS_ITEM_MATERIAL_EQUIPMENT_END_2		=10035999,  //

	E_OIS_ITEM_MATERIAL_WING_START_1		=10030111,  //
	E_OIS_ITEM_MATERIAL_WING_END_1			=10030200,  //

	E_OIS_ITEM_MATERIAL_WING_START_2		=10036000,  //
	E_OIS_ITEM_MATERIAL_WING_END_2			=10039999,  //


	E_OIS_ITEM_NEWER_GIFT_START				=10040000,  //
	E_OIS_ITEM_NEWER_GIFT_END				=10049999,  //



	E_OIS_GIFT_START					    =10990000,  //
	E_OIS_GIFT_END						    =10999999,  //

	E_OIS_EQUIPMENT_START					=11010000,  //
	E_OIS_EQUIPMENT_END						=11189999,  //

	E_OIS_EQUIPMENT_ARRAY_HELMET_START		=11010000,  //
	E_OIS_EQUIPMENT_ARRAY_HELMET_END        =11019999,  //

	E_OIS_EQUIPMENT_ARRAY_JERSEY_START		=11020000,  //
	E_OIS_EQUIPMENT_ARRAY_JERSEY_END	    =11029999,  //

	E_OIS_EQUIPMENT_ARRAY_TROUSER_START	    =11030000,  //
	E_OIS_EQUIPMENT_ARRAY_TROUSER_END		=11039999,  //

	E_OIS_EQUIPMENT_ARRAY_SHOE_START		=11040000,  //
	E_OIS_EQUIPMENT_ARRAY_SHOE_END			=11049999,  //

	E_OIS_EQUIPMENT_ARRAY_GLOVES_START		=11050000,  //
	E_OIS_EQUIPMENT_ARRAY_GLOVES_END		=11059999,  //

	E_OIS_EQUIPMENT_ARRAY_PROTECT_START		=11060000,  //
	E_OIS_EQUIPMENT_ARRAY_PROTECT_END		=11069999,  //

	E_OIS_EQUIPMENT_WING1_START				=11070000,  //
	E_OIS_EQUIPMENT_WING1_END				=11079999,  //

	E_OIS_EQUIPMENT_WING2_START				=11080000,  //
	E_OIS_EQUIPMENT_WING2_END				=11089999,  //

	E_OIS_EQUIPMENT_WING3_START				=11090000,  //
	E_OIS_EQUIPMENT_WING3_END				=11099999,  //
	
	E_OIS_EQUIPMENT_WING4_START				=11100000,  //
	E_OIS_EQUIPMENT_WING4_END				=11109999,  //

	E_OIS_EQUIPMENT_WING5_START				=11110000,  //
	E_OIS_EQUIPMENT_WING5_END				=11119999,  //

	E_OIS_EQUIPMENT_WING6_START				=11120000,  //
	E_OIS_EQUIPMENT_WING6_END				=11129999,  //

	E_OIS_EQUIPMENT_WING7_START				=11130000,  //
	E_OIS_EQUIPMENT_WING7_END				=11139999,  //

	E_OIS_EQUIPMENT_WING8_START				=11140000,  //
	E_OIS_EQUIPMENT_WING8_END				=11149999,  //

	E_OIS_EQUIPMENT_RING_START				=11150000,  //
	E_OIS_EQUIPMENT_RING_END				=11159999,  //

	E_OIS_EQUIPMENT_NECKLACE_START			=11160000,  //
	E_OIS_EQUIPMENT_NECKLACE_END			=11169999,  //

	E_OIS_EQUIPMENT_NEW_WING_START			=11170000,  //
	E_OIS_EQUIPMENT_NEW_WING_END			=11179999,  //

	E_OIS_EQUIPMENT_WUSOUL_START			=11180100,  //
	E_OIS_EQUIPMENT_WUSOUL_END				=11180799,  //

	E_OIS_NPC_START							=12000000,  //
	E_OIS_NPC_END							=12049999,  //

	E_OIS_NPC_MAJOR_ROLE_START				=12000000,  //
	E_OIS_NPC_MAJOR_ROLE_END				=12009999,  //

	E_OIS_NPC_POPULARITY_ROLE_START			=12010000,  //
	E_OIS_NPC_POPULARITY_ROLE_END			=12019999,  //

	E_OIS_NPC_EXPLORER_ROLE_START			=12020000,  //
	E_OIS_NPC_EXPLORER_ROLE_END             =12029999,  //

	E_OIS_NPC_MONSTER_START					=12030000,  //
	E_OIS_NPC_MONSTER_END					=12039999,  //

	E_OIS_NPC_SCENE_OBJ_START				=12040000,  //
	E_OIS_NPC_SCENE_OBJ_END					=12049999,  //

	E_OIS_NPC_JUMPER_START					=12050000,  //
	E_OIS_NPC_JUMPER_END					=12059999,  //

	E_OIS_NPC_MONSTER_ARRAY2_START			=12060000,	//
	E_OIS_NPC_MONSTER_ARRAY2_END			=12119999,	//

	E_OIS_TASK_START						=14010000,  //
	E_OIS_TASK_END							=14039999,  //

	E_OIS_TASK_MAIN_START					=14010000,  //
	E_OIS_TASK_MAIN_END						=14019999,  //

	E_OIS_TASK_BRANCH_START					=14020000,  //
	E_OIS_TASK_BRANCH_END					=14029999,  //

	E_OIS_TASK_CHALLENGE_START				=14030000,  //
	E_OIS_TASK_CHALLENGE_END				=14039999,  //

	E_OIS_TASK_LOOP_START					=14040000,  //
	E_OIS_TASK_LOOP_END						=14049999,  //

	E_OIS_MILITARY_RANK_START				=15000000,  //
	E_OIS_MILITARY_RANK_END					=15009999,  //

	E_OIS_FUBEN_START						=16010000,  //
	E_OIS_FUBEN_END							=16059999,  //

	E_OIS_FUBEN_NORMAL_START				=16010000,  //
	E_OIS_FUBEN_NORMAL_END					=16019999,  //

	E_OIS_FUBEN_HARD_START					=16020000,  //
	E_OIS_FUBEN_HARD_END					=16029999,  //

	E_OIS_FUBEN_SHENJIANG_START				=16030000,  //
	E_OIS_FUBEN_SHENJIANG_END				=16039999,  //

	E_OIS_FUBEN_XINMO_START					=16040000,  //
	E_OIS_FUBEN_XINMO_END					=16049999,  //

	E_OIS_FUBEN_HUODONG_START				=16050000,  //
	E_OIS_FUBEN_HUODONG_END					=16059999,  //

	E_OIS_FUBENARRAY_START					=17010000,  //
	E_OIS_FUBENARRAY_END					=17059999,  //

	E_OIS_FUBENARRAY_NORMAL_START           =17010000,  //
	E_OIS_FUBENARRAY_NORMAL_END             =17019999,  //

	E_OIS_FUBENARRAY_HARD_START				=17020000,  //
	E_OIS_FUBENARRAY_HARD_END				=17029999,  //

	E_OIS_FUBENARRAY_SHENJIANG_START        =17030000,  //
	E_OIS_FUBENARRAY_SHENJIANG_END          =17039999,  //

	E_OIS_FUBENARRAY_XINMO_START			=17040000,  //
	E_OIS_FUBENARRAY_XINMO_END				=17049999,  //

	E_OIS_FUBENARRAY_HUODONG_START			=17050000,  //
	E_OIS_FUBENARRAY_HUODONG_END			=17059999,  //

	E_OIS_SKILL_START						=21000000,  //
	E_OIS_SKILL_END							=23999999,  //

	E_OIS_SKILL_NORMAL_START				=21000000,  //
	E_OIS_SKILL_NORMAL_END					=21999999,  //

	E_OIS_SKILL_SPECIAL_START				=22000000,  //
	E_OIS_SKILL_SPECIAL_END					=22999999,  //

	E_OIS_SKILL_BUFFCALL_START				=23000000,  //
	E_OIS_SKILL_BUFFCALL_END				=23999999,  //

	E_OIS_BUFF_START						=31000000,  //
	E_OIS_BUFF_END							=39999999,  //

	E_OIS_FRAGMENT_START					=41000000,  //
	E_OIS_FRAGMENT_END						=49999999,  //


	E_OIS_PASSIVESKILLBOOK_START			=54000000,  //
	E_OIS_PASSIVESKILLBOOK_END				=54099999,  //
	
	E_OIS_BLOODWELFARE_GAME_START			=16040000,  //
	E_OIS_BLOODWELFARE_GAME_END				=16049999,  //
	E_OIS_TEST_END,
};

struct SLogConsumeDiamond
{
	unsigned int type;
	unsigned int gID;
	unsigned int itemID;
};

/*
数据库blob字段结构----------------------------------------------------------------------------------------------------
开始
*/

enum EDBLength
{
	MAX_TASK_COUNT=300, //总的任务个数
	MAX_TASK_FINISHED_COUNT_BLOB_LENGTH=1328, //1200+128,#4*300.

	MAX_CURRENT_TASK_COUNT=30, //当前正在做的任务个数,应该不会超过30.
	MAX_CURRENT_TASK_COUNT_BLOB_LENGTH=608, //16*30+128.

	MAX_PACKET_CAPACITY=120, //
	MAX_PACKET_CAPACITY_BLOB_LENGTH=4096, //4096,#20*120.
	FREE_PACKET_CAPACITY=40, //

	MAX_WING_PAGE_CAPACITY=10, //
	MAX_WING_PAGE_BLOB_LENGTH=288, //160+128,#20*8.
	MAX_WING_COMPOUNDER_BLOB_LENGTH=192, //8*8:64+128.
	MAX_WUSOUL_PAGE_CAPACITY = 6, //

	MAX_EQUIPMENT_PAGE_CAPACITY=8, //
	MAX_EQUIPMENT_STRENGTHEN_CAPACITY=800, //
	MAX_EQUIPMENT_STRENGTHEN_CAPACITY_BLOB_LENGTH=9728, //9600+128,#12*800.

	MAX_MATE_CAPACITY=50, //
	MAX_MATE_BLOB_LENGTH=24128, //18400+128//24000+128.

	MAX_RANDOM_RECORD_CAPACITY=10, //
	MAX_RANDOM_RECRUIT_BLOB_LENGTH=168, //#4*10,40+128.

	MAX_TODAY_FUBEN_COUNT=150, //每天记录打副本数量,精英有80,神将加心魔大概在20个左右
	MAX_TODAY_FUBEN_BLOB_LENGTH=1000, //150*5+250.
	MAX_RANK_RECORD_CAPACITY=4000, //
	MAX_CHALLENGE_RECORD_CAPACITY=40, //信息记录容量扩展到40.
	MAX_COMPOUND_WING_STAR_CAPACITY=256, //
	MAX_HARD_FUBEN_RECORD_CAPACITY=100, //

	MAX_TODAY_PRIZE_RECORD=128, //
	MAX_TODAY_PRIZE_BLOB_LENGTH=640, //128*4+128.

	MAX_PRIZE_RECORD=256, //
	MAX_PRIZE_BLOB_LENGTH=1152, //256*4+128.

	MAX_SENIOR_FUBEN_COUNT=50, //
	MAX_STRENGTH_INFO_BLOB_LENGTH=140, //12*1,12+128.
	MAX_CONSUME_DIAMOND_BLOB_LENGTH=212, //84*1,84+128.
	MAX_EASY_MATE_ARRAY_BLOB_LENGTH=152, //128+24.
	MAX_MISC_BLOB_LENGTH=2048, //2048,1196已经用2013-10-10.
	MAX_RANK_BLOB_LENGTH=40960, //122*100+2+4,千人榜36*1000；
	MAX_RANK_COUNT=100, //
	MAX_RANK_CHALLENGE_COUNT=1000, //
	MAX_CHALLENGE_RECORD_BLOB_LENGTH=2560, //56*40。
	MAX_NEW_SERVER_PRIZE_RANK=10, //
	MAX_TERRITORY_NUM=200,//最多200个领地，
	MAX_PUBLICMATE_NUM=1, //目前只有一个结构体存到数据库


	MAX_GANG_AFFAIRS_BLOB_LENGTH=2048,	//20*64.
	MAX_GANG_ROLELIST_BLOB_LENGTH=20480, //200*68.
	MAX_GANG_TASKORITEMORGEMS_BLOB_LENGTH=1024, //预留字段blob长度
	MAX_GANG_AFFAIRS_COUNT=20,			//最大成员动态信息数量
	MAX_GANG_ROLELIST_COUNT=200,		//最大帮派玩家数量
	MAX_GANGLIST_COUNT=100,				//单服最大帮派个数
	MAX_GANG_JOINLIST_BLOB_LENGTH=10240,	//50*120.
	MAX_GANG_JOINLIST_COUNT=50,	//申请加入列表最大玩家数

	MAX_FRIEND_OFFLINE_APPLY_COUNT =1000,  //玩家离线时，存储邀请记录的最大条目
	MAX_FRIEND_OFFLINE_REPLY_COUNT =1000,  //玩家离线时，存储回复记录的最大条目
	MAX_FRIEND_COUNT =30,  //好友上线数目
	MAX_FRIEND_APPLY_COUNT =40, //好友的申请记录信息

	MAX_GANGFIGHT_NUM =50, //因为最多只有100个帮派，而帮战是一对一的，所以帮战最大数为50。
	MAX_BREAKOFF_BROTHERS_DATA_COUNT =512, //存储最大的断交信息数.
	MAX_BROTHERS_BOON_DATA_COUNT =512,	//存储最大的结拜福利信息数.
	MAX_RANK_RECHARGE_COUNT =100,	//充值排行最大数

	MAX_DISCUSS_SCENE_PAGE =20, //场景的页数
	MAX_DISCUSS_SCENE =10, //最大挖角场景
	MAX_DISCUSS_SCENE_BLOG =20480, //2048*10

	MAX_COACH_CAPACITY=50, //教练的数目
	MAX_COACH_BLOB_LENGTH=24128, 
	MAX_CLUBCONDITION_COUNT = 400,//保存俱乐部刷新的成就
	MAX_ROLECLUBCONTION_COUNT = 400,
	MAX_CLUBCONDITION_BLOB_LENGTH = 20480, //玩家个人俱乐部成就
	MAX_INTOGAMEDATA_BLOB_LENGTH = 4096, //玩家进入比赛的记录

	MAX_ARRAY_CAPACITY=10*7, //阵型对应的装备栏
	FREE_ARRAY_CAPACITY=10*7, //默认开启的数目
	MAX_ARRAY_BLOB_LENGTH=2048, //512,#20*10*7. 整个阵型装备栏大小
	MAX_REFRESHITEM_MAXCOUNT=48, //
	MAX_PLAYERRECORD_MAXLENGTH=80, //
	MAX_PLAYERRECORD_MAXCOUNT=10, //

	MAX_TREASURE_CAPACITY=100, //
	MAX_TREASURE_CAPACITY_BLOB_LENGTH=4096, //4096,#20*120.

};


/***
//打包文件
*/
struct SPackedFileIndex
{
	char name[128];
	unsigned int startIndex;
	unsigned int endIndex;
};

struct SPackedFiles
{
	unsigned short count;
	SPackedFileIndex files[100/*count*/];
};

struct SMiscDB
{
	int shootMonsterCount;
};

struct SGetRoleInfoReq
{
	int i; 
};

struct SGetRoleInfoRsp
{
	SRole role;
};






#endif	//__PNL_PROTOCOLS_H__
