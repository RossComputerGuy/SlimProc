#include <soc/mmu.hpp>
#include <stdexcept>

int mmu::write(sc_uint<32> address, sc_uint<32> data) {
	mmu_entry_t entry = this->get_mapped_foraddress(address);
	if (entry.address == 0 && entry.size == 0) throw MMU_ERROR_NOT_MAPPED;
	if (!(entry.flags & MMU_ENTRY_WRITE)) throw MMU_ERROR_PERMISSION;
	if (entry.flags & MMU_ENTRY_PTR) {
		*(unsigned long*)((uintptr_t)entry.ptr + (entry.address - address)) = data;
		return 0;
	}
	if (entry.flags & MMU_ENTRY_CB) return entry.write(entry.address - address, data);
	return 0;
}

sc_uint<32> mmu::read(sc_uint<32> address) {
	mmu_entry_t entry = this->get_mapped_foraddress(address);
	if (entry.address == 0 && entry.size == 0) throw MMU_ERROR_NOT_MAPPED;
	if (!(entry.flags & MMU_ENTRY_READ)) throw MMU_ERROR_PERMISSION;
	if (entry.flags & MMU_ENTRY_PTR) return sc_uint<32>(*(unsigned long*)((uintptr_t)entry.ptr + (entry.address - address)));
	if (entry.flags & MMU_ENTRY_CB) return entry.read(entry.address - address);
	return 0;
}

mmu_entry_t mmu::get_mapped_foraddress(sc_uint<32> address) {
	for (auto it = this->entries.begin(); it != this->entries.end(); it++) {
		mmu_entry_t entry = *it;
		if (entry.address >= address && (entry.size + entry.address) < address) return entry;
	}
	return { 0, 0, 0, NULL, NULL, NULL };
}

void mmu::map(sc_uint<32> address, sc_uint<32> size, uint8_t flags) {
	for (sc_uint<32> i = 0; i < size; i++) {
		mmu_entry_t entry = this->get_mapped_foraddress(address + i);
		if (entry.address != 0 && entry.size != 0) throw MMU_ERROR_MAPPED;
	}
	mmu_entry_t entry = {
		address, size, flags | MMU_ENTRY_ALLOC,
		NULL, NULL, malloc(size)
	};
	if (entry.ptr == NULL) throw std::runtime_error("Failed to allocate memory");
	this->entries.push_back(entry);
}

void mmu::map(sc_uint<32> address, sc_uint<32> size, uint8_t flags, void* ptr) {
	for (sc_uint<32> i = 0; i < size; i++) {
		mmu_entry_t entry = this->get_mapped_foraddress(address + i);
		if (entry.address != 0 && entry.size != 0) throw MMU_ERROR_MAPPED;
	}
	mmu_entry_t entry = {
		address, size, flags | MMU_ENTRY_PTR,
		NULL, NULL, ptr
	};
	this->entries.push_back(entry);
}

void mmu::map(sc_uint<32> address, sc_uint<32> size, uint8_t flags, mmu_read read, mmu_write write) {
	for (sc_uint<32> i = 0; i < size; i++) {
		mmu_entry_t entry = this->get_mapped_foraddress(address + i);
		if (entry.address != 0 && entry.size != 0) throw MMU_ERROR_MAPPED;
	}
	mmu_entry_t entry = {
		address, size, flags | MMU_ENTRY_CB,
		read, write, NULL
	};
	this->entries.push_back(entry);
}

void mmu::unmap(sc_uint<32> address) {
	for (auto it = this->entries.begin(); it != this->entries.end(); it++) {
		mmu_entry_t entry = *it;
		if (entry.address >= address && (entry.size + entry.address) < address) {
			this->entries.erase(it);
			return;
		}
	}
	throw MMU_ERROR_MAPPED;
}