#!/usr/bin/env python3
"""
Valgrind Output Analyzer and Summarizer
Analyzes large Valgrind memory check outputs and provides a concise summary.
"""

import re
import sys
from collections import defaultdict, Counter
from typing import Dict, List, Tuple, Set

class ValgrindAnalyzer:
    def __init__(self):
        self.memory_leaks = []
        self.uninitialized_errors = []
        self.context_summary = defaultdict(int)
        self.file_summary = defaultdict(int)
        self.function_summary = defaultdict(int)
        self.error_types = Counter()
        self.total_bytes_leaked = 0
        self.total_blocks_leaked = 0
        self.suppressed_bytes = 0
        self.suppressed_blocks = 0
        
    def parse_valgrind_output(self, content: str):
        """Parse the Valgrind output and extract key information."""
        lines = content.split('\n')
        
        current_error = None
        in_leak_block = False
        in_error_context = False
        
        for i, line in enumerate(lines):
            line = line.strip()
            
            # Parse error summary
            if "ERROR SUMMARY:" in line:
                match = re.search(r'(\d+) errors from (\d+) contexts.*suppressed: (\d+)', line)
                if match:
                    self.total_errors = int(match.group(1))
                    self.total_contexts = int(match.group(2))
                    self.total_suppressed = int(match.group(3))
            
            # Parse suppressions
            if "used_suppression:" in line:
                match = re.search(r'suppressed: ([\d,]+) bytes in (\d+) blocks', line)
                if match:
                    bytes_str = match.group(1).replace(',', '')
                    self.suppressed_bytes += int(bytes_str)
                    self.suppressed_blocks += int(match.group(2))
            
            # Parse memory leaks
            leak_match = re.match(r'==\d+== (\d+) bytes in (\d+) blocks? are (.+?) in loss record', line)
            if leak_match:
                bytes_leaked = int(leak_match.group(1))
                blocks_leaked = int(leak_match.group(2))
                leak_type = leak_match.group(3)
                
                self.memory_leaks.append({
                    'bytes': bytes_leaked,
                    'blocks': blocks_leaked,
                    'type': leak_type,
                    'stack': []
                })
                self.total_bytes_leaked += bytes_leaked
                self.total_blocks_leaked += blocks_leaked
                in_leak_block = True
                continue
            
            # Parse error contexts
            error_context_match = re.match(r'==\d+== (\d+) errors? in context (\d+) of (\d+):', line)
            if error_context_match:
                error_count = int(error_context_match.group(1))
                context_num = int(error_context_match.group(2))
                total_contexts = int(error_context_match.group(3))
                self.context_summary[context_num] = error_count
                in_error_context = True
                continue
            
            # Parse uninitalized value errors
            if "Conditional jump or move depends on uninitialised value" in line:
                self.error_types["Uninitialized Values"] += 1
                if len(lines) > i + 1:
                    next_line = lines[i + 1].strip()
                    func_match = re.search(r'at 0x[A-F0-9]+: (.+?) \((.+?)\)', next_line)
                    if func_match:
                        function = func_match.group(1)
                        location = func_match.group(2)
                        self.uninitialized_errors.append({
                            'function': function,
                            'location': location
                        })
                        self.function_summary[function] += 1
                        # Extract filename
                        if ':' in location:
                            filename = location.split(':')[0]
                            self.file_summary[filename] += 1
            
            # Parse other error types
            if "Invalid read" in line or "Invalid write" in line:
                if "Invalid read" in line:
                    self.error_types["Invalid Read"] += 1
                else:
                    self.error_types["Invalid Write"] += 1
            
            # Parse stack traces for current leak/error
            if in_leak_block and line.startswith('==') and 'at 0x' in line:
                stack_match = re.search(r'at 0x[A-F0-9]+: (.+?) \((.+?)\)', line)
                if stack_match and self.memory_leaks:
                    function = stack_match.group(1)
                    location = stack_match.group(2)
                    self.memory_leaks[-1]['stack'].append({
                        'function': function,
                        'location': location
                    })
                    self.function_summary[function] += 1
                    if ':' in location:
                        filename = location.split(':')[0]
                        self.file_summary[filename] += 1
            
            # End of leak/error block
            if line.startswith('==') and line.endswith('==') and len(line.strip()) == len('==81658=='):
                in_leak_block = False
                in_error_context = False
    
    def generate_summary(self) -> str:
        """Generate a comprehensive summary of the Valgrind analysis."""
        summary = []
        summary.append("🔍 VALGRIND ANALYSIS SUMMARY")
        summary.append("=" * 50)
        summary.append("")
        
        # Overall statistics
        summary.append("📊 OVERALL STATISTICS:")
        summary.append(f"  Total Errors: {getattr(self, 'total_errors', 'N/A')}")
        summary.append(f"  Error Contexts: {getattr(self, 'total_contexts', 'N/A')}")
        summary.append(f"  Suppressed Errors: {getattr(self, 'total_suppressed', 'N/A')}")
        summary.append(f"  Total Memory Leaked: {self.total_bytes_leaked:,} bytes in {self.total_blocks_leaked} blocks")
        summary.append(f"  Suppressed Memory: {self.suppressed_bytes:,} bytes in {self.suppressed_blocks} blocks")
        summary.append("")
        
        # Error types breakdown
        if self.error_types:
            summary.append("🚨 ERROR TYPES:")
            for error_type, count in self.error_types.most_common():
                summary.append(f"  {error_type}: {count} occurrences")
            summary.append("")
        
        # Most problematic files
        if self.file_summary:
            summary.append("📁 MOST PROBLEMATIC FILES:")
            for filename, count in sorted(self.file_summary.items(), key=lambda x: x[1], reverse=True)[:10]:
                summary.append(f"  {filename}: {count} issues")
            summary.append("")
        
        # Most problematic functions
        if self.function_summary:
            summary.append("🔧 MOST PROBLEMATIC FUNCTIONS:")
            for function, count in sorted(self.function_summary.items(), key=lambda x: x[1], reverse=True)[:10]:
                summary.append(f"  {function}: {count} issues")
            summary.append("")
        
        # Memory leak analysis
        if self.memory_leaks:
            leak_types = Counter()
            largest_leaks = []
            
            for leak in self.memory_leaks:
                leak_types[leak['type']] += 1
                largest_leaks.append((leak['bytes'], leak['type'], leak.get('stack', [])))
            
            summary.append("💧 MEMORY LEAK ANALYSIS:")
            summary.append("  Leak Types:")
            for leak_type, count in leak_types.most_common():
                summary.append(f"    {leak_type}: {count} instances")
            
            summary.append("  Largest Leaks:")
            for bytes_leaked, leak_type, stack in sorted(largest_leaks, key=lambda x: x[0], reverse=True)[:5]:
                summary.append(f"    {bytes_leaked} bytes ({leak_type})")
                if stack and len(stack) > 0:
                    summary.append(f"      Origin: {stack[0]['function']} ({stack[0]['location']})")
            summary.append("")
        
        # Uninitialized value errors
        if self.uninitialized_errors:
            summary.append("⚠️  UNINITIALIZED VALUE ERRORS:")
            uninit_files = Counter()
            uninit_functions = Counter()
            
            for error in self.uninitialized_errors:
                uninit_functions[error['function']] += 1
                if ':' in error['location']:
                    filename = error['location'].split(':')[0]
                    uninit_files[filename] += 1
            
            summary.append("  Most affected files:")
            for filename, count in uninit_files.most_common(5):
                summary.append(f"    {filename}: {count} errors")
            
            summary.append("  Most affected functions:")
            for function, count in uninit_functions.most_common(5):
                summary.append(f"    {function}: {count} errors")
            summary.append("")
        
        # Context analysis
        if self.context_summary:
            summary.append("📋 ERROR CONTEXT ANALYSIS:")
            summary.append(f"  Total contexts with errors: {len(self.context_summary)}")
            high_error_contexts = [(ctx, count) for ctx, count in self.context_summary.items() if count > 1]
            if high_error_contexts:
                summary.append("  Contexts with multiple errors:")
                for ctx, count in sorted(high_error_contexts, key=lambda x: x[1], reverse=True)[:5]:
                    summary.append(f"    Context {ctx}: {count} errors")
            summary.append("")
        
        # Recommendations
        summary.append("💡 RECOMMENDATIONS:")
        
        if self.error_types.get("Uninitialized Values", 0) > 0:
            summary.append("  🔸 Initialize all variables before use")
            summary.append("  🔸 Use member initialization lists in constructors")
            summary.append("  🔸 Consider using smart pointers for automatic memory management")
        
        if self.total_bytes_leaked > 0:
            summary.append("  🔸 Review memory allocation and deallocation patterns")
            summary.append("  🔸 Ensure proper cleanup in destructors")
            summary.append("  🔸 Consider RAII principles")
        
        if "strlen" in str(self.function_summary):
            summary.append("  🔸 Check string pointer initialization before strlen() calls")
            summary.append("  🔸 Use std::string instead of raw char* where possible")
        
        summary.append("")
        summary.append("🎯 PRIORITY ACTIONS:")
        
        # Prioritize actions based on error frequency
        if self.file_summary:
            top_file = max(self.file_summary.items(), key=lambda x: x[1])
            summary.append(f"  1. Focus on fixing issues in: {top_file[0]} ({top_file[1]} issues)")
        
        if self.error_types.get("Uninitialized Values", 0) > 5:
            summary.append("  2. Run the string initialization fix script on your codebase")
        
        if self.total_bytes_leaked > 10000:  # > 10KB
            summary.append(f"  3. Address memory leaks ({self.total_bytes_leaked:,} bytes total)")
        
        return "\n".join(summary)

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 analyze_valgrind.py <valgrind_output_file>")
        sys.exit(1)
    
    filename = sys.argv[1]
    
    try:
        with open(filename, 'r') as f:
            content = f.read()
    except Exception as e:
        print(f"Error reading file {filename}: {e}")
        sys.exit(1)
    
    analyzer = ValgrindAnalyzer()
    analyzer.parse_valgrind_output(content)
    
    summary = analyzer.generate_summary()
    print(summary)
    
    # Also save to file
    output_filename = filename.replace('.txt', '_summary.txt')
    try:
        with open(output_filename, 'w') as f:
            f.write(summary)
        print(f"\n📄 Summary also saved to: {output_filename}")
    except Exception as e:
        print(f"\n⚠️  Could not save summary to file: {e}")

if __name__ == "__main__":
    main()
