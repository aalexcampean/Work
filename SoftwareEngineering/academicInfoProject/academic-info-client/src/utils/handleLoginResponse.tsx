import jwtDecode from "jwt-decode";
import { authenticationService } from "../Authentication/authentication.service";

export default (response:Response) => {
    return response.text().then(text => {
      const data : any = text && jwtDecode(text);
      data['jwt'] = text;
      if (!response.ok) {
          const error = (data && data.message) || response.statusText;
          return Promise.reject(error);
      }

      return data;
    });
  }