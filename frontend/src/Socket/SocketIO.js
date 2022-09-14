import io from "socket.io-client";

const socketOBJ = io("http://localhost:5000", { transports: ["websocket"] });

export default socketOBJ;
