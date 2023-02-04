#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1000
char str[60];

struct Data {
    char url[100];
    int outdegree;
    double pagerank;
    struct Data* next;
};

struct Data *head;
struct Data* createEmptyList();
void scan_file(char *file_name, struct Data **curr);
void free_list(struct Data* head);
void search_file(char *file_name, char *argv[], int argc,struct Data **curr);

int main(int argc, char **argv) {

    if (argc > 2) {
        head = createEmptyList(); 
        scan_file("pagerankList.txt",&head);
        // free_list(head);
        search_file("invertedIndex.txt",argv,argc,&head);
        free_list(head);
    }
}

struct Data* createEmptyList() {
    return NULL;
}

void scan_file(char *file_name, struct Data **curr){

    struct Data *head = NULL;
    struct Data *current = NULL;

    FILE *fp = fopen(file_name,"r");
    if (fp == NULL) {
        printf("File was empty man!! Fill it up and check agian.\n");
    }

    char record[MAX_LENGTH];
    char url[100];
    int outdegree;
    double pagerank;
    if (fgets(record, MAX_LENGTH,fp) == NULL ){
        printf("file is empty\n");
    }
    else {

        while (fgets(record, MAX_LENGTH,fp) != NULL ){
            sscanf(record,"%[^,],%d, %lf", url, &outdegree, &pagerank);

            struct Data *new = malloc(sizeof(struct Data));
            strcpy(new->url, url);
            new->outdegree = outdegree;
            new->pagerank = pagerank;
            new->next = NULL;

            if (head == NULL) {
                head = new;
                current = new;
            } else {
                current->next = new;
                current = new;
            }
        }
        fclose(fp);

        current = head;
        while (current != NULL) {
            // printf("%s %d %lf\n", current->url, current->outdegree, current->pagerank);
            current = current->next;
        }
    *curr = head;
    }
}

void free_list(struct Data* head) {
    struct Data* current = head;
    while (current != NULL) {
        struct Data* temp = current;
        current = current->next;
        free(temp);
    }
}


void search_file(char *file_name, char *argv[],int argc,struct Data **curr) {
    FILE *fp = fopen(file_name, "r");
    fputs

    if (fp == NULL) {
        printf("go back bro!! check again whats the error \n");
    }

    char record[MAX_LENGTH];
    char url[100];
    char word[100];
    int url_count[argc];
    char word_urls[argc][100][100];
    int unmatched = 0;
    char unmatched_url[100][100];
    // int matched = 0;

    // Initialize the URL count to 0 for each word
    int i = 0;
    while (i < argc) {
        url_count[i] = 0;
        i++;
    }

    while(fgets(record, MAX_LENGTH, fp) != NULL) {
        sscanf(record, "%s %[^\n]", word, url);

        // Check if the word is in argv
        int i = 1;
        while (i < argc) {
            if (strcmp(word, argv[i]) == 0) {
                // Store the URL

                char *url_s = strtok(url," ");
                while (url_s != NULL){
                    strcpy(word_urls[i][url_count[i]], url_s);
                    // printf("%s\n",word_urls[i][url_count[i]]);
                    url_count[i]++;
                    url_s = strtok(NULL," ");
                }
            }   
        i++;
        }
        int found = 0;
        //argc_1
        int j = 1;
        while (j < argc) {
            //argc_2 for 2nd word
            int k = j + 1;
            while (k < argc) {
                //checking for word repetition to avoid erros
                if (j != k) {
                    //for url_1 iterate
                    int l = 0;
                    while (l < url_count[j]) {
                        //for url_2 iterate
                        int m = 0;
                        while (m < url_count[k]){
                            
                            if (strcmp(word_urls[j][l], word_urls[k][m]) != 0) {
                                found = 0;
                                int n = 0;
                            while (n < unmatched) {
                                if (strcmp(word_urls[j][l], unmatched_url[n]) == 0) {
                                    found = 1;
                                    break;
                                }
                            n++;
                            }
                            if (found == 0) {
                            strcpy(unmatched_url[unmatched], word_urls[j][k]);
                            unmatched++;
                            }
                            }








                            else if (strcmp(word_urls[j][l], word_urls[k][m]) == 0){
                               struct Data *curr = head;
                               while (curr != NULL) {
                                    if (strcmp(curr->url, word_urls[j][l]) == 0){
                                        
                                        printf("%s\n", word_urls[j][l]);
                                        break;
                                    }
                                    else {

                                        curr = curr->next;
                                    }
                                }
                                
                               found  = 1;
                            }
                            //    break;
                        m++;
                        }
                    l++;
                    }
                }
            k++;    
            }
        j++;
        }
        if (unmatched > 0) {
        printf("Unmatched URLs:\n");
        int i = 0;
        while (i < unmatched) {
            printf("%s\n", unmatched_url[i]);
            i++;
        }
        }
        if (found == 1){
            break;
        }
        
    }
fclose(fp);

}
