# 
# Copyright (c) 2024, sakumisu
#  
# SPDX-License-Identifier: Apache-2.0
#  

set(CONFIG_BT_BROADCASTER 1)
set(CONFIG_BT_OBSERVER 1)
set(CONFIG_BT_HOST_CRYPTO 1)
set(CONFIG_BT_CONN 1)
set(CONFIG_BT_ECC 1)
set(CONFIG_BT_SMP 1)
set(CONFIG_BT_HOST_CCM 1)
set(CONFIG_BT_RPA 1)

# set(CONFIG_BT_BREDR 1)
# set(CONFIG_BT_RFCOMM 1)
# set(CONFIG_BT_HFP_HF 1)

set(CONFIG_BT_DIS 1)
set(CONFIG_BT_BAS 1)
set(CONFIG_BT_HRS 1)
set(CONFIG_BT_TPS 1)
# set(CONFIG_BT_OTS 1)

list(APPEND zephyr_bluetooth_incs
${CMAKE_CURRENT_LIST_DIR}/core/include 
${CMAKE_CURRENT_LIST_DIR}/core/src 
${CMAKE_CURRENT_LIST_DIR}/core/src/tinycrypt/include
${CMAKE_CURRENT_LIST_DIR}/osal/freertos 
${CMAKE_CURRENT_LIST_DIR}/drivers
${CMAKE_CURRENT_LIST_DIR}/.
)

list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/osal/freertos/k_os.c
${CMAKE_CURRENT_LIST_DIR}/osal/freertos/k_queue.c
${CMAKE_CURRENT_LIST_DIR}/osal/freertos/k_work_q.c
${CMAKE_CURRENT_LIST_DIR}/osal/freertos/k_mem_slab.c
${CMAKE_CURRENT_LIST_DIR}/osal/freertos/k_poll.c
)

# tinycrypt, including all sources
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/tinycrypt/source/aes_decrypt.c
${CMAKE_CURRENT_LIST_DIR}/core/src/tinycrypt/source/aes_encrypt.c
${CMAKE_CURRENT_LIST_DIR}/core/src/tinycrypt/source/cbc_mode.c
${CMAKE_CURRENT_LIST_DIR}/core/src/tinycrypt/source/ctr_mode.c
${CMAKE_CURRENT_LIST_DIR}/core/src/tinycrypt/source/ccm_mode.c
${CMAKE_CURRENT_LIST_DIR}/core/src/tinycrypt/source/cmac_mode.c
${CMAKE_CURRENT_LIST_DIR}/core/src/tinycrypt/source/ctr_prng.c
${CMAKE_CURRENT_LIST_DIR}/core/src/tinycrypt/source/ecc_dh.c
${CMAKE_CURRENT_LIST_DIR}/core/src/tinycrypt/source/ecc.c
${CMAKE_CURRENT_LIST_DIR}/core/src/tinycrypt/source/ecc_dsa.c
${CMAKE_CURRENT_LIST_DIR}/core/src/tinycrypt/source/hmac.c
${CMAKE_CURRENT_LIST_DIR}/core/src/tinycrypt/source/hmac_prng.c
${CMAKE_CURRENT_LIST_DIR}/core/src/tinycrypt/source/sha256.c
${CMAKE_CURRENT_LIST_DIR}/core/src/tinycrypt/source/utils.c
)

list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/utils/buf.c
${CMAKE_CURRENT_LIST_DIR}/core/src/utils/atomic_c.c
)

# common
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/common/log.c
# ${CMAKE_CURRENT_LIST_DIR}/core/src/common/dummy.c
)

if(CONFIG_BT_RPA)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/common/rpa.c
)
endif()

# host
if(CONFIG_BT_ECC)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/host/hci_ecc.c
)
endif()

if(CONFIG_BT_A2DP)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/host/a2dp.c
)
endif()

if(CONFIG_BT_AVDTP)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/host/avdtp.c
)
endif()

if(CONFIG_BT_RFCOMM)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/host/rfcomm.c
)
endif()

if(CONFIG_BT_SETTINGS)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/host/settings.c
)
endif()

if(CONFIG_BT_HOST_CCM)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/host/aes_ccm.c
)
endif()

if(CONFIG_BT_BREDR)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/host/br.c
${CMAKE_CURRENT_LIST_DIR}/core/src/host/keys_br.c
${CMAKE_CURRENT_LIST_DIR}/core/src/host/l2cap_br.c
${CMAKE_CURRENT_LIST_DIR}/core/src/host/sdp.c
${CMAKE_CURRENT_LIST_DIR}/core/src/host/ssp.c
)
endif()

if(CONFIG_BT_HFP_HF)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/host/hfp_hf.c
${CMAKE_CURRENT_LIST_DIR}/core/src/host/at.c
)
endif()

list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/host/uuid.c
${CMAKE_CURRENT_LIST_DIR}/core/src/host/addr.c
${CMAKE_CURRENT_LIST_DIR}/core/src/host/buf.c
${CMAKE_CURRENT_LIST_DIR}/core/src/host/hci_core.c
${CMAKE_CURRENT_LIST_DIR}/core/src/host/hci_common.c
${CMAKE_CURRENT_LIST_DIR}/core/src/host/id.c
)

if(CONFIG_BT_BROADCASTER)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/host/adv.c
)
endif()

if(CONFIG_BT_OBSERVER)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/host/scan.c
)
endif()

if(CONFIG_BT_HOST_CRYPTO)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/host/crypto.c
)
endif()

if(CONFIG_BT_ECC)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/host/ecc.c
)
endif()

if(CONFIG_BT_CONN)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/host/conn.c
${CMAKE_CURRENT_LIST_DIR}/core/src/host/l2cap.c
${CMAKE_CURRENT_LIST_DIR}/core/src/host/att.c
${CMAKE_CURRENT_LIST_DIR}/core/src/host/gatt.c
)
endif()

if(CONFIG_BT_SMP)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/host/smp.c
${CMAKE_CURRENT_LIST_DIR}/core/src/host/keys.c
)
else()
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/host/smp_null.c
)
endif()

if(CONFIG_BT_ISO)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/host/iso.c
${CMAKE_CURRENT_LIST_DIR}/core/src/host/conn.c
)
endif()

if(CONFIG_BT_DF)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/host/direction.c
)
endif()

if(CONFIG_BT_DIS)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/services/dis.c
)
endif()

if(CONFIG_BT_BAS)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/services/bas.c
)
endif()

if(CONFIG_BT_HRS)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/services/hrs.c
)
endif()

if(CONFIG_BT_TPS)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/services/tps.c
)
endif()

if(CONFIG_BT_OTS)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/services/ots/ots.c
${CMAKE_CURRENT_LIST_DIR}/core/src/services/ots/ots_l2cap.c
${CMAKE_CURRENT_LIST_DIR}/core/src/services/ots/ots_obj_manager.c
${CMAKE_CURRENT_LIST_DIR}/core/src/services/ots/ots_oacp.c
${CMAKE_CURRENT_LIST_DIR}/core/src/services/ots/ots_olcp.c
)
endif()

if(CONFIG_BT_OTS_DIR_LIST_OBJ)
list(APPEND zephyr_bluetooth_srcs
${CMAKE_CURRENT_LIST_DIR}/core/src/services/ots_dir_list.c
)
endif()

list(APPEND zephyr_bluetooth_srcs ${CMAKE_CURRENT_LIST_DIR}/zephyr_init.c ${CMAKE_CURRENT_LIST_DIR}/zephyr_demo_init.c)
