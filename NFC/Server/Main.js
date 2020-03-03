console.log("----Main Start !" + " ("+ process.version + ")----");

// Accepter Load
console.log("----Accepter Load Start !----");
var accepter = require("./Component/Accepter.js");

// Create Server
accepter.CreateServer();