#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;

// -----
const bool silent = true;
const bool use_abs_knn = false;
const bool norm_year   = false;
const int  nfold  = 20;
const int  ntest  = 5000;
const bool use_all_instance = false;

inline void assert_true( bool exp ){
    if( !exp ){
        fprintf( stderr, "assert error\n" );
        exit( -1 );
    }
}

inline void assert_true( bool exp, const char *msg ){
    if( !exp ){
        fprintf( stderr, "assert error:%s\n", msg );
        exit( -1 );
    }
}

inline double sqrs( double a ){
    a = fabs( a );
    if( a > 25.0 ) a = 25.0;
    return a * a;
}

inline double get_metric( double rmse ){
    return 1000000.0 / rmse;
}
namespace rnd{    
    inline double next_double(){
        return static_cast<double>( rand() ) / (static_cast<double>( RAND_MAX )+1.0);
    }
    inline double next_double2(){
        return (static_cast<double>( rand() ) + 1.0 ) / (static_cast<double>(RAND_MAX) + 2.0);
    }    
    inline int next_int( void ){
        return (int)rand();
    }
    inline int next_int( int n ){
        return (int) floor( next_double() * n ) ;
    }
    inline double sample_normal(){
        double x,y,s;
        do{
            x = 2 * next_double2() - 1.0;
            y = 2 * next_double2() - 1.0;
            s = x*x + y*y;
        }while( s >= 1.0 || s == 0.0 );
        
        return x * sqrt( -2.0 * log(s) / s ) ;
    }    
    inline double sample_normal( double mu, double sigma ){
        return sample_normal() * sigma + mu;
    }

    template<typename T>
    inline void exchange( T &a, T &b ){
        T c;
        c = a;
        a = b;
        b = c;
    }

    template<typename T>
    inline void shuffle( T *data, size_t sz ){
        if( sz == 0 ) return;
        for( int i = (int)sz - 1; i > 0; i-- ){
            exchange( data[i], data[ next_int( i+1 ) ] );
        } 
    }
};

double scale_score = 150.0;

struct Param{
    int active_type;
    int max_round, num_round;
    int reg_method;
    int num_user, num_item, num_global, num_factor, num_gregfree;
    float base_score;
    float learning_rate, wd_user, wd_item, wd_gbias, wd_ubias, wd_ibias;
    float B_user, B_item;
    Param(){
        num_user = num_item = num_global = num_factor = 0;
        learning_rate = 0.01f;
        wd_user = wd_item = 0.01f;
        wd_ubias= wd_ibias= wd_gbias = 0.0f;
        base_score = 0.0f;
        num_gregfree = 0;
        active_type = 0; max_round = 1270;
        B_user = B_item = 1.0;
        reg_method = 0; num_round = 0;
    }
    
    inline float map_active( float sum ){
        switch( active_type ){
        case 2 : return 1.0f/(1.0f+expf(-sum ));
        default: return sum;
        }                
    } 
    
    inline float cal_grad( float r, float pred ){
        return r - pred;
    };
    
    inline void set_base( float base ){
        switch( active_type ){
        case 2 : 
            assert_true( base > 1e-6f && base < 1.0f - 1e-6f, "base_error" );
            base_score = - logf( 1.0f / base - 1.0f ); 
            break;
        default: base_score = base;
        }        
    }
};

struct Vector{
    float *ptr;
    int x_max;
    Vector(){     
//        printf("Vector Begin!");
        ptr = NULL;
    //    printf("Vector End!"); 
    }
    inline float &operator[]( int idx ){
        return ptr[ idx ];
    }
    inline void free_space(){
        if( ptr != NULL ) {
            delete [] ptr; ptr = NULL;
        }
    }
    inline void alloc_space(){
        ptr = new float[ x_max ];        
    }
    inline void alloc_space( int x_max ){
        this->x_max = x_max; this->alloc_space();
    }
    inline Vector &operator=( float val ){
        std::fill( ptr, ptr+x_max, val );
        return *this;
    }    
    inline Vector &operator*=( float val ){
        for( int i = 0; i < x_max; i ++ ){
            ptr[ i ] *= val;
        }
        return *this;
    }    
    inline Vector &add( const Vector &v, float scale = 1.0f ){
        for( int i = 0; i < x_max; i ++ ){
            ptr[ i ] += v.ptr[i] * scale;
        }
        return *this;
    }
    inline double dot( const Vector &v ) const{
        double sum = 0.0;
        for( int i = 0; i < x_max; i ++ ){
            sum += v.ptr[i] * ptr[i];
        }
        return sum;
    }
};

