using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace SnakeGUI
{
    public partial class Form1 : Form
    {
        System.Windows.Forms.Timer gameTimer = new();
        List<Point> snake = new();
        Point food;
        string direction = "right";
        int score = 0;
        int cellSize = 20;
        int columns = 30;
        int rows = 20;

        public Form1()
        {
            InitializeComponent();
            this.DoubleBuffered = true;
            this.ClientSize = new Size(columns * cellSize, rows * cellSize + 30);
            this.KeyPreview = true;
            this.KeyDown += HandleKey;
            this.Text = "🐍 Snake GUI - C# WinForms";

            StartGame();

            gameTimer.Interval = 120;
            gameTimer.Tick += GameLoop;
            gameTimer.Start();
        }

        void StartGame()
        {
            snake.Clear();
            snake.Add(new Point(columns / 2, rows / 2));
            SpawnFood();
            direction = "right";
            score = 0;
        }

        void HandleKey(object? sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Up && direction != "down") direction = "up";
            if (e.KeyCode == Keys.Down && direction != "up") direction = "down";
            if (e.KeyCode == Keys.Left && direction != "right") direction = "left";
            if (e.KeyCode == Keys.Right && direction != "left") direction = "right";
        }

        void GameLoop(object? sender, EventArgs e)
        {
            MoveSnake();
            Invalidate(); // força redesenho
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            Graphics g = e.Graphics;

            // desenha a cobra
            foreach (var p in snake)
                g.FillRectangle(Brushes.Green, p.X * cellSize, p.Y * cellSize, cellSize, cellSize);

            // desenha a comida
            g.FillRectangle(Brushes.Red, food.X * cellSize, food.Y * cellSize, cellSize, cellSize);

            // pontuação
            g.DrawString($"Score: {score}", this.Font, Brushes.Black, new PointF(5, rows * cellSize));
        }

        void MoveSnake()
        {
            Point head = snake[0];
            Point next = direction switch
            {
                "up" => new Point(head.X, head.Y - 1),
                "down" => new Point(head.X, head.Y + 1),
                "left" => new Point(head.X - 1, head.Y),
                "right" => new Point(head.X + 1, head.Y),
                _ => head
            };

            if (next.X < 0 || next.Y < 0 || next.X >= columns || next.Y >= rows || snake.Contains(next))
            {
                gameTimer.Stop();
                MessageBox.Show($"💀 Game Over!\nScore: {score}", "Fim de jogo");
                StartGame();
                return;
            }

            snake.Insert(0, next);

            if (next == food)
            {
                score++;
                SpawnFood();
            }
            else
            {
                snake.RemoveAt(snake.Count - 1);
            }
        }

        void SpawnFood()
        {
            Random rand = new();
            do
            {
                food = new Point(rand.Next(columns), rand.Next(rows));
            } while (snake.Contains(food));
        }
    }
}
