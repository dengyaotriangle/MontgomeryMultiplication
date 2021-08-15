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
typedef montctx_t<uint32_t,uint64_t> montctx32_t;
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
typedef mont_e_t<uint32_t,uint64_t> mont31_t;
template<> montctx32_t mont31_t::ctx=montctx32_t(998244353);
