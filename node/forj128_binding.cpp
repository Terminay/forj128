#include <napi.h>
#include "forj128.h"

namespace {

Napi::Value Hash(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Expected one argument").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Value arg = info[0];
    if (!arg.IsString() && !arg.IsBuffer()) {
        Napi::TypeError::New(env, "Expected string or Buffer").ThrowAsJavaScriptException();
        return env.Null();
    }

    uint8_t digest[FORJ128_DIGEST_BYTES];

    if (arg.IsString()) {
        std::string input = arg.As<Napi::String>().Utf8Value();
        forj128(reinterpret_cast<const uint8_t*>(input.data()), input.size(), digest);
    } else {
        Napi::Buffer<uint8_t> buffer = arg.As<Napi::Buffer<uint8_t>>();
        forj128(buffer.Data(), buffer.Length(), digest);
    }

    return Napi::Buffer<uint8_t>::Copy(env, digest, FORJ128_DIGEST_BYTES);
}

}  // namespace

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("hash", Napi::Function::New(env, Hash));
    return exports;
}

NODE_API_MODULE(forj128, Init)