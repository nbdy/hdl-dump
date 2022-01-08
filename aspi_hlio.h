/*
 * aspi_hlio.h - ASPI high-level I/O
 * $Id: aspi_hlio.h,v 1.7 2006/09/01 17:32:42 bobi Exp $
 *
 * Copyright 2004 Bobi B., w1zard0f07@yahoo.com
 *
 * This file is part of hdl_dump.
 *
 * hdl_dump is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * hdl_dump is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with hdl_dump; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#if !defined(_ASPI_HLIO_H)
#define _ASPI_HLIO_H

#include "config.h"
#include "wnaspi32.h"
#include <stddef.h>
#include <windows.h>

C_START

typedef struct scsi_device_type scsi_device_t;
typedef struct scsi_devices_list_type scsi_devices_list_t;

struct scsi_device_type {
  int host, scsi_id, lun;
  int type; /* 0: probably a HDD; 5: MMC device (CD- or DVD-drive) */
  u_int32_t align;
  char name[28 + 1];
  u_int32_t sector_size, size_in_sectors;
  unsigned long status;
};

struct scsi_devices_list_type {
  u_int32_t used, alloc;
  scsi_device_t* device;
};

int aspi_load(void);
int aspi_unload(void);

int aspi_scan_scsi_bus(scsi_devices_list_t** list);
void aspi_dlist_free(scsi_devices_list_t* list);

SRB_ExecSCSICmd* aspi_prepare_stat(int host,
                                   int scsi_id,
                                   int lun,
                                   /*@out@*/ u_int8_t buf[8],
                                   /*@returned@*/ /*@out@*/ SRB_ExecSCSICmd* cmd);

int aspi_stat(int host,
              int scsi_id,
              int lun,
              u_int32_t* sector_size,
              u_int32_t* size_in_sectors);

int aspi_mmc_read_cd(int host,
                     int scsi_id,
                     int lun,
                     u_int32_t start_sector,
                     u_int32_t num_sectors,
                     u_int32_t sector_size,
                     void* output);

SRB_ExecSCSICmd* aspi_prepare_read_10(int host,
                                      int scsi_id,
                                      int lun,
                                      u_int32_t start_sector,
                                      u_int32_t num_sectors,
                                      /*@out@*/ void* output,
                                      /*@returned@*/ /*@out@*/ SRB_ExecSCSICmd* cmd);

int aspi_read_10(int host,
                 int scsi_id,
                 int lun,
                 u_int32_t start_sector,
                 u_int32_t num_sectors,
                 void* output);

/* pointer should be passed to aspi_dispose_error_msg when no longer needed */
unsigned long aspi_get_last_error_code(void);
const char* aspi_get_last_error_msg(void);
const char* aspi_get_error_msg(unsigned long aspi_error_code);
void aspi_dispose_error_msg(char* msg);

C_END

#endif /* _ASPI_HLIO_H defined? */
