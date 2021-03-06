/* interrupts.c: i386-interrupt-handling
 * Copyright © 2011 Lukas Martini
 *
 * This file is part of Xelix.
 *
 * Xelix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Xelix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Xelix. If not, see <http://www.gnu.org/licenses/>.
 */

#include <lib/generic.h>
#include <interrupts/interface.h>
#include "idt.h"

#define EOI_MASTER 0x20
#define EOI_SLAVE  0xA0

#define sendEOI(w) outb(w, 0x20)

/* Gets called from interrupts.asm and calls the generic interrupt
 * handler in src/interrupts/interrupts.c.
 * 
 * Only here for EOIs.
 */
cpu_state_t* __attribute__((__cdecl__)) interrupts_firstCallBack(cpu_state_t* regs)
{
	// Spurious interrupts
	if(regs->interrupt == IRQ7)
		return regs;
	if(regs->interrupt == IRQ15)
	{
		/* We have to EOI the master PIC because it can't know it's
		 * only a spurious interrupt
		 */
		sendEOI(EOI_MASTER);
		return regs;
	}
	
	// Is this an IRQ?
	if(regs->interrupt > 31)
	{
		// If this IRQ involved the slave, send a EOI to the slave.
		if (regs->interrupt >= 40)
			sendEOI(EOI_SLAVE);

		sendEOI(EOI_MASTER); // Master
	}
	
	return interrupts_callback(regs);
}

void arch_interrupts_init()
{
	idt_init();
}
