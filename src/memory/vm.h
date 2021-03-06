#pragma once

/* Copyright © 2011 Fritz Grimpen
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

struct vm_context;

struct vm_page
{
	enum
	{
		VM_SECTION_STACK,   /* Initial stack */
		VM_SECTION_CODE,    /* Contains program code and is read-only */
		VM_SECTION_DATA,    /* Contains static data */
		VM_SECTION_HEAP,    /* Allocated by brk(2) at runtime */
		VM_SECTION_MMAP,    /* Allocated by mmap(2) at runtime */
		VM_SECTION_KERNEL,  /* Contains kernel-internal data */
		VM_SECTION_UNMAPPED /* Unmapped */
	} section;

	bool readonly:1;
	bool cow:1; /* Copy-on-Write mechanism */
	bool allocated:1;

	void *cow_src_addr;
	void *virt_addr;
	void *phys_addr;
};

typedef void (*vm_iterator_t)(struct vm_context *, struct vm_page *, uint32_t);

/* Initialize vm_kernelContext for paging_init() */
void vm_init();
struct vm_context *vm_kernelContext;
struct vm_context *vm_currentContext;
struct vm_context *vm_processContext;
void *vm_faultAddress;

/* Some callbacks for magic functions */
void (*vm_applyPage)(struct vm_context *, struct vm_page *);

/* Generate new page context */
struct vm_context *vm_new();
struct vm_page *vm_new_page();

int vm_add_page(struct vm_context *ctx, struct vm_page *pg);

struct vm_page *vm_get_page_phys(struct vm_context *ctx, void *phys_addr);
struct vm_page *vm_get_page_virt(struct vm_context *ctx, void *virt_addr);
struct vm_page *vm_get_page(struct vm_context *ctx, uint32_t offset);

/* Remove pages in a specific context by physical or virtual address */
struct vm_page *vm_rm_page_phys(struct vm_context *ctx, void *phys_addr);
struct vm_page *vm_rm_page_virt(struct vm_context *ctx, void *virt_addr);

/* Iterator */
int vm_iterate(struct vm_context *ctx, vm_iterator_t callback);

uint32_t vm_count_pages(struct vm_context *ctx);
void vm_dump_page(struct vm_page *pg);
void vm_dump(struct vm_context *ctx);
void vm_handle_fault(uint32_t code, void *addr, void *instruction);

/* Get/Set cached paging context */
void vm_set_cache(struct vm_context *ctx, void *cache);
void *vm_get_cache(struct vm_context *ctx);

#ifdef __i386__
	#define PAGE_SIZE 4096
	#define VM_ALIGN(x) (typeof(x))(((uint32_t)(x) & 0xFFFFF000) + 0x1000)
#else
	#define PAGE_SIZE 0
	#define VM_ALIGN(x) (x)
#endif
