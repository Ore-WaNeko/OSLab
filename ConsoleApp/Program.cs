using System;
using System.Diagnostics;

class Program
{
    static void Main()
    {
        // Start child process and wait
        var child = Process.Start("whoami");
        child?.WaitForExit();

        // Print parent (current) process id
        Console.WriteLine($"Process ID is: {Process.GetCurrentProcess().Id}");
    }
}
