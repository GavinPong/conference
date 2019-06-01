/**********************************************************
datatime:201905301700
author:trb team
version:1.0

文件概述：
|-此文件仅用来给第三方互动库提供者使用；
|-互动库提供者，需按此文件来提供互动功能接口；
|-user_id：目前是根据房间内用户列表序号定义的，可拓展为数据库中的用户ID，由互动库底层决定使用哪种
|-room_id：目前是根据服务器上会议室列表序号定义的，可拓展为数据库中的房间ID，由互动库底层决定使用哪种
|-结构体成员可以按需新增


=======================================history start==============================================
datetime:20190531
version:1.0
modify：
|-提供配套文档
|-enum _ret_code_exin新增新的别名 result_code_e
|-on_conference_state接口中result类型由int修正为result_code_e
|-conference_state_e枚举列表新增自己离开会议室状态值CONFERENCE_STATE_ROOM_EXIT
|-新增描述辅流状态的结构体aux_stream_state_info_t
|-修改get_conference_room_info接口参数将roomid改成roomIndx
---------------------------------------------------------------------------------------------------
datetime:20190530
version:0.6
modify：
|-修正接口中结构体名称不对的问题
---------------------------------------------------------------------------------------------------
datetime:20190521
version:0.5
modify：
|-新增音视频授权接口；
|-新增点对点接口；
|-新增ret_code_e枚举表
|-完善mediaInfo结构体
|-新增room_inf_t结构体
|-新增user_inf_t结构体
|-新增申请辅流权限接口
|-修改conference_chat_info_t
|-完善saudio_mixer_props_s
==============================================history end==============================================

**********************************************************/

typedef enum _conference_state_e{
	CONFERENCE_STATE_LOGIN_MCU = 1,    		// 连接MCU获取会议室列表完成
	CONFERENCE_STATE_LOGIN_ROOM,			// 登录指定会议室完成,返回本地用户信息
	CONFERENCE_STATE_USER_ENTER,    		// 有用户进入会议室
	CONFERENCE_STATE_USER_LEAVE,   			// 有用户离开会议室
	CONFERENCE_STATE_ROOM_EXIT,   			// 自己离开会议室
	CONFERENCE_STATE_USER_TALK,    			// 有用户音频状态变化
	CONFERENCE_STATE_USER_BCAST,    		// 有用户视频状态变化
	CONFERENCE_STATE_USER_CHAIR,    		// 有用户主讲状态变化
	CONFERENCE_STATE_LOOKED,    			// 作为听讲时，被查看视频
	CONFERENCE_STATE_USER_CLOSE,    		// 连接异常.
	CONFERENCE_STATE_USER_REQTALK,   		//用户申请发言
	CONFERENCE_STATE_CONNECT_MCU_FAILED, 	//登录MCU失败
	CONFERENCE_STATE_LOGIN_ROOM_FAILED,  	//登录房间失败
	CONFERENCE_STATE_USER_KICKED,     		//用户被踢出了房间
	CONFERENCE_STATE_USER_VPOS,      		//用户视频布局位置改变
	CONFERENCE_STATE_UPDATE_INTERACT,    	//互动端有更新
	CONFERENCE_STATE_USER_CHAT,    			// 收到聊天信息
	CONFERENCE_STATE_USER_VNC,    			// VNC状态变化
	CONFERENCE_STATE_NICK_NAME,   			//用户昵称发生变化  
	CONFERENCE_STATE_RECV_JOIN,   			//收到加入信息  
	CONFERENCE_STATE_RECV_INVITE,   		//收到邀请信息
	CONFERENCE_STATE_REJECT_JOIN,   		//收到拒绝加入信息
	CONFERENCE_STATE_ALLOW_JOIN,   			//收到同意加入信息
	CONFERENCE_STATE_REJECT_INVITE,   		//收到拒绝邀请信息
	CONFERENCE_STATE_ALLOW_INVITE,   		//收到同意邀请信息
	CONFERENCE_STATE_TRANSPARENT,   		//透传数据
	CONFERENCE_STATE_USER_AUX,		   		//有用户辅流状态发生变化
	
	//CONFERENCE_STATE_USER = 10000,   		//用户自定义信息 使用+1的方式递增
}conference_state_e;

