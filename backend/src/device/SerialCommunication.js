var serialport = require('serialport');
var SerialPort = serialport.SerialPort;
var io = require('socket.io');

var serialDeviceControlPeristaltic = new SerialPort("COM5", {
    baudrate: 9600,
    parser: serialport.parser.readline("\n"),
});

serialDeviceControlPeristaltic.on("open",()=>{
    console.log("Open port serial");
});

serialDeviceControlPeristaltic.on("data",(data)=>{
    io.emit('dataDevice', {
        valor: data
    })
});

io.on("connect", (socket) =>{
    console.log("Um usuario conectado")
});

module.exports = serialDeviceControlPeristaltic;