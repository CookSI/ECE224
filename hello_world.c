/*
* "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

//Includes
#include <stdio.h>
#include <system.h>
#include <altera_avalon_pio_regs.h>
#include "altera_up_avalon_audio.h"
#include "sys/alt_irq.h"

//Defines

//Structs

//Global Variables
int flag;

//Function Declaration
void interrupt();
void polling();
static void interrupt_init(void* context, alt_u32 id);

int main(){

	//Initial Registers & Vars
	int egm_enable;
	int egm_busy;
	int egm_period;
	int egm_pulse_width;
	int egm_average_latency;
	int egm_missed;
	int egm_multi;

	int counter = 0;

	int mode = IORD(SWITCH_PIO_BASE, 0) & 0x01;
	printf("Mode is: %d\n", mode);
	int mode = 0; //change later
	//Read Switch PIO (0 - Interrupt, 1 - Polling)
	if (mode == 1){
		polling();
	}
	else {
		interrupt();
	}

	//Make BG tasks call

	//Start EGM for each tests run

	//Check EGM for its test run status

	//Print results at end of each test

	//Update registers for next test run

	//Determine if experiment is done

	return 0;
}

//ISR
static void interrupt_init(void* context, alt_u32 id){
	IOWR( RESPONSE_OUT_BASE, 0, 1);
	IOWR( RESPONSE_OUT_BASE, 0, 0);
	IOWR( STIMULUS_IN_BASE, 3, 0x0);
}

//Interrupt Code
void interrupt(){
	alt_irq_register( BUTTON_PIO_IRQ, (void *)0, interrupt_init);
	IOWR( STIMULUS_IN_BASE, 2, 1);
	//Check if EGM is active
		//background task call
}


//Polling Code
void polling(){

}

