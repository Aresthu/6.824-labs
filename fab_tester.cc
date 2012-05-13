#include <cstdio>
#include <string>
#include "extent_client.h"

using namespace std;

int main(int argc, char* argv[]) {
  printf("creating extent client for address %s ...\n", argv[1]);
  extent_client ec(argv[1]);
  printf("done");

  extent_protocol::extentid_t id = atoi(argv[3]);

  if (strcmp(argv[2], "put") == 0) {
    printf("calling put for eid %lld with \"%s\" ...\n", id, argv[4]);
    int r = ec.put(id, argv[4]);
    ec.flush(id);
    printf("result: %d\n", r);
  } else if (strcmp(argv[2], "get") == 0) {
    printf("calling get for eid %lld...\n", id);
    string s;
    int r = ec.get(id, s);
    printf("result: %d, val \"%s\"\n", r, s.c_str());
  } else if (strcmp(argv[2], "remove") == 0) { 
    printf("calling remove for eid %lld...\n", id);
    int r = ec.remove(id); 
    ec.flush(id);
    printf("result: %d\n", r);
  } else if (strcmp(argv[2], "getattr") == 0) {
    printf("calling getattr for eid %lld...\n", id);
    extent_protocol::attr attr;
    int r = ec.getattr(id, attr); 
    printf("result: %d, atime: %u, mtime: %u, ctime: %u size: %u\n", r,
        attr.atime, attr.mtime, attr.ctime, attr.size);
  } else {
    printf("unknown command: %s\n", argv[2]);
  }

  return 0;
}