struct Matrix{
    float *ptr;
    int y_max, x_max;
    Matrix(){ 
        //printf("Matrix Begin!");
        ptr = NULL;
    //    printf("Matrix End!");
    }
    inline void alloc_space(){
        ptr = new float[ y_max * x_max ];        
    }
    inline void free_space(){
        if( ptr != NULL ) {
            delete [] ptr; ptr = NULL;
        }
    }
    inline void alloc_space( int y_max, int x_max ){
        this->y_max = y_max; this->x_max = x_max; this->alloc_space();
    }
    inline Matrix &operator*=( float val ){
        for( int i = 0; i < x_max * y_max; i ++ ){
            ptr[ i ] *= val;
        }
        return *this;
    }
    inline Vector operator[]( int idx ){
        Vector v;
        v.x_max = x_max; v.ptr = ptr + idx * x_max;
        return v;
    }
    inline void randinit( float sigma = 0.01f ){
        for( int i = 0; i < y_max * x_max; i ++ ){
            ptr[ i ] = rnd::sample_normal() * sigma;
        } 
    }
};

struct Elem{
    float  label;
    int num_global;
    int num_ufactor;
    int num_ifactor;
    unsigned *index_global;
    unsigned *index_ufactor;
    unsigned *index_ifactor;
    float *value_global;
    float *value_ufactor;
    float *value_ifactor;

    inline int total_num( void ) const{
        return num_global + num_ufactor + num_ifactor;
    }
    inline void set_space( unsigned *index, float *value ){
        index_global = index;
        value_global = value;
        index_ufactor= index_global  + num_global;
        index_ifactor= index_ufactor + num_ufactor;
        value_ufactor= value_global  + num_global;
        value_ifactor= value_ufactor + num_ufactor;
    }
    inline void alloc_space( void ){
        this->set_space( new unsigned[ total_num() ], new float[ total_num() ] );
    }
    inline void free_space( void ){
        delete [] index_global;
        delete [] value_global;
    }    
};        

