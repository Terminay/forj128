{
  "targets": [
    {
      "target_name": "forj128",
      "sources": [ "forj128.c", "forj128_binding.cpp" ],
      "include_dirs": [ "..", "<!(node -p \"require('path').dirname(require.resolve('node-addon-api'))\")" ],
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