const connection = require('../database/connection');
const SerialPort = require('serialport');


/*SerialPort.list().then(
  ports => ports.forEach(console.log),
  err => console.error(err)
)*/

const serialport = new SerialPort('COM5',{
    baudRate: 57600,
    autoOpen: false,
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
        const getDataSerialPort = "";

        

        serialport.open((err)=>{
          if (err) {
            return console.log('Error opening port: ', err.message)
          }
          setTimeout(() => {
            serialport.close((err) => {
              console.log('closed?', err);
            });
          }, 1000);
        });

        serialport.write(packageSendSerial);
        return reponse.json(packageSendSerial);
    }
};