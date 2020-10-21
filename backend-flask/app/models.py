from app import db
from datetime import datetime

class Pump(db.Model):
    id = db.Column(db.Integer, primary_key=True, nullable=False)
    id_Pump = db.Column(db.Integer, nullable=False)
    status = db.Column(db.Integer, nullable=False)
    clockwise = db.Column(db.Integer, nullable=False)
    time_Step = db.Column(db.Integer, nullable=False)
    pulse_Ratio = db.Column(db.Integer, nullable=False)
    code_Fault = db.Column(db.Integer, nullable=False)
    registration_Date = db.Column(db.DateTime, default=datetime.utcnow)
    def __repr__(self):
        return '<Pump id:{}, id_pump:{}>'.format(self.id, self.id_Pump)
    
    @property
    def serialize(self):
        return {
            'id': self.id,
            'idPump': self.id_Pump,
            'status': self.status,
            'clockwise': self.clockwise,
            'timeStep': self.time_Step,
            'pulseRatio': self.pulse_Ratio,
            'CodeFault': self.code_Fault,
            'registrationDate': self.registration_Date
        }

class Balance(db.Model):
    id = db.Column(db.Integer, primary_key=True, nullable=False)
    id_Balance = db.Column(db.Integer, nullable=False)
    status = db.Column(db.Integer, nullable=False)
    scale = db.Column(db.Integer, nullable=False)
    weight = db.Column(db.Integer, nullable=False)
    code_Fault = db.Column(db.Integer, nullable=False)
    registration_Date = db.Column(db.DateTime, default=datetime.utcnow)
    def __repr__(self):
        return '<Balance id:{}, id_Balance:{}>'.format(self.id, self.id_Balance)
    
    @property
    def serialize(self):
        return {
            'id': self.id,
            'idBalance': self.id_Balance,
            'status': self.status,
            'scale': self.scale,
            'weight': self.weight,
            'CodeFault': self.code_Fault,
            'registrationDate': self.registration_Date
        }