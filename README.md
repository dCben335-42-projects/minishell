# Shellost

> A from-scratch, Bash-like shell written in C — lexer, parser, AST, expansion,
> redirections, pipelines, builtins and signals, all built on a custom `libft`.

**Shellost** was our first big C project at **42 Lyon**. We built it as a team of
two: **Benoit Cabocel** (`dCben335` / `bcabocel`) and **Antoine Bonneau**
(`abonneau`, **AzallLab / Chen**, also `ChenRaptor` in the git history).

The goal was simple on paper and huge in practice: read a command line, understand
it, execute it like a real shell, and never leak memory while doing it.

---

## The team

### Benoit Cabocel — `dCben335` / `bcabocel`

**Runtime, execution and the shell experience.**

- Shell state, environment storage and `SHLVL` handling
- Main REPL loop, prompt, banner, history and continuation prompts
- Builtins: `cd`, `echo`, `env`, `export`, `unset`, `exit`, `:`, `debug`
- Environment-variable and wildcard expansion
- Redirections: `<`, `>`, `>>`, `<<`, `<<-` and heredoc caching
- Command execution: `PATH` resolution, `fork`/`execve`/`wait`, exit statuses
- Orchestrator, pipelines, `&&`, `||`, `;`, subshells and subshell redirections
- Signals: `SIGINT`/`SIGQUIT` handling across shell, heredoc, fork and capture contexts
- Config flags, colors, debug modes, build system and memory cleanup
- The custom `libft` used across the project

### Antoine Bonneau — `abonneau`, AzallLab / Chen

**Parsing, grammar and AST architecture.**

- Initial lexer and tokenizer, then the token-by-token parser refactor
- Syntax validation: operands, operators, parentheses, semicolons and continuation
- AST builder: commands, operators, pipes, parentheses and nested subshells
- AST node types, token masks and token-rule maps
- AST JSON printer used by the debug tooling
- Heredoc handling in the lexer and default signal behavior
- Environment init/read helpers, `pwd`, wildcard structure and prefix parsing
- Struct normalization, comments, Norm fixes and many parser bug fixes

### Shared work

We reviewed, merged, debugged and Norm-cleaned almost everything together.
The split above is based on the git history and the main ownership of each module;
the final shell is very much a two-person project.

---

## Features

### Shell language

| Feature                                                             | Status | Main implementation |
| ------------------------------------------------------------------- | ------ | ------------------- |
| Interactive REPL with `readline` and history                        | Done   | Benoit              |
| Command sequences with `;`                                          | Done   | Benoit              |
| Pipelines with `\|`                                                 | Done   | Benoit              |
| Logical lists with `&&` and `\|\|`                                  | Done   | Benoit              |
| Subshells with `( ... )`                                            | Done   | Antoine / Benoit    |
| Redirections attached to subshells                                  | Done   | Antoine / Benoit    |
| Logical negation with `! command`                                   | Done   | Benoit              |
| Exit status expansion with `$?`                                     | Done   | Benoit              |
| Multi-line continuation for quotes, parentheses, pipes and heredocs | Done   | Antoine / Benoit    |
| Syntax-error reporting                                              | Done   | Antoine / Benoit    |

```sh
$ (echo hello | tr a-z A-Z) && echo "done"
HELLO
done

$ ! false && echo "the negation worked"
the negation worked
```

### Lexer and parser

- Character-by-character lexer with a dedicated state for quotes and heredocs
- Handles single quotes, double quotes and empty quoted strings
- Recognizes words, spaces, operators, redirections, parentheses and EOF
- Detects unterminated quotes and asks for more input
- Tracks opening/closing parentheses across the whole input
- Validates left/right operands, empty parentheses, empty semicolons and
  misplaced operators
- Produces clear `syntax error near unexpected token` messages
- Handles heredoc delimiters, quoted delimiters and `<<-` tab stripping
- Uses bitmasks and rule maps instead of giant `if` chains

### Abstract Syntax Tree

- Every token is converted into a typed AST node
- Supports sequences, base commands, pipes, `&&`, `||`, semicolons, subshells,
  redirections and nested groups
