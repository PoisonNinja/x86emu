#pragma once

#include <tinyx86.h>

struct board;

union cpu_register {
    uint32_t regs_32;
    uint16_t regs_16;
    uint8_t regs_8;
};

struct cpu_segment {
    uint32_t base, limit;
    uint16_t selector;
};

/*
 * Not a real representation of the EFLAGS register. Instead, for certain
 * flags, generally the arithmetic flags, the status of the field stores
 * whether we need to recompute the flag status. However, other flags,
 * such as the interrupt and direction flag remain real values.
 */
struct eflags {
    uint8_t carry : 1;
    uint8_t reserved_1 : 1;
    uint8_t parity : 1;
    uint8_t reserved_2 : 1;
    uint8_t adjust : 1;
    uint8_t reserved_3 : 1;
    uint8_t zero : 1;
    uint8_t sign : 1;
    uint8_t trap : 1;
    uint8_t interrupt : 1;
    uint8_t direction : 1;
    uint8_t overflow : 1;
    uint8_t iopl : 2;
    uint8_t nested_task : 1;
    uint8_t reserved_4 : 1;
    uint8_t resume : 1;
    uint8_t vm : 1;
    uint8_t alignment_check : 1;
    uint8_t virtual_interrupt : 1;
    uint8_t virtual_interrupt_pending : 1;
    uint8_t cpuid : 1;
    uint16_t reserved_5 : 10;
};

struct cpu_prefix_state {
    struct cpu_segment* segment;
#define CPU_PREFIX_STATE_OPERAND32(cpu) ((cpu)->prefix_state.operand32 ? 1 : 0)
    uint8_t operand32;
    uint8_t repne;
    uint8_t repe;
};

struct cpu {
    struct board* board;
    union cpu_register ax, bx, cx, dx;
    union cpu_register sp, bp, si, di, ip;
    struct cpu_segment cs, ds, ss, es, fs, gs;
    struct eflags eflags;
    struct cpu_prefix_state prefix_state;
#define CPU_STOPPED 0x0
#define CPU_RUNNING 0x1
#define CPU_HALTED 0x2
    uint8_t state;
};

extern void cpu_cycle(struct cpu* cpu);

extern void cpu_reset(struct cpu* cpu);

extern struct cpu* cpu_create(void);
extern void cpu_destroy(struct cpu* cpu);

extern void cpu_dump(struct cpu* cpu);
