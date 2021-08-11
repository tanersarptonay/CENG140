	/*frodo*/
	AddNewEdge(curr, "gandalf");
	AddNewEdge(curr, "bilbo" );
	AddNewEdge(curr, "sam");
	AddNewEdge(curr, "merry");
	AddNewEdge(curr, "the_ring");

	/*gandalf*/
	curr = EDGE(supernode)[0];
	AddEdge(curr, supernode);
	AddEdge(curr, EDGE(supernode)[1]);
	AddEdge(curr, EDGE(supernode)[4]);

	/*bilbo*/
	curr = EDGE(supernode)[1];
	AddEdge(curr, supernode);
	AddEdge(curr, EDGE(supernode)[0]);
	AddNewEdge(curr, "smeagol");
	AddEdge(curr, EDGE(supernode)[4]);

	/*smeagol*/
	curr = EDGE( EDGE(supernode)[1] )[2];
	AddEdge(curr, EDGE(supernode)[4]);

	/*sam*/
	curr = EDGE(supernode)[2];
	AddEdge(curr, supernode);
	AddEdge(curr, EDGE(supernode)[3]);

	/*merry*/
	curr = EDGE(supernode)[3];
	AddEdge(curr, EDGE(supernode)[2]);
	AddEdge(curr, supernode);
	
	/*-----------------------------------------------*/

	/*elrond*/
	curr = AddNewEdge(supernode2, "gandalf");
	AddNewEdge(supernode2, "legolas");
	AddNewEdge(supernode2, "boromir");
	AddNewEdge(supernode2, "gimli");

	/*gandalf*/
	AddEdge(curr, supernode2);

	/*legolas*/
	curr = EDGE(supernode2)[1];
	AddEdge(curr, supernode2);
	AddEdge(curr, EDGE(supernode2)[0]);
	new = curr = AddNewEdge(curr, "aragorn");

	/*aragorn*/
	AddEdge(curr, supernode2);
	curr = AddNewEdge(curr, "frodo");

	/*frodo*/
	AddEdge(curr, new);

	/*boromir*/
	curr = EDGE(supernode2)[2];
	AddEdge(curr, new);

	/*gimli*/
	curr = EDGE(supernode2)[3];
	AddEdge(curr, new);







----------------------



/*frodo*/
	IOAddNewEdge(curr, "gandalf");
	IOAddNewEdge(curr, "bilbo" );
	IOAddNewEdge(curr, "sam");
	IOAddNewEdge(curr, "merry");
	IOAddNewEdge(curr, "the_ring");

	/*gandalf*/
	curr = EDGE(supernode)[0];
	IOAddEdge(curr, supernode);
	IOAddEdge(curr, EDGE(supernode)[1]);
	IOAddEdge(curr, EDGE(supernode)[4]);

	/*bilbo*/
	curr = EDGE(supernode)[1];
	IOAddEdge(curr, supernode);
	IOAddEdge(curr, EDGE(supernode)[0]);
	IOAddNewEdge(curr, "smeagol");
	IOAddEdge(curr, EDGE(supernode)[4]);

	/*smeagol*/
	curr = EDGE( EDGE(supernode)[1] )[2];
	IOAddEdge(curr, EDGE(supernode)[4]);

	/*sam*/
	curr = EDGE(supernode)[2];
	IOAddEdge(curr, supernode);
	IOAddEdge(curr, EDGE(supernode)[3]);

	/*merry*/
	curr = EDGE(supernode)[3];
	IOAddEdge(curr, EDGE(supernode)[2]);
	IOAddEdge(curr, supernode);
	
	/*-----------------------------------------------*/

	/*elrond*/
	curr = IOAddNewEdge(supernode2, "gandalf");
	IOAddNewEdge(supernode2, "legolas");
	IOAddNewEdge(supernode2, "boromir");
	IOAddNewEdge(supernode2, "gimli");

	/*gandalf*/
	IOAddEdge(curr, supernode2);

	/*legolas*/
	curr = EDGE(supernode2)[1];
	IOAddEdge(curr, supernode2);
	IOAddEdge(curr, EDGE(supernode2)[0]);
	new = curr = IOAddNewEdge(curr, "aragorn");

	/*aragorn*/
	IOAddEdge(curr, supernode2);
	curr = IOAddNewEdge(curr, "frodo");

	/*frodo*/
	IOAddEdge(curr, new);

	/*boromir*/
	curr = EDGE(supernode2)[2];
	IOAddEdge(curr, new);

	/*gimli*/
	curr = EDGE(supernode2)[3];
	IOAddEdge(curr, new);