import { Button, Card, CardActions, CardContent, CardHeader, createStyles, makeStyles, TextField, Theme } from "@material-ui/core";
import jwtDecode from "jwt-decode";
import { useContext, useEffect, useReducer } from "react";
import { Navigate, useLocation } from "react-router-dom";
import handleLoginResponse from "../utils/handleLoginResponse";
import { authenticationService } from "./authentication.service";
import { Context } from "./authStore";

const useStyles = makeStyles((theme: Theme) =>
  createStyles({
    container: {
      display: 'flex',
      flexWrap: 'wrap',
      width: 400,
      margin: `${theme.spacing(0)} auto`
    },
    loginBtn: {
      marginTop: theme.spacing(2),
      flexGrow: 1
    },
    header: {
      textAlign: 'center',
      background: '#212121',
      color: '#fff'
    },
    card: {
      marginTop: theme.spacing(10)
    }
  })
);



type State={
    username: string
    password: string
    disabledButton: boolean
    helperText: string
    isError: boolean
};

const initialState:State = {
    username: '',
    password: '',
    disabledButton: true,
    helperText: '',
    isError: false
  };

  type Action = { type: 'setUsername', payload: string }
  | { type: 'setPassword', payload: string }
  | { type: 'setIsButtonDisabled', payload: boolean }
  | { type: 'loginSuccess', payload: string }
  | { type: 'loginFailed', payload: string }
  | { type: 'setIsError', payload: boolean };


  const reducer = (state: State, action: Action): State => {
    switch (action.type) {
      case 'setUsername': 
        return {
          ...state,
          username: action.payload
        };
      case 'setPassword': 
        return {
          ...state,
          password: action.payload
        };
      case 'setIsButtonDisabled': 
        return {
          ...state,
          disabledButton: action.payload
        };
      case 'loginSuccess': 
        return {
          ...state,
          helperText: action.payload,
          isError: false
        };
      case 'loginFailed': 
        return {
          ...state,
          helperText: action.payload,
          isError: true
        };
      case 'setIsError': 
        return {
          ...state,
          isError: action.payload
        };
    }
  }

  

  const Login = () => {

    const classes = useStyles();
    const [state, dispatch] = useReducer(reducer, initialState);
    const {authState, authDispatch} = useContext(Context);
    let location = useLocation();

    useEffect(() => {
        if (state.username.trim() && state.password.trim()) {
         dispatch({
           type: 'setIsButtonDisabled',
           payload: false
         });
        } else {
          dispatch({
            type: 'setIsButtonDisabled',
            payload: true
          });
        }
      }, [state.username, state.password]);
      
    //we will get it from the API
    const handleLogin = () => {
      authenticationService.login(state.username, state.password).then((user: any) => {
        authDispatch(({
          type: 'LOGIN',
          payload: user,
        }));
        window.location.reload();

      }, (rejected : any) => {
        //authenticationService.logout();
        authDispatch(({
          type: 'loginFailed',
          payload: 'Wrong username or password',
        }));  
        console.log(rejected);
      },
      (rejected : any) => {
        authenticationService.logout();
        authDispatch(({
          type: 'LOGOUT',
          payload: null,
        }));
        console.log(rejected);
      });
   };
   
  

   const handleKeyPress = (event: React.KeyboardEvent) => {
    if (event.keyCode === 13 || event.which === 13) {
      state.disabledButton || handleLogin();
    }
    };

    const handleUsernameChange: React.ChangeEventHandler<HTMLInputElement> =
  (event) => {
    dispatch({
      type: 'setUsername',
      payload: event.target.value
    });
  };



    const handlePasswordChange: React.ChangeEventHandler<HTMLInputElement> =
  (event) => {
    dispatch({
      type: 'setPassword',
      payload: event.target.value
    });
  };

    return (
      <form className={classes.container} noValidate autoComplete="off">
        <Card className={classes.card}>
          <CardHeader className={classes.header} title="Academic Info" />
          <CardContent>
            <div>
              <TextField
                error={state.isError}
                fullWidth
                id="username"
                type="email"
                label="Username"
                placeholder="Username"
                margin="normal"
                onChange={handleUsernameChange}
                onKeyPress={handleKeyPress}
              />
              <TextField
                error={state.isError}
                fullWidth
                id="password"
                type="password"
                label="Password"
                placeholder="Password"
                margin="normal"
                helperText={state.helperText}
                onChange={handlePasswordChange}
                onKeyPress={handleKeyPress}
              />
            </div>
          </CardContent>
          <CardActions>
            <Button
              variant="contained"
              size="large"
              color="secondary"
              className={classes.loginBtn}
              onClick={handleLogin}
              disabled={state.disabledButton}>
              Login
            </Button>
          </CardActions>
        </Card>
      </form>
    );
  }
  


  export default Login;