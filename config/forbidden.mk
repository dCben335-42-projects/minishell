ALLOWED_FUNC = readline|rl_clear_history|rl_on_new_line|rl_replace_line|rl_redisplay|add_history|printf|malloc|free|write|access|open|read|close|fork|wait|waitpid|wait3|wait4|signal|sigaction|sigemptyset|sigaddset|kill|exit|getcwd|chdir|stat|lstat|fstat|unlink|execve|dup|dup2|pipe|opendir|readdir|closedir|strerror|perror|isatty|ttyname|ttyslot|ioctl|getenv|tcsetattr|tcgetattr|tgetent|tgetflag|tgetnum|tgetstr|tgoto|tputs

forbid:
	@echo "Checking for forbidden functions:"
	@if nm -u minishell | egrep -v -w "$(ALLOWED_FUNC)"; then \
		echo "✅ No forbidden functions"; \
	else \
		echo "❌ Forbidden functions found" && exit 1; \
	fi
	@echo "Searching for forbidden source usages:"
	@if grep -rnw srcs -e '\bputs\b' -e '\bputchar\b'; then \
		echo "❌ Forbidden source calls found" && exit 1; \
	else \
		echo "✅ No forbidden source calls"; \
	fi

.PHONY: forbid