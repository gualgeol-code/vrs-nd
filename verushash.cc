#include <napi.h>
#include "crypto/verus_hash.h"

// Logika inti C++ tetap sama
CVerusHash* vh;
CVerusHashV2* vh2;
CVerusHashV2* vh2b1;
bool initialized = false;

void initialize() {
    if (!initialized) {
        CVerusHash::init();
        CVerusHashV2::init();
        initialized = true;
    }
    vh = new CVerusHash();
    vh2 = new CVerusHashV2(SOLUTION_VERUSHHASH_V2);
    vh2b1 = new CVerusHashV2(SOLUTION_VERUSHHASH_V2_1);
}

// Pembungkus N-API untuk fungsi-fungsi hash
Napi::Value VerusInit(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    initialize();
    return env.Undefined();
}

Napi::Value VerusHash(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsBuffer()) {
        Napi::TypeError::New(env, "Argument harus berupa Buffer").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Buffer<unsigned char> buffer = info[0].As<Napi::Buffer<unsigned char>>();
    unsigned char result[32];

    if (!initialized) {
        initialize();
    }

    vh->Reset();
    vh->Write(buffer.Data(), buffer.Length());
    vh->Finalize(result);

    return Napi::Buffer<unsigned char>::Copy(env, result, 32);
}

Napi::Value VerusHashV2(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsBuffer()) {
        Napi::TypeError::New(env, "Argument harus berupa Buffer").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Buffer<unsigned char> buffer = info[0].As<Napi::Buffer<unsigned char>>();
    unsigned char result[32];

    if (!initialized) {
        initialize();
    }
    
    vh2->Reset();
    vh2->Write(buffer.Data(), buffer.Length());
    vh2->Finalize(result);

    return Napi::Buffer<unsigned char>::Copy(env, result, 32);
}

Napi::Value VerusHashV2b(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsBuffer()) {
        Napi::TypeError::New(env, "Argument harus berupa Buffer").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Buffer<unsigned char> buffer = info[0].As<Napi::Buffer<unsigned char>>();
    unsigned char result[32];

    if (!initialized) {
        initialize();
    }

    vh2->Reset();
    vh2->Write(buffer.Data(), buffer.Length());
    vh2->Finalize2b(result);

    return Napi::Buffer<unsigned char>::Copy(env, result, 32);
}

Napi::Value VerusHashV2b1(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsBuffer()) {
        Napi::TypeError::New(env, "Argument harus berupa Buffer").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::Buffer<unsigned char> buffer = info[0].As<Napi::Buffer<unsigned char>>();
    unsigned char result[32];

    if (!initialized) {
        initialize();
    }

    vh2b1->Reset();
    vh2b1->Write(buffer.Data(), buffer.Length());
    vh2b1->Finalize2b(result);

    return Napi::Buffer<unsigned char>::Copy(env, result, 32);
}

// Inisialisasi modul
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "init"), Napi::Function::New(env, VerusInit));
    exports.Set(Napi::String::New(env, "hash"), Napi::Function::New(env, VerusHash));
    exports.Set(Napi::String::New(env, "hashV2"), Napi::Function::New(env, VerusHashV2));
    exports.Set(Napi::String::New(env, "hashV2b"), Napi::Function::New(env, VerusHashV2b));
    exports.Set(Napi::String::New(env, "hashV2b1"), Napi::Function::New(env, VerusHashV2b1));
    return exports;
}

NODE_API_MODULE(verushash, Init)
