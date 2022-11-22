import {useContext, useEffect, useState} from 'react';
import {Context} from '../Authentication/authStore';
import Course from './Course';
import courseService from './course.service';
import './StudentCourses.css';
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
import { useNavigate } from "react-router-dom";
import {authenticationService} from "../Authentication/authentication.service";
import Table from 'react-bootstrap/Table'
import NavigationBar from '../ReusableComponents/NavigationBar';

const StudentCourses = () => {

    
    const {authState, authDispatch} = useContext(Context);
    var courseList = new Array<Course>();
    const [courses, setCourses] = useState(new Array<Course>());
    

    useEffect(() => {
        const fun = async () => {
            return await courseService.getCourses(authState.username!, authState.token!)
        };
        fun().then(item => setCourses(item));
    }, []);

     //we will get it from the API
     let navigate = useNavigate();
     const handleLogout = () => {
         authenticationService.logout();
         authDispatch(({
             type: 'LOGOUT',
             payload: null,
         }));
 
         let path = `/login`;
         navigate(path);
         window.location.reload();
     };
     
     const handleViewGrades=()=>{
         let path="/grades"
         navigate(path);
         window.location.reload();
     }

     const handleEnrol=()=>{
        let path="/enrol"
        navigate(path);
        window.location.reload();
     }
    
    const handleSignContracts=()=>{
        let path="/sign"
        navigate(path);
        window.location.reload();
    }
    

    return (
        <div>
        <NavigationBar />

        <div className="container">
            <h1>Student courses</h1>
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
                        id="enrol-to-years-button"
                        variant="contained"
                        size="large"
                        color="primary"
                        onClick={handleEnrol}
                        >
                        Enrol to a year or 2 of study
                    </Button>
                    <Button
                        id="view-grades-button"
                        variant="contained"
                        size="large"
                        color="primary"
                        onClick={handleViewGrades}
                        >
                        View Grades 
                    </Button>
                    <Button
                        id="sign-contracts-button"
                        variant="contained"
                        size="large"
                        color="primary"
                        onClick={handleSignContracts}
                        >
                        Sign contracts 
                    </Button>

                </CardActions>


            </div>
        </div>
    );
};

export default StudentCourses;