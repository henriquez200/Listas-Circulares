#ifndef PLAYLIST_H
#define PLAYLIST_H

typedef struct Musica {
    char titulo[100];
    char artista[100];
    int duracao;
    struct Musica* proxima;
    struct Musica* anterior;
} Musica;

typedef struct {
    Musica* atual;
    int tamanho;
    int modo_repeticao;
} Playlist;

Playlist* criar_playlist();
void liberar_playlist(Playlist* playlist);

void adicionar_musica(Playlist* playlist, const char* titulo, const char* artista, int duracao);
int remover_musica(Playlist* playlist, const char* titulo);

void proxima_musica(Playlist* playlist);
void musica_anterior(Playlist* playlist);

void alternar_modo_repeticao(Playlist* playlist);

void listar_musicas(Playlist* playlist);
Musica* buscar_musica(Playlist* playlist, const char* titulo);
void exibir_musica_atual(Playlist* playlist);

#endif
