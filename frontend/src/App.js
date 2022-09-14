import React, { useState, useEffect } from "react";
import "./App.css";
import FrontPage from "./IndexPage/FrontPage.js";
import socketOBJ from "./Socket/SocketIO.js";
import JoinQueue from "./QueueSystem/JoinQueue";

function App() {
  useEffect(() => {
    socketOBJ.on("connect", () => {
      console.log("Web Socket Establish");
    });
    socketOBJ.on("message", (msg) => {
      console.log(msg);
    });
  }, []);

  return (
    <body id="body">
      {/* <FrontPage /> */}
      <JoinQueue />
    </body>
  );
}
export default App;
