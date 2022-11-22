import Course from "./Course";

const getCourses = (username: String, jwt: String): Promise<Array<Course>> => {
    return fetch(`${process.env.REACT_APP_SERVER_ADDR}/api/course/${username}`, {
        headers: new Headers({
            'Authorization': `Bearer ${jwt}`,
        })
    }).then(response => response.json())
        .then(response => response.map((item: { id: number; name: String; noOfCredits: number; isOptional: boolean; }) => new Course(item.id, item.name, item.noOfCredits, item.isOptional)));
}

const getCoursesByYear = (username: String, jwt: String, yearId: Number): Promise<Array<Course>> => {
    return fetch(`${process.env.REACT_APP_SERVER_ADDR}/api/course/curriculum/${yearId.toString()}`, {
        headers: new Headers({
            'Authorization': `Bearer ${jwt}`,
        })
    }).then(response => response.json())
        .then(response => response.map((item: { id: number; name: String; noOfCredits: number; isOptional: boolean; }) => new Course(item.id, item.name, item.noOfCredits, item.isOptional)));
}

const getCoursesTeacher = (username: String, jwt: String): Promise<Array<Course>> => {
    return fetch(`${process.env.REACT_APP_SERVER_ADDR}/api/course`, {
        headers: new Headers({
            'Authorization': `Bearer ${jwt}`,
        })
    }).then(response => response.json())
        .then(response => response.map((item: { id: number; name: String; noOfCredits: number; isOptional: boolean; }) => new Course(item.id, item.name, item.noOfCredits, item.isOptional)));
}

const getCoursesStudentYear = (username: String, jwt: String, yearId: Number): Promise<Array<Course>> => {
    return fetch(`${process.env.REACT_APP_SERVER_ADDR}/api/course/grades/${username}/${yearId}`, {
        headers: new Headers({
            'Authorization': `Bearer ${jwt}`,
        })
    })
        .then(response => response.json())
        .then(response => response.map((item: { id: number; name: String; noOfCredits: number; isOptional: boolean; curriculumID: number; teacherID: number; }) => new Course(item.id, item.name, item.noOfCredits, item.isOptional)))
        .catch(error => console.log(error.message)); // logs any error from the promise
}

const proposeOptionalCourses = (jwt: String, name: String, credits: number, isOptional: boolean): any => {
    const requestOptions = {
        method: 'POST',
        headers: {'Authorization': `Bearer ${jwt}`, 'Content-Type': 'application/json'},
        body: JSON.stringify({'name': name, 'credits': credits, 'isOptional': isOptional}),
    };

    return fetch(`${process.env.REACT_APP_SERVER_ADDR}/api/courses/optional`, requestOptions)
}


export default {getCourses, getCoursesTeacher, getCoursesByYear, proposeOptionalCourses, getCoursesStudentYear}