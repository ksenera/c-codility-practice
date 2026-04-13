# c-codility-practice

C/C++ interview prep engine. Built for GM Codility + beyond.
Drills DSA families in C first, C++ later. Every problem is derived from first principles — no tutorial-following.

---

## Stack

| Tool | Purpose |
|------|---------|
| C (gcc) | Primary drill language — GM Codility target |
| C++ (g++) | Added later for OOP pattern drills |
| GDB | Register-level memory inspection during pointer drills |
| Valgrind | Memory leak detection |
| Docker | Isolated ARM64 compile environment (matches Raspberry Pi) |
| Git | Version control + commit log as learning history |

---

## Repo Structure

```
c-codility-practice/
├── Dockerfile              # ARM64 Ubuntu + gcc + g++ + gdb + valgrind
├── Makefile                # compile any .c or .cpp file
├── run.sh                  # quick compile+run: ./run.sh filename
├── logger.c                # C command-line session logger (argc/argv drill)
├── .gitignore              # ignores *.out *.o binaries
├── README.md               # this file
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

Each folder will contain:
```
family/
├── solution.c          # implementation
├── solution_test.c     # assert-based TDD
└── notes.md            # invariant, scaffold, error log for this family
```

---

## Docker Setup

### What the Dockerfile does
Builds an ARM64 Ubuntu 22.04 container with gcc, g++, gdb, valgrind pre-installed.
ARM64 matches your M1 Mac natively — no emulation overhead.

### Build the image (one time)
```bash
docker build -t c-practice .
```

### Start a session
```bash
cd ~/c-codility-practice
docker run -it --rm -v $(pwd):/code c-practice
```

### Docker flag reference
```
docker build
  -t c-practice     tag/name the image "c-practice"
  .                 build context = current directory (finds Dockerfile here)

docker run
  -i                interactive — keeps stdin open so you can type
  -t                allocate a terminal (makes it feel like a real shell)
  -it               always used together for interactive sessions
  --rm              delete container on exit — keeps things clean, state lives in files
  -v $(pwd):/code   volume mount
                    $(pwd) = your Mac's current directory
                    /code  = where it appears inside the container
                    same files, two views — edit on Mac, compile in Docker
```

### Confirm you're inside Docker
Your prompt changes from:
```
kushikasenera@e6:e4:f0:e0:e6:94 ~%        ← Mac
```
to:
```
root@696fdfb6224d:/code#                   ← inside Docker
```

### Verify tools
```bash
gcc --version
g++ --version
gdb --version
valgrind --version
ls    # should show your folders
```

---

## Compile & Run

### Quick script
```bash
./run.sh hashmap/solution       # compiles hashmap/solution.c and runs it
```

### Makefile
```bash
make hashmap/solution.out       # compiles with -Wall -Wextra -g
./hashmap/solution.out
make clean                      # removes all .out files
```

### Manual gcc
```bash
gcc -Wall -Wextra -g -o solution solution.c && ./solution
```

### With GDB (register inspection)
```bash
gcc -g -o solution solution.c   # -g = include debug symbols
gdb ./solution
(gdb) layout regs               # open register dashboard
(gdb) break main                # set breakpoint at main
(gdb) run                       # execute — watch registers change live
(gdb) x/8xb &variable          # dump raw memory bytes at any variable
(gdb) quit
```

### With Valgrind (memory leak check)
```bash
valgrind --leak-check=full ./solution
```

---

## Compile Flag Reference
```
-Wall       enable all standard warnings
-Wextra     enable extra warnings beyond -Wall
-g          include debug symbols (required for GDB)
-o name     name the output binary
```

---

## Logger
C command-line session logger. Teaches argc/argv, fopen, fprintf, time.h.

```bash
gcc -Wall -Wextra -o logger logger.c
./logger session_log.txt "your note here"
./logger errors.txt "forgot malloc needs sizeof — wrote malloc(Node) not malloc(sizeof(Node))"
grep "malloc" errors.txt    # retrieve by keyword
```

---

## Problem List — GM Codility Target

Pulled from GM's confirmed LeetCode frequency list:

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

## Drill Protocol (per problem)

```
PREDICTION  → what family does this belong to? why?
SIGNAL      → what in the problem triggered that prediction?
SCAFFOLD    → plain English solution before any code
ASSERTS     → write test cases first (TDD)
IMPLEMENT   → blank IDE, no reference
COMPILE     → gcc -Wall -Wextra, zero warnings
LOG         → ./logger errors.txt "what blanked and why"
COMMIT      → git commit -m "feat(graphs): LC323 connected components"
```

---

## Git Commit Taxonomy

```
feat(family):   new problem implementation
fix(family):    bug fix in existing solution
build(docker):  Dockerfile or build system changes
docs(readme):   documentation updates
refactor:       restructure without changing behaviour
test:           adding or fixing assert-based tests
```

---

## Status
- [x] Docker environment built
- [x] GDB + Valgrind installed
- [x] Folder structure created
- [x] Makefile added
- [x] Logger in progress
- [ ] C phoneme warmup (warmup.c)
- [ ] LC323 Connected Components
- [ ] LC41 First Missing Positive
- [ ] LC64 Minimum Path Sum
- [ ] LC146 LRU Cache
