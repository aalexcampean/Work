import Course from "./Course";
import Student from "./Student";

const getStudents = (username: String, jwt: String): Promise<Array<Student>> => {
    return fetch(`${process.env.REACT_APP_SERVER_ADDR}/api/student/${username}`, {
        headers: new Headers({
            'Authorization': `Bearer ${jwt}`,
        })
    }).then(response => response.json())
        .then(response => response.map((item: { id: number; fname: String; lname: String; group: number, year: number, grade: number }) => new Student(item.id, item.fname, item.lname, item.group, item.year, item.grade)));
}

const getStudentsByGroup = (jwt: String, group: number): Promise<Array<Student>> => {
    return fetch(`${process.env.REACT_APP_SERVER_ADDR}/api/students/group/2`, {
        headers: new Headers({
            'Authorization': `Bearer ${jwt}`,
        })
    }).then(response => response.json())
        .then(res => {
            console.log(res);
            return res;
        })
        .then(response => response.map((item: { id: number; firstName: String; lastName: String; gradeAverage: number; year: number; group: number }) => new Student(item.id, item.firstName, item.lastName, item.group, item.year, item.gradeAverage)));
}

const getStudentsByYear = (jwt: String, year: number): Promise<Array<Student>> => {
    return fetch(`${process.env.REACT_APP_SERVER_ADDR}/api/students/year/${year}`, {
        headers: new Headers({
            'Authorization': `Bearer ${jwt}`,
        })
    }).then(response => response.json())
        .then(res => {
            console.log(res);
            return res;
        })
        .then(response => response.map((item: { id: number; firstName: String; lastName: String; gradeAverage: number; year: number; group: number }) => new Student(item.id, item.firstName, item.lastName, item.group, item.year, item.gradeAverage)));
}

const signContract = (jwt: String, yearId: Number, selectedCourses: Array<Course>) => {
    const requestOptions = {
        method: 'POST',
        headers: {'Authorization': `Bearer ${jwt}`, 'Content-Type': 'application/json'},
        body: JSON.stringify({'courses': selectedCourses}),
    };
    return fetch(`${process.env.REACT_APP_SERVER_ADDR}/api/profile/sign-contract/${yearId}`, requestOptions);
}

const checkEnrollToYear = (jwt: String, yearId: Number) => {
    const requestOptions = {
        method: 'POST',
        headers: {'Authorization': `Bearer ${jwt}`},
    };
    fetch(`${process.env.REACT_APP_SERVER_ADDR}/api/profile/check-enroll/${yearId}`, requestOptions)
        .then(response => response.json())
        .then(response => response.map((item: { message: string }) => item.message));

}

const enrollToYear = (jwt: String, yearId: Number) => {
    const requestOptions = {
        method: 'POST',
        headers: {'Authorization': `Bearer ${jwt}`},
    };
    return fetch(`${process.env.REACT_APP_SERVER_ADDR}/api/profile/enroll/${yearId}`, requestOptions);
}

export default {getStudents, getStudentsByGroup, getStudentsByYear, checkEnrollToYear, enrollToYear, signContract}