#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Ensures that the given object pointer is not NULL.
 *
 * This function checks if the provided object pointer is NULL. If it is,
 * the function prints an error message indicating that the specified
 * object name is a null pointer.
 *
 * @param object Pointer to the object that must not be NULL.
 * @param name Name of the object, used in the error message if the object is
 * NULL.
 */
void require_not_null(const void* object, const char* name);

/**
 * @brief Repeats a given character a specified number of times and returns the
 * resulting string.
 *
 * This function allocates memory for a new string and fills it with the given
 * character repeated the specified number of times. The string is
 * null-terminated.
 *
 * @param c The character to repeat.
 * @param count The number of times to repeat the character.
 * @return A pointer to the newly allocated string containing the repeated
 * character. The caller is responsible for freeing the allocated memory.
 *         Returns NULL if memory allocation fails.
 */
char* repeat(char c, int count);

inline void require_not_null(const void* object, const char* name) {
    if (object == NULL) {
        perror(strcat("Null pointer: ", name));
    }
}

inline char* repeat(const char c, const int count) {
    char* string = malloc(count + 1);
    require_not_null(string, "string");
    memset(string, c, count);
    string[count] = '\0';

    return string;
}

#endif
