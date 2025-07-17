using System;
using System.Collections.Generic;
using System.Threading;

class SnakeGame
{
    private static int width = 30;
    private static int height = 20;
    static List<(int x, int y)> snake = new(); //define o corpo da cobra como uma lista de tuplas (x, y)
    static (int x, int y) food; //define a comida como uma tupla (x, y)
    static string direction = "right";
    static bool gameOver = false;
    static int score = 0;

    static Thread? inputThread; // thread para capturar a tecla do usuário
    static readonly object lockObj = new(); // objeto de bloqueio para sincronização(impede que duas threads acessem a mesma variável ao mesmo tempo)


    static void Main()
    {
        Console.CursorVisible = false;
        Console.SetWindowSize(width + 2, height + 3);
        Console.SetBufferSize(width + 2, height + 3);

        snake.Add((width / 2, height / 2));
        SpawnFood();
        inputThread = new Thread(InputLoop);
        inputThread.Start();

        while (!gameOver)
        {
            Draw();
            Logic();
            Thread.Sleep(Math.Max(40, 120 - score * 5));
        }

        Console.Clear();
        Console.SetCursorPosition(width / 2 - 5, height / 2);
        Console.WriteLine("💀 GAME OVER 💀");
        Console.SetCursorPosition(width / 2 - 5, height / 2 + 1);
        Console.WriteLine($"🎯 Pontuação: {score}");
        Console.SetCursorPosition(0, height + 2);
        inputThread.Join();
        Console.WriteLine("Pressione qualquer tecla para sair...");
        Console.ReadKey();

    }

    static void Draw()
    {
        Console.Clear();
        Console.WriteLine(new string('■', width + 2));
        for (int y = 0; y < height; y++)
        {
            Console.Write("■");
            for (int x = 0; x < width; x++)
            {
                if ((x, y) == food)
                    Console.Write("■");
                else if (snake.Contains((x, y)))
                    Console.Write("●");
                else
                    Console.Write(" ");
            }
            Console.WriteLine("■");
        }
        Console.WriteLine(new string('■', width + 2));
        Console.WriteLine($"🎯 Pontuação: {score}");
    }
    static void InputLoop()
    {
        while (!gameOver)
        {
            if (Console.KeyAvailable)
            {
                var key = Console.ReadKey(true).Key;
                lock (lockObj)
                {
                    if (key == ConsoleKey.UpArrow && direction != "down") direction = "up";
                    if (key == ConsoleKey.DownArrow && direction != "up") direction = "down";
                    if (key == ConsoleKey.LeftArrow && direction != "right") direction = "left";
                    if (key == ConsoleKey.RightArrow && direction != "left") direction = "right";
                }
            }
            Thread.Sleep(10);
        }
    }

    static void Logic()
    {
        string dir;
        lock (lockObj)
        {
            dir = direction;
        }
        var head = snake[0];
        (int x, int y) next = dir switch
        {
            "up" => (head.x, head.y - 1),
            "down" => (head.x, head.y + 1),
            "left" => (head.x - 1, head.y),
            "right" => (head.x + 1, head.y),
            _ => head
        };

        if (next.x < 0 || next.y < 0 || next.x >= width || next.y >= height || snake.Contains(next))
        {
            gameOver = true;
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

    static void SpawnFood()
    {
        Random rand = new();
        do
        {
            food = (rand.Next(0, width), rand.Next(0, height));
        } while (snake.Contains(food));
    }
}