class SVDTrainer{
private:
    Matrix W_user, W_item;
    Vector g_bias, u_bias, i_bias;
    Vector tmp_ufactor, tmp_ifactor;    
private:
    inline static void project( Vector w, float B ){
        float sum = w.dot( w );
        if( sum > B ){
            w *= sqrtf( B / sum );
        }            
    }
    inline static void reg_L1( float &w, float wd ){
        if( w > wd ) w -= wd;
        else 
            if( w < -wd ) w += wd;
            else w = 0.0f;
    }    
public:
    Param param;
    inline void init( void ){
        g_bias.alloc_space( param.num_global );
        u_bias.alloc_space( param.num_user );
        i_bias.alloc_space( param.num_item );
        tmp_ufactor.alloc_space( param.num_factor );
        tmp_ifactor.alloc_space( param.num_factor );
        W_user.alloc_space( param.num_user, param.num_factor );
        W_item.alloc_space( param.num_item, param.num_factor );

        printf("num_user=%d, num_item=%d, num_global=%d\n", param.num_user, param.num_item, param.num_global );
        this->init_params();
    }    
    inline void init_params( void ){
        g_bias = 0.0f; u_bias = 0.0f; i_bias = 0.0f;
        W_user.randinit(); W_item.randinit();
    }
    inline void free_space(){
        g_bias.free_space(); u_bias.free_space(); i_bias.free_space();
        W_user.free_space(); W_item.free_space();
        tmp_ufactor.free_space(); tmp_ifactor.free_space();
    }        
    inline float pred( const Elem &feature ){ 
        double sum = param.base_score;
        {//bias
            for( int i = 0; i < feature.num_global; i ++ ){
                sum += feature.value_global[ i ] * g_bias[ feature.index_global[i] ];
            }
            
            for( int i = 0; i < feature.num_ufactor; i ++ ){
                sum += feature.value_ufactor[ i ] * u_bias[ feature.index_ufactor[i] ];
            }
             
            for( int i = 0; i < feature.num_ifactor; i ++ ){
                sum +=  feature.value_ifactor[i] * i_bias[ feature.index_ifactor[i] ];
            }
        }
        {// tmp factor
            tmp_ufactor = 0.0f;
            tmp_ifactor = 0.0f;
            for( int i = 0; i < feature.num_ufactor; i ++ ){
                const unsigned uid = feature.index_ufactor[i];
                tmp_ufactor.add( W_user[ uid ], feature.value_ufactor[i] );
            }            
            for( int i = 0; i < feature.num_ifactor; i ++ ){
                const unsigned iid = feature.index_ifactor[i];
                tmp_ifactor.add( W_item[ iid ], feature.value_ifactor[i] );
            }                        
        }        
        sum += tmp_ufactor.dot( tmp_ifactor );        
        return param.map_active( (float)sum ); 
    }    
    inline void update( const Elem &feature ){
        float err = param.cal_grad( feature.label, this->pred( feature ) );
        
        for( int i = 0; i < feature.num_global; i ++ ){
            const unsigned gid = feature.index_global[i];                
            g_bias[ gid ] += param.learning_rate * err * feature.value_global[i];
            if( gid >= (unsigned)param.num_gregfree ){
                if( param.reg_method == 0 ){
                    g_bias[ gid ] *= ( 1.0f - param.learning_rate * param.wd_gbias );
                }else{
                    reg_L1( g_bias[ gid ], param.learning_rate * param.wd_gbias );
                }
            }
        }        
        for( int i = 0; i < feature.num_ufactor; i ++ ){
            const unsigned uid = feature.index_ufactor[i];                
            float scale = param.learning_rate * err * feature.value_ufactor[i];
            W_user[ uid ].add( tmp_ifactor, scale );
            u_bias[ uid ] += scale;
            W_user[ uid ] *= ( 1.0f - param.learning_rate * param.wd_user );
            u_bias[ uid ] *= ( 1.0f - param.learning_rate * param.wd_ubias );
        }        
        for( int i = 0; i < feature.num_ifactor; i ++ ){
            const unsigned iid = feature.index_ifactor[i];
            float scale = param.learning_rate * err * feature.value_ifactor[i];
            W_item[ iid ].add( tmp_ufactor, scale );              
            i_bias[ iid ] += scale;
            W_item[ iid ] *= ( 1.0f - param.learning_rate * param.wd_item );       
            i_bias[ iid ] *= ( 1.0f - param.learning_rate * param.wd_ibias );            
        }
    }
}; 

struct TrainEntry{
    int locID;
    int materialID;
    int herb;
    int rm;
    unsigned year;
    float YGSMN;

    inline static int get_herb( const char *s_hb ){
        if( !strcmp( s_hb, "conv" ) ) return 0;
        if( !strcmp( s_hb, "RR1" ) )  return 1;        
        if( !strcmp( s_hb, "RR2Y" ) ) return 2;
        if( !strcmp( s_hb, "NULL" ) ) return 3;
        return 3;
    }
    inline static int get_rm( const char *s_rm ){
        if( !strcmp( s_rm, "NULL" ) ) return -1;
        return (int)( atof( s_rm ) * 10 );
    }
    inline void from_train( const char *s ){
        char s_hb[ 256 ], s_rm[ 256 ];
        sscanf( s, "%*d,%d,%*d,%d,%[^,],%f,%*[^,],%[^,],%u-%*d-%*d", &locID, &materialID, s_hb, &YGSMN, s_rm, &year );
        herb = get_herb( s_hb );
        rm = get_rm( s_rm );
        this->norm();
    }
    inline void from_query( const char *s ){
        char s_hb[ 256 ], s_rm[ 256 ];
        sscanf( s, "%d,%d,%[^,],%[^,],%u", &locID, &materialID, s_hb, s_rm, &year );
        herb = get_herb( s_hb );        
        rm   = get_rm( s_rm );
        this->norm();
    }
    inline void norm( void ){
        if( norm_year ){
            locID = (unsigned)locID * 6  + year - 2004;
        }
        assert_true( year >=2004 && year < 2010, "year range");
    }
};

class IFeatGen{
public:
    virtual int size( void ) const = 0;
    virtual int gen( vector<unsigned> &findex, vector<float> &fvalue, const TrainEntry &e, unsigned base = 0 ) = 0;
};

