import React, { useState, useEffect } from "react";
import socketOBJ from "../Socket/SocketIO.js";
import Logo from "../assets/logo.png";
import "./JoinQueue.css";

function JoinQueue() {
  var datetime = new Date();
  const [name, setName] = useState("");

  const joinQueue = (e) => {
    e.preventDefault();
    const data = { username: name, id: socketOBJ.id };
    socketOBJ.emit("joinQueue", data);
  };

  return (
    <div className="box">
      <div className="imageCenter">
        <img src={Logo} className="logo" />
      </div>

      <div className="lcomponents">
        <label className="loginLabel">Queue System</label>
      </div>
      <form className="lcomponents" onSubmit={joinQueue}>
        <label className="fLabel">Enter Your Name:</label>
        <input
          type="text"
          name="name"
          onChange={(e) => setName(e.target.value)}
          required
        />
        <input style={{ marginTop: "2%" }} type="submit" />
      </form>
    </div>
  );
}
export default JoinQueue;
