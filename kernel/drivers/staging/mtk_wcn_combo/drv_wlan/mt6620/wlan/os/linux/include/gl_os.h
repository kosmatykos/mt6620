/*******************************************************************************
* Copyright (c) 2013, MediaTek Inc.
*
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License version 2 as published by the Free
* Software Foundation.
*
* Alternatively, this software may be distributed under the terms of BSD
* license.
********************************************************************************
*/

/*******************************************************************************
* THIS SOFTWARE IS PROVIDED BY MEDIATEK "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, NON-INFRINGEMENT OR FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL MEDIATEK BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************************
*/

#ifndef _GL_OS_H
#define _GL_OS_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/
/*------------------------------------------------------------------------------
* Flags for LINUX(OS) dependent
*------------------------------------------------------------------------------
*/
#define CFG_MAX_WLAN_DEVICES                1	/* number of wlan card will coexist */

#define CFG_MAX_TXQ_NUM                     4	/* number of tx queue for support multi-queue h/w  */

#define CFG_USE_SPIN_LOCK_BOTTOM_HALF       0	/* 1: Enable use of SPIN LOCK Bottom Half for LINUX
						   0: Disable - use SPIN LOCK IRQ SAVE instead */

#define CFG_TX_PADDING_SMALL_ETH_PACKET     0	/* 1: Enable - Drop ethernet packet if it < 14 bytes.
						   And pad ethernet packet with dummy 0 if it < 60 bytes.
						   0: Disable */

#define CFG_TX_STOP_NETIF_QUEUE_THRESHOLD   256	/* packets */

#define CFG_TX_STOP_NETIF_PER_QUEUE_THRESHOLD   64	/* packets */
#define CFG_TX_START_NETIF_PER_QUEUE_THRESHOLD  32	/* packets */

#define ETH_P_1X                            0x888E
#define IPTOS_PREC_OFFSET                   5
#define USER_PRIORITY_DEFAULT               0

#define ETH_WPI_1X                         0x88B4

#define ETH_HLEN                                14
#define ETH_TYPE_LEN_OFFSET                     12
#define ETH_P_IP                                0x0800
#define ETH_P_1X                                0x888E
#define ETH_P_PRE_1X                            0x88C7

#define IPVERSION                               4
#define IP_HEADER_LEN                           20

#define IPVH_VERSION_OFFSET                     4	/* For Little-Endian */
#define IPVH_VERSION_MASK                       0xF0
#define IPTOS_PREC_OFFSET                       5
#define IPTOS_PREC_MASK                         0xE0

#define SOURCE_PORT_LEN                         2
/* NOTE(Kevin): Without IP Option Length */
#define LOOK_AHEAD_LEN                          (ETH_HLEN + IP_HEADER_LEN + \
SOURCE_PORT_LEN)

/* 802.2 LLC/SNAP */
#define ETH_LLC_OFFSET                          (ETH_HLEN)
#define ETH_LLC_LEN                             3
#define ETH_LLC_DSAP_SNAP                       0xAA
#define ETH_LLC_SSAP_SNAP                       0xAA
#define ETH_LLC_CONTROL_UNNUMBERED_INFORMATION  0x03

/* Bluetooth SNAP */
#define ETH_SNAP_OFFSET                         (ETH_HLEN + ETH_LLC_LEN)
#define ETH_SNAP_LEN                            5
#define ETH_SNAP_BT_SIG_OUI_0                   0x00
#define ETH_SNAP_BT_SIG_OUI_1                   0x19
#define ETH_SNAP_BT_SIG_OUI_2                   0x58

#define BOW_PROTOCOL_ID_SECURITY_FRAME          0x0003

#if defined(MT6620)
#define CHIP_NAME    "MT6620"
#elif defined(MT5931)
#define CHIP_NAME    "MT5931"
#elif defined(MT6628)
#define CHIP_NAME    "MT6628"
#endif

#define DRV_NAME "["CHIP_NAME "]: "

