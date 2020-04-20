const connection = require('../database/connection');
const SerialPort = require('serialport');


/*SerialPort.list().then(
  ports => ports.forEach(console.log),
  err => console.error(err)
)*/

const serialPort = new SerialPort('COM5',{
    baudRate: 57600,
    parser: SerialPort.parsers.Readline,
  }, 
  function (err) {
    if (err) {
      return console.log('Error: ', err.message);
    }
});

module.exports = {
  async create(request, reponse) {

    const { peristalticPumpNumber, peristalticPumpRatio, peristalticPumpTempOn, peristalticPumpTurn } = request.body;
    const packageSendSerial = `<c;${peristalticPumpNumber};${peristalticPumpRatio};${peristalticPumpTempOn};${peristalticPumpTurn}>`;

    serialPort.write(packageSendSerial);
    
    return reponse.json(packageSendSerial);
  }
};