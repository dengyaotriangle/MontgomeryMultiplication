#include<bits/stdc++.h>
using namespace std;
//dengyaotriangle!

//# 30 31 62 63
template<typename T,typename UT> class montctx_t{
private:
    typedef T val_t;
    typedef UT mval_t;
    static const int tlen=sizeof(val_t)*8;
public:
    val_t mdn,mdn2,p2,r;
    montctx_t(val_t x):mdn(x),mdn2(x<<1),p2(-mval_t(mdn)%mdn),r(1){
        for(int i=1;i<tlen;i<<=1)r*=2+r*mdn;
    }
    inline val_t redc(mval_t x)const{return (x+(val_t(x)*r)*mval_t(mdn))>>tlen;}
    inline val_t redu(val_t x)const{return x>=mdn2?x-mdn2:x;}
    inline val_t reds(val_t x)const{return x>=mdn?x-mdn:x;}
};
//# 30 31
typedef montctx_t<uint32_t,uint64_t> montctx32_t;
//# 62 63
typedef montctx_t<uint64_t,unsigned __int128> montctx64_t;
//# 30 62
template<typename T,typename UT> class mont_t{
private:
    typedef T val_t;
    typedef UT mval_t;
    static montctx_t<T,UT> ctx;
    val_t v;
public:
    static montctx_t<T,UT> getctx(){return ctx;}
    static void setctx(const montctx_t<T,UT>&x){ctx=x;}
    
    explicit operator val_t()const{return ctx.reds(ctx.redc(v));}
    mont_t(val_t x){v=ctx.redc(x*(mval_t)ctx.p2);}
    mont_t(){}
    mont_t(const mont_t&a):v(a.v){}
    mont_t&operator+=(const mont_t&a){v=ctx.redu(v+a.v);return*this;}
    mont_t&operator-=(const mont_t&a){v=ctx.redu(v-a.v+ctx.mdn2);return*this;}
    mont_t&operator*=(const mont_t&a){v=ctx.redc(v*(mval_t)a.v);return*this;}
    mont_t&operator=(const mont_t&a){v=a.v;return*this;}
    mont_t operator+(const mont_t&a)const{return mont_t(*this)+=a;}
    mont_t operator-(const mont_t&a)const{return mont_t(*this)-=a;}
    mont_t operator*(const mont_t&a)const{return mont_t(*this)*=a;}
    mont_t operator-()const{mont_t r;r.v=(v?ctx.mdn2-v:0);return r;}
    bool operator==(const mont_t&a)const{return ctx.reds(v)==ctx.reds(a.v);}
    bool operator!=(const mont_t&a)const{return !(*this==a);}
    friend std::istream&operator>>(std::istream&s,mont_t&v){val_t tmp;s>>tmp;v=mont_t(tmp);return s;}
    friend std::ostream&operator<<(std::ostream&s,const mont_t&v){return s<<val_t(v);}
};
//# 30
typedef mont_t<uint32_t,uint64_t> mont30_t;
template<> montctx32_t mont30_t::ctx=montctx32_t(998244353);
//# 62
typedef mont_t<uint64_t,unsigned __int128> mont62_t;
template<> montctx64_t mont62_t::ctx=montctx64_t(998244353);
//# 31 63
template<typename T,typename UT> class mont_e_t{
private:
    typedef T val_t;
    typedef UT mval_t;
    static montctx_t<T,UT> ctx;
    val_t v;
public:
    static montctx_t<T,UT> getctx(){return ctx;}
    static void setctx(const montctx_t<T,UT>&x){ctx=x;}
    
    explicit operator val_t()const{return ctx.reds(ctx.redc(v));}
    mont_e_t(val_t x){v=ctx.reds(ctx.redc(x*(mval_t)ctx.p2));}
    mont_e_t(){}
    mont_e_t(const mont_e_t&a):v(a.v){}
    mont_e_t&operator+=(const mont_e_t&a){v=ctx.reds(v+a.v);return*this;}
    mont_e_t&operator-=(const mont_e_t&a){v=ctx.reds(v-a.v+ctx.mdn);return*this;}
    mont_e_t&operator*=(const mont_e_t&a){v=ctx.reds(ctx.redc(v*(mval_t)a.v));return*this;}
    mont_e_t&operator=(const mont_e_t&a){v=a.v;return*this;}
    mont_e_t operator+(const mont_e_t&a)const{return mont_e_t(*this)+=a;}
    mont_e_t operator-(const mont_e_t&a)const{return mont_e_t(*this)-=a;}
    mont_e_t operator*(const mont_e_t&a)const{return mont_e_t(*this)*=a;}
    mont_e_t operator-()const{mont_e_t r;r.v=(v?ctx.mdn-v:0);return r;}
    bool operator==(const mont_e_t&a)const{return v==a.v;}
    bool operator!=(const mont_e_t&a)const{return !(*this==a);}
    friend std::istream&operator>>(std::istream&s,mont_e_t&v){val_t tmp;s>>tmp;v=mont_e_t(tmp);return s;}
    friend std::ostream&operator<<(std::ostream&s,const mont_e_t&v){return s<<val_t(v);}
};
//# 31
typedef mont_e_t<uint32_t,uint64_t> mont31_t;
template<> montctx32_t mont31_t::ctx=montctx32_t(998244353);
//# 63
typedef mont_e_t<uint64_t,unsigned __int128> mont63_t;
template<> montctx64_t mont63_t::ctx=montctx64_t(998244353);
//#

mt19937 rng,trng;
template<typename t> t rndi(t l,t r){return uniform_int_distribution<t>(l,r)(rng);}

