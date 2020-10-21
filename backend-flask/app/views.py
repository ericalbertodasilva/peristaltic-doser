from flask import render_template, jsonify, url_for
from app import app
from app.models import Pump, Balance
from datetime import *

@app.route('/')
def index():
    return 'Backend application running!'

@app.route('/_status_pump/<int:id_Pump>', methods=['GET',])
def _status_pump(id_Pump):
    result = Pump.query.filter_by(id_Pump=id_Pump).order_by(Pump.id.desc()).first()
    return jsonify(result.serialize)

@app.route('/_status_balance/<int:id_Balance>', methods=['GET',])
def _status_balance(id_Balance):
    result = Balance.query.filter_by(id_Balance=id_Balance).order_by(Balance.id.desc()).first()
    return jsonify(result.serialize)

@app.route('/_status_pump_all/<int:id_Pump>', methods=['GET',])
def _status_pump_all(id_Pump):
    results = [i.serialize for i in Pump.query.filter_by(id_Pump=id_Pump).all()]
    return jsonify(results=results)

@app.route('/_status_balance_all/<int:id_Balance>', methods=['GET',])
def _status_balance_all(id_Balance):
    results = [i.serialize for i in Balance.query.filter_by(id_Balance=id_Balance).all()]
    return jsonify(results=results)