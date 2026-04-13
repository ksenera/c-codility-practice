# c-codility-practice

C/C++ interview prep engine. Built for GM Codility + beyond.
Derives DSA families from first principles in C first, C++ later.
Feeds directly into the Obsidian "god mode" vault — no duplicate logging.

---

## Stack

| Tool | Purpose |
|------|---------|
| C (gcc) | Primary drill language — GM Codility target |
| C++ (g++) | Added later for OOP pattern drills |
| GDB | Register-level memory inspection during pointer drills |
| Valgrind | Memory leak detection |
| Docker | Isolated ARM64 Ubuntu environment (matches Raspberry Pi architecture) |
| Git | Version control — commit log doubles as learning history |
| Obsidian | "god mode" vault — logger writes problem notes directly into it |

---

## Repo Structure

```
c-codility-practice/
├── Dockerfile              # ARM64 Ubuntu 22.04 + gcc + g++ + gdb + valgrind
├── Makefile                # compile any .c or .cpp file with one command
├── run.sh                  # launches Docker with both mounts (code + vault)
├── logger.c                # C program — prompts scaffold questions, writes to Obsidian
├── .gitignore              # ignores *.out *.o a.out binaries
├── README.md               # this file
│
├── Encoding/               # blank recall sessions — no reference allowed
├── Reference/              # C/C++ vocab, mechanics, pointer notes
├── Tracking/               # session_log.txt — raw terminal error log
│
├── hashmap/                # HashMap family — count, track, lookup
├── two_pointers/           # Two Pointers family — sorted arrays, pairs
├── sliding_window/         # Sliding Window family — subarray problems
├── linked_list/            # Linked List family — pointer manipulation
├── trees/                  # Trees family — recursion, DFS, BFS
├── stack/                  # Stack family — LIFO, monotonic stack
├── graphs/                 # Graphs family — BFS, DFS, connected components
└── dp/                     # DP family — memoization, tabulation
```

Each family folder contains:
```
family/
├── solution.c          # derived implementation — blank IDE, no reference
├── solution_test.c     # assert-based TDD test file
└── notes.md            # invariant, anchor sentence, error log for this family
```

---

## Obsidian Integration

Vault path: `/Users/kushikasenera/god mode`

The logger writes `.md` files matching `tpl-problem.md` format directly into:
```
/vault/02_PROBLEMS/LC-XXXX-Problem-Name.md
```

Inside Docker the vault is mounted at `/vault`. Open Obsidian and the note
is already there — YAML frontmatter intact, linkable to `03_KERNELS/`.

### Mount both volumes (already in run.sh)
```bash
docker run -it --rm \
  -v $(pwd):/code \
  -v "/Users/kushikasenera/god mode":/vault \
  c-practice
```

### Verify vault is mounted inside Docker
```bash
ls /vault
# should show: 01_DAILY  02_PROBLEMS  03_KERNELS  04_ERRORS  05_VARIANTS  06_DASHBOARDS
```

### Logger output format (matches tpl-problem.md)
```markdown
---
type: problem
status: draft
created: 2026-04-12 23:45
kernel_guess: graphs
errors: []
variants: []
---

Clues:: n nodes, edges list, count groups
Invariant:: visit neighbors you haven't seen, increment counter per new start
Result::
Links_kernels:: [[BFS-DFS-Graphs-Grids-]]
Links_recording::

## Plan
- Kernel chosen & why: BFS/DFS — count disconnected groups
- State / invariant: visited[] array, iterate all nodes

## Reflection
- What slowed me?
- Next time prompt:
```

---

## Docker Setup

### What the Dockerfile does
ARM64 Ubuntu 22.04 + gcc + g++ + gdb + valgrind.
ARM64 = M1 Mac runs it natively, no emulation, same arch as Raspberry Pi.

### Build image (one time, or after Dockerfile changes)
```bash
docker build -t c-practice .
```

### Start a session (use run.sh — mounts both code and vault)
```bash
cd ~/c-codility-practice
./run.sh
```

