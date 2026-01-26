```
┌─────────────────────────────────────────────────────────────────────────────┐

Step 3: Data Loader (Teaching First)
Let me teach you what a data loader does and why, before we code anything.

What is a Data Loader?
A data loader reads a file from disk and returns its contents in memory.

Real-world example:

File on disk: BTCUSDT_1m.csv (100 MB)
What we do: Read it into RAM
Return: Vector of strings (each line of CSV)

Why Do We Need It?

Without buffering (BAD):

std::ifstream file("data.csv");
std::string line;
while (std::getline(file, line)) {  // 1 system call per line
    // Process
}

1 million lines = 1 million system calls
SLOW because syscalls are expensive

With buffering (GOOD):

std::ifstream file("data.csv");
char buffer[65536];                      // 64KB buffer
file.rdbuf()->pubsetbuf(buffer, 65536); // Tell OS to use this buffer
std::string line;
while (std::getline(file, line)) {       // 1 syscall per 64KB!
    // Process
}

1 million lines = ~16 syscalls
FAST because fewer syscalls

File I/O Concepts You Should Know

1. What is a syscall?
   System call = asking OS to do something
   Reading file requires syscall
   Syscalls are slow (context switch to kernel)

2. What is buffering?
   Read 64KB at once (1 syscall)
   Break it into lines (no syscalls)
   Read next 64KB (1 syscall)
   Create 65536-byte buffer on stack
   rdbuf() = get file's buffer object
   pubsetbuf(buffer, size) = use our buffer instead of default
   Now OS reads 65KB chunks, not 1 line at a time
   Much faster!

3. OS Page Cache
   OS caches disk reads
   First read: slow (from disk)
   Second read: fast (from OS cache)

└─────────────────────────────────────────────────────────────────────────────┘
```