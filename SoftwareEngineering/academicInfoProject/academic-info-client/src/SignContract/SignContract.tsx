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
import {useNavigate} from "react-router-dom";
import {authenticationService} from "../Authentication/authentication.service";
import {Context} from '../Authentication/authStore';
import Login from "../Authentication/Login";
import Course from '../Course/Course';
import courseService from '../Course/course.service';
import '../Course/TeacherCourses.css';
import Table from 'react-bootstrap/Table'
import Dropdown from 'react-dropdown';
import {FormControl} from "react-bootstrap";
import UserCourses from '../Course/UserCourses';
import usercourseService from '../Course/usercourses.service';
import studentService from '../Course/student.service';
import Year from "../Year/Year";
import yearService from "../Year/year.service";
import NavigationBar from "../ReusableComponents/NavigationBar";
// Styling
import './SignContract.css';

const SignContract = () => {

    const {authState, authDispatch} = useContext(Context);

    const [selectedYear, setSelectedYear] = useState(new Year(-1, -1));
    const [years, setYears] = useState(new Array<Year>());
    const [courses, setCourses] = useState(new Array<Course>());

    const [disableSignButton, setDisableSignButton] = useState(false);
    const [disableSignInput, setDisableSignInput] = useState(false);
    const [signitureInput, setSignitureInput] = useState('');

    const [selectedOptionalCount, setSelectedOptionalCount] = useState(0);
    const [mandatoryCoursesCount, setMandatoryCoursesCount] = useState(0);

    const [visibleAlreadySignedMessage, setVisibleAlreadySignedMessage] = useState(false);
    const [signMessage, setSignMessage] = useState('');

    useEffect(() => {
        const fun = async () => {
            return await yearService.getUserYears(authState.username!, authState.token!);
        };
        fun().then(item => {
            setYears(item);
            if (item.length > 0) {
                setSelectedYear(item[0]);
            }
        });
    }, []);
    
    useEffect(() => {
        console.log(mandatoryCoursesCount);
        console.log(courses.length);
        console.log(selectedOptionalCount);
        if (signitureInput !== '' && (mandatoryCoursesCount === courses.length || selectedOptionalCount > 0)) {
            setDisableSignButton(false);
        } else {
            setDisableSignButton(true);
        }

    }, [signitureInput, selectedOptionalCount, mandatoryCoursesCount]);
    

    useEffect(() => {
        const getAllCoursesInYear = async () => {
            if (selectedYear !== null) {
                return await courseService.getCoursesByYear(authState.username!, authState.token!, selectedYear.Id!);
            } else return await courseService.getCourses(authState.username!, authState.token!);
        };

        const getAllCoursesInContract = async () => {
            if (selectedYear !== null) {    
                return await courseService.getCoursesStudentYear(authState.username!, authState.token!, selectedYear.Id!);
            } else return await courseService.getCourses(authState.username!, authState.token!);
        };

        try {
            getAllCoursesInContract()
                .then(contractCourses => {
                    if (contractCourses.length == 0) {
                        getAllCoursesInYear().then(yearCourses => {
                            setCourses(yearCourses);
                        })
                        setDisableSignInput(false);
                        setSignMessage("");
                        setVisibleAlreadySignedMessage(false);
                    } else {
                        setCourses(contractCourses);
                        setCourses(contractCourses.map(course => {
                            course.IsDisabled = true;
                            course.IsChecked = true;
                            return course
                        }));
                        setSignMessage("Contract already signed");
                        setVisibleAlreadySignedMessage(true);
                        setDisableSignInput(true);
                        setDisableSignButton(true);
                    }
                })
        } catch (error) {
            console.log(error);
            alert(error);
        }


        const countMandatoryCourses = () => {
            var count = 0
            courses.forEach(course => {
                if (!course.IsOptional) count++;
            })
            setMandatoryCoursesCount(count);
        }
        
        countMandatoryCourses();
        setSignitureInput("");
        setSelectedOptionalCount(0);
    }, [selectedYear]);


    useEffect(() => {
        // If we selected 3 optional courses => all other optional courses will be disabled
        if (selectedOptionalCount === 3) {
            setCourses(courses.map(course => {
                if (course.IsOptional && !course.IsChecked) {
                    course.IsDisabled = true;
                }
                return course
            }));
        } else if (selectedOptionalCount < 3) {
            setCourses(courses.map(course => {
                if (course.IsOptional && !course.IsChecked) {
                    course.IsDisabled = false;
                }
                return course
            }));
        }
    }, [selectedOptionalCount]);

    const handleSignContracts = () => {
        const selectedCourses = courses.filter(course => course.IsChecked);
        studentService.signContract(authState.token!, selectedYear.Id!, selectedCourses);
        window.alert('Contract successfully signed!')
        window.location.reload();
    };

    const onSelectYear = (textYear: any) => {
        setSelectedYear(new Year(Number.parseInt(textYear.value), Number.parseInt(textYear.label)))
    }

    const onCheckOptionalCourse = (inputCourse: Course) => {
        // Checking if we're checking or uncheking a course
        if (inputCourse.IsChecked === false) {
            setSelectedOptionalCount(prevCount => prevCount + 1);
        } else setSelectedOptionalCount(prevCount => prevCount - 1);

        // Modifying the "IsChecked" valued of the course in the list
        setCourses(courses.map(course => {
            if (course.Id === inputCourse.Id) {
                course.IsChecked = !inputCourse.IsChecked;
            }
            return course;
        }));
    }

    const onInputSigniture = (e: any) => {
        setSignitureInput(e.currentTarget.value);
    }

    return (
        <>
            <NavigationBar></NavigationBar>
            <div className="container">
                <h4>Year:</h4>
                <Dropdown
                    arrowClosed={<span className="arrow-closed"/>}
                    arrowOpen={<span className="arrow-open"/>}
                    options={years.map(item => new Option(item.Year.toString(), item.Id.toString()))}
                    onChange={onSelectYear}
                    value={selectedYear.Year === -1 ? new Option('', '') : new Option(selectedYear.Year.toString(), selectedYear.Id.toString())}
                    placeholder="Select an option"></Dropdown>

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
                            <td><input type='checkbox' checked={course.IsChecked} disabled={course.IsDisabled}
                                       onChange={() => onCheckOptionalCourse(course)}/></td>
                        </tr>
                    ))}
                    </tbody>
                </Table>

            </div>
            <div className="container">
                <CardActions className='centered-container'>
                    <TextField
                        id="signiture-input"
                        variant="outlined"
                        label="Your Signiture"
                        value={signitureInput}
                        disabled={disableSignInput}
                        onChange={onInputSigniture}
                    />
                    <Button
                        id="sign-contracts-button"
                        variant="contained"
                        size="large"
                        color="primary"
                        disabled={disableSignButton}
                        onClick={handleSignContracts}
                    >
                        Sign contract
                    </Button>
                    <h5 id="already-signed-message"
                        hidden={!visibleAlreadySignedMessage}>{signMessage}</h5>
                </CardActions>
            </div>
        </>
    );
};

export default SignContract;