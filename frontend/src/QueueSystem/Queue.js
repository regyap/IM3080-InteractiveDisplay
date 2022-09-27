import React, { useState, useEffect } from "react";
import ListGroup from "react-bootstrap/ListGroup";
import Button from "react-bootstrap/Button";
import Card from "react-bootstrap/Card";
import { useNavigate } from "react-router-dom";
import socketOBJ from "../Socket/SocketIO.js";
import "./Queue.css";

function JoinQueue() {
  const [updatedTime, setUpdatedTime] = useState("");
  const [queueData, setQueueData] = useState([]);
  const navigate = useNavigate();

  useEffect(() => {
    socketOBJ.on("queue", (res) => {
      var msg = res["data"];
      setQueueData(msg);
      const current = new Date();
      setUpdatedTime(current.toLocaleTimeString("en-US"));
      console.log(msg);
    });
  }, []);

  function onExit(e) {
    e.preventDefault();
    //Fix adding username here
    // const data = { username: name, id: socketOBJ.id };
    const data = { id: socketOBJ.id };
    socketOBJ.emit("exitQueue");
    navigate("/");
  }

  return (
    <Card style={{ width: "30rem" }}>
      <Card.Body>
        <Card.Title>Queue</Card.Title>
        <ListGroup variant="flush">
          {/* <ListGroup.Item>Cras justo odio</ListGroup.Item> */}
          {queueData.map((data) => {
            return <ListGroup.Item>{data["username"]}</ListGroup.Item>;
          })}
        </ListGroup>
        <Button variant="danger" className="float-end" onClick={onExit}>
          Exit Queue
        </Button>
      </Card.Body>

      <Card.Footer className="text-muted">
        {"Updated: " + updatedTime}
      </Card.Footer>
    </Card>
  );
}
export default JoinQueue;
