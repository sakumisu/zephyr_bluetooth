#ifndef K_QUEUE_H_
#define K_QUEUE_H_

/**
 * @cond INTERNAL_HIDDEN
 */

struct k_queue {
	struct k_sem sem;
	sys_slist_t data_q;
	sys_dlist_t poll_events;
};

#define Z_QUEUE_INITIALIZER(obj) { .sem = { .name = #obj } }

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @defgroup queue_apis Queue APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * @brief Initialize a queue.
 *
 * This routine initializes a queue object, prior to its first use.
 *
 * @param queue Address of the queue.
 *
 * @return N/A
 */
void k_queue_init(struct k_queue *queue);

/**
 * @brief Cancel waiting on a queue.
 *
 * This routine causes first thread pending on @a queue, if any, to
 * return from k_queue_get() call with NULL value (as if timeout expired).
 * If the queue is being waited on by k_poll(), it will return with
 * -EINTR and K_POLL_STATE_CANCELLED state (and per above, subsequent
 * k_queue_get() will return NULL).
 *
 * @funcprops \isr_ok
 *
 * @param queue Address of the queue.
 *
 * @return N/A
 */
void k_queue_cancel_wait(struct k_queue *queue);

/**
 * @brief Append an element to the end of a queue.
 *
 * This routine appends a data item to @a queue. A queue data item must be
 * aligned on a word boundary, and the first word of the item is reserved
 * for the kernel's use.
 *
 * @funcprops \isr_ok
 *
 * @param queue Address of the queue.
 * @param data Address of the data item.
 *
 * @return N/A
 */
void k_queue_append(struct k_queue *queue, void *data);

/**
 * @brief Append an element to a queue.
 *
 * This routine appends a data item to @a queue. There is an implicit memory
 * allocation to create an additional temporary bookkeeping data structure from
 * the calling thread's resource pool, which is automatically freed when the
 * item is removed. The data itself is not copied.
 *
 * @funcprops \isr_ok
 *
 * @param queue Address of the queue.
 * @param data Address of the data item.
 *
 * @retval 0 on success
 * @retval -ENOMEM if there isn't sufficient RAM in the caller's resource pool
 */
int32_t k_queue_alloc_append(struct k_queue *queue, void *data);

/**
 * @brief Prepend an element to a queue.
 *
 * This routine prepends a data item to @a queue. A queue data item must be
 * aligned on a word boundary, and the first word of the item is reserved
 * for the kernel's use.
 *
 * @funcprops \isr_ok
 *
 * @param queue Address of the queue.
 * @param data Address of the data item.
 *
 * @return N/A
 */
void k_queue_prepend(struct k_queue *queue, void *data);

/**
 * @brief Prepend an element to a queue.
 *
 * This routine prepends a data item to @a queue. There is an implicit memory
 * allocation to create an additional temporary bookkeeping data structure from
 * the calling thread's resource pool, which is automatically freed when the
 * item is removed. The data itself is not copied.
 *
 * @funcprops \isr_ok
 *
 * @param queue Address of the queue.
 * @param data Address of the data item.
 *
 * @retval 0 on success
 * @retval -ENOMEM if there isn't sufficient RAM in the caller's resource pool
 */
int32_t k_queue_alloc_prepend(struct k_queue *queue, void *data);

/**
 * @brief Inserts an element to a queue.
 *
 * This routine inserts a data item to @a queue after previous item. A queue
 * data item must be aligned on a word boundary, and the first word of
 * the item is reserved for the kernel's use.
 *
 * @funcprops \isr_ok
 *
 * @param queue Address of the queue.
 * @param prev Address of the previous data item.
 * @param data Address of the data item.
 *
 * @return N/A
 */
void k_queue_insert(struct k_queue *queue, void *prev, void *data);

/**
 * @brief Atomically append a list of elements to a queue.
 *
 * This routine adds a list of data items to @a queue in one operation.
 * The data items must be in a singly-linked list, with the first word
 * in each data item pointing to the next data item; the list must be
 * NULL-terminated.
 *
 * @funcprops \isr_ok
 *
 * @param queue Address of the queue.
 * @param head Pointer to first node in singly-linked list.
 * @param tail Pointer to last node in singly-linked list.
 *
 * @retval 0 on success
 * @retval -EINVAL on invalid supplied data
 *
 */
