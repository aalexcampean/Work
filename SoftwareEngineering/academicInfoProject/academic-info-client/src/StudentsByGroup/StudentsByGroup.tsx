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

import Table from 'react-bootstrap/Table'

import Student from "../Course/Student";
import studentService from "../Course/student.service";

const StudentsByGroup = () => {

    const {authState, authDispatch} = useContext(Context);

    var studentsList = new Array<Student>();
    const [students, setStudents] = useState(new Array<Student>());
    
    const [isDisabled, setIsDisabled] = useState(false);
    useEffect(() => {
        const fun = async () => {
            return await studentService.getStudentsByGroup(authState.token!, 2)
        };
        fun().then(item => setStudents(item));
    }, []);
    
    const handleSignContracts = () => {
        setIsDisabled(!isDisabled)
    };


    return (
        <body>
        <div className="container">
            <h4>Students by group: </h4>
            <Table className="table table-striped table-bordered">
            <thead>
                    <tr>
                        <th>Student id</th>
                        <th>Student name</th>
                        <th>Average Grade</th>
                        <th>Year</th>
                        <th>Group</th>
                        
                    </tr>
                </thead>
                <tbody>
                    {students&&students.map(item => (
                    <tr key={item.Id}> 
                        <td>{item.Id}</td>
                        <td > {item.firstName} {item.lastName}</td>
                        <td >{item.Group}</td>
                        <td >{item.Year}</td>
                        <td>{item.Grade}</td>
                    </tr>

                ) )}
                </tbody>
                </Table> 
            
        </div>
    
        
        </body>

    );
};

export default StudentsByGroup;