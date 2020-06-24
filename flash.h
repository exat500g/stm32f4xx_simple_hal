#pragma once

#include <stdint.h>
#include <stm32f4xx_flash.h>

//STM32F4 only
#define FLASH_SECTOR1_ADDR 0x08004000
#define FLASH_SECTOR2_ADDR 0x08008000
#define FLASH_SECTOR3_ADDR 0x0800C000

void flash_unlock(void);
void flash_lock(void);
int32_t flash_erase(uint8_t sector_id); //FLASH_Sector_3
int flash_getSectorAttr(uint8_t id,uint32_t *addr,uint32_t *size);
int32_t flash_write32(uint32_t addr,uint32_t *data,uint32_t len);
int32_t flash_write32_force(uint32_t addr,uint32_t *data,uint32_t len);
