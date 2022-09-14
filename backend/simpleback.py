from flask import Flask, Response, request, jsonify
from flask_cors import CORS
from flask_socketio import SocketIO


app = Flask(__name__)
CORS(app, resources={r"/*": {"origins": "*"}})
socket = SocketIO(app=app, cors_allowed_origins='*')

mode = ""

@app.route('/')
def index():
    return "Default Message"


@app.route('/json', methods=["POST", "GET"])          
def data():
    data = {
            'red': "1",
            'green': "2",
            'blue': "3",
            }
    response = jsonify(data)
    return (response, 200)

@app.route('/change', methods=["POST"])          
def change():
    if request.method == "POST":
        data = request.get_json()
        mode = data[mode]
        return ('', 204)

@socket.on('joinQueue')
def handleJoinQueue(msg):
    # Add to Queue DB if success, send this
    socket.send(data = msg["username"] + " registered!", to= msg["id"])
    

if __name__ == '__main__':
    # app.run(host='0.0.0.0', port=5000, threaded=True)
    socket.run(app)