/*
 * File: bootloader.h
 * Created on: 4/8/2024
 * Author:  Abdallah Alnemr
 *
 */


#ifndef BOOTLOADER_H
#define BOOTLOADER_H

/* ----------------- Includes start -----------------*/
#include "main.h"
/* ----------------- Includes end -----------------*/


/* ----------------- Macro Declarations start -----------------*/
#define BL_DEBUG_UART                &huart2
#define BL_HOST_COMMUNICATION_UART   &huart3
#define CRC_ENGINE_OBJ               &hcrc

#define DEBUG_INFO_DISABLE           0
#define DEBUG_INFO_ENABLE            1
#define BL_DEBUG_ENABLE              DEBUG_INFO_ENABLE

#define BL_HOST_BUFFER_RX_LENGTH     200

#define BL_ENABLE_UART_DEBUG_MESSAGE 0x00
#define BL_ENABLE_SPI_DEBUG_MESSAGE  0x01
#define BL_ENABLE_CAN_DEBUG_MESSAGE  0x02
#define BL_DEBUG_METHOD (BL_ENABLE_UART_DEBUG_MESSAGE)

#define CBL_GET_VER_CMD              0x10
#define CBL_GET_HELP_CMD             0x11
#define CBL_GET_CID_CMD              0x12

/* Get Read Protection Status */
#define CBL_GET_RDP_STATUS_CMD       0x13
#define CBL_GO_TO_ADDR_CMD           0x14
#define CBL_FLASH_ERASE_CMD          0x15
#define CBL_MEM_WRITE_CMD            0x16

/* Enable/Disable Write Protection */
#define CBL_ED_W_PROTECT_CMD         0x17
#define CBL_MEM_READ_CMD             0x18

/* Get Sector Read/Write Protection Status */
#define CBL_READ_SECTOR_STATUS_CMD   0x19
#define CBL_OTP_READ_CMD             0x20

/* Change Read Out Protection Level */
#define CBL_CHANGE_ROP_Level_CMD     0x21

#define CBL_VENDOR_ID                100
#define CBL_SW_MAJOR_VERSION         1
#define CBL_SW_MINOR_VERSION         1
#define CBL_SW_PATCH_VERSION         0

/* CRC_VERIFICATION */
#define CRC_TYPE_SIZE_BYTE           4

#define CRC_VERIFICATION_FAILED      0x00
#define CRC_VERIFICATION_PASSED      0x01

#define CBL_SEND_NACK                0xAB
#define CBL_SEND_ACK                 0xCD

/* Start address of sector2 */
#define FLASH_SECTOR2_BASE_ADDRESS   0x08008000U

#define ADDRESS_IS_INVALID           0x00
#define ADDRESS_IS_VALID             0x01

#define STM32F407_SRAM1_SIZE         (112 * 1024)
#define STM32F407_SRAM2_SIZE         (16 * 1024)
#define STM32F407_SRAM3_SIZE         (64 * 1024)
#define STM32F407_FLASH_SIZE         (1024 * 1024)
#define STM32F407_SRAM1_END          (SRAM1_BASE + STM32F407_SRAM1_SIZE)
#define STM32F407_SRAM2_END          (SRAM2_BASE + STM32F407_SRAM2_SIZE)
#define STM32F407_SRAM3_END          (CCMDATARAM_BASE + STM32F407_SRAM3_SIZE)
#define STM32F407_FLASH_END          (FLASH_BASE + STM32F407_FLASH_SIZE)

/* CBL_FLASH_ERASE_CMD */
#define CBL_FLASH_MAX_SECTOR_NUMBER  12
#define CBL_FLASH_MASS_ERASE         0xFF   

#define INVALID_SECTOR_NUMBER        0x00
#define VALID_SECTOR_NUMBER          0x01
#define UNSUCCESSFUL_ERASE           0x02
#define SUCCESSFUL_ERASE             0x03

#define HAL_SUCCESSFUL_ERASE         0xFFFFFFFFU

/* CBL_MEM_WRITE_CMD */
#define FLASH_PAYLOAD_WRITE_FAILED   0x00
#define FLASH_PAYLOAD_WRITE_PASSED   0x01

#define FLASH_LOCK_WRITE_FAILED      0x00
#define FLASH_LOCK_WRITE_PASSED      0x01

/* CBL_GET_RDP_STATUS_CMD */
#define ROP_LEVEL_READ_INVALID       0x00
#define ROP_LEVE_READL_VALID         0X01

/* CBL_CHANGE_ROP_Level_CMD */
#define ROP_LEVEL_CHANGE_INVALID     0x00
#define ROP_LEVEL_CHANGE_VALID       0X01

#define CBL_ROP_LEVEL_0              0x00
#define CBL_ROP_LEVEL_1              0x01
#define CBL_ROP_LEVEL_2              0x02
/* ----------------- Macro Declarations end -----------------*/


/* ----------------- Data Type Declarations start -----------------*/
typedef enum{
	BL_NACK = 0,
	BL_OK
}BL_Status;

typedef void (*pMainApp)(void);
typedef void (*Jump_Ptr)(void);
/* ----------------- Data Type Declarations end -----------------*/


/* ----------------- Macro Functions Declarations start  -----------------*/
/* ----------------- Macro Functions Declarations end  -----------------*/


/* ----------------- Functions Decleration start -----------------*/
static void bootloader_jump_to_user_app(void);

static void Bootloader_Get_Version(uint8_t *Host_Buffer);
static void Bootloader_Get_Help(uint8_t *Host_Buffer);
static void Bootloader_Get_Chip_Identification_Number(uint8_t *Host_Buffer);
static void Bootloader_Read_Protection_Level(uint8_t *Host_Buffer);
static void Bootloader_Jump_To_Address(uint8_t *Host_Buffer);
static void Bootloader_Erase_Flash(uint8_t *Host_Buffer);
static void Bootloader_Memory_Write(uint8_t *Host_Buffer);
static void Bootloader_Enable_RW_Protection(uint8_t *Host_Buffer);
static void Bootloader_Memory_Read(uint8_t *Host_Buffer);
static void Bootloader_Get_Sector_Protection_Status(uint8_t *Host_Buffer);
static void Bootloader_Read_OTP(uint8_t *Host_Buffer);
static void Bootloader_Change_Read_Protection_Level(uint8_t *Host_Buffer);

static uint8_t Bootloader_CRC_Verify(uint8_t *pData, uint32_t Data_Len, uint32_t Host_CRC);
static void Bootloader_Send_ACK(uint8_t Replay_Len);
static void Bootloader_Send_NACK(void);
static void Bootloader_Send_Data_To_Host(uint8_t *Host_Buffer, uint32_t Data_Len);
static uint8_t Host_Address_Verification(uint32_t Jump_Address);
static uint8_t Perform_Flash_Erase(uint8_t Sector_Numebr, uint8_t Number_Of_Sectors);
/* ----------------- Functions Decleration end -----------------*/


/* -----------------  SW Interfaces Declarations start -----------------*/
BL_Status BL_UART_Fetch_Host_Command(void);
void BL_Print_Message(char *format, ...);
/* -----------------  SW Interfaces Declarations end -----------------*/

#endif /* BOOTLOADER_H */