/* Define if target platform is Android.
* It should already be defined in Android kernel source
*/
#ifndef CONFIG_ANDROID
#define CONFIG_ANDROID      0
#endif

/* for CFG80211 IE buffering mechanism */
#define CFG_CFG80211_IE_BUF_LEN     (512)

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/
#include <linux/version.h>	/* constant of kernel version */

#include <linux/kernel.h>	/* bitops.h */

#include <linux/timer.h>	/* struct timer_list */
#include <linux/jiffies.h>	/* jiffies */
#include <linux/delay.h>	/* udelay and mdelay macro */

#if CONFIG_ANDROID
#include <linux/wakelock.h>
#endif

#if LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 12)
#include <linux/irq.h>		/* IRQT_FALLING */
#include <linux/hardirq.h>	/*for in_interrupt */
#endif

#include <linux/netdevice.h>	/* struct net_device, struct net_device_stats */
#include <linux/etherdevice.h>	/* for eth_type_trans() function */
#include <linux/wireless.h>	/* struct iw_statistics */
#include <linux/if_arp.h>
#include <linux/inetdevice.h>	/* struct in_device */

#include <linux/ip.h>		/* struct iphdr */

#include <linux/string.h>	/* for memcpy()/memset() function */
#include <linux/stddef.h>	/* for offsetof() macro */

#include <linux/proc_fs.h>	/* The proc filesystem constants/structures */

#include <linux/rtnetlink.h>	/* for rtnl_lock() and rtnl_unlock() */
#include <linux/kthread.h>	/* kthread_should_stop(), kthread_run() */
#include <asm/uaccess.h>	/* for copy_from_user() */
#include <linux/fs.h>		/* for firmware download */
#include <linux/vmalloc.h>

#include <linux/kfifo.h>	/* for kfifo interface */
#include <linux/cdev.h>		/* for cdev interface */

#include <linux/firmware.h>	/* for firmware download */

#if defined(_HIF_SDIO)
#include <linux/mmc/sdio.h>
#include <linux/mmc/sdio_func.h>
#endif

#include <linux/random.h>

#include <linux/lockdep.h>

#include <asm/io.h>		/* readw and writew */

#if WIRELESS_EXT > 12
#include <net/iw_handler.h>
#endif

#include "version.h"
#include "config.h"

#if CFG_ENABLE_WIFI_DIRECT_CFG_80211
#include <linux/wireless.h>
#include <net/cfg80211.h>
#endif

#include <linux/module.h>

#include "gl_typedef.h"
#include "typedef.h"
#include "queue.h"
#include "gl_kal.h"
#if CFG_CHIP_RESET_SUPPORT
#include "gl_rst.h"
#endif
#include "hif.h"

#include "debug.h"

#include "wlan_lib.h"
#include "wlan_oid.h"

#if CFG_ENABLE_AEE_MSG
#include <linux/aee.h>
#endif

extern BOOLEAN fgIsBusAccessFailed;

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
#define GLUE_FLAG_HALT          BIT(0)
#define GLUE_FLAG_INT           BIT(1)
#define GLUE_FLAG_OID           BIT(2)
#define GLUE_FLAG_TIMEOUT       BIT(3)
#define GLUE_FLAG_TXREQ         BIT(4)
#define GLUE_FLAG_SUB_MOD_INIT  BIT(5)
#define GLUE_FLAG_SUB_MOD_EXIT  BIT(6)
#define GLUE_FLAG_SUB_MOD_MULTICAST  BIT(7)
#define GLUE_FLAG_FRAME_FILTER      BIT(8)
#define GLUE_FLAG_HALT_BIT          (0)
#define GLUE_FLAG_INT_BIT           (1)
#define GLUE_FLAG_OID_BIT           (2)
#define GLUE_FLAG_TIMEOUT_BIT       (3)
#define GLUE_FLAG_TXREQ_BIT         (4)
#define GLUE_FLAG_SUB_MOD_INIT_BIT  (5)
#define GLUE_FLAG_SUB_MOD_EXIT_BIT  (6)
#define GLUE_FLAG_SUB_MOD_MULTICAST_BIT  (7)
#define GLUE_FLAG_FRAME_FILTER_BIT  (8)

