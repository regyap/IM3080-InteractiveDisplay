import React, { useState, useEffect } from "react";
import socketOBJ from "../Socket/SocketIO.js";
import Card from "react-bootstrap/Card";
import { Slider } from "@mui/material";
import Button from "react-bootstrap/Button";
import { useNavigate } from "react-router-dom";
import "./RGB.css";
import "./FrontPage.css";

function RGB() {
  const [redValue, setRedValue] = useState(0);
  const [greenValue, setGreenValue] = useState(0);
  const [blueValue, setBlueValue] = useState(0);
  const [beats, setBeats] = useState("bread");
  const navigate = useNavigate();

  function changeVal(colour, value) {
    const data = {
      mode: beats,
      red: redValue,
      green: greenValue,
      blue: blueValue,
    };
    if (colour === "red") {
      setRedValue(value);
      data["red"] = value;
    } else if (colour === "green") {
      setGreenValue(value);
      data["green"] = value;
    } else if (colour === "blue") {
      setBlueValue(value);
      data["blue"] = value;
    }
    socketOBJ.emit("buttonPressed", data);
    console.log(data);
  }

  function emitReq(button) {
    const data = {
      mode: button,
      red: redValue,
      green: greenValue,
      blue: blueValue,
    };
    setBeats(button);
    socketOBJ.emit("buttonPressed", data);
    console.log(data);
  }

  function onBack(e) {
    e.preventDefault();
    navigate("/control");
  }

  return (
    <>
      <div className="forminput">
        <button
          value="Bread"
          className={beats === "bread" ? "fButtonActivated" : "fButton"}
          onClick={() => emitReq("bread")}
        >
          Bread
        </button>

        <button
          value="Sunflower"
          className={beats === "sunflower" ? "fButtonActivated" : "fButton"}
          onClick={() => emitReq("sunflower")}
        >
          Sunflower
        </button>
      </div>
      <div className="forminput">
      <Card
        style={{
          
          boxShadow:
            "inset 0 0 50px #fff,inset 20px 0 80px #f0f,inset -20px 0 80px #0ff,inset 20px 0 300px #f0f,inset -20px 0 300px #0ff",
          marginTop: "20px",
        }} className="card"
      >
        {/* <Card.Body>
          <Card.Title>Time Left</Card.Title>
        </Card.Body> */}
        <div className="sliderbox">
          <label className="slabel">R: </label>
          <Slider
            size="medium"
            value={redValue}
            aria-label="Small"
            valueLabelDisplay="auto"
            min={0}
            max={255}
            onChange={(event, value) => changeVal("red", value)}
          />
          <label className="vlabel">{redValue}</label>
        </div>
        <div className="sliderbox">
          <label className="slabel">G: </label>
          <Slider
            size="medium"
            value={greenValue}
            aria-label="Small"
            valueLabelDisplay="auto"
            min={0}
            max={255}
            onChange={(event, value) => changeVal("green", value)}
          />
          <label className="vlabel">{greenValue}</label>
        </div>
        <div className="sliderbox">
          <label className="slabel">B: </label>
          <Slider
            size="medium"
            value={blueValue}
            aria-label="Small"
            valueLabelDisplay="auto"
            min={0}
            max={255}
            onChange={(event, value) => changeVal("blue", value)}
   
          />
          <label className="vlabel">{blueValue}</label>
        </div>
      </Card>
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
export default RGB;
