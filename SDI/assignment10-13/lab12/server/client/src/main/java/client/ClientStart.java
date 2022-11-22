package client;

import client.ui.UI;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;


public class ClientStart {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext("client.config");
        UI ui = context.getBean(UI.class);
        ui.run();
        System.out.println("bye");
    }
}
