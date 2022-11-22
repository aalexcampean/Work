import Year from "./Year";

const getYears = ( jwt: String): Promise<Array<Year>> => {
    return fetch(`${process.env.REACT_APP_SERVER_ADDR}/api/years`, {
        headers: new Headers({
            'Authorization': `Bearer ${jwt}`,
        })
    }).then(response => response.json())
        .then(response => response.map((item: { id: number; year:number }) => new Year(item.id, item.year)));
}
const getUserYears = (username:String, jwt: String): Promise<Array<Year>> => {
    return fetch(`${process.env.REACT_APP_SERVER_ADDR}/api/years/user/` + username, {
        headers: new Headers({
            'Authorization': `Bearer ${jwt}`,
        })
    }).then(response => response.json())
        .then(response => response.map((item: { id: number; year:number }) => new Year(item.id, item.year)));
}

export default {getYears,getUserYears}