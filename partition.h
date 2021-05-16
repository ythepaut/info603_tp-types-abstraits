/**
 * INFO603 TP Exercice 1
 * Lucas CHARDONNET - Yohann THEPAUT
 *
 * Sémentique axiomatique de la procédure partition
 */

#ifndef TP1_PARTITION_H
#define TP1_PARTITION_H

int* median(int* a, int* b, int* c);

void partition(int* tab, int i, int j, int* k);

int assertion2(int* tab, int k, int j, int i);
int assertion3(int* tab, int i, int l);
int assertion4(int* tab, int l, int k);
int assertion6(int* tab, int i, int j, int pivot, int position_pivot);

#endif //TP1_PARTITION_H
