# Projeto C++: Scroll Numbers

Este projeto é um programa simples em C++ que exibe uma sequência de números com diferentes velocidades de rolagem.

## Função `scroll_numbers`

A função `scroll_numbers` recebe um valor inteiro como parâmetro e exibe uma sequência de números até esse valor. A sequência é exibida cinco vezes, cada uma com uma velocidade de rolagem diferente.

```cpp
void scroll_numbers(int value)
{  
  for (int i = INITIAL_VALUE; i <= LIMITS_MAX; i++)
  {
    show_number(i);
    delay(DELAY_SCROLL_5);
  }

  for (int i = INITIAL_VALUE; i <= LIMITS_MAX; i++)
  {
    show_number(i);
    delay(DELAY_SCROLL_25);
  }

  for (int i = INITIAL_VALUE; i <= LIMITS_MAX; i++)
  {
    show_number(i);
    delay(DELAY_SCROLL_50);
  }

  for (int i = INITIAL_VALUE; i <= LIMITS_MAX; i++)
  {
    show_number(i);
    delay(DELAY_SCROLL_250);
  }
  
  for (int i = INITIAL_VALUE; i <= value; i++)
  {
    show_number(i);
    delay(DELAY_SCROLL_500);
  }
}
```

## Como usar

Para usar este programa, você precisa chamar a função `scroll_numbers` com o valor máximo que deseja exibir.

## Dependências

Este projeto depende da função `show_number` para exibir os números e da função `delay` para controlar a velocidade de rolagem. Ambas as funções não estão incluídas neste arquivo e devem ser fornecidas pelo usuário.
