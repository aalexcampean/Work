import {
    Button,
    Card,
    CardActions,
    CardContent,
    CardHeader,
    Checkbox,
    createStyles,
    Input,
    makeStyles,
    OutlinedInput,
    TextField,
    Theme
} from "@material-ui/core";
import React, {useContext, useEffect, useReducer, useState} from 'react';
import {useNavigate} from "react-router-dom";
import {authenticationService} from "../Authentication/authentication.service";
import {Context} from '../Authentication/authStore';
import Login from "../Authentication/Login";
import Course from '../Course/Course';
import courseService from '../Course/course.service';
import studentService from '../Course/student.service';
import '../Course/TeacherCourses.css';
import Table from 'react-bootstrap/Table'
import Dropdown from 'react-dropdown';
import {FormControl} from "react-bootstrap";
import UserCourses from '../Course/UserCourses';
import usercourseService from '../Course/usercourses.service';
import yearService from "../Year/year.service";
import Year from "../Year/Year";
import NavigationBar from "../ReusableComponents/NavigationBar";
// Styling
import './EnrollToYear.css';

const EnroltoYear = () => {

    const {authState, authDispatch} = useContext(Context);

    const [selectedYear, setSelectedYear] = useState(new Year(-1, -1));
    const [years, setYears] = useState(new Array<Year>());
    const [enrolledYears, setEnrolledYears] = useState(new Array<Year>());
    const [courses, setCourses] = useState(new Array<Course>());

    const [disableEnrollButton, setDisableEnrollButton] = useState(false);
    const [visibleAlreadyEnrolledMessage, setVisibleAlreadyEnrolledMessage] = useState(false);

    const [enrollMessage, setEnrollMessage] = useState('');
    const [selectedYearsCount, setSelectedYearsCount] = useState(0);

    useEffect(() => {
        const getEnrolledYears = async () => {
            return await yearService.getUserYears(authState.username!, authState.token!);
        };
        const getAllYears = async () => {
            return await yearService.getYears(authState.token!)
        };

        getAllYears().then(item => {
            setYears(item);
            if (item.length > 0) {
                setSelectedYear(item[0]);
            }
        });
        getEnrolledYears().then(item => {
            setEnrolledYears(item);
        })
    }, []);

    useEffect(() => {
        const checkIfEnrolled = async () => {
            if (selectedYear !== null) {
                if (enrolledYears.filter(year => year.Id === selectedYear.Id).length > 0) {
                    setEnrollMessage('Already enrolled in this year!');
                    setVisibleAlreadyEnrolledMessage(true);
                    setDisableEnrollButton(true);
                } else if (enrolledYears.length == 2) {
                    setEnrollMessage('Already enrolled in 2 year!');
                    setVisibleAlreadyEnrolledMessage(true);
                    setDisableEnrollButton(true);
                } else {
                    setVisibleAlreadyEnrolledMessage(false);
                    setDisableEnrollButton(false);
                }
            }
        }
        const getAllCoursesInYear = async () => {
            if (selectedYear !== null) {
                return await courseService.getCoursesByYear(authState.username!, authState.token!, selectedYear.Id!);
            } else return await courseService.getCourses(authState.username!, authState.token!);
        };

        try {
            checkIfEnrolled();
            getAllCoursesInYear()
                .then(yearCourses => {
                    setCourses(yearCourses);
                })
        } catch (error) {
            console.log(error);
            alert(error);
        }
        setSelectedYearsCount(0);
    }, [selectedYear]);

    const onSelectYear = (textYear: any) => {
        setSelectedYear(new Year(Number.parseInt(textYear.value), Number.parseInt(textYear.label)))
    }

    const handleEnrol = () => {
        studentService.enrollToYear(authState.token!, selectedYear.Id!);
        window.alert('Successfully enrolled!')
        window.location.reload();
    };

    return (
        <>
            <NavigationBar></NavigationBar>
            <div className="container">
                <h1>Enrol to a year or 2 of study</h1>
                <h4>Year:</h4>
                <Dropdown
                    arrowClosed={<span className="arrow-closed"/>}
                    arrowOpen={<span className="arrow-open"/>}
                    options={years.map(item => new Option(item.Year.toString(), item.Id.toString()))}
                    onChange={onSelectYear}
                    value={selectedYear.Year === -1 ? new Option('', '') : new Option(selectedYear.Year.toString(), selectedYear.Id.toString())}
                    placeholder="Select an option">
                </Dropdown>

                <h4>Your courses: </h4>
                <Table className="table table-striped table-bordered">
                    <thead>
                    <tr>
                        <th>Course name</th>
                        <th>Credits</th>
                        <th>Optional/Mandatory</th>

                    </tr>
                    </thead>
                    <tbody>
                    {courses && courses.map(course => (
                        <tr key={course.Id}>
                            <td> {course.Name}</td>
                            <td>{course.NoOfCredits} </td>
                            <td>{course.IsOptional ? "Optional" : "Mandatory"}</td>
                        </tr>
                    ))}
                    </tbody>
                </Table>
                <CardActions className='centered-container'>
                    <Button
                        id="sign-contracts-button"
                        variant="contained"
                        size="large"
                        color="primary"
                        disabled={disableEnrollButton}
                        onClick={handleEnrol}>
                        Enrol
                    </Button>
                    <h5 id="already-enrolled-message"
                        hidden={!visibleAlreadyEnrolledMessage}>{enrollMessage}</h5>
                </CardActions>
            </div>
        </>
    );
};

export default EnroltoYear;