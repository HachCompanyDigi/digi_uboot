/*
 * Copyright (C) 2012-2015 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * SPDX-License-Identifier:    GPL-2.0+
 *
*/

#ifndef __SECURE_MX6Q_H__
#define __SECURE_MX6Q_H__

#include <linux/types.h>
#include <common.h>
#include <asm/arch/sys_proto.h>

/* -------- start of HAB API updates ------------*/

#define hab_rvt_report_event_p					\
(								\
	((is_cpu_type(MXC_CPU_MX6Q) ||				\
	  is_cpu_type(MXC_CPU_MX6D)) &&				\
	  (soc_rev() >= CHIP_REV_1_5)) ?			\
	((hab_rvt_report_event_t *)HAB_RVT_REPORT_EVENT_NEW) :	\
	((is_cpu_type(MXC_CPU_MX6DL) ||				\
	  is_cpu_type(MXC_CPU_MX6SOLO)) &&			\
	 (soc_rev() >= CHIP_REV_1_2)) ?				\
	((hab_rvt_report_event_t *)HAB_RVT_REPORT_EVENT_NEW) :	\
	((hab_rvt_report_event_t *)HAB_RVT_REPORT_EVENT)	\
)

#define hab_rvt_report_status_p					\
(								\
	((is_cpu_type(MXC_CPU_MX6Q) ||				\
	  is_cpu_type(MXC_CPU_MX6D)) &&				\
	  (soc_rev() >= CHIP_REV_1_5)) ?			\
	((hab_rvt_report_status_t *)HAB_RVT_REPORT_STATUS_NEW) :\
	((is_cpu_type(MXC_CPU_MX6DL) ||				\
	  is_cpu_type(MXC_CPU_MX6SOLO)) &&			\
	 (soc_rev() >= CHIP_REV_1_2)) ?				\
	((hab_rvt_report_status_t *)HAB_RVT_REPORT_STATUS_NEW) :\
	((hab_rvt_report_status_t *)HAB_RVT_REPORT_STATUS)	\
)

#define hab_rvt_authenticate_image_p				\
(								\
	((is_cpu_type(MXC_CPU_MX6Q) ||				\
	  is_cpu_type(MXC_CPU_MX6D)) &&				\
	  (soc_rev() >= CHIP_REV_1_5)) ?			\
	((hab_rvt_authenticate_image_t *)HAB_RVT_AUTHENTICATE_IMAGE_NEW) : \
	((is_cpu_type(MXC_CPU_MX6DL) ||				\
	  is_cpu_type(MXC_CPU_MX6SOLO)) &&			\
	 (soc_rev() >= CHIP_REV_1_2)) ?				\
	((hab_rvt_authenticate_image_t *)HAB_RVT_AUTHENTICATE_IMAGE_NEW) : \
	((hab_rvt_authenticate_image_t *)HAB_RVT_AUTHENTICATE_IMAGE)	\
)

#define hab_rvt_entry_p						\
(								\
	((is_cpu_type(MXC_CPU_MX6Q) ||				\
	  is_cpu_type(MXC_CPU_MX6D)) &&				\
	  (soc_rev() >= CHIP_REV_1_5)) ?			\
	((hab_rvt_entry_t *)HAB_RVT_ENTRY_NEW) :		\
	((is_cpu_type(MXC_CPU_MX6DL) ||				\
	 is_cpu_type(MXC_CPU_MX6SOLO)) &&			\
	 (soc_rev() >= CHIP_REV_1_2)) ?				\
	((hab_rvt_entry_t *)HAB_RVT_ENTRY_NEW) :		\
	((hab_rvt_entry_t *)HAB_RVT_ENTRY)			\
)

#define hab_rvt_exit_p						\
(								\
	((is_cpu_type(MXC_CPU_MX6Q) ||				\
	  is_cpu_type(MXC_CPU_MX6D)) &&				\
	  (soc_rev() >= CHIP_REV_1_5)) ?			\
	((hab_rvt_exit_t *)HAB_RVT_EXIT_NEW) :			\
	((is_cpu_type(MXC_CPU_MX6DL) ||				\
	 is_cpu_type(MXC_CPU_MX6SOLO)) &&			\
	 (soc_rev() >= CHIP_REV_1_2)) ?				\
	((hab_rvt_exit_t *)HAB_RVT_EXIT_NEW) :			\
	((hab_rvt_exit_t *)HAB_RVT_EXIT)			\
)

