#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAXLEN 1024

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

void limpiar(char *cadena, char *resultado) {
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

void cambiar(char *cadena) {
	int x = sizeof(cadena)-1;
	if (cadena[x] == '/') {
		cadena[x] = '\0';
		x =x-1;
	}
	while (cadena[x] != '/') {
		cadena[x] = '\0';
		x = x-1;
	}
}

void err_quit(char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

void mostrar(char *dato, char *ruta) {
	printf("<thead> <tr> <th><input type=\"checkbox\" name=\"nombre\" /></th> <th style=\"float:left;\"> \n");
	printf("/%s",dato);
	printf("</th> <th><!--<input type=\"button\" value=\"Abrir\" />--></th> </tr> </thead>\n");
	//printf("<input type=\"hidden\" value=\"%s/%s\" name=\"path\">\n",ruta,dato);
	//printf("<input type=\"hidden\" value=\"%s\" name=\"namefd\">\n",dato);
}

void listar(char *ruta) {
	DIR *dir;
	struct dirent *mydirent;
	int i = 1;
	if((dir = opendir(ruta)) == NULL) {
		err_quit("opendir");
	}
	while((mydirent = readdir(dir)) != NULL) {
		char *name = mydirent->d_name;
		mostrar(name, ruta);
	}
	closedir(dir);
	//exit(EXIT_SUCCESS);
}

void imprimir(char *dato) {
	printf("Content-type: text/html\n\n");
	printf("<!DOCTYPE html>\n");
	printf("<html>\n");
	printf("<head><title>Administrador de Archivos</title></head>\n");
	printf("<body>\n");
		printf("<div style=\"background:#2a2a2a; color:#fff; height:50px; padding:20px;\"> <h1>Administrador de Archivos</h1> </div>\n");
		printf("<form action=\"index.cgi\" method=\"post\" enctype=\"text/plain\" >\n");
			printf("<div style=\"padding-top:20px; padding-left:40px;\">\n");
				printf("<input type=\"text\" value=\"");
				printf("%s", dato);
				printf("\" name=\"ruta\" size=\"50\" maxlength=\"80\">\n");
				printf("<input type=\"submit\" value=\"ir\" />\n");
				printf("<p><b>Directorio Actual: <code>");
				printf("%s", dato);
				printf("</code></b> </p>\n");
				//printf("<input type=\"submit\" value=\"Atras\" />");
			printf("</div>\n");
		printf("</form>\n");
		printf("<form action=\"index.cgi\" method=\"post\" enctype=\"text/plain\" >\n");
			printf("<div style=\"padding-left:40px;\">\n");
				char newdato[80];
				limpiar(dato,newdato);
				cambiar(newdato);
				printf("<input type=\"hidden\" name=\"irAtras\" value=\"");
					printf("%s", newdato);printf("\">");
				printf("<input type=\"submit\" value=\"Atras\" />");
			printf("</div>\n");
		printf("</form>\n");
		printf("<form action=\"index.cgi\" method=\"post\" enctype=\"text/plain\" >\n");
			printf("<div style=\"background:#f2f2f2; padding:10px;\">\n");
				printf("<input type=\"button\" value=\"Nuevo directorio\" onclick=\"window.location.href='newdir.cgi'\"/>\n");
				printf("<input type=\"button\" value=\"Nuevo archivo\" onClick=\"window.location.href='newfile.cgi'\"/>\n");
			printf("</div>\n");
		printf("</form>\n");
		printf("<form action=\"opendir.cgi\" method=\"post\">\n");
			printf("<div style=\"padding:10px; padding-left:40px;\">\n");
			printf("<table>\n");
				printf("<thead> <tr> <th>Marcar</th> <th>Nombre</th> <th></th> </tr> </thead>\n");
				printf("<tbody>\n");
					listar(dato);
					//printf("<thead> <tr> <th><input type="checkbox" /></th> <th>new</th> <th>file</th> </tr> </thead>\n");
				printf("</tbody>\n");
			printf("</table>\n");
			printf("</div>\n");
			printf("<div style=\"background:#f2f2f2; padding:10px;\">\n");
				printf("<input type=\"button\" value=\"Copiar\" onclick=\"window.location.href='copy.cgi'\"/>\n");
				printf("<input type=\"button\" value=\"Mover\" onclick=\"window.location.href='move.cgi'\"/>\n");
				printf("<input type=\"button\" value=\"Eliminar\" onclick=\"window.location.href='elim.cgi'\"/>\n");
			printf("</div>\n");
		printf("</form>\n");
		printf("<div style=\"padding:20px; background:#2a2a2a; color:#fff;\"> <p>&copy; ASO 2-2014</p> </div>\n");
	printf("</body>\n");
	printf("</html>\n");
}

int main(void) {
	imprimir("/home");
	return 0;
}


