int X_DirectoryNode::insert(DataObject obj, X_Node **new_node)
{
SET_OF_MBR *s1, *s2;
X_Node *follow, *new_son;
int return_value;
follow = choose_subtree(obj); // choose a son node to insert obj into
return_value = follow->insert(obj, &new_son); // insert obj into subtree
update_mbr(follow->calc_mbr()); // update MBR of old son node
if (return_value == SPLIT){
add_mbr(new_son->calc_mbr()); // insert mbr of new son node into current node
if (num_of_mbrs() > CAPACITY){ // overflow occurs
if (split(mbrs, s1, s2) == TRUE){
// topological or overlap-minimal split was successfull
set_mbrs(s1);
*new_node = new X_DirectoryNode(s2);
return SPLIT;
}
else // there is no good split
{
*new_node = new X_SuperNode();
(*new_node)->set_mbrs(mbrs);
return SUPERNODE;
} }
} else if (return_value == SUPERNODE){ // node ‘follow’ becomes a supernode
remove_son(follow);
insert_son(new_son);
}
return NO_SPLIT;
}