class MatrixElemCSR{
private:
    vector<float> row_label;
    vector<int>   row_ptr;
    vector<int>   reindex;
    vector<unsigned> findex;
    vector<float>    fvalue;
public:
    unsigned gsize, usize, isize;
public:
    MatrixElemCSR(){
        this->clear();
    }
    inline void clear(){
        row_label.clear();
        row_ptr.clear(), row_ptr.push_back( 0 );
        findex.clear();
        fvalue.clear();
        reindex.clear();
    }
    inline int num_row(){
        return (int)row_label.size();
    }
    inline void load( vector<IFeatGen*> &ggen,
                      vector<IFeatGen*> &ugen, 
                      vector<IFeatGen*> &igen, 
                      const vector<TrainEntry> &data ){
        for( size_t i = 0; i < data.size(); i ++ ){
            usize = gsize = isize = 0;
            int ng = 0, nu = 0, ni = 0;
            for( unsigned j = 0; j < ggen.size(); j ++ ){                
                ng += ggen[j]->gen( findex, fvalue, data[i], gsize );
                gsize += ggen[j]->size();
            }
            row_ptr.push_back( row_ptr.back() + ng );
            for( unsigned j = 0; j < ugen.size(); j ++ ){                
                nu += ugen[j]->gen( findex, fvalue, data[i], usize );
                usize += ugen[j]->size();
            }
            row_ptr.push_back( row_ptr.back() + nu );            
            for( unsigned j = 0; j < igen.size(); j ++ ){                
                ni += igen[j]->gen( findex, fvalue, data[i], isize );
                isize += igen[j]->size();
            }
            row_ptr.push_back( row_ptr.back() + ni );
            row_label.push_back( data[i].YGSMN / scale_score );
            reindex.push_back( (int)i );
        }
    }
    inline void shuffle( size_t sz, size_t start = 0 ){
        rnd::shuffle( &reindex[start], sz );
    }
    inline void shuffle(){
        this->shuffle( reindex.size() );
    }
    inline Elem operator[]( int r ){
        r = reindex[ r ];
        Elem e;
        e.label = row_label[ r ];
        e.num_global   = row_ptr[ r * 3 + 1 ] - row_ptr[ r * 3 + 0 ];
        e.num_ufactor  = row_ptr[ r * 3 + 2 ] - row_ptr[ r * 3 + 1 ];
        e.num_ifactor  = row_ptr[ r * 3 + 3 ] - row_ptr[ r * 3 + 2 ];            
        e.set_space( &findex[ row_ptr[ r * 3 ] ], &fvalue[ row_ptr[ r * 3 ] ] );
        return e;
    }
};

// feature generators
namespace feat{
    // material ID
    struct MID : public IFeatGen{
    private:
        int num_mat;
        int scale;
    public:
        inline void init( int num_mat, int scale = 1 ){
            this->num_mat = num_mat;
            this->scale   = scale;
        }
        virtual int size( void ) const{
            return num_mat * scale;
        }
        virtual int gen( vector<unsigned> &findex, vector<float> &fvalue, const TrainEntry &e, unsigned base ){
            int mid = e.materialID;
            if( scale == 6 ) mid = mid * 6 + e.year - 2004; 
            findex.push_back( base + mid );
            fvalue.push_back( 1.0f );
            return 1;
        }
    };
    // location ID
    struct LID : public IFeatGen{
    private:
        int num_loc;
    public:
        inline void init( int num_loc ){
            this->num_loc = num_loc;
        }
        virtual int size( void ) const{
            return num_loc;
        }
        virtual int gen( vector<unsigned> &findex, vector<float> &fvalue, const TrainEntry &e, unsigned base ){
            findex.push_back( base + e.locID );
            fvalue.push_back( 1.0f );
            return 1;
        }
    };
    struct LLID : public IFeatGen{
    private:
        int num_loc;
    public:
        inline void init( int num_loc ){
            this->num_loc = num_loc;
        }
        virtual int size( void ) const{
            return num_loc * 6 ;
        }
        virtual int gen( vector<unsigned> &findex, vector<float> &fvalue, const TrainEntry &e, unsigned base ){            
            assert_true( e.year >= 2004 && e.year < 2010, "year");
            findex.push_back( base + e.locID * 6 + e.year - 2004 );
            fvalue.push_back( 1.0f );
            return 1;
        }
    };
    // herb location
    struct HerbLoc: public IFeatGen{
    private:
        int mode;
        int scale;
        int num_loc;
    public:
        inline void init( int num_loc, int mode = 3, int scale =1 ){
            this->num_loc = num_loc;
            this->mode = mode;
            this->scale= 1;
        }
        virtual int size( void ) const{
            return num_loc * mode * scale;
        }
        virtual int gen( vector<unsigned> &findex, vector<float> &fvalue, const TrainEntry &e, unsigned base ){
            if( e.herb < mode ) {
                int lid = e.locID;
                if( scale == 6 ){
                    lid = lid * 6 + e.year - 2004;
                }
                findex.push_back( lid * mode + e.herb + base );
                fvalue.push_back( 1.0f );
                return 1;
            }else{
                return 0;
            }
        }
    };    

