#include <node.h>
#include <nan.h>

using v8::FunctionTemplate;

#if defined(_WIN32)
# include "fds-win.h"
#else
# include "fds-unix.h"
#endif

NAN_MODULE_INIT(Init) {
  Nan::Set(target, Nan::New("nonblock").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(nonblock)).ToLocalChecked());
}

NODE_MODULE(fds, Init);
