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
import React, {useContext, useEffect, useReducer, useState} from 'react';
import { useNavigate } from "react-router-dom";
import {authenticationService} from "../Authentication/authentication.service";
import {Context} from '../Authentication/authStore';
import Login from "../Authentication/Login";
import Course from '../Course/Course';
import courseService from '../Course/course.service';
import '../Course/TeacherCourses.css';
import Table from 'react-bootstrap/Table'
import { FormControl } from "react-bootstrap";
import UserCourses from '../Course/UserCourses';
import usercourseService from '../Course/usercourses.service';

const AddGrades = () => {

    const {authState, authDispatch} = useContext(Context);

    var courseList = new Array<Course>();
    const [courses, setCourses] = useState(new Array<Course>());
    const [usercourses, setUserCourses] = useState(new Array<UserCourses>());
    useEffect(() => {
        const fun = async () => {
            return await courseService.getCourses(authState.username!, authState.token!)
        };
        fun().then(item => setCourses(item));
    }, []);

    useEffect(() => {
        const fun = async () => {
            return await usercourseService.getUserCourses(authState.username!, authState.token!)
        };
        fun().then(item => setUserCourses(item));
    }, []);

    return (
        <body>
        
        <div className="container">
            <h4>Your grades: </h4>
            <Table className="table table-striped table-bordered">
            <thead>
                    <tr>
                        <th>Course name</th>
                        <th>Credits</th>
                        <th>Optional/Mandatory</th>
                        <th>Grade</th>
                    </tr>
                </thead>
                <tbody>
                    {courses&&courses.map(item => (
                    <tr key={item.Id}> 
                        <td > {item.Name}</td>
                        <td >{item.NoOfCredits} </td>
                        <td >{item.IsOptional ? "Optional" : "Mandatory"}</td>
                       
                    </tr>

                ) )}
                </tbody>
                </Table> 
            
        </div>
        
        </body>

    );
};

export default AddGrades;