#define GLUE_BOW_KFIFO_DEPTH        (1024)
/* #define GLUE_BOW_DEVICE_NAME        "MT6620 802.11 AMP" */
#define GLUE_BOW_DEVICE_NAME        "ampc0"

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef struct _GL_WPA_INFO_T {
	UINT_32 u4WpaVersion;
	UINT_32 u4KeyMgmt;
	UINT_32 u4CipherGroup;
	UINT_32 u4CipherPairwise;
	UINT_32 u4AuthAlg;
	BOOLEAN fgPrivacyInvoke;
#if CFG_SUPPORT_802_11W
	UINT_32 u4Mfp;
#endif
} GL_WPA_INFO_T, *P_GL_WPA_INFO_T;

typedef enum _ENUM_RSSI_TRIGGER_TYPE {
	ENUM_RSSI_TRIGGER_NONE,
	ENUM_RSSI_TRIGGER_GREATER,
	ENUM_RSSI_TRIGGER_LESS,
	ENUM_RSSI_TRIGGER_TRIGGERED,
	ENUM_RSSI_TRIGGER_NUM
} ENUM_RSSI_TRIGGER_TYPE;

#if CFG_ENABLE_WIFI_DIRECT
typedef enum _ENUM_SUB_MODULE_IDX_T {
	P2P_MODULE = 0,
	SUB_MODULE_NUM
} ENUM_SUB_MODULE_IDX_T;

typedef enum _ENUM_NET_REG_STATE_T {
	ENUM_NET_REG_STATE_UNREGISTERED,
	ENUM_NET_REG_STATE_REGISTERING,
	ENUM_NET_REG_STATE_REGISTERED,
	ENUM_NET_REG_STATE_UNREGISTERING,
	ENUM_NET_REG_STATE_NUM
} ENUM_NET_REG_STATE_T;

#endif

typedef struct _GL_IO_REQ_T {
	QUE_ENTRY_T rQueEntry;
/* wait_queue_head_t       cmdwait_q; */
	BOOL fgRead;
	BOOL fgWaitResp;
#if CFG_ENABLE_WIFI_DIRECT
	BOOL fgIsP2pOid;
#endif
	P_ADAPTER_T prAdapter;
	PFN_OID_HANDLER_FUNC pfnOidHandler;
	PVOID pvInfoBuf;
	UINT_32 u4InfoBufLen;
	PUINT_32 pu4QryInfoLen;
	WLAN_STATUS rStatus;
	UINT_32 u4Flag;
} GL_IO_REQ_T, *P_GL_IO_REQ_T;

#if CFG_ENABLE_BT_OVER_WIFI
typedef struct _GL_BOW_INFO {
	BOOLEAN fgIsRegistered;
	dev_t u4DeviceNumber;	/* dynamic device number */
/*    struct kfifo            *prKfifo;       / * for buffering indicated events * / */
	struct kfifo rKfifo;	/* for buffering indicated events */
	spinlock_t rSpinLock;	/* spin lock for kfifo */
	struct cdev cdev;
	UINT_32 u4FreqInKHz;	/* frequency */

	UINT_8 aucRole[CFG_BOW_PHYSICAL_LINK_NUM];	/* 0: Responder, 1: Initiator */
	ENUM_BOW_DEVICE_STATE aeState[CFG_BOW_PHYSICAL_LINK_NUM];
	PARAM_MAC_ADDRESS arPeerAddr[CFG_BOW_PHYSICAL_LINK_NUM];

	wait_queue_head_t outq;

#if CFG_BOW_SEPARATE_DATA_PATH
/* Device handle */
	struct net_device *prDevHandler;
	BOOLEAN fgIsNetRegistered;
#endif
} GL_BOW_INFO, *P_GL_BOW_INFO;
#endif

