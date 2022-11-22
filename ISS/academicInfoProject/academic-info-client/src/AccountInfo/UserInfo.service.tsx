import UserInfo from './UserInfo'

class UserInfoService {
    public getUserInfo = (jwt: String): Promise<UserInfo> => {
        // @ts-ignore
        return fetch(`${process.env.REACT_APP_SERVER_ADDR}/api/profile`, {
            headers: new Headers({'Authorization': `Bearer ${jwt}`})
        })
            .then(response => response.json())
            .then(responseJson => new UserInfo(responseJson.firstName, responseJson.lastName, responseJson.email, responseJson.phoneNumber))
            .catch(error => console.log('There was an error: ' + error))
    }

    public setUserInfo = (jwt: String, firstName: String, lastname: String, email: String, phone: String): any => {
        const requestOptions = {
            method: 'POST',
            headers: {'Authorization': `Bearer ${jwt}`, 'Content-Type': 'application/json'},
            body: JSON.stringify({'firstName': firstName, 'lastName': lastname, 'email': email, 'phoneNumber': phone}),
        };

        return fetch(`${process.env.REACT_APP_SERVER_ADDR}/api/profile`, requestOptions)
    }
}

export default UserInfoService;