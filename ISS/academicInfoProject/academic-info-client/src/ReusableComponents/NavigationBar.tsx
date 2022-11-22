import {Button, CardActions} from '@material-ui/core';
import React, {useContext} from 'react';
import {useNavigate} from 'react-router-dom';
import {authenticationService} from '../Authentication/authentication.service';
import {Context} from '../Authentication/authStore';
// Styling
import './NavigationBar.css';

const NavigationBar = () => {
    const {authState, authDispatch} = useContext(Context);

    //we will get it from the API
    let navigate = useNavigate();

    const handleNavigateHome = () => {
        let path='/'
        navigate(path);
        window.location.reload();
    }

    const handleSeeAccount = () => {
        let path = `/account-info`;
        navigate(path);
        window.location.reload();
    }

    const handleLogout = () => {
        authenticationService.logout();
        authDispatch(({
            type: 'LOGOUT',
            payload: null,
        }));

        let path = `/login`;
        navigate(path);
        window.location.reload();
    };

    return (
        <nav id="nav-bar">
            <div id="nav-title">
                <Button
                    id="home-button"
                    variant="text"
                    disableRipple
                    onClick={handleNavigateHome}>
                    <h1>Academic Info</h1>
                </Button>
            </div>
            <div id="nav-buttons">
                <Button
                    id="nav-button"
                    variant="contained"
                    size="large"
                    color="secondary"
                    onClick={handleSeeAccount}>
                    Account
                </Button>
                <Button
                    id="nav-button"
                    variant="contained"
                    size="large"
                    color="secondary"
                    onClick={handleLogout}>
                    Logout
                </Button>
            </div>
        </nav>
    )
}

export default NavigationBar;