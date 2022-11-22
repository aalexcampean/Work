package view;

import model.adtContainers.IDictionary;
import model.adtContainers.MyDictionary;
import view.Commands.Command;

import java.util.HashMap;
import java.util.Scanner;

public class TextMenu {
    private IDictionary<String, Command> commands;

    public TextMenu() {
        this.commands = new MyDictionary<>();
    }

    public void addCommand(Command c) {
        commands.add(c.getKey(), c);
    }

    private void printMenu() {
        for (Command c : this.commands.values()) {
            String line = String.format("%4s: %s", c.getKey(), c.getDescription());
            System.out.println(line);
        }
    }

    public void show() {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            printMenu();
            System.out.printf("Input the option: ");
            String key = scanner.nextLine();
            Command cmd = commands.get(key);
            if (cmd == null) {
                System.out.println("Invalid Option");
                continue;
            }
            cmd.execute();
        }
    }
}
