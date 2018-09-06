#ifndef _RTSP_SERVER_H_
#define _RTSP_SERVER_H_
#include "Rtsp_sys.h"

#define DP_RTSP_SERVER_MEDIA_ADDR_MAX_LEN					20
#define DP_RTSP_SERVER_MEDIA_STREAM_MAX						2

typedef enum _DP_RTSP_SERVER_TRANSPORT_E{
	DP_RTSP_SERVER_TRANSPORT_INVALID_TYPE = -1,
	DP_RTSP_SERVER_TRANSPORT_FREE_TYPE = 0,
	DP_RTSP_SERVER_TRANSPORT_TCP_TYPE = 1,				
	DP_RTSP_SERVER_TRANSPORT_UDP_TYPE = 2,	
	DP_RTSP_SERVER_TRANSPORT_MUL_TYPE = 3,	
	DP_RTSP_SERVER_TRANSPORT_MAX,
}DP_RTSP_SERVER_TRANSPORT_E;


typedef enum _DP_RTSP_SERVER_PORTOCOL_VERSION_E
{
	//RTSP 1.0
	DP_RTSP_SERVER_PORTOCOL_VERSION_1 = 1,
	//RTSP 2.0
	DP_RTSP_SERVER_PORTOCOL_VERSION_2,
	DP_RTSP_SERVER_PORTOCOL_VERSION_MAX,
}DP_RTSP_SERVER_PORTOCOL_VERSION_E;

typedef enum _DP_RTSP_SERVER_DEBUG_LEVEL_E
{
	DP_RTSP_SERVER_DEBUG_LEVEL_OFF = 0,
	DP_RTSP_SERVER_DEBUG_LEVEL_ERROR,
	DP_RTSP_SERVER_DEBUG_LEVEL_WARNING,
	DP_RTSP_SERVER_DEBUG_LEVEL_ALL,
	DP_RTSP_SERVER_DEBUG_LEVEL_MAX,
}DP_RTSP_SERVER_DEBUG_LEVEL_E;

typedef enum _DP_RTSP_SERVER_AAC_PROFILE_LEVEL_E
{
	DP_RTSP_SERVER_AAC_MAIN = 1,
	DP_RTSP_SERVER_AAC_LC = 2,
	DP_RTSP_SERVER_AAC_SSR = 3,
	DP_RTSP_SERVER_AAC_LTP = 4,
	DP_RTSP_SERVER_AAC_SBR = 5,
	DP_RTSP_SERVER_AAC_HVXC = 9,
	DP_RTSP_SERVER_AAC_MAX,
}DP_RTSP_SERVER_AAC_PROFILE_LEVEL_E;



typedef enum _DP_RTSP_SERVER_RETVAL_E
{
	//ͨ�óɹ�����
	DP_RTSP_SERVER_RETVAL_SUCCESS = 0,
	//�߳��˳�״̬����
	DP_RTSP_SERVER_RETVAL_THREAD_EXIT_SUCCESS = 1,
	//RTCP SRʱ�������OK
	DP_RTSP_SERVER_RETVAL_TIMEOUT_CHECK_SUCCESS = 2,
	//Check �˻�ʧ��
	DP_RTSP_SERVER_RETVAL_CHECK_USERNAME_FAILED = -1,
	//Check ����ʧ��
	DP_RTSP_SERVER_RETVAL_CHECK_PASSWORD_FAILED = -2,
	//�������õĲ����쳣����Ч
	DP_RTSP_SERVER_RETVAL_PARAM_ABNORMAL = -3,
	//�����˻���Ϣʧ��
	DP_RTSP_SERVER_RETVAL_SET_USERINFO_FAILED = -4,
	//ͨ�����ò���ʧ��
	DP_RTSP_SERVER_RETVAL_SET_PARAM_FAILED = -5,
	//���������
	DP_RTSP_SERVER_RETVAL_HANDLE_ABNORMAL = -6,
	//��������ʧ��
	DP_RTSP_SERVER_RETVAL_PROCESS_FALIED = -7,
	//�鲥���������У���ֹ�޸�ʧ��
	DP_RTSP_SERVER_RETVAL_CHANGE_MULTICAST_FALIED = -8,

	DP_RTSP_SERVER_RETVAL_PROCESS_MAX = 0xFFFF
}DP_RTSP_SERVER_RETVAL_E;

typedef enum _DP_RTSP_SERVER_MEDIA_TYPE_E
{
	DP_RTSP_SERVER_MEDIA_H264 = 0,
	DP_RTSP_SERVER_MEDIA_H265,
	DP_RTSP_SERVER_MEDIA_PCM,
	DP_RTSP_SERVER_MEDIA_MP3,
	DP_RTSP_SERVER_MEDIA_AAC,
	DP_RTSP_SERVER_MEDIA_ADTS_AAC,
	DP_RTSP_SERVER_MEDIA_LATM_AAC,
	DP_RTSP_SERVER_MEDIA_MAX,
}DP_RTSP_SERVER_MEDIA_TYPE_E;

