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
import Dropdown from 'react-dropdown';
import Year from "../Year/Year";
import yearService from "../Year/year.service";

const ViewGradesStudent = () => {

    const {authState, authDispatch} = useContext(Context);

    const [selectedYear, setSelectedYear] = useState(new Year(-1,-1));
    const [years, setYears] = useState(new Array<Year>());

    var courseList = new Array<Course>();
    const [courses, setCourses] = useState(new Array<Course>());
    const [usercourses, setUserCourses] = useState(new Array<UserCourses>());

    useEffect(() => {
        const fun = async () => {
            return await yearService.getUserYears(authState.username!, authState.token!)
        };
        fun().then(item =>{
             setYears(item);
             if (item.length > 0){
             setSelectedYear(item[0]);
             }
    });
    }, []);

    useEffect(() => {
        const fun = async () => {
            if (selectedYear != null){
                return await usercourseService.getUserCoursesByYear(authState.username!,selectedYear.Year!, authState.token!);
                //return await usercourseService.getUserCourses(authState.username!, authState.token!);
            }
            else return await usercourseService.getUserCourses(authState.username!, authState.token!);
        };
        fun().then(item => setUserCourses(item));
    },  [selectedYear]);

    const onSelectYear = (textYear: any) => {
        setSelectedYear(new Year(Number.parseInt(textYear.value),Number.parseInt(textYear.label) ))
    }
   /*
    useEffect(() => {
        const fun = async () => {
            return await usercourseService.getUserCourses(authState.username!, authState.token!)
        };
        fun().then(item => setUserCourses(item));
    }, [usercourses]);
    */
    console.log(usercourses);
    return (
        <body>
        
        <div className="container">
            <h4>Year:</h4>
            <Dropdown  
            arrowClosed={<span className="arrow-closed" />}
            arrowOpen={<span className="arrow-open" />} options={years.map(item => new Option(item.Year.toString(), item.Id.toString()))}  onChange={onSelectYear} value={new Option(selectedYear.Year.toString(), selectedYear.Id.toString())} placeholder="Select an option"></Dropdown>

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
                    {usercourses&&usercourses.map(item => (
                    <tr key={item.Id}> 
                        <td > {item.Name}</td>
                        <td >{item.NoOfCredits} </td>
                        <td >{item.IsOptional ? "Optional" : "Mandatory"}</td>
                        <td>{item.Grade}</td>
                    </tr>

                ) )}
                </tbody>
                </Table> 
            
        </div>
        
        </body>

    );
};

export default ViewGradesStudent;