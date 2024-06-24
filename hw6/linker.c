#include "content.h"

/**
 * @brief Reads a MIC-1 object file and converts it into a content.
 *
 * This function opens a file specified by the given filename, reads its
 * contents, and populates a content_t structure with instructions and symbols
 * found in the file.
 *
 * @param filename The name of the file to be read.
 * @return content_t* Pointer to the newly created content_t structure
 * containing the file's contents.
 */
content_t* file_to_content(const char* filename);

/**
 * @brief Merges multiple content into a single content.
 *
 * This function performs a first pass to merge instructions and symbols from
 * multiple content_t structures into a single content_t structure. The merged
 * instructions and symbols are adjusted to have contiguous addresses. The input
 * content_t structures and their internal structures are freed after merging.
 *
 * @param contents An array of pointers to content_t structures to be merged.
 * @param num_contents The number of content_t structures in the array.
 * @return content_t* Pointer to the newly created content_t structure
 * containing the merged instructions and symbols.
 */
content_t* first_pass(content_t** contents, int num_contents);

instruction_list_t* second_pass(const content_t* first_pass_content);

char* addr_to_bitstring(int addr);

void write_machine_code(
    FILE* file, const instruction_list_t* machine_code_list);

int main(const int argc, char* argv[]) {
    int filenames_start_index = 1;

    if (argc > 1 && strcmp(argv[1], "-s") == 0) {
        filenames_start_index++;
    }

    char** filenames = &argv[filenames_start_index];
    const int num_files = argc - filenames_start_index;
    content_t** contents = malloc(sizeof(content_t) * num_files);
    require_not_null(contents, "contents");
    for (int i = 0; i < num_files; ++i) {
        contents[i] = file_to_content(filenames[i]);
    }
    const content_t* first_pass_content = first_pass(contents, num_files);

    // Second pass
    const instruction_list_t* machine_code_list =
        second_pass(first_pass_content);
    write_machine_code(stdout, machine_code_list);

    return 0;
}

content_t* file_to_content(const char* filename) {
    content_t* content = create_content();

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror(strcat("Fail to open file: ", filename));
        exit(1);
    }

    // Scan instructions
    int addr = 0;
    char bitstring[18];
    while (fscanf(file, "%d %17s\n", &addr, bitstring) != EOF) {
        if (addr == 4096) {
            break;
        }

        instruction_t* instruction = create_instruction(addr, bitstring);
        instruction->is_resolved = bitstring[0] != 'U';
        const char* bitstring_addr = &bitstring[!instruction->is_resolved];
        strncpy(instruction->bitstring, bitstring_addr, 16);
        instruction->bitstring[16] = '\0';
        if (!instruction->is_resolved) {
            instruction->label = malloc(26);
            fscanf(file, "%25s", instruction->label);
            instruction->label[25] = '\0';
        }

        add_instruction(content->instruction_list, instruction);
    }

    // Scan symbols
    char label[26];
    while (fscanf(file, "%25s %d", label, &addr) != EOF) {
        add_symbol(content->symbol_table, label, addr);
    }

    fclose(file);

    return content;
}

content_t* first_pass(content_t** contents, const int num_contents) {
    content_t* result_content = create_content();
    instruction_list_t* result_instruction_list =
        result_content->instruction_list;
    symbol_table_t* result_symbol_table = result_content->symbol_table;

    int addr_offset = 0;
    for (int i = 0; i < num_contents; ++i) {
        // ReSharper disable once CppDFANullDereference
        content_t* content = contents[i];
        instruction_list_t* instruction_list = content->instruction_list;
        symbol_table_t* symbol_table = content->symbol_table;

        for (instruction_t* instruction = instruction_list->head;
             instruction != NULL; instruction = instruction->next) {
            instruction->addr += addr_offset;
            add_instruction(result_instruction_list, instruction);
        }

        for (const symbol_t* symbol = symbol_table->head; symbol != NULL;
             symbol = symbol->next) {
            add_symbol(
                result_symbol_table, symbol->label, symbol->addr + addr_offset);
        }

        addr_offset = content->instruction_list->tail->addr + 1;

        free(content);
        free(instruction_list);
        free_symbol_table(symbol_table);
    }

    free(contents);

    return result_content;
}

instruction_list_t* second_pass(const content_t* first_pass_content) {
    const instruction_list_t* instruction_list =
        first_pass_content->instruction_list;
    const symbol_table_t* symbol_table = first_pass_content->symbol_table;

    instruction_list_t* machine_code_list = create_instruction_list();
    for (const instruction_t* instruction = instruction_list->head;
         instruction != NULL; instruction = instruction->next) {
        char bitstring[17];
        if (instruction->is_resolved) {
            strncpy(bitstring, instruction->bitstring, 17);
        } else {
            // unresolved case
            strncpy(bitstring, instruction->bitstring, 4);
            const symbol_t* symbol =
                search_symbol(symbol_table, instruction->label);
            if (symbol == NULL) {
                perror(strcat("Unknown symbol: ", instruction->label));
                exit(1);
            }
            char* addr_bitstring = addr_to_bitstring(symbol->addr);
            strncpy(&bitstring[4], addr_bitstring, 12);
            bitstring[16] = '\0';
            free(addr_bitstring);
        }
        instruction_t* machine_code =
            create_instruction(instruction->addr, bitstring);
        add_instruction(machine_code_list, machine_code);
    }

    return machine_code_list;
}

char* addr_to_bitstring(const int addr) {
    if (addr < 0 || addr > MIC1_MAX_ADDRESS) {
        fprintf(stderr, "Invalid address: %d\n", addr);
        exit(1);
    }

    char* bitstring = malloc(MIC1_MAX_ADDRESS_BITS);
    require_not_null(bitstring, "bitstring");

    for (int i = 0; i < MIC1_MAX_ADDRESS_BITS; ++i) {
        bitstring[MIC1_MAX_ADDRESS_BITS - i - 1] = addr & 1 << i ? '1' : '0';
    }

    return bitstring;
}

void write_machine_code(
    FILE* file, const instruction_list_t* machine_code_list) {
    int line_number = 0;
    for (const instruction_t* instruction = machine_code_list->head;
         instruction != NULL; instruction = instruction->next) {
        while (line_number < instruction->addr) {
            const char* halt = "1111111111111111\n";
            fprintf(file, "%s", halt);
            line_number++;
        }
        fprintf(file, "%s\n", instruction->bitstring);
        line_number++;
    }
}
