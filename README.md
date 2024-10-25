# Repositório dedicado aos meus códigos de projetos com Arduino

# 24/10/2024 - Contagem Regressiva

Criei um algoritmo para simular um cronômetro de contagem regressiva, onde posso selecionar através de um botão qual será o início da contagem, e um segundo botão que irá dar o início para a contagem, ela será exibida em um display de 7 segmentos com 4 caracteres.

## As ligações realizadas

- Display Baixo 1 `|` Arduino A0
- Display Baixo 2 `|` Arduino 5
- Display Baixo 3 `|` não está conectado com nada
- Display Baixo 4 `|` Arduino 4
- Display Baixo 5 `|` Arduino 8
- Display Baixo 6 `|` Arduino 11
- Display Cima 1 `|` Arduino 6
- Display Cima 2 `|` Arduino 2
- Display Cima 3 `|` Arduino 7
- Display Cima 4 `|` Arduino 9
- Display Cima 5 `|` Arduino 10
- Display Cima 6 `|` Arduino 3
- Botão 1 `|` Arduino 12
- Botão 2 `|` Arduino 13
- Led com resistor 1 `|` Arduino A1
- Led com resistor 2 `|` Arduino A2
- Led com resistor 3 `|` Arduino A3
- Led com resistor 4 `|` Arduino A4
- Led com resistor 5 `|` Arduino A5
- Todos os componentes foram ligados ao GND corretamente

## Conceitos relevantes

### Multiplexação

- A multiplexação é a técnica usada para controlar múltiplos dígitos de um display de 7 segmentos, acendendo um dígito de cada vez em rápida sucessão, de modo que pareça que todos estão acesos simultaneamente. Isso economiza pinos no Arduino, pois você compartilha os mesmos pinos de segmentos entre os dígitos, e alterna rapidamente qual dígito está ativo.
- A função `switchDigit` ativa o pino do dígito correto enquanto mantém os outros desligados, permitindo a exibição de um dígito por vez.
- A exibição dos números de forma contínua ocorre graças ao loop dentro da função `displayTime`, que varre os dígitos rapidamente o suficiente para que o olho humano perceba como se todos estivessem acesos ao mesmo tempo.

### Mapeamento de Segmentos

- O display de 7 segmentos é controlado pelo mapeamento dos segmentos individuais que precisam ser ativados para exibir um número específico. Cada número tem um conjunto de segmentos (a-g) que precisam ser acesos para formar a figura correta.
- A função `lightNumber` utiliza um array chamado segmentMap que armazena quais segmentos devem ser acesos para cada número (de 0 a 9) e também para o caractere `-` (usado para indicar uma pausa ou o modo de escolha do tempo).

### Controle de Botões e Estados

- O controle dos botões permite a seleção de tempos predefinidos e o início/pausa da contagem. O código utiliza flags booleanas para controlar o estado do sistema, como `counting` para saber se o cronômetro está em contagem ou não, e `timeReachedZero` para identificar se a contagem chegou a zero.
- Quando o `button1` é pressionado, ele alterna o estado entre iniciar e pausar a contagem.
- O `button2` permite alternar entre diferentes tempos predefinidos quando a contagem está pausada.

### Controle do Tempo

- O conceito de controle de tempo é gerido por duas variáveis: `currentMinutes` e `currentSeconds`. A função `countdown` decrementa os segundos a cada ciclo, e quando os segundos chegam a zero, ela ajusta os minutos e reinicia os segundos para 59. Esse controle cria o comportamento de contagem regressiva em um formato de relógio.
- O `delay(1000)` na função `countdown` garante que a contagem ocorra a cada segundo, dando tempo suficiente para que os dígitos sejam exibidos entre os decrementos.

### Array para Armazenar Tempos

- O array `times[][2]` armazena os tempos disponíveis em minutos e segundos, permitindo fácil acesso e troca de tempos ao pressionar o botão 2.

### Evitar "Delay Bloqueante" com Loop de Multiplexação

- Dentro da função `displayTime`, a multiplexação dos dígitos é feita com pequenos delays de 3 milisegundos, o que permite que a multiplexação aconteça sem bloquear completamente o loop principal. Isso evita que o Arduino fique inativo por longos períodos, permitindo que o programa continue a verificar os botões e controlar a contagem enquanto os dígitos são exibidos.
