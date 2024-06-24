#ifndef CONTENT_H
#define CONTENT_H

#include "common.h"
#include "instruction.h"
#include "symbol.h"

typedef struct content {
    instruction_list_t* instruction_list;
    symbol_table_t* symbol_table;
} content_t;

content_t* create_content();

void free_content(content_t* content);

inline content_t* create_content() {
    content_t* content = malloc(sizeof(content_t));
    require_not_null(content, "content");
    content->instruction_list = create_instruction_list();
    content->symbol_table = create_symbol_table();

    return content;
}

inline void free_content(content_t* content) {
    if (content == NULL) {
        return;
    }

    free_instruction_list(content->instruction_list);
    free_symbol_table(content->symbol_table);
    free(content);
}

#endif
