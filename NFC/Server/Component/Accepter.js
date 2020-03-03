var http = require("http");

console.log("----Accepter Load !----");

// localhost
var hostname = "127.0.0.1";
var port = 3000;

// Create Server
var CreateServer = function () {
    http.createServer(function (request, response) {
        // Occurred Error
        // response.write(200, { "Content-Type": "text/plan" });
        response.end("CreateServer Success!");
    }).listen(port, hostname);

    console.log("Server running at http://" + hostname + ":" + port);
}

// DEF
module.exports = 
{
    CreateServer: CreateServer
}