#include "content.h"

content_t* first_pass(char** filenames, const int num_files);

int main(const int argc, char* argv[]) {
    int filenames_start_index = 1;
    if (argc > 1 && strcmp(argv[1], "-s") == 0) {
        filenames_start_index++;
    }

    char** filenames = &argv[filenames_start_index];
    const content_t* first_pass_content =
        first_pass(filenames, argc - filenames_start_index);

    dump_instruction_list(first_pass_content->instruction_list);
    dump_symbol_table(first_pass_content->symbol_table);

    return 0;
}

content_t* first_pass(char** filenames, const int num_files) {
    content_t* content = create_content();

    for (int i = 0; i < num_files; ++i) {
        const char* filename = filenames[i];
        FILE* file = fopen(filename, "r");
        if (file == NULL) {
            perror(strcat("Fail to open file: ", filename));
            exit(1);
        }

        // Scan instructions
        int line_number = 0;
        char bitstring[18];
        while (fscanf(file, "%d %17s\n", &line_number, bitstring) != EOF) {
            if (line_number == 4096) {
                break;
            }

            instruction_t* instruction =
                create_instruction(line_number, bitstring);
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
        int addr = 0;
        char label[26];
        while (fscanf(file, "%25s %d", label, &addr) != EOF) {
            add_symbol(content->symbol_table, label, addr);
        }

        fclose(file);
    }

    return content;
}
