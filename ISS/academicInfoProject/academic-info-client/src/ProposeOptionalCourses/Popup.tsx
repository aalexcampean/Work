import { Button } from "@material-ui/core";
import React from "react";
 
const Popup = (props: { handleClose: React.MouseEventHandler<HTMLSpanElement> | undefined; content: boolean | React.ReactChild | React.ReactFragment | React.ReactPortal | null | undefined; }) => {
  return (
    <div className="popup-box">
      <div className="box">
        
     
        {props.content}
      </div>
    </div>
  );
};
 
export default Popup;