Or manually:
```bash
docker run -it --rm \
  -v $(pwd):/code \
  -v "/Users/kushikasenera/god mode":/vault \
  c-practice
```

### Docker flag reference
```
docker build
  -t c-practice       tag/name the image "c-practice"
  .                   build context = current directory (finds Dockerfile here)

docker run
  -i                  interactive — keeps stdin open so you can type
  -t                  allocate a pseudo-terminal (makes it feel like a real shell)
  -it                 always together for interactive sessions
  --rm                delete container on exit — state lives in mounted files not container
  -v $(pwd):/code     Mac's c-codility-practice/ appears at /code inside Docker
  -v "path":/vault    Mac's Obsidian vault appears at /vault inside Docker
  $(pwd)              shell expands to absolute path of current directory
```

### Confirm you're inside Docker
```
kushikasenera@e6:e4:f0:e0:e6:94 ~%     <- Mac terminal
root@696fdfb6224d:/code#                <- inside Docker
```

---

## Compile & Run

### Makefile (preferred)
```bash
make graphs/solution.out        # compiles graphs/solution.c with -Wall -Wextra -g
./graphs/solution.out           # run it
make clean                      # delete all .out binaries
```

### Manual gcc
```bash
gcc -Wall -Wextra -g -o solution solution.c && ./solution
```

### With GDB — register inspection and memory viewing
```bash
gcc -g -o solution solution.c       # must compile with -g for debug symbols
gdb ./solution
(gdb) layout regs                   # open register dashboard — watch rax rsp rip live
(gdb) break main                    # set breakpoint at main
(gdb) run                           # execute — stops at breakpoint
(gdb) next                          # step one line forward
(gdb) print x                       # print value of variable x
(gdb) x/8xb &variable              # dump 8 raw bytes at variable's memory address
(gdb) x/4xw &arr                   # dump array as 4 hex words
(gdb) quit
```

### With Valgrind — memory leak detection
```bash
valgrind --leak-check=full ./solution
# "definitely lost: 0 bytes" = clean
# anything else = memory leak — fix before committing
```

---

## Compile Flag Reference
```
-Wall       all standard warnings
-Wextra     extra warnings Wall misses (unused params, missing return, etc.)
-g          embed debug symbols — required for GDB to show variable names + line numbers
-o name     name the output binary (default is a.out if omitted)
&&          run second command only if first succeeds
```

---

## Important Linux Commands (inside Docker)

### Navigation
```bash
pwd                     # print working directory — absolute path of where I am
ls                      # list files in current directory
ls -la                  # list all files including hidden, with permissions + sizes
cd /code                # go to mounted C project
cd /vault               # go to mounted Obsidian vault
cd /vault/02_PROBLEMS   # go directly to problems folder in vault
cd ..                   # go up one directory
```

### File operations
```bash
touch file.c            # create empty file
mkdir foldername        # create directory
cp src dest             # copy file
mv src dest             # move or rename file
rm file                 # delete file (no undo)
cat file.c              # print file contents to terminal
head -20 file.c         # print first 20 lines
```

### Search and inspect
```bash
grep "malloc" errors.txt            # find lines containing "malloc"
grep -r "visited" graphs/           # search recursively in folder
grep -n "TODO" solution.c           # show line numbers with matches
find . -name "*.c"                  # find all .c files from current directory
find . -name "*.md"                 # find all markdown files
wc -l solution.c                    # count lines in file
```

### Compilation shortcuts
```bash
gcc -Wall -Wextra -g -o prog prog.c && ./prog     # compile and run in one line
make clean && make graphs/solution.out             # clean then recompile
```

### Git (run from Mac terminal, not inside Docker)
```bash
git status                          # what changed?
git add file.c                      # stage specific file
git add .                           # stage everything
git commit -m "feat(graphs): LC323 connected components"
git push                            # push to github
git log --oneline                   # compact commit history
git diff file.c                     # what changed since last commit
```

