import React, {useState, useEffect} from "react";
import {useRef} from "react"; 
import './Index.css';
// import button from './button.js'
// import button from 'react-bootstrap/esm/button';


function FrontPage(){
    const [facts, setFacts] = useState("");

    function okjhgvc()
    {
        fetch("https://catfact.ninja/fact")
        .then((response) => response.json())
        .then((data)=> {setFacts(data["fact"])
        console.log(data["fact"])}

        
        )

        //get states of 2 buttons and check if array is 0
        // if 0 then post then refresh the array

        // const forminput = useRef("")
        // const[submitted,setsubmitted] = useState([])


        
        
        
    };

        

    return(
        <>

        
            <div>{facts}</div>
            <form >
            <div class="forminput">
            
            <button 
            
            name="Default" 
            value="Default"
            id="Default"
            onClick={okjhgvc}
            > 
            Default

            </button>
             </div>
              <div class="forminput">
            <button 
            
            name="Theme" 
            value="Theme"
            id="Theme"
            onClick={okjhgvc}> 
            Theme
            </button>
            
            </div>
            </form>
            
            </>
        
    );
}
export default FrontPage;