const int t=1000;
const int u=1e6;

const int mdn=1e9+7;

int main(){
    int seed;
    cin>>seed;
    trng=mt19937(seed);
    {   
        long long t0=chrono::steady_clock().now().time_since_epoch().count();
        int z=1;
        for(int i=1;i<t*u;i++){
            z=z*(unsigned long long)i%mdn;
        }
        long long t1=chrono::steady_clock().now().time_since_epoch().count();
        cout<<z<<' '<<(t1-t0)/1e9<<endl;
    }
    {   
        long long t0=chrono::steady_clock().now().time_since_epoch().count();
        int chk=0;
        rng=trng;
        for(int i=0;i<t;i++){
            int mdn=rndi(1ll,(1ll<<29)-1)*2+1;
            mont30_t::setctx(montctx32_t(mdn));
            mont30_t a(1),ret(1),v1(1);
            for(int i=0;i<u;i++){
                a*=ret;ret=ret+v1;
            }
            chk^=uint32_t(a);
        }
        long long t1=chrono::steady_clock().now().time_since_epoch().count();
        cout<<chk<<' '<<(t1-t0)/1e9<<endl;
    }
    {   
        long long t0=chrono::steady_clock().now().time_since_epoch().count();
        int chk=0;
        rng=trng;
        for(int i=0;i<t;i++){
            uint32_t mdn=rndi(1ll,(1ll<<29)-1)*2+1;
            uint32_t a=1,ret=1;
            for(int i=0;i<u;i++){
                a=a*(unsigned long long)ret%mdn;ret++;
            }
            chk^=uint32_t(a);
        }
        long long t1=chrono::steady_clock().now().time_since_epoch().count();
        cout<<chk<<' '<<(t1-t0)/1e9<<endl;
    }

    {   
        long long t0=chrono::steady_clock().now().time_since_epoch().count();
        int chk=0;
        rng=trng;
        for(int i=0;i<t;i++){
            int mdn=rndi(1ll,(1ll<<30)-1)*2+1;
            mont31_t::setctx(montctx32_t(mdn));
            mont31_t a(1),ret(1);
            for(int i=0;i<u;i++){
                a*=ret;ret=ret+1;
            }
            chk^=uint32_t(a);
        }
        long long t1=chrono::steady_clock().now().time_since_epoch().count();
        cout<<chk<<' '<<(t1-t0)/1e9<<endl;
    }
    return 0;
    {   
        long long t0=chrono::steady_clock().now().time_since_epoch().count();
        int chk=0;
        rng=trng;
        for(int i=0;i<t;i++){
            uint32_t mdn=rndi(1ll,(1ll<<30)-1)*2+1;
            uint32_t a=1,ret=1;
            for(int i=0;i<u;i++){
                a=a*(unsigned long long)ret%mdn;ret++;
            }
            chk^=uint32_t(a);
        }
        long long t1=chrono::steady_clock().now().time_since_epoch().count();
        cout<<chk<<' '<<(t1-t0)/1e9<<endl;
    }

    {   
        long long t0=chrono::steady_clock().now().time_since_epoch().count();
        long long chk=0;
        rng=trng;
        for(int i=0;i<t;i++){
            long long mdn=rndi(1ll,(1ll<<61)-1)*2+1;
            mont62_t::setctx(montctx64_t(mdn));
            mont62_t a(1),ret(1);
            for(int i=0;i<u;i++){
                a*=ret;ret=ret+1;
            }
            chk^=uint64_t(a);
        }
        long long t1=chrono::steady_clock().now().time_since_epoch().count();
        cout<<chk<<' '<<(t1-t0)/1e9<<endl;
    }
    {   
        long long t0=chrono::steady_clock().now().time_since_epoch().count();
        long long chk=0;
        rng=trng;
        for(int i=0;i<t;i++){
            uint64_t mdn=rndi(1ll,(1ll<<61)-1)*2+1;
            uint64_t a=1,ret=1;
            for(int i=0;i<u;i++){
                a=a*(unsigned __int128)ret%mdn;ret++;
            }
            chk^=uint64_t(a);
        }
        long long t1=chrono::steady_clock().now().time_since_epoch().count();
        cout<<chk<<' '<<(t1-t0)/1e9<<endl;
    }


    {   
        long long t0=chrono::steady_clock().now().time_since_epoch().count();
        long long chk=0;
        rng=trng;
        for(int i=0;i<t;i++){
            long long mdn=rndi(1ll,(1ll<<62)-1)*2+1;
            mont63_t::setctx(montctx64_t(mdn));
            mont63_t a(1),ret(1);
            for(int i=0;i<u;i++){
                a*=ret;ret=ret+1;
            }
            chk^=uint64_t(a);
        }
        long long t1=chrono::steady_clock().now().time_since_epoch().count();
        cout<<chk<<' '<<(t1-t0)/1e9<<endl;
    }
    {   
        long long t0=chrono::steady_clock().now().time_since_epoch().count();
        long long chk=0;
        rng=trng;
        for(int i=0;i<t;i++){
            uint64_t mdn=rndi(1ll,(1ll<<62)-1)*2+1;
            uint64_t a=1,ret=1;
            for(int i=0;i<u;i++){
                a=a*(unsigned __int128)ret%mdn;ret++;
            }
            chk^=uint64_t(a);
        }
        long long t1=chrono::steady_clock().now().time_since_epoch().count();
        cout<<chk<<' '<<(t1-t0)/1e9<<endl;
    }
    return 0;
}