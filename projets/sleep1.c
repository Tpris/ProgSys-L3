#include <unistd.h>
#include <signal.h>

int main(void) {
  sleep(1);
  raise(9);
  return 0;
}