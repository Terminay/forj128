#include <nan.h>
#include "forj128.h"

using namespace Nan;
using namespace v8;

NAN_MODULE_INIT(Init) {
    Set(target, New<String>("hash").ToLocalChecked(),
        New<Function>(Hash));
}

NAN_METHOD(Hash) {
    if (info.Length() < 1) {
        ThrowTypeError("Expected one argument");
        return;
    }

    Local<Value> arg = info[0];
    if (!arg->IsString() && !Buffer::HasInstance(arg)) {
        ThrowTypeError("Expected string or Buffer");
        return;
    }

    uint8_t digest[FORJ128_DIGEST_BYTES];

    if (arg->IsString()) {
        Utf8String str(arg);
        forj128((const uint8_t*)*str, str.length(), digest);
    } else {
        char* data = Buffer::Data(arg);
        size_t len = Buffer::Length(arg);
        forj128((const uint8_t*)data, len, digest);
    }

    info.GetReturnValue().Set(CopyBuffer((char*)digest, FORJ128_DIGEST_BYTES).ToLocalChecked());
}

NODE_MODULE(forj128, Init)