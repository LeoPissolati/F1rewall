#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <fcntl.h>   // open(), O_RDWR
#include <stdio.h>   // perror()
#include <stdlib.h>  // exit()

int tun_fd = open("/dev/net/tun", O_RDWR); //Guarda o file descriptor em uma varíavel interna e faz read and write do arquivo 

if (tun_fd < 0) {
    perror("Erro ao abrir /dev/net/tun");
    exit(1);
}