typedef enum _conference_media_type_e{
	CONFERENCE_MEDIA_TYPE_AUDIO = 1,//音频流
	CONFERENCE_MEDIA_TYPE_VIDEO_MAJOR,//主流
	CONFERENCE_MEDIA_TYPE_VIDEO_MINOR,//辅流
	CONFERENCE_MEDIA_TYPE_VIDEO_MINOR2,//辅流2
}conference_media_type_e;

//开发库提供者完成定义
typedef enum _ret_code_e{
	retCode_Success = 0,				                // 正常
	retCode_False,				             // 失败
	retCode_ParamErr,				             // 参数错误
	retCode_InitErr,				              // 初始化错误
	retCode_InitedErr,			             // 已经初始化
	retCode_UninitErr,			             // 反初始化错误
	retCode_SockErr,				              // SOCK错误或者异常
	retCode_AddrErr,				              // IP地址错误
	retCode_PortErr,				              // 端口错误
	retCode_CreateSockErr,		         // 创建SOCK错误
	retCode_SockBindErr,			          // 绑定SOCK错误
	retCode_SockCnntErr,			          // 连接SOCK错误
	retCode_SockListenErr,		         // 监听SOCK错误
	retCode_SockAcceptErr,		         // 接收SOCK连接错误
	retCode_SockSendErr,			          // sock发送数据错误
	retCode_SockRecvErr,			          // sock接收数据错误
	retCode_SizeNotEnough,		          // 空间或大小不够
	retCode_SizeEnough,			            // 空间或大小足够了
	retCode_MsgErr,				               // 指令错误
	retCode_CurlErr,				              // Curl库错误
	retCode_CurlInitErr,			          // CURL库初始化失败
	retCode_CurlSendErr,			          // CURL库发送失败
	retCode_CurlRecvErr,			          // CURL库接收失败
	retCode_FileErr,				              // 文件错误或异常
	retCode_FileExistErr,		          // 文件已存在
	retCode_FileNoteExistErr,		       // 文件不存在
	retCode_FileHaveOpen,		          // 文件已经打开
	retCode_FileCreateErr,		         // 创建文件错误
	retCode_FileOpenErr,			          // 打开文件错误	
	retCode_FileReadErr,			          // 读文件错误
	retCode_FileReadEnd,			          // 读到文件结尾
	retCode_FileWriteErr,		          // 写文件错误
	retCode_FileSeekErr,			          // 文件seek错误
	retCode_FileCloseErr,		          // 关闭文件错误
	retCode_FileCopyErr,			          // 复制文件错误
	retCode_FileCutErr,			           // 剪切文件错误	
	retCode_FileFormatErr,		         // 文件格式错误
	retCode_FileSameErr,			          // 操作或对象重复
	retCode_FileAccessErr,		         // 文件无法访问
	retCode_FileSizeErr,			          // 大小尺寸不对
	retCode_FileFindErr,			          // 查找失败
	retCode_FileRemoveErr,           // 删除文件错误
	retCode_DirErr,				               // 目录错误或异常
	retCode_DirExistErr,			          // 目录已存在
	retCode_DirNotexistErr,		        // 目录不存在
	retCode_DirCreateErr,		          // 创建目录错误
	retCode_DirOpenErr,			           // 打开目录错误	
	retCode_DirCloseErr,			          // 关闭目录错误
	retCode_DirCopyErr,			           // 复制目录错误
	retCode_DirCutErr,			            // 剪切目录错误
	retCode_DirFindErr,			           // 查找目录错误	
	retCode_DirSameErr,			           // 目录重名
	retCode_DirAccessErr,		          // 目录无法访问
	retCode_DirRemoveErr,            // 删除目录错误
	retCode_MemoryErr,			             // 内存错误或异常 
	retCode_MemoryAllocErr,		        // 内存分配错误 
	retCode_MemoryFreeErr,		         // 内存释放错误 
	retCode_MemoryOutErr,		          // 内存大小不够
	retCode_StreamErr,			             // 流错误(文件流、数据流等)
	retCode_StreamNotErr,		          // 不存在这个流
	retCode_StreamExistErr,		        // 已存在这个流
	retCode_ListErr,				              // 列表错误
	retCode_QueueErr,				             // 队列错误
	retCode_QueueNodeErr,		          // 队列中节点错误
	retCode_QueueEmptyErr,		         // 队列空
	retCode_QueueFullErr,		          // 队列满
	retCode_QueueFindErr,		          // 查找节点失败
	retCode_XmlErr,				               // xml错误
	retCode_XmlOpenErr,			           // 打开xml文件失败
	retCode_XmlNodeErr,			           // 获取XML节点内容失败
	retCode_XmlAttributeErr,	        // 获取XML节点属性内容失败
	retCode_XmlNodeNotExist,	        // XML节点不存在
	retCode_RecordErr,			             // 录制错误
	retCode_RecordRunErr,		          // 录制进行中
	retCode_RecordNotStart,		         // 录制已结束、或者录制未开始	
	retCode_RecordStopErr,		         // 录制停止失败
	retCode_RecordDircetErr,	        // 启动电影模式录制失败
	retCode_RecordResErr,		          // 启动资源模式录制失败
	retCode_VaCheckErr,              // va函数调用失败
	retCode_VaProfileErr,            // 不支持这种profile
	retCode_VaRcErr,		               // 不支持这种码率控制模式
	retCode_VaAdmixing,               // 合成模式中，不支持同时编解码
	retCode_EncSupportErr,           // 不支持编码
	retCode_EncErr,			                // 编码失败
	retCode_EncInitedErr,		          // 编码器初始化失败
	retCode_EncNotFindErr,		         // 找不到编码器
	retCode_EncUninitErr,		          // 编码器未初始化
	retCode_ParseErr,				             // 解析失败
	retCode_DecSupportErr,           // 不支持解码
	retCode_DecSupportYUV420,        // 不支持解码成yuv420
	retCode_DecNotFindEntryPoint,    // 找不到入口点
	retCode_DecFailed,                // 解码失败
	retCode_OpNotSupport,		          // 操作不被支持
	retCode_YUVFormatErr,		          // 不支持的YUV格式
	retCode_IDEnrityErr,			           // 身份ID错误
	retCode_Timeout,				               // 超时错误
	retCode_NotObjectErr,             // 找不到对象
	retCode_ObjectSupportErr,        // 对象不支持此功能
	retCode_DataErr,                  // 数据错误(非法数据)
	retCode_ZlibErr,                  // zlib库错误
	retCode_NotLoginErr,              // 没有登陆
	retCode_ReloginedErr,             // 不能重复登陆了
	retCode_StateErr,                 // 状态不对
	retCode_ThreadErr,                // 线程错误
	retCode_CamCtrlErr,		             // 远摇摄像头失败
	retCode_AccessErr,                // 拒绝访问
	retCode_UserPasswordErr,         // 用户名或密码错误
	retCode_NotLoginInfo,            // 未设置登陆信息
	retCode_NoScreenConnection,        //没有显示器接入
	retCode_UnSupportResolution,          //不支持的分辨率
	retCode_UnCompleteData,                  //不完整的数据
	retCode_Unknow = 1000,			           // 未知错误

	// 互动错误代码
	retCode_Exception = 0x1002, //异常错误
	retCode_ServerInterErr,//服务器内部错误
	retCode_NvalidSessionErr,//无效的会话
	retCode_NotFindUserErr,//找不到用户
	retCode_VerifiFailureErr,//验证失败
	retCode_DenyAccessErr,//拒绝访问
	retCode_InvalidParam,//参数错误
	retCode_SytemMantainErr,//系统正在维护
	retCode_MuchVisitedErr,//访问人数过多

	retCode_NotFindFileErr,//文件未找到") },
	retCode_NotFindFileListErr,//文件列表未找到") },
	retCode_FileListExist,//文件列表已存在") },
	retCode_FileTransChnUnexist,//文件传输通道不存在") },
	retCode_FileUploading,//文件正在上传中") },
	retCode_FileTooLarge,//文件大小超过限定值") },
	retCode_SenderDidnotUpload,//发送者还未上传该文件") },
	retCode_FileExist,//文件已存在") },

	retCode_NanmeOrPasswordErr,//用户名或密码错误") },
	retCode_RoomUnexist,//房间未找到") },
	retCode_RoomFull,//房间已满") },
	retCode_ApplicationTypeMismatch,//应用类型不匹配") },
	retCode_ServerMismatch,//服务器不匹配") },
	retCode_SpecifiedServerNotFound,//未找到指定的服务器") },
	retCode_ServerFull,//服务器已满员") },
	retCode_UserExist,//用户已存在") },
	retCode_NeedRoomPassword,//需要输入房间密码") },
	retCode_RoomLock,//房间已锁定") },
	retCode_RoomOverdue,//房间已过期") },
	retCode_RoomClosed,//房间已关闭") },
	retCode_ModeratorRefusesJoin,//主持人拒绝用户进入") },
	retCode_UuserAreBlackListed,//用户被列入黑名单") },
	retCode_ServerCascadeFailure,//服务器级联失败") },
	retCode_ServerNotBoot,//服务器未启动") },
	retCode_ServerStoped,//服务器已停止") },
	retCode_LackOfBalance,//余额不足") },
	retCode_ServiceDiscontinuation,//服务已停用") },

	retCode_ChairPasswordErr,//主席密码错误") },
	retCode_InteractiveClassroomUnexist,//互动课堂不存在") },
	retCode_AccessDenied,//拒绝访问") },
	retCode_KickOut,//踢出房间,
	retCode_UserClose,//用户异常
	retCode_StreamTypeMismatch,//流类型不匹配") },
	retCode_ExceedMaxPreview,//超出最大预览数") },
	retCode_OutOfResources,//资源不足") },
	retCode_NetworkException,//网络异常") },
	retCode_RegisterIdle,			// 空闲/未注册
	retCode_Registering,			// 注册中
	retCode_Registered,			// 已注册
	retCode_DeRegistered,			// 已注销
	retCode_RegisterFailed,		// 注册失败
	retCode_ErrorNetwork,         // 网络错误
	retCode_ErrorAuthFailed,      // 认证失败
	retCode_UserBusy,				// 用户忙
	retCode_LongTimeNoReSponse,	// 长时间无应答
	retCode_LoginFailed,			// 登录失败
}ret_code_e, result_code_e;

