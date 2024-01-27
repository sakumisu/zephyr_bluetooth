add_library(zephyr_bluetooth STATIC)

target_include_directories(zephyr_bluetooth PUBLIC
core/include 
core/src 
core/src/tinycrypt/include
osal/freertos 
drivers
.
)

target_sources(zephyr_bluetooth PRIVATE
osal/freertos/k_os.c
osal/freertos/k_queue.c
osal/freertos/k_work_q.c
osal/freertos/k_mem_slab.c
osal/freertos/k_poll.c
)

target_sources(zephyr_bluetooth PRIVATE
core/src/tinycrypt/source/utils.c
core/src/tinycrypt/source/ecc_dh.c
core/src/tinycrypt/source/ecc.c
core/src/tinycrypt/source/ecc_dsa.c
core/src/tinycrypt/source/aes_decrypt.c
core/src/tinycrypt/source/aes_encrypt.c
core/src/tinycrypt/source/cbc_mode.c
core/src/tinycrypt/source/ctr_mode.c
core/src/tinycrypt/source/ccm_mode.c
core/src/tinycrypt/source/cmac_mode.c
core/src/tinycrypt/source/sha256.c
core/src/tinycrypt/source/hmac.c
core/src/tinycrypt/source/hmac_prng.c
core/src/tinycrypt/source/ctr_prng.c
)

target_sources(zephyr_bluetooth PRIVATE
core/src/utils/buf.c
core/src/utils/atomic_c.c
)

target_sources(zephyr_bluetooth PRIVATE
core/src/common/log.c
# core/src/common/dummy.c
)

target_sources(zephyr_bluetooth PRIVATE
core/src/host/crypto.c
)

target_sources(zephyr_bluetooth PRIVATE
core/src/host/uuid.c
core/src/host/addr.c
core/src/host/buf.c
core/src/host/hci_core.c
core/src/host/hci_common.c
core/src/host/id.c
)

target_sources(zephyr_bluetooth PRIVATE
core/src/host/adv.c
)

target_sources(zephyr_bluetooth PRIVATE
core/src/host/scan.c
)

target_sources(zephyr_bluetooth PRIVATE
core/src/host/conn.c
core/src/host/l2cap.c
core/src/host/att.c
core/src/host/gatt.c
)

target_sources(zephyr_bluetooth PRIVATE
core/src/host/smp_null.c
)

target_sources(zephyr_bluetooth PRIVATE zephyr_init.c)
