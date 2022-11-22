<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
    <style>
        html, body {
            height: 100%;
        }
        html {
            display: table;
            margin: auto;
        }
        body {
            display: table-cell;
            vertical-align: middle;
            horiz-align: center;
            background-color: white;
            font-family: "Arial", sans-serif;
        }
        .button {
            width: 100px;
            height: 40px;
            border-radius: 15px;
            color: white;
            background-color: teal;
        }
        body{
            background-color: rgba(0, 255, 129, 0.44);
        }
    </style>
</head>
<body>
<h3>Login</h3>
<%
    if(session.getAttribute("fail") != null && session.getAttribute("fail").equals("login_issue")) {
%>
<p>Login failed, please try again.</p>
<%
    }
%>

<form action="LoginController" method="post">
    <p>Username:
    <input type="text" name="username"> <br>
    </p>
    <p>Password:
    <input type="password" name="password"> <br>
    <br></p>
    <input class="button" type="submit" value="Login"/>
</form>
</body>
</html>