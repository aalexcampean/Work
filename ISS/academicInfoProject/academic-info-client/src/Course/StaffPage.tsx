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

const StaffPage = () => {

    const homePath='/staff-page';
    const {authState, authDispatch} = useContext(Context);


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
     
     const handleGetByGroup=()=>{
         let path="/studentsGroup"
         navigate(path);
         window.location.reload();
     }

     const handleGetByYear=()=>{
        let path="/studentsYear"
        navigate(path);
        window.location.reload();
     }
    
   
    

    return (
        <div>
        <NavigationBar />

        <div className="container">
        <CardActions>
                    <Button
                        id="getStudentsByGroup"
                        variant="contained"
                        size="large"
                        color="primary"
                        onClick={handleGetByGroup}
                        >
                        Get students by group
                    </Button>
                    <Button
                        id="getStudentsByYear"
                        variant="contained"
                        size="large"
                        color="primary"
                        onClick={handleGetByYear}
                        >
                        Get students by year 
                    </Button>
                    

                </CardActions>


            </div>
        </div>
    );
};

export default StaffPage;