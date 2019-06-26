# Socket Server and Client With Pthreads
Este repositório foi feito como EP1 da matéria de DSID

O cliente faz uma série de requisições ao servidor, que as responde criando um número limitado de pthreads. A medida que as requisições vão terminando, se houver uma nova requisição na fila, ela é alocado na pthread recém liberada.

Para compilar, é necessário ter instalado um compilador C (por exemplo o mingw-w64) e estar utilizando o WINDOWS. 
Na pasta do arquivo, digite: gcc servidor.c -o servidor -lws2_32 -pthread 
Após o comando acima, digite:  servidor
Com isso, o servidor estará de pé. Agora, temos que compilar o cliente:
gcc cliente.c -o cliente -lws2_32
Após o comando acima, digite: cliente
