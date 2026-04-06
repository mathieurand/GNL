*This project has been created as part of the 42 curriculum by tokyrand.*

# Get Next Line

## Description
`get_next_line` is a C function that reads from a file descriptor (`fd`) and returns **exactly one line per call**, while keeping the reading state between calls using a `static` variable.

Project goals:
- understand and use static variables;
- handle low-level input with `read`;
- manage dynamic memory safely;
- keep correct behavior for different buffer sizes (`BUFFER_SIZE`).

The function must return:
- a string containing the line (including `\n` when present),
- `NULL` when there is nothing left to read or when an error occurs.

---

## Instructions

### Mandatory files
- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`

### Bonus files
- `get_next_line_bonus.c`
- `get_next_line_utils_bonus.c`
- `get_next_line_bonus.h`

### Compilation (mandatory)
Example with `BUFFER_SIZE=42`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

Compilation without explicitly defining `BUFFER_SIZE` (default value set in the header):

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c
```

### Quick `main.c` test example
Use this minimal `main.c` to test line-by-line reading:

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
	{
		printf("Usage: %s <file>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

Compile and run:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c && ./a.out test1
```

### Testing
Recommended test cases:
- empty files;
- files with and without final `\n`;
- very long lines;
- very small (`1`) and very large `BUFFER_SIZE`;
- multiple file descriptors (bonus).

---

## Selected algorithm and justification

### Core idea
The implementation uses a **persistent storage string** (`stash` which I called `cloud`) across calls:

1. Read chunks of `BUFFER_SIZE` bytes with `read`.
2. Append each chunk to `cloud`.
3. Stop reading as soon as `\n` is found in `cloud` (or on EOF).
4. Extract one output line from `cloud`.
5. Keep the remaining part of `cloud` for the next call.

### Why this approach
- It follows the subject requirement: incremental reading instead of loading the full file.
- It is efficient: already-read data is reused and not read again.
- It is robust for common edge cases (EOF, file without trailing newline, long lines).
- It directly demonstrates the intended use of `static` state.

### Mandatory flow details
- `get_everything(fd, cloud)`: reads and fills `cloud` until a newline (`SEP`) is found or reading ends.
- `extract_line(&cloud)`: builds the output line (including `SEP` when available) and updates `cloud` with the remaining data.
- `ft_strchr(cloud)`: checks whether `cloud` already contains `SEP` to stop reading early.

### Bonus: multiple FDs with one static variable
To support multiple file descriptors simultaneously, the bonus version stores per-`fd` state in an indexed structure (for example, an array of pointers), while keeping a single `static` declaration in `get_next_line`.
Each `fd` has its own `cloud`, allowing alternating calls (`fd 3`, then `fd 4`, then `fd 3`, etc.) without mixing states.

### Complexity (high-level)
- Time: proportional to the total number of bytes read.
- Memory: proportional to the current line size plus unconsumed remainder.

---

## Resources

### Technical references
- `read(2)` manual: https://man7.org/linux/man-pages/man2/read.2.html
- `malloc(3)` / `free(3)` manual: https://man7.org/linux/man-pages/man3/malloc.3.html
- `open(2)` manual: https://man7.org/linux/man-pages/man2/open.2.html
- C reference (strings, memory): https://en.cppreference.com/w/c

### AI usage
AI was used only as a **learning support tool** to:
- verify the README structure against the subject.