typedef _intvite_type_e{
	INVITE_TYPE_VIDEO,
	INVITE_TYPE_AUDIO,
}intvite_type_e;


typedef struct _aux_stream_state_info_s{
	int m_i32UserID,//用户id
	int m_i32ResponseState;//响应状态0-失败 1-成功 2-申请中(暂未使用)
	conference_media_type_e m_eMediaType;//流类型
}aux_stream_state_info_t;


typedef struct _conference_chat_info_s{
	int m_i32SrcID;
	int m_i32DstID;
	int m_i32Color;
	char m_strContent[128];
}conference_chat_info_t;	

typedef struct _media_info_s
{//32字节
	unsigned short m_u16MediaType;        //媒体类型0-audio 1-main video 2-aux video...
	unsigned short m_u16CodecID;          //编码类型,视频编码时 3表示h264, 音频编码时, 0-pcm 1-opus  2-g7221  3-amrwb
	unsigned short m_u16FrameSeq;         //低8位:组包标识  1-始 0-中间 2-结束 3完整包
	unsigned short m_u16KeyFrame;         //视频关键帧0-否 1-是 或者音频采样位数
	unsigned short m_u16Framerate;        //视频帧率或者一个音频编码包的持续时间(单位ms)
	unsigned short m_u16StreamID;         //数据流序号
	int      m_u32W_S;					//视频宽 或音频采样率
	int      m_u32H_C;					//视频高 或音频声道数   
	int      m_u32Bitrate;                //码率,单位K(原始数据码率=0)
	unsigned long long m_u64TimeStamp;    //时间戳(ms)    
}media_info_t;