/*
* type definition of pointer to p2p structure
*/
typedef struct _GL_P2P_INFO_T GL_P2P_INFO_T, *P_GL_P2P_INFO_T;

struct _GLUE_INFO_T {
/* Device handle */
	struct net_device *prDevHandler;

/* Device Index(index of arWlanDevInfo[]) */
	INT_32 i4DevIdx;

/* Device statistics */
	struct net_device_stats rNetDevStats;

/* Wireless statistics struct net_device */
	struct iw_statistics rIwStats;

/* spinlock to sync power save mechanism */
	spinlock_t rSpinLock[SPIN_LOCK_NUM];

/* semaphore for ioctl */
	struct semaphore ioctl_sem;

	UINT_32 u4Flag;		/* GLUE_FLAG_XXX */
	UINT_32 u4PendFlag;
/* UINT_32 u4TimeoutFlag; */
	UINT_32 u4OidCompleteFlag;
	UINT_32 u4ReadyFlag;	/* check if card is ready */

/* Number of pending frames, also used for debuging if any frame is
* missing during the process of unloading Driver.
*
* NOTE(Kevin): In Linux, we also use this variable as the threshold
* for manipulating the netif_stop(wake)_queue() func.
*/
	INT_32 ai4TxPendingFrameNumPerQueue[4][CFG_MAX_TXQ_NUM];
	INT_32 i4TxPendingFrameNum;
	INT_32 i4TxPendingSecurityFrameNum;

/* current IO request for kalIoctl */
	GL_IO_REQ_T OidEntry;

/* registry info*/
	REG_INFO_T rRegInfo;

/* firmware */
	struct firmware *prFw;

/* Host interface related information */
/* defined in related hif header file */
	GL_HIF_INFO_T rHifInfo;

/*! \brief wext wpa related information */
	GL_WPA_INFO_T rWpaInfo;

/* Pointer to ADAPTER_T - main data structure of internal protocol stack */
	P_ADAPTER_T prAdapter;

#ifdef WLAN_INCLUDE_PROC
	struct proc_dir_entry *pProcRoot;
#endif				/* WLAN_INCLUDE_PROC */

/* Indicated media state */
	ENUM_PARAM_MEDIA_STATE_T eParamMediaStateIndicated;

/* Device power state D0~D3 */
	PARAM_DEVICE_POWER_STATE ePowerState;

	struct completion rScanComp;	/* indicate scan complete */
	struct completion rHaltComp;	/* indicate main thread halt complete */
	struct completion rPendComp;	/* indicate main thread halt complete */
#if CFG_ENABLE_WIFI_DIRECT
	struct completion rSubModComp;	/*indicate sub module init or exit complete */
#endif
	WLAN_STATUS rPendStatus;

	QUE_T rTxQueue;

/* OID related */
	QUE_T rCmdQueue;
/* PVOID                   pvInformationBuffer; */
/* UINT_32                 u4InformationBufferLength; */
/* PVOID                   pvOidEntry; */
/* PUINT_8                 pucIOReqBuff; */
/* QUE_T                   rIOReqQueue; */
/* QUE_T                   rFreeIOReqQueue; */

	wait_queue_head_t waitq;
	struct task_struct *main_thread;

	struct timer_list tickfn;

#if CFG_SUPPORT_EXT_CONFIG
	UINT_16 au2ExtCfg[256];	/* NVRAM data buffer */
	UINT_32 u4ExtCfgLength;	/* 0 means data is NOT valid */
#endif

#if 1				/* CFG_SUPPORT_WAPI */
/* Should be large than the PARAM_WAPI_ASSOC_INFO_T */
	UINT_8 aucWapiAssocInfoIEs[42];
	UINT_16 u2WapiAssocInfoIESz;
#endif

#if CFG_ENABLE_BT_OVER_WIFI
	GL_BOW_INFO rBowInfo;
#endif

#if CFG_ENABLE_WIFI_DIRECT
	P_GL_P2P_INFO_T prP2PInfo;
#if CFG_SUPPORT_P2P_RSSI_QUERY
/* Wireless statistics struct net_device */
	struct iw_statistics rP2pIwStats;
#endif
#endif
	BOOLEAN fgWpsActive;
	UINT_8 aucWSCIE[500];	/*for probe req */
	UINT_16 u2WSCIELen;
	UINT_8 aucWSCAssocInfoIE[200];	/*for Assoc req */
	UINT_16 u2WSCAssocInfoIELen;

/* NVRAM availability */
	BOOLEAN fgNvramAvailable;

