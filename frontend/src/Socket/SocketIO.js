import io from "socket.io-client";
import { SERVER_IP } from "../Constant";

const socketOBJ = io(SERVER_IP, { transports: ["websocket"] });

export default socketOBJ;
