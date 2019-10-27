#ifndef _DRV_TAPI_KPI_IO_H
#define _DRV_TAPI_KPI_IO_H
/******************************************************************************

                              Copyright (c) 2014
                            Lantiq Deutschland GmbH

  For licensing information, see the file 'LICENSE' in the root folder of
  this software module.

******************************************************************************/

/**
   \file drv_tapi_kpi_io.h
   This file contains the interface declaration that can be used by other
   drivers to access the Kernel Packet Interface (KPI).
   The KPI is used to exchange packetized data with other drivers.
*/

/** \defgroup TAPI_INTERFACE_KPI Kernel Packet interface
    Function interface that can be used by other drivers to exchange packetized
    voice streams with the TAPI driver. */
/*@{*/

/* ========================================================================== */
/*                                 Includes                                   */
/* ========================================================================== */
#include <ifx_types.h>
#include "drv_tapi_io.h"      /* needed for TAPI events */

/* ========================================================================== */
/*                               Configuration                                */
/* ========================================================================== */
/** Definition of the maximum number of channels in a KPI group; same for all
    groups. */
#define IFX_TAPI_KPI_MAX_CHANNEL_PER_GROUP  16

/* Alias names for groups. */
#define IFX_TAPI_KPI_UDP                    IFX_TAPI_KPI_GROUP1
#define IFX_TAPI_KPI_DECT                   IFX_TAPI_KPI_GROUP2
#define IFX_TAPI_KPI_HDLC                   IFX_TAPI_KPI_GROUP3

/** Defines the size of egress FIFOs in each KPI group; same for all groups. */
#define IFX_TAPI_KPI_EGRESS_FIFO_SIZE       200
/** Defines the size of ingress FIFOs in each KPI group; same for all groups. */
#define IFX_TAPI_KPI_INGRESS_FIFO_SIZE      200
/** Define an upper limit for the KPI buffer pool growth */
#define IFX_TAPI_KPI_GROWTH_LIMIT         1000

/* ========================================================================== */
/*                             Macro definitions                              */
/* ========================================================================== */
/** Definition of KPI group 0 */
#define IFX_TAPI_KPI_GROUP0       0x0000
/** Definition of KPI group 1 */
#define IFX_TAPI_KPI_GROUP1       0x1000
/** Definition of KPI group 2 */
#define IFX_TAPI_KPI_GROUP2       0x2000
/** Definition of KPI group 3 */
#define IFX_TAPI_KPI_GROUP3       0x3000
/** Definition of KPI group 4 */
#define IFX_TAPI_KPI_GROUP4       0x4000
/** Definition of KPI group 5 */
#define IFX_TAPI_KPI_GROUP5       0x5000
/** Definition of KPI group 6 */
#define IFX_TAPI_KPI_GROUP6       0x6000
/** Definition of KPI group 7 */
#define IFX_TAPI_KPI_GROUP7       0x7000
/** Definition of KPI group 8 */
#define IFX_TAPI_KPI_GROUP8       0x8000
/** Definition of KPI group 9 */
#define IFX_TAPI_KPI_GROUP9       0x9000
/** Definition of KPI group 10 */
#define IFX_TAPI_KPI_GROUP10      0xA000
/** Definition of KPI group 11 */
#define IFX_TAPI_KPI_GROUP11      0xB000
/** Definition of KPI group 12 */
#define IFX_TAPI_KPI_GROUP12      0xC000
/** Definition of KPI group 13 */
#define IFX_TAPI_KPI_GROUP13      0xD000
/** Definition of KPI group 14 */
#define IFX_TAPI_KPI_GROUP14      0xE000
/** Definition of KPI group 15 */
#define IFX_TAPI_KPI_GROUP15      0xF000

/* ========================================================================== */
/*                             Type definitions                               */
/* ========================================================================== */

/** Type IFX_TAPI_KPI_CH_t is used for the KPI channel numbers. The KPI channel
    consists of the KPI group in the 4 MSB bits, and the channel within this
    group in the LSB bits of this type. For example, channel 5 in group 2 is
    built as (IFX_TAPI_KPI_GROUP2 | 0x0005) */
typedef IFX_uint16_t    IFX_TAPI_KPI_CH_t;

/** Enum used to name the packet streams that can be re-directed to the KPI */
typedef enum
{
   /** Source stream generated by CODer. */
   IFX_TAPI_KPI_STREAM_COD,
   /** Source stream generated by DECT. */
   IFX_TAPI_KPI_STREAM_DECT,
   /** Source stream generated by HDLC. */
   IFX_TAPI_KPI_STREAM_HDLC,
   /** Maximum stream. */
   IFX_TAPI_KPI_STREAM_MAX
} IFX_TAPI_KPI_STREAM_t;

