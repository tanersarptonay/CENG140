	/*king_theoden*/
	AddNewEdge(supernode, "riders_of_rohan");
	AddNewEdge(supernode, "eowyn");
	AddNewEdge(supernode, "eomer");
	AddNewEdge(supernode, "orcs");
	AddNewEdge(supernode, "aragorn");

	/*riders_of_rohan*/
	curr = EDGE(supernode)[0];
	AddEdge(curr, supernode);
	AddEdge(curr, EDGE(supernode)[2]);

	/*eomer*/
	curr = EDGE(supernode)[2];
	AddEdge(curr, supernode);

	/*eowyn*/
	curr = EDGE(supernode)[1];
	AddEdge(curr, supernode);
	AddNewEdge(curr, "merry");
	AddNewEdge(curr, "witch_king");

	/*merry*/
	AddEdge(EDGE(curr)[1], curr);

	/*witch_king*/
	curr = EDGE(curr)[2];
	AddEdge(curr, supernode);
	AddEdge(curr, EDGE(supernode)[3]);

	/*orcs*/
	AddEdge(EDGE(supernode)[3], curr);

	/*aragorn*/
	curr = EDGE(supernode)[4];
	AddEdge(curr, supernode);
	AddNewEdge(curr, "gimli");
	AddNewEdge(curr, "legolas");

	/*gimli*/
	AddEdge(EDGE(curr)[1], supernode);
	AddEdge(EDGE(curr)[1], curr);
	AddEdge(EDGE(curr)[1], EDGE(curr)[2]);

	/*legolas*/
	AddEdge(EDGE(curr)[2], supernode);
	AddEdge(EDGE(curr)[2], curr);
	AddEdge(EDGE(curr)[2], EDGE(curr)[1]);

	/*---------------------------------------------*/

	/*knights_of_gondor*/
	curr = AddNewEdge(supernode2, "gandalf");

	/*gandalf*/
	AddEdge(curr, supernode2);
	AddNewEdge(curr, "pippin");
	AddNewEdge(curr, "orcs");

	/*pippin*/
	curr = EDGE(curr)[1];
	AddEdge(curr, EDGE(supernode2)[0]);
	curr = AddNewEdge(curr, "faramir");

	/*faramir*/
	AddNewEdge(curr, "denethor");

	/*denethor*/
	AddEdge(EDGE(curr)[0], curr);

	/*orcs*/
	new = EDGE(EDGE(supernode2)[0])[2];
	curr = AddNewEdge(new, "witch_king");

	/*witch_king*/
	AddEdge(curr, new);
	AddEdge(curr, EDGE(supernode2)[0]);
	AddEdge(curr, supernode2);
