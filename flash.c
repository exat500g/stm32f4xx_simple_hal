#include "flash.h"
#include "stm32f4xx.h"

static int getSectorByID(uint8_t sector_id,uint32_t *sector);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Unlocks Flash for write access
  * @param  None
  * @retval None
  */
void flash_unlock(void)
{ 
	FLASH_Unlock(); 
	/* Clear pending flags (if any) */  
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
}
void flash_lock(void)
{ 
	FLASH_Lock();
}

int32_t flash_erase(uint8_t sector_id){
	uint32_t sector;
	if(getSectorByID(sector_id,&sector)!=0)return -1;
	if (FLASH_EraseSector(sector, VoltageRange_3) != FLASH_COMPLETE){
		return -2;
    }
	return 0;
}


int32_t flash_write32(uint32_t addr,uint32_t *data,uint32_t len){
	uint32_t i=0;
	for(i=0;i<len;i++){
		if(FLASH_ProgramWord(addr,data[i]) == FLASH_COMPLETE){
			if ( ((uint32_t*)addr)[0] != data[i] ){
				return -2;
			}
			addr += 4;
		}
	}
	return 0;
}
int32_t flash_write32_force(uint32_t addr,uint32_t *data,uint32_t len){
	uint32_t i=0;
	for(i=0;i<len;i++){
		FLASH_ProgramWord(addr,data[i]);
		addr += 4;
	}
	return 0;
}

int flash_getSectorAttr(uint8_t id,uint32_t *addr,uint32_t *size){
	uint32_t _addr=0x08000000,_size=0,offset=0;
	int ret=0;
	if(id>=12){
		id-=12;
		_addr=0x08100000;
	}
	switch(id){
		case 0:case 1:case 2:case 3:
			_addr+=0;
			_size=0x00004000;
			offset=id;
			break;
		case 4:
			_addr+=0x10000;
			_size=0x00010000;
			offset=id-4;
			break;
		case 5:case 6:case 7:case 8:case 9:case 10:case 11:
			_addr+=0x20000;
			_size=0x00020000;
			offset=id-5;
			break;
		default:
			ret=-1;
			break;
	}
	if(ret==0){
		if(addr)
		addr[0]=_addr+_size*offset;
		if(size)
		size[0]=_size;
	}
	return ret;
}
static int getSectorByID(uint8_t id,uint32_t *sector){
	if(sector==0)return 0;
	if(id<=11){
		sector[0]=0x08*id;
		return 0;
	}else if(id<=23){
		sector[0]=0x20+0x08*id;
		return 0;
	}
	return -1;
}



