using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpConsoleSnake
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            Game demo = new Game(40, 20);
            demo.Start();
        }
    }
}
