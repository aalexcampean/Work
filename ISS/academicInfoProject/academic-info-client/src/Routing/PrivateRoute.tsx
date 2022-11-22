import { useContext } from 'react';
import { Navigate, Route, useLocation } from 'react-router-dom';
import { Context } from '../Authentication/authStore';
import { Role } from '../Authentication/Roles';
import AccessDenied from '../Fail/AccessDenied';

const PrivateRoute = ({ children, roles, }: { children: JSX.Element;  roles: Array<Role>;}) => {
  let location = useLocation();
  const {authState, authDispatch} = useContext(Context);
  const userHasRequiredRole = authState.username && authState.role != null && roles.includes(authState.role) ? true : false;

  if (!authState.username == null) {
    return <Navigate to="/login" state={{ from: location }} />;
  }
  if (!userHasRequiredRole) {
    return <AccessDenied />; // build your won access denied page (sth like 404)
  }
  
  return children;
};

export default PrivateRoute;