typedef enum _DP_RTSP_SERVER_FRAME_TYPE_E
{
	DP_RTSP_SERVER_H264_FRAME_I = 0,
	DP_RTSP_SERVER_H264_FRAME_PB,
	DP_RTSP_SERVER_H265_FRAME_I ,
	DP_RTSP_SERVER_H265_FRAME_PB,
	DP_RTSP_SERVER_FRAME_PCM,
	DP_RTSP_SERVER_FRAME_MP3,
	DP_RTSP_SERVER_FRAME_AAC,
	DP_RTSP_SERVER_FRAME_MAX,
}DP_RTSP_SERVER_FRAME_TYPE_E;

typedef enum _DP_RTSP_SERVER_DATA_STATUS_E
{
	DP_RTSP_SERVER_DATA_STATUS_OFF = 0,
	DP_RTSP_SERVER_DATA_STATUS_ON,	
	DP_RTSP_SERVER_DATA_STATUS_MAX,
}DP_RTSP_SERVER_DATA_STATUS_E;

typedef enum _DP_RTSP_SERVER_MULTICAST_STATUS_E
{
	DP_RTSP_SERVER_MULTICAST_STATUS_OFF = 0,
	DP_RTSP_SERVER_MULTICAST_STATUS_ON,	
	DP_RTSP_SERVER_MULTICAST_STATUS_MAX,
}DP_RTSP_SERVER_MULTICAST_STATUS_E;

typedef struct _DP_RTSP_SERVER_ADAPTION_PARAMETER_S
{
	DP_U8 u8PacketLoss;					//������
	DP_U32 s32HighestSeqNo;				//RR���ն˰����
	DP_U32 u32Jitter;					//����
	DP_U32 u32LastSR;					//���һ�ε�SR����ʱ��(1/65536 s)
	DP_U32 u32DelaySinceLastSR;	//���ն˽��յ����һ��SR�����ʹ˴�RR��ʱ��(1/65536 s)
	DP_U32 u32CurrentRR;						//��ǰ���յ��˴�RR����ʱ��(1/65536 s)
}DP_RTSP_SERVER_ADAPTION_PARAMETER_S;


typedef struct _DP_RTSP_SERVER_INIT_INFO_S
{
	DP_S16 s16UrlMax;						//URL ��ʵ������
	DP_U16 u16ServerPort;					//Server Listen �����˿�
	DP_S16 s16PollThreadMax;				//����ģʽ�߳���ѯ���ֵ���̷߳���Clinet ����
	DP_S16 s16UrlClientRespMax;			//����ģʽServer���������
	DP_RTSP_SERVER_PORTOCOL_VERSION_E enRtspPortocolVersion;			//Э��汾��Ĭ�ϰ汾1
	DP_S8 s8InputQueueDataMaxConut;	//���û�����е���󻺴�֡��
}DP_RTSP_SERVER_INIT_INFO_S;


typedef struct _DP_RTSP_SERVER_CODE_PARAM_S
{
	DP_RTSP_SERVER_MEDIA_TYPE_E enMediaType;
	union{
			struct _MediaVideo{ 
				DP_S8 s8VideoFarmeRate;		
				DP_S32 s32VideoBitrate;			
				DP_S16 s16VideoWidth;			
				DP_S16 s16VideoHeigth;		
			}stMediaVideo;
			struct _MediaAudio{
				DP_S8 s8AudioChannel;			
				DP_S32 s32AudioSampleRate;	
				DP_S16 s16AudioOutRate;
				DP_RTSP_SERVER_AAC_PROFILE_LEVEL_E enAudioProfile;
			}stMediaAudio;
		}unMedia;
}DP_RTSP_SERVER_CODE_PARAM_S;


typedef struct _DP_RTSP_SERVER_CLIENT_INFO_S
{
	DP_S8 s8ClientConnectType;
	DP_S8 s8MediaConut;
	DP_U8 u8ClientAddr[DP_RTSP_SERVER_MEDIA_ADDR_MAX_LEN];
	union{
		struct _UdpConnectInfo{ 
			DP_U16 u16ClientPort[DP_RTSP_SERVER_MEDIA_STREAM_MAX][2];		
			DP_U16 u16ServerPort[DP_RTSP_SERVER_MEDIA_STREAM_MAX][2];					
		}stUdpConnectInfo;
		struct _TcpConnectInfo{
			DP_S8 s8ClientChannel[DP_RTSP_SERVER_MEDIA_STREAM_MAX][2];	
		}stTcpConnectInfo;
	}unConnectInfo;
}DP_RTSP_SERVER_CLIENT_INFO_S;

typedef struct _DP_RTSP_SERVER_URL_SERVE_INFO_S
{	
	DP_S16 s16ClientMaxConut;
	DP_S16 s16ClientRespConut;
	DP_RTSP_SERVER_CLIENT_INFO_S *pstClientInfo;
}DP_RTSP_SERVER_URL_SERVE_INFO_S;

