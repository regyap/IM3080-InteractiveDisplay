import React, { useState, useEffect } from "react";
import socketOBJ from "../Socket/SocketIO.js";
import { useNavigate } from "react-router-dom";
import Button from "react-bootstrap/Button";
import "./Interactive.css";

function Interactive() {
  const navigate = useNavigate();

  function emitReq(button) {
    const data = { mode: button };
    socketOBJ.emit("buttonPressed", data);
  }
  function onBack(e) {
    e.preventDefault();
    navigate("/control");
  }
  return (
    <>
      <div className="forminput">
        <button
          value="Ripple"
          className="fButton"
          onClick={() => emitReq("/control")}
          // style={ emitReq ?  'border: 1px solid black': 'border: 1px solid grey' }
        >
          Ripple
        </button>

        <button
          value="Wave"
          class="fButton"
          onClick={() => navigate("/control/interactive")}
        >
          Wave
        </button>
      </div>
      <Button
        variant="danger"
        className="float-end"
        onClick={onBack}
        style={{ marginTop: "15px" }}
      >
        Back
      </Button>
    </>
  );
}
export default Interactive;
