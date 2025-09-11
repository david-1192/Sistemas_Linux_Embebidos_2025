#ifndef MONITOR_H
#define MONITOR_H

typedef struct {
    unsigned long total;
    unsigned long available;
    unsigned long swap_total;
    unsigned long swap_free;
} MemoryInfo;

typedef struct {
    char model[256];
    int cores;
} CPUInfo;

typedef struct {
    double usage;
} CPUUsage;

MemoryInfo read_memory_info();
CPUInfo read_cpu_info();
void calculate_cpu_usage(CPUUsage *usage, int core_count);
void display_info(MemoryInfo mem, CPUInfo cpu, CPUUsage *usage, int core_count);

#endif