    // herb location
    struct RMLoc: public IFeatGen{
    private:
        int mode;
        int scale;
        int num_loc;
        const static double mean = 32.7;
        const static double svar = 25.5;
    public:
        inline void init( int num_loc, int mode = 1, int scale = 1 ){
            this->num_loc = num_loc;
            this->mode    = mode;
            this->scale   = scale;
        }
        virtual int size( void ) const{
            return num_loc * mode * scale;
        }
        virtual int gen( vector<unsigned> &findex, vector<float> &fvalue, const TrainEntry &e, unsigned base ){
            if( e.rm >= 0 ) {
                int lid = e.locID;
                if( scale == 6 ) {
                    lid = lid * 6 + e.year - 2004;
                }
                findex.push_back( lid * mode + base );
                fvalue.push_back( (e.rm - mean) / svar );
                if( mode >= 2 ){
                    findex.push_back( lid * mode + base + 1 );
                    float s = (e.rm-mean) / svar;
                    fvalue.push_back( s*s );
                }
                return mode;
            }else{
                return 0;
            }
        }
    };
    struct RMID: public IFeatGen{
    private:
    public:
        virtual int size( void ) const{
            return 100;
        }
        virtual int gen( vector<unsigned> &findex, vector<float> &fvalue, const TrainEntry &e, unsigned base ){
            if( e.rm >= 0 ) {
                findex.push_back( e.rm + base );
                fvalue.push_back( 1.0 );
                return 1;
            }else{
                return 0;
            }
        }
    };    
    // herb
    struct Herb: public IFeatGen{
    public:
        virtual int size( void ) const{
            return 3;
        }
        virtual int gen( vector<unsigned> &findex, vector<float> &fvalue, const TrainEntry &e, unsigned base ){
            if( e.herb < 3 ) {
                findex.push_back( e.herb + base );
                fvalue.push_back( 1.0f );
                return 1;
            }else{
                return 0;
            }
        }        
    };
    
