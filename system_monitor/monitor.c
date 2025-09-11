#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "monitor.h"

// Función para leer /proc/meminfo
MemoryInfo read_memory_info() {
    MemoryInfo mem = {0};
    FILE *file = fopen("/proc/meminfo", "r");
    if (file == NULL) {
        perror("Error abriendo /proc/meminfo");
        return mem;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "MemTotal:")) {
            sscanf(line, "MemTotal: %lu kB", &mem.total);
        } else if (strstr(line, "MemAvailable:")) {
            sscanf(line, "MemAvailable: %lu kB", &mem.available);
        } else if (strstr(line, "SwapTotal:")) {
            sscanf(line, "SwapTotal: %lu kB", &mem.swap_total);
        } else if (strstr(line, "SwapFree:")) {
            sscanf(line, "SwapFree: %lu kB", &mem.swap_free);
        }
    }
    fclose(file);
    return mem;
}

// Función para leer /proc/cpuinfo
CPUInfo read_cpu_info() {
    CPUInfo cpu = {0};
    FILE *file = fopen("/proc/cpuinfo", "r");
    if (file == NULL) {
        perror("Error abriendo /proc/cpuinfo");
        return cpu;
    }

    char line[256];
    int cores = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "model name")) {
            strncpy(cpu.model, strchr(line, ':') + 2, sizeof(cpu.model) - 1);
            cpu.model[strcspn(cpu.model, "\n")] = '\0';
        } else if (strstr(line, "cpu cores")) {
            sscanf(strchr(line, ':') + 2, "%d", &cpu.cores);
        } else if (strstr(line, "processor")) {
            cores++;
        }
    }
    fclose(file);
    
    if (cpu.cores == 0) {
        cpu.cores = cores;
    }
    
    return cpu;
}

// Función para leer /proc/stat y calcular uso de CPU
void calculate_cpu_usage(CPUUsage *usage, int core_count) {
    static unsigned long long prev_total[32] = {0};
    static unsigned long long prev_idle[32] = {0};
    
    FILE *file = fopen("/proc/stat", "r");
    if (file == NULL) {
        perror("Error abriendo /proc/stat");
        return;
    }

    char line[256];
    int core_index = -1;
    
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "cpu", 3) == 0) {
            if (line[3] == ' ') {
                // CPU total
                unsigned long long user, nice, system, idle, iowait, irq, softirq;
                sscanf(line + 5, "%llu %llu %llu %llu %llu %llu %llu", 
                       &user, &nice, &system, &idle, &iowait, &irq, &softirq);
                
                unsigned long long total = user + nice + system + idle + iowait + irq + softirq;
                unsigned long long total_diff = total - prev_total[0];
                unsigned long long idle_diff = idle - prev_idle[0];
                
                if (prev_total[0] != 0 && total_diff > 0) {
                    usage[0].usage = 100.0 * (total_diff - idle_diff) / total_diff;
                }
                
                prev_total[0] = total;
                prev_idle[0] = idle;
                
            } else if (core_index < core_count - 1) {
                // CPU cores
                core_index++;
                unsigned long long user, nice, system, idle, iowait, irq, softirq;
                sscanf(line + 5, "%llu %llu %llu %llu %llu %llu %llu", 
                       &user, &nice, &system, &idle, &iowait, &irq, &softirq);
                
                unsigned long long total = user + nice + system + idle + iowait + irq + softirq;
                unsigned long long total_diff = total - prev_total[core_index + 1];
                unsigned long long idle_diff = idle - prev_idle[core_index + 1];
                
                if (prev_total[core_index + 1] != 0 && total_diff > 0) {
                    usage[core_index + 1].usage = 100.0 * (total_diff - idle_diff) / total_diff;
                }
                
                prev_total[core_index + 1] = total;
                prev_idle[core_index + 1] = idle;
            }
        }
    }
    fclose(file);
}

// Función para mostrar información en pantalla
void display_info(MemoryInfo mem, CPUInfo cpu, CPUUsage *usage, int core_count) {
    system("clear"); // Limpiar pantalla
    
    printf("=== MONITOR DEL SISTEMA ===\n\n");
    
    // Información de memoria
    printf("MEMORIA:\n");
    printf("  Total instalada: %.2f GB\n", mem.total / 1024.0 / 1024.0);
    printf("  Memoria física usada: %.2f GB (%.1f%%)\n", 
           (mem.total - mem.available) / 1024.0 / 1024.0,
           100.0 * (mem.total - mem.available) / mem.total);
    printf("  Memoria virtual usada: %.2f GB (%.1f%%)\n",
           (mem.swap_total - mem.swap_free) / 1024.0 / 1024.0,
           mem.swap_total > 0 ? 100.0 * (mem.swap_total - mem.swap_free) / mem.swap_total : 0);
    
    // Información del procesador
    printf("\nPROCESADOR:\n");
    printf("  Modelo: %s\n", cpu.model);
    printf("  Núcleos: %d\n", cpu.cores);
    
    // Uso de CPU
    printf("\nCARGA DEL PROCESADOR:\n");
    printf("  Total: %.1f%%\n", usage[0].usage);
    for (int i = 1; i <= core_count; i++) {
        printf("  Núcleo %d: %.1f%%\n", i - 1, usage[i].usage);
    }
}

int main() {
    // Obtener información inicial del CPU
    CPUInfo cpu = read_cpu_info();
    int core_count = cpu.cores;
    
    // Reservar memoria para los usos de CPU (total + núcleos)
    CPUUsage *cpu_usage = malloc((core_count + 1) * sizeof(CPUUsage));
    if (cpu_usage == NULL) {
        perror("Error reservando memoria");
        return 1;
    }
    
    printf("Iniciando monitor del sistema...\n");
    sleep(2);
    
    while (1) {
        MemoryInfo mem = read_memory_info();
        calculate_cpu_usage(cpu_usage, core_count);
        display_info(mem, cpu, cpu_usage, core_count);
        sleep(2);
    }
    
    free(cpu_usage);
    return 0;
}