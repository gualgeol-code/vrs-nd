{
  "targets": [
    {
      "target_name": "verushash",
      "sources": [
        "crypto/haraka.c",
        "crypto/haraka_portable.c",
        "crypto/uint256.cpp",
        "crypto/utilstrencodings.cpp",
        "crypto/verus_hash.cpp",
        "crypto/verus_clhash.cpp",
        "crypto/verus_clhash_portable.cpp",
        "verushash.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('node-addon-api')\")"
      ],
      "cflags!": [
        "-fno-exceptions"
      ],
      "cflags_cc!": [
        "-fno-exceptions",
        "-std=c++11"
      ],
      "cflags_cc": [
        "-std=c++17"
      ],
      "xcode_settings": {
        "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
        "MACOSX_DEPLOYMENT_TARGET": "10.7",
        "GCC_VERSION": "com.apple.compilers.llvm.clang.1_0",
        "CLANG_CXX_LANGUAGE_STANDARD": "c++17"
      },
      "msvs_settings": {
        "VCCLCompilerTool": {
          "ExceptionHandling": 1,
          "AdditionalOptions": [
            "/std:c++17"
          ]
        }
      },
      "defines": [
        "NAPI_DISABLE_CPP_EXCEPTIONS"
      ]
    }
  ]
}
