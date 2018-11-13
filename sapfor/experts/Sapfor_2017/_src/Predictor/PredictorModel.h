#ifndef _XP_STRUCTS_H_
#define _XP_STRUCTS_H_

#include <vector>
#include <list>

typedef std::vector<int> vect_int;
typedef std::vector<long> vect_long;

struct var;
struct loop;

//enum ReductionOp {SUM, PRODUCT, MAX, MIN, AND, OR, EQV, NEQV, MAXLOC, MINLOC, EMPTY, REGULAR, OUTPUT};
/*enum DepType 
{
	REDUCTION,  // редукционная переменная (и операция)
	PRIVATE,    // приватная переменная для цикла (присваивание до чтения внутри цикла, за пределами цикла не читается перед присваиванием)
	OUT,
	FLOW,
	ANTI,
	VAR_DEP_IS,      // есть зависимость по массиву (может быть уточнена через redop EMPTY, REGULAR, OUTPUT, POSSIBLE)
	VAR_DEP_NO,
	EXIT,       // есть выход из цикла
	CALL_OP,       // есть вызов подпрограммы //нужно ли?
	IO,         // операторы ввода-вывода....//нужно ли?
	IO_RESTRICT,// операторы ввода-вывода, плохие для распараллеливания на DVM...//нужно ли?
	NO_PRIVATE, // это не является зависимостью - но временный шаг !!!
	PRIVATE_ALL, 
	F_PRIVATE, // first private for OpenMP
	L_PRIVATE, // last private for OpenMP
//	FAIL,       // а с чем-то анализатор не справился
	OTHER_CAUSE
};*/

//================ Internal form of DB ===============
struct mach
{
	int id;
	char *name;
	enum mach_Type comm_type;
	double TStart;
	double TByte;
	long proc_number;	
	long proc_perf;	
};

struct proc_set
{
	int id;
	int proc_num;
	vect_long proc;
};
	
struct classizes
{
	int id;
	char *varid; // will change to var->name;
	var *v;// so change to var->name;
	int value;
};

struct task_var
{
	int id;
	char *name; 
	char *comment;
	vector<struct classizes> values;
};

struct monom
{
	int id;
	int koef;
	char *varid; //need to remove
	var *v;
	bool can_be_calc; //may be only for debug

	float Calculate(); //вычисляет
};

struct expr
{
	int id;
	char *text;
	char *polix_text;
	bool is_line_expr;
	vector<monom> monoms;
	bool can_be_calc; //may be only for debug

    float Calculate() { return 0.0; } //вычисляет
    float Calculate(float) { return 0.0; } //вычисляет если может, иначе присваивает float, can_be_calc=false
    string Calculate(expr *express, var *v, expr *ex) { return ""; } //подставляет вместо переменной выражение
    char* find_varid() { return NULL; } //возвращает имя первой переменной в выражении
    int find_num(bool *can) { return 0; } //возвращает размер первого смещения в выражении
    var* find_v() { return NULL; } //возвращает первую переменную в выражении
};

struct var
{
	int id;
	char *name;
	int routine;
	char *type;
	int type_size;
	int rank;
	vector<int> dim;
	vector<bool> NotDistr; //заполняется в Find_loop_distr()
	vector<expr *> low;
	vector<expr *> hi;

	bool io_restrict; //сюда кидаем и common признак, если плохой блок
	bool call_restrict; //используется в вызове вcтроенной функции поэтому не может быть распределена
	bool red_restrict; //используется в редукции поэтому не может быть распределена
	bool is_allocatable;
	long first_alloc_line; // вообще лучше оператор, и сравнивать их порядок выполнения
	long addr;
	bool not_write_in_loops;
    //Признак приватности массива для всех циклов программы, 
    //означает что нет переноса значений из одного цикла за его пределы.
    //его не ставит Анализатор
    //ставим в Find_loop_distr()
	bool is_private; 	

	vector <var *> io_rest_list; // последний в этом списке имеет io_restrict, остальные пишутся в одних массивах
	vector <int> io_rest_line; // номера циклов связей массивов по записи и номер строки плохого оператора ввода-вывода

	bool is_private_in_one_loop;
	var(int _id):id(_id){}
	var(){}
};

struct usage
{
	long id;
	var *v; //we assumed that such var exists in BD
	usage *that; 
	long that_id; 
	loop* that_loop;
	long that_loop_id; 
	char mode; // W or R
	long oper;
	vector<expr *> indexes;
};

struct oper
{
	long id;
	long line;
	bool is_allocate;
};

struct alloc
{
	long usage_id; // using while make indexes - can be dismissed after that
	long oper_id;
	long line;
	var *v;
	vector<expr *> low;
	vector<expr *> hi;
};

