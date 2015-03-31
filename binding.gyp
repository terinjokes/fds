{
  "targets": [
    {
      "target_name": "fds",
      "sources": [
        "src/fds.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "conditions": [
        [ "OS=='win'", {
          "sources": [
            "./src/fds-win.h",
            "./src/fds-win.cc"
          ]
        }, {
          "sources": [
            "./src/fds-unix.h",
            "./src/fds-unix.cc"
          ]
        }
      ]]
    }
  ]
}
