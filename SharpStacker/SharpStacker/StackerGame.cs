using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace SharpStacker
{
    class Block
    {
        public Block(Texture2D texture, int platformSize)
        {
            size = new Vector2(texture.Width, texture.Height);

            this.platformSize = platformSize;
        }

        public bool Collide(Rectangle rect)
        {
            if (this.rect.Intersects(rect))
            {
                return true;
            }
            else return false;
        }

        public Rectangle rect
        {
            get
            {
                return new Rectangle((int)pos.X, (int)pos.Y, (int)size.X, (int)size.Y);
            }
        }
        public int platformSize { get; private set; }

        public Vector2 pos { get; set; }
        public Vector2 size { get; private set; }
    }

    public class StackerGame
    {
        public StackerGame(ContentManager Content)
        {
            m_font = Content.Load<SpriteFont>("font");
            m_rectangle = Content.Load<Texture2D>("block");

            // Initialize list / vector
            m_platforms = new List<Block>();

            // Run setup
            Setup();

            //Debug.WriteLine("Platform " + i + ": " + m_platforms.ElementAt(i).pos.Y);
        }

        public void DisposeAll()
        {
            m_rectangle.Dispose();
        }

        private Texture2D m_rectangle;
        private SpriteFont m_font;

        private List<Block> m_platforms;

        private int m_currentPlatform;
        private int m_platformNum;
        private int m_platformSpeed;

        private bool isRunning;
        private bool hasWon;
        private bool hasLost;

        public void update(GameTime deltaTime)
        {
            //Debug.WriteLine();

            if (isRunning)
            {
                // Move platform
                var platform = m_platforms.ElementAt(m_currentPlatform);

                float newX = platform.pos.X + (m_platformSpeed * (float)deltaTime.ElapsedGameTime.TotalSeconds);

                platform.pos = new Vector2(newX, platform.pos.Y);

                // Bounce platform off wall
                if (platform.pos.X < 0 || platform.pos.X + (platform.size.X * platform.platformSize) > Game1.screenSize.X)
                {
                    m_platformSpeed *= -1;
                }
            }
        }

        public void draw(ref SpriteBatch spriteBatch)
        {
            for (int k = 0; k <= m_currentPlatform; k++)
            {
                var i = m_platforms.ElementAt(k);
                for (int j = 0; j < i.platformSize; j++)
                {
                    spriteBatch.Draw(m_rectangle, new Vector2(i.pos.X + (j * i.size.X), i.pos.Y), Color.White);
                }
            }

            if (hasWon)
            {
                spriteBatch.DrawString(m_font, "You have Won!\nPress space", new Vector2(Game1.screenSize.X / 2 - 128, Game1.screenSize.Y / 2), Color.Black);
            }
            else if (hasLost)
            {
                spriteBatch.DrawString(m_font, "You have Lost!\nPress space", new Vector2(Game1.screenSize.X / 2 - 128, Game1.screenSize.Y / 2), Color.Black);
            }
        }

        private KeyboardState oldState = Keyboard.GetState();

        public void handleInput()
        {
            if (isRunning)
            {
                KeyboardState newState = Keyboard.GetState();

                if (newState.IsKeyDown(Keys.Space) && oldState.IsKeyUp(Keys.Space))
                {
                    checkIntersect();

                    m_currentPlatform += 1;

                    m_platformSpeed = Math.Abs(m_platformSpeed) + 100;
                }

                if (m_currentPlatform == m_platformNum)
                {
                    m_currentPlatform = m_platformNum - 1;
                    isRunning = false;

                    if (!hasLost)
                        hasWon = true;
                }

                oldState = newState;
            }
            else if (!isRunning && (hasWon || hasLost))
            {
                KeyboardState newState = Keyboard.GetState();

                if (newState.IsKeyDown(Keys.Space) && oldState.IsKeyUp(Keys.Space))
                {
                    // Reset game
                    Setup();
                }

                oldState = newState;
            }
        }

        private void checkIntersect()
        {
            // Check if 2 platforms intersect
            if (m_currentPlatform != 0)
            {
                bool isIntersecting = false;

                for (int i = 0; i < m_platforms.ElementAt(m_currentPlatform).platformSize; i++)
                {
                    for (int j = 0; j < m_platforms.ElementAt(m_currentPlatform - 1).platformSize; j++)
                    {
                        Rectangle cur = new Rectangle((int)m_platforms.ElementAt(m_currentPlatform).pos.X + (i * m_rectangle.Width), (int)m_platforms.ElementAt(m_currentPlatform).pos.Y, m_rectangle.Width, m_rectangle.Height);
                        Rectangle last = new Rectangle((int)m_platforms.ElementAt(m_currentPlatform - 1).pos.X + (j * m_rectangle.Width), (int)m_platforms.ElementAt(m_currentPlatform - 1).pos.Y, m_rectangle.Width, m_rectangle.Height); ;

                        if (cur.Intersects(last))
                        {
                            isIntersecting = true;
                        }
                    }
                }

                if (!isIntersecting)
                {
                    isRunning = false;
                    hasLost = true;
                }
            }
        }

        private void Setup()
        {
            m_platforms.Clear();

            m_currentPlatform = 0;
            m_platformNum = 16;
            m_platformSpeed = 200;

            isRunning = true;

            hasWon = false;
            hasLost = false;

            // Setup platforms
            for (int i = m_platformNum; i > 0; i--)
            {
                m_platforms.Add(new Block(m_rectangle, i));
            }

            for (int i = 0; i < m_platformNum; i++)
            {

                if (i == 0)
                {
                    m_platforms.ElementAt(i).pos = new Vector2(0, Game1.screenSize.Y - ((i + 1) * m_rectangle.Width));
                }
                else
                {
                    m_platforms.ElementAt(i).pos = new Vector2(0, Game1.screenSize.Y - ((i + 1) * m_rectangle.Width) + i);
                }
            }
        }
    }
}
