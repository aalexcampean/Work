import {
    Button,
    Card,
    CardActions,
    CardContent,
    CardHeader,
    createStyles,
    
    Input,
    makeStyles,
    OutlinedInput,
    TextField,
    Theme
} from "@material-ui/core";
import React, {useContext, useEffect, useReducer, useState, useRef} from 'react';
import { useNavigate } from "react-router-dom";
import {authenticationService} from "../Authentication/authentication.service";
import {Context} from '../Authentication/authStore';
import Login from "../Authentication/Login";
import Course from '../Course/Course';
import courseService from '../Course/course.service';
import '../Course/TeacherCourses.css';
import Table from 'react-bootstrap/Table'
import Popup from './Popup';
import { FormControl } from "react-bootstrap";

const ProposeOptionalCourses = () => {

   

    const {authState, authDispatch} = useContext(Context);
    const [isOpen, setIsOpen] = useState(false);
    const [clickList, setClickList] = React.useState(
        [...Array(1).keys()].map(x => ({ id: `button-propose ${x + 1}`, value: 0 }))
      );
      const buttonClick = (idx: number) => (e: any) => {
        const result = [...clickList];
        result[idx].value += 1;
        setClickList(result);
        setIsOpen(!isOpen);
       
      };
      const togglePopup = () => {
        setIsOpen(!isOpen);
      }
      const valueRef1 = useRef('')
      const valueRef2 = useRef('')
      const valueRef3 = useRef('')
      
      const handleYes = async () => {
        setIsOpen(!isOpen);
        const credits = Number(valueRef2.current);
        
        var isOptional = false;
        if (valueRef3.current == 'yes' || valueRef3.current == 'Yes')
            isOptional = true;
        else if (valueRef3.current == 'no' || valueRef3.current == 'No')
            isOptional = false;
        
        return await courseService.proposeOptionalCourses(authState.username!, valueRef1.current,  credits, isOptional)
      }

    var courseList = new Array<Course>();
    const [courses, setCourses] = useState(new Array<Course>());
    useEffect(() => {
        const fun = async () => {
            return await courseService.getCourses(authState.username!, authState.token!)
        };
        fun().then(item => setCourses(item));
    }, []);

    return (
        <body>
        
        <div className="container">
            <h4>List of optional courses approved until now</h4>
            <Table className="table table-striped table-bordered">
            <thead>
                    <tr>
                        <th>Course name</th>
                        <th>Credits</th>
                        <th>Optional/Mandatory</th>
                    </tr>
                </thead>
                <tbody>
                    {courses&&courses.map(item => (
                    <tr key={item.Id}> 
                        <td > {item.Name}</td>
                        <td >{item.NoOfCredits} </td>
                        <td >{item.IsOptional ? "Optional" : "Mandatory"}</td>
                    </tr>
                ))}
                </tbody>
                </Table> 
            
        </div>
        <div className="container">
            <div>
            <TextField inputRef={valueRef1}   id="outlined-basic" label="Input the course name" variant="outlined" /> 
            </div>
            <div>
            <TextField inputRef={valueRef1} id="outlined-basic" label="Input the credits" variant="outlined" /> 
            </div>
            <div>
            <TextField inputRef={valueRef1} id="outlined-basic" label="Is it optional?(Yes/No)" variant="outlined" /> 
            </div>
            
            <div>
            <Button
                        onClick={buttonClick(0)}
                        id="propose-button"
                        variant="contained"
                        size="large"
                        color="primary">
                        Propose
             </Button>

            </div>
            
            <div>
              { clickList[0].value > 2 &&
                <h6>You cannot propose more than 2 optional courses!</h6> }
            </div>
            {clickList[0].value < 3 && isOpen && <Popup
                content={<>
            <b>     Are you sure you want to propose this course?          </b>
            <Button
                        onClick={handleYes}
                        id="yes"
                        variant="contained"
                        size="large"
                        color="primary">
                        Yes
             </Button>
             <Button
                        onClick={togglePopup}
                        id="no"
                        variant="contained"
                        size="large"
                        color="primary">
                        No
             </Button>
            
            
             </>}
            handleClose={togglePopup}
    />}
           
        
        </div>
        </body>

    );
};

export default ProposeOptionalCourses;