#pragma once

#include <tinyx86.h>

extern struct memory_region* memory_init_rom(struct board* board, addr_t base,
                                             size_t size);

extern uint8_t rom_read_u8(struct memory_region* region, addr_t addr);
extern void rom_write_u8(struct memory_region* region, addr_t addr,
                           uint8_t value);

extern uint16_t rom_read_u16(struct memory_region* region, addr_t addr);
extern void rom_write_u16(struct memory_region* region, addr_t addr,
                           uint16_t value);
