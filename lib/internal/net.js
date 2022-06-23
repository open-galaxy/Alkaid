'use strict';

class Socket {
  constructor(options) {}
}

class Server {
  constructor(options, connectionListener) {
    if (typeof options === 'function') {
      connectionListener = options;
      options = {};
    } else if (options == null || typeof options === 'object') {
      options = { ...options };
    } else {
      throw new TypeError('First argument must be an object or a function');
    }

    this.onConnection = connectionListener;
  }

  listen(port, listeningListener) {
    const fd = tcp.open();
    tcp.bind(fd, port);

    const err = tcp.listen(fd);

    if (typeof listeningListener === 'function' && err === 0) {
      listeningListener();
    }

    return;
  }

}

function createServer(options, connectionListener) {
  return new Server(options, connectionListener);
}

module.exports = {
  Socket,
  Server,
  createServer,
};