{
  "targets": [
    {
      "target_name": "forj128",
      "sources": [ "../forj128.c" ],
      "include_dirs": [ "." ],
      "cflags": [ "-O2" ],
      "libraries": [ "-lm" ],
      "conditions": [
        ["OS=='win'", {
          "sources": [],
          "libraries": []
        }]
      ]
    }
  ]
}