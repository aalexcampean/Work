import UserCourses from "./UserCourses";

const getUserCourses =  (username: String ,jwt: String) : Promise<Array<UserCourses>> => {
    return fetch(`${process.env.REACT_APP_SERVER_ADDR}/api/course/${username}`, { 
        headers: new Headers({
            'Authorization': `Bearer ${jwt}`, 
        })
    }).then(response => response.json())
    .then(response => response.map( (item: { id:number,name: String; noOfCredits: number; isOptional: boolean; grade:number }) => new UserCourses( item.id, item.name, item.noOfCredits, item.isOptional,item.grade)));
}
const getUserCoursesByYear = (username: String, year: Number, jwt: String): Promise<Array<UserCourses>> => {
    return fetch(`${process.env.REACT_APP_SERVER_ADDR}/api/course/grades/${username}/${year.toString()}`, {
        headers: new Headers({
            'Authorization': `Bearer ${jwt}`,
        })
    }).then(response => response.json())
        .then(response => response.map((item: { id: number; name: String; noOfCredits: number; isOptional: boolean; grade: number}) => new UserCourses(item.id, item.name, item.noOfCredits, item.isOptional, item.grade)));
}

export default {getUserCourses, getUserCoursesByYear}