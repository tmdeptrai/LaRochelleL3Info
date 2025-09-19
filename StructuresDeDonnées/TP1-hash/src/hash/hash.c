#include "hash.h"
//#include "hash.inc"
#include <stdlib.h>
#include <stdbool.h>   
#include <string.h> 

const static size_t hashtable_primes[] =
{
 11,
 19,
 37,
 73,
 109,
 163,
 251,
 367,
 557,
 823,
 1237,
 1861,
 2777,
 4177,
 6247,
 9371,
 14057,
 21089,
 31627,
 47431,
 71143,
 106721,
 160073,
 240101,
 360163,
 540217,
 810343,
 1215497,
 1823231,
 2734867,
 4102283,
 6153409,
 9230113,
 13845163,
};
static const double HASHTABLE_MIN_COLLISIONS = 0.3;
static const double HASHTABLE_MAX_COLLISIONS = 3.0;

static const size_t HASHTABLE_NB_PRIMES = sizeof(hashtable_primes) / sizeof(size_t);

#define HASHTABLE_MIN_SIZE hashtable_primes[0]
#define HASHTABLE_MAX_SIZE hashtable_primes[HASHTABLE_NB_PRIMES - 1]

static HashTable   *
_hashtable_new(size_t length, size_t size, size_t(*hash) (const void *, size_t), int (*compare) (const void *, const void *))
{
    HashTable *table = (HashTable *) malloc(sizeof(size_t) * 3 + 2 * sizeof(void *) + sizeof(List) * length);

    if (table) {
        size_t              i;

        table->hash = hash;
        table->compare = compare;
        table->length = length;
        table->nb = 0;
        table->size = size;
        for (i = 0; i < length; i++) {
            table->list[i] = NULL;
        }
    }
    return table;

}


HashTable          *
hashtable_new(size_t size, size_t(*hash) (const void *, size_t), int (*compare) (const void *, const void *))
{
    return _hashtable_new(HASHTABLE_MIN_SIZE, size, hash, compare);
}

static void
_hashtable_resize(HashTable ** ptable)
{
    double              ratio = (*ptable)->nb / (double)(*ptable)->length;

    if ((*ptable)->nb >= HASHTABLE_MIN_SIZE &&
        (*ptable)->nb <= HASHTABLE_MAX_SIZE &&
    (ratio > HASHTABLE_MAX_COLLISIONS || ratio < HASHTABLE_MIN_COLLISIONS)) {
        size_t              i = 1;
        HashTable          *new;

        while (hashtable_primes[i] < (*ptable)->nb)
            i++;

        new = _hashtable_new(hashtable_primes[i],
                             (*ptable)->size,
                             (*ptable)->hash,
                             (*ptable)->compare);

        if (new) {
            size_t              j;

            new->nb = (*ptable)->nb;
            for (j = 0; j < (*ptable)->length; j++) {
                List                list = (*ptable)->list[j], next;

                while (list) {
                    size_t              h = new->hash(list->data, new->length);

                    next = list->next;
                    list->next = new->list[h];
                    new->list[h] = list;
                    list = next;
                }
            }
            free(*ptable);
            *ptable = new;
        }
    }
}

void
hashtable_apply(HashTable * table, void (*func) (void *, void *), void *extra_data)
{
    // A COMPLETER (applique la fonction func sur tous les elements de la table en utilisant extra_data
    if (table == NULL||func == NULL) return;

    for (size_t i = 0; i < table->length;i++){
        if (table->list[i]!=NULL){
            list_foreach(table->list[i],func,extra_data);
        }
    }
}

void
hashtable_print(HashTable * table, void (*print) (void *, FILE *), FILE * stream)
{
    if (!table || !print || !stream) return; // safety check

    for (size_t i = 0; i < table->length; i++) {
        List bucket = table->list[i];

        while (bucket) {
            print(bucket->data, stream);
            bucket = bucket->next;
        }
    }
}

void
hashtable_delete(HashTable * table, void (*delete) (void *))
{
        // A COMPLETER (supprime tous les elements de la tale)
    for (size_t i = 0;i<table->length;i++){
        list_delete(&table->list[i],delete);
    }
}

void               *
hashtable_lookup(HashTable * table, void *data)
{
        // A COMPLETER  (recherche d'un element dans une table)
    size_t h = table->hash(data,table->length);

    List bucket = table->list[h];

    return list_find_data(bucket,data,table->compare);
}

int
hashtable_insert(HashTable ** ptable, void *data, void (*delete) (void *))
{
        // A COMPLETER (insere une element dans une table)
    HashTable *table = *ptable;
    if (!table) return 0; //table empty

    void* found = hashtable_lookup(table,data);
    if (found) return 0; //already exists

    size_t h = table->hash(data,table->length);
    List *bucket = &table->list[h];
    list_append(bucket,data,table->size);

    //Update table length + resize if necessary
    table->nb++;
    _hashtable_resize(ptable);
    
    return 1; //Success
}

int
hashtable_retract(HashTable ** ptable, void *data, void (*delete) (void *))
{
        // A COMPLETER (supprime une element d'une table)
    HashTable *table = *ptable;
    if (!table) return 0;

    size_t h = table->hash(data,table->length);
    List *bucket = &table->list[h];

    //Find the index of the data
    int index = list_index_data(*bucket,data,table->compare);
    if (index<0) return 0; //Not found

    list_remove_nth(bucket,(size_t)index,delete); //remove the data at n-th index if found

    //Update table length and resize if necessary
    table->nb--;
    _hashtable_resize(ptable);

    return 1; //Success
}

