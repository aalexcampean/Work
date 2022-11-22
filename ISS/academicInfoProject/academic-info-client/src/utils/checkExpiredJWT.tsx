import jwtDecode from "jwt-decode";

const checkExpiredJWT = (jwt: string) => {
    var decodedToken : any = jwtDecode(jwt);
    var dateNow = new Date();

    if(decodedToken['exp'] * 1000 < dateNow.getTime())
         return true;
    return false
}

export default checkExpiredJWT;