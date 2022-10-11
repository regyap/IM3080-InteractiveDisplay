import React, { useState, useEffect } from "react";
import socketOBJ from "../Socket/SocketIO.js";
import Card from "react-bootstrap/Card";
import "./FrontPage.css";

function FrontPage() {
  useEffect(() => {
    socketOBJ.on("buttonReply", (msg) => {
      console.log(msg);

      
    });
  }, []);

  function emitReq(button) {
    socketOBJ.emit("buttonPressed", button);
  }
  

  return (
    <>
      <Card style={{ width: "50rem",  boxShadow: "inset 0 0 50px #fff,inset 20px 0 80px #f0f,inset -20px 0 80px #0ff,inset 20px 0 300px #f0f,inset -20px 0 300px #0ff"}} >
        <Card.Body>
          <Card.Title>Time Left</Card.Title>
        </Card.Body>
      </Card>
      <div class="forminput">
        <button value="Default" class="fButton" onClick={() => emitReq("default")}>
          Default
        </button>
      </div>
      <div class="forminput">
        <button value="Theme" class="fButton" onClick={() => emitReq("theme")}>
          Theme
        </button>
      </div>
    </>
  );
}
export default FrontPage;
