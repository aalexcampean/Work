import React, {createContext, Dispatch, ReactNode, useReducer} from "react";
import Reducer, {Action} from "./authReducer";
import {State} from "./authReducer";
import {Role} from "./Roles";


interface IAuthContext {
    username: string | null,
    token: string | null,
    role: Role | null,
    dispatch?: () => void;
}

const initialState = {
    username: localStorage.getItem('username'),
    token: localStorage.getItem('jwt'),
    role: localStorage.getItem('role') != null ? Role[localStorage.getItem('role') as keyof typeof Role] : null
};

type StoreProps = {
    children: JSX.Element
}

const AuthStore = ({children}: StoreProps) => {
    const [authState, authDispatch] = useReducer(Reducer, initialState);

    return (<Context.Provider value={{authState, authDispatch}}>
        {children}
    </Context.Provider>)
}

export const Context = createContext<{ authState: State, authDispatch: Dispatch<Action>; }>({
    authState: initialState,
    authDispatch: () => null
});

export default AuthStore;