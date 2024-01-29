#include <zephyr.h>

void zephyr_bluetooth_thread_entry(void *parameter)
{
    extern void demo_central(void);
    demo_central();

    k_thread_abort(NULL);
}

k_thread_stack_t ble_demo_stack[2048];

int bluetooth_demo_init(int argc, char **argv)
{
    extern void zephyr_init(void);
    zephyr_init();

    k_thread_create("bledemo", ble_demo_stack, sizeof(ble_demo_stack), zephyr_bluetooth_thread_entry, NULL, 10);

    return 0;
}