---

## TDD — Assert Based (current tier)

```c
#include <assert.h>

// write asserts BEFORE implementing the function — TDD
assert(count_components(5, edges1, 3) == 2);
assert(count_components(5, edges2, 4) == 1);

// assert passes = silent
// assert fails  = crash with file + line number printed
```

Rule: zero gcc warnings before committing. Zero valgrind leaks before committing.
Next tier: Unity framework after first 3 problems solved.

---

## Logger — Scaffold Prompts

`./logger` asks these questions in order, then writes a formatted `.md` to `/vault/02_PROBLEMS/`:

```
1. Problem name + number?       → filename + title
2. Family prediction?           → kernel_guess (YAML)
3. Signal — what triggered it?  → Clues::
4. Invariant — one sentence?    → Invariant::
5. What slowed you?             → Reflection: What slowed me?
6. Next time prompt?            → Reflection: Next time prompt:
```

---

## Drill Protocol (per problem)

```
1. PREDICTION   → what family? say it before reading fully
2. SIGNAL       → what word/pattern triggered that?
3. SCAFFOLD     → plain English — what does one step do?
4. ASSERTS      → write expected input/output as assert() calls
5. IMPLEMENT    → blank editor, no reference
6. COMPILE      → gcc -Wall -Wextra — zero warnings
7. VALGRIND     → zero leaks
8. LOG          → ./logger writes note to /vault/02_PROBLEMS/
9. COMMIT       → git commit with conventional commit message
```

---

## Git Commit Taxonomy

```
feat(family):       new problem implementation
  feat(graphs):     LC323 connected components
  feat(dp):         LC64 minimum path sum
fix(family):        bug fix in existing solution
build(docker):      Dockerfile or run.sh changes
build(make):        Makefile changes
docs(readme):       documentation updates
refactor:           restructure without behaviour change
test:               adding or fixing assert-based tests
chore:              gitignore, cleanup, non-code changes
```

---

## Problem List — GM Codility Target

| Freq | Problem | Difficulty | Family | Status |
|------|---------|-----------|--------|--------|
| 100% | Connected Components (LC323) | Medium | Graphs | 🔲 |
| 64.4% | First Missing Positive (LC41) | Hard | Array | 🔲 |
| 64.4% | Minimum Path Sum (LC64) | Medium | DP | 🔲 |
| 56.8% | LRU Cache (LC146) | Medium | Design | 🔲 |
| 56.8% | Full Rounds Played (LC1904) | Medium | Math/String | 🔲 |
| 56.8% | Last Visited Integers (LC2899) | Easy | Array | 🔲 |
| 56.8% | Widest Vertical Area (LC1637) | Easy | Sort | 🔲 |
| 56.8% | Dot Product Sparse Vectors (LC1570) | Medium | Two Pointers | 🔲 |

---

## Anchor Sentences

```
GRAPHS:       "visit neighbors you haven't seen — visited[] is the lock"
HASHMAP:      "array indexed by value — O(1) store and retrieve"
TWO POINTERS: "squeeze inward until they meet"
SLIDING WIN:  "expand right until broken, shrink left until fixed"
LINKED LIST:  "save next, reverse pointer, slide forward"
STACK:        "last in first out — what did I just push?"
DP:           "current answer depends on previous answer — fill the table"
TREES:        "ask None, ask one node, combine children"
```

---

## Status
- [x] Docker environment built (gcc + g++ + gdb + valgrind)
- [x] Obsidian vault mounted at /vault via run.sh
- [x] Folder structure created (8 families + Encoding + Reference + Tracking)
- [x] Makefile added
- [x] Git repo live — github.com/ksenera/c-codility-practice
- [ ] logger.c — you are writing this now
- [ ] warmup.c — C phoneme drill
- [ ] LC323 Connected Components
- [ ] LC41 First Missing Positive
- [ ] LC64 Minimum Path Sum
- [ ] LC146 LRU Cache