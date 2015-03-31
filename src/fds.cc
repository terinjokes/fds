#include <node.h>
#include <nan.h>

using v8::Object;
using v8::Handle;
using v8::FunctionTemplate;
using v8::String;

#if defined(_WIN32)
# include "fds-win.h"
#else
# include "fds-unix.h"
#endif

void Init(Handle<Object> exports) {
  exports->Set(NanNew<String>("nonblock"), NanNew<FunctionTemplate>(nonblock)->GetFunction());
}

NODE_MODULE(fds, Init);
