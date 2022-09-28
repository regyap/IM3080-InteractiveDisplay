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
      <Card style={{ width: "30rem" }}>
        <Card.Body>
          <Card.Title>Time Left</Card.Title>
        </Card.Body>
      </Card>
      <div class="forminput">
        <button
          value="Default"
          class="fButton"
          onClick={() => emitReq("default")}
        >
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
