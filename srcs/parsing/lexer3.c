#include "parsing.h"

// Advance and skip whitespace
static void skip_spaces(const char **input) {
	while (**input && ft_isspace(**input))
		(*input)++;
}

// Helper to detect end of token
static bool is_token_sep(char c) {
	return ft_isspace(c) || c == '\0';
}

// Get one token at a time
t_token *get_next_token(const char **input_ptr) {
	const char *input = *input_ptr;
	skip_spaces(&input);

	if (*input == '\0')
		return NULL;

	size_t start = 0;
	size_t len = 0;

	// Handle quoted strings
	if (*input == '"' || *input == '\'') {
		char quote = *input;
		input++;  // Skip opening quote
		start = input - *input_ptr;

		while (*input && *input != quote)
			input++;

		len = input - (*input_ptr + start);
		t_token *tok = init_token(0, *input_ptr, start, len);
		if (*input == quote)
			input++;  // Skip closing quote
		*input_ptr = input;
		return tok;
	}

	// Handle normal token (split at space)
	start = input - *input_ptr;
	while (*input && !ft_isspace(*input))
		input++;

	len = input - (*input_ptr + start);
	*input_ptr = input;
	return init_token(0, *input_ptr, start, len);
}

int main() {
	const char *input = "bonjour \"sa va $YOU\"";
	const char *cursor = input;

	t_token *tok;
	while ((tok = get_next_token(&cursor)) != NULL) {
		printf("Token: [%s]\n", tok->value);
		free(tok->value);
		free(tok);
	}
	return 0;
}