int k_queue_append_list(struct k_queue *queue, void *head, void *tail);

/**
 * @brief Atomically add a list of elements to a queue.
 *
 * This routine adds a list of data items to @a queue in one operation.
 * The data items must be in a singly-linked list implemented using a
 * sys_slist_t object. Upon completion, the original list is empty.
 *
 * @funcprops \isr_ok
 *
 * @param queue Address of the queue.
 * @param list Pointer to sys_slist_t object.
 *
 * @retval 0 on success
 * @retval -EINVAL on invalid data
 */
int k_queue_merge_slist(struct k_queue *queue, sys_slist_t *list);

/**
 * @brief Get an element from a queue.
 *
 * This routine removes first data item from @a queue. The first word of the
 * data item is reserved for the kernel's use.
 *
 * @note @a timeout must be set to K_NO_WAIT if called from ISR.
 *
 * @funcprops \isr_ok
 *
 * @param queue Address of the queue.
 * @param timeout Non-negative waiting period to obtain a data item
 *                or one of the special values K_NO_WAIT and
 *                K_FOREVER.
 *
 * @return Address of the data item if successful; NULL if returned
 * without waiting, or waiting period timed out.
 */
void *k_queue_get(struct k_queue *queue, k_timeout_t timeout);

/**
 * @brief Remove an element from a queue.
 *
 * This routine removes data item from @a queue. The first word of the
 * data item is reserved for the kernel's use. Removing elements from k_queue
 * rely on sys_slist_find_and_remove which is not a constant time operation.
 *
 * @note @a timeout must be set to K_NO_WAIT if called from ISR.
 *
 * @funcprops \isr_ok
 *
 * @param queue Address of the queue.
 * @param data Address of the data item.
 *
 * @return true if data item was removed
 */
bool k_queue_remove(struct k_queue *queue, void *data);

/**
 * @brief Append an element to a queue only if it's not present already.
 *
 * This routine appends data item to @a queue. The first word of the data
 * item is reserved for the kernel's use. Appending elements to k_queue
 * relies on sys_slist_is_node_in_list which is not a constant time operation.
 *
 * @funcprops \isr_ok
 *
 * @param queue Address of the queue.
 * @param data Address of the data item.
 *
 * @return true if data item was added, false if not
 */
bool k_queue_unique_append(struct k_queue *queue, void *data);

/**
 * @brief Query a queue to see if it has data available.
 *
 * Note that the data might be already gone by the time this function returns
 * if other threads are also trying to read from the queue.
 *
 * @funcprops \isr_ok
 *
 * @param queue Address of the queue.
 *
 * @return Non-zero if the queue is empty.
 * @return 0 if data is available.
 */
int k_queue_is_empty(struct k_queue *queue);

/**
 * @brief Peek element at the head of queue.
 *
 * Return element from the head of queue without removing it.
 *
 * @param queue Address of the queue.
 *
 * @return Head element, or NULL if queue is empty.
 */
void *k_queue_peek_head(struct k_queue *queue);

/**
 * @brief Peek element at the tail of queue.
 *
 * Return element from the tail of queue without removing it.
 *
 * @param queue Address of the queue.
 *
 * @return Tail element, or NULL if queue is empty.
 */
void *k_queue_peek_tail(struct k_queue *queue);

/**
 * @brief Statically define and initialize a queue.
 *
 * The queue can be accessed outside the module where it is defined using:
 *
 * @code struct k_queue <name>; @endcode
 *
 * @param name Name of the queue.
 */
#define K_QUEUE_DEFINE(name) \
	STRUCT_SECTION_ITERABLE(k_queue, name) = \
		Z_QUEUE_INITIALIZER(name)

/** @} */

struct k_fifo {
	struct k_queue _queue;
};

/**
 * @cond INTERNAL_HIDDEN
 */
#define Z_FIFO_INITIALIZER(obj) \
	{ \
	._queue = Z_QUEUE_INITIALIZER(obj._queue) \
	}

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @defgroup fifo_apis FIFO APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * @brief Initialize a FIFO queue.
 *
 * This routine initializes a FIFO queue, prior to its first use.
 *
 * @param fifo Address of the FIFO queue.
 *
 * @return N/A
 */
