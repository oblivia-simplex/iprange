#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "iprange.h"

unsigned int ip2int (char *ipstr){
  unsigned short int o0, o1, o2, o3;
  unsigned int ipint;
  if (4 != sscanf(ipstr, "%hd.%hd.%hd.%hd", &o3, &o2, &o1, &o0)){
    fprintf(stderr, "Error parsing IP address: %s\nExiting.\n", ipstr);
    exit(1);
  }
  ipint = (o0) | (o1 << 8) | (o2 << 16) | (o3 << 24);
  return ipint;
}

void int2ip (unsigned int ipint, char *ipstr) {
  unsigned char o[4];
  int i;
  memset(ipstr, 0, 18);
  for (i = 0; i < 4; i++){
    o[i] = ipint & 0xFF;
      ipint >>= 8;
  }
  snprintf(ipstr, 18, "%u.%u.%u.%u", o[3], o[2], o[1], o[0]);
  return;
}

void cidr_min_max(char *cidr, unsigned int *min, unsigned int *max){
  unsigned short int mask, offset;
  int ipint, bitmask, sep = 0;
  char ipstr[18];
  memset(ipstr, 0, 18);

  while (cidr[sep++] != '/' && sep < 18)
    ;
  if (sep == 18 || sep < 7) {
    fprintf(stderr, "Error parsing CIDR: %s\nExiting.\n", cidr);
    exit(1);
  }
  sscanf(cidr+sep, "%hd", &mask);
  sscanf(cidr, "%s", ipstr);
  ipint = ip2int(ipstr);
  offset = 32 - mask;
  bitmask = (0xFFFFFFFF >> offset) << offset;
  *min = ipint & bitmask;
  *max = ipint | (~bitmask);
  return;
}


void cidr_list(char *cidr){
  unsigned int min, max;
  cidr_min_max(cidr, &min, &max);
  list_min_max(min, max);
  return;
}

void list_min_max(unsigned int min, unsigned int max){
  char ipstr[18];
  while (min <= max) {
    int2ip(min++, ipstr);
    printf("%s\n", ipstr);
  }
  return;
}

int main (int argc, char **argv){

  if (argc == 2){
    cidr_list (argv[1]);
    return 0;
  } else if (argc == 3) {
    unsigned int min, max;
    min = ip2int(argv[1]);
    max = ip2int(argv[2]);
    list_min_max(min, max);
    return 0;
  } else {
    fprintf(stderr,"Usage: %s <min-ip> <max-ip>\n           -- or --\n       %s <cidr>\n", argv[0], argv[0]);
    return (1);
  }

}
