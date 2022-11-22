import { Role } from "./Roles";

export type State={
    username: string | null,
    token: string | null, 
    role: Role | null
};

export type Action = { type: 'LOGIN', payload: State }
  | { type: 'LOGOUT', payload: null } | {type:'loginFailed', payload: string};

  const Reducer = (state: State, action: Action) => {
    switch(action.type){
        case 'LOGIN':
            return {
                ...state,
                username: action.payload.username,
                token: action.payload.token,
                role: action.payload.role
            }
       
        case 'LOGOUT':
            return {
                ...state,
                username: null,
                token: null,
                role: null
            }
        default: return state;
    };
};
export default Reducer;
