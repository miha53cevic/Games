using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpConsoleSnake
{
    class World
    {
        public World(Vector2 l_mapSize, ref char[,] l_map)
        {
            m_mapSize = l_mapSize;
            m_map = l_map;

            rand = new Random();

            RespawnApple();
        }

        private Random rand;

        public void update(ref Snake l_snake)
        {
            if (m_map[m_apple.y, m_apple.x] != 'x')
            {
                l_snake.GrowSnake();
                RespawnApple();
            }
        }

        public void draw()
        {
            Console.CursorVisible = false;
            Console.SetCursorPosition(0, 0);

            for (int y = 0; y < m_map.GetLength(0); y++)
            {
                for (int x = 0; x < m_map.GetLength(1); x++)
                {
                    switch(m_map[y, x])
                    {
                        case '.':
                            {
                                Console.Write(".");
                                break;
                            }
                        case 'x':
                            {
                                Console.Write("x");
                                break;
                            }
                        case 'O':
                            {
                                Console.Write("O");
                                break;
                            }
                        case 'o':
                            {
                                Console.Write("o");
                                break;
                            }
                    }
                }
                Console.WriteLine();
            }
        }

        private void RespawnApple()
        {
            m_apple.x = rand.Next(0, m_mapSize.x);
            m_apple.y = rand.Next(0, m_mapSize.y);

            m_map[m_apple.y, m_apple.x] = 'x';
        }

        private Vector2 m_apple = new Vector2();
        private Vector2 m_mapSize = new Vector2();
        private char[,] m_map;
    }
}
