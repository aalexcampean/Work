package Common.Request;

import java.io.*;

public class Request {
    private String header;
    private String body;

    // Constants
    private static final String LINE_SEPARATOR = System.getProperty("line.separator");
    public static final String OK = "ok";
    public static final String ERROR = "error";

    public Request(){}

    public Request(String header, String body) {
        this.header = header;
        this.body = body;
    }

    public String getHeader() {return header;}
    public void setHeader(String header) {this.header = header;}

    public String getBody() {return body;}
    public void setBody(String body) {this.body = body;}

    public void read(InputStream inputStream) throws IOException {
        var buffer = new BufferedReader(new InputStreamReader(inputStream));
        header = buffer.readLine();
        body = buffer.readLine();
    }

    public void write(OutputStream outputStream) throws IOException {
        outputStream.write((header + LINE_SEPARATOR + body + LINE_SEPARATOR).getBytes());
    }

    @Override
    public String toString() {
        return "Request{" +
                "header='" + header + '\'' +
                ", body='" + body + '\'' +
                '}';
    }
}
