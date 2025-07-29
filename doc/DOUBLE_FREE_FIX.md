# Double-Free Fix Guide

## The Problem
The Valgrind output shows:
```
==68168== Invalid free() / delete / delete[] / realloc()
==68168==    at 0x484499B: operator delete(void*, unsigned long)
```

This indicates a double-free error, likely in std::string destructors during program shutdown.

## Solutions:

### 1. Static Object Management
Ensure static/global string objects are properly managed:

```cpp
// Instead of global strings like:
std::string globalLogPath;  // BAD - can cause shutdown issues

// Use static local variables or smart pointers:
const std::string& getLogPath() {
    static std::string logPath;  // BETTER - guaranteed initialization order
    return logPath;
}

// Or use dynamic allocation for critical strings:
std::unique_ptr<std::string> logPath;
```

### 2. String Assignment Safety
```cpp
// Replace unsafe assignments with safer alternatives:
// Instead of:
logPath = someOtherString;  // Can cause issues if strings have different allocators

// Use:
logPath.assign(someOtherString);
// Or:
logPath = std::string(someOtherString);
```

### 3. Logger Cleanup
The issue seems to be in xit::IO::Logger. Ensure proper cleanup:

```cpp
// In Logger destructor:
Logger::~Logger() {
    Stop();  // Ensure cleanup before destruction
    // Clear string members safely
    if (!logPath.empty()) {
        logPath.clear();
    }
}
```

### 4. Exit Handling
```cpp
// Register cleanup handlers for proper shutdown:
std::atexit([]() {
    // Cleanup critical resources before exit
    Logger::GetInstance().Stop();
});
```
