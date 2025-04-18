#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

Playlist* criar_playlist() {
    Playlist* p = (Playlist*) malloc(sizeof(Playlist));
    if (p) {
        p->atual = NULL;
        p->tamanho = 0;
        p->modo_repeticao = 0;
    }
    return p;
}

void liberar_playlist(Playlist* playlist) {
    if (!playlist || !playlist->atual) {
        free(playlist);
        return;
    }

    Musica* atual = playlist->atual;
    Musica* inicio = atual;
    do {
        Musica* proxima = atual->proxima;
        free(atual);
        atual = proxima;
    } while (atual != inicio);

    free(playlist);
}

void adicionar_musica(Playlist* playlist, const char* titulo, const char* artista, int duracao) {
    if (!playlist) return;

    Musica* nova = (Musica*) malloc(sizeof(Musica));
    if (!nova) return;

    strcpy(nova->titulo, titulo);
    strcpy(nova->artista, artista);
    nova->duracao = duracao;

    if (!playlist->atual) {
        nova->proxima = nova;
        nova->anterior = nova;
        playlist->atual = nova;
    } else {
        Musica* ult = playlist->atual->anterior;

        nova->proxima = playlist->atual;
        nova->anterior = ult;

        ult->proxima = nova;
        playlist->atual->anterior = nova;
    }

    playlist->tamanho++;
    printf("Música \"%s\" adicionada com sucesso!\n", titulo);
}

int remover_musica(Playlist* playlist, const char* titulo) {
    if (!playlist || !playlist->atual) return 0;

    Musica* atual = playlist->atual;
    Musica* inicio = atual;

    do {
        if (strcmp(atual->titulo, titulo) == 0) {
            if (atual->proxima == atual) {
                playlist->atual = NULL;
            } else {
                atual->anterior->proxima = atual->proxima;
                atual->proxima->anterior = atual->anterior;
                if (playlist->atual == atual)
                    playlist->atual = atual->proxima;
            }
            free(atual);
            playlist->tamanho--;
            printf("Música \"%s\" removida com sucesso!\n", titulo);
            return 1;
        }
        atual = atual->proxima;
    } while (atual != inicio);

    printf("Música \"%s\" não encontrada!\n", titulo);
    return 0;
}

void proxima_musica(Playlist* playlist) {
    if (playlist && playlist->atual) {
        playlist->atual = playlist->atual->proxima;
        exibir_musica_atual(playlist);
    }
}

void musica_anterior(Playlist* playlist) {
    if (playlist && playlist->atual) {
        playlist->atual = playlist->atual->anterior;
        exibir_musica_atual(playlist);
    }
}

void alternar_modo_repeticao(Playlist* playlist) {
    if (playlist) {
        playlist->modo_repeticao = !playlist->modo_repeticao;
        printf("Modo de repetição %s.\n", playlist->modo_repeticao ? "ativado" : "desativado");
    }
}

void listar_musicas(Playlist* playlist) {
    if (!playlist || !playlist->atual) {
        printf("Playlist vazia.\n");
        return;
    }

    Musica* atual = playlist->atual;
    Musica* inicio = atual;
    int i = 1;

    printf("\n--- Músicas da Playlist ---\n");
    do {
        printf("%d. %s - %s (%d segundos)%s\n", i, atual->titulo, atual->artista, atual->duracao,
               atual == playlist->atual ? " <-- atual" : "");
        atual = atual->proxima;
        i++;
    } while (atual != inicio);
}

Musica* buscar_musica(Playlist* playlist, const char* titulo) {
    if (!playlist || !playlist->atual) return NULL;

    Musica* atual = playlist->atual;
    Musica* inicio = atual;

    do {
        if (strcmp(atual->titulo, titulo) == 0) {
            printf("Música encontrada: %s - %s (%d segundos)\n", atual->titulo, atual->artista, atual->duracao);
            return atual;
        }
        atual = atual->proxima;
    } while (atual != inicio);

    printf("Música \"%s\" não encontrada.\n", titulo);
    return NULL;
}

void exibir_musica_atual(Playlist* playlist) {
    if (playlist && playlist->atual) {
        Musica* m = playlist->atual;
        printf("Tocando agora: %s - %s (%d segundos)\n", m->titulo, m->artista, m->duracao);
    } else {
        printf("Nenhuma música está sendo tocada.\n");
    }
}
