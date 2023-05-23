# assemly-compiler

Compiler is working. Each version functions differently. Have fun exploring the madness that this is. 

S     ->     Name Identifier Spot Identifier R E
<R>     ->     Place <A> <B> Home
<E>     ->     Show Identifier
<A>     ->    Name Identifier
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
