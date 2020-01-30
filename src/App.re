open ApolloHooks;

module AppQuery = [%graphql {|
  query AppQuery {
    pokemons(first: 10) {
      name
    }
  }
|}];

[@react.component]
let make = () => {
 /* Both variant and records available */
  let (simple, _full) = useQuery(AppQuery.definition);

  <div>
  {
    switch(simple) {
      | Loading => <p>{React.string("Loading...")}</p>
      | Data(data) =>
        <ul>
          {
            switch(data##pokemons){
              | Some(pokemons) =>
                pokemons->Belt.Array.map(pokemon => {
                  <li>{pokemon->Belt.Option.flatMap(poke => poke##name)->Belt.Option.map(name => name->React.string)->Belt.Option.getWithDefault(React.null)}</li>
                })->React.array
              | None => React.null
            }
          }
        </ul>
      | NoData
      | Error(_) => <p>{React.string("Get off my lawn!")}</p>
    }
  }
  </div>
}