/* OwnerId to be used with the voice buffer functions requiring an ID */
enum
{
   IFX_TAPI_BUFFER_OWNER_UNKNOWN    = 0x00,
   IFX_TAPI_BUFFER_OWNER_FW         = 0x01,
   IFX_TAPI_BUFFER_OWNER_KPI2UDP    = 0x10,
   IFX_TAPI_BUFFER_OWNER_COD_KPI    = 0x11,
   IFX_TAPI_BUFFER_OWNER_COD_MPS    = 0x12,
   IFX_TAPI_BUFFER_OWNER_COD_FW     = 0x13,
   IFX_TAPI_BUFFER_OWNER_HDLC       = 0x20,
   IFX_TAPI_BUFFER_OWNER_HDLC_KPI   = 0x21,
   IFX_TAPI_BUFFER_OWNER_HDLC_VMMC  = 0x22,
   IFX_TAPI_BUFFER_OWNER_HDLC_MPS   = 0x23,
   IFX_TAPI_BUFFER_OWNER_HDLC_FW    = 0x24
};

/** Structure to configure the re-direction of packet streams to the KPI.
    Used by IOCTL \ref IFX_TAPI_KPI_CH_CFG_SET.

    \remarks
    - stream = COD & KPI group = 0 : default, stream will be sent to user space.
    - stream = COD & KPI group > 0 : packet stream will be sent to KPI.
    - stream = DECT & KPI group = 0 : DECT packet stream will be discarded.
    - stream = DECT & KPI group > 0 : DECT packet stream will be sent to KPI.
*/
typedef struct
{
   /** Packet stream that should be re-directed,
       see \ref IFX_TAPI_KPI_STREAM_t. */
   IFX_TAPI_KPI_STREAM_t     nStream;
   /** KPI group and channel where the stream should be sent to. */
   IFX_TAPI_KPI_CH_t         nKpiCh;
} IFX_TAPI_KPI_CH_CFG_t;

/** Structure to configure the KPI group parameters;
    used by IOCTL \ref IFX_TAPI_KPI_GRP_CFG_SET.
*/
typedef struct
{
   /** Group to be configured given as with the IFX_TAPI_KPI_GROUPx defines */
   IFX_TAPI_KPI_CH_t         nKpiGroup;
   /** Number of slots in the egress FIFO. */
   IFX_uint8_t               nEgressFifoSize;
   /** Number of slots in the ingress FIFO. */
   IFX_uint8_t               nIngressFifoSize;
} IFX_TAPI_KPI_GRP_CFG_t;

/* ========================================================================== */
/*                           Function prototypes                              */
/* ========================================================================== */

/** Sleep until data is available for reading with \ref IFX_TAPI_KPI_ReadData.

   \param  nKpiGroup    KPI group to wait on for new data.

   \return Returns value as follows:
   - IFX_SUCCESS:  Data is now available for reading in the specified
                        KPI group.
   - IFX_ERROR:    If wait was aborted or invalid parameters were given.
*/
extern IFX_return_t IFX_TAPI_KPI_WaitForData (IFX_TAPI_KPI_CH_t nKpiGroup);

/** Read packet from TAPI KPI.

   \param  nKpiGroup    KPI group where to read data from.
   \param  *nKpiChannel Returns the KPI channel number within the given
                        group where the packet was received.
   \param  **pPacket    Returns a pointer to a buffer-pool element with the
                        received data. The ownership of the returned buffer-pool
                        element is passed to the client calling this interface.
                        It is the responsibility of the client to free this
                        element by calling \ref IFX_TAPI_VoiceBufferPut after
                        having processed the data.
   \param  *nPacketLength  Returns the length of the received data. If the
                        returned length is 0, this means that no packets were
                        available for reading.
   \param  *nMore       Returns whether more packets are ready to be read
                        within the same KPI group. 0 means that no more packets
                        are ready, 1 means that more packets are available for
                        reading.

   \return
   Returns the number of data bytes successfully read, otherwise IFX_ERROR.
*/
extern IFX_int32_t  IFX_TAPI_KPI_ReadData (IFX_TAPI_KPI_CH_t nKpiGroup,
                                           IFX_TAPI_KPI_CH_t *nKpiChannel,
                                           void **pPacket,
                                           IFX_uint32_t *nPacketLength,
                                           IFX_uint8_t *nMore);

