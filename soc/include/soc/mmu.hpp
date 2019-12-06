#pragma once

#include <list>
#include <systemc.h>

#define MMU_ENTRY_READ (1 << 0)
#define MMU_ENTRY_WRITE (1 << 1)
#define MMU_ENTRY_EXEC (1 << 2)

#define MMU_ENTRY_PTR ((1 << 3) & ~(1 << 4))
#define MMU_ENTRY_CB (~(1 << 3) & (1 << 4))
#define MMU_ENTRY_ALLOC (MMU_ENTRY_PTR | (1 << 5))

#define MMU_ENTRY_RW (MMU_ENTRY_READ | MMU_ENTRY_WRITE)
#define MMU_ENTRY_RWE (MMU_ENTRY_RW | MMU_ENTRY_EXEC)
#define MMU_ENTRY_RE (MMU_ENTRY_READ | MMU_ENTRY_EXEC)

typedef sc_uint<32> (*mmu_read)(sc_uint<32> address);
typedef int (*mmu_write)(sc_uint<32> address, sc_uint<32> data);

typedef struct {
	sc_uint<32> address;
	sc_uint<32> size;
	sc_uint<8> flags;

	mmu_read read;
	mmu_write write;
	void* ptr;
} mmu_entry_t;

#define MMU_ERROR_NONE 0
#define MMU_ERROR_NOT_MAPPED 1
#define MMU_ERROR_MAPPED 2
#define MMU_ERROR_PERMISSION 3

#define MMU_SIZE_RAM (10*1024*1024)

#define MMU_ADDR_RAM (2*1024)

SC_MODULE(mmu) {
	public:
		SC_CTOR(mmu) {
			this->map(MMU_ADDR_RAM, MMU_SIZE_RAM, MMU_ENTRY_RWE);
		}

		virtual int write(sc_uint<32> address, sc_uint<32> data);
		virtual sc_uint<32> read(sc_uint<32> address);
		virtual mmu_entry_t get_mapped_foraddress(sc_uint<32> address);
		virtual void map(sc_uint<32> address, sc_uint<32> size, uint8_t flags);
		virtual void map(sc_uint<32> address, sc_uint<32> size, uint8_t flags, void* ptr);
		virtual void map(sc_uint<32> address, sc_uint<32> size, uint8_t flags, mmu_read read, mmu_write write);
		virtual void unmap(sc_uint<32> address);
	private:
		std::list<mmu_entry_t> entries;
};