#define k_fifo_init(fifo) \
	({ \
	SYS_PORT_TRACING_OBJ_FUNC_ENTER(k_fifo, init, fifo); \
	(fifo)->_queue.sem.name = #fifo; \
	k_queue_init(&(fifo)->_queue); \
	SYS_PORT_TRACING_OBJ_FUNC_EXIT(k_fifo, init, fifo); \
	})

/**
 * @brief Cancel waiting on a FIFO queue.
 *
 * This routine causes first thread pending on @a fifo, if any, to
 * return from k_fifo_get() call with NULL value (as if timeout
 * expired).
 *
 * @funcprops \isr_ok
 *
 * @param fifo Address of the FIFO queue.
 *
 * @return N/A
 */
#define k_fifo_cancel_wait(fifo) \
	({ \
	SYS_PORT_TRACING_OBJ_FUNC_ENTER(k_fifo, cancel_wait, fifo); \
	k_queue_cancel_wait(&(fifo)->_queue); \
	SYS_PORT_TRACING_OBJ_FUNC_EXIT(k_fifo, cancel_wait, fifo); \
	})

/**
 * @brief Add an element to a FIFO queue.
 *
 * This routine adds a data item to @a fifo. A FIFO data item must be
 * aligned on a word boundary, and the first word of the item is reserved
 * for the kernel's use.
 *
 * @funcprops \isr_ok
 *
 * @param fifo Address of the FIFO.
 * @param data Address of the data item.
 *
 * @return N/A
 */
#define k_fifo_put(fifo, data) \
	({ \
	SYS_PORT_TRACING_OBJ_FUNC_ENTER(k_fifo, put, fifo, data); \
	k_queue_append(&(fifo)->_queue, data); \
	SYS_PORT_TRACING_OBJ_FUNC_EXIT(k_fifo, put, fifo, data); \
	})

/**
 * @brief Add an element to a FIFO queue.
 *
 * This routine adds a data item to @a fifo. There is an implicit memory
 * allocation to create an additional temporary bookkeeping data structure from
 * the calling thread's resource pool, which is automatically freed when the
 * item is removed. The data itself is not copied.
 *
 * @funcprops \isr_ok
 *
 * @param fifo Address of the FIFO.
 * @param data Address of the data item.
 *
 * @retval 0 on success
 * @retval -ENOMEM if there isn't sufficient RAM in the caller's resource pool
 */
#define k_fifo_alloc_put(fifo, data) \
	({ \
	SYS_PORT_TRACING_OBJ_FUNC_ENTER(k_fifo, alloc_put, fifo, data); \
	int ret = k_queue_alloc_append(&(fifo)->_queue, data); \
	SYS_PORT_TRACING_OBJ_FUNC_EXIT(k_fifo, alloc_put, fifo, data, ret); \
	ret; \
	})

/**
 * @brief Atomically add a list of elements to a FIFO.
 *
 * This routine adds a list of data items to @a fifo in one operation.
 * The data items must be in a singly-linked list, with the first word of
 * each data item pointing to the next data item; the list must be
 * NULL-terminated.
 *
 * @funcprops \isr_ok
 *
 * @param fifo Address of the FIFO queue.
 * @param head Pointer to first node in singly-linked list.
 * @param tail Pointer to last node in singly-linked list.
 *
 * @return N/A
 */
#define k_fifo_put_list(fifo, head, tail) \
	({ \
	SYS_PORT_TRACING_OBJ_FUNC_ENTER(k_fifo, put_list, fifo, head, tail); \
	k_queue_append_list(&(fifo)->_queue, head, tail); \
	SYS_PORT_TRACING_OBJ_FUNC_EXIT(k_fifo, put_list, fifo, head, tail); \
	})

/**
 * @brief Atomically add a list of elements to a FIFO queue.
 *
 * This routine adds a list of data items to @a fifo in one operation.
 * The data items must be in a singly-linked list implemented using a
 * sys_slist_t object. Upon completion, the sys_slist_t object is invalid
 * and must be re-initialized via sys_slist_init().
 *
 * @funcprops \isr_ok
 *
 * @param fifo Address of the FIFO queue.
 * @param list Pointer to sys_slist_t object.
 *
 * @return N/A
 */
