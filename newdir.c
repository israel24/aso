#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void separar(char *cadena, char *linea, char separador) {
	int x, y;
	x = 0; y = 0;
	while ((linea[x]) && (linea[x] != separador)) {
		cadena[x] = linea[x];
		x = x + 1;
	}
	cadena[x] = '\0';
	if (linea[x])
		++x;
	y = 0;
	while (linea[y] = linea[x]) {
		linea[y] = linea[x];
		y++;
		x++;
	}
}

void remplazar(char *cadena, char *resultado) {
	char *separador = "%2F";
	char *remplazo = "/";
	int i =0;
	int j =0;
	for(i=0;i<(strlen(cadena));i++) {
		if( (cadena[i] == separador[0]) && (cadena[i+1] == separador[1]) && (cadena[i+2] == separador[2]) ) {
			resultado[j] = '/';
			i = i+2;
		}
		else {
			resultado[j] = cadena[i];
		}
		j = j+1;
	}
	resultado[j] = '\0';
}

void err_quit(char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

void imprimir() {
	printf("Content-type: text/html\n\n");
	printf("<!DOCTYPE html>");
	printf("<html>");
	printf("<head> <title>Crear Nuevo Directorio</title> </head>");
	printf("<body>");
	printf("<div style=\"background:#2a2a2a; color:#fff; height:50px; padding:20px;\"> <h1>Administrador de Archivos</h1> </div>");
	printf("<div>");
		printf("<div style=\"height:300px; padding:30px;\">");
			printf("<p><a href=\"index.cgi\">Volver</a></p><br>");
			printf("<p>Crear <strong>Nuevo Directorio:</strong></p><br>");
			printf("<div>");
				printf("<form action=\"/cgi-bin/procgi/newdir.cgi\" method=\"post\">");
					printf("<p><label>Nombre:</label><input type=\"text\"  /></p><br>");
					printf("<input type=\"submit\" value=\"Crear\" />");
				printf("</form>");
			printf("</div>");
		printf("</div>");
		printf("<div style=\"padding:20px; background:#2a2a2a; color:#fff;\"> <p>&copy; ASO 2-2014</p> </div>");
	printf("</div>");
	printf("</body>");
	printf("</html>");
}

int main(void) {
	char *lenstr;
	char inputBuffer[1024];
	int contentLength;
	int i;
	char x;
	char sms[80];
	lenstr = getenv("CONTENT_LENGTH");
	if (lenstr!= NULL)
		contentLength = atoi(lenstr);
	else
		contentLength = 0;
	if (contentLength > sizeof(inputBuffer)-1)
		contentLength = sizeof(inputBuffer)-1;
	i = 0;
	while (i < contentLength) {
		x = fgetc(stdin);
		if (x==EOF)
			break;
		inputBuffer[i] = x;
		i++;
	}
	inputBuffer[i] = '\0';
	contentLength = i;
	//printf("%s\n", inputBuffer);
	separar(sms, inputBuffer, '=');
	separar(sms, inputBuffer, '&');
	//printf("%s\n", sms);
	char nuevo[80];
	remplazar(sms,nuevo);
	//imprimir(nuevo);
	imprimir();
	return 0;
} 
