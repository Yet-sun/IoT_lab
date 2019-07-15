var app = require("express")();
var server = require("http").Server(app);
var io = require("socket.io")(8088);

server.listen(8087);

app.get("/", function(req, res) {
    res.sendfile(__dirname + "/index.html");
});
io.on("connection", function(socket) {
    socket.emit("news", { hello: "world" });
    socket.on("data", function(data) {
        console.log(data);
    });
    var net = require("net");

    // 创建TCP服务器
    var server2 = net.createServer(function(socket2) {
        console.log("client connected");

        // 监听客户端的数据
        socket2.on("data", function(data) {
            d = data.toString().split("x");
            socket.emit("news", {
                c: d[0],
                h: d[1]
            });
            console.log("server got data from client: ", data.toString());
        });
        // 监听客户端断开连接事件
        socket2.on("end", function(data) {
            console.log("connection closed");
        });
        // 发送数据给客户端
        socket2.write("Hello\r\n");
    });
    // 启动服务
    server2.listen(8090, "192.168.43.59", function() {
        console.log("server bound");
    });
});