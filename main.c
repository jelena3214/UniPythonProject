#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_SIZE 1000

void input_values(int n, int *p) {
    printf("Unesite %d vrednosti:", n * n);
    for (int i = 0; i < n * n; i++) {
        scanf("%d", p + i);
    }
}

int check(int *p, int n) {
    if (n == 1 || n == 2) return 0; // tada ne mozemo formirti mag sq
    int d = p[1] - p[0];
    for (int i = 2; i < n; i++) {
        if (p[i] - p[i - 1] != d)return 0;
    }
    return 1;
}

void arr_print(int *p, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", *(p + i));
    }
}

void arr_print2(int **p, int n) {
    for (int i = 0; i < n; i++) {
        arr_print(p[i], n);
        putchar('\n');
    }
}

void safe_allocate1(int *p) {
    if (p == NULL) {
        printf("Can't allocate space");
        exit(-1);
    }
}

void safe_allocate2(int **p) {
    if (p == NULL) {
        printf("Can't allocate space");
        exit(-1);
    }
}

void deallocate(int **p, int n) {
    for (int i = 0; i < n; i++) {
        free(p[i]);
    }
    free(p);
}

int **create_matrix(int n, int **matrix) {
    for (int i = 0; i < n; i++) {
        matrix[i] = calloc(n, sizeof(int));
        safe_allocate1(matrix[i]);
    }
    return matrix;
}

int **
initialize_magic_square(int **matrix, int *p, int *temp) { // fali provera da li je iz skupa vrednosti unetih na pocetku
    int num, row, column, value;
    printf("Koliko elemenata zelite da unesete?");
    scanf("%d", &num);

    for (int i = 0; i < num; i++) {
        printf("Unesite broj vrste, kolone i vrednost koju zelite da upisete");
        scanf("%d %d %d", &row, &column, &value);
        matrix[row][column] = value;
        p[i] = value;
        (*temp)++;
    }
    return matrix;
}

//kreiramo koren i propagiramo sinove, i za svakog odredimo flag, ubacimo ih u red, ko ima -1 izbacimo, ko ima 0 granamo dalje
//ispis stabla
//prolazak kroz stablo ispis resenja, provera da l su savrsena


//FUNKCIJE ZA RACUNANJE ZBIRA PO KOLONAMA, REDOVIMA, DIJAGONALAMA
int row_sum(int *p, int n) {
    int rowsum = 0;
    for (int i = 0; i < n; i++) {
        if (p[i] == 0) return 0;
        rowsum += p[i];
    }
    return rowsum;
}

int column_sum(int **matrix, int n, int column) {
    int columnsum = 0;
    for (int i = 0; i < n; i++) {
        if (matrix[i][column] == 0) return 0;
        columnsum += matrix[i][column];
    }
    return columnsum;
}

int main_diagonal_sum(int **matrix, int n) {
    int maindiagonal = 0;
    for (int i = 0; i < n; i++) {
        if (matrix[i][i] == 0) return 0;
        maindiagonal += matrix[i][i];
    }
    return  maindiagonal;
}

int sub_diagonal_sum(int **matrix, int n) {
    int subdiagonal = 0;
    for (int i = 0, j = n - 1; i < n; i++, j--) {
        if (matrix[i][j] == 0) return 0;
        subdiagonal += matrix[i][j];
    }
    return subdiagonal;
}

