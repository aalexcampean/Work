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
import Dropdown from 'react-dropdown';
import Table from 'react-bootstrap/Table'

import Student from "../Course/Student";
import studentService from "../Course/student.service";
import Year from "../Year/Year";
import yearService from "../Year/year.service";
import NavigationBar from "../ReusableComponents/NavigationBar";

const StudentsByYear = () => {

    const {authState, authDispatch} = useContext(Context);

    const [selectedYear, setSelectedYear] = useState(new Year(-1, -1));
    const [years, setYears] = useState(new Array<Year>());
    const [students, setStudents] = useState(new Array<Student>());


    useEffect(() => {
        const fun = async () => {
            return await yearService.getYears(authState.token!);
        };
        fun().then(item => {
            setYears(item);
            if (item.length > 0) {
                setSelectedYear(item[0]);
            }
        });
    }, []);

    useEffect(() => {
        const getStudentsInYear = async () => {
            if (selectedYear !== null) {
                return await studentService.getStudentsByYear(authState.token!, selectedYear.Id!)
            } else return await studentService.getStudents(authState.username!, authState.token!);
        };
        console.log("here");
        try {
            getStudentsInYear()
                .then(item => {
                    setStudents(item);
                    console.log(item);
                })
        } catch (error) {
            console.log(error);
            alert(error);
        }
    }, [selectedYear]);

    const onSelectYear = (textYear: any) => {
        setSelectedYear(new Year(Number.parseInt(textYear.value), Number.parseInt(textYear.label)))
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
                    placeholder="Select an option">
                </Dropdown>

                <h4>Students by year: </h4>
                <Table className="table table-striped table-bordered">
                    <thead>
                    <tr>
                        <th>Student name</th>
                        <th>Year</th>
                        <th>Group</th>
                        <th>Grade</th>

                    </tr>
                    </thead>
                    <tbody>
                    {students && students.map(item => (
                        <tr key={item.Id}>
                            <td> {item.firstName} {item.lastName}</td>
                            <td>{item.Year}</td>
                            <td>{item.Group}</td>
                            <td>{item.Grade == 0 ? "N/A" : item.Grade}</td>
                        </tr>

                    ))}
                    </tbody>
                </Table>

            </div>
        </>

    );
};

export default StudentsByYear;