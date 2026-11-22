*This project was created as part of the 42 curriculum by marisous*

# Table of Contents

1. [Description](#description)
   1. [Algorithm](#algorithm)
   2. [Binary file support (`BINNARY_FILE`)](#binary-file-support-binnary_file)
2. [Instructions](#instructions)
   1. [Standard version](#standard-version)
   2. [Bonus version (multiple file descriptors)](#bonus-version-multiple-file-descriptors)
   3. [Compilation flags](#compilation-flags)
   4. [Testing](#testing)
3. [Resources](#resources)
   1. [Tutorials & references](#tutorials--references)
   2. [AI usage](#ai-usage)
   3. [System setup](#system-setup)


---


# Description

The goal of this project is to implement the function `get_next_line(int fd)`, which reads and returns the next line from a file descriptor one call at a time, preserving state between calls through a `static` variable. The function must handle any `BUFFER_SIZE` supplied at compile time (from 1 up to 500 000 bytes) as well as simultaneous reads from multiple file descriptors (bonus part).

The project is split into two independent versions that share the same public API (`get_next_line`) but differ in their internal state management:

| File(s) | Version |
|---|---|
| `get_next_line.c` + `get_next_line_utils.c` | Standard — single fd, one `static t_gnl` |
| `get_next_line_bonus.c` + `get_next_line_utils_bonus.c` | Bonus — up to `FOPEN_MAX_MJ` (1001) simultaneous fds, static array of `t_gnl` |

Both versions use the same `t_gnl` structure (defined in their respective header) to track the read buffer, the growing line accumulator, and leftover bytes between calls.


## Algorithm

The core loop inside `get_next_line` repeats until a complete line is ready:

1. **Preliminary read** (`preliminary_and_split2` / `_bonus`):
   if no unprocessed bytes remain in the buffer, issue a fresh `read(2)`.
   - `read < 0` → reset state, return `NULL`.
   - `read == 0` (EOF) → if a partial line is pending, set the `read0_1st` / `read0` flag so the loop exits on the next iteration and that last line is returned; if the accumulator is empty, return `NULL` immediately.

2. **Split & accumulate** (`ft_split2` / `_bonus`):
   scan the buffer from the current position (`buff0`) looking for `'\n'`.
   - Append everything up to and including `'\n'` (or end-of-buffer if not found) to the growing `retval` accumulator via `ft_memjoin` / `ft_memjoin_bonus`.
   - Update `leftover` and `buff0` so the next call resumes exactly where this one stopped inside the buffer — no byte is ever re-read or lost.

3. **Exit condition**: the loop breaks when a `'\n'` was found in the buffer *or* when the EOF flag is set.
   A null terminator is then appended (unless `BINNARY_FILE` is set) and the heap pointer is returned to the caller.

**Memory strategy (bonus):** `ft_new_malloc` / `ft_memjoin_bonus` implement an optional capacity-doubling allocator: if the accumulator still has room, the existing buffer is reused in-place with no copy; otherwise the capacity is doubled for large mid-line chunks, keeping the total number of `malloc` calls roughly O(log n) for long lines.


## Binary file support (`BINNARY_FILE`)

Defining `BINNARY_FILE=1` at compile time switches the return mode: instead of appending a `'\0'` terminator, the function returns the raw byte pointer directly from the accumulator.

> [!CAUTION]
> When `BINNARY_FILE=1`, the returned pointer is **not** a C-string. Using `printf("%s", line)` or any `str*` function on it is undefined behaviour.
> To inspect the content you need a byte-level printer such as the `print_memory` function from the Piscine or the system `hexdump` / `xxd` utility.

> [!WARNING]
> **Current limitation — no hard line boundary without a size return value.**
> In binary mode `get_next_line` still uses `'\n'` (byte `0x0A`) as the only line delimiter. Because binary data may not contain `0x0A` for arbitrarily long stretches, the "line" that is returned can span the entire file. More critically, the caller has no way to know how many bytes were returned: the function signature returns a plain `char *` with no accompanying length. Without an additional out-parameter (e.g. `ssize_t *size`) or a wrapper struct, the caller cannot safely determine where the line ends — it must rely on the first `'\n'` it encounters in memory, which may well lie outside the allocated buffer. A proper binary-safe implementation would need to expose that size somehow.


---


# Instructions


## Standard version

Compile and link the two standard files together with your own `main`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl
./gnl
```


## Bonus version (multiple file descriptors)

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
./gnl_bonus
```


## Compilation flags

| Flag | Default | Effect |
|---|---|---|
| `-D BUFFER_SIZE=N` | `42` (standard) / `10` (bonus) | Sets the internal read buffer size. Clamped to `[1, 500000]`. |
| `-D FOPEN_MAX_MJ=N` | `1001` | *(Bonus only)* Maximum number of simultaneously open fds. |
| `-D BINNARY_FILE=1` | `0` | Returns raw bytes without null terminator — see [binary file note](#binary-file-support-binnary_file) above. |


## Testing

> [!NOTE]
> The `Makefile`, `main.c`, `main_bonus.c`, the text fixtures (`text*.txt`, `variable_nls.txt`, `lines_around_10.txt`, `read_error.txt`) and the binary edge-case files in `limits/` are **not part of the submitted version**. They are preserved in the commit just before the final submission and can be restored with:
>
> ```bash
> git checkout a07d479
> ```

Once checked out, the test harness exercises the function against a variety of line-ending patterns and against the binary files in `limits/`. Both test binaries can be built and run under Valgrind to check for memory leaks:

```bash
make
valgrind --leak-check=full ./gnl
valgrind --leak-check=full ./gnl_bonus
```

The Makefile also provides the following utility rules in that commit:

| Rule | Effect |
|---|---|
| `make` / `make all` | Compiles both the standard and bonus test binaries. |
| `make clean` | Removes object files. |
| `make fclean` | Removes object files and binaries. |
| `make re` | `fclean` then `all`. |
| `make norm` | Runs Norminette with reduced output (issues only). |

To return to the submitted version afterwards:

```bash
git checkout main
```


---


# Resources


## Tutorials & references

- [File descriptors and `read(2)` — Linux man pages.](https://www.man7.org/linux/man-pages/man2/read.2.html)
- [Static variables in C — a short explainer.](https://en.wikipedia.org/wiki/Static_variable)
- [`hexdump` / `xxd` reference for inspecting binary output.](https://www.man7.org/linux/man-pages/man1/hexdump.1.html)


## AI usage

For conceptual questions and hints during development I used a ChatGPT project configured with the same CS50-style policy as in the libft project: hints and correctness checks only, no full solutions.

Additionally, I used an AI agent (Google Antigravity) for the following:

- Generating the Doxygen documentation (`@brief`, `@param`, `@return`, `@var`) placed in `get_next_line.h` and `get_next_line_bonus.h`.
- Writing and proofreading this README file.


## System setup

My personal dotfiles (Emacs, Alacritty, tmux) are available at:

<https://github.com/sousamj2/.reticencias.git>

Emacs was the editor used throughout this project. The LSP integration for C (`clangd`) was set up via the `compile_commands.json` generated by the `Makefile`.

