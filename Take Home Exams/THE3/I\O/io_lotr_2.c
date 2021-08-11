	/*uruk_hai*/
	AddNewEdge(supernode, "saruman");
	AddNewEdge(supernode, "ents");

	/*saruman*/
	curr = EDGE(supernode)[0];
	AddEdge(curr, supernode);
	curr = AddNewEdge(curr, "gandalf");

	/*gandalf*/
	AddEdge(curr, EDGE(supernode)[0]);
	new = AddNewEdge(curr, "eomer");
	AddNewEdge(curr, "king_theoden");

	/*eomer*/
	AddEdge(new, curr);

	/*king_theoden*/
	new = EDGE(EDGE(supernode)[0])[1]; /*gandalf*/
	curr = EDGE(new)[2];
	AddEdge(curr, new);

	/*ents*/
	curr = EDGE(supernode)[1];
	AddEdge(curr, supernode);
	AddNewEdge(curr, "pippin");
	AddNewEdge(curr, "merry");

	/*pippin*/
	curr = EDGE(EDGE(supernode)[1])[1];
	AddEdge(curr, EDGE(supernode)[1]);
	AddEdge(curr, EDGE(EDGE(supernode)[1])[2]);
	AddEdge(curr, new);

	/*merry*/
	curr = EDGE(EDGE(supernode)[1])[2];
	AddEdge(curr, EDGE(supernode)[1]);
	AddEdge(curr, EDGE(EDGE(supernode)[1])[1]);
	AddEdge(curr, new);

	/*----------------------------------------------*/

	/*king_theoden*/
	AddNewEdge(supernode2, "gamling");
	AddNewEdge(supernode2, "eomer");
	AddNewEdge(supernode2, "eowyn");
	AddNewEdge(supernode2, "aragorn");

	/*gamling*/
	AddEdge(EDGE(supernode2)[0], supernode2);

	/*eomer*/
	curr = EDGE(supernode2)[1];
	AddEdge(curr, supernode2);
	AddEdge(curr, EDGE(supernode2)[2]);

	/*eowyn*/
	curr = EDGE(supernode2)[2];
	AddEdge(curr, supernode2);
	AddEdge(curr, EDGE(supernode2)[1]);

	/*aragorn*/
	curr = EDGE(supernode2)[3];
	new = curr;
	AddEdge(curr, supernode2);
	AddNewEdge(curr, "legolas");
	AddNewEdge(curr, "gimli");
	AddNewEdge(curr, "haldir");

	/*legolas*/
	curr = EDGE(new)[1];
	AddEdge(curr, supernode2);
	AddEdge(curr, new);
	AddEdge(curr, EDGE(new)[2]);

	/*gimli*/
	curr = EDGE(new)[2];
	AddEdge(curr, supernode2);
	AddEdge(curr, new);
	AddEdge(curr, EDGE(new)[1]);

	/*haldir*/
	curr = EDGE(new)[3];
	AddEdge(curr, new);
	AddEdge(curr, EDGE(new)[1]);



------------------------------------------------


/*uruk_hai*/
	IOAddNewEdge(supernode, "saruman");
	IOAddNewEdge(supernode, "ents");

	/*saruman*/
	curr = EDGE(supernode)[0];
	IOAddEdge(curr, supernode);
	curr = IOAddNewEdge(curr, "gandalf");

	/*gandalf*/
	IOAddEdge(curr, EDGE(supernode)[0]);
	new = IOAddNewEdge(curr, "eomer");
	IOAddNewEdge(curr, "king_theoden");

	/*eomer*/
	IOAddEdge(new, curr);

	/*king_theoden*/
	new = EDGE(EDGE(supernode)[0])[1]; /*gandalf*/
	curr = EDGE(new)[2];
	IOAddEdge(curr, new);

	/*ents*/
	curr = EDGE(supernode)[1];
	IOAddEdge(curr, supernode);
	IOAddNewEdge(curr, "pippin");
	IOAddNewEdge(curr, "merry");

	/*pippin*/
	curr = EDGE(EDGE(supernode)[1])[1];
	IOAddEdge(curr, EDGE(supernode)[1]);
	IOAddEdge(curr, EDGE(EDGE(supernode)[1])[2]);
	IOAddEdge(curr, new);

	/*merry*/
	curr = EDGE(EDGE(supernode)[1])[2];
	IOAddEdge(curr, EDGE(supernode)[1]);
	IOAddEdge(curr, EDGE(EDGE(supernode)[1])[1]);
	IOAddEdge(curr, new);

	/*----------------------------------------------*/

	/*king_theoden*/
	IOAddNewEdge(supernode2, "gamling");
	IOAddNewEdge(supernode2, "eomer");
	IOAddNewEdge(supernode2, "eowyn");
	IOAddNewEdge(supernode2, "aragorn");

	/*gamling*/
	IOAddEdge(EDGE(supernode2)[0], supernode2);

	/*eomer*/
	curr = EDGE(supernode2)[1];
	IOAddEdge(curr, supernode2);
	IOAddEdge(curr, EDGE(supernode2)[2]);

	/*eowyn*/
	curr = EDGE(supernode2)[2];
	IOAddEdge(curr, supernode2);
	IOAddEdge(curr, EDGE(supernode2)[1]);

	/*aragorn*/
	curr = EDGE(supernode2)[3];
	new = curr;
	IOAddEdge(curr, supernode2);
	IOAddNewEdge(curr, "legolas");
	IOAddNewEdge(curr, "gimli");
	IOAddNewEdge(curr, "haldir");

	/*legolas*/
	curr = EDGE(new)[1];
	IOAddEdge(curr, supernode2);
	IOAddEdge(curr, new);
	IOAddEdge(curr, EDGE(new)[2]);

	/*gimli*/
	curr = EDGE(new)[2];
	IOAddEdge(curr, supernode2);
	IOAddEdge(curr, new);
	IOAddEdge(curr, EDGE(new)[1]);

	/*haldir*/
	curr = EDGE(new)[3];
	IOAddEdge(curr, new);
	IOAddEdge(curr, EDGE(new)[1]);
