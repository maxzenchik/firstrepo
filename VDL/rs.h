
#ifndef _EZPWD_RS
#define _EZPWD_RS

#include <algorithm>
#include <vector>
#include <type_traits>
#include <cstdint>
#include <cstring>
#include <string>
#include <iostream>
//#include <array>

#include "ezpwd/output"	// ezpwd::hex... std::ostream shims for outputting containers of uint8_t data

namespace ezpwd {


    class reed_solomon_base {
    public:
	virtual size_t		datum()		const = 0;	// a data element's bits
	virtual size_t		symbol()	const = 0;	// a symbol's bits
	virtual int		size()		const = 0;	// R-S block size (maximum total symbols)
	virtual int		nroots()	const = 0;	// R-S roots (parity symbols)
	virtual	int		load()		const = 0;	// R-S net payload (data symbols)

	virtual		       ~reed_solomon_base()
	{
	    ;
	}
				reed_solomon_base()
	{
	    ;
	}

	void			encode(
				    std::string	       &data )
	    const
	{
	    typedef uint8_t	uT;
	    typedef std::pair<uT *, uT *>
				uTpair;
	    data.resize( data.size() + nroots() );
        encode( uTpair( (uT *)&data[0], (uT *)&(data[0]) + data.size() ));
	}

	void			encode(
				    const std::string  &data,
				    std::string	       &parity )
	    const
	{
	    typedef uint8_t	uT;
	    typedef std::pair<const uT *, const uT *>
				cuTpair;
	    typedef std::pair<uT *, uT *>
				uTpair;
	    parity.resize( nroots() );
        encode( cuTpair( (const uT *)&(*data.begin()), (const uT *)&(*data.begin()) + data.size() ),
            uTpair( (uT *)&(*parity.begin()), (uT *)&(*parity.begin()) + parity.size() ));
	}

	template < typename T >
	void			encode(
				    std::vector<T>     &data )
	    const
	{
	    typedef typename std::make_unsigned<T>::type
				uT;
	    typedef std::pair<uT *, uT *>
				uTpair;
	    data.resize( data.size() + nroots() );
        encode( uTpair( (uT *)&(*data.begin()), (uT *)&(*data.begin()) + data.size() ));
	}
	template < typename T >
	void			encode(
				    const std::vector<T>&data,
				    std::vector<T>     &parity )
	    const
	{
	    typedef typename std::make_unsigned<T>::type
				uT;
	    typedef std::pair<const uT *, const uT *>
				cuTpair;
	    typedef std::pair<uT *, uT *>
				uTpair;
	    parity.resize( nroots() );
        encode( cuTpair( (uT *)&(*data.begin()), (uT *)&(*data.begin()) + data.size() ),
            uTpair( (uT *)&(*parity.begin()), (uT *)&(*parity.begin()) + parity.size() ));
	}

	template < typename T, size_t N >
	void			encode(
				    std::array<T,N>    &data,
				    int			pad	= 0 ) // ignore 'pad' symbols at start of array
	    const
	{
	    typedef typename std::make_unsigned<T>::type
				uT;
	    typedef std::pair<uT *, uT *>
				uTpair;
        encode( uTpair( (uT *)&(*data.begin()) + pad, (uT *)&(*data.begin()) + data.size() ));
	}

	virtual void		encode(
				    const std::pair<uint8_t *, uint8_t *>
						       &data )
	    const
	= 0;
	virtual void		encode(
				    const std::pair<const uint8_t *, const uint8_t *>
						       &data,
				    const std::pair<uint8_t *, uint8_t *>
						       &parity )
	    const
	= 0;
	virtual void		encode(
				    const std::pair<uint16_t *, uint16_t *>
						       &data )
	    const
	= 0;
	virtual void		encode(
				    const std::pair<const uint16_t *, const uint16_t *>
						       &data,
				    const std::pair<uint16_t *, uint16_t *>
						       &parity )
	    const
	= 0;
	virtual void		encode(
				    const std::pair<uint32_t *, uint32_t *>
						       &data )
	    const
	= 0;
	virtual void		encode(
				    const std::pair<const uint32_t *, const uint32_t *>
						       &data,
				    const std::pair<uint32_t *, uint32_t *>
						       &parity )
	    const
	= 0;

	int			decode(
				    std::string	       &data,
				    const std::vector<int>
				    		       &erasure	= std::vector<int>(),
				    std::vector<int>   *position= 0 )
	    const
	{
	    typedef uint8_t	uT;
	    typedef std::pair<uT *, uT *>
				uTpair;
        return decode( uTpair( (uT *)&(*data.begin()), (uT *)&(*data.begin()) + data.size() ),
			   erasure, position );
	}

	int			decode(
				    std::string	       &data,
				    std::string	       &parity,
				    const std::vector<int>
				    		       &erasure	= std::vector<int>(),
				    std::vector<int>   *position= 0 )
	    const
	{
	    typedef uint8_t	uT;
	    typedef std::pair<uT *, uT *>
				uTpair;
        return decode( uTpair( (uT *)&(*data.begin()), (uT *)&(*data.begin()) + data.size() ),
               uTpair( (uT *)&(*parity.begin()), (uT *)&(*parity.begin()) + parity.size() ),
			   erasure, position );
	}

	template < typename T >
	int			decode(
				    std::vector<T>     &data,
				    const std::vector<int>
				    		       &erasure	= std::vector<int>(),
				    std::vector<int>   *position= 0 )
	    const
	{
	    typedef typename std::make_unsigned<T>::type
				uT;
	    typedef std::pair<uT *, uT *>
				uTpair;
        return decode( uTpair( (uT *)&(*data.begin()), (uT *)&(*data.begin()) + data.size() ),
			   erasure, position );
	}

	template < typename T >
	int			decode(
				    std::vector<T>     &data,
				    std::vector<T>     &parity,
				    const std::vector<int>
				    		       &erasure	= std::vector<int>(),
				    std::vector<int>   *position= 0 )
	    const
	{
	    typedef typename std::make_unsigned<T>::type
				uT;
	    typedef std::pair<uT *, uT *>
				uTpair;
        return decode( uTpair( (uT *)&(*data.begin()), (uT *)&(*data.begin()) + data.size() ),
               uTpair( (uT *)&(*parity.begin()), (uT *)&(*parity.begin()) + parity.size() ),
			   erasure, position );
	}

