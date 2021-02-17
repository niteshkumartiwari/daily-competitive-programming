Thread Safe
Nitesh Kumar Tiwari



class Node{
    private List<Node> child;
    private Node parent;
    private boolean locked;
    private AtomicInteger lockedChildNode;
    private boolean inLockedProcess;

    Node(){
        //Initialize child
        this.child= new ArrayList<>();
        this.parent= null;
        this.locked = false;
        this.lockedChildNode=0;
        this.inLockedProcess=false;
        this.childNodesInProgress=false;
    }
}

public boolean lock(Node node){
    if(node.isLocked()) return true;

    //if some child is already locked
    if(node.getLockedChildNode() > 0) return false;

    //acquire lock for current node
    while(node.inLockedProcess || node.childNodesInProgress);
    node.inLockedProcess=true;

    //traverse upwards to check if any ancestors are locked
    for(Node curr= node.getParent();curr!=null; curr= node.getParent()){
        if(curr == null) break;
        while(curr.inLockedProcess);
        if(curr.isLocked()) return false;
        curr.childNodesInProgress=true;
    }

    //traverse the ancestors to update the locked child counter
    for(Node curr= node.getParent();curr!=null; curr= node.getParent()){
        if(curr == null) break;
        curr.incLockedChildNode(1);
        curr.childNodesInProgress=false;
    }
    
    node.setLocked(true);//lock the node
    
     //release the lock on current Node
    node.inLockedProcess=false;

    return true;
}

public boolean unlock(Node node){
    if(!node.isLocked()) return true;

    node.setLocked(false);//unlock the node
    //traverse the ancestors to update the locked child counter
    for(Node curr= node.getParent();curr!=null; curr= node.getParent()){
        if(curr == null) break;
        int val= curr.getLockedChildNode();
        curr.setLockedChildNode(val-1);
    }

    return true;
}