    // location ID, NN by cosine
    struct LocNN : public IFeatGen{
    private:
        struct Entry{
            float score;
            int lid, mid;
            inline bool operator<( const Entry &p )const{
                if( lid < p.lid ) return true;
                if( lid > p.lid ) return false;
                return mid < p.mid;
            }
        };
        vector<int>    cnt_mat;
        vector<double> mean_mat;
        vector<float>  tmp_score;
        vector<bool>   tmp_flag;        
        vector<Entry>  data;
        int num_loc;
        int swap_pos;
    private:       
        double scale;
        int top_k, use_imfb, num_knn;
        vector<int> knninfo;
    public:
        inline void calc_NN( int from_lid ){
            vector< pair< float, int> > ans;
            for( size_t i = 0; i < data.size(); ){
                size_t top = i;
                double sum = 0.0f, wsum = 4.0;
                while( top < data.size() && data[ top ].lid == data[ i ].lid ){
                    double val = data[ top ].score - mean_mat[ data[top].mid ];
                    if( tmp_flag[ data[ top ].mid ] ){
                        sum += tmp_score[ data[ top ].mid ] * val; 
                        wsum += val * val;
                    }     
                    top ++;
                }
                if( data[i].lid != from_lid ){
                    float sc = sum / sqrt(wsum);
                    ans.push_back( make_pair( - sc, data[i].lid ) );
                }
                i = top;
            }
            sort( ans.begin(), ans.end() );
            
            for( int i = 0; i < top_k; i ++ ){
                if( ans[i].first < 0.0 ){
                    knninfo[ from_lid * top_k + i ] = ans[i].second;
                    num_knn ++;
                }else{
                    knninfo[ from_lid * top_k + i ] = -1;
                }
            }
        }
        inline void init( vector<TrainEntry> &train, int num_loc, int num_mat, double avg_mean, int top_k, double scale, int use_imfb = 0, int swap_pos = 0 ){
            this->swap_pos = swap_pos;
            if( swap_pos != 0 ) rnd::exchange( num_loc, num_mat );
            this->num_loc = num_loc;
            this->top_k = top_k;
            this->scale = scale;
            this->use_imfb = use_imfb;
            this->num_knn  = 0;
            data.clear();
            knninfo.resize( top_k * num_loc );
            cnt_mat.resize( num_mat );
            mean_mat.resize( num_mat );
            tmp_flag.resize( num_mat );
            tmp_score.resize( num_mat );
            fill( cnt_mat.begin(), cnt_mat.end(), 0 );
            fill( mean_mat.begin(), mean_mat.end(), 0.0 );
            fill( tmp_flag.begin(), tmp_flag.end(), false );
            fill( tmp_score.begin(), tmp_score.end(), false );

            for( size_t i = 0; i < train.size(); i ++ ){
                Entry e;
                if( swap_pos == 0 ){
                    e.lid = train[i].locID; e.mid = train[i].materialID;
                }else{
                    e.lid = train[i].materialID; e.mid = train[i].locID;
                }                
                e.score = train[i].YGSMN;
                cnt_mat[ e.mid ] ++;
                mean_mat[ e.mid ] += e.score;
                data.push_back( e );
            }

            for( size_t i = 0; i < mean_mat.size(); i ++ ){
                mean_mat[ i ] = (mean_mat[i] + avg_mean) / (cnt_mat[i]+1);
            }
            {// start calc NN
                sort( data.begin(), data.end() );
                for( size_t i = 0; i < data.size(); ){
                    size_t top = i + 1;
                    while( top < data.size() && data[top].lid == data[i].lid ) top ++;
                    for( size_t j = i; j < top; j ++ ){
                        tmp_flag [ data[j].mid ] = true;
                        tmp_score[ data[j].mid ] = data[j].score - mean_mat[ data[j].mid ]; 
                    }
                    this->calc_NN( data[i].lid );
                    for( size_t j = i; j < top; j ++ ){
                        tmp_flag [ data[j].mid ] = false;
                    }
                    i = top;
                }
            }
            if( true ){ 
                printf("knn init end:avg_knn=%lf\n", (double)num_knn / num_loc ); 
            }
        }
        
        virtual int size( void ) const{
            if( use_imfb != 0 ) {
                return num_loc * top_k * 2;
            }else{
                return num_loc * top_k ;
            }
        }
        virtual int gen( vector<unsigned> &findex, vector<float> &fvalue, const TrainEntry &e, unsigned base ){
            int cnt = 0;
            int locID = e.locID;
            Entry ef;
            ef.mid = e.materialID;

            if( swap_pos != 0 ){
                ef.mid = e.locID;
                locID = e.materialID;
            }

            for( int i = 0; i < top_k ; i ++ ){
                ef.lid = knninfo[ locID * top_k + i ];
                if( ef.lid < 0 ) break;
                size_t j = lower_bound( data.begin(), data.end(), ef ) - data.begin();
                if( j >= data.size() || data[j].lid != ef.lid || data[j].mid != ef.mid ) continue;                

                findex.push_back( locID * top_k + i + base );
                fvalue.push_back( (data[j].score - mean_mat[ data[j].mid ]) / 10.0 );
                if( use_imfb != 0 ){
                    findex.push_back( locID * top_k + i + base + num_loc * top_k );
                    fvalue.push_back( 1.0 );
                }
                cnt ++;
            }

            int num = use_imfb == 0 ? cnt: cnt * 2;
            if( cnt > 0 ){
                float inv = 1.0f / sqrt( cnt );
                for( int i = 0; i < num; i ++ ){
                    fvalue[ fvalue.size()-i-1 ] *= inv;
                }
            }
            return num;
        }
    };    
};

using namespace feat;