	template < typename T, size_t N >
	int			decode(
				    std::array<T,N>    &data,
				    int			pad	= 0, // ignore 'pad' symbols at start of array
				    const std::vector<int>
				    		       &erasure	= std::vector<int>(),
				    std::vector<int>   *position= 0 )
	    const
	{
	    typedef typename std::make_unsigned<T>::type
				uT;
	    typedef std::pair<uT *, uT *>
				uTpair;
        return decode( uTpair( (uT *)&(*data.begin()) + pad, (uT *)&(*data.begin()) + data.size() ),
			   erasure, position );
	}

	virtual int		decode(
				    const std::pair<uint8_t *, uint8_t *>
						       &data,
				    const std::vector<int>
				    		       &erasure	= std::vector<int>(),
				    std::vector<int>   *position= 0 )
	    const
	= 0;
	virtual int		decode(
				    const std::pair<uint8_t *, uint8_t *>
						       &data,
				    const std::pair<uint8_t *, uint8_t *>
						       &parity,
				    const std::vector<int>
				    		       &erasure	= std::vector<int>(),
				    std::vector<int>   *position= 0 )
	    const
	= 0;
	virtual int		decode(
				    const std::pair<uint16_t *, uint16_t *>
						       &data,
				    const std::vector<int>
				    		       &erasure	= std::vector<int>(),
				    std::vector<int>   *position= 0 )
	    const
	= 0;
	virtual int		decode(
				    const std::pair<uint16_t *, uint16_t *>
						       &data,
				    const std::pair<uint16_t *, uint16_t *>
						       &parity,
				    const std::vector<int>
				    		       &erasure	= std::vector<int>(),
				    std::vector<int>   *position= 0 )
	    const
	= 0;
	virtual int		decode(
				    const std::pair<uint32_t *, uint32_t *>
						       &data,
				    const std::vector<int>
				    		       &erasure	= std::vector<int>(),
				    std::vector<int>   *position= 0 )
	    const
	= 0;
	virtual int		decode(
				    const std::pair<uint32_t *, uint32_t *>
						       &data,
				    const std::pair<uint32_t *, uint32_t *>
						       &parity,
				    const std::vector<int>
				    		       &erasure	= std::vector<int>(),
				    std::vector<int>   *position= 0 )
	    const
	= 0;
    };
} // namespace ezpwd

inline
std::ostream		       &operator<<(
				    std::ostream       &lhs,
				    const ezpwd::reed_solomon_base
						       &rhs )
{
    return lhs << "RS(" << rhs.size() << "," << rhs.load() << ")";
}

namespace ezpwd {
    //
    // gfpoly - default field polynomial generator functor.
    //
    template < int SYM, int PLY >
    struct gfpoly {
	int 			operator() ( int sr )
	    const
	{
	    if ( sr == 0 )
		sr			= 1;
	    else {
		sr	      	      <<= 1;
		if ( sr & ( 1 << SYM ))
		    sr	       	       ^= PLY;
		sr		       &= (( 1 << SYM ) - 1);
	    }
	    return sr;
	}
    };
    

    template < typename TYP, int SYM, int PRM, class PLY,
	       typename MTX=int, typename GRD=int >
    class reed_solomon_tabs
    : public reed_solomon_base {

    public:
	static const size_t	DATUM	= 8 * sizeof TYP();	// bits / TYP
	static const size_t	SYMBOL	= SYM;			// bits / symbol
	static const int	MM	= SYM;
	static const int	SIZE	= ( 1 << SYM ) - 1;	// maximum symbols in field
	static const int	NN	= SIZE;
	static const int	A0	= SIZE;
	static const int	MODS				// modulo table: 1/2 the symbol size squared, up to 4k
#if defined( EZPWD_NO_MOD_TAB )
					= 0;
#else
					= SYM > 8 ? ( 1 << 12 ) : ( 1 << SYM << SYM/2 );
#endif
     TYP alpha_to[NN+1];
     TYP index_of[NN+1];
     TYP mod_of[MODS];
     MTX		mutex;
     int 		iprim;
     /*static std::array<TYP,NN+1> alpha_to;
     static std::array<TYP,NN+1> index_of;
     static std::array<TYP,MODS> mod_of;*/

    private:

    protected:


	virtual		       ~reed_solomon_tabs()
	{
	    ;
	}
				reed_solomon_tabs()
				    : reed_solomon_base()
	{
	    // lock, if guard/mutex provided, and do init if not already done.  We check one value
	    // which changes several times; this is safe, 'cause the mutex will not be released (for
	    // us to check) 'til the initializing thread has completely initialized it.
	    GRD			guard( mutex ); (void)guard;
	    if ( iprim >= 0 )
		return;
#if defined( DEBUG ) && DEBUG >= 1
	    std::cout << "RS(" << SIZE << ",*): Initialize for " << NN << " symbols size, " << MODS << " modulo table." << std::endl;
#endif
	    // Generate Galois field lookup tables
	    index_of[0]			= A0;	// log(zero) = -inf
	    alpha_to[A0]		= 0;	// alpha**-inf = 0
	    PLY			poly;
	    int			sr	= poly( 0 );
	    for ( int i = 0; i < NN; i++ ) {
		index_of[sr]		= i;
		alpha_to[i]		= sr;
		sr			= poly( sr );
	    }
	    // If it's not primitive, exit
        if ( sr != alpha_to[0] )
        throw std::exception();//();//("reed-solomon: Galois field polynomial not primitive" );
	    // Generate modulo table for some commonly used (non-trivial) values
	    for ( int x = NN; x < NN + MODS; ++x )
		mod_of[x-NN]		= _modnn( x );
	    // Find prim-th root of 1, index form, used in decoding.
	    iprim			= 1;
	    while ( iprim % PRM != 0 )
		iprim		       += NN;
	    iprim 		       /= PRM;
	}

	// 
	// modnn -- modulo replacement for galois field arithmetics, optionally w/ table acceleration
	//
	//  @x:		the value to reduce (will never be -'ve)
	//
	//  where
	//  MM = number of bits per symbol
	//  NN = (2^MM) - 1
	//
	//  Simple arithmetic modulo would return a wrong result for values >= 3 * NN
	//
	TYP	 		_modnn(
				    int			x )
	    const
	{
	    while ( x >= NN ) {
		x		       -= NN;
		x			= ( x >> MM ) + ( x & NN );
	    }
	    return x;
	}
	TYP	 		modnn(
				    int			x )
	    const
	{
	    while ( x >= NN + MODS ) {
		x		       -= NN;
		x			= ( x >> MM ) + ( x & NN );
	    }
	    if ( MODS && x >= NN )
		x			= mod_of[x-NN];
	    return x;
	}
    };

