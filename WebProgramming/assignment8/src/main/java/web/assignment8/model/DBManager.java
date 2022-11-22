package web.assignment8.model;

import web.assignment8.domain.User;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DBManager {
    private Statement stmt;
    private static Connection connection;

    public DBManager() {
        connect();
    }

    public static void connect() {
        if(connection == null) {
            String url = "jdbc:mysql://localhost:3306/forum";
            try{
                Class.forName( "com.mysql.jdbc.Driver" );
                connection = DriverManager.getConnection( url, "root", "" );
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public static Connection getConnection() {
        if(connection == null)
            connect();
        return connection;
    }

    public User authenticate(String username, String password) {
        User u = null;
        try {
            String sql = "SELECT * FROM users WHERE username = '" + username + "' AND password = '" + password + "'";

            PreparedStatement stmt = getConnection().prepareStatement(sql);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                u = new User(rs.getInt("id"), rs.getString("username"), rs.getString("password"));
            }
            rs.close();
            connection = null;

        } catch(SQLException e) {
            e.printStackTrace();
        }
        return u;
    }

    public void deleteUserFromSession(int userId) {
        try {
            String sql = "DELETE FROM session WHERE user_id=" + userId;

            PreparedStatement stmt = getConnection().prepareStatement(sql);
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
    public void addUserToSession(int id, int userId) {
        try {
            String sql = "INSERT INTO session VALUES (" + id + ", " + userId + ")";

            PreparedStatement stmt = getConnection().prepareStatement(sql);
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public int getSessionCount() {
        try {
            String sql = "SELECT COUNT(*) FROM session";

            PreparedStatement stmt = getConnection().prepareStatement(sql);
            ResultSet rs = stmt.executeQuery();
            int value = 0;
            if (rs.next())
                value = rs.getInt(1);
            rs.close();
            connection = null;

            return value;
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return 0;
    }

    public int getNextTopicId(){
        try {
            String sql = "SELECT id FROM topics ORDER BY id DESC LIMIT 1;";

            PreparedStatement stmt = getConnection().prepareStatement(sql);
            ResultSet rs = stmt.executeQuery();
            int value = 0;
            if (rs.next())
                value = rs.getInt(1);
            rs.close();


            value+=1;
            return value;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return 0;
    }
    public String getTopics(){
        try{
            String s = "Already existing topics: \n";
            String sql = "SELECT name FROM topics;";

            PreparedStatement stmt = getConnection().prepareStatement(sql);
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                s += " "+rs.getString(1)+" | ";
            }
            rs.close();
            return s;
        }
        catch (SQLException e) {
            e.printStackTrace();
            return "Not already existing topics!";
        }
    }

    public boolean checkIfExistentTopic(String givenTopic){
        try{
            String sql = "SELECT * FROM topics WHERE name = '" + givenTopic + "'";

            PreparedStatement stmt = getConnection().prepareStatement(sql);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return true;
            }
            rs.close();
            return false;
        }
        catch (SQLException e) {
            e.printStackTrace();
            return false;
        }

    }

    public int getTopicId(String givenTopic){
        if(checkIfExistentTopic(givenTopic)){
            try{
                String sql = "SELECT id FROM topics WHERE name = '" + givenTopic + "'";

                PreparedStatement stmt = getConnection().prepareStatement(sql);
                ResultSet rs = stmt.executeQuery();
                int value = 0;
                if (rs.next())
                    value = rs.getInt(1);
                rs.close();
                return value;
            }
            catch (SQLException e) {
                e.printStackTrace();

            }
        }
        return 0;
    }

    public void addTopic(String givenTopic){
            if (!checkIfExistentTopic(givenTopic)) {
            try {
                int val = this.getNextTopicId();
                String sql2 = "INSERT INTO topics(id,name) VALUES (" + val+ ",'" + givenTopic + "')";
                PreparedStatement stmt2 = getConnection().prepareStatement(sql2);
                stmt2.executeUpdate();
            } catch (SQLException e) {
                e.printStackTrace();
            }            }
    }
    public int getNextPostId(){
        try {
            String sql = "SELECT id FROM posts ORDER BY id DESC LIMIT 1;";

            PreparedStatement stmt = getConnection().prepareStatement(sql);
            ResultSet rs = stmt.executeQuery();
            int value = 0;
            if (rs.next())
                value = rs.getInt(1);
            rs.close();


            value+=1;
            return value;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return 0;
    }

    public void addPost(int topic, int author, String title, String content){
        try {
            int val = this.getNextPostId();
            String sql2 = "INSERT INTO posts VALUES (" + val+ "," + topic + ","+author+",'"+title+"','"+content+"')";
            PreparedStatement stmt2 = getConnection().prepareStatement(sql2);
            stmt2.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void deletePost(int id){
        try {
            String sql = "DELETE FROM posts WHERE id=" + id;

            PreparedStatement stmt = getConnection().prepareStatement(sql);
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
