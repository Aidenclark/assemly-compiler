Invocation:
    frontEnd [file]

-Filename may be specified

=========================================================================

Example Invocation:

	./frontEnd -> blank for input

    or

    ./frontEnd p2g3 

=========================================================================
BNF:

<S>      ->     Name Identifier Spot Identifier <R> <E> 
<R>     ->     Place <A> <B> Home
<E>     ->     ShowIdentifier
<A>     ->    NameIdentifier
<B>     ->    empty |  .   <C>. <B> | <D> <B>
<C>     ->    <F> | <G>
<D>     ->    <H> | <J> | <K> | <L>  | <E> | <F>
<F>     ->    {If   Identifier <T> <W> <D> } | { Do Again <D> <T> <W> }
<G>    ->     Here Number There 
<T>    ->     <<  |  <-
<V>   ->     +|   %|   &
<H>   ->     /  <Z>
<J>   ->     Assign Identifier <D>
<K>   ->    Spot Number Show Number|  Move Identifer Show Identifier
<L>   ->    Flip Identifier
<W>   ->   Number<V>  Number  |   Number .  
<Z>   ->     Identifier|  Number




// site for string.at() https://www.geeksforgeeks.org/string-at-in-cpp/
// stie for string.end() https://www.javatpoint.com/cpp-string-end-function