    //
    // class reed_solomon - Reed-Solomon codec
    //
    // @TYP:		A symbol datum; {en,de}code operates on arrays of these
    // @DATUM:		Bits per datum (a TYP())
    // @SYM{BOL}, MM:	Bits per symbol
    // @NN:		Symbols per block (== (1<<MM)-1)
    // @alpha_to:	log lookup table
    // @index_of:	Antilog lookup table
    // @genpoly:	Generator polynomial
    // @NROOTS:		Number of generator roots = number of parity symbols
    // @FCR:		First consecutive root, index form
    // @PRM:		Primitive element, index form
    // @iprim:		prim-th root of 1, index form
    // @PLY:		The primitive generator polynominal functor
    // @MTX:		A std::mutex like object, or a dummy
    // @GRD:		A std::lock_guard, or anything that can take an MTX
    //
    //     All reed_solomon<T, ...> instances with the same template type parameters share a common
    // (static) set of alpha_to, index_of and genpoly tables.  The first instance to be constructed
    // initializes the tables (optionally protected by a std::mutex/std::lock_guard).
    // 
    //     Each specialized type of reed_solomon implements a specific encode/decode method
    // appropriate to its datum 'TYP'.  When accessed via a generic reed_solomon_base pointer, only
    // access via "safe" (size specifying) containers or iterators is available.
    //
    template < typename TYP, int SYM, int RTS, int FCR, int PRM, class PLY,
	       typename MTX=int, typename GRD=int >
    class reed_solomon
	: public reed_solomon_tabs<TYP, SYM, PRM, PLY, MTX, GRD> {

    public:
	typedef reed_solomon_tabs<TYP, SYM, PRM, PLY, MTX, GRD>
				tabs_t;
	using tabs_t::DATUM;
	using tabs_t::SYMBOL;
	using tabs_t::MM;
	using tabs_t::SIZE;
	using tabs_t::NN;
	using tabs_t::A0;

	using tabs_t::mutex;
	using tabs_t::iprim;

	using tabs_t::alpha_to;
	using tabs_t::index_of;

	using tabs_t::modnn;

	static const int	NROOTS	= RTS;
	static const int	LOAD	= SIZE - NROOTS;	// maximum non-parity symbol payload

    protected:
     TYP genpoly[NROOTS + 1];

    public:
	virtual size_t		datum() const
	{
	    return DATUM;
	}

	virtual size_t		symbol() const
	{
	    return SYMBOL;
	}

	virtual int		size() const
	{
	    return SIZE;
	}

	virtual int		nroots() const
	{
	    return NROOTS;
	}

	virtual int		load() const
	{
	    return LOAD;
	}

	using reed_solomon_base::encode;
	virtual void		encode(
				    const std::pair<uint8_t *, uint8_t *>
						       &data )
	    const
	{
	    encode_mask( data.first, data.second - data.first - NROOTS, data.second - NROOTS );
	}

	virtual void		encode(
				    const std::pair<const uint8_t *, const uint8_t *>
						       &data,
				    const std::pair<uint8_t *, uint8_t *>
						       &parity )
	    const
	{
        if ( parity.second - parity.first != NROOTS )
        throw std::exception();//( "reed-solomon: parity length incompatible with number of roots" );
	    encode_mask( data.first, data.second - data.first, parity.first );
	}

	virtual void		encode(
				    const std::pair<uint16_t *, uint16_t *>
						       &data )
	    const
	{
	    encode_mask( data.first, data.second - data.first - NROOTS, data.second - NROOTS );
	}

	virtual void		encode(
				    const std::pair<const uint16_t *, const uint16_t *>
						       &data,
				    const std::pair<uint16_t *, uint16_t *>
						       &parity )
	    const
	{
        if ( parity.second - parity.first != NROOTS )
        throw std::exception();//( "reed-solomon: parity length incompatible with number of roots" );
	    encode_mask( data.first, data.second - data.first, parity.first );
	}

	virtual void		encode(
				    const std::pair<uint32_t *, uint32_t *>
						       &data )
	    const
	{
	    encode_mask( data.first, data.second - data.first - NROOTS, data.second - NROOTS );
	}

	virtual void		encode(
				    const std::pair<const uint32_t *, const uint32_t *>
						       &data,
				    const std::pair<uint32_t *, uint32_t *>
						       &parity )
	    const
	{
        if ( parity.second - parity.first != NROOTS )
        throw std::exception();//( "reed-solomon: parity length incompatible with number of roots" );
	    encode_mask( data.first, data.second - data.first, parity.first );
	}

	template < typename INP >
	void			encode_mask(
				    const INP	       *data,
				    int			len,
				    INP		       *parity )	// pointer to all NROOTS parity symbols

	    const
	{
        if ( len < 1 )
        throw std::exception();//( "reed-solomon: must provide space for all parity and at least one non-parity symbol" );

	    const TYP       	       *dataptr;
	    TYP			       *pariptr;
	    const size_t		INPUT	= 8 * sizeof ( INP );

	    if ( DATUM != SYMBOL || DATUM != INPUT ) {
		// Our DATUM (TYP) size (eg. uint8_t ==> 8, uint16_t ==> 16, uint32_t ==> 32)
		// doesn't exactly match our R-S SYMBOL size (eg. 6), or our INP size; Must mask and
		// copy.  The INP data must fit at least the SYMBOL size!
        if ( SYMBOL > INPUT )
            throw std::exception();//( "reed-solomon: output data type too small to contain symbols" );
		std::array<TYP,SIZE>	tmp;
		TYP			msk	= static_cast<TYP>( ~0UL << SYMBOL );
		for ( int i = 0; i < len; ++i )
		    tmp[LOAD - len + i]		= data[i] & ~msk;
		dataptr				= &tmp[LOAD - len];
		pariptr				= &tmp[LOAD];

		encode( dataptr, len, pariptr );

		// we copied/masked data; copy the parity symbols back (may be different sizes)
		for ( int i = 0; i < NROOTS; ++i )
		    parity[i]			= pariptr[i];
	    } else {
		// Our R-S SYMBOL size, DATUM size and INP type size exactly matches; use in-place.
		dataptr				= reinterpret_cast<const TYP *>( data );
		pariptr				= reinterpret_cast<TYP *>( parity );

		encode( dataptr, len, pariptr );
	    }
	}
	    
	using reed_solomon_base::decode;
	virtual int		decode(
				    const std::pair<uint8_t *, uint8_t *>
						       &data,
				    const std::vector<int>
				    		       &erasure	= std::vector<int>(),
				    std::vector<int>   *position= 0 )
	    const
	{
	    return decode_mask( data.first, data.second - data.first, (uint8_t *)0,
				erasure, position );
	}

	virtual int		decode(
				    const std::pair<uint8_t *, uint8_t *>
						       &data,
				    const std::pair<uint8_t *, uint8_t *>
						       &parity,
				    const std::vector<int>
				    		       &erasure	= std::vector<int>(),
				    std::vector<int>   *position= 0 )
	    const
	{
        if ( parity.second - parity.first != NROOTS )
        throw std::exception();//( "reed-solomon: parity length incompatible with number of roots" );
	    return decode_mask( data.first, data.second - data.first, parity.first,
				erasure, position );
	}

	virtual int		decode(
				    const std::pair<uint16_t *, uint16_t *>
						       &data,
				    const std::vector<int>
				    		       &erasure	= std::vector<int>(),
				    std::vector<int>   *position= 0 )
	    const
	{
	    return decode_mask( data.first, data.second - data.first, (uint16_t *)0,
				erasure, position );
	}

	virtual int		decode(
				    const std::pair<uint16_t *, uint16_t *>
						       &data,
				    const std::pair<uint16_t *, uint16_t *>
						       &parity,
				    const std::vector<int>
				    		       &erasure	= std::vector<int>(),
				    std::vector<int>   *position= 0 )
	    const
	{
        if ( parity.second - parity.first != NROOTS )
        throw std::exception();//( "reed-solomon: parity length incompatible with number of roots" );
	    return decode_mask( data.first, data.second - data.first, parity.first,
				erasure, position );
	}

	virtual int		decode(
				    const std::pair<uint32_t *, uint32_t *>
						       &data,
				    const std::vector<int>
				    		       &erasure	= std::vector<int>(),
				    std::vector<int>   *position= 0 )
	    const
	{
	    return decode_mask( data.first, data.second - data.first, (uint32_t *)0,
				erasure, position );
	}

	virtual int		decode(
				    const std::pair<uint32_t *, uint32_t *>
						       &data,
				    const std::pair<uint32_t *, uint32_t *>
						       &parity,
				    const std::vector<int>
				    		       &erasure	= std::vector<int>(),
				    std::vector<int>   *position= 0 )
	    const
	{
        if ( parity.second - parity.first != NROOTS )
        throw std::exception();//( "reed-solomon: parity length incompatible with number of roots" );
	    return decode_mask( data.first, data.second - data.first, parity.first,
				erasure, position );
	}

	// 
	// decode_mask	-- mask INP data into valid SYMBOL data
	// 
	///     Incoming data may be in a variety of sizes, and may contain information beyond the
	/// R-S symbol capacity.  For example, we might use a 6-bit R-S symbol to correct the lower
	/// 6 bits of an 8-bit data character.  This would allow us to correct common substitution
	/// errors (such as '2' for '3', 'R' for 'T', 'n' for 'm').
	/// 
	template < typename INP >
	int			decode_mask(
				    INP		       *data,
				    int			len,
				    INP		       *parity	= 0,	// either 0, or pointer to all parity symbols
				    const std::vector<int>
				    		       &erasure	= std::vector<int>(),
				    std::vector<int>   *position= 0 )
	    const
	{
        if ( len < ( parity ? 0 : NROOTS ) + 1 )
        throw std::exception();//( "reed-solomon: must provide all parity and at least one non-parity symbol" );
	    if ( ! parity ) {
		len			       -= NROOTS;
		parity				= data + len;
	    }

	    TYP		       	       *dataptr;
	    TYP			       *pariptr;
	    const size_t		INPUT	= 8 * sizeof ( INP );

	    std::array<TYP,SIZE>	tmp;
	    TYP				msk	= static_cast<TYP>( ~0UL << SYMBOL );
	    const bool			cpy	= DATUM != SYMBOL || DATUM != INPUT;
	    if ( cpy ) {
		// Our DATUM (TYP) size (eg. uint8_t ==> 8, uint16_t ==> 16, uint32_t ==> 32)
		// doesn't exactly match our R-S SYMBOL size (eg. 6), or our INP size; Must copy.
		// The INP data must fit at least the SYMBOL size!
        if ( SYMBOL > INPUT )
            throw std::exception();//( "reed-solomon: input data type too small to contain symbols" );
		for ( int i = 0; i < len; ++i ) {
		    tmp[LOAD - len + i]		= data[i] & ~msk;
		}
		dataptr				= &tmp[LOAD - len];
		for ( int i = 0; i < NROOTS; ++i ) {
            if ( TYP( parity[i] ) & msk )
            throw std::exception();//( "reed-solomon: parity data contains information beyond R-S symbol size" );
		    tmp[LOAD + i]		= parity[i];
		}
		pariptr				= &tmp[LOAD];
	    } else {
		// Our R-S SYMBOL size, DATUM size and INPUT type sizes exactly matches
		dataptr				= reinterpret_cast<TYP *>( data );
		pariptr				= reinterpret_cast<TYP *>( parity );
	    }

	    int			corrects;
	    if ( ! erasure.size() && ! position ) {
		// No erasures, and error position info not wanted.
		corrects			= decode( dataptr, len, pariptr );
	    } else {
		// Either erasure location info specified, or resultant error position info wanted;
		// Prepare pos (a temporary, if no position vector provided), and copy any provided
		// erasure positions.  After number of corrections is known, resize the position
		// vector.  Thus, we use any supplied erasure info, and optionally return any
		// correction position info separately.
		std::vector<int>       _pos;
		std::vector<int>       &pos	= position ? *position : _pos;
		pos.resize( std::max( size_t( NROOTS ), erasure.size() ));
		std::copy( erasure.begin(), erasure.end(), pos.begin() );
		corrects			= decode( dataptr, len, pariptr,
							  &pos.front(), erasure.size() );
        if ( corrects > int( pos.size() ))
            throw std::exception();//( "reed-solomon: FATAL: produced too many corrections; possible corruption!" );
		pos.resize( std::max( 0, corrects ));
	    }

	    if ( cpy && corrects > 0 ) {
		for ( int i = 0; i < len; ++i ) {
		    data[i]		       &= msk;
		    data[i]		       |= tmp[LOAD - len + i];
		}
		for ( int i = 0; i < NROOTS; ++i ) {
		    parity[i]			= tmp[LOAD + i];
		}
	    }
	    return corrects;
	}

	virtual		       ~reed_solomon()
	{
	    ;
	}
				reed_solomon()
				    : reed_solomon_tabs<TYP, SYM, PRM, PLY, MTX, GRD>()
	{
	    // lock, if guard/mutex provided, and do init if not already done.  We check one element
	    // of the array; this is safe, 'cause the mutex will not be released (for us to check)
	    // 'til the initializing thread has completely initialized the array.
	    GRD			guard( mutex ); (void)guard;
	    if ( genpoly[0] )
		return;
#if defined( DEBUG ) && DEBUG >= 2
	    std::cout << "RS(" << SIZE << "," << LOAD << "): Initialize for " << NROOTS << " roots." << std::endl;
#endif
	    // Form RS code generator polynomial from its roots
	    genpoly[0]			= 1;
	    for ( int i = 0, root = FCR * PRM; i < NROOTS; i++, root += PRM ) {
		genpoly[i + 1]		= 1;
		// Multiply genpoly[] by  @**(root + x)
		for ( int j = i; j > 0; j-- ) {
		    if ( genpoly[j] != 0 )
			genpoly[j]	= genpoly[j - 1]
			    ^ alpha_to[modnn(index_of[genpoly[j]] + root)];
		    else
			genpoly[j]	= genpoly[j - 1];
		}
		// genpoly[0] can never be zero
		genpoly[0]		= alpha_to[modnn(index_of[genpoly[0]] + root)];
	    }
	    // convert genpoly[] to index form for quicker encoding
	    for ( int i = 0; i <= NROOTS; i++ )
		genpoly[i]		= index_of[genpoly[i]];
	}

	void			encode(
				    const TYP	       *data,
				    int			len,
				    TYP		       *parity ) // at least nroots
	    const
	{
	    // Check length parameter for validity
	    int			pad	= NN - NROOTS - len;
        if ( pad < 0 || pad >= NN )
        throw std::exception();//( "reed-solomon: data length incompatible with block size and error correction symbols" );
	    for ( int i = 0; i < NROOTS; i++ )
		parity[i]		= 0;
	    for ( int i = 0; i < len; i++ ) {
		TYP		feedback= index_of[data[i] ^ parity[0]];
		if ( feedback != A0 )
		    for ( int j = 1; j < NROOTS; j++ )
			parity[j]      ^= alpha_to[modnn(feedback + genpoly[NROOTS - j])];

		std::rotate( parity, parity + 1, parity + NROOTS );
		if ( feedback != A0 )
		    parity[NROOTS - 1]	= alpha_to[modnn(feedback + genpoly[0])];
		else
		    parity[NROOTS - 1]	= 0;
	    }
#if defined( DEBUG ) && DEBUG >= 2
	    std::cout << *this << " encode " << std::vector<TYP>( data, data + len )
		      << " --> " << std::vector<TYP>( parity, parity + NROOTS ) << std::endl;
#endif
	}

	int			decode(
				    TYP		       *data,
				    int			len,
				    TYP		       *parity,		// Requires: at least NROOTS
				    int		       *eras_pos= 0,	// Capacity: at least NROOTS
				    int			no_eras	= 0,	// Maximum:  at most  NROOTS
				    TYP		       *corr	= 0 )	// Capacity: at least NROOTS
	    const
	{
	    typedef std::array< TYP, NROOTS >
				typ_nroots;
	    typedef std::array< TYP, NROOTS+1 >
				typ_nroots_1;
	    typedef std::array< int, NROOTS >
				int_nroots;

	    typ_nroots_1	lambda  { { 0 } };
	    typ_nroots		syn;
	    typ_nroots_1	b;
	    typ_nroots_1	t;
	    typ_nroots_1	omega;
	    int_nroots		root;
	    typ_nroots_1	reg;
	    int_nroots		loc;
	    int			count	= 0;

	    // Check length parameter and erasures for validity
	    int			pad	= NN - NROOTS - len;
        if ( pad < 0 || pad >= NN )
        throw std::exception();//( "reed-solomon: data length incompatible with block size and error correction symbols" );
	    if ( no_eras ) {
        if ( no_eras > NROOTS )
            throw std::exception();//( "reed-solomon: number of erasures exceeds capacity (number of roots)" );
        for ( int i = 0; i < no_eras; ++i )
            if ( eras_pos[i] < 0 || eras_pos[i] >= len + NROOTS )
            throw std::exception();//( "reed-solomon: erasure positions outside data+parity" );
        }

	    // form the syndromes; i.e., evaluate data(x) at roots of g(x)
	    for ( int i = 0; i < NROOTS; i++ )
		syn[i]			= data[0];

	    for ( int j = 1; j < len; j++ ) {
		for ( int i = 0; i < NROOTS; i++ ) {
		    if ( syn[i] == 0 ) {
			syn[i]		= data[j];
		    } else {
			syn[i]		= data[j]
			    ^ alpha_to[modnn(index_of[syn[i]] + ( FCR + i ) * PRM)];
		    }
		}
	    }

	    for ( int j = 0; j < NROOTS; j++ ) {
		for ( int i = 0; i < NROOTS; i++ ) {
		    if ( syn[i] == 0 ) {
			syn[i]		= parity[j];
		    } else {
			syn[i] 		= parity[j]
			    ^ alpha_to[modnn(index_of[syn[i]] + ( FCR + i ) * PRM)];
		    }
		}
	    }

	    // Convert syndromes to index form, checking for nonzero condition
	    TYP 		syn_error = 0;
	    for ( int i = 0; i < NROOTS; i++ ) {
		syn_error	       |= syn[i];
		syn[i]			= index_of[syn[i]];
	    }

	    int			deg_lambda = 0;
	    int			deg_omega = 0;
	    int			r	= no_eras;
	    int			el	= no_eras;
	    if ( ! syn_error ) {
		// if syndrome is zero, data[] is a codeword and there are no errors to correct.
		count			= 0;
		goto finish;
	    }

	    lambda[0] 			= 1;
	    if ( no_eras > 0 ) {
		// Init lambda to be the erasure locator polynomial.  Convert erasure positions
		// from index into data, to index into Reed-Solomon block.
		lambda[1]		= alpha_to[modnn(PRM * (NN - 1 - ( eras_pos[0] + pad )))];
		for ( int i = 1; i < no_eras; i++ ) {
		    TYP		u	= modnn(PRM * (NN - 1 - ( eras_pos[i] + pad )));
		    for ( int j = i + 1; j > 0; j-- ) {
			TYP	tmp	= index_of[lambda[j - 1]];
			if ( tmp != A0 ) {
			    lambda[j]  ^= alpha_to[modnn(u + tmp)];
			}
		    }
		}
	    }

#if DEBUG >= 1
	    // Test code that verifies the erasure locator polynomial just constructed
	    // Needed only for decoder debugging.
    
	    // find roots of the erasure location polynomial
	    for( int i = 1; i<= no_eras; i++ )
		reg[i]			= index_of[lambda[i]];

	    count			= 0;
	    for ( int i = 1, k = iprim - 1; i <= NN; i++, k = modnn( k + iprim )) {
		TYP		q	= 1;
		for ( int j = 1; j <= no_eras; j++ ) {
		    if ( reg[j] != A0 ) {
			reg[j]		= modnn( reg[j] + j );
			q	       ^= alpha_to[reg[j]];
		    }
		}
		if ( q != 0 )
		    continue;
		// store root and error location number indices
		root[count]		= i;
		loc[count]		= k;
		count++;
	    }
	    if ( count != no_eras ) {
		std::cout << "ERROR: count = " << count << ", no_eras = " << no_eras 
			  << "lambda(x) is WRONG"
			  << std::endl;
		count = -1;
		goto finish;
	    }
#if DEBUG >= 2
	    if ( count ) {
	        std::cout
		    << "Erasure positions as determined by roots of Eras Loc Poly: ";
		for ( int i = 0; i < count; i++ )
		    std::cout << loc[i] << ' ';
		std::cout << std::endl;
	        std::cout
		    << "Erasure positions as determined by roots of eras_pos array: ";
		for ( int i = 0; i < no_eras; i++ )
		    std::cout << eras_pos[i] << ' ';
		std::cout << std::endl;
	    }
#endif
#endif

	    for ( int i = 0; i < NROOTS + 1; i++ )
		b[i]			= index_of[lambda[i]];

	    //
	    // Begin Berlekamp-Massey algorithm to determine error+erasure locator polynomial
	    //
	    while ( ++r <= NROOTS ) { // r is the step number
		// Compute discrepancy at the r-th step in poly-form
		TYP		discr_r	= 0;
		for ( int i = 0; i < r; i++ ) {
		    if (( lambda[i] != 0 ) && ( syn[r - i - 1] != A0 )) {
			discr_r	       ^= alpha_to[modnn(index_of[lambda[i]] + syn[r - i - 1])];
		    }
		}
		discr_r			= index_of[discr_r];	// Index form
		if ( discr_r == A0 ) {
		    // 2 lines below: B(x) <-- x*B(x)
		    // Rotate the last element of b[NROOTS+1] to b[0]
		    std::rotate( b.begin(), b.begin()+NROOTS, b.end() );
		    b[0]		= A0;
		} else {
		    // 7 lines below: T(x) <-- lambda(x)-discr_r*x*b(x)
		    t[0]		= lambda[0];
		    for ( int i = 0; i < NROOTS; i++ ) {
			if ( b[i] != A0 ) {
			    t[i + 1]	= lambda[i + 1]
				^ alpha_to[modnn(discr_r + b[i])];
			} else
			    t[i + 1]	 = lambda[i + 1];
		    }
		    if ( 2 * el <= r + no_eras - 1 ) {
			el		= r + no_eras - el;
			// 2 lines below: B(x) <-- inv(discr_r) * lambda(x)
			for ( int i = 0; i <= NROOTS; i++ ) {
			    b[i]	= ((lambda[i] == 0)
					   ? A0
					   : modnn(index_of[lambda[i]] - discr_r + NN));
			}
		    } else {
			// 2 lines below: B(x) <-- x*B(x)
			std::rotate( b.begin(), b.begin()+NROOTS, b.end() );
			b[0]		= A0;
		    }
		    lambda		= t;
		}
	    }

	    // Convert lambda to index form and compute deg(lambda(x))
	    for ( int i = 0; i < NROOTS + 1; i++ ) {
		lambda[i]		= index_of[lambda[i]];
		if ( lambda[i] != NN )
		    deg_lambda		= i;
	    }
	    // Find roots of error+erasure locator polynomial by Chien search
	    reg				= lambda;
	    count			= 0; // Number of roots of lambda(x)
	    for ( int i = 1, k = iprim - 1; i <= NN; i++, k = modnn( k + iprim )) {
		TYP		q	= 1; // lambda[0] is always 0
		for ( int j = deg_lambda; j > 0; j-- ) {
		    if ( reg[j] != A0 ) {
			reg[j]		= modnn( reg[j] + j );
			q	       ^= alpha_to[reg[j]];
		    }
		}
		if ( q != 0 )
		    continue; // Not a root
		// store root (index-form) and error location number
#if DEBUG >= 2
		std::cout << "count " << count << " root " << i << " loc " << k << std::endl;
#endif
		root[count]		= i;
		loc[count]		= k;
		// If we've already found max possible roots, abort the search to save time
		if ( ++count == deg_lambda )
		    break;
	    }
	    if ( deg_lambda != count ) {
		// deg(lambda) unequal to number of roots => uncorrectable error detected
		count			= -1;
		goto finish;
	    }
	    //
	    // Compute err+eras evaluator poly omega(x) = s(x)*lambda(x) (modulo x**NROOTS). in
	    // index form. Also find deg(omega).
	    //
	    deg_omega 			= deg_lambda - 1;
	    for ( int i = 0; i <= deg_omega; i++ ) {
		TYP		tmp	= 0;
		for ( int j = i; j >= 0; j-- ) {
		    if (( syn[i - j] != A0 ) && ( lambda[j] != A0 ))
			tmp	       ^= alpha_to[modnn(syn[i - j] + lambda[j])];
		}
		omega[i]		= index_of[tmp];
	    }

	    //
	    // Compute error values in poly-form. num1 = omega(inv(X(l))), num2 = inv(X(l))**(fcr-1)
	    // and den = lambda_pr(inv(X(l))) all in poly-form
	    //
	    for ( int j = count - 1; j >= 0; j-- ) {
		TYP		num1	= 0;
		for ( int i = deg_omega; i >= 0; i-- ) {
		    if ( omega[i] != A0 )
			num1	       ^= alpha_to[modnn(omega[i] + i * root[j])];
		}
		TYP		num2	= alpha_to[modnn(root[j] * ( FCR - 1 ) + NN)];
		TYP		den	= 0;

		// lambda[i+1] for i even is the formal derivative lambda_pr of lambda[i]
		for ( int i = std::min(deg_lambda, NROOTS - 1) & ~1; i >= 0; i -= 2 ) {
		    if ( lambda[i + 1] != A0 ) {
			den	       ^= alpha_to[modnn(lambda[i + 1] + i * root[j])];
		    }
		}
#if defined( DEBUG ) && DEBUG >= 1
		if ( den == 0 ) {
		    std::cout << "ERROR: denominator = 0" << std::endl;
		    count = -1;
		    goto finish;
		}
#endif
		// Apply error to data.  Padding ('pad' unused symbols) begin at index 0.
		if ( num1 != 0 ) {
		    if ( loc[j] < pad ) {
			// If the computed error position is in the 'pad' (the unused portion of the
			// R-S data capacity), then our solution has failed -- we've computed a
			// correction location outside of the data and parity we've been provided!
#if DEBUG >= 2
			std::cout
			    << "ERROR: RS(" << SIZE <<"," << LOAD
			    << ") computed error location: " << loc[j]
			    << " within " << pad << " pad symbols, not within "
			    << LOAD - pad << " data or " << NROOTS << " parity"
			    << std::endl;
#endif
			count = -1;
			goto finish;
		    }

		    TYP		cor	= alpha_to[modnn(index_of[num1]
							 + index_of[num2]
							 + NN - index_of[den])];
		    // Store the error correction pattern, if a correction buffer is available
		    if ( corr )
			corr[j] 	= cor;
		    // If a data/parity buffer is given and the error is inside the message or
		    // parity data, correct it
		    if ( loc[j] < ( NN - NROOTS )) {
			if ( data ) {
			    data[loc[j] - pad] ^= cor;
			}
		    } else if ( loc[j] < NN ) {
		        if ( parity )
		            parity[loc[j] - ( NN - NROOTS )] ^= cor;
		    }
		}
	    }

	finish:
#if defined( DEBUG ) && DEBUG > 0
	    if ( count > NROOTS )
		std::cout << "ERROR: Number of corrections: " << count << " exceeds NROOTS: " << NROOTS << std::endl;
#endif
#if defined( DEBUG ) && DEBUG > 1
	    std::cout << "data      x" << std::setw( 3 ) << len    << ": " << std::vector<uint8_t>( data, data + len ) << std::endl;
	    std::cout << "parity    x" << std::setw( 3 ) << NROOTS << ": " << std::string(  len * 2, ' ' ) << std::vector<uint8_t>( parity, parity + NROOTS ) << std::endl;
	    if ( count > 0 ) {
		std::string errors( 2 * ( len + NROOTS ), ' ' );
		for ( int i = 0; i < count; ++i ) {
		    errors[2*(loc[i]-pad)+0] = 'E';
		    errors[2*(loc[i]-pad)+1] = 'E';
		}
		for ( int i = 0; i < no_eras; ++i ) {
		    errors[2*(eras_pos[i])+0] = 'e';
		    errors[2*(eras_pos[i])+1] = 'e';
		}
		std::cout << "e)ra,E)rr x" << std::setw( 3 ) << count  << ": " << errors << std::endl;
	    }
#endif
	    if ( eras_pos != NULL ) {
		for ( int i = 0; i < count; i++)
		    eras_pos[i]		= loc[i] - pad;
	    }
	    return count;
	}
    }; // class reed_solomon

