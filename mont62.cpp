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
typedef montctx_t<uint64_t,unsigned __int128> montctx64_t;
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
typedef mont_t<uint64_t,unsigned __int128> mont62_t;
template<> montctx64_t mont62_t::ctx=montctx64_t(998244353);
