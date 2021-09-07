'use strict';

(function(){

var net = require('net'),
//    ansi = require('./ansi_up.js'),
    iconv = require('iconv-lite'),
    TextDecoder = require('text-encoding').TextDecoder;

  // string to uint array
function unicodeStringToTypedArray(s) {
    var escstr = encodeURIComponent(s);
    var binstr = escstr.replace(/%([0-9A-F]{2})/g, function(match, p1) {
        return String.fromCharCode('0x' + p1);
    });
    var ua = new Uint8Array(binstr.length);
    Array.prototype.forEach.call(binstr, function (ch, i) {
        ua[i] = ch.charCodeAt(0);
    });
    return ua;
}

// uint array to string
function typedArrayToUnicodeString(ua) {
    var binstr = Array.prototype.map.call(ua, function (ch) {
        return String.fromCharCode(ch);
    }).join('');
    var escstr = binstr.replace(/(.)/g, function (m, p) {
        var code = p.charCodeAt(p).toString(16).toUpperCase();
        if (code.length < 2) {
            code = '0' + code;
        }
        return '%' + code;
    });
    return decodeURIComponent(escstr);
}

function WebTelnetProxy(io, port, host) {
  if(this && (this instanceof WebTelnetProxy)) {
    this.reset();
    if(io) this.bind(io, port, host);
  } else {
    return new WebTelnetProxy(io, port, host);
  }
}

WebTelnetProxy.prototype = {
  reset: function() {
    this.io = null;
    this.logTraffic = false;

    this.isRunning = false;
    this.timer = 0;
    this.lastTick = 0;

    this.sockets = {};  // sid -> socket
    this.socketsCount = 0;
    
    this.port = 23;
    this.host = '127.0.0.1';
    this.decoder = new TextDecoder('gb2312');
    return this;
  },

  showTraffic: function(y) {
    this.logTraffic = y;
    return this;
  },

  setCharset: function(cs) {
    this.charset = cs;
    this.decoder = new TextDecoder(cs);
    return this;
  },

  bind: function(io, port, host) {
    if(this.isRunning) throw new Error('WebTelnetProxy is already running.');

    var proxy = this;
    proxy.io = io;
    proxy.port = port;
    proxy.host = host;

    io.on('connection', function(sock){
      proxy.onConnected(sock);
    });

    proxy.lastTick = Date.now();
    proxy.isRunning = true;

    // init tick() timer
    proxy.tick();
    proxy.timer = setInterval(function(){
      proxy.tick();
    }, 1000);
    
    return this;
  },

  shutdown: function() {
    if(!this.isRunning) return;

    // clear tick() timer
    if(this.timer) clearInterval(this.timer);

    this.reset();

    return this;
  },

  tick: function() {
    var server = this;
    server.lastTick = Date.now();
  },

  onDisconnected: function(webSock) {
    var proxy = this;
    var peerSock = webSock.peerSock;
    if(peerSock) {
      webSock.peerSock = null;
      peerSock.peerSock = null;
      peerSock.end();
    }
    delete proxy.sockets[ webSock.id ];
    proxy.socketsCount --;
  },

  connectTelnet: function(webSock) {
    var proxy = this;

    var telnet = net.connect( proxy.port, proxy.host, function() {
      webSock.emit('status', '服务器连接成功。\n');
    });

    telnet.peerSock = webSock;
    webSock.peerSock = telnet;
    telnet.write('123456789abcd\n');

    telnet.on('data', function(buf) {
      var peerSock = telnet.peerSock;
      if(peerSock) {
      	var str = proxy.decoder.decode(buf);
//        str = ansi.ansi_to_html(str);
        peerSock.emit('stream', str);
      }
    });
    telnet.on('error', function(){
    });
    telnet.on('close', function(){
      if(proxy.logTraffic) console.log('telnet disconnected');
      webSock.emit('status', '与服务器断开连接。\n');
    });
    telnet.on('end', function(){
      var peerSock = telnet.peerSock;
      if(peerSock) {
        peerSock.peerSock = null;
        telnet.peerSock = null;
      }
    });
  },

  onConnected: function(webSock) {
    var proxy = this;

//    console.log('proxy client connected, socket id: ' + webSock.id);
      webSock.on('stream', function(message) {
      message = message.replace("<","＜");
//      message = message.replace(">","＞");
      if(proxy.charset && (proxy.charset !== 'utf8')) {
        message = iconv.encode(message, proxy.charset);
      }
//    console.log('websocket: ', message);
      var peerSock = webSock.peerSock;
      if(peerSock) {
        peerSock.write(message);
      } else {
        proxy.connectTelnet(webSock);
      }
    });

    webSock.on('disconnect', function(){
      if(proxy.logTraffic) console.log('proxy client disconnected, socket id: ' + webSock.id);
      proxy.onDisconnected(webSock);
    });

    proxy.sockets[webSock.id] = webSock;
    proxy.socketsCount ++;
  },
};

exports = module.exports = WebTelnetProxy;

})();