    // 
    // Define the static reed_solomon...<...> members; allowed in header for template types.
    // 
    //     The reed_solomon_tags<...>::iprim < 0 is used to indicate to the first instance that the
    // static tables require initialization.  If reed_solomon_tabs<...>::mutex is something like a
    // std::mutex, and GRD is a std::lock_guard, then the mutex is acquired for the test and
    // initialization.
    // 
/*    template < typename TYP, int SYM, int PRM, class PLY, typename MTX, typename GRD >
        MTX				reed_solomon_tabs< TYP, SYM, PRM, PLY, MTX, GRD >::mutex;

    template < typename TYP, int SYM, int PRM, class PLY, typename MTX, typename GRD >
        int				reed_solomon_tabs< TYP, SYM, PRM, PLY, MTX, GRD >::iprim = -1;

    template < typename TYP, int SYM, int PRM, class PLY, typename MTX, typename GRD >
        std::array< TYP, reed_solomon_tabs< TYP, SYM, PRM, PLY, MTX, GRD >::NN + 1 >
        reed_solomon_tabs< TYP, SYM, PRM, PLY, MTX, GRD >::alpha_to;

    template < typename TYP, int SYM, int PRM, class PLY, typename MTX, typename GRD >
        std::array< TYP, reed_solomon_tabs< TYP, SYM, PRM, PLY, MTX, GRD >::NN + 1 >
                    reed_solomon_tabs< TYP, SYM, PRM, PLY, MTX, GRD >::index_of;
    template < typename TYP, int SYM, int PRM, class PLY, typename MTX, typename GRD >
        std::array< TYP, reed_solomon_tabs< TYP, SYM, PRM, PLY, MTX, GRD >::MODS >
                    reed_solomon_tabs< TYP, SYM, PRM, PLY, MTX, GRD >::mod_of;

    template < typename TYP, int SYM, int RTS, int FCR, int PRM, class PLY, typename MTX, typename GRD >
        std::array< TYP, reed_solomon< TYP, SYM, RTS, FCR, PRM, PLY, MTX, GRD >::NROOTS + 1 >
                    reed_solomon< TYP, SYM, RTS, FCR, PRM, PLY, MTX, GRD >::genpoly;

    // ezpwd::log_<N,B> -- compute the log base B of N at compile-time
    template <size_t N, size_t B=2> struct log_{       enum { value = 1 + log_<N/B, B>::value }; };
    template <size_t B>		    struct log_<1, B>{ enum { value = 0 }; };
    template <size_t B>		    struct log_<0, B>{ enum { value = 0 }; };

    // 
    // __RS( ... ) -- Define a reed-solomon codec 
    // 
    // @SYMBOLS:	Total number of symbols; must be a power of 2 minus 1, eg 2^8-1 == 255
    // @PAYLOAD:	The maximum number of non-parity symbols, eg 253 ==> 2 parity symbols
    // @POLY:		A primitive polynomial appropriate to the SYMBOLS size
    // @FCR:		The first consecutive root of the Reed-Solomon generator polynomial
    // @PRIM:		The primitive root of the generator polynomial
    // 
#   define __RS_TYP( TYPE, SYMBOLS, PAYLOAD, POLY, FCR, PRIM )		\
	ezpwd::reed_solomon<						\
	    TYPE,							\
	    ezpwd::log_< (SYMBOLS) + 1 >::value,			\
	    (SYMBOLS) - (PAYLOAD), FCR, PRIM,				\
	    ezpwd::gfpoly<						\
		ezpwd::log_< (SYMBOLS) + 1 >::value,			\
		POLY >>

#   define __RS( NAME, TYPE, SYMBOLS, PAYLOAD, POLY, FCR, PRIM )	\
	__RS_TYP( TYPE, SYMBOLS, PAYLOAD, POLY, FCR, PRIM ) {		\
	    NAME()							\
		: __RS_TYP( TYPE, SYMBOLS, PAYLOAD, POLY, FCR, PRIM )()	\
	    {;}								\
	}

    //
    // RS<SYMBOLS, PAYLOAD> -- Standard partial specializations for Reed-Solomon codec type access
    //
    //     Normally, Reed-Solomon codecs are described with terms like RS(255,252).  Obtain various
    // standard Reed-Solomon codecs using macros of a similar form, eg. RS<255, 252>. Standard PLY,
    // FCR and PRM values are provided for various SYMBOL sizes, along with appropriate basic types
    // capable of holding all internal Reed-Solomon tabular data.
    // 
    //     In order to provide "default initialization" of const RS<...> types, a user-provided
    // default constructor must be provided.
    // 
    template < size_t SYMBOLS, size_t PAYLOAD > struct RS;
    template < size_t PAYLOAD > struct RS<    3, PAYLOAD> : public __RS( RS, uint8_t,      3, PAYLOAD,     0x7,	 1,  1 );
    template < size_t PAYLOAD > struct RS<    7, PAYLOAD> : public __RS( RS, uint8_t,      7, PAYLOAD,     0xb,	 1,  1 );
    template < size_t PAYLOAD > struct RS<   15, PAYLOAD> : public __RS( RS, uint8_t,     15, PAYLOAD,    0x13,	 1,  1 );
    template < size_t PAYLOAD > struct RS<   31, PAYLOAD> : public __RS( RS, uint8_t,     31, PAYLOAD,    0x25,	 1,  1 );
    template < size_t PAYLOAD > struct RS<   63, PAYLOAD> : public __RS( RS, uint8_t,     63, PAYLOAD,    0x43,	 1,  1 );
		//VDL3
    template < size_t PAYLOAD > struct RS<   72, PAYLOAD> : public __RS( RS, uint8_t,     72, PAYLOAD,   0x187,	 120,  1 );
		//
    template < size_t PAYLOAD > struct RS<  127, PAYLOAD> : public __RS( RS, uint8_t,    127, PAYLOAD,    0x89,	 1,  1 );
    template < size_t PAYLOAD > struct RS<  255, PAYLOAD> : public __RS( RS, uint8_t,    255, PAYLOAD,   0x187,	 1,  1 );
    template < size_t PAYLOAD > struct RS<  511, PAYLOAD> : public __RS( RS, uint16_t,   511, PAYLOAD,   0x211,	 1,  1 );
    template < size_t PAYLOAD > struct RS< 1023, PAYLOAD> : public __RS( RS, uint16_t,  1023, PAYLOAD,   0x409,	 1,  1 );
    template < size_t PAYLOAD > struct RS< 2047, PAYLOAD> : public __RS( RS, uint16_t,  2047, PAYLOAD,   0x805,	 1,  1 );
    template < size_t PAYLOAD > struct RS< 4095, PAYLOAD> : public __RS( RS, uint16_t,  4095, PAYLOAD,  0x1053,	 1,  1 );
    template < size_t PAYLOAD > struct RS< 8191, PAYLOAD> : public __RS( RS, uint16_t,  8191, PAYLOAD,  0x201b,	 1,  1 );
    template < size_t PAYLOAD > struct RS<16383, PAYLOAD> : public __RS( RS, uint16_t, 16383, PAYLOAD,  0x4443,	 1,  1 );
    template < size_t PAYLOAD > struct RS<32767, PAYLOAD> : public __RS( RS, uint16_t, 32767, PAYLOAD,  0x8003,	 1,  1 );
    template < size_t PAYLOAD > struct RS<65535, PAYLOAD> : public __RS( RS, uint16_t, 65535, PAYLOAD, 0x1100b,	 1,  1 );
    
    template < size_t SYMBOLS, size_t PAYLOAD > struct RS_CCSDS;
		template < size_t PAYLOAD > struct RS_CCSDS<255, PAYLOAD> : public __RS( RS_CCSDS, uint8_t, 255, PAYLOAD, 0x187, 120, 1 );
*/

