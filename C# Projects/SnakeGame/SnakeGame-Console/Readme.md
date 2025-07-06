
# 🐍 Snake Game (Console) - C#

Um jogo clássico da cobrinha (Snake), totalmente implementado em **C# puro**, utilizando apenas o `System.Console`. Ideal para aprender lógica, controle de fluxo, threads e manipulação de tela no console.

---

## 🎮 Controles

- Use as **setas do teclado**: `↑ ↓ ← →` para controlar a cobra.
- Coma os blocos `■` (comida) para crescer e ganhar pontos.
- Evite bater nas paredes ou em si mesmo.

---

## 🧠 Funcionalidades

- Responsivo: input em **thread separada**
- Velocidade aumenta conforme a pontuação
- Interface com bordas e pontuação ao final
- Estrutura enxuta usando `List<(x, y)>` e `switch`

---

## ⚙️ Requisitos

- [.NET SDK 6+](https://dotnet.microsoft.com/download)
- Console compatível com `SetCursorPosition()` (recomendado: Windows)

---

## 🚀 Como executar

### 1. Crie o projeto:
```bash
dotnet new console -n SnakeGame
cd SnakeGame

3. Substitua o conteúdo de Program.cs com o código do jogo.
4. Execute:
dotnet run

Feito por Carlos Alexandre com C# e 🧠.