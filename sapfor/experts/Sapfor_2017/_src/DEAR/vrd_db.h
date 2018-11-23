#ifndef _VRD_DB_H
#define _VRD_DB_H

/*
*   Simple SQL-engine (SQLite) wrapper
*
*   Only one data-base can be opened at a time.
*   Only one table of the current DB can be read at a time.
*   The table is read as a whole. (Memory is freed automatically.)
*   All the data are put|get as character strings.
*/

#ifdef __cplusplus
extern "C" {
#endif

int vrd_open(char * proj);  // open DB <proj>.db by project name
int vrd_close(void);        // close the current db
int vrd_flush(void);        // commit the previous transaction and begin the new 

/*
*   Insert or update data
*/

int vrd_put_row(char * table,   // <table> of current DB
        char * fields);         //  comma separated colomn values
/************************ usage sample:
*** for a table with the first colomn defined as PRIMARY KEY:
*    char buf[1000];
*    int pkey;
*    // key value set by the user:
*    for(i=0; i<nLoop; i++) {
*       pkey = i+1;
*       sprintf(buf, "%d,    %d, %d, %d, %d, %d, %d ",   pkey,
*           sLoop[i].line, sLoop[i].nops, sLoop[i].name,
*           sLoop[i].erange[0], sLoop[i].erange[1], sLoop[i].erange[2] );
*       rowid = vrd_put_row("loops", buf);
*    }
*    // key value is generated and returned
*    for(i=0; i<nLoop; i++) {
*       sprintf(buf,   "NULL, %d, %d, %d, %d, %d, %d ",
*           sLoop[i].line, sLoop[i].nops, sLoop[i].name,
*           sLoop[i].erange[0], sLoop[i].erange[1], sLoop[i].erange[2] );
*       pkey = vrd_put_row("loops", buf);
*    }
********************** end of sample **/

/*
*   Read a table as <rows>*<cols> 1D-array of strings
*   NOTE: only one table can present in memory at a time; next get_table
*       destroys the previous table (in fact, it frees memory!)
*   NOTE: in debugging mode is ignored !
*/

int vrd_get_table(char * table, // Table name
        int* rows, int* cols,   //  the number of rows and colomns
        char*** fields,         //  <rows>*<cols> strings - values (by rows)
        char*** col_names);     //  <cols> strings -- colomn names

/************************ usage sample:
*    int cols, rows, i, j, rc;
*    char ** data, ** names;
*
*    rc = vrd_get_table( "loops", &rows, &cols, &data, &names);
*
*    if(rc==0){
*        printf("AFTER get_table\n");
*        printf(" cols = %d   rows = %d \n", cols, rows);
*        for(i=0; i<cols; i++) printf(" %s ", names[i]);
*        printf("\n");
*        for(j=0; j< cols*rows; ){
*            for(i=0; i<cols; i++,j++) printf(" %s ", data[j]);
*            printf("\n");
*            }
*    }
********************** end of sample **/

/*
*   Arbitrary SELECT-operator
*/

int vrd_select(char * sql,      // SELECT body
        int* rows, int* cols,   //  the number of rows and colomns
        char*** fields,         //  <rows>*<cols> strings - values (by rows)
        char*** col_names);     //  <cols> strings -- colomn names

/*
*   DEBUGGING MODE flag:
*   -- do not apply SQL-commands to a database <name>.db,
*   -- but only print them to a file <name>.deb.
*   Then they can be applyed to any <database> by the command:
*       vrdbutil <database> <name>.deb
*/
extern int vrdb_deb;

#ifdef __cplusplus
}
#endif
#endif /* _VRD_DB_H_ */
