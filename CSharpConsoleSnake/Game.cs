using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//stopwatch
using System.Diagnostics;

namespace CSharpConsoleSnake
{
    class Game
    {
        public Game(int l_sizeX, int l_sizeY)
        {
            m_map = new char[l_sizeY, l_sizeX];

            for (int y = 0; y < m_map.GetLength(0); y++)
            {
                for (int x = 0; x < m_map.GetLength(1); x++)
                {
                    m_map[y, x] = '.';
                }
            }

            m_mapSize.x = l_sizeX;
            m_mapSize.y = l_sizeY;

            m_world = new World(m_mapSize, ref m_map);
            m_snake = new Snake(m_mapSize, ref m_map);

            m_bRunning = true;
        }

        public void Start()
        {
            while (m_bRunning)
            {
                sw.Restart();

                sw.Start();

                handleInput();
                update();
                render();

                sw.Stop();

                getDeltaTime();
            }
        }

        private void handleInput()
        {
            m_snake.handleInput();
        }

        private void update()
        {
            float frameTime = 1f / 5f;

            if (m_fElapsedTime / 1000f >= frameTime)
            {
                m_snake.update();

                m_fElapsedTime -= m_fElapsedTime;
            }

            m_world.update(ref m_snake);
        }

        private void render()
        {
            m_world.draw();
        }

        private void getDeltaTime()
        {
            m_fElapsedTime += sw.ElapsedMilliseconds;
        }

        private char[,] m_map;
        private bool m_bRunning;

        private Vector2 m_mapSize = new Vector2();

        private Snake m_snake;
        private World m_world;

        private float m_fElapsedTime;
        private Stopwatch sw = new Stopwatch();
    }
}
