import {
    Button,
    Card,
    CardActions,
    CardContent,
    CardHeader,
    createStyles,
    makeStyles,
    TextField,
    Theme
} from "@material-ui/core";
import React, {useContext, useEffect, useReducer, useState} from 'react';
import {useNavigate} from "react-router-dom";
import {authenticationService} from "../Authentication/authentication.service";
import {Context} from '../Authentication/authStore';
import Login from "../Authentication/Login";
import Course from './Course';
import courseService from './course.service';
import Table from 'react-bootstrap/Table';
import NavigationBar from '../ReusableComponents/NavigationBar';
// Styling
import './TeacherCourses.css';

const TeacherCourses = () => {

    const {authState, authDispatch} = useContext(Context);
 
    var courseList = new Array<Course>();
    const [courses, setCourses] = useState(new Array<Course>());

    useEffect(() => {
        const fun = async () => {
            return await courseService.getCoursesTeacher(authState.username!, authState.token!)
        };
        fun().then(item => {
            setCourses(item)
        });
    }, []);

    //we will get it from the API
    let navigate = useNavigate();
    const handlePropose = () => {
       
        let path = `/propose-optional-courses`;
        navigate(path);
        window.location.reload();
    };
    const handleAddGrades = () => {
       
        let path = `/add-grades`;
        navigate(path);
        window.location.reload();
    };


    return (
        <>
            <NavigationBar  />
            <div className="container">
                <h1>Teacher courses</h1>
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
                      <CardActions>
                        <Button
                            id="propose-optional-button"
                            variant="contained"
                            size="large"
                            color="primary"
                            onClick={handlePropose}
                            >
                            Propose Optional Courses
                        </Button>
                        <Button
                            id="add-grades-button"
                            variant="contained"
                            size="large"
                            color="primary"
                            onClick={handleAddGrades}
                            >
                            Add Grades 
                        </Button>
                    </CardActions>
            </div>
        </>
    );
};

export default TeacherCourses;