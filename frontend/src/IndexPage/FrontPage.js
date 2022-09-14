import React, { useState, useEffect } from "react";
import socketOBJ from "../Socket/SocketIO.js";
import "./FrontPage.css";

function FrontPage() {
  // const [facts, setFacts] = useState("");

  // function request() {
  //   fetch("https://catfact.ninja/fact")
  //     .then((response) => response.json())
  //     .then((data) => {
  //       setFacts(data["fact"]);
  //       console.log(data["fact"]);
  //     });
  // }

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
      {/* <div>{facts}</div> */}
      <div class="forminput">
        <button name="Default" value="Default" id="Default" onClick={emitReq}>
          Default
        </button>
      </div>
      <div class="forminput">
        <button name="Theme" value="Theme" id="Theme" onClick={emitReq}>
          Theme
        </button>
      </div>
    </>
  );
}
export default FrontPage;
