# Memory Safety Compilation Flags
# Add these to your xmakefile.json or Makefile

## Debug Build Flags
-g3                    # Maximum debug information
-O0                    # No optimization for easier debugging
-fsanitize=address     # AddressSanitizer for memory errors
-fsanitize=undefined   # UndefinedBehaviorSanitizer
-fno-omit-frame-pointer # Keep frame pointers for better stack traces

## Warning Flags
-Wall                  # Enable all warnings
-Wextra               # Extra warning flags  
-Wuninitialized       # Warn about uninitialized variables
-Winit-self           # Warn about self-initialization
-Wmaybe-uninitialized # Warn about possibly uninitialized variables
-Wshadow              # Warn about variable shadowing
-Wnull-dereference    # Warn about null pointer dereferences

## Memory Safety Runtime Flags
-fstack-protector-strong  # Stack protection
-D_FORTIFY_SOURCE=2      # Runtime buffer overflow detection

## Example usage in xmake:
# set_warnings("all", "extra")
# add_cxxflags("-fsanitize=address", "-fsanitize=undefined")
# add_ldflags("-fsanitize=address", "-fsanitize=undefined")
