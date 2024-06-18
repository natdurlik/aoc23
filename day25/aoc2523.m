(* ::Package:: *)

(* ::Input:: *)
(*input=Import["/home/leartsura/Documents/projects/aoc23/input"];*)


(* ::Input:: *)
(*lines:=StringSplit[input, "\n"]*)


(* ::Input:: *)
(*notEmpty[s_]:=s!=""*)


(* ::Input:: *)
(*wiring:=Select[notEmpty][StringSplit[#,{":"," "}]]&/@lines*)


(* ::Input:: *)
(*G=Flatten[Table[UndirectedEdge[#[[1]],#[[i]]],{i,2,Length[#]}]&/@wiring];*)


(* ::Input:: *)
(*Graph[G]*)


(* ::Input:: *)
(*FindEdgeCut[G]*)


(* ::Input:: *)
(*mincut=FindMinimumCut[G];*)


(* ::Input:: *)
(*mincut[[1]]*)
(*Apply[Times,Length[#]&/@mincut[[2]]]*)