/** Write packet from KPI client to TAPI KPI.

   \param  nKpiChannel  KPI channel the data is written to.
   \param  pPacket      Pointer to a buffer-pool element with the data to be
                        written. The buffer-pool element must be from the TAPI
                        voice buffer pool. Use \ref IFX_TAPI_VoiceBufferGet
                        to get a buffer-pool element.
   \param  nPacketLength  Length of the data to be written in bytes.

   \return
   On success, the number of bytes written is returned (zero indicates
   nothing was written). On error, IFX_ERROR is returned.

   \remarks
   The ownership of the buffer-pool element is only passed to the KPI if this
   call successfuly writes all data. This is only the case if this function
   returns the same value as given in the parameter nPacketLength. When this
   write fails, or less data than given was written, the buffer still
   belongs to the caller, who has to discard it or write it again.
*/
extern IFX_int32_t  IFX_TAPI_KPI_WriteData (IFX_TAPI_KPI_CH_t nKpiChannel,
                                            void *pPacket,
                                            IFX_uint32_t nPacketLength);

/** Report an event from KPI client to TAPI.

   \param  nKpiChannel  KPI channel the data is written to.
   \param  pTapiEvent   Pointer to TAPI event to report.

   \remarks
   The function will overwrite the TAPI channel in the given event with the
   TAPI channel that is associated with the given KPI channel.
*/
extern IFX_void_t   IFX_TAPI_KPI_ReportEvent (IFX_TAPI_KPI_CH_t nKpiChannel,
                                              IFX_TAPI_EVENT_t *pTapiEvent);

/**
   Retrieve a voice packet buffer.

   \return
      - Pointer to a packet buffer on success or
      - IFX_NULL in case of an error.

   \remarks
      Use this to get a buffer for sending with \ref IFX_TAPI_KPI_WriteData.
   \remarks C++ does not allow a typecast to void as parameter. Type void must
   be used instead.
*/
extern IFX_void_t*  IFX_TAPI_VoiceBufferGet (void);

/**
   Discard a voice packet buffer.

   \param  pData  Pointer to a buffer that was retrieved through a call of
                  \ref IFX_TAPI_VoiceBufferGet.
   \return IFX_SUCCESS or IFX_ERROR

   \remarks
      Use this to discard a buffer that was received with
      \ref IFX_TAPI_KPI_ReadData.
*/
extern IFX_int32_t  IFX_TAPI_VoiceBufferPut (IFX_void_t *pData);

/**
   Retrieve a buffer for a voice packet and set the ID of the caller.

   \param  ownerId      ID value provided by the caller.

   \return
   Returns IFX_NULL in case of an error, otherwise returns packet buffer.

   \remarks
   This function uses a global IRQ lock - multiple drivers may be loaded and
   all may try to retrieve buffers from this shared pool in an IRQ context.
   Therefore, the interrupt is locked during access to the shared buffer pool.
*/
extern IFX_void_t*  IFX_TAPI_VoiceBufferGetWithOwnerId (IFX_uint32_t ownerId);

#ifdef TAPI_PACKET_OWNID
/**
   Update owner ID for voice packet buffer.

   \param  pData     Pointer to a buffer that was retrieved through a call of
                     \ref IFX_TAPI_VoiceBufferGet.
   \param  ownerId   ID value provided by the caller.

   \return IFX_SUCCESS or IFX_ERROR

   \remarks
   This function uses a global irq lock - multiple drivers may be loaded and
   all may try to retrieve buffers from this shared pool in an IRQ context.
   Therefore, the interrupt is locked during access to the shared buffer pool.
*/
extern IFX_int32_t  IFX_TAPI_VoiceBufferChOwn (IFX_void_t *pb,
                                               IFX_uint32_t ownerID);
#endif /* TAPI_PACKET_OWNID */

/** Optionally: the KPI client might register a pointer to
                an egress tasklet (Linux) structure to its group
   \param nKpiGroup        KPI group to register the tasklet to
   \param pEgressTasklet   Void pointer to a (Linux) tasklet_struct

   \return IFX_SUCCESS or IFX_ERROR in case the KPI group cannot
                          be used/initialized
*/
extern IFX_return_t IFX_TAPI_KPI_EgressTaskletRegister (
                                                IFX_TAPI_KPI_CH_t nKpiGroup,
                                                IFX_void_t *pEgressTasklet );

/**
   Frees all buffers in the pool that are allocated and have the given ID.

   \param  ownerId      ID value provided by the caller.

   \return IFX_SUCCESS or IFX_ERROR

   \remarks
   This function uses a global IRQ lock - multiple drivers may be loaded and
   all may try to retrieve buffers from this shared pool in an IRQ context.
   Therefore, the interrupt is locked during access to the shared buffer pool.
*/
extern IFX_int32_t   IFX_TAPI_VoiceBufferFreeAllOwnerId (IFX_uint32_t ownerId);

/*@}*/ /* TAPI_INTERFACE_KPI */
#endif /* _DRV_TAPI_KPI_IO_H */