    // 
    // strength<PARITY>	-- compute strength (given N parity symbols) of R-S correction
    // 
    //     Returns a confidence strength rating, which is the ratio:
    // 
    //         100 - ( errors * 2 + erasures ) * 100 / parity
    // 
    // which is proportional to the number of parity symbols unused by the reported number of
    // corrected symbols.  If 0, then all parity resources were consumed to recover the R-S
    // codeword, and we can have no confidence in the result.  If -'ve, indicates more parity
    // resources were consumed than available, indicating that the result is likely incorrect.
    // 
    //     Accounts for the fact that a signalled erasure may not be reported in the corrected
    // position vector, if the symbol happens to match the computed value.  Note that even if the
    // error or erasure occurs within the "parity" portion of the codeword, this doesn't reduce the
    // effective strength -- all symbols in the R-S complete codeword are equally effective in
    // recovering any other symbol in error/erasure.
    // 
    template < size_t PARITY >
    int				strength(
				    int			corrected,
				    const std::vector<int>&erasures,	// original erasures positions
				    const std::vector<int>&positions )	// all reported correction positions
    {
	// -'ve indicates R-S failure; all parity consumed, but insufficient to correct the R-S
	// codeword.  Missing an unknown number of additional required parity symbols, so just
	// return -1 as the strength.
	if ( corrected < 0 ) {
#if defined( DEBUG ) && DEBUG >= 2
	    std::cout
		<< corrected << " corrections (R-S decode failure) == -1 confidence"
		<< std::endl;
#endif
	    return -1;
	}
    if ( corrected != int( positions.size() ))
        throw std::exception();//( "inconsistent R-S decode results" );

	// Any erasures that don't turn out to contain errors are not returned as fixed positions.
	// However, they have consumed parity resources.  Search for each erasure location in
	// positions, and if not reflected, add to the corrected/missed counters.
	int			missed	= 0;
    for ( auto e=erasures.begin(); e!= erasures.end(); ++e ) {
	    if ( std::find( positions.begin(), positions.end(), e ) == positions.end() ) {
		++corrected;
		++missed;
#if defined( DEBUG ) && DEBUG >= 2
		std::cout
		    << corrected << " corrections (R-S erasure missed): " << e
		    << std::endl;
#endif
	    }
	}
	int			errors	= corrected - erasures.size();
	int			consumed= errors * 2 + erasures.size();
	int			confidence= 100 - consumed * 100 / PARITY;
#if defined( DEBUG ) && DEBUG >= 2
	std::cout
	    << corrected << " corrections (R-S decode success)"
	    << " at: "			<< positions
	    << ", "			<< erasures.size() + missed
	    << " erasures ("		<< missed
	    << " unreported) at: "	<< erasures
	    << ") ==> "			<< errors
	    <<  " errors, and " 	<< consumed << " / " << PARITY
	    << " parity used == "	<< confidence
	    << "% confidence"
	    << std::endl;
#endif
	return confidence;
    }
    
} // namespace ezpwd
    
#endif // _EZPWD_RS