	BOOLEAN fgMcrAccessAllowed;

/* MAC Address Overriden by IOCTL */
	BOOLEAN fgIsMacAddrOverride;
	PARAM_MAC_ADDRESS rMacAddrOverride;

	SET_TXPWR_CTRL_T rTxPwr;

/* for cfg80211 scan done indication */
	struct cfg80211_scan_request *prScanRequest;

/* to indicate registered or not */
	BOOLEAN fgIsRegistered;

/* for cfg80211 connected indication */
	UINT_32 u4RspIeLength;
	UINT_8 aucRspIe[CFG_CFG80211_IE_BUF_LEN];

	UINT_32 u4ReqIeLength;
	UINT_8 aucReqIe[CFG_CFG80211_IE_BUF_LEN];
};

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 0)
/* linux 2.4 */
typedef void (*PFN_WLANISR) (int irq, void *dev_id, struct pt_regs * regs);
#else
typedef irqreturn_t(*PFN_WLANISR) (int irq, void *dev_id,
				   struct pt_regs * regs);
#endif

typedef void (*PFN_LINUX_TIMER_FUNC) (unsigned long);

/* generic sub module init/exit handler
*   now, we only have one sub module, p2p
*/
#if CFG_ENABLE_WIFI_DIRECT
typedef BOOLEAN(*SUB_MODULE_INIT) (P_GLUE_INFO_T prGlueInfo);
typedef BOOLEAN(*SUB_MODULE_EXIT) (P_GLUE_INFO_T prGlueInfo);

typedef struct _SUB_MODULE_HANDLER {
	SUB_MODULE_INIT subModInit;
	SUB_MODULE_EXIT subModExit;
	BOOLEAN fgIsInited;
} SUB_MODULE_HANDLER, *P_SUB_MODULE_HANDLER;

#endif

#if CONFIG_NL80211_TESTMODE

typedef struct _NL80211_DRIVER_TEST_MODE_PARAMS {
	UINT_32 index;
	UINT_32 buflen;
} NL80211_DRIVER_TEST_MODE_PARAMS, *P_NL80211_DRIVER_TEST_MODE_PARAMS;

/*SW CMD */
typedef struct _NL80211_DRIVER_SW_CMD_PARAMS {
	NL80211_DRIVER_TEST_MODE_PARAMS hdr;
	UINT_8 set;
	unsigned long adr;
	unsigned long data;
} NL80211_DRIVER_SW_CMD_PARAMS, *P_NL80211_DRIVER_SW_CMD_PARAMS;

struct iw_encode_exts {
	__u32 ext_flags;	/*!< IW_ENCODE_EXT_* */
	__u8 tx_seq[IW_ENCODE_SEQ_MAX_SIZE];	/*!< LSB first */
	__u8 rx_seq[IW_ENCODE_SEQ_MAX_SIZE];	/*!< LSB first */
	__u8 addr[MAC_ADDR_LEN];	/*!< ff:ff:ff:ff:ff:ff for broadcast/multicast
					 *   (group) keys or unicast address for
					 *   individual keys */
	__u16 alg;		/*!< IW_ENCODE_ALG_* */
	__u16 key_len;
	__u8 key[32];
};

/*SET KEY EXT */
typedef struct _NL80211_DRIVER_SET_KEY_EXTS {
	NL80211_DRIVER_TEST_MODE_PARAMS hdr;
	UINT_8 key_index;
	UINT_8 key_len;
	struct iw_encode_exts ext;
} NL80211_DRIVER_SET_KEY_EXTS, *P_NL80211_DRIVER_SET_KEY_EXTS;

