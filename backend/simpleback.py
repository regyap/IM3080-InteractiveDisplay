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

# @app.route('/joinQueue', methods=["POST"])          
# def joinQueue():
#     userData = request.get_json()
#     print(userData["username"])
#     db.session.add(Queue(username=userData["username"], time=userData["time"]))
#     db.session.commit()
#     response = {"status": "success"}
#     return (response, 200)

# @app.route('/exitQueue', methods=["POST"])          
# def exitQueue():
#     userData = request.get_json()
#     Queue.query.filter_by(username = userData["username"]).delete()
#     db.session.commit()
#     response = {"status": "success"}
#     return (response, 200)

# @socket.on('queueStatus')
# def queueStatus(msg):
#     # Add to Queue DB if success, send this
#     socket.send(data = msg["username"] + " registered!", to= msg["id"])

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
        for user in usernames:
            print(user.userData())


if __name__ == '__main__':
    # app.run(host='0.0.0.0', port=5000, threaded=True)
    db.create_all()
    socket.start_background_task(target=backgroundQueueSocket)
    socket.run(app, host='0.0.0.0', port=5000)
    