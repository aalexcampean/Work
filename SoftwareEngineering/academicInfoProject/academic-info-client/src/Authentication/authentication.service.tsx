import {useContext} from "react";
import handleLoginResponse from "../utils/handleLoginResponse";
import {Context} from "./authStore";


const login = (username: String, password: String): any => {
    const requestOptions = {
        method: 'POST',
        headers: {'Content-Type': 'application/json'},
        body: JSON.stringify({'username': username, 'password': password}),
    };
    console.log(process.env.REACT_APP_SERVER_ADDR)
    return fetch(`${process.env.REACT_APP_SERVER_ADDR}/api/authentication/login`, requestOptions)
        .then(handleLoginResponse)
        .then(user => {
                localStorage.setItem('jwt', user['jwt']);
                localStorage.setItem('username', user['username']);
                localStorage.setItem('role', user['http://schemas.microsoft.com/ws/2008/06/identity/claims/role'])
                return {
                    username: user['username'],
                    "token": user['jwt'],
                    'role': user['http://schemas.microsoft.com/ws/2008/06/identity/claims/role']
                };
            }, (rejected: any) => {
                console.log(rejected);
                return Promise.reject(rejected);
            }
        );
}

const logout = () => {
    localStorage.removeItem('jwt');
    localStorage.removeItem('username');
    localStorage.removeItem('role');

}
export const authenticationService = {login, logout};