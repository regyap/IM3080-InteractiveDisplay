from flask import Flask, Response, request, jsonify
from flask_cors import CORS
from flask_socketio import SocketIO
from flask_sqlalchemy import SQLAlchemy
import datetime
import serial
import os

app = Flask(__name__)
CORS(app, resources={r"/*": {"origins": "*"}})
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///app.db'
socket = SocketIO(app=app, cors_allowed_origins='*')
db = SQLAlchemy(app)
duration = 1
sessionDuration = datetime.timedelta(minutes=duration)

class Queue(db.Model):
    id = db.Column(db.String, primary_key=True)
    username = db.Column(db.String(80), nullable=False)
 
    def userData(self):
        return {"id":self.id, "username":self.username}

class Session(db.Model):
    id = db.Column(db.String, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    iat = db.Column(db.DateTime, nullable=False)

    def sessionData(self):
        return {"id":self.id, "username":self.username, "iat":self.iat}

@app.route('/')
def index():
    usernames = db.session.query(Queue.username).all()
    usernameList = []
    for username in usernames:
        usernameList.append(username[0])
    print(usernameList)
    return str(usernameList)

@socket.on('joinQueue')
def joinQueue(msg):
    print(msg)
    duplicateCheck = Queue.query.filter_by(id = str(msg["id"])).count()
    if duplicateCheck == 0:
        db.session.add(Queue(id=msg["id"], username=msg["username"]))
        db.session.commit()
        reply = {"status": "success" , "id": msg["id"]}
        socket.emit("joinQueue", data = reply, to= msg["id"])
    else:
        reply = {"status": "fail" , "id": msg["id"], "err":"Duplicate ID"}
        socket.emit("joinQueue", data = reply, to= msg["id"])

@socket.on('exitQueue')
def exitQueue():
    Queue.query.filter_by(id=request.sid).delete()
    db.session.commit()
    print(request.sid + " exited queue")

@socket.on('buttonPressed')
def buttonPressed(data):
    text = data
    ser.write(text.encode("utf-8"))
    print(data + " transmited from frontend")

@socket.on('connect')
def disconnect():
    Queue.query.filter_by(id=request.sid).delete()
    db.session.commit()
    print(request.sid + " connected")

@socket.on('disconnect')
def disconnect():
    Queue.query.filter_by(id=request.sid).delete()
    db.session.commit()
    print(request.sid + " disconnected")

def backgroundQueueSocket():
    while True:
        socket.sleep(1)
        usernames = db.session.query(Queue).all()
        queueData = []
        for user in usernames:
            queueData.append(user.userData())
        res = {"data": queueData}
        socket.emit("queue", data = res)
        print("Current Queue:")
        print(str(queueData) + "\n")

def sessionSocket():
    while True:
        socket.sleep(1)
        inSession = db.session.query(Session).count() != 0
        queueCount = db.session.query(Queue).count()
        now = datetime.datetime.now()

        if (not inSession) and (queueCount != 0):
            userData = db.session.query(Queue).first()
            print(userData.userData)
            db.session.add(Session(id=userData.id, username=userData.username, iat=now))
            res = {"data":{"id":userData.id, "username":userData.username, "iat":str(now.isoformat()), "expiry":(str((now +datetime.timedelta(minutes=duration)).isoformat()))}}
            socket.emit("enterSession", data = res, to=userData.id) #emit smth to trigger session
            Queue.query.filter_by(id=userData.id).delete()
            db.session.commit()

        elif (inSession):
            userSession = db.session.query(Session).first()
            if ((now - userSession.iat) > sessionDuration ):
                res = {"data":{"id":userSession.id, "username":userSession.username, "iat":str(userSession.iat)}}
                socket.emit("exitSession", data = res, to=userSession.id) #emit smth to trigger exit
                Session.query.filter_by(id=userSession.id).delete()
                db.session.commit()
            else:
                print(userSession.username + " is in session")
                continue


if __name__ == '__main__':
    # app.run(host='0.0.0.0', port=5000, threaded=True)
    if os.path.exists("app.db"):
        os.remove("app.db")
    # ser = serial.Serial("/dev/ttyACM0", 9600, timeout=1)
    # ser.reset_input_buffer()
    db.create_all()
    socket.start_background_task(target=backgroundQueueSocket)
    socket.start_background_task(target=sessionSocket)
    socket.run(app, host='0.0.0.0', port=5000)
    