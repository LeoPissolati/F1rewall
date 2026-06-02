#ifndef TUN_H
#define TUN_H

int tun_open(const char *dev_name);
void tun_configure(const char *dev_name, const char *ip, const char *subnet);

#endif