int set_flag(int **matrix, int n, int numberofzeros){
    int *arrrow , *arrcol, row, col;
    arrrow = calloc(n, sizeof(int));
    arrcol = calloc(n, sizeof(int));
    safe_allocate1(arrrow);
    safe_allocate1(arrcol);
    int main_diagonal = main_diagonal_sum(matrix, n);
    int sub_diagonal = sub_diagonal_sum(matrix, n);

    for(int i = 0, k = 0, s = 0; i < n; i++){
        row =  row_sum(matrix[i], n);
        if(row != 0) {
            arrrow[k++] = row;
        }
        col = column_sum(matrix, n, i);
        if(col != 0){
            arrcol[s++] = col;
        }
    }
    int row_check = arrrow[0], column_check = arrcol[0];
    if(row_check != 0 && column_check != 0){
        for (int i = 0; i < n; i++) {
            if (arrrow[i] != 0 || arrcol[i] != 0) {
                if ((arrrow[i] != row_check && arrrow[i] != 0) || (arrcol[i] != column_check && arrcol[i]!= 0)) return -1;
            }
        }
        if(row_check != column_check)return -1;
        if(main_diagonal == 0 && sub_diagonal != 0){
            if( sub_diagonal == row_check && sub_diagonal == column_check) return 0;
        }
        if(sub_diagonal == 0 && main_diagonal != 0){
            if( main_diagonal == row_check && main_diagonal ==  column_check) return 0;
        }

        if(main_diagonal == 0 && sub_diagonal == 0) return 0;

        if( main_diagonal == sub_diagonal && main_diagonal == row_check && main_diagonal == column_check){
            if(numberofzeros == 0){
                return 1; //magicni kvadrat
            }
            else return 0; //granaj dalje
        } else return -1;
    }else if(column_check == 0 && row_check != 0){
        for (int i = 0; i < n; i++) {
            if (arrrow[i] != 0) {
                if (arrrow[i] != row_check)return -1;
            }
        }
        if(main_diagonal == 0 && sub_diagonal != 0){
            if( sub_diagonal == row_check)return 0;
        }
        if(sub_diagonal == 0 && main_diagonal != 0){
            if( main_diagonal == row_check)return 0;
        }
        if(main_diagonal == 0 && sub_diagonal == 0) return 0;

    }else if(row_check == 0 && column_check != 0){
        for (int i = 0; i < n; i++) {
            if (arrcol[i] != 0) {
                if (arrcol[i] != column_check)return -1;
            }
        }
        if(main_diagonal == 0 && sub_diagonal != 0){
            if( sub_diagonal == column_check)return 0;
        }
        if(sub_diagonal == 0 && main_diagonal != 0){
            if( main_diagonal == column_check)return 0;
        }
        if(main_diagonal == 0 && sub_diagonal == 0) return 0;

    } else{
        if(main_diagonal == 0 && sub_diagonal != 0){
            return 0;
        }
        if(sub_diagonal == 0 && main_diagonal != 0){
            return 0;
        }
        if(main_diagonal == 0 && sub_diagonal == 0) return 0;
    }

}

typedef struct coordinates {
    int x, y;
} coordinates;

struct coordinates *Clearedcoord(struct coordinates *p, int numofzeros, int k) {
    for (int i = k; i < numofzeros - 1; i++) {
        p[i] = p[i + 1];
    }
    return p;
}

typedef struct TREE_NODE {
    int **info; //info je matrica, odnosno pokazivac na vrste matrice
    int leaf_flag; // info da li granati dalje i da li je to resenje
    struct TREE_NODE **sons; // pokazivac na listu pokazivaca, svaki pokazivac iz liste pokjazuje na novog sina
    struct coordinates *zeros; //pozicije nula
    int num_of_zeros;
    int *values;
}
        TREE_NODE;

struct TREE_NODE *tree(int **value, int m, int n, int *valuestoput) { // m je broj sinova
    struct TREE_NODE *temp = (struct TREE_NODE *) malloc(sizeof(struct TREE_NODE));
    temp->info = value;
    temp->leaf_flag = 0;
    temp->sons = malloc(m * sizeof(struct TREE_NODE *));
    temp->zeros = malloc(sqrt(m) * sizeof(struct coordinates));
    temp->values = malloc(sqrt(m) * sizeof(int));
    //memcpy(temp->values, valuestoput, m*sizeof(int));

    safe_allocate1(temp->values);
    for (int i = 0; i < sqrt(m); i++) {
        temp->values[i] = valuestoput[i];
    }

    int k = 0;
    for (int i = 0; i < n; i++) { //pozicije nula u matrici
        for (int j = 0; j < n; j++) {
            if (value[i][j] == 0) {
                temp->zeros[k].x = i;
                temp->zeros[k].y = j;
                k++;
            }
        }
    }
    temp->num_of_zeros = k;
    return temp;
}

