package view.Commands;

import controller.Controller;
import exception.CustomException;

public class RunExample extends Command{
    private Controller ctrl;

    public RunExample(String k, String d, Controller c) {
        super(k, d);
        this.ctrl = c;
    }

    @Override
    public void execute() {
        try {
            this.ctrl.allSteps();
        }
        catch (CustomException e){
            System.out.println(e.getMessage());
        }
    }
}
