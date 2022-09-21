from flask import Flask, Response, request, jsonify
from flask_cors import CORS
from flask_socketio import SocketIO
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
CORS(app, resources={r"/*": {"origins": "*"}})
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///app.db'
socket = SocketIO(app=app, cors_allowed_origins='*')
db = SQLAlchemy(app)

class Queue(db.Model):
    id = db.Column(db.String, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)

    def userData(self):
        return {"id":self.id, "username":self.username}

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
    duplicateCheck = Queue.query.filter_by(id = msg["id"]).count()
    if duplicateCheck == 0:
        db.session.add(Queue(id=msg["id"], username=msg["username"]))
        db.session.commit()
        reply = {"status": "success" , "id": msg["id"]}
        socket.emit("joinQueue", data = reply, to= msg["id"])
    else:
        reply = {"status": "fail" , "id": msg["id"], "err":"Duplicate ID"}
        socket.emit("joinQueue", data = reply, to= msg["id"])
    
@socket.on('disconnect')
def disconnect():
    Queue.query.filter_by(id=request.sid).delete()
    db.session.commit()
    print(request.sid)

def backgroundQueueSocket():
    while True:
        socket.sleep(5)
        usernames = db.session.query(Queue).all()
        queueData = []
        for user in usernames:
            queueData.append(user.userData())
        print(queueData)

if __name__ == '__main__':
    # app.run(host='0.0.0.0', port=5000, threaded=True)
    db.create_all()
    socket.start_background_task(target=backgroundQueueSocket)
    socket.run(app, host='0.0.0.0', port=5000)
    