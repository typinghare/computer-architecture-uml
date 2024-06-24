#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

/**
 * @brief Structure representing a symbol node in a symbol table.
 */
typedef struct symbol {
    /* The label of the symbol (up to 25 characters + null terminator) */
    char label[26];
    /* The address of the instruction associated with this symbol */
    int addr;
    /* Pointer to the next symbol in the linked list */
    struct symbol* next;
} symbol_t;

/**
 * @brief Represents a symbol table, which is a collection of symbols.
 */
typedef struct symbol_table {
    symbol_t* head;
    symbol_t* tail;
} symbol_table_t;

/**
 * @brief Creates a new symbol table.
 *
 * @return symbol_table_t* Pointer to the newly created symbol table.
 */
symbol_table_t* create_symbol_table();

/**
 * @brief Adds a symbol to the symbol table.
 *
 * @param symbol_table The symbol table to add to.
 * @param label The label of the symbol to add.
 * @param addr The address of the instruction associated with the symbol.
 */
void add_symbol(symbol_table_t* symbol_table, const char* label, int addr);

/**
 * @brief Searches for a symbol by its label in the symbol table.
 *
 * @param symbol_table Pointer to the symbol table.
 * @param label The label of the symbol to search for.
 * @return symbol_t* Pointer to the found symbol, or NULL if not found.
 */
symbol_t* search_symbol(const symbol_table_t* symbol_table, const char* label);

/**
 * @brief Dumps the symbol table.
 */
void dump_symbol_table(const symbol_table_t* symbol_table);

/**
 * @brief Recursively frees a linked list of symbols.
 *
 * This function recursively frees each symbol in a linked list of symbols.
 * If the given symbol is NULL, the function does nothing.
 *
 * @param symbol Pointer to the first symbol in the linked list.
 */
void free_symbol(symbol_t* symbol);

/**
 * @brief Frees the memory allocated for a symbol table.
 *
 * This function frees the entire symbol table structure, including its head
 * and tail symbols. If the given symbol table is NULL, the function does
 * nothing.
 *
 * @param symbol_table Pointer to the symbol table.
 */
void free_symbol_table(symbol_table_t* symbol_table);

inline symbol_table_t* create_symbol_table() {
    symbol_table_t* symbol_table = malloc(sizeof(symbol_table_t));
    require_not_null(symbol_table, "symbol table");

    symbol_table->head = NULL;
    symbol_table->tail = NULL;

    return symbol_table;
}

inline void
add_symbol(symbol_table_t* symbol_table, const char* label, const int addr) {
    require_not_null(symbol_table, "symbol table");
    require_not_null(label, "label");

    if (search_symbol(symbol_table, label) != NULL) {
        perror(strcat("Duplicate symbol: ", label));
        exit(1);
    }

    symbol_t* symbol = malloc(sizeof(symbol_t));
    require_not_null(symbol, "symbol");

    strcpy(symbol->label, label);
    symbol->addr = addr;
    symbol->next = NULL;

    if (symbol_table->head == NULL) {
        symbol_table->head = symbol_table->tail = symbol;
    } else {
        symbol_table->tail->next = symbol;
        symbol_table->tail = symbol;
    }
}

inline symbol_t*
search_symbol(const symbol_table_t* symbol_table, const char* label) {
    require_not_null(symbol_table, "symbol table");
    require_not_null(label, "label");

    for (symbol_t* symbol = symbol_table->head; symbol != NULL;
         symbol = symbol->next) {
        if (strcmp(symbol->label, label) == 0) {
            return symbol;
        }
    }

    return NULL;
}

inline void dump_symbol_table(const symbol_table_t* symbol_table) {
    require_not_null(symbol_table, "symbol table");

    printf("-----------[Symbol Table]------------\n");
    FILE* file = popen("sort -k1,1 -f", "w");
    for (const symbol_t* symbol = symbol_table->head; symbol != NULL;
         symbol = symbol->next) {
        fprintf(file, "%-25s %4d\n", symbol->label, symbol->addr);
    }
    fclose(file);
    wait(NULL);
    printf("-------------------------------------\n");
}

inline void free_symbol(symbol_t* symbol) {
    if (symbol == NULL) {
        return;
    }

    symbol_t* next_symbol = symbol->next;
    free_symbol(next_symbol);
    free(symbol);
}

inline void free_symbol_table(symbol_table_t* symbol_table) {
    if (symbol_table == NULL) {
        return;
    }

    free_symbol(symbol_table->head);
    free(symbol_table);
}

#endif