#endif

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/
/*----------------------------------------------------------------------------*/
/* Macros of SPIN LOCK operations for using in Glue Layer                     */
/*----------------------------------------------------------------------------*/
#if CFG_USE_SPIN_LOCK_BOTTOM_HALF
#define GLUE_SPIN_LOCK_DECLARATION()
#define GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, rLockCategory)   \
{ \
if (rLockCategory < SPIN_LOCK_NUM) \
spin_lock_bh(&(prGlueInfo->rSpinLock[rLockCategory])); \
}
#define GLUE_RELEASE_SPIN_LOCK(prGlueInfo, rLockCategory)   \
{ \
if (rLockCategory < SPIN_LOCK_NUM) \
spin_unlock_bh(&(prGlueInfo->rSpinLock[rLockCategory])); \
}
#else /* !CFG_USE_SPIN_LOCK_BOTTOM_HALF */
#define GLUE_SPIN_LOCK_DECLARATION()                        UINT_32 __u4Flags =	\
0
#define GLUE_ACQUIRE_SPIN_LOCK(prGlueInfo, rLockCategory)   \
{ \
if (rLockCategory < SPIN_LOCK_NUM) \
spin_lock_irqsave(&(prGlueInfo)->rSpinLock[ \
rLockCategory], __u4Flags); \
}
#define GLUE_RELEASE_SPIN_LOCK(prGlueInfo, rLockCategory)   \
{ \
if (rLockCategory < SPIN_LOCK_NUM) \
spin_unlock_irqrestore(&(prGlueInfo->rSpinLock[	\
rLockCategory]), \
__u4Flags); \
}
#endif /* !CFG_USE_SPIN_LOCK_BOTTOM_HALF */

/*----------------------------------------------------------------------------*/
/* Macros for accessing Reserved Fields of native packet                      */
/*----------------------------------------------------------------------------*/
#define GLUE_GET_PKT_QUEUE_ENTRY(_p)	\
(&(((struct sk_buff *)(_p))->cb[0]))

#define GLUE_GET_PKT_DESCRIPTOR(_prQueueEntry)	\
((P_NATIVE_PACKET)((UINT_32)_prQueueEntry - \
offsetof(struct sk_buff, cb[0])))

#define  GLUE_SET_PKT_FLAG_802_11(_p)  \
(*((PUINT_8)&(((struct sk_buff *)(_p))->cb[4])) |= BIT(7))

#define GLUE_SET_PKT_FLAG_1X(_p)  \
(*((PUINT_8)&(((struct sk_buff *)(_p))->cb[4])) |= BIT(6))

#define GLUE_SET_PKT_FLAG_PAL(_p)  \
(*((PUINT_8)&(((struct sk_buff *)(_p))->cb[4])) |= BIT(5))

#define GLUE_SET_PKT_FLAG_P2P(_p)  \
(*((PUINT_8)&(((struct sk_buff *)(_p))->cb[4])) |= BIT(4))

#define GLUE_SET_PKT_TID(_p, _tid)  \
(*((PUINT_8)&(((struct sk_buff *)(_p))->cb[4])) |= \
(((UINT_8)((_tid) & (BITS(0, 3))))))

#define GLUE_SET_PKT_FRAME_LEN(_p, _u2PayloadLen) \
(*((PUINT_16)&(((struct sk_buff *)(_p))->cb[6])) = \
(UINT_16)(_u2PayloadLen))

#define GLUE_GET_PKT_FRAME_LEN(_p)    \
(*((PUINT_16)&(((struct sk_buff *)(_p))->cb[6])))

#define  GLUE_GET_PKT_IS_802_11(_p)	   \
((*((PUINT_8)&(((struct sk_buff *)(_p))->cb[4]))) & (BIT(7)))

#define  GLUE_GET_PKT_IS_1X(_p)	       \
((*((PUINT_8)&(((struct sk_buff *)(_p))->cb[4]))) & (BIT(6)))

