# fds

[![Greenkeeper badge](https://badges.greenkeeper.io/terinjokes/fds.svg)](https://greenkeeper.io/)
> Set non-block mode on file descriptors.

## Why?

Part of the API contract for [libuv](https://github.com/libuv/libuv) specifies that file descriptors should already be in non-blocking mode.
Newer versions of libuv set the non-blocking flag, and thus node version that utilize them have the fix. Unfortunately 0.10 and the early versions of 0.12 do not.

This is a simple backport of libuv code packaged up into a module that can be utilized everywhere.

## Usage

```javascript
var http = require('http');
var fds = require('fds');

fds.nonblock(3)

http.createServer(function(req, res) {
  res.writeHead(200, {
    'Content-Type': 'text/plain'
  });
  res.end('Hello World\n');
}).listen({
  fd: 3
});
```
