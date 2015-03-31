#include <node.h>
#include <nan.h>
#include <fcntl.h>
#include <errno.h>

#if defined(__linux__) || defined(__FreeBSD__) || defined(__APPLE__) || defined(_AIX)
# include <sys/ioctl.h>
#endif

using v8::Object;
using v8::Handle;

NAN_METHOD(nonblock) {
  NanScope();
  int fd = args[0]->Uint32Value();
  int set = 1;
  int flags;
  int r;

#if defined(__linux__) || defined(__FreeBSD__) || defined(__APPLE__) || defined(_AIX)
  do
    r = ioctl(fd, FIONBIO, &set);
  while (r == -1 && errno == EINTR);

  if (r) {
    NanThrowError(NanError(strerror(errno), errno));
    NanReturnUndefined();
  }

  NanReturnUndefined();
#else
  do
    r = fncntl(fd, F_GETFL);
  while (r == -1 && errno == EINTR);

  if (r == -1)
    NanThrowError(NanError(strerror(errno), errno));
    NanReturnUndefined();

  if (!!(r & O_NONBLOCK) == !!set)
    NanReturnUndefined();

  flags = r | O_NONBLOCK;

  do
    r = fcntl(fd, F_SETFL, flags);
  while (r == -1 && errno == EINTR);

  if (r)
    NanThrowError(NanError(strerror(errno), errno));
    NanReturnUndefined();

  NanReturnUndefined();
#endif
}
