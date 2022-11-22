package Client;

import Client.View.UI;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

import java.util.concurrent.ExecutorService;

public class ClientStart {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext context=
                new AnnotationConfigApplicationContext("client.config");
        ExecutorService executorService = context.getBean(ExecutorService.class);
        UI ui = context.getBean(UI.class);
        ui.run();

        executorService.shutdownNow();
    }
}