#define k_fifo_put_slist(fifo, list) \
	({ \
	SYS_PORT_TRACING_OBJ_FUNC_ENTER(k_fifo, put_slist, fifo, list); \
	k_queue_merge_slist(&(fifo)->_queue, list); \
	SYS_PORT_TRACING_OBJ_FUNC_EXIT(k_fifo, put_slist, fifo, list); \
	})

/**
 * @brief Get an element from a FIFO queue.
 *
 * This routine removes a data item from @a fifo in a "first in, first out"
 * manner. The first word of the data item is reserved for the kernel's use.
 *
 * @note @a timeout must be set to K_NO_WAIT if called from ISR.
 *
 * @funcprops \isr_ok
 *
 * @param fifo Address of the FIFO queue.
 * @param timeout Waiting period to obtain a data item,
 *                or one of the special values K_NO_WAIT and K_FOREVER.
 *
 * @return Address of the data item if successful; NULL if returned
 * without waiting, or waiting period timed out.
 */
#define k_fifo_get(fifo, timeout) \
	({ \
	SYS_PORT_TRACING_OBJ_FUNC_ENTER(k_fifo, get, fifo, timeout); \
	void *ret = k_queue_get(&(fifo)->_queue, timeout); \
	SYS_PORT_TRACING_OBJ_FUNC_EXIT(k_fifo, get, fifo, timeout, ret); \
	ret; \
	})

/**
 * @brief Query a FIFO queue to see if it has data available.
 *
 * Note that the data might be already gone by the time this function returns
 * if other threads is also trying to read from the FIFO.
 *
 * @funcprops \isr_ok
 *
 * @param fifo Address of the FIFO queue.
 *
 * @return Non-zero if the FIFO queue is empty.
 * @return 0 if data is available.
 */
#define k_fifo_is_empty(fifo) \
	k_queue_is_empty(&(fifo)->_queue)

/**
 * @brief Peek element at the head of a FIFO queue.
 *
 * Return element from the head of FIFO queue without removing it. A usecase
 * for this is if elements of the FIFO object are themselves containers. Then
 * on each iteration of processing, a head container will be peeked,
 * and some data processed out of it, and only if the container is empty,
 * it will be completely remove from the FIFO queue.
 *
 * @param fifo Address of the FIFO queue.
 *
 * @return Head element, or NULL if the FIFO queue is empty.
 */
#define k_fifo_peek_head(fifo) \
	({ \
	SYS_PORT_TRACING_OBJ_FUNC_ENTER(k_fifo, peek_head, fifo); \
	void *ret = k_queue_peek_head(&(fifo)->_queue); \
	SYS_PORT_TRACING_OBJ_FUNC_EXIT(k_fifo, peek_head, fifo, ret); \
	ret; \
	})

/**
 * @brief Peek element at the tail of FIFO queue.
 *
 * Return element from the tail of FIFO queue (without removing it). A usecase
 * for this is if elements of the FIFO queue are themselves containers. Then
 * it may be useful to add more data to the last container in a FIFO queue.
 *
 * @param fifo Address of the FIFO queue.
 *
 * @return Tail element, or NULL if a FIFO queue is empty.
 */
#define k_fifo_peek_tail(fifo) \
	({ \
	SYS_PORT_TRACING_OBJ_FUNC_ENTER(k_fifo, peek_tail, fifo); \
	void *ret = k_queue_peek_tail(&(fifo)->_queue); \
	SYS_PORT_TRACING_OBJ_FUNC_EXIT(k_fifo, peek_tail, fifo, ret); \
	ret; \
	})

/**
 * @brief Statically define and initialize a FIFO queue.
 *
 * The FIFO queue can be accessed outside the module where it is defined using:
 *
 * @code struct k_fifo <name>; @endcode
 *
 * @param name Name of the FIFO queue.
 */
#define K_FIFO_DEFINE(name) \
	STRUCT_SECTION_ITERABLE_ALTERNATE(k_queue, k_fifo, name) = \
		Z_FIFO_INITIALIZER(name)