- Preserves operator precedence and parent/subshell relationships
- Supports nested subshells and subshell redirections
- Built-in JSON AST printer for debugging
- Recursive construction with centralized cleanup on allocation failure

### Execution

- Forks and executes external commands with `execve`
- Resolves command names through `PATH`, including absolute and relative paths
- Correctly reports:
  - command not found (`127`)
  - permission denied (`126`)
  - is a directory (`126`)
  - signal termination (`128 + signal`)
- Waits for all children and returns the status of the last pipeline element
- Runs builtins in the parent shell when needed, preserving environment changes
- Applies redirections to both builtins and external commands
- Supports redirections on subshells and pipelines
- Handles `SIGINT`/`SIGQUIT` differently in shell, heredoc, child and capture
  contexts, including `130` exit codes

### Redirections and heredocs

- `<` — input redirection
- `>` — output redirection with truncation
- `>>` — output redirection with append
- `<<` — heredoc
- `<<-` — heredoc with leading tab stripping
- Quoted heredoc delimiters disable variable expansion
- Heredoc contents are cached and reused across continuation prompts
- Ambiguous redirect detection
- Redirections are expanded before being opened
- Redirections work on simple commands, builtins and subshells

```sh
$ cat <<EOF
hello $USER
EOF

$ cat <<'EOF'
hello $USER
EOF
```

### Expansion

- Environment variables: `$HOME` and `$?`.
- Unquoted expansion with word splitting
- Quoted expansion without unwanted splitting
- Adjacent quoted/unquoted segments joined into one argument
- Empty variables handled correctly
- Wildcards:
  - `*` and `?`
  - multiple path segments
  - directory traversal
  - quoted wildcards stay literal
  - escaped wildcards stay literal
- Wildcard results are collected in a tree, sorted, and inserted into `argv`
- `.`/`..` are filtered and unknown entry types are resolved with `stat`

### Builtins

| Builtin  | What it does                                                                            |
| -------- | --------------------------------------------------------------------------------------- |
| `cd`     | Supports `cd`, `cd PATH`, `cd -`, `HOME`, `OLDPWD`, updates `PWD`/`OLDPWD`              |
| `echo`   | Supports `-n` and multiple `-n`-style flags                                             |
| `env`    | Prints the current environment                                                          |
| `export` | Adds/updates variables, supports `KEY=VALUE` and `KEY+=VALUE`, prints when called alone |
| `unset`  | Removes variables and refreshes the exec environment                                    |
| `pwd`    | Prints the shell's tracked working directory                                            |
| `exit`   | Handles numeric arguments, too many arguments and non-numeric values                    |
| `:`      | No-op builtin that returns success                                                      |
| `debug`  | Toggles token, AST, exit-code and full debug output                                     |

Builtins can be enabled or disabled individually in `includes/config.h`, and all
builtins support redirections.

### Environment and configuration

- Environment stored in a binary search tree for fast lookup
- Converted into a null-terminated array for `execve`
- `SHLVL` increment on startup
- Default `PATH` and fallback environment setup
- Feature flags for:
  - wildcard expansion
  - variable expansion
  - interactive-terminal-only mode
  - startup banner
  - each builtin
  - logical negation
  - default environment and `SHLVL`
- Configurable prompt continuation strings, colors and error messages
- Valgrind suppression file included

---

## Architecture

```text
srcs/
├── main.c                 REPL, startup, banner
├── prompt.c               continuation prompts and re-parsing
├── signals.c              signal contexts and handlers
├── parsing/               lexer, tokenizer, parser, heredoc reader
├── ast_builder/           token list -> AST construction
├── orchestrator/          AST walker: sequences, pipes, subshells, &&/||/;
├── exec/                  expansion, redirections, builtins, execve, statuses
├── structs/               shell, env, token, AST, lexer and wildcard types
└── utils/                 debug output, fd helpers, cleanup, error wrappers
```

### Command lifecycle

```text
readline
   -> lexer        characters become tokens
   -> parser       tokens are validated and rules are checked
   -> ast_builder  tokens become an AST
   -> orchestrator chooses the execution strategy
   -> exec         expand args, apply redirections, run builtin or execve
   -> wait         collect child statuses and set $?
```

---

