#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_PRODS 50
#define MAX_LEN 100
#define MAX_NT 26
#define MAX_T 26

typedef struct {
    char lhs;
    char rhs[MAX_LEN];
} Production;

typedef struct {
    bool terminals[MAX_T];
    bool epsilon;
} Set;

Production productions[MAX_PRODS];
int num_productions = 0;
Set first_sets[MAX_NT];
Set follow_sets[MAX_NT];
bool calculated_first[MAX_NT] = {false};
bool calculated_follow[MAX_NT] = {false};

// Function declarations
void read_grammar_from_file(const char* filename);
void calculate_first_set(char symbol);
void calculate_follow_set(char non_terminal);
Set get_first_set_string(const char* string);
void write_results_to_file(const char* filename);
bool is_non_terminal(char c);
bool is_terminal(char c);
int get_index(char c);
void print_set(FILE* fp, Set set);
bool is_ll1_grammar(void);

// Initialize empty set
Set new_set() {
    Set set;
    memset(&set, 0, sizeof(Set));
    return set;
}

// Set union operation
void set_union(Set* dest, Set src) {
    for (int i = 0; i < MAX_T; i++) {
        dest->terminals[i] |= src.terminals[i];
    }
    dest->epsilon |= src.epsilon;
}

// Read grammar from file
void read_grammar_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open input file %s\n", filename);
        exit(1);
    }

    char line[MAX_LEN];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        // Skip empty lines
        if (strlen(line) == 0) continue;
        
        // Parse production
        if (strlen(line) >= 3 && line[1] == '-' && line[2] == '>') {
            productions[num_productions].lhs = line[0];
            strcpy(productions[num_productions].rhs, line + 3);
            num_productions++;
        }
    }
    fclose(file);
}

// Calculate FIRST set for a symbol
void calculate_first_set(char symbol) {
    int index = get_index(symbol);
    if (calculated_first[index]) return;
    
    calculated_first[index] = true;
    Set* first = &first_sets[index];
    
    for (int i = 0; i < num_productions; i++) {
        if (productions[i].lhs != symbol) continue;
        
        const char* rhs = productions[i].rhs;
        if (strlen(rhs) == 0) {
            first->epsilon = true;
            continue;
        }
        
        if (is_terminal(rhs[0])) {
            first->terminals[get_index(rhs[0])] = true;
        } else if (is_non_terminal(rhs[0])) {
            calculate_first_set(rhs[0]);
            set_union(first, first_sets[get_index(rhs[0])]);
            
            int j = 0;
            while (rhs[j] != '\0' && first_sets[get_index(rhs[j])].epsilon) {
                j++;
                if (rhs[j] != '\0') {
                    if (is_terminal(rhs[j])) {
                        first->terminals[get_index(rhs[j])] = true;
                        break;
                    } else if (is_non_terminal(rhs[j])) {
                        calculate_first_set(rhs[j]);
                        set_union(first, first_sets[get_index(rhs[j])]);
                    }
                }
            }
        }
    }
}

// Calculate FIRST set for a string
Set get_first_set_string(const char* string) {
    Set result = new_set();
    if (strlen(string) == 0) {
        result.epsilon = true;
        return result;
    }
    
    bool all_derive_epsilon = true;
    for (int i = 0; string[i] != '\0' && all_derive_epsilon; i++) {
        if (is_terminal(string[i])) {
            result.terminals[get_index(string[i])] = true;
            all_derive_epsilon = false;
        } else if (is_non_terminal(string[i])) {
            set_union(&result, first_sets[get_index(string[i])]);
            if (!first_sets[get_index(string[i])].epsilon) {
                all_derive_epsilon = false;
            }
        }
    }
    if (all_derive_epsilon) {
        result.epsilon = true;
    }
    return result;
}

// Calculate FOLLOW set for a non-terminal
void calculate_follow_set(char non_terminal) {
    int index = get_index(non_terminal);
    if (calculated_follow[index]) return;
    
    calculated_follow[index] = true;
    
    // Add $ to start symbol's FOLLOW set
    if (non_terminal == productions[0].lhs) {
        follow_sets[index].terminals[get_index('$')] = true;
    }
    
    for (int i = 0; i < num_productions; i++) {
        char* rhs = productions[i].rhs;
        int len = strlen(rhs);
        
        for (int j = 0; j < len; j++) {
            if (rhs[j] == non_terminal) {
                if (j == len - 1) {
                    calculate_follow_set(productions[i].lhs);
                    set_union(&follow_sets[index], follow_sets[get_index(productions[i].lhs)]);
                } else {
                    Set first_next = get_first_set_string(&rhs[j + 1]);
                    
                    for (int k = 0; k < MAX_T; k++) {
                        if (first_next.terminals[k]) {
                            follow_sets[index].terminals[k] = true;
                        }
                    }
                    
                    if (first_next.epsilon) {
                        calculate_follow_set(productions[i].lhs);
                        set_union(&follow_sets[index], follow_sets[get_index(productions[i].lhs)]);
                    }
                }
            }
        }
    }
}

// Write results to output file
void write_results_to_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Cannot open output file %s\n", filename);
        return;
    }

    // Print grammar
    fprintf(file, "Grammar:\n");
    fprintf(file, "--------\n");
    for (int i = 0; i < num_productions; i++) {
        fprintf(file, "%c -> %s\n", productions[i].lhs, productions[i].rhs);
    }
    fprintf(file, "\n");

    // Print FIRST sets
    fprintf(file, "FIRST Sets:\n");
    fprintf(file, "-----------\n");
    for (char nt = 'A'; nt <= 'Z'; nt++) {
        bool has_productions = false;
        for (int i = 0; i < num_productions; i++) {
            if (productions[i].lhs == nt) {
                has_productions = true;
                break;
            }
        }
        if (has_productions) {
            fprintf(file, "FIRST(%c) = ", nt);
            print_set(file, first_sets[get_index(nt)]);
            fprintf(file, "\n");
        }
    }
    fprintf(file, "\n");

    // Print FOLLOW sets
    fprintf(file, "FOLLOW Sets:\n");
    fprintf(file, "------------\n");
    for (char nt = 'A'; nt <= 'Z'; nt++) {
        bool has_productions = false;
        for (int i = 0; i < num_productions; i++) {
            if (productions[i].lhs == nt) {
                has_productions = true;
                break;
            }
        }
        if (has_productions) {
            fprintf(file, "FOLLOW(%c) = ", nt);
            print_set(file, follow_sets[get_index(nt)]);
            fprintf(file, "\n");
        }
    }
    fprintf(file, "\n");

    // Print LL(1) status
    fprintf(file, "LL(1) Analysis:\n");
    fprintf(file, "--------------\n");
    if (is_ll1_grammar()) {
        fprintf(file, "The grammar is LL(1)\n");
    } else {
        fprintf(file, "The grammar is not LL(1)\n");
        
        // Print conflicts
        fprintf(file, "\nConflicts found:\n");
        for (char nt = 'A'; nt <= 'Z'; nt++) {
            bool has_productions = false;
            for (int i = 0; i < num_productions; i++) {
                if (productions[i].lhs == nt) {
                    Set first_alpha = get_first_set_string(productions[i].rhs);
                    
                    for (int j = i + 1; j < num_productions; j++) {
                        if (productions[j].lhs == nt) {
                            Set first_beta = get_first_set_string(productions[j].rhs);
                            
                            // Check for FIRST-FIRST conflicts
                            for (int k = 0; k < MAX_T; k++) {
                                if (first_alpha.terminals[k] && first_beta.terminals[k]) {
                                    fprintf(file, "FIRST-FIRST conflict for non-terminal %c between productions %d and %d\n",
                                            nt, i + 1, j + 1);
                                }
                            }
                            
                            // Check for FIRST-FOLLOW conflicts
                            if (first_alpha.epsilon || first_beta.epsilon) {
                                Set follow_nt = follow_sets[get_index(nt)];
                                for (int k = 0; k < MAX_T; k++) {
                                    if ((first_alpha.epsilon && first_beta.terminals[k] && follow_nt.terminals[k]) ||
                                        (first_beta.epsilon && first_alpha.terminals[k] && follow_nt.terminals[k])) {
                                        fprintf(file, "FIRST-FOLLOW conflict for non-terminal %c between productions %d and %d\n",
                                                nt, i + 1, j + 1);
                                    }
                                }
                            }
                        }
                    }
                    has_productions = true;
                }
            }
        }
    }
    
    fclose(file);
}

// Utility functions
bool is_non_terminal(char c) {
    return c >= 'A' && c <= 'Z';
}

bool is_terminal(char c) {
    return (c >= 'a' && c <= 'z') || c == '$';
}

int get_index(char c) {
    if (is_non_terminal(c)) return c - 'A';
    return c - 'a';
}

void print_set(FILE* fp, Set set) {
    fprintf(fp, "{ ");
    for (int i = 0; i < MAX_T; i++) {
        if (set.terminals[i]) {
            fprintf(fp, "%c ", i + 'a');
        }
    }
    if (set.epsilon) fprintf(fp, "ε ");
    fprintf(fp, "}");
}

// Check if grammar is LL(1)
bool is_ll1_grammar() {
    for (char nt = 'A'; nt <= 'Z'; nt++) {
        for (int i = 0; i < num_productions; i++) {
            if (productions[i].lhs != nt) continue;
            
            Set first_alpha = get_first_set_string(productions[i].rhs);
            
            for (int j = i + 1; j < num_productions; j++) {
                if (productions[j].lhs != nt) continue;
                
                Set first_beta = get_first_set_string(productions[j].rhs);
                
                // Check FIRST-FIRST conflicts
                for (int k = 0; k < MAX_T; k++) {
                    if (first_alpha.terminals[k] && first_beta.terminals[k]) {
                        return false;
                    }
                }
                
                // Check FIRST-FOLLOW conflicts
                if (first_alpha.epsilon || first_beta.epsilon) {
                    Set follow_nt = follow_sets[get_index(nt)];
                    for (int k = 0; k < MAX_T; k++) {
                        if ((first_alpha.epsilon && first_beta.terminals[k] && follow_nt.terminals[k]) ||
                            (first_beta.epsilon && first_alpha.terminals[k] && follow_nt.terminals[k])) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    // Initialize sets
    for (int i = 0; i < MAX_NT; i++) {
        first_sets[i] = new_set();
        follow_sets[i] = new_set();
    }
    
    // Read grammar from file
    read_grammar_from_file("grammar.txt");
    
    // Calculate FIRST and FOLLOW sets
    for (char nt = 'A'; nt <= 'Z'; nt++) {
        calculate_first_set(nt);
    }
    
    for (char nt = 'A'; nt <= 'Z'; nt++) {
        calculate_follow_set(nt);
    }
    
    // Write results to file
    write_results_to_file("output.txt");
    
    printf("Analysis complete. Results written to output.txt\n");
    
    return 0;
}
