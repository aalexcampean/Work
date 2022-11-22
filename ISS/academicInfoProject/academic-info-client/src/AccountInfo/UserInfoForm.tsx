import {
    TextField,
    Button,
    Paper,
    ButtonGroup
} from "@material-ui/core";
import React, {useContext, useEffect, useState} from "react";
import NavigationBar from "../ReusableComponents/NavigationBar";
import UserInfoService from "./UserInfo.service";
import UserInfo from './UserInfo'
import {Context} from "../Authentication/authStore";
// Styling
import './UserInfoForm.css';

const UserInfoForm = () => {
    const {authState, authDispatch} = useContext(Context);

    const [initialState, setinitialState] = useState(1);

    const [inputFirstName, setInputFirstName] = useState("");
    const [inputLastName, setInputLastName] = useState("");
    const [inputEmail, setInputEmail] = useState("");
    const [inputPhone, setInputPhone] = useState("");

    const userInfoService = new UserInfoService();

    useEffect(() => {
        const fun = async () => {
            return await userInfoService.getUserInfo(authState.token!);
        };
        fun().then(item => {
            console.log(item)
            setInputFirstName(item.FirstName || "");
            setInputLastName(item.LastName || "");
            setInputEmail(item.EmailAddress || "");
            setInputPhone(item.PhoneNumber || "");
        });
        setinitialState(0);
    }, [initialState]);

    const onInputFirstNameChange = (e: any) => {
        setInputFirstName(e.currentTarget.value);
    }

    const onInputLastNameChange = (e: any) => {
        setInputLastName(e.currentTarget.value);
    }

    const onInputEmailChange = (e: any) => {
        setInputEmail(e.currentTarget.value);
    }

    const onInputPhoneChange = (e: any) => {
        setInputPhone(e.currentTarget.value);
    }

    const handleSubmit = (e: any) => {
        e.preventDefault();
        userInfoService.setUserInfo(authState.token!, inputFirstName, inputLastName, inputEmail, inputPhone)
    }

    const handleReset = () => {
        setinitialState(1)
        setInputFirstName("");
        setInputLastName("");
        setInputEmail("");
        setInputPhone("");
    }

    return (
        <>
            <NavigationBar></NavigationBar>
            <div className="main-page">
                <Paper className="information-form">
                    <div className="information-form-content">
                        <h2>Edit Personal Information</h2>

                        <TextField
                            required
                            id="first-name-input"
                            className="form-item"
                            label="First Name"
                            value={inputFirstName}
                            variant="outlined"
                            onChange={onInputFirstNameChange}
                        />

                        <TextField
                            required
                            id="last-name-input"
                            className="form-item"
                            label="Last Name"
                            value={inputLastName}
                            variant="outlined"
                            onChange={onInputLastNameChange}
                        />

                        <TextField
                            required
                            id="email-input"
                            className="form-item"
                            label="Email Address"
                            value={inputEmail}
                            variant="outlined"
                            onChange={onInputEmailChange}
                        />

                        <TextField
                            required
                            id="phone-number-input"
                            className="form-item"
                            label="Phone Number"
                            value={inputPhone}
                            variant="outlined"
                            onChange={onInputPhoneChange}
                        />

                        <div
                            id="form-button-group"
                            className="form-item">
                            <Button
                                className="form-button"
                                variant="contained"
                                color="secondary"
                                onClick={handleSubmit}>
                                Submit
                            </Button>
                            <Button
                                className="form-button"
                                variant="contained"
                                color="secondary"
                                onClick={handleReset}>
                                Reset
                            </Button>
                        </div>
                    </div>
                </Paper>
            </div>
        </>
    );
}

export default UserInfoForm;