struct TREE_NODE *createNode(int **value, int n, struct coordinates *zero_positions, int numofzeros,
                             int *valuestoput) { // br vrsta matrice, jer mora da se kopira
    struct TREE_NODE *newNode = malloc(sizeof(struct TREE_NODE));
    if (newNode == NULL) {
        printf("Can't allocate space");
        exit(-1);
    }
    newNode->info = calloc(n, sizeof(int *));
    safe_allocate2(newNode->info);
    for (int i = 0; i < n; i++) {
        newNode->info[i] = calloc(n, sizeof(int));
        safe_allocate2(newNode->info);
        for (int j = 0; j < n; j++) {
            newNode->info[i][j] = value[i][j];
        }
    }
    newNode->num_of_zeros = numofzeros;
    newNode->leaf_flag = 0;
    newNode->sons = NULL;
    newNode->values = malloc(numofzeros * sizeof(int));
    safe_allocate1(newNode->values);
    for (int i = 0; i < n; i++) {
        newNode->values[i] = valuestoput[i];
    }
    newNode->zeros = (struct coordinates *) malloc(numofzeros * sizeof(struct coordinates));
    //safe al
    for (int i = 0; i < numofzeros; i++) {
        newNode->zeros[i] = zero_positions[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < numofzeros; k++) {
                if (value[i][j] != 0 && newNode->zeros[k].x == i && newNode->zeros[k].y == j) {
                    newNode->zeros = Clearedcoord(zero_positions, numofzeros, k);
                    (newNode->num_of_zeros)--;
                }
            }
        }
    }

    return newNode;
}

//QUEUE
struct queueNode {
    struct TREE_NODE *info;
    struct queueNode *next;
};

struct queue {
    struct queueNode *front, *rear;
    int size;
};

struct queueNode *newNode(struct TREE_NODE *treen, int n) {//n je velicina kvadrata
    struct queueNode *temp = (struct queueNode *) malloc(sizeof(struct queueNode));
    //SAFE AL
    temp->info = (struct TREE_NODE *) malloc(sizeof(struct TREE_NODE));
    //SAFE AL
    temp->info->info = malloc(n * sizeof(int *));
    safe_allocate2(temp->info->info);
    for (int i = 0; i < n; i++) {
        temp->info->info[i] = calloc(n, sizeof(int));
        safe_allocate1(temp->info->info[i]);
        for (int j = 0; j < n; j++) {
            temp->info->info[i][j] = treen->info[i][j];
        }
    }
    temp->info->leaf_flag = treen->leaf_flag;
    temp->info->num_of_zeros = treen->num_of_zeros;
    int num_of_unused_values = n * n - temp->info->num_of_zeros;
    temp->info->values = malloc(num_of_unused_values * sizeof(int));
    safe_allocate1(temp->info->values);
    for (int i = 0; i < num_of_unused_values; i++) {
        temp->info->values[i] = treen->values[i];
    }

    temp->info->zeros = (struct coordinates *) malloc(temp->info->num_of_zeros * sizeof(struct coordinates));
    for (int i = 0; i < temp->info->num_of_zeros; i++) {
        temp->info->zeros[i] = treen->zeros[i];
    }

    temp->info->sons = NULL;

    temp->next = NULL;
    return temp;
}

struct queue *createQueue() {
    struct queue *q = (struct queue *) malloc(sizeof(struct queue));
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

void add(struct queue *q, struct TREE_NODE *treen, int n) {
    struct queueNode *temp = newNode(treen, n);
    (q->size)++;
    if (q->rear == NULL) { //ako je red prazan
        q->front = temp;
        q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

void delete(struct queue *q) {
    if (q->front == NULL)
        return;
    (q->size)--;
    struct queueNode *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
}

int isempty(struct queue *q) {
    if (q->size != 0) {
        return 0; //false
    }
    return 1;
}

void print_queue(struct queue *q, int n) {
    struct queueNode *temp = q->front;
    int k = q->size;
    while (k > 0) {
        arr_print2(temp->info->info, n);
        putchar('\n');
        temp = temp->next;
        k--;
    }
}

int number_of_sons(int n, int **matrix) {
    int not = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0) not++;
        }
    }
    return pow(not, 2);
}

int *difference_between_arrays(int arr1[], int *arr2, int n, int size, int num) {
    int *arr3 = malloc(size * sizeof(int));
    safe_allocate1(arr3);
    int e, k = 0, found;
    for (int i = 0; i < n * n; i++) {
        e = arr2[i];
        found = 0;
        for (int j = 0; j < num; j++) {
            if (e == arr1[j]) {
                found = 1;
                break;
            }
        }
        if (found == 0) {
            *(arr3 + k) = e;
            k++;
        }
    }
    return arr3;
}

