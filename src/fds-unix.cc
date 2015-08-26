#include <nan.h>
#include <fcntl.h>
#include <errno.h>

#if defined(__linux__) || defined(__FreeBSD__) || defined(__APPLE__) || defined(_AIX)
# include <sys/ioctl.h>
#endif

NAN_METHOD(nonblock) {
  int fd = info[0]->Uint32Value();
  int set = 1;
  int r;

#if defined(__linux__) || defined(__FreeBSD__) || defined(__APPLE__) || defined(_AIX)
  do
    r = ioctl(fd, FIONBIO, &set);
  while (r == -1 && errno == EINTR);

  if (r) {
    Nan::ThrowError(strerror(errno));
    return;
  }
#else
  int flags;

  do
    r = fncntl(fd, F_GETFL);
  while (r == -1 && errno == EINTR);

  if (r == -1) {
    Nan::ThrowError(strerror(errno));
    return;
  }

  if (!!(r & O_NONBLOCK) == !!set) {
    return;
  }

  flags = r | O_NONBLOCK;

  do {
    r = fcntl(fd, F_SETFL, flags);
  } while (r == -1 && errno == EINTR);

  if (r) {
    Nan::ThrowError(strerror(errno));
    return;
  }
#endif
}