typedef struct _room_info_s{
	char m_strRoomID[64];
	char m_strRoomName[32];
	char m_strCreatorID[32];
	time_t  m_tStartTime;         //会议开始时间
	time_t  m_tEndTime;         //会议开始时间
	int m_s32MaxUserCnt;			//会议室支持的最大成员数  
	int m_s32CurUserCnt;			//会议室当前成员数
}room_info_t;

typedef struct _user_info_s{
	/***user自身的属性*******/
	unsigned char m_u8IsMaster;	//是否主讲 0 - 听讲  1 - 主讲, 暂时不考虑中间态
	unsigned char m_u8IsChairMan;//是否主席
	unsigned char m_u8BcastVideo;//是否广播video，广播定义为全授权
	unsigned char m_u8BcastAudio;//是否广播audio，广播定义为全授权
	unsigned char m_u8GainAux[CONFERENCE_AUX_MAX];//是否获取到辅流资源
	unsigned char m_u8SignalStatus;	//信号状态（强度）

	/***user在本端的属性*******/
	char m_strID[32];	//用户ID
	char m_strUserName[32];//用户名
	char m_strNickName[32];//用户昵称
	unsigned char m_u8AuthVideo;//有没有权限拉视频流（是否被授权） 0-不能 1-正在申请授权	 2-可以
	unsigned char m_u8AuthAudio;//有没有权限拉音频流（是否被授权） 0-不能 1-正在申请授权  2-可以
	unsigned char m_u8AudioState;//音频状态,0 未发言 1 请求发言(等待发言) 2 正在发言
}user_info_t;
		