// simple implementation
class YieldPredictor{
private:
    // trainer
    SVDTrainer trainer;
    // feature generator
    vector<IFeatGen*>  ugen, igen, ggen;    
    // number of key instances
    int num_core_instance;
    // average of scorea
    double avg_score, avg_score_all;
    // feature format data
    MatrixElemCSR mtrain, mquery;
private:
    inline void remap_index( vector<int> &mindex,
                             vector<int> &lindex,
                             vector<TrainEntry> &train, 
                            vector<TrainEntry> &query ){
        {
            for( size_t i = 0; i < train.size(); i ++ ){
                mindex.push_back( train[i].materialID );
            }
            for( size_t i = 0; i < query.size(); i ++ ){
                mindex.push_back( query[i].materialID );
            }
            sort( mindex.begin(), mindex.end() );
            mindex.resize( unique( mindex.begin(), mindex.end() ) - mindex.begin() );
            for( size_t i = 0; i < train.size(); i ++ ){
                train[i].materialID = lower_bound( mindex.begin(), mindex.end(), train[i].materialID ) - mindex.begin();
            }
            for( size_t i = 0; i < query.size(); i ++ ){
                query[i].materialID = lower_bound( mindex.begin(), mindex.end(), query[i].materialID ) - mindex.begin();
            }
        }        
        {
            for( size_t i = 0; i < train.size(); i ++ ){
                lindex.push_back( train[i].locID );
            }
            for( size_t i = 0; i < query.size(); i ++ ){
                lindex.push_back( query[i].locID );
            }
            sort( lindex.begin(), lindex.end() );
            lindex.resize( unique( lindex.begin(), lindex.end() ) - lindex.begin() );
            for( size_t i = 0; i < train.size(); i ++ ){
                train[i].locID =  lower_bound( lindex.begin(), lindex.end(), train[i].locID ) - lindex.begin();
            }
            for( size_t i = 0; i < query.size(); i ++ ){
                query[i].locID =  lower_bound( lindex.begin(), lindex.end(), query[i].locID ) - lindex.begin();
            }            
        }
    }    
private:
    MID gMID, gMIDY;
    LID gLID;
    LLID gLLID;
    RMLoc  gRMLoc;
    HerbLoc  gHerbLoc;
    RMID   gRMID;
    Herb    gHerb;
    LocNN   gLocNN, gMatNN;
    // key----------------------------------------------
    inline void init_gens( vector<TrainEntry> &train, 
                           vector<TrainEntry> &query,
                           vector<string> &droughtMonitor, 
                           vector<string> &droughtNOAA, 
                           vector<string> &locations, 
                           vector<int> &varieties ){
        vector<int> mindex, lindex;
        this->remap_index( mindex, lindex, train, query );        
        ugen.clear(); igen.clear(); ggen.clear();        
        // initialization
        gMID.init( mindex.size() );
        gMIDY.init( mindex.size(), 6 );
        gLID.init( lindex.size() );
        gLLID.init( lindex.size() );
        gHerbLoc.init( lindex.size(), 3, 6 );
        gRMLoc.init( lindex.size(), 2, 6 );
        // 20 nn
        //gLocNN.init( train, lindex.size(), mindex.size(), avg_score, 30, 10.0, 1, 1 );
        //gMatNN.init( train, lindex.size(), mindex.size(), avg_score, 30, 10.0, 1, 0 );
        // configuration
        ugen.push_back( &gMID );
        igen.push_back( &gLLID );
        igen.push_back( &gLID );
        igen.push_back( &gRMLoc );
        //igen.push_back( &gHerbLoc );
        //ggen.push_back( &gMIDY );
        //ggen.push_back( &gMatNN );
        //ggen.push_back( &gHerb );
    }
    inline void init_trainer( void ){
        Param &p = trainer.param;
        p.num_factor = 64;
        p.num_user = mtrain.usize;
        p.num_item = mtrain.isize;
        p.num_global= mtrain.gsize;
        p.active_type = 2;
        p.learning_rate = 0.02f;
        p.wd_item = 0.0005f;
        p.wd_user = p.wd_item;       
        p.reg_method = 0;
        p.num_round =  -60;
        //if( ggen.size() > 0 ) p.num_gregfree = ggen[0]->size();
        p.wd_gbias = 0.001f;
        p.set_base( avg_score / scale_score );
        trainer.init();
    }
    inline void clear_all( void ){
        trainer.free_space();
        mtrain.clear(); mquery.clear();
    }
private:
    // do cross validation
    inline int do_nfold( void ){
        mtrain.shuffle( num_core_instance );
        //int top = mtrain.num_row() * (nfold-1) / nfold;
        int start = ntest;
        int top   = num_core_instance;
        if( use_all_instance ){
            mtrain.shuffle( mtrain.num_row() - start, start );
            top = mtrain.num_row();
        }
        if( trainer.param.num_round > 0 ) return trainer.param.num_round;
        if( trainer.param.num_round < 0 ) trainer.param.num_round = -trainer.param.num_round;
        if( !silent ) {
            printf("%d/%d=%lf\n", ntest, top, (double)top/ntest );
        }
        double last_rmse, curr_rmse = 150.0;
        int nround = 0;
        do{
            nround ++;
            last_rmse = curr_rmse;
            // run training 
            for( int i = start; i < top; i ++ ){
                trainer.update( mtrain[i] );
            }
            curr_rmse = 0.0;
            for( int i = 0; i < start; i ++ ){
                Elem e = mtrain[i];
                curr_rmse += sqrs( e.label - trainer.pred( e ) );
            }
            curr_rmse = sqrt( curr_rmse / ( start ) );
            if( !silent ){
                printf("rmse=%lf, nround=%d, metric=%lf\n", curr_rmse * scale_score, nround, get_metric( curr_rmse * scale_score ) );
            }
        }while( (curr_rmse < last_rmse && nround < trainer.param.max_round) || nround < trainer.param.num_round  );
        if( true ){
            printf("nfold:rmse=%lf, nround=%d, metric=%lf\n", last_rmse * scale_score, nround, get_metric( last_rmse * scale_score ) );        
        }
        if( nround < 60 ) nround = 60;
        return nround - 1;
    }
    // run training
    inline void do_train( void ){
        int nround = this->do_nfold();
        int top = num_core_instance;
        if( use_all_instance ){
            mtrain.shuffle(); top = mtrain.num_row();
        }
        trainer.init_params();
        for( int itr = 0; itr < nround; itr ++ ){
            for( int i = 0; i < top; i ++ ){
                trainer.update( mtrain[i] );
            }
        }
    }
public:
    YieldPredictor( void ){      
        srand( 100 ); 
    }
    vector<double> predictYield( vector <string> trainingData, 
                                 vector <string> droughtMonitor, 
                                 vector <string> droughtNOAA, 
                                 vector <string> locations, 
                                 vector <string> varieties, 
                                 vector <string> queries ){
        {// clear all
            this->clear_all();
        }
        {// fetch varieties
            vector<int> var_index;
            for( size_t i = 0; i < varieties.size(); i ++ ){
                var_index.push_back( atoi( varieties[i].c_str() ) );
            }
            sort( var_index.begin(), var_index.end() );

            // load necessary data
            double sum = 0.0, sum_other = 0.0, max_score = 0.0, min_score = 150.0;
            TrainEntry e;
            vector<TrainEntry> train, query, train_other;
            for( size_t i = 0; i < trainingData.size(); i ++ ){
                e.from_train( trainingData[i].c_str() );
                size_t idx = lower_bound( var_index.begin(), var_index.end(), e.materialID ) - var_index.begin();
                if( idx < var_index.size() && var_index[idx] == e.materialID ){
                    train.push_back( e );
                    sum += e.YGSMN;
                }else{
                    train_other.push_back( e );
                    sum_other += e.YGSMN;
                }
                if( max_score < e.YGSMN ) max_score = e.YGSMN; 
                if( min_score > e.YGSMN ) min_score = e.YGSMN;
            }
            {
                printf("trainingData.size()=%d/%d=%lf\n",(int)train.size(), (int)trainingData.size(), (double)train.size()/trainingData.size() );            
                this->avg_score = sum / train.size();
                this->avg_score_all = (sum+sum_other) / trainingData.size();
                this->num_core_instance = (int)train.size();
                if( use_all_instance ){
                    for( size_t j = 0; j < train_other.size(); j ++ ){
                        train.push_back( train_other[j] );
                    }
                }
                train_other.clear();
            }
            if( max_score > 150.0 ) scale_score = max_score + 1.0;
            if( true ){
                printf("avg_score=%lf, max_score=%lf, min_score=%lf, avg_all=%lf\n", avg_score, max_score, min_score, avg_score_all );
            }                          
            
            for( size_t i = 0; i < queries.size(); i ++ ){
                e.from_query( queries[i].c_str() );
                query.push_back( e );
            }
            // init generators
            this->init_gens( train, query, droughtMonitor, droughtNOAA, locations, var_index );
            // load data
            mtrain.load( ggen, ugen, igen, train ); 
            mquery.load( ggen, ugen, igen, query );
            // init trainer
            this->init_trainer();
            // do training
            this->do_train();
        }
        {// prepare return
            vector<double> ret;
            for( int i = 0; i < mquery.num_row(); i ++ ){
                ret.push_back( trainer.pred( mquery[i] ) * scale_score );
            }
            return ret;
        }
    }
};