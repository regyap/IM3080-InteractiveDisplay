import React, { useState, useEffect } from "react";
import { BrowserRouter as Router, Routes, Route, Link } from "react-router-dom";
import "./App.css";
import FrontPage from "./IndexPage/FrontPage.js";
import socketOBJ from "./Socket/SocketIO.js";
import JoinQueue from "./QueueSystem/JoinQueue";

function App() {
  useEffect(() => {
    socketOBJ.on("connect", () => {
      console.log("Web Socket Establish: " + socketOBJ.id);
    });
    socketOBJ.on("queueStatus", (res) => {
      console.log(res);
    });
    // socketOBJ.on("message", (msg) => {
    //   console.log(msg);
    // });
  }, []);

  return (
    <body id="body">
      <Router>
        <Routes>
          <Route path="/" element={<JoinQueue />} />
          {/* <Route path="/queue" element={<Queue />} /> */}
          <Route path="/control" element={<FrontPage />} />
        </Routes>
      </Router>
    </body>
  );
}
export default App;