/**
 * The conference SDK event handler structure.
 */
typedef struct {
    /** 聊天信息上报器
 
     @param pchat_info 会议聊天信息指针.
     */
	void (*on_conference_chat) (const conference_chat_info_t *pchat_info);
    
    /** 会议中各种事件上报接口
     
     @param result 0:成功,other:异常.
	 @param conference_state_id事件ID，具体查看conference_state_e
	 @param puser_info:用户信息指针。开发库提供者完成定义
	 @param append_data：附加数据
     */
	void (*on_conference_state) (result_code_e result, conference_state_e  conference_state_id, const user_info_t *puser_info, void *append_data);

    /** 数据流上报接口
     
     @param pmedia_data 数据媒体头信息指针.
     @param pdata 数据指针.
	 @param data_size 数据长度.
	 @param user_id 数据来源.
	 @param media_type 媒体类型.
     */
	void (*on_conference_stream_data) (const media_info_t *pmedia_info, const char *pdata, int data_len, int user_id, conference_media_type_e media_type);

} conference_event_handler_t;

typedef struct _audio_mixer_props_s{
	int m_i32Sample;//采样率
	int m_i32Channel;//通道数
	int m_i32SampleBit;//每采样数bit位
}audio_mixer_props_t;


/** 初始化开发库
    @param pmixer_props 混音器输出属性,用于设置互动回调出的PCM的属性.
    @param pevent_handler 事件处理器指针.
*/
ret_code_e init(const audio_mixer_props_t *pmixer_props, const conference_event_handler_t *pevent_handler);
//---------------------------------------------------------------------------------------------------------
/** 反初始化开发库
*/
ret_code_e uninit();
//---------------------------------------------------------------------------------------------------------
/** 连接服务器
    @param pserver_ddr MCU地址.
    @param server_port MCU端口.
	@param pusername 登录用户名.
    @param ppassWord 登录密  码.
*/
ret_code_e connect_MCU(const char* pserver_ddr, int server_port, const char* pusername, const char* ppassWord);
//---------------------------------------------------------------------------------------------------------
/** 断开服务器 

*/
ret_code_e disconnect_MCU();
//---------------------------------------------------------------------------------------------------------
/** 获取服务器上会议室数量 
	@param pcount 存储会议室个数指针.
*/
ret_code_e get_conference_room_count(int* pcount);
//---------------------------------------------------------------------------------------------------------
/** 获取对应会议室id的房间信息 
	@param room_indx 会议室在服务器上的序号
	@param proom_info 会议室信息: 开发库提供者完成定义.
*/
ret_code_e get_conference_room_info(int room_indx, room_info_t* proom_info);
//---------------------------------------------------------------------------------------------------------
/** 登录指定会议室id的会议室 
	@param conference_room_id 会议室id: 0<= id < (*pcount).
*/
ret_code_e login_conference_room(int conference_room_id);
//---------------------------------------------------------------------------------------------------------
/** 退出房间
*/
ret_code_e logout_conference_room();
//---------------------------------------------------------------------------------------------------------
/** 踢出房间
	@param user_id 用户ID.
*/
ret_code_e kickout_conference_room(int user_id);
//---------------------------------------------------------------------------------------------------------
/** 邀请通话（建立点对点也用这个）:请求加入+邀请加入通用，内部逻辑做区分
	@param user_id 用户ID.
	@param intvite_type:通话类型，详见intvite_type_e表.
	@param ctrl:1-开始 0-停止.
*/
ret_code_e invite(int user_id, intvite_type_e intvite_type, int ctrl);
//---------------------------------------------------------------------------------------------------------
/** 控制用户的邀请
	@param user_id 用户ID.
	@param ctrl 1-同意，0-拒绝.
*/
ret_code_e ctrl_user_invite(int user_id, int ctrl);
//---------------------------------------------------------------------------------------------------------
/** 获取自己的用户信息 
	@param puser_info 用户信息缓存地址.
*/
ret_code_e get_own_user_info(user_info_t* puser_info);
//---------------------------------------------------------------------------------------------------------
/** 获取会议室内用户数
	@param pcount 用户数缓存地址.
*/
ret_code_e get_user_count(int* pcount);
//---------------------------------------------------------------------------------------------------------
/** 获取指定ID的用户信息 
	@param user_id 用户id
	@param puser_info 用户信息缓存地址.
*/
ret_code_e get_user_info(int user_id, user_info_t* puser_info);
//---------------------------------------------------------------------------------------------------------
/** 发送聊天信息 
	@param user_id pconference_chat_info:聊天信息缓存地址.
*/
ret_code_e send_chat(const conference_chat_info_t* pconference_chat_info);
//---------------------------------------------------------------------------------------------------------
/** 申请主讲 
	@param ctrl:1-申请、0-取消申请.
*/
ret_code_e apply_for_master(int ctrl);
//---------------------------------------------------------------------------------------------------------
/** 申请发言
	@param ctrl:1-申请、0-取消申请.
*/
ret_code_e apply_for_talk(int ctrl);
//---------------------------------------------------------------------------------------------------------
/** 申请辅流权限
	@param ctrl:1-申请、0-取消申请.
*/
ret_code_e apply_for_aux(int ctrl);
//---------------------------------------------------------------------------------------------------------
/** 拒绝/允许用户发言 + 停止正在进行的发言
	@param user_id：用户ID .
	@param ctrl：1-运行 、0-拒绝.
*/
ret_code_e ctrl_user_talk_apply(int user_id, int ctrl); 
//---------------------------------------------------------------------------------------------------------
/** 授权音频权限
	@param src_user_id：授权出去的用户 .
	@param sdst_user_id：接受授权的用户.
	@param ctrl：1-启用授权 0-关闭授权.
*/
ret_code_e auth_audio(int src_user_id, int sdst_user_id, int ctrl);
//---------------------------------------------------------------------------------------------------------
/** 授权视频权限
	@param src_user_id：授权出去的用户 .
	@param sdst_user_id：接受授权的用户.
	@param ctrl：1-启用授权 0-关闭授权.
*/
ret_code_e auth_video(int src_user_id, int dst_user_id, int ctrl);
//---------------------------------------------------------------------------------------------------------
/** 查看用户视频：用户向服务器发送流
	@param user_id：用户ID .
	@param ctrl：1-开始 、0-停止 .
*/
ret_code_e check_user_video(int user_id, int ctrl);
//---------------------------------------------------------------------------------------------------------
/** 查看用户音频：用户向服务器发送流
	@param user_id：用户ID .
	@param ctrl：1-开始 、0-停止 .
*/
ret_code_e check_user_audio(int user_id, int ctrl);
//---------------------------------------------------------------------------------------------------------
/** 给房间内所有人授权查看user_id的视频
	@param user_id：用户ID .
	@param ctrl：1-开始 、0-停止 .
*/
ret_code_e bcast_user_video(int user_id, int ctrl);
//---------------------------------------------------------------------------------------------------------
/** 给房间内所有人授权查看user_id的音频
	@param user_id：用户ID .
	@param ctrl：1-开始 、0-停止 .
*/
ret_code_e bcast_user_audio(int user_id, int ctrl);
//---------------------------------------------------------------------------------------------------------
/** 切换互动端
	@param user_id：互动端用户ID .
*/
ret_code_e set_interact(int user_id);
//---------------------------------------------------------------------------------------------------------
/** 发流
	@param pmedia_headr：流数据头信息指针 .
	@param pdata：流数据指针 .
	@param data_len：流数据长度 .
	@param media_type：流类型，详见conference_media_type_e .
*/
ret_code_e send_stream(const media_info_t* pmedia_info, const char* pdata, int data_len, conference_media_type_e media_type);
//---------------------------------------------------------------------------------------------------------
/** 向服务器发送接收流请求
	@param user_id:用户ID .
	@param media_type：流类型，详见conference_media_type_e .
	@param ctrl：1-开始 0-停止 .
*/
ret_code_e recv_stream(int user_id, conference_media_type_e media_type, int ctrl);
//---------------------------------------------------------------------------------------------------------
/** 透传上层数据接口
	@param user_id:用户ID .
	@param pdata：数据缓存地址.
	@param data_len：数据长度.
	@param data_type：0-二进制 1-字串.
*/
ret_code_e send_transparent_data(int user_id, const char *pdata, int data_len, int data_type);
