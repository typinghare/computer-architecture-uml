#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_null.h>

#include "common.h"

typedef struct instruction {
    int line_number;
    char bitstring[17];
    bool is_resolved;
    char* label;
    struct instruction* next;
} instruction_t;

typedef struct instruction_list {
    instruction_t* head;
    instruction_t* tail;
} instruction_list_t;

instruction_list_t* create_instruction_list();

instruction_t* create_instruction(int line_number, const char* bitstring);

void add_label(instruction_t* instruction, const char* label);

void add_instruction(
    instruction_list_t* instruction_list, instruction_t* instruction);

void dump_instruction_list(const instruction_list_t* instruction_list);

void free_instruction(instruction_t* instruction);

void free_instruction_list(instruction_list_t* instruction_list);

inline instruction_list_t* create_instruction_list() {
    instruction_list_t* instruction_list = malloc(sizeof(instruction_list_t));
    require_not_null(instruction_list, "instruction list");

    return instruction_list;
}

inline instruction_t*
create_instruction(const int line_number, const char* bitstring) {
    instruction_t* instruction = malloc(sizeof(instruction_t));
    require_not_null(instruction, "instruction");
    instruction->line_number = line_number;
    strncpy(instruction->bitstring, bitstring, 16);
    instruction->is_resolved = true;
    instruction->label = NULL;
    instruction->next = NULL;

    return instruction;
}

inline void add_label(instruction_t* instruction, const char* label) {
    char* _label = malloc(sizeof(char) * 6);
    require_not_null(label, "instruction label");

    strcpy(_label, label);
    instruction->label = _label;
}

inline void add_instruction(
    instruction_list_t* instruction_list, instruction_t* instruction) {
    if (instruction_list->head == NULL) {
        instruction_list->head = instruction_list->tail = instruction;
    } else {
        instruction_list->tail->next = instruction;
        instruction_list->tail = instruction;
    }
}

inline void dump_instruction_list(const instruction_list_t* instruction_list) {
    printf("------------[instruction list]------------");
    for (const instruction_t* instruction = instruction_list->head;
         instruction != NULL; instruction = instruction->next) {
        char* mark = instruction->is_resolved ? "" : "U";
        char* label = instruction->label == NULL ? "" : instruction->label;
        printf(
            "\n%-4d %s%-4s  %s", instruction->line_number, mark,
            instruction->bitstring, label);
    }
    printf("\n------------------------------------------\n");
}

inline void free_instruction(instruction_t* instruction) {
    if (instruction == NULL) {
        return;
    }

    instruction_t* next_instruction = instruction->next;
    free_instruction(next_instruction);
    if (instruction->label != NULL) {
        free(instruction->label);
    }
    free(instruction);
}

inline void free_instruction_list(instruction_list_t* instruction_list) {
    if (instruction_list == NULL) {
        return;
    }

    free_instruction(instruction_list->head);
    free(instruction_list);
}

#endif
