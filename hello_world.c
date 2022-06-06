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
int counter = 0;

//Function Declaration
void interrupt();
void polling();
int background();
static void interrupt_init(void* context, alt_u32 id);
void egm_init(int period, int egm_period, int egm_pulse_width, int egm_enable);

int main(){

	//Initial Registers & Vars


	int mode = IORD(SWITCH_PIO_BASE, 0) & 0x01;
	printf("Mode is: %d\n", mode);
	mode = 0;
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
	//Interrupt initialize
	alt_irq_register( BUTTON_PIO_IRQ, (void *)0, interrupt_init);
	//ENABLE the Button_PIO_IR
	IOWR( STIMULUS_IN_BASE, 2, 1);

	//int egm_enable;
	int egm_busy;
	//int egm_period;
	//int egm_pulse_width;
	int egm_average_latency;
	int egm_missed;
	int egm_multi;

	int period;
	for (period = 2; period < 5000; period+=2) {

		IOWR(EGM_BASE, 0, 0);
		IOWR(EGM_BASE, 2, period);
		IOWR(EGM_BASE, 3, period/2);
		IOWR(EGM_BASE, 0, 1);
		//egm_init(period, egm_period, egm_pulse_width, egm_enable);
		egm_busy = IORD(EGM_BASE, 1);
		while(egm_busy == 1) {
			background();
			counter++;
		}
		egm_average_latency = IORD(EGM_BASE, 4);
		egm_missed = IORD(EGM_BASE, 5);
		egm_multi = IORD(EGM_BASE, 6);
		printf("Average Latency: %d\nMissed: %d\nMulti: %d\n", egm_average_latency, egm_missed, egm_multi);
	}
	//Check if EGM is active
		//background task call
}

//void egm_init(int period, int egm_period, int egm_pulse_width, int egm_enable){
//	egm_period = IOWR(EGM_BASE, 2, period);
//	egm_pulse_width = IOWR(EGM_BASE, 3, period/2);
//	egm_enable = IOWR(EGM_BASE, 0, 1);
//}

//Polling Code
void polling(){

}

int background(){
	int j;
	int x = 0;
	int grainsize = 4;
	int g_taskProcessed = 0;

	for(j = 0; j < grainsize; j++) {
		g_taskProcessed++;
	}
	return x;
}