## Build

### Requirements

- `cc` with C99-compatible flags
- `make`
- GNU `readline` and `history`
- The `libft` git submodule

### Clone and build

```sh
git clone --recurse-submodules git@github.com:dCben335-42-projects/minishell.git
cd minishell
make
./minishell
```

If you already cloned without submodules:

```sh
git submodule update --init --recursive
```

### Makefile targets

| Target              | Description                                          |
| ------------------- | ---------------------------------------------------- |
| `make` / `make all` | Build `minishell`                                    |
| `make clean`        | Remove objects and `libft` objects                   |
| `make fclean`       | Remove objects and binary                            |
| `make re`           | Full rebuild                                         |
| `make run`          | Build and run                                        |
| `make val`          | Run under Valgrind with the project suppression file |
| `make norm`         | Run Norminette on sources, includes and `libft`      |
| `make gen`          | Regenerate the source/include `.mk` file lists       |

The source and header lists are generated automatically into
`config/sources.mk` and `config/includes.mk`, so new files are picked up by
running `make gen`.

---

## Our custom libft

Shellost heavily uses our own `libft` submodule
(`libs/libft`, by Benoit), extended far beyond the basic 42 library:

- `ft_printf` with a callback-based format mapping
- `get_next_line`
- Dynamic arrays for tokens, AST children and arguments
- Binary trees for the environment and wildcard results
- Pointer wrappers with built-in allocation-error tracking
- String helpers, array-of-strings helpers, math helpers and sorting
- Shell-specific helpers such as `ft_fnmatch`, `ft_strnegate` and
  `ft_strpositivate` for wildcard escaping

Using one shared helper library kept memory ownership consistent and made it
possible to build a large, modular project with a very small standard C surface.

---

## Debugging

Enable the debug builtin in `includes/config.h`:

```c
# define FLAG_BUILTIN_DEBUG TRUE
```

Then use:

```sh
$ debug --tokens      # show the token stream
$ debug --ast         # show the AST as JSON
$ debug --exitcode    # show the last exit code after each command
$ debug --all         # enable everything
$ debug --help        # list options
```

---

## What we learned

This project taught us how much happens between pressing Enter and running a
program: quoting rules, operator precedence, file-descriptor lifetimes, process
groups, signal contexts, heredoc caching, expansion ordering and the difference
between "it works" and "it works without leaking, crashing or corrupting the
parent shell".

It was our first large C codebase, our first serious use of an AST in a real
program, and our first project where clean interfaces and memory discipline
mattered as much as the feature list.

---

## Customizing the shell

Almost everything user-facing lives in [`includes/config.h`](includes/config.h),
so you can tweak the shell without touching the code. It is organized in
labelled sections:

- **Shell name** — `SHELL_NAME` changes the name used in messages and prompts.
- **Feature flags** — enable or disable wildcard expansion, variable expansion,
  interactive-terminal-only mode (`FLAG_ATTY_ONLY`), the startup banner and
  logical negation.
- **Builtins** — each builtin (`FLAG_BUILTIN_CD`, `FLAG_BUILTIN_ECHO`,
  `FLAG_BUILTIN_ENV`, `FLAG_BUILTIN_EXPORT`, `FLAG_BUILTIN_PWD`,
  `FLAG_BUILTIN_EXIT`, `FLAG_BUILTIN_UNSET`, `FLAG_BUILTIN_DEBUG`,
  `FLAG_BUILTIN_VOID`) can be turned on or off individually.
- **Environment** — toggle the default environment and `SHLVL` handling and
  override the fallback `DEFAULT_PATH`.
- **Readline prompts** — customize the continuation prompts shown for quotes,
  parentheses, heredocs, `&&`, `||` and pipes.
- **Lexer symbols** — change the characters used for expansion (`$`), wildcards
  (`*`, `?`) and quotes.
- **Colors** — edit the ANSI color macros (both raw and readline-safe versions)
  to restyle the prompt and shell output.
- **Messages** — all error, syntax and builtin messages are defines, so you can
  translate or reword them freely.

Flip a flag to `FALSE` (or edit a define) and rebuild with `make re`.

---

**Shellost** — built by two students, one command at a time.