#define GLUE_GET_PKT_TID(_p)	    \
((*((PUINT_8)&(((struct sk_buff *)(_p))->cb[4]))) & (BITS(0, 3)))

#define GLUE_GET_PKT_IS_PAL(_p)	       \
((*((PUINT_8)&(((struct sk_buff *)(_p))->cb[4]))) & (BIT(5)))

#define GLUE_GET_PKT_IS_P2P(_p)	       \
((*((PUINT_8)&(((struct sk_buff *)(_p))->cb[4]))) & (BIT(4)))

#define GLUE_SET_PKT_HEADER_LEN(_p, _ucMacHeaderLen)	\
(*((PUINT_8)&(((struct sk_buff *)(_p))->cb[5])) = \
(UINT_8)(_ucMacHeaderLen))

#define GLUE_GET_PKT_HEADER_LEN(_p) \
(*((PUINT_8)&(((struct sk_buff *)(_p))->cb[5])))

#define GLUE_SET_PKT_ARRIVAL_TIME(_p, _rSysTime) \
(*((POS_SYSTIME)&(((struct sk_buff *)(_p))->cb[8])) = \
(OS_SYSTIME)(_rSysTime))

#define GLUE_GET_PKT_ARRIVAL_TIME(_p)	 \
(*((POS_SYSTIME)&(((struct sk_buff *)(_p))->cb[8])))

/* Check validity of prDev, private data, and pointers */
#define GLUE_CHK_DEV(prDev) \
((prDev && *((P_GLUE_INFO_T *)netdev_priv(prDev))) ? TRUE : FALSE)

#define GLUE_CHK_PR2(prDev, pr2) \
((GLUE_CHK_DEV(prDev) && pr2) ? TRUE : FALSE)

#define GLUE_CHK_PR3(prDev, pr2, pr3) \
((GLUE_CHK_PR2(prDev, pr2) && pr3) ? TRUE : FALSE)

#define GLUE_CHK_PR4(prDev, pr2, pr3, pr4) \
((GLUE_CHK_PR3(prDev, pr2, pr3) && pr4) ? TRUE : FALSE)

#define GLUE_SET_EVENT(pr) \
kalSetEvent(pr)

#define GLUE_INC_REF_CNT(_refCount)     atomic_inc((atomic_t *)&(_refCount))
#define GLUE_DEC_REF_CNT(_refCount)     atomic_dec((atomic_t *)&(_refCount))

#define DbgPrint(...)
/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
#ifdef WLAN_INCLUDE_PROC
INT_32 procRemoveProcfs(struct net_device *prDev, char *pucDevName);

INT_32 procInitProcfs(struct net_device *prDev, char *pucDevName);
#endif /* WLAN_INCLUDE_PROC */

#if CFG_ENABLE_BT_OVER_WIFI
BOOLEAN glRegisterAmpc(P_GLUE_INFO_T prGlueInfo);

BOOLEAN glUnregisterAmpc(P_GLUE_INFO_T prGlueInfo);
#endif

#if CFG_ENABLE_WIFI_DIRECT

VOID wlanSubModRunInit(P_GLUE_INFO_T prGlueInfo);

VOID wlanSubModRunExit(P_GLUE_INFO_T prGlueInfo);

BOOLEAN wlanSubModInit(P_GLUE_INFO_T prGlueInfo);

BOOLEAN wlanSubModExit(P_GLUE_INFO_T prGlueInfo);

VOID
wlanSubModRegisterInitExit(SUB_MODULE_INIT rSubModInit,
			   SUB_MODULE_EXIT rSubModExit,
			   ENUM_SUB_MODULE_IDX_T eSubModIdx);

BOOLEAN wlanExportGlueInfo(P_GLUE_INFO_T * prGlueInfoExpAddr);

BOOLEAN wlanIsLaunched(VOID);

void p2pSetMulticastListWorkQueueWrapper(P_GLUE_INFO_T prGlueInfo);

#endif

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif /* _GL_OS_H */
