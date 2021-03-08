Thread Safe Nitesh Kumar Tiwari

class Node {
    private List<Node> child;
    private Node parent;
    private volatile AtomicInteger locked;
    private volatile AtomicInteger lockedChildNode;

    Node() {
        // Initialize child
        this.child = new ArrayList<>();
        this.parent = null;
        this.locked = 0;
        this.lockedChildNode = 0;
    }

}

    public boolean lock(Node node) {
        if (node.locked > 0)
            return true;

        node.locked++;// incr. first
        if (node.lockedChildNode > 0)
            return false;

        if (node.locked > 1) {// only allow first thread to enter
            node.locked--;
            return false;
        }

        // traverse upwards to check if any ancestors are locked
        Node parent;
        for (parent = node.getParent(); parent != null && node.locked; parent = node.getParent()) {
            if (parent == null)
                break;

            parent.lockedChildNode++;
            if (parent.locked > 0) {// <-Td
                node.locked = 0;
                parent.lockedChildNode--;
                break;
            }
        }

        // traverse the ancestors to update the locked child counter till the last
        // parent we traversed
        for (Node curr = node.getParent(); curr != parent && !node.locked; curr = node.getParent()) {
            if (curr == null)
                break;
            curr.lockedChildNode--;
        }

        return node.locked == 1;
    }

public boolean unlock(Node node){
    if(!node.isLocked()) return true;

    node.locked=0;//unlock the node
    //traverse the ancestors to update the locked child counter
    for(Node curr= node.getParent();curr!=null; curr= node.getParent()){
        if(curr == null) break;
        curr.lockedChildNode--;
    }

    return true;
}