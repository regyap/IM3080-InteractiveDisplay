import React, { useState, useEffect } from "react";
import { useNavigate } from "react-router-dom";
import socketOBJ from "../Socket/SocketIO.js";
import Logo from "../assets/ntu2.png";
import "./JoinQueue.css";

function JoinQueue() {
  const [name, setName] = useState("");
  const navigate = useNavigate();

  useEffect(() => {
    socketOBJ.on("joinQueue", (res) => {
      if (res["id"] === socketOBJ.id && res["status"] === "success") {
        console.log("Queue Joined");
        navigate("/queue");
      } else if (res["id"] === socketOBJ.id && res["status"] === "fail") {
        alert(res["err"]);
      }
    });
  }, []);

  const joinQueue = (e) => {
    e.preventDefault();
    const data = { username: name, id: socketOBJ.id };
    console.log(data);
    socketOBJ.emit("joinQueue", data);
  };

  return (
    <div className="box">
      <div className="imageCenter">
        <img src={Logo} className="logo" />
      </div>

    
      <form className="lcomponents" onSubmit={joinQueue}>
        <label className="fLabel">Enter Name:</label>
        <input onChange={(e) => setName(e.target.value)} required />
        <input style={{ marginTop: "2%" }} type="submit" value="Join Queue" />
      </form>
    </div>
  );
}
export default JoinQueue;
