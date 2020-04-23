const express = require('express');
const { celebrate, Segments, Joi } = require('celebrate');


const routes = express.Router();
const BombController = require('./controllers/BombConfigController');



routes.post('/bomb', celebrate({
    [Segments.BODY]: Joi.object().keys({
        peristalticPumpNumber: Joi.number().min(1).max(4).required(), 
        peristalticPumpRatio: Joi.number().min(0).max(100).required(), 
        peristalticPumpTempOn: Joi.number().min(0).max(100).required(), 
        peristalticPumpTurn: Joi.string().required(),
        peristalticPumpTurningDirection: Joi.string().required(),
    })
}), BombController.create)

module.exports = routes;