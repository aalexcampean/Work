import React, {useContext, useEffect} from 'react';
import logo from './logo.svg';
import './App.css';
import {Router, Route, Link, Routes, Navigate} from 'react-router-dom';
import Login from './Authentication/Login';
import AuthStore, {Context} from './Authentication/authStore';
import PrivateRoute from './Routing/PrivateRoute';
import StudentCourses from './Course/StudentCourses';
import TeacherCourses from './Course/TeacherCourses';
import UserInfoForm from './AccountInfo/UserInfoForm'
import {Role} from './Authentication/Roles';
import NotFound from './Fail/NotFound';
import checkExpiredJWT from './utils/checkExpiredJWT';
import ProposeOptionalCourses from './ProposeOptionalCourses/ProposeOptionalCourses';
import ViewGradesStudent from './ViewGradesStudent/ViewGradesStudent';
import EnroltoYear from './EnroltoYear/EnroltoYear';
import SignContract from './SignContract/SignContract';
import StaffPage from './Course/StaffPage';
import AddGrades from './AddGrades/AddGrades';
import StudentsByYear from './StudentsByYear/StudentsByYear';
import StudentsByGroup from './StudentsByGroup/StudentsByGroup';


function App() { 
  const {authState, authDispatch} = useContext(Context);
 
  return (
    <AuthStore>
      <Routes>
      <Route path="/"  element={ authState.token && !checkExpiredJWT(authState.token) ? ( authState.role == Role.teacher ? <Navigate to="/teacher-courses" /> :(authState.role==Role.student ? <Navigate to="/user-courses" />:<Navigate to="/staff-page" />)) : <Login></Login>}>
        
      </Route>
      <Route path="login" element={(authState.token && !checkExpiredJWT(authState.token)) ?  <Navigate to="/"/> : <Login />} />
      <Route
        path="teacher-courses"
        element={
          <PrivateRoute roles={[Role.teacher]}>
            <TeacherCourses />
          </PrivateRoute>
        }
      />
      <Route
        path="user-courses"
        element={
          <PrivateRoute roles={[Role.student]}>
            <StudentCourses />
          </PrivateRoute>
        }
      />

      <Route
        path="staff-page"
        element={
          <PrivateRoute roles={[Role.admin]}>
            <StaffPage />
          </PrivateRoute>
        }
      />

      <Route
        path="propose-optional-courses"
        element={
          <PrivateRoute roles={[Role.teacher]}>
            <ProposeOptionalCourses />
          </PrivateRoute>
        }
      />
      <Route
        path="grades"
        element={
          <PrivateRoute roles={[Role.student]}>
            <ViewGradesStudent />
          </PrivateRoute>
        }
      />

      <Route
        path="enrol"
        element={
          <PrivateRoute roles={[Role.student]}>
            <EnroltoYear />
          </PrivateRoute>
        }
      />

      <Route
          path="account-info"
          element={
              <PrivateRoute roles={[Role.teacher, Role.student, Role.admin]}>
                  <UserInfoForm/>
              </PrivateRoute>
          }
        />

      <Route
          path="sign"
          element={
              <PrivateRoute roles={[ Role.student]}>
                  <SignContract/>
              </PrivateRoute>
          }
        />

      <Route
          path="add-grades"
          element={
              <PrivateRoute roles={[ Role.teacher]}>
                  <AddGrades/>
              </PrivateRoute>
          }
        />

      <Route
          path="studentsGroup"
          element={
              <PrivateRoute roles={[ Role.admin]}>
                  <StudentsByGroup/>
              </PrivateRoute>
          }
        />

      <Route
          path="studentsYear"
          element={
              <PrivateRoute roles={[ Role.admin]}>
                  <StudentsByYear/>
              </PrivateRoute>
          }
        />
      <Route path="*" element={<NotFound />} />
    </Routes>
    </AuthStore>
  );

}

export default App;