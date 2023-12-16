#ifndef _OS_KVS_H
#define _OS_KVS_H
#include <stdint.h>

/**
 * @brief Initialize the key-value store.
 * 
 * @return int 0 if initialization is successful, otherwise an error code.
 */
int kv_store_init(void);

/**
 * @brief Uninitialize the key-value store.
 * 
 * @return int 0 if initialization is successful, otherwise an error code.
 */
int kv_store_uninit(void);

/**
 * @brief Store a uint32_t value associated with a key.
 * 
 * @param key The key for the value.
 * @param value The uint32_t value to be stored.
 * @return int 0 if successful, otherwise an error code.
 */
int os_kv_put_uint32(char* key, uint32_t value);

/**
 * @brief Store a uint64_t value associated with a key.
 * 
 * @param key The key for the value.
 * @param value The uint64_t value to be stored.
 * @return int 0 if successful, otherwise an error code.
 */
int os_kv_put_uint64(char* key, uint64_t value);

/**
 * @brief Store a string value associated with a key.
 * 
 * @param key The key for the value.
 * @param value The string value to be stored.
 * @return int 0 if successful, otherwise an error code.
 */
int os_kv_put_string(char* key, char* value);

/**
 * @brief Get the uint32_t value associated with a key.
 * 
 * @param key The key to look up.
 * @param value Pointer to a uint32_t variable to store the retrieved value.
 * @return int 0 if successful, otherwise an error code.
 */
int os_kv_get_uint32(char* key, uint32_t* value);

/**
 * @brief Get the uint64_t value associated with a key.
 * 
 * @param key The key to look up.
 * @param value Pointer to a uint64_t variable to store the retrieved value.
 * @return int 0 if successful, otherwise an error code.
 */
int os_kv_get_uint64(char* key, uint64_t* value);

/**
 * @brief Get the string value associated with a key.
 * 
 * @param key The key to look up.
 * @return char* A pointer to the retrieved string value, or NULL if key not found.
 */
int os_kv_get_string(char* key, char* value, size_t *len);

/**
 * @brief Remove a key-value pair from the store.
 * 
 * @param key The key to be removed.
 * @return int 0 if successful, otherwise an error code.
 */
int os_kv_remove(char* key);

/**
 * @brief Flush all data from caches into the key-value store.
 * 
 * @return int 0 if successful, otherwise an error code.
 */
int os_kv_flush_data(void);
#endif