typedef struct _DP_RTSP_SERVER_MEDIA_STREAM_INFO_S
{
	DP_RTSP_SERVER_FRAME_TYPE_E enFrameType;
	DP_P_U8 pu8FrameStream;
	DP_S32 s32FrameSize;
	DP_U32 u32TimeStamp;
}DP_RTSP_SERVER_MEDIA_STREAM_INFO_S;

typedef struct _DP_RTSP_SERVER_MULTICAST_INFO_S
{
	DP_U8 u8MulticastTTL;			//�鲥TTL
	DP_S8 s8MulticastAddr[DP_RTSP_SERVER_MEDIA_ADDR_MAX_LEN];//�鲥IP
	DP_RTSP_SERVER_MULTICAST_STATUS_E enMulticastEnabled;//�Ƿ�ʹ��
}DP_RTSP_SERVER_MULTICAST_INFO_S;

typedef struct _DP_RTSP_SERVER_MEDIA_VIDEO_CONFIG_S
{
	DP_S16 s16VideoSPSsize;
	DP_S16 s16VideoVPSsize;
	DP_S16 s16VideoPPSsize;
	DP_P_U8 pu8VideoSPS;
	DP_P_U8 pu8VideoPPS;
	DP_P_U8 pu8VideoVPS;
}DP_RTSP_SERVER_MEDIA_VIDEO_CONFIG_S;


typedef DP_S32 (*DP_CALL_BACK_SetInputDataStatus)(DP_HANDLE_ID HandleId,DP_RTSP_SERVER_DATA_STATUS_E enQueueStatus);


typedef DP_S32 (*DP_CALL_BACK_SetVideoAdaptionParameter)(DP_HANDLE_ID HandleId,DP_STREAM_ID StreamId,DP_RTSP_SERVER_ADAPTION_PARAMETER_S stVideoAdaption);


#ifdef __cplusplus
extern "C" {
#endif

DP_S32 DP_RTSP_SERVER_Init(DP_RTSP_SERVER_INIT_INFO_S stRtspInitInfo,DP_CALL_BACK_SetInputDataStatus funcDataStatusFunction,
	DP_CALL_BACK_SetVideoAdaptionParameter funcVideoAdaptionFunction);

DP_S32 DP_RTSP_SERVER_SetDebugLevel(DP_RTSP_SERVER_DEBUG_LEVEL_E enDebugLevel);

DP_S32 DP_RTSP_SERVER_GetDebugLevel(DP_V);

DP_S32   DP_RTSP_SERVER_SetUrlMulticastParameter(DP_HANDLE_ID HandleId,DP_STREAM_ID StreamId,DP_RTSP_SERVER_MULTICAST_INFO_S stMulticastInfo);

DP_V DP_RTSP_SERVER_SetTestPollThreadMaxOrUrlClientRespMax(DP_S16 s16PollThreadMax,DP_S16 s16UrlClientRespMax);

DP_HANDLE_ID DP_RTSP_SERVER_AddMediaName(DP_P_U8 pu8UrlMediaName,DP_S32 s32UrlMediaNameSize);

DP_STREAM_ID DP_RTSP_SERVER_CodeParamBindMediaName(DP_HANDLE_ID HandleId,
		DP_RTSP_SERVER_CODE_PARAM_S stCodeParam);

DP_S32 DP_RTSP_SERVER_SetCodeParam(DP_HANDLE_ID HandleId,DP_STREAM_ID StreamId,
		DP_RTSP_SERVER_CODE_PARAM_S stCodeParam);

DP_S32 DP_RTSP_SERVER_SetMediaSPS_PPS_VPS(DP_HANDLE_ID HandleId,DP_STREAM_ID StreamId,DP_RTSP_SERVER_MEDIA_VIDEO_CONFIG_S stSdpInfo);


DP_S32 DP_RTSP_SERVER_ChangeUserInfo(DP_HANDLE_ID HandleId,
			DP_P_U8 pu8SrcUserName,DP_P_U8 pu8SrcPassword,
			DP_P_U8 pu8DestUserName,DP_P_U8 pu8DestPassword);

DP_S32 DP_RTSP_SERVER_GetUrlServeInfo(DP_HANDLE_ID HandleId,
		DP_RTSP_SERVER_URL_SERVE_INFO_S *pstUrlServeInfo);

DP_S32 DP_RTSP_SERVER_FreeUrlServeInfo(DP_RTSP_SERVER_URL_SERVE_INFO_S *pstUrlServeInfo);

DP_S32 DP_RTSP_SERVER_MediaStreamInput(DP_HANDLE_ID HandleId,DP_STREAM_ID StreamId,
			DP_RTSP_SERVER_MEDIA_STREAM_INFO_S stMediaStream);

DP_S32 DP_RTSP_SERVER_Start(DP_V);

DP_V DP_RTSP_SERVER_Stop(DP_V);

DP_S32 DP_RTSP_SERVER_UnInit(DP_V);

#ifdef __cplusplus
}
#endif

#endif