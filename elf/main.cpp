//
// Created by chan on 2018/4/3.
//

#include "elf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

#define ALIGN(P, ALIGNBYTES)  (((unsigned long)(P) + (ALIGNBYTES) -1) & ~((ALIGNBYTES) - 1))

int main(int argc, char* argv[]) {

    const char* payload = argv[1];
    const char* target = argv[2];

    struct stat buf;
    stat(payload, &buf);
    int payload_size = buf.st_size;

    stat(target, &buf);
    int target_size = buf.st_size;

    std::cout << "payload: " << payload << " size: " << payload_size << std::endl;
    std::cout << "target: " << target <<  " size: " << target_size << std::endl;

    FILE* payload_file = fopen(payload, "rb");
    FILE* target_file = fopen(target, "rb");

	char *base = new char[2 * target_size + payload_size];
	fseek(target_file, 0, SEEK_SET);
	fread(base, 1, target_size, target_file);

	Elf32_Ehdr  *ehdr = (Elf32_Ehdr *)(base);
	Elf32_Phdr  *phdr = (Elf32_Phdr *)(base + sizeof(Elf32_Ehdr));

    Elf32_Phdr *first_phdr = NULL;
    Elf32_Phdr *last_phdr = NULL;

    std::cout << "find ph, count: " << ehdr->e_phnum << std::endl;
	for (int i = 0; i < ehdr->e_phnum; ++i) {
        std::cout << "index: " << i << " type: " << phdr->p_type << std::endl;
        if (phdr->p_type == PT_LOAD) {
            if (first_phdr == NULL) {
                first_phdr = phdr;
            } else {
                last_phdr = phdr;
            }
            std::cout << "find pt load" << std::endl;
        } else if (phdr->p_type == PT_DYNAMIC) {
            std::cout << "find pt dynamic" << std::endl;
        }
        ++phdr;
	}

    return 0;
}