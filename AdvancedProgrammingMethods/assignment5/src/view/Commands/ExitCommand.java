package view.Commands;

public class ExitCommand extends Command{
    public ExitCommand(String k, String d) {
        super(k, d);
    }

    @Override
    public void execute() throws Exception {
        System.exit(0);
    }
}