/* The following are taken from HAB4 SIS */

/* Status definitions */
enum hab_status {
	HAB_STS_ANY = 0x00,
	HAB_FAILURE = 0x33,
	HAB_WARNING = 0x69,
	HAB_SUCCESS = 0xf0
};

/* Security Configuration definitions */
enum hab_config {
	HAB_CFG_RETURN = 0x33, /**< Field Return IC */
	HAB_CFG_OPEN = 0xf0, /**< Non-secure IC */
	HAB_CFG_CLOSED = 0xcc /**< Secure IC */
};

/* State definitions */
enum hab_state {
	HAB_STATE_INITIAL = 0x33, /**< Initialising state (transitory) */
	HAB_STATE_CHECK = 0x55, /**< Check state (non-secure) */
	HAB_STATE_NONSECURE = 0x66, /**< Non-secure state */
	HAB_STATE_TRUSTED = 0x99, /**< Trusted state */
	HAB_STATE_SECURE = 0xaa, /**< Secure state */
	HAB_STATE_FAIL_SOFT = 0xcc, /**< Soft fail state */
	HAB_STATE_FAIL_HARD = 0xff, /**< Hard fail state (terminal) */
	HAB_STATE_NONE = 0xf0, /**< No security state machine */
	HAB_STATE_MAX
};

/*Function prototype description*/
typedef enum hab_status hab_rvt_report_event_t(enum hab_status, uint32_t,
		uint8_t* , size_t*);
typedef enum hab_status hab_rvt_report_status_t(enum hab_config *,
		enum hab_state *);
typedef enum hab_status hab_loader_callback_f_t(void**, size_t*, const void*);
typedef enum hab_status hab_rvt_entry_t(void);
typedef enum hab_status hab_rvt_exit_t(void);
typedef void *hab_rvt_authenticate_image_t(uint8_t, ptrdiff_t,
		void **, size_t *, hab_loader_callback_f_t);
typedef void hapi_clock_init_t(void);

#ifdef CONFIG_ROM_UNIFIED_SECTIONS
#define HAB_RVT_BASE			0x00000100
#else
#define HAB_RVT_BASE			0x00000094
#endif

#define HAB_RVT_ENTRY			(*(uint32_t *)(HAB_RVT_BASE + 0x04))
#define HAB_RVT_EXIT			(*(uint32_t *)(HAB_RVT_BASE + 0x08))
#define HAB_RVT_AUTHENTICATE_IMAGE	(*(uint32_t *)(HAB_RVT_BASE + 0x10))
#define HAB_RVT_REPORT_EVENT		(*(uint32_t *)(HAB_RVT_BASE + 0x20))
#define HAB_RVT_REPORT_STATUS		(*(uint32_t *)(HAB_RVT_BASE + 0x24))

#define HAB_RVT_REPORT_EVENT_NEW               (*(uint32_t *)0x000000B8)
#define HAB_RVT_REPORT_STATUS_NEW              (*(uint32_t *)0x000000BC)
#define HAB_RVT_AUTHENTICATE_IMAGE_NEW         (*(uint32_t *)0x000000A8)
#define HAB_RVT_ENTRY_NEW                      (*(uint32_t *)0x0000009C)
#define HAB_RVT_EXIT_NEW                       (*(uint32_t *)0x000000A0)

#define HAB_RVT_CLOCK_INIT ((hapi_clock_init_t *)0x0000024D)

#define HAB_CID_ROM 0 /**< ROM Caller ID */
#define HAB_CID_UBOOT 1 /**< UBOOT Caller ID*/
/* ----------- end of HAB API updates ------------*/

/*
 * Check if the device is closed.
 * @return: 1 if the device is closed, 0 otherwise.
 */
bool is_hab_enabled(void);

/*
 * Authenticate and decrypt binary.
 * @ddr_start: memory address of the binary to be authenticated
 * @image_size: binary size, excluding CSF block.
 * @return: 1 if the authentication was successful.
 *
 * Note: the IVT must be attached at the end of the image and padded
 *       to 0x1000. The CSF block must be attached after the IVT.
 * Note: On open devices, this method always returns 1.
 */
uint32_t authenticate_image(uint32_t ddr_start, uint32_t image_size);

#endif
