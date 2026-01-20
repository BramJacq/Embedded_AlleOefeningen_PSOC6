#include "cyhal.h"
#include "cybsp.h" 
#include "cy_retarget_io.h"
#include "cy_serial_flash_qspi.h"
#include "cycfg_qspi_memslot.h"

#define PACKET_SIZE             (64u)     /* Memory Read/Write size */

#define NUM_BYTES_PER_LINE      (16u)
#define MEM_SLOT_NUM            (0u)      /* Slot number of the memory to use */
#define QSPI_BUS_FREQUENCY_HZ   (50000000lu)
#define FLASH_DATA_AFTER_ERASE  (0xFFu)   /* Flash data after erase */

void check_status(char *message, uint32_t status)
{
    if (0u != status)
    {
        printf("\r\n================================================================================\r\n");
        printf("\nFAIL: %s\r\n", message);
        printf("Error Code: 0x%08X\r\n", (unsigned int)status);
        printf("\r\n================================================================================\r\n");
        
        while(true); 
    }
}


void print_array(char *message, uint8_t *buf, uint32_t size)
{
    printf("\r\n%s (%u bytes):\r\n", message, (unsigned int)size);
    printf("-------------------------\r\n");

    for (uint32_t index = 0; index < size; index++)
    {
        printf("0x%02X ", buf[index]);

        if (0u == ((index + 1) % NUM_BYTES_PER_LINE))
        {
            printf("\r\n");
        }
    }
}



int main(void)
{
    cy_rslt_t result;
	uint8_t tx_buf[PACKET_SIZE] = {'H','e','l','l','o',' ','W','o','r','l','d','!',0};
    uint8_t rx_buf[PACKET_SIZE]; 	
    uint32_t ext_mem_address = 0x00;    
    size_t sectorSize;

    cybsp_init();
    
    __enable_irq();
    
    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);

    printf("\x1b[2J\x1b[;H");
    printf("********* CE228954 - PSoC 6 MCU QSPI Flash Read and Write Using SFDP **********\r\n\n");
    

    cy_serial_flash_qspi_init(&SFDP_SlaveSlot_0, CYBSP_QSPI_D0,
              CYBSP_QSPI_D1, CYBSP_QSPI_D2, CYBSP_QSPI_D3, NC, NC, NC, NC,
              CYBSP_QSPI_SCK, CYBSP_QSPI_SS, QSPI_BUS_FREQUENCY_HZ);

   
    sectorSize = cy_serial_flash_qspi_get_erase_size(ext_mem_address);
    printf("\r\nTotal Flash Size: %u bytes\r\n", cy_serial_flash_qspi_get_size());

    printf("\r\n1. Erasing %u bytes of memory\r\n", sectorSize);
	cy_serial_flash_qspi_erase(ext_mem_address, sectorSize);	
    
    printf("\r\n3. Writing data to memory\r\n");
    result = cy_serial_flash_qspi_write(ext_mem_address, PACKET_SIZE, tx_buf);
    check_status("Writing to memory failed", result);

    printf("\r\n4. Reading back for verification\r\n");
    result = cy_serial_flash_qspi_read(ext_mem_address, PACKET_SIZE, rx_buf);
    check_status("Reading memory failed", result);
    print_array("Received Data", rx_buf, PACKET_SIZE);

    check_status("Read data does not match with written data. Read/Write operation failed.",
    memcmp(tx_buf, rx_buf, PACKET_SIZE));


    for (;;)
    {

    }
}

