from flask import jsonify, request
from app import app
from app.models import Pump, Balance, Pump_Config, Balance_Config
from datetime import *

@app.route('/')
def index():
    return 'Backend application running!'

@app.route('/status_pump/<int:id_Pump>', methods=['GET',])
def status_pump(id_Pump):
    result = Pump.query.filter_by(id_Pump=id_Pump).order_by(Pump.id.desc()).first()
    return jsonify(result.serialize)

@app.route('/status_pump_all/<int:id_Pump>', methods=['GET',])
def status_pump_all(id_Pump):
    results = [i.serialize for i in Pump.query.filter_by(id_Pump=id_Pump).all()]
    return jsonify(results=results)


@app.route('/config_pump/<int:id_Pump>', methods=['POST',])
def config_pump(id_Pump):
    data = request.form
    result = Pump_Config.query.filter_by(id=id_Pump).first()
    result.status = data.get('status')
    result.clockwise = data.get('clockwise')
    result.time_Step = data.get('timeStep')
    result.pulse_Ratio = data.get('pulseRatio')
    result.code_Fault = 0
    result.confirmation = 0
    db.session.commit()

@app.route('/status_balance/<int:id_Balance>', methods=['GET',])
def status_balance(id_Balance):
    result = Balance.query.filter_by(id_Balance=id_Balance).order_by(Balance.id.desc()).first()
    return jsonify(result.serialize)

@app.route('/status_balance_all/<int:id_Balance>', methods=['GET',])
def status_balance_all(id_Balance):
    results = [i.serialize for i in Balance.query.filter_by(id_Balance=id_Balance).all()]
    return jsonify(results=results)

@app.route('/config_balance/<int:id_Balance>', methods=['POST',])
def config_balance(id_Balance):
    data = request.form
    result = Balance_Config.query.filter_by(id=id_Balance).first()
    result.status = data.get('status') # set scale
    result.code_Fault = 0
    result.confirmation = 0
    if data.get('status') == 1:
        result.name = data.get('name')
        result.scale = Balance.query.filter_by(id_Balance=id_Balance).order_by(Balance.id.desc()).first().weight
    else:
        result.name = 'Stop'
        result.scale = 0
    db.session.commit()
