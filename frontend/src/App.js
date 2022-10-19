import React, { useState, useEffect } from "react";
import { BrowserRouter as Router, Routes, Route, Link } from "react-router-dom";
import { useNavigate } from "react-router-dom";
import "./App.css";
import FrontPage from "./IndexPage/FrontPage.js";
import socketOBJ from "./Socket/SocketIO.js";
import JoinQueue from "./QueueSystem/JoinQueue";
import Queue from "./QueueSystem/Queue";
import RGB from "./IndexPage/RGB";
import "bootstrap/dist/css/bootstrap.min.css";

function App() {
  const navigate = useNavigate();
  const [inSession, setInSession] = useState(false);
  const [expiry, setExpiry] = useState("");
  useEffect(() => {
    socketOBJ.on("connect", () => {
      console.log("Web Socket Establish: " + socketOBJ.id);
    });
    socketOBJ.on("queueStatus", (res) => {
      console.log(res);
    });
    socketOBJ.on("enterSession", (res) => {
      console.log(res);
      setExpiry(Date.parse(res["data"]["expiry"]));
      navigate("/control");
      setInSession(true);
    });
    socketOBJ.on("exitSession", (res) => {
      console.log(res);
      navigate("/");
      setInSession(false);
    });
    // socketOBJ.on("message", (msg) => {
    //   console.log(msg);
    // });
  }, []);

  return (
    <body id="body">
      <Routes>
        <Route path="/" element={<JoinQueue />} />
        <Route path="/queue" element={<Queue />} />
        {inSession ? (
          <Route
            path="/control"
            element={<FrontPage expiry={expiry} setSession={setInSession} />}
          />
        ) : (
          <></>
        )}
        {inSession ? <Route path="/control/rgb" element={<RGB />} /> : <></>}
      </Routes>
    </body>
  );
}
export default App;
