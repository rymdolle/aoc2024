#!/usr/bin/env escript

main([]) ->
    main(["input.txt"]);
main([File]) ->
    Data = parse(File),
    Part1 = [element(1, N) || N <- lists:filter(fun part1/1, Data)],
    Part2 = [element(1, N) || N <- lists:filter(fun part2/1, Data)],
    io:format("~p\n", [lists:sum(Part1)]),
    io:format("~p\n", [lists:sum(Part2)]).

parse(File) ->
    {ok, Data} = file:read_file(File),
    Lines = re:split(Data, "\n", [trim]),
    [begin
         [A, B] = binary:split(Line, <<": ">>),
         Values = binary:split(B, <<" ">>, [global]),
         {binary_to_integer(A), [binary_to_integer(N) || N <- Values]}
     end || Line <- Lines].

part1({Target, [Target]}) -> true;
part1({_, [_]}) -> false;
part1({Target, [A,B|_]}) when  A * B > Target andalso A + B > Target ->
    false;
part1({Target, [A,B|Values]}) ->
    part1({Target, [A*B|Values]}) orelse part1({Target, [A+B|Values]}).

part2({Target, [Target]}) -> true;
part2({_, [_]}) -> false;
part2({Target, [A,B|_]}) when  A * B > Target andalso A + B > Target ->
    false;
part2({Target, [A,B|Values]}) ->
    C = list_to_integer(io_lib:format("~b~b", [A,B])),
    part2({Target, [A*B|Values]}) orelse
    part2({Target, [A+B|Values]}) orelse
    part2({Target, [C|Values]}).
