import React, { useState, useEffect } from "react";
import socketOBJ from "../Socket/SocketIO.js";
import "./FrontPage.css";

function FrontPage() {
  function emitReq() {
    socketOBJ.emit("buttonPressed", "Hello World");
  }

  useEffect(() => {
    socketOBJ.on("buttonReply", (msg) => {
      console.log(msg);
    });
  }, []);

  return (
    <>
      <div class="forminput">
        <button value="Default" class="fButton" onClick={emitReq}>
          Default
        </button>
      </div>
      <div class="forminput">
        <button value="Theme" class="fButton" onClick={emitReq}>
          Theme
        </button>
      </div>
    </>
  );
}
export default FrontPage;