/** @} */

struct k_lifo {
	struct k_queue _queue;
};

/**
 * @cond INTERNAL_HIDDEN
 */

#define Z_LIFO_INITIALIZER(obj) \
	{ \
	._queue = Z_QUEUE_INITIALIZER(obj._queue) \
	}

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @defgroup lifo_apis LIFO APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * @brief Initialize a LIFO queue.
 *
 * This routine initializes a LIFO queue object, prior to its first use.
 *
 * @param lifo Address of the LIFO queue.
 *
 * @return N/A
 */
#define k_lifo_init(lifo) \
	({ \
	SYS_PORT_TRACING_OBJ_FUNC_ENTER(k_lifo, init, lifo); \
	k_queue_init(&(lifo)->_queue); \
	SYS_PORT_TRACING_OBJ_FUNC_EXIT(k_lifo, init, lifo); \
	})

/**
 * @brief Add an element to a LIFO queue.
 *
 * This routine adds a data item to @a lifo. A LIFO queue data item must be
 * aligned on a word boundary, and the first word of the item is
 * reserved for the kernel's use.
 *
 * @funcprops \isr_ok
 *
 * @param lifo Address of the LIFO queue.
 * @param data Address of the data item.
 *
 * @return N/A
 */
#define k_lifo_put(lifo, data) \
	({ \
	SYS_PORT_TRACING_OBJ_FUNC_ENTER(k_lifo, put, lifo, data); \
	k_queue_prepend(&(lifo)->_queue, data); \
	SYS_PORT_TRACING_OBJ_FUNC_EXIT(k_lifo, put, lifo, data); \
	})

/**
 * @brief Add an element to a LIFO queue.
 *
 * This routine adds a data item to @a lifo. There is an implicit memory
 * allocation to create an additional temporary bookkeeping data structure from
 * the calling thread's resource pool, which is automatically freed when the
 * item is removed. The data itself is not copied.
 *
 * @funcprops \isr_ok
 *
 * @param lifo Address of the LIFO.
 * @param data Address of the data item.
 *
 * @retval 0 on success
 * @retval -ENOMEM if there isn't sufficient RAM in the caller's resource pool
 */
#define k_lifo_alloc_put(lifo, data) \
	({ \
	SYS_PORT_TRACING_OBJ_FUNC_ENTER(k_lifo, alloc_put, lifo, data); \
	int ret = k_queue_alloc_prepend(&(lifo)->_queue, data); \
	SYS_PORT_TRACING_OBJ_FUNC_EXIT(k_lifo, alloc_put, lifo, data, ret); \
	ret; \
	})

/**
 * @brief Get an element from a LIFO queue.
 *
 * This routine removes a data item from @a LIFO in a "last in, first out"
 * manner. The first word of the data item is reserved for the kernel's use.
 *
 * @note @a timeout must be set to K_NO_WAIT if called from ISR.
 *
 * @funcprops \isr_ok
 *
 * @param lifo Address of the LIFO queue.
 * @param timeout Waiting period to obtain a data item,
 *                or one of the special values K_NO_WAIT and K_FOREVER.
 *
 * @return Address of the data item if successful; NULL if returned
 * without waiting, or waiting period timed out.
 */
#define k_lifo_get(lifo, timeout) \
	({ \
	SYS_PORT_TRACING_OBJ_FUNC_ENTER(k_lifo, get, lifo, timeout); \
	void *ret = k_queue_get(&(lifo)->_queue, timeout); \
	SYS_PORT_TRACING_OBJ_FUNC_EXIT(k_lifo, get, lifo, timeout, ret); \
	ret; \
	})

/**
 * @brief Statically define and initialize a LIFO queue.
 *
 * The LIFO queue can be accessed outside the module where it is defined using:
 *
 * @code struct k_lifo <name>; @endcode
 *
 * @param name Name of the fifo.
 */
#define K_LIFO_DEFINE(name) \
	STRUCT_SECTION_ITERABLE_ALTERNATE(k_queue, k_lifo, name) = \
		Z_LIFO_INITIALIZER(name)

/** @} */

#endif