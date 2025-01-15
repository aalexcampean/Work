// See https://aka.ms/new-console-template for more information

using a4_futures_and_continuations.Implementation;

class Program
{
    static void Main()
    {
        var hosts = new List<string> {
            //"www.cs.ubbcluj.ro/~hfpop/teaching/pfl/requirements.html",
            "www.cs.ubbcluj.ro/~forest/newton/index.html",
            "www.cs.ubbcluj.ro/~rlupsa/edu/pdp/index.html",
            "www.columbia.edu/~fdc/sample.html"
        };

        //DirectCallback.Run(hosts);
        //TasksMechanism.Run(hosts);
        AsyncTaskMechanism.Run(hosts);
    }
}
