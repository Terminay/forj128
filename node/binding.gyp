{
  "targets": [
    {
      "target_name": "forj128",
      "sources": [ "../forj128.c", "forj128_binding.cpp" ],
      "include_dirs": [ "..", "<!(node -e \"console.log(require('node-addon-api').include)\")" ],
      "cflags": [ "-O2", "-Wall", "-Wextra" ],
      "cflags_cc": [ "-std=c++17" ],
      "libraries": [ "-lm" ],
      "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ],
      "conditions": [
        ["OS=='win'", {
          "libraries": []
        }]
      ]
    }
  ]
}