struct sector_usage
{
	long id;
	var *v; //we assumed that such var exists in BD
	vector<long> oper;
	vector<expr *> min_ind;
	vector<expr *> max_ind;
	vector<expr *> step;
};

struct glob_shadow
{
	var *v;
	loop *loop;
	vector<int> shad_wid_left;
	vector<int> shad_wid_right;
	vector<sector_usage *> write_use;
};

/*
struct depend
{
	int id; 
	DepType dep_t;
	char* varid;
	var *v;
	ReductionOp red_op;
	int dimno;
	struct var *loc_arr;
	int loc_cnt;
	vector<long> dep_usage_id;
};*/

struct loop
{
	int id;
	int line;
	int last_line;
	long oper_id; //id цикла
	long routine_id;
	long time;
	char *varid;
	var *v;
	expr *first, *last, *step;
	expr *old_first, *old_last, *old_step;
	long iter;
	bool iter_was_changed;

	loop *parent;
	vector<loop *> children;
	vector<loop *> self_call;
	bool tightly_with_parent;

	vector<long> oper;
	vector<long> oper_lines;
	vector<usage> var_access;
	//vector<depend> depends;
	vector<var *> remote_vars; //remote operation in this node, not inner, not outer
	bool is_io;
	bool is_par;

	vector<sector_usage> write_sect;
	vector<sector_usage> read_sect;
};

struct routine
{
	int id;
	char *name;
	long line;
	long last_var_line;
	long body_line;
	long body_oper;
	int file_id;
	loop *root;
	vector<var*> r_var;
};

struct call
{
	int id;
	long oper_before;
	long oper;
	routine *rout;
	vector<expr*> arg;

};


//===================== Addition form ==================
struct seq_loop  // getting unusefull
{	long loop_line;
	long beg_line;
	long end_line;
	double times;
	double iter_time;
	bool ifgoto; //флаг того, что надо пробегать цикл, а не умножать время витка на его количество
};

struct my_red
{	
    //ReductionOp type;
	vector<var*> red_var;
	var *red_loc_arr;
	int red_loc_cnt;
};

struct my_shad
{	
    var * sh_var;
	vector<long> lower;
	vector<long> upper;
	bool corner;
};

//================= Directives and Predict Results =====================
struct dir_bin_data
{	vector<int> data;
	float time;
};

struct data_distr_scheme
{
	int proc_id;
	vector<var *> array;
	vector<vect_int> dim_distr;
};

struct tmp_distr_var
{
	int id;
	vector<int> proc_dim;
};

struct Interval_node
{
	Interval *inter;
	int line;
	int type; //0=main  1=inner_seq
	double iter_count;

	vector<Interval_node *> children;

	void insert(loop *curr_loop, Interval *tmp_inter, int type, double times);
	void add(loop *curr_loop, Interval *tmp_inter, int type, double times);
	void print(int level);
	void calc(double times);
};

struct scheme_type
{
	int id;
	int xp_id;
	char name[16];
	vector <dir_bin_data> v_dir_bin;
	vector <seq_loop> seq_loops;
	vector <long> oper_line;
	vector <long> oper_id;
	vector <string> v_dir_str;

	vector<Interval *> results; // getting unusefull
	vector<int> res_lines; // getting unusefull

	struct Interval_node* Interval_tree;
};

struct res
{
    double poss;
	int line; //номер слудующей инструкции
//	bool go;
	Interval *inter_max;
	Interval *inter_min;
	Interval *inter_mid;

    res() {}; 
};

struct conf	
{	
    long proc_num;		
	long_vect  proc_set;		
	long mark;	
};

struct searched
{
    long proc_num;		
	int proc_id_diff;
	long_vect  proc_set;		
	double time;	
};

typedef std::vector<searched> searched_vect;

struct inter_perf
{
	float seq_time;
	float par_time;
	float comm_time;
	loop *loop;
};

struct scheme_perf
{
	int sch_id;
	int proc_num;
	vector<long> proc_set;

	inter_perf main;
	vector<inter_perf> intervals;
};

typedef vector<scheme_type> one_routine_all_scheme;
typedef vector<var*> vect_var;
typedef vector<usage*> vect_usage;

struct control_block
{
	vector<long> oper_line;
	vector<long> oper_id;

	bool flow_inside; //все операторы внутри блока идут последовательно. Нет переходов внутри и наружу.
	control_block *next_block;
	vector<control_block *> jump;
	vector<var*> write_data;
	vector<var*> read_data;
};

struct control_graph
{
	control_block *root_block;
	vector<control_block> block;
};

struct associate_align
{
	// b(k)->a(k,m)
	vector<int> dim_align; // dim_align[0]=0
	//and remember a(k,m) to make replace
};
#endif