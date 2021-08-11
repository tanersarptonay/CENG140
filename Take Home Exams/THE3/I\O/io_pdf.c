	/*burhan*/
	AddNewEdge(supernode, "sacit");
AddNewEdge(supernode, "sahika");
AddNewEdge(supernode, "makbule");

/*sacit*/
curr = EDGE(supernode)[0];
curr = AddNewEdge(curr, "sertac");
AddEdge(curr, EDGE(supernode)[0]);

/*sahika*/
curr = EDGE(supernode)[1];
AddEdge(curr, EDGE(supernode)[0]);

/*makbule*/
curr = EDGE(supernode)[2];
AddEdge(curr, supernode);
AddEdge(curr, EDGE(supernode)[1]);

/*-------------------------------------------*/
/*makbule*/
AddNewEdge(supernode2, "sahika");
AddNewEdge(supernode2, "burhan");
	
/*sahika*/
curr = EDGE(supernode2)[0];
AddNewEdge(curr, "osman");
	
/*osman*/
curr = EDGE(curr)[0];
AddEdge(curr, EDGE(supernode2)[0]);
AddNewEdge(curr, "asli");

/*asli*/
curr = EDGE(curr)[1];
AddEdge(curr, EDGE(EDGE(supernode2)[0])[0] );
AddNewEdge(curr, "cem");

/*burhan*/
AddEdge(EDGE(supernode2)[1], curr);


-----------------------------------------------------


		/*burhan*/
	IOAddNewEdge(supernode, "sacit");
IOAddNewEdge(supernode, "sahika");
IOAddNewEdge(supernode, "makbule");

/*sacit*/
curr = EDGE(supernode)[0];
curr = IOAddNewEdge(curr, "sertac");
IOAddEdge(curr, EDGE(supernode)[0]);

/*sahika*/
curr = EDGE(supernode)[1];
IOAddEdge(curr, EDGE(supernode)[0]);

/*makbule*/
curr = EDGE(supernode)[2];
IOAddEdge(curr, supernode);
IOAddEdge(curr, EDGE(supernode)[1]);

/*-------------------------------------------*/
/*makbule*/
IOAddNewEdge(supernode2, "sahika");
IOAddNewEdge(supernode2, "burhan");
	
/*sahika*/
curr = EDGE(supernode2)[0];
IOAddNewEdge(curr, "osman");
	
/*osman*/
curr = EDGE(curr)[0];
IOAddEdge(curr, EDGE(supernode2)[0]);
IOAddNewEdge(curr, "asli");

/*asli*/
curr = EDGE(curr)[1];
IOAddEdge(curr, EDGE(EDGE(supernode2)[0])[0] );
IOAddNewEdge(curr, "cem");

/*burhan*/
IOAddEdge(EDGE(supernode2)[1], curr);