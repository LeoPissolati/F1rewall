#include "tun.h"

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

int tun_open(const char *dev_name) {
    struct ifreq ifr;
    int fd;

    fd = open("/dev/net/tun", O_RDWR);
    if (fd < 0) {
        perror("Erro ao abrir /dev/net/tun");
        return -1;
    }

    memset(&ifr, 0, sizeof(ifr));

    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;

    if (dev_name != NULL) {
        strncpy(ifr.ifr_name, dev_name, IFNAMSIZ - 1);
        ifr.ifr_name[IFNAMSIZ - 1] = '\0';
    }

    if (ioctl(fd, TUNSETIFF, (void *)&ifr) < 0) {
        perror("Erro no ioctl TUNSETIFF");
        close(fd);
        return -1;
    }

    printf("[TUN] Interface '%s' criada com sucesso.\n", ifr.ifr_name);
    return fd;
}

void tun_configure(const char *dev_name, const char *ip, const char *subnet) {
    char cmd[256];

    snprintf(cmd, sizeof(cmd), "ip addr add %s/%s dev %s", ip, subnet, dev_name);
    if (system(cmd) != 0) {
        fprintf(stderr, "Erro ao atribuir IP à interface %s\n", dev_name);
        exit(1);
    }

    snprintf(cmd, sizeof(cmd), "ip link set %s up", dev_name);
    if (system(cmd) != 0) {
        fprintf(stderr, "Erro ao ativar interface %s\n", dev_name);
        exit(1);
    }

    printf("[TUN] Interface '%s' configurada com IP %s/%s e ativada.\n", dev_name, ip, subnet);
}