#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Token types
typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    double value;
} Token;

// Parser state
typedef struct {
    const char* input;
    int position;
    Token current_token;
} Parser;

// Function declarations
Token get_next_token(Parser* parser);
double parse_expression(Parser* parser);
double parse_term(Parser* parser);
double parse_factor(Parser* parser);
double parse_number(Parser* parser);

// Initialize parser
void init_parser(Parser* parser, const char* input) {
    parser->input = input;
    parser->position = 0;
    parser->current_token = get_next_token(parser);
}

// Get next token from input
Token get_next_token(Parser* parser) {
    Token token;
    
    // Skip whitespace
    while (isspace(parser->input[parser->position])) {
        parser->position++;
    }
    
    // Check for end of input
    if (parser->input[parser->position] == '\0') {
        token.type = TOKEN_EOF;
        return token;
    }
    
    // Check for numbers
    if (isdigit(parser->input[parser->position])) {
        char* endptr;
        token.value = strtod(&parser->input[parser->position], &endptr);
        token.type = TOKEN_NUMBER;
        parser->position += (endptr - &parser->input[parser->position]);
        return token;
    }
    
    // Check for operators and parentheses
    switch (parser->input[parser->position]) {
        case '+':
            token.type = TOKEN_PLUS;
            break;
        case '-':
            token.type = TOKEN_MINUS;
            break;
        case '*':
            token.type = TOKEN_MULTIPLY;
            break;
        case '/':
            token.type = TOKEN_DIVIDE;
            break;
        case '(':
            token.type = TOKEN_LPAREN;
            break;
        case ')':
            token.type = TOKEN_RPAREN;
            break;
        default:
            token.type = TOKEN_ERROR;
            return token;
    }
    
    parser->position++;
    return token;
}

// Consume current token and get next
void eat(Parser* parser, TokenType type) {
    if (parser->current_token.type == type) {
        parser->current_token = get_next_token(parser);
    } else {
        fprintf(stderr, "Unexpected token\n");
        exit(1);
    }
}

// Parse expression: term ((PLUS | MINUS) term)*
double parse_expression(Parser* parser) {
    double result = parse_term(parser);
    
    while (parser->current_token.type == TOKEN_PLUS || 
           parser->current_token.type == TOKEN_MINUS) {
        Token token = parser->current_token;
        if (token.type == TOKEN_PLUS) {
            eat(parser, TOKEN_PLUS);
            result += parse_term(parser);
        } else if (token.type == TOKEN_MINUS) {
            eat(parser, TOKEN_MINUS);
            result -= parse_term(parser);
        }
    }
    
    return result;
}

// Parse term: factor ((MUL | DIV) factor)*
double parse_term(Parser* parser) {
    double result = parse_factor(parser);
    
    while (parser->current_token.type == TOKEN_MULTIPLY || 
           parser->current_token.type == TOKEN_DIVIDE) {
        Token token = parser->current_token;
        if (token.type == TOKEN_MULTIPLY) {
            eat(parser, TOKEN_MULTIPLY);
            result *= parse_factor(parser);
        } else if (token.type == TOKEN_DIVIDE) {
            eat(parser, TOKEN_DIVIDE);
            double divisor = parse_factor(parser);
            if (divisor == 0) {
                fprintf(stderr, "Division by zero\n");
                exit(1);
            }
            result /= divisor;
        }
    }
    
    return result;
}

// Parse factor: NUMBER | LPAREN expression RPAREN
double parse_factor(Parser* parser) {
    Token token = parser->current_token;
    
    if (token.type == TOKEN_NUMBER) {
        eat(parser, TOKEN_NUMBER);
        return token.value;
    } else if (token.type == TOKEN_LPAREN) {
        eat(parser, TOKEN_LPAREN);
        double result = parse_expression(parser);
        eat(parser, TOKEN_RPAREN);
        return result;
    } else if (token.type == TOKEN_MINUS) {
        eat(parser, TOKEN_MINUS);
        return -parse_factor(parser);
    }
    
    fprintf(stderr, "Invalid factor\n");
    exit(1);
}

// Main function to parse input
double parse(const char* input) {
    Parser parser;
    init_parser(&parser, input);
    double result = parse_expression(&parser);
    
    if (parser.current_token.type != TOKEN_EOF) {
        fprintf(stderr, "Unexpected tokens after expression\n");
        exit(1);
    }
    
    return result;
}

// Example usage
int main() {
    const char* expressions[] = {
        "2 + 3 * 4",
        "(2 + 3) * 4",
        "10 / 2 - 3",
        "-5 + 10"
    };
    
    for (int i = 0; i < sizeof(expressions) / sizeof(expressions[0]); i++) {
        printf("Expression: %s\n", expressions[i]);
        printf("Result: %.2f\n\n", parse(expressions[i]));
    }
    
    return 0;
}
