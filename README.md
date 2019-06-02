# ep1_dsid
EP1 de DSID

Para compilar, é necessário ter instalado um compilador C (por exemplo o mingw-w64) e estar utilizando o WINDOWS. 
Na pasta do arquivo, digite: gcc servidor.c -o servidor -lws2_32 -pthread 
Após o comando acima, digite:  servidor
Com isso, o servidor estará de pé. Agora, temos que compilar o cliente:
gcc cliente.c -o cliente -lpthread -lws2_32
Após o comando acima, digite: cliente
