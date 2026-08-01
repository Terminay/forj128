{
  "targets": [
    {
      "target_name": "forj128",
      "sources": [ "../forj128.c", "forj128_binding.cpp" ],
      "include_dirs": [ "..", "<!(node -e \"console.log(require('nan').include)\")" ],
      "cflags": [ "-O2" ],
      "libraries": [ "-lm" ],
      "conditions": [
        ["OS=='win'", {
          "libraries": []
        }]
      ]
    }
  ]
}