using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//keyboard input

/*  
        - Add PresentationCore.dll assembly as a reference.
        - Add WindowsBase.dll assembly as a reference.

        Ako greska STA Thread dodadati iznad Main   [STAThread]     
*/
using System.Windows.Input;

namespace CSharpConsoleSnake
{
    class Snake
    {
        public Snake(Vector2 l_mapSize, ref char[,] l_map)
        {
            m_mapSize = l_mapSize;
            m_map = l_map;

            m_snakeSize = 3;

            for (int i = 0; i < m_snakeSize; i++)
            {
                Vector2 temp = new Vector2();
                temp.x = (m_mapSize.x / 2) + i;
                temp.y = m_mapSize.y / 2;

                m_map[temp.y, temp.x] = 'o';

                m_snake.AddLast(temp);
            }
        }

        public void handleInput()
        {
            if (Keyboard.IsKeyDown(System.Windows.Input.Key.A) && m_dir != Direction.RIGHT)         m_dir = Direction.LEFT;
            else if (Keyboard.IsKeyDown(System.Windows.Input.Key.D) && m_dir != Direction.LEFT)     m_dir = Direction.RIGHT;
            else if (Keyboard.IsKeyDown(System.Windows.Input.Key.W) && m_dir != Direction.DOWN)     m_dir = Direction.UP;
            else if (Keyboard.IsKeyDown(System.Windows.Input.Key.S) && m_dir != Direction.UP)       m_dir = Direction.DOWN;
        }

        public void update()
        {
            MoveSnake();
        }

        public void GrowSnake()
        {
            m_snake.AddLast(m_snake.Last());
        }

        private void MoveSnake()
        {
            m_map[m_snake.First().y, m_snake.First().x] = 'o';

            Vector2 temp = new Vector2();
            temp.x = m_snake.First().x;
            temp.y = m_snake.First().y;

            if (m_dir == Direction.LEFT && m_dir != Direction.RIGHT)            temp.x--;
            else if (m_dir == Direction.RIGHT && m_dir != Direction.LEFT)       temp.x++;
            else if (m_dir == Direction.UP && m_dir != Direction.DOWN)          temp.y--;
            else if (m_dir == Direction.DOWN && m_dir != Direction.UP)          temp.y++;

            //Outside of map
            if (temp.x < 0)                         temp.x = m_mapSize.x - 1;
            else if (temp.x > m_mapSize.x - 1)      temp.x = 0;
            else if (temp.y < 0)                    temp.y = m_mapSize.y - 1;
            else if (temp.y > m_mapSize.y - 1)      temp.y = 0;

            m_snake.AddFirst(temp);

            m_map[m_snake.First().y, m_snake.First().x] = 'O';
            m_map[m_snake.Last().y, m_snake.Last().x] = '.';

            m_snake.RemoveLast();
        }

        enum Direction
        {
            LEFT, RIGHT, UP, DOWN
        }

        private LinkedList<Vector2> m_snake = new LinkedList<Vector2>();
        private int m_snakeSize;
        private Vector2 m_mapSize = new Vector2();
        private Direction m_dir = Direction.LEFT;

        private char[,] m_map;
    }
}