int *remove_from_arr(int *arr, int n, int value) {
    int index;
    for (int i = 0; i < n; i++) {
        if (arr[i] == value) {
            index = i;
        }
    }
    for (int j = index; j < n - 1; j++) {
        arr[j] = arr[j + 1];
    }
    return arr;
}



int main() {
    int *magic_square_values, p[MAX_SIZE], temp = 0; //temp br unetih elemenata u kvadrat na pocetku,  p niz tih brojev
    int size_of_magic_square, flag;
    int **init_state;
    struct TREE_NODE *root;
    struct queue *Q = createQueue();

    printf("Unesite velicinu magicnog kvadrata n");
    scanf("%d", &size_of_magic_square);

    magic_square_values = calloc(pow(size_of_magic_square, 2), sizeof(int));
    safe_allocate1(magic_square_values);

    input_values(size_of_magic_square, magic_square_values);
    flag = check(magic_square_values, size_of_magic_square); // DODAJ DA SE IZVRSAVA SAMO AKO JE FLAG 1

    //arr_print(magic_square_values, pow(size_of_magic_square,2));
    if (flag) {
        init_state = (int **) malloc(size_of_magic_square * sizeof(int *));
        safe_allocate2(init_state);

        init_state = create_matrix(size_of_magic_square, init_state);
        init_state = initialize_magic_square(init_state, p, &temp);
        //int jk = set_flag(init_state, size_of_magic_square, 2);
        int *s = difference_between_arrays(p, magic_square_values, size_of_magic_square,
                                           pow(size_of_magic_square, 2) - temp, temp);
        root = tree(init_state, number_of_sons(size_of_magic_square, init_state), size_of_magic_square, s);
        root->leaf_flag = set_flag(root->info, size_of_magic_square, root->num_of_zeros);
        //arr_print2(root->info, size_of_magic_square);
        //add(Q, root, size_of_magic_square);
        //arr_print(s, pow(size_of_magic_square, 2) - temp);
        int **square = init_state;
        int loop = pow(size_of_magic_square, 2) - temp; //broj neubacenih vrednosti na pocetku
        int numofzeros = root->num_of_zeros; //broj koordinata nula na pocetku
        struct coordinates *zerocoordinates = (struct coordinates *) malloc(numofzeros * sizeof(struct coordinates));
        //safe al
        for (int i = 0; i < numofzeros; i++) {
            zerocoordinates[i] = root->zeros[i];
        }
        struct TREE_NODE **rootsons = root->sons;
        int *notinmatrix = malloc(loop * sizeof(int));
        safe_allocate1(notinmatrix);
        for (int i = 0; i < loop; i++) {
            notinmatrix[i] = root->values[i];
        }
        //safe al
        for (int i = 0; i < numofzeros; i++) {
            zerocoordinates[i] = root->zeros[i];
        }
        while(!isempty(Q)) {
            for (int i = 0, sonposition = 0; i < loop; i++) {
                for (int j = 0; j < numofzeros; j++) {
                    square[zerocoordinates[j].x][zerocoordinates[j].y] = root->values[i]; //ubacivanje vrednosti u matricu na odredjenu poziciju
                    rootsons[sonposition] = createNode(square, size_of_magic_square, zerocoordinates, numofzeros,
                                                       remove_from_arr(notinmatrix, numofzeros,
                                                                       root->values[i])); //kreiranje novog sina
                    rootsons[sonposition]->leaf_flag = set_flag(rootsons[sonposition]->info, size_of_magic_square, rootsons[sonposition]->num_of_zeros); //setuje 0 -1 ili 1 za svaki cvor
                    //arr_print2(rootsons[sonposition]->info, size_of_magic_square);
                    add(Q, rootsons[sonposition], size_of_magic_square);
                    square[zerocoordinates[j].x][zerocoordinates[j].y] = 0;
                    sonposition++;
                }
            }
            if(Q->front->info->leaf_flag == -1){
                delete(Q);
            } else if(Q->front->info->leaf_flag == 0){
                continue;
            }else{
                arr_print2(Q->front->info->info, size_of_magic_square);
                delete(Q);
            }

        }
        print_queue(Q, size_of_magic_square);

        //arr_print2(root->info, size_of_magic_square);

        deallocate(init_state, size_of_magic_